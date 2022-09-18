################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/WDT/subdir.mk
-include MCAL/UART/subdir.mk
-include MCAL/TIMER/subdir.mk
-include MCAL/PWM/subdir.mk
-include MCAL/IIC/subdir.mk
-include MCAL/GIE/subdir.mk
-include MCAL/EXTI/subdir.mk
-include MCAL/EEPROM/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include HAL/Switch/subdir.mk
-include HAL/StepMotor/subdir.mk
-include HAL/SevSeg/subdir.mk
-include HAL/LM35/subdir.mk
-include HAL/LD/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/L293D/subdir.mk
-include HAL/Keypad/subdir.mk
-include HAL/EXT_EEPROM/subdir.mk
-include App/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
ATMEGA_32A.lss \

FLASH_IMAGE += \
ATMEGA_32A.hex \

EEPROM_IMAGE += \
ATMEGA_32A.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: ATMEGA_32A.elf secondary-outputs

# Tool invocations
ATMEGA_32A.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ATMEGA_32A.map -mmcu=atmega32 -o "ATMEGA_32A.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ATMEGA_32A.lss: ATMEGA_32A.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ATMEGA_32A.elf  >"ATMEGA_32A.lss"
	@echo 'Finished building: $@'
	@echo ' '

ATMEGA_32A.hex: ATMEGA_32A.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ATMEGA_32A.elf  "ATMEGA_32A.hex"
	@echo 'Finished building: $@'
	@echo ' '

ATMEGA_32A.eep: ATMEGA_32A.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex ATMEGA_32A.elf  "ATMEGA_32A.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ATMEGA_32A.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 ATMEGA_32A.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ATMEGA_32A.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
