/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "fatfs.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usb_host.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "files.h"
#include <string.h>
#include "screen.h"
#include "debug.h"

#include "arm_math.h"
#include "arm_const_structs.h"

#include "dsp.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

// size of DMA buffer
#define BUFF_SIZE 4096

#define BUFF_HALF BUFF_SIZE / 2

#define READ_BUFFER_SIZE FFT_SIZE

#define TITLE_SIZE 40


// limits of digital input for ultrasound detection
#define RECORD_MAX_LIM 1500

#define RECORD_MIN_LIM 500

// sampling frequency
#define FREQUENCY 96000

#define TIME 3

#define SAMPLES_NUM FREQUENCY * TIME

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */


typedef enum state_t {
	IDLE,
	MOUNTING,
	MOUNTED,
	RECORDING_START,
	RECORDING,
	COPY_FIRST_HALF,
	COPY_SECOND_HALF,
	RECORDING_STOP,
	PROCESSING
} state_t;

volatile state_t state = IDLE;

uint16_t ADC_Buffer[BUFF_SIZE];

volatile uint16_t current_index = 0;



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_USB_HOST_Process(void);

/* USER CODE BEGIN PFP */

//writes buffer data to specific file starting from specific index
// (adds number of written samples from "written")
void write_buffer(
		usb_file_t* usb_file, uint16_t* buffer,
		uint16_t start, uint16_t amount, uint32_t* written
		);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern ApplicationTypeDef Appli_state;


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	FATFS flashdrive;
	usb_file_t wav_file;
	usb_file_t info_file;
	usb_file_t raw_data_file;
	uint32_t written = 0;

	char title[TITLE_SIZE];
	char info_title[TITLE_SIZE];

	float32_t magnitude;
	uint32_t index;
	float32_t frequency;
	uint16_t prev;

	uint16_t to_read;

	uint16_t Read_Buffer[READ_BUFFER_SIZE];

	uint16_t Temporary_Buffer[READ_BUFFER_SIZE];

	float32_t FFT_Buffer[FFT_BUFFER_SIZE];


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */


  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USB_HOST_Init();
  MX_RTC_Init();
  MX_TIM3_Init();
  MX_ADC1_Init();
  MX_FATFS_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim3);
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*) ADC_Buffer, BUFF_SIZE);


  create_header(&wav_file, FREQUENCY, TIME, 4);
  raw_data_file.title = "raw_data.wav";



