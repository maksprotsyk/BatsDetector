# BatsDetector

BatsDetector is a project focused on studying bats by detecting the ultrasound they emit.
Our device can record the ultrasound, process it, and acquire useful information, such as the frequency of the signal.

## Hardware

BatsDetector is based on the STM32F407VE microcontroller.
It uses the piezoelectric sensor from the HC-SR04 rangefinder together with the
MAX9812L gain module to detect ultrasound to the best of our capabilities.

We also connect to the Nokia 5110 LCD-display to always monitor the status of our device.

## Software

BatsDetector essentially does two things:
- It listens to its surroundings and awaits an ultrasonic signal. 
- When it detects any, the device then records it, computes the frequency and the intensity of the signal, and creates a copy that is slowed down to be heard by a human for testing potential.

This is done in a few steps:
1) First, the microphone module constantly feeds samples of its data into an ADC (Analog-Digital Converter) where our microprocessor is listening to it and waiting for a signal of certain strength. Since our microphone is by far most sensitive to frequencies around ~40kHz, which is just what we need, a sound in that range will be much more audible than others.
2) When an ultrasonic signal is detected, the microprocessor instantly starts recording the sound for 3 seconds using DMA (Direct Memory Access). Before that, though, the signal passes through a few high-pass and linear filters, which cleans it up and highlighting the important high frequencies. The sound is then written to a `.wav` file.
3) Meanwhile, the same sound also goes through an FFT (Fast Fourier Transform), which computes the magnitude of different ranges of frequencies in the signal, allowing us to find out the leading one (our ultrasound). Then, using the magnitude of that specific frequency from the transform, we can calculate the intensity of our ultrasound.
