################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/L293D/L293D_config.c \
../HAL/L293D/L293D_prog.c 

OBJS += \
./HAL/L293D/L293D_config.o \
./HAL/L293D/L293D_prog.o 

C_DEPS += \
./HAL/L293D/L293D_config.d \
./HAL/L293D/L293D_prog.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/L293D/%.o: ../HAL/L293D/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


