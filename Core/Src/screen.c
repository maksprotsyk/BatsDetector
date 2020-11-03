/*
 * screen.c
 *
 */


#include "screen.h"

int initialise_LCD(LCD5110_display* lcd, SPI_HandleTypeDef* hspi){
	if (!lcd || !hspi){
		return -1;
	}
	lcd->hw_conf.spi_handle = hspi;
	lcd->hw_conf.spi_cs_pin =  CS_Pin;
	lcd->hw_conf.spi_cs_port = CS_Port;
	lcd->hw_conf.rst_pin =  RST_Pin;
	lcd->hw_conf.rst_port = RST_Port;
	lcd->hw_conf.dc_pin =  DC_Pin;
	lcd->hw_conf.dc_port = DC_Port;
	lcd->def_scr = lcd5110_def_scr;
	LCD5110_init(&(lcd->hw_conf), LCD5110_NORMAL_MODE, 0x40, 2, 3);
	return 0;
}
