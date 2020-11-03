/*
 * range_finder.c
 *
 */

#include "range_finder.h"


int impulse_time(TIM_HandleTypeDef* timer){
    uint16_t start = HAL_GetTick();
    HAL_GPIO_WritePin(RangePort, TrigPin, GPIO_PIN_SET);
    mydelay(16, timer);
    HAL_GPIO_WritePin(RangePort, TrigPin, GPIO_PIN_RESET);
    while(HAL_GPIO_ReadPin(RangePort, EchoPin) == GPIO_PIN_RESET )
    {
    	if (HAL_GetTick() - start > MAX_DELAY){
    		return -1;
    	}
    }
    restart_timer(timer);
    while(HAL_GPIO_ReadPin(RangePort, EchoPin) == GPIO_PIN_SET )
    {
    	if (HAL_GetTick() - start > MAX_DELAY){
    		return -1;
    	}
    }
    return get_timer(timer);
}

float distance_with_time(int time){
	return (340. / 20000.) * time;
}

float calculate_distance(TIM_HandleTypeDef* timer){
	int time = impulse_time(timer);
	if (time == -1){
		return -1;
	}
	return distance_with_time(time);
}


_Bool check_ultrasound(int impulse, TIM_HandleTypeDef* timer){
	int new_impulse = impulse_time(timer);
	if (new_impulse == -1){
		return 1;
	}

	_Bool obstacle = ((new_impulse >= (2000 + impulse)) || ((new_impulse + 2000) <= impulse));
	new_impulse = impulse_time(timer);
	obstacle = obstacle && ((new_impulse >= (2000 + impulse)) || ((new_impulse + 2000) <= impulse));

	return obstacle;
}

