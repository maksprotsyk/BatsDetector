/*
 * debug.c
 *
 *  Created on: Jan 7, 2021
 *      Author: mprotsyk
 */

#include "debug.h"

void send_signal(FRESULT op_res){
	if (op_res != FR_OK){
		HAL_GPIO_TogglePin(LD5_GPIO_Port, LD5_Pin);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(LD5_GPIO_Port, LD5_Pin);
		//clear_print("Error!!!");
	}

}
