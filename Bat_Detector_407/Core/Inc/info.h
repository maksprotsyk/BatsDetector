/*
 * info.h
 *
 *  Created on: Jan 9, 2021
 *      Author: mprotsyk
 */

#ifndef INC_INFO_H_
#define INC_INFO_H_

#include "fatfs.h"
#include "debug.h"
#include "main.h"
#include "arm_math.h"



typedef struct info_file
{
	char* title;
	FIL file;

} info_file_t;


#define ONE_MESSAGE 40

char message[ONE_MESSAGE];

void create_info(info_file_t* info_file) {
	send_signal(
			f_open(&info_file->file,
				   info_file->title,
				  FA_CREATE_ALWAYS | FA_WRITE)
				  );
}

void close_info(info_file_t* info_file) {
	send_signal(f_close(&info_file->file));
}

void write_array(info_file_t* info_file, float32_t* data, uint16_t size) {
	UINT bytes_written;

	for (uint16_t i = 0; i < size; i++) {
		snprintf(message, ONE_MESSAGE, "%ld ", (int32_t) data[i]);
		send_signal(
					f_write(&info_file->file,
							message,
							sizeof(message),
							&bytes_written)
							);
	}

	send_signal(
				f_write(&info_file->file,
					    "\n",
						1,
						&bytes_written)
						);


}


void write_str(info_file_t* info_file, char* message, uint16_t size) {
	UINT bytes_written;
	send_signal(
			f_write(&info_file->file,
			message,
			size,
			&bytes_written)
			);
}





#endif /* INC_INFO_H_ */
