/*
 * screen.h
 *
 */

#ifndef INC_SCREEN_H_
#define INC_SCREEN_H_

#include "lcd5110.h"
#include "pins.h"
#include "stm32f4xx_hal.h"


int initialise_LCD(LCD5110_display* lcd, SPI_HandleTypeDef* hspi);

#endif /* INC_SCREEN_H_ */
