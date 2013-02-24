################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/console.c \
../src/cr_startup_lpc176x.c \
../src/led_array.c \
../src/main.c \
../src/scan.c 

OBJS += \
./src/console.o \
./src/cr_startup_lpc176x.o \
./src/led_array.o \
./src/main.o \
./src/scan.o 

C_DEPS += \
./src/console.d \
./src/cr_startup_lpc176x.d \
./src/led_array.d \
./src/main.d \
./src/scan.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\mcarino\Documents\LPCXpresso_5.0.14_1109\workspace\CMSISv2p00_LPC17xx\inc" -I"C:\Users\mcarino\Documents\LPCXpresso_5.0.14_1109\workspace\led_array_arm\src\os" -O2 -g -Wall -Werror -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fomit-frame-pointer -std=gnu99 -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/cr_startup_lpc176x.o: ../src/cr_startup_lpc176x.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\mcarino\Documents\LPCXpresso_5.0.14_1109\workspace\CMSISv2p00_LPC17xx\inc" -I"C:\Users\mcarino\Documents\LPCXpresso_5.0.14_1109\workspace\led_array_arm\src\os" -O2 -g -Wall -Werror -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fomit-frame-pointer -std=gnu99 -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_startup_lpc176x.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


