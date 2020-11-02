/*
 * screen.h
 *
 */

#ifndef INC_SCREEN_H_
#define INC_SCREEN_H_

#include "stm32f4xx_hal.h"
#include "timer.h"
#include "pins.h"



#define MaxSize 32;

enum errors {TooLongMessage = -1};

void send_half_byte(uint8_t num, TIM_HandleTypeDef* timer);

void send_byte(uint8_t num, TIM_HandleTypeDef* timer);

void send_char(char c, TIM_HandleTypeDef* timer);

void command(uint8_t num, TIM_HandleTypeDef* timer);

int write(char* str, TIM_HandleTypeDef* timer);

#endif /* INC_SCREEN_H_ */
