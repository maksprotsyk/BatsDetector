/*
 * range_finder.h
 *
 */

#ifndef INC_RANGE_FINDER_H_
#define INC_RANGE_FINDER_H_

#include "stm32f4xx_hal.h"
#include "timer.h"
#include "pins.h"

#define MAX_DELAY 58

int impulse_time(TIM_HandleTypeDef* timer);

float distance_with_time(int time);

float calculate_distance(TIM_HandleTypeDef* timer);


_Bool check_ultrasound(int impulse, TIM_HandleTypeDef* timer);

#endif /* INC_RANGE_FINDER_H_ */