/*
	main_screen_init();
  println("DEVICE IS\n READY!");
*/
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    MX_USB_HOST_Process();

    /* USER CODE BEGIN 3 */
    switch(state) {
    case MOUNTING:
    	//HAL_GPIO_TogglePin(LD6_GPIO_Port, LD6_Pin);
    	//clear_print("MOUNTING USB\n FLASHDRIVE...");
    	send_signal(f_mount(&flashdrive, USBHPath, 1));
    	//println("MOUNTED");
    	HAL_Delay(1000);

    	state = MOUNTED;
    	break;

    case RECORDING_START:
    	// creates file for saving samples
    	HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
    	create_file(&raw_data_file);
    	state = RECORDING;
    	break;

    case COPY_FIRST_HALF:
    	state = RECORDING;
    	// copying first half of buffer to file
    	write_buffer(&raw_data_file, ADC_Buffer, 0, BUFF_HALF, &written);
    	break;

    case COPY_SECOND_HALF:
    	state = RECORDING;
    	// copying second half of buffer to file
    	write_buffer(&raw_data_file, ADC_Buffer, BUFF_HALF, BUFF_HALF, &written);
    	break;

    case RECORDING_STOP:
    	HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
    	// closing file to save it
    	close_file(&raw_data_file);
    	state = PROCESSING;
    	//clear_print("RECORDED TO");
    	//println(title);
    	//println("WAITING FOR\n COMMANDS");
    	break;

    case PROCESSING:
    	HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
    	HAL_GPIO_TogglePin(LD6_GPIO_Port, LD6_Pin);

    	// creating wav file for our audio
    	generate_title(title, "%dh%dm%ds.wav", TITLE_SIZE);
    	wav_file.title = title;
    	create_file(&wav_file);
    	write_header(&wav_file);

    	// creating info file for measured frequencies and intensities
    	generate_title(info_title, "%dh%dm%ds.txt", TITLE_SIZE);
    	info_file.title = info_title;
    	create_file(&info_file);

    	// opening raw data to read it
    	read_file(&raw_data_file);

    	// initializing FIR filter
    	init_filter();

    	prev = FIRST_SIGNAL;

    	while (written > 0) {
    		HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);

    		if (written >= READ_BUFFER_SIZE) {
    			to_read = READ_BUFFER_SIZE;
    		}
    		else {
    			to_read = written;
    		}
    		written -= to_read;

    		// reading data and filtering it with linear filter for
    		// calculating frequencies
    		read_buffer(&raw_data_file, Read_Buffer, to_read);
    		linear_filter(Read_Buffer, prev, READ_BUFFER_SIZE, Temporary_Buffer);

    		// using High-Pass filter on our data
    		fir_filter(Read_Buffer);
    		// saving  filtered data to wav file
    		write_little_endian_data(&wav_file, Read_Buffer, to_read);

    		// performing FFT and calculating main frequency
    		// for data filtered with linear filter
    		perform_fft(Temporary_Buffer, 0, FFT_Buffer);
    		calculate_magnitudes(FFT_Buffer, &magnitude, &index);
    		frequency = get_frequency(index, FREQUENCY);
    		write_array(&info_file, &frequency, 1);

    		if (written == 0) {
    			break;
    		}

    		if (prev == 0) {
    			write_array(&info_file, FFT_Buffer, FFT_BUFFER_SIZE);
    		}

    		// setting prev variable for next linear filter
    		// cycle
    		prev = Temporary_Buffer[READ_BUFFER_SIZE - 1];


    	}
    	// closing all files
    	close_file(&raw_data_file);
    	close_file(&wav_file);
    	close_file(&info_file);

    	HAL_GPIO_TogglePin(LD6_GPIO_Port, LD6_Pin);
    	HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
    	state = MOUNTED;
    default:
    	break;
    }


  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN) {
	if (GPIO_PIN == BUTTON_Pin){

		switch(state) {

		case IDLE:
			// mounting usb after button press
			if (Appli_state == APPLICATION_READY) {
				HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
			    state = MOUNTING;
			}
			else {
				HAL_GPIO_TogglePin(LD5_GPIO_Port, LD5_Pin);
			}
			break;

		case MOUNTED:
			// recording after button press
			HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
			state = RECORDING_START;
			break;

		default:
			break;
		}

	}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if (htim->Instance == TIM3){
		if (current_index >= BUFF_SIZE){
			current_index = 0;
		}
		// ultrasound detected
		if (
			state == MOUNTED && (ADC_Buffer[current_index] >= RECORD_MAX_LIM
			|| ADC_Buffer[current_index] <= RECORD_MIN_LIM)

		) {
			state = RECORDING_START;
			HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
		}
		current_index += 1;
	}
}


void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc){
	if (state == RECORDING) {
		state = COPY_FIRST_HALF;
	}
	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	if (state == RECORDING) {
		state = COPY_SECOND_HALF;
	}
	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
}



void write_buffer(
		usb_file_t* usb_file, uint16_t* buffer,
		uint16_t start, uint16_t amount, uint32_t* written)
{
	HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_SET);

	// if we don't have enough memory in our file
	// for full buffer
	if (*written + amount > SAMPLES_NUM) {
		amount = SAMPLES_NUM - *written;
		state = RECORDING_STOP;
	}

	write_data(usb_file, buffer + start, amount);
	*written += amount;
	HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);

}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
