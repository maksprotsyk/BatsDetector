#ifndef INC_FILES_H_
#define INC_FILES_H_

#include "fatfs.h"
#include "debug.h"
#include "main.h"
#include "rtc.h"
#include "arm_math.h"

// wav file header size
#define HEADER_SIZE 44

// max size of one string message sent to usb
// ("write_array" function)
#define ONE_MESSAGE 40

// max amount of data that can be sent with "write_little_endian_data"
#define MAX_LITTLE_ENDIAN_SIZE 4096

// for using RTS to name files
RTC_TimeTypeDef current_time = {0};
RTC_DateTypeDef current_date = {0};

// message which we use to send string data
char message[ONE_MESSAGE];


typedef struct usb_file
{
	char* title;
	FIL file;
	uint8_t header[HEADER_SIZE];

} usb_file_t;


// convert big-endian to little and vice versa
uint16_t reverse_bytes(uint16_t num);


// gets respective byte of 32bit number
uint8_t get_byte(uint32_t num, uint8_t byte_num);


// creates header for the wav file given sampling frequency, duration in seconds
// and slowdown coefficient
void create_header(
		usb_file_t* wav_file, uint32_t frequency,
		uint32_t duration, uint32_t slowdown
		);

// creates the given file on the USB disk
void create_file(usb_file_t* usb_file);


// writes header of the file to the respective file on USB disk
// returns number of successfully written bytes
UINT write_header(usb_file_t* usb_file);

// writes data of the given size to the respective file on USB disk
// returns number of successfully written bytes
UINT write_data(usb_file_t* usb_file, uint16_t* data, uint16_t size);


// writes data of the given size to the respective file on USB disk
// and changes the order of bytes in all uint16_t
// returns number of successfully written bytes
UINT write_little_endian_data(usb_file_t* usb_file, uint16_t* data, uint16_t size);


// closes respective file on USB disk
void close_file(usb_file_t* usb_file);


// opens respective file for reading
void read_file(usb_file_t* usb_file);


// writes str of given size to the respective file on USB disk
UINT write_str(usb_file_t* usb_file, char* message, uint16_t size);


// writes array of floats to respective file on USB disk
// (sends them as strings (before that converts to integer)
void write_array(usb_file_t* info_file, float32_t* data, uint16_t size);

// reads data of given size (number of uin16_t)
// from respective file on USB disk to the given
// buffer
UINT read_buffer(usb_file_t* info_file, uint16_t* buffer,  uint16_t size);


// generates title using template and current time
void generate_title(char* title , const char* template, uint16_t title_size);



uint16_t reverse_bytes(uint16_t num) {
	return ((num & 0x00FF) << 8) | (num >> 8);
}


uint8_t get_byte(uint32_t num, uint8_t byte_num) {
	return (uint8_t) (num >> (8 * byte_num));
}


void create_header(usb_file_t* wav_file, uint32_t frequency, uint32_t duration, uint32_t slowdown) {

	// sample size is 2 bytes
	uint32_t data_size = 2 * duration * frequency;

	uint32_t full_size = data_size + HEADER_SIZE;

	uint32_t byte_rate = 2 * frequency / slowdown;

	frequency /= slowdown;

	// creating header with 0 on unfilled indices
	uint8_t header[HEADER_SIZE] = {
			'R', 'I', 'F', 'F',
			0, 0, 0, 0,
		    'W', 'A', 'V', 'E',
			'f', 'm', 't', ' ',
			0x10, 0x00, 0x00, 0x00,
			0x01, 0x00, 0x01, 0x00,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0x02, 0x00, 0x10, 0x00,
			'd', 'a', 't', 'a',
			0, 0, 0, 0
	};


	for (uint8_t i = 0; i < 4; i++) {
		header[4+i] = get_byte(full_size, i);
		header[24+i] = get_byte(frequency, i);
		header[28+i] = get_byte(byte_rate, i);
		header[40+i] = get_byte(data_size, i);

	}
	for (uint8_t i = 0; i < HEADER_SIZE; i++) {
		wav_file->header[i] = header[i];
	}

}


void create_file(usb_file_t* usb_file) {
	send_signal(
			f_open(&usb_file->file,
					usb_file->title,
				  FA_CREATE_ALWAYS | FA_WRITE)
				  );
}

UINT write_header(usb_file_t* usb_file) {
	UINT bytes_written;
	send_signal(
			f_write(
					&usb_file->file,
					usb_file->header,
					HEADER_SIZE,
					&bytes_written)
					);
	return bytes_written;
}


UINT write_data(usb_file_t* usb_file, uint16_t* data, uint16_t size) {
	UINT bytes_written;
	send_signal(
			f_write(
					&usb_file->file,
					data,
					sizeof(uint16_t) * size,
					&bytes_written)
					);
	return bytes_written;
}


UINT write_little_endian_data(usb_file_t* usb_file, uint16_t* data, uint16_t size) {
	uint16_t little_endian_data[MAX_LITTLE_ENDIAN_SIZE];
	for (uint16_t i = 0; i < size; i++) {
		little_endian_data[i] = reverse_bytes(data[i]);
	}
	return write_data(usb_file, little_endian_data, size);
}



void close_file(usb_file_t* usb_file) {
	send_signal(f_close(&usb_file->file));
}


void read_file(usb_file_t* usb_file) {
	send_signal(
				f_open(&usb_file->file,
						usb_file->title,
						FA_OPEN_EXISTING | FA_READ)
				);
}



UINT write_str(usb_file_t* usb_file, char* message, uint16_t size) {
	UINT bytes_written;
	send_signal(
			f_write(&usb_file->file,
			message,
			size,
			&bytes_written)
			);
	return bytes_written;
}


void write_array(usb_file_t* info_file, float32_t* data, uint16_t size) {
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

UINT read_buffer(usb_file_t* info_file, uint16_t* buffer,  uint16_t size) {
	UINT bytes_read;
	send_signal(
			f_read(
					&info_file->file,
					buffer,
					sizeof(uint16_t) * size,
					&bytes_read)
					);

	return bytes_read;
}

void generate_title(char* title , const char* template, uint16_t title_size) {
	HAL_RTC_GetTime(&hrtc, &current_time, RTC_FORMAT_BIN);
	snprintf(title, title_size, template, current_time.Hours,
           	 current_time.Minutes, current_time.Seconds);
	HAL_RTC_GetDate(&hrtc, &current_date, RTC_FORMAT_BIN);
}


#endif /* INC_FILES_H_ */
