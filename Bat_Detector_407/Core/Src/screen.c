/*
 * screen.c
 *
 *  Created on: Jan 17, 2021
 *      Author: mprotsyk
 */

#include "screen.h"



void main_screen_init() {
	  MAIN_SCREEN.hw_conf.spi_handle = &hspi2;
	  MAIN_SCREEN.hw_conf.spi_cs_pin =  CS_Pin;
	  MAIN_SCREEN.hw_conf.spi_cs_port = CS_GPIO_Port;
	  MAIN_SCREEN.hw_conf.rst_pin =  RST_Pin;
	  MAIN_SCREEN.hw_conf.rst_port = RST_GPIO_Port;
	  MAIN_SCREEN.hw_conf.dc_pin =  DC_Pin;
	  MAIN_SCREEN.hw_conf.dc_port = DC_GPIO_Port;
	  MAIN_SCREEN.def_scr = lcd5110_def_scr;
	  LCD5110_init(&MAIN_SCREEN.hw_conf, LCD5110_NORMAL_MODE, 0x40, 2, 3);
}



void println(char* str) {
	LCD5110_printf(&MAIN_SCREEN, BLACK, "%s\n", str);
}

void clear_print(char* str) {
	LCD5110_clear_scr(&MAIN_SCREEN);
	LCD5110_set_cursor(0, 0, &MAIN_SCREEN);
	println(str);
}
