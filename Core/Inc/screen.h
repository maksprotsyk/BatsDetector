/*
 * screen.h
 *
 *  Created on: Nov 1, 2020
 *      Author: mprotsyk
 */

#ifndef INC_SCREEN_H_
#define INC_SCREEN_H_

#include "stm32f4xx_hal.h"
#include "timer.h"

// defining pins for data
#define Data_Port GPIOD
#define D4_PIN GPIO_PIN_8
#define D5_PIN GPIO_PIN_9
#define D6_PIN GPIO_PIN_10
#define D7_PIN GPIO_PIN_11

//defining rs and e pins
#define RS_Pin GPIO_PIN_0
#define Write_Port GPIOE
#define Write_Pin GPIO_PIN_1

#define MaxSize 32;

enum errors {TooLongMessage = -1};

void send_half_byte(uint8_t num, TIM_HandleTypeDef* timer){
	HAL_GPIO_WritePin(Data_Port, D4_PIN, num % 2);
	num /= 2;
	HAL_GPIO_WritePin(Write_Port, Write_Pin, GPIO_PIN_SET);
	mydelay(12, timer);
	HAL_GPIO_WritePin(Write_Port, Write_Pin, GPIO_PIN_RESET);
	mydelay(50, timer);

	HAL_GPIO_WritePin(Data_Port, D5_PIN, num % 2);
	num /= 2;
	HAL_GPIO_WritePin(Write_Port, Write_Pin, GPIO_PIN_SET);
	mydelay(12, timer);
	HAL_GPIO_WritePin(Write_Port, Write_Pin, GPIO_PIN_RESET);
	mydelay(50, timer);
	HAL_GPIO_WritePin(Data_Port, D6_PIN, num % 2);
	num /= 2;
	HAL_GPIO_WritePin(Write_Port, Write_Pin, GPIO_PIN_SET);
	mydelay(12, timer);
	HAL_GPIO_WritePin(Write_Port, Write_Pin, GPIO_PIN_RESET);
	mydelay(50, timer);

	HAL_GPIO_WritePin(Data_Port, D7_PIN, num % 2);
	num /= 2;
	HAL_GPIO_WritePin(Write_Port, Write_Pin, GPIO_PIN_SET);
	mydelay(12, timer);
	HAL_GPIO_WritePin(Write_Port, Write_Pin, GPIO_PIN_RESET);
	mydelay(50, timer);
}

void send_byte(uint8_t num, TIM_HandleTypeDef* timer){
	send_half_byte(num & 0xF, timer);
	send_half_byte((num >> 4) & 0xF, timer);
}

int send_char(char c, TIM_HandleTypeDef* timer){
	HAL_GPIO_WritePin(Write_Port, RS_Pin, GPIO_PIN_SET);
	send_byte(c, timer);
	return 0;
}

int command(uint8_t num, TIM_HandleTypeDef* timer){
	HAL_GPIO_WritePin(Write_Port, RS_Pin, GPIO_PIN_RESET);
	send_byte(num, timer);
}


int write(char* str, TIM_HandleTypeDef* timer){
    uint8_t index = 0;
    while (str[index] != '\0'){
    	if (index > 31){
    		return TooLongMessage;
    	}

        send_char(str[index], timer);
        index += 1;
    }
    return 0;
}


#endif /* INC_SCREEN_H_ */
