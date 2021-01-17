/*
 * screen.h
 *
 *  Created on: Jan 8, 2021
 *      Author: mprotsyk
 */

#ifndef INC_SCREEN_H_
#define INC_SCREEN_H_

#include "lcd5110.h"
#include "main.h"


LCD5110_display MAIN_SCREEN;


// initializes LCD5110_display with specific pins
void main_screen_init();

// simply prints string + \n on the screen
void println(char* str);

// clears the screen and then display string at the beginning
// (add \n)
void clear_print(char* str);




#endif /* INC_SCREEN_H_ */
