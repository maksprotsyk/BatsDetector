################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc.c \
../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc_bot.c \
../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc_scsi.c 

OBJS += \
./Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc.o \
./Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc_bot.o \
./Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc_scsi.o 

C_DEPS += \
./Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc.d \
./Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc_bot.d \
./Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc_scsi.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc.o: ../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I"/Users/mprotsyk/UCU/POC/project_new/Bat_Detector_407/DSP/Inc" -I"/Users/mprotsyk/UCU/POC/project_new/Bat_Detector_407/LCD5110/Inc" -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc_bot.o: ../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc_bot.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I"/Users/mprotsyk/UCU/POC/project_new/Bat_Detector_407/DSP/Inc" -I"/Users/mprotsyk/UCU/POC/project_new/Bat_Detector_407/LCD5110/Inc" -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc_bot.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc_scsi.o: ../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc_scsi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I"/Users/mprotsyk/UCU/POC/project_new/Bat_Detector_407/DSP/Inc" -I"/Users/mprotsyk/UCU/POC/project_new/Bat_Detector_407/LCD5110/Inc" -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc_scsi.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

