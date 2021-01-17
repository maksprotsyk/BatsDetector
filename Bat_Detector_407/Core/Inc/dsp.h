/*
 * dsp.h
 *
 *  Created on: Jan 16, 2021
 *      Author: mprotsyk
 */

#ifndef INC_DSP_H_
#define INC_DSP_H_

#include "arm_math.h"
#include "arm_const_structs.h"
#include "main.h"

// number of samples for fast Fourier transformation model
#define FFT_SIZE 512

// buffer size (we also have to work with imaginary part)
#define FFT_BUFFER_SIZE 2 * FFT_SIZE

// number of coefficients for FIR filter
#define COEFFICIENTS 25

// Median of our collected ADC values (2^12 / 2)
#define MEDIAN 2048

// Number which shows that the current signal was sent first
#define FIRST_SIGNAL 0


float32_t FILTER_COEFFICIENTS[COEFFICIENTS] = {
		-0.0052,
		0.0099,
		0.0057,
		-0.0206,
		-0.0063,
		0.0343,
		0.0069,
		-0.0555,
		-0.0080,
		0.1013,
		0.0085,
		-0.3167,
		0.4914,
		-0.3167,
		0.0085,
		0.1013,
		-0.0080,
		-0.0555,
		0.0069,
		0.0343,
		-0.0063,
		-0.0206,
		0.0057,
		0.0099,
		-0.0052
};

arm_fir_instance_f32 FILTER;

float32_t FILTER_STATES[FFT_SIZE + COEFFICIENTS - 1];


// calculates mean of given buffer of size FFT_SIZE
void calculate_mean(uint16_t* data_buffer, float32_t* mean);


// performs FFT on given buffer from the start index (takes FFT_SIZE values)
// and saves results to fft_buffer
void perform_fft(uint16_t* data_buffer, uint32_t start,  float32_t* fft_buffer);


// calculates max magnitude  got from FFT
// and saves it with its index
void calculate_magnitudes(float32_t* fft_buffer, float32_t* magnitude, uint32_t* index);


// calculates the most significant frequency by index of the max magnitude
// and sampling frequency
float32_t get_frequency(uint32_t index, uint32_t frequency);



// initializes FIR High-Pass filter
void init_filter();

// Performs FIR-filter filtration on the given buffer
// (buffer should be of size FFT_SIZE
void fir_filter(uint16_t* buffer);


// performs Linear filtration on the given buffer and saves calculated values to result
// size - size of buffer array (as well as result)
// prev - last got filtered value (if == FIRST_SIGNAL, is not used)
void linear_filter(uint16_t* buffer, uint16_t prev, uint16_t size, uint16_t* result);



void perform_fft(uint16_t* data_buffer, uint32_t start,  float32_t* fft_buffer) {
	float32_t mean;
	calculate_mean(data_buffer, &mean);

	for (uint16_t i = 0; i < FFT_SIZE; i++) {
		fft_buffer[2 * i] = (float32_t)data_buffer[i] - mean;
		fft_buffer[2 * i + 1] = 0;
	}
	arm_cfft_f32(&arm_cfft_sR_f32_len512, fft_buffer, 0, 1);

}


void calculate_mean(uint16_t* data_buffer, float32_t* mean) {
	uint32_t sum = 0;
	for (int i = 0; i < FFT_SIZE; i++) {
		sum += data_buffer[i];
	}
	*mean = ((float32_t) sum) / FFT_SIZE;
}


void calculate_magnitudes(float32_t* fft_buffer, float32_t* magnitude, uint32_t* index){
	float32_t magnitudes[FFT_SIZE];
	arm_cmplx_mag_f32(fft_buffer, magnitudes, FFT_SIZE);
	arm_max_f32(magnitudes, FFT_SIZE, magnitude, index);
}


float32_t get_frequency(uint32_t index, uint32_t frequency) {
	if (index > (FFT_SIZE / 2)) {
		index = FFT_SIZE - index;
	}
	return frequency * ((float32_t) index) / FFT_SIZE;
}



void init_filter() {
	arm_fir_init_f32(
			&FILTER, COEFFICIENTS,
			FILTER_COEFFICIENTS,
			FILTER_STATES, FFT_SIZE
			);
}


void fir_filter(uint16_t* buffer) {
	float32_t float_buffer[FFT_SIZE];
	float32_t float_result[FFT_SIZE];
	for (uint16_t i = 0; i < FFT_SIZE; i++) {
		float_buffer[i] = (float32_t)buffer[i] - MEDIAN;
	}
	arm_fir_f32(&FILTER, float_buffer, float_result, FFT_SIZE);
	for (uint16_t i = 0; i < FFT_SIZE; i++) {
			buffer[i] = (uint16_t) float_result[i] + MEDIAN;
		}
}

void linear_filter(uint16_t* buffer, uint16_t prev, uint16_t size, uint16_t* result) {
	if (prev == FIRST_SIGNAL) {
		prev = buffer[0];
	}
	result[0] = (15 * prev + buffer[0]) >> 4;
	for (int i = 1; i < size; i++) {
		result[i] = (15 * result[i-1] + buffer[i]) >> 4;
	}
}




#endif /* INC_DSP_H_ */
