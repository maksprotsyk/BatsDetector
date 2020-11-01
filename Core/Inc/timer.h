/*
 * timer.h
 *
 *  Created on: Nov 1, 2020
 *      Author: mprotsyk
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "stm32f4xx_hal.h"

void mydelay (uint16_t mcs, TIM_HandleTypeDef* timer);

void restart_timer (TIM_HandleTypeDef* timer);

uint16_t get_timer (TIM_HandleTypeDef* timer);

#endif /* INC_TIMER_H_ */
