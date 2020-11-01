/*
 * screen.h
 *
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

void send_half_byte(uint8_t num, TIM_HandleTypeDef* timer);

void send_byte(uint8_t num, TIM_HandleTypeDef* timer);

void send_char(char c, TIM_HandleTypeDef* timer);

void command(uint8_t num, TIM_HandleTypeDef* timer);

int write(char* str, TIM_HandleTypeDef* timer);

#endif /* INC_SCREEN_H_ */
