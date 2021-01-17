/*
 * debug.h
 *
 *  Created on: Jan 7, 2021
 *      Author: mprotsyk
 */

#ifndef INC_DEBUG_H_
#define INC_DEBUG_H_

#include "main.h"
#include "fatfs.h"


// sends red led signal if the result of operation is not OK
void send_signal(FRESULT op_res);



#endif /* INC_DEBUG_H_ */
