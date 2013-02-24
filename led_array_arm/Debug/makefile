################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/os/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: led_array_arm.axf

# Tool invocations
led_array_arm.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\mcarino\Documents\LPCXpresso_5.0.14_1109\workspace\CMSISv2p00_LPC17xx\Debug" -Xlinker -Map="led_array_arm.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "led_array_arm_Debug.ld" -o "led_array_arm.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) led_array_arm.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "led_array_arm.axf"; # arm-none-eabi-objcopy -O binary "led_array_arm.axf" "led_array_arm.bin" ; checksum -p LPC1769 -d "led_array_arm.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
