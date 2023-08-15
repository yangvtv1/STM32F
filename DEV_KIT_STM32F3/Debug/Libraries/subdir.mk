################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/drv_common.c \
../Libraries/plog.c \
../Libraries/test_callback.c 

OBJS += \
./Libraries/drv_common.o \
./Libraries/plog.o \
./Libraries/test_callback.o 

C_DEPS += \
./Libraries/drv_common.d \
./Libraries/plog.d \
./Libraries/test_callback.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/%.o: ../Libraries/%.c Libraries/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I"C:/Users/ATC/STM32CubeIDE/workspace_1.8.0/DEV_KIT_STM32F3/Libraries" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries

clean-Libraries:
	-$(RM) ./Libraries/drv_common.d ./Libraries/drv_common.o ./Libraries/plog.d ./Libraries/plog.o ./Libraries/test_callback.d ./Libraries/test_callback.o

.PHONY: clean-Libraries

