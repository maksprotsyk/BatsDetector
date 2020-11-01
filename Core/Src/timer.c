/*
 * timer.c
 *
 *  Created on: Nov 1, 2020
 *      Author: mprotsyk
 */
#include "timer.h"

void mydelay (uint16_t mcs, TIM_HandleTypeDef* timer)
{
	__HAL_TIM_SET_COUNTER(timer,0);
	while (__HAL_TIM_GET_COUNTER(timer) < mcs);
}


void restart_timer (TIM_HandleTypeDef* timer){
	__HAL_TIM_SET_COUNTER(timer,0);
}


uint16_t get_timer (TIM_HandleTypeDef* timer)
{
	return __HAL_TIM_GET_COUNTER(timer);

}


