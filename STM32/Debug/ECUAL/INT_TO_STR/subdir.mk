################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ECUAL/INT_TO_STR/INT_TO_STR.c 

OBJS += \
./ECUAL/INT_TO_STR/INT_TO_STR.o 

C_DEPS += \
./ECUAL/INT_TO_STR/INT_TO_STR.d 


# Each subdirectory must supply rules for building sources it contributes
ECUAL/INT_TO_STR/%.o ECUAL/INT_TO_STR/%.su: ../ECUAL/INT_TO_STR/%.c ECUAL/INT_TO_STR/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ECUAL-2f-INT_TO_STR

clean-ECUAL-2f-INT_TO_STR:
	-$(RM) ./ECUAL/INT_TO_STR/INT_TO_STR.d ./ECUAL/INT_TO_STR/INT_TO_STR.o ./ECUAL/INT_TO_STR/INT_TO_STR.su

.PHONY: clean-ECUAL-2f-INT_TO_STR

