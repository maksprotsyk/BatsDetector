################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD5110/Src/lcd5110.c \
../LCD5110/Src/lcd5110_hal.c \
../LCD5110/Src/lcd5110_ll.c 

OBJS += \
./LCD5110/Src/lcd5110.o \
./LCD5110/Src/lcd5110_hal.o \
./LCD5110/Src/lcd5110_ll.o 

C_DEPS += \
./LCD5110/Src/lcd5110.d \
./LCD5110/Src/lcd5110_hal.d \
./LCD5110/Src/lcd5110_ll.d 


# Each subdirectory must supply rules for building sources it contributes
LCD5110/Src/lcd5110.o: ../LCD5110/Src/lcd5110.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I"/Users/mprotsyk/UCU/POC/project_new/Bat_Detector_407/LCD5110/Inc" -I"/Users/mprotsyk/UCU/POC/project_new/Bat_Detector_407/DSP/Inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"LCD5110/Src/lcd5110.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
LCD5110/Src/lcd5110_hal.o: ../LCD5110/Src/lcd5110_hal.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I"/Users/mprotsyk/UCU/POC/project_new/Bat_Detector_407/LCD5110/Inc" -I"/Users/mprotsyk/UCU/POC/project_new/Bat_Detector_407/DSP/Inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"LCD5110/Src/lcd5110_hal.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
LCD5110/Src/lcd5110_ll.o: ../LCD5110/Src/lcd5110_ll.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I"/Users/mprotsyk/UCU/POC/project_new/Bat_Detector_407/LCD5110/Inc" -I"/Users/mprotsyk/UCU/POC/project_new/Bat_Detector_407/DSP/Inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"LCD5110/Src/lcd5110_ll.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

