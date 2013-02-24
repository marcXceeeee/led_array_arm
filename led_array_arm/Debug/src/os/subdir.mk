################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/os/cpu_c.c \
../src/os/cpu_core.c \
../src/os/os_core.c \
../src/os/os_cpu_c.c \
../src/os/os_dbg.c \
../src/os/os_flag.c \
../src/os/os_task.c \
../src/os/os_time.c \
../src/os/os_tmr.c 

S_SRCS += \
../src/os/cpu_a.s 

ASM_SRCS += \
../src/os/os_cpu_a.asm 

OBJS += \
./src/os/cpu_a.o \
./src/os/cpu_c.o \
./src/os/cpu_core.o \
./src/os/os_core.o \
./src/os/os_cpu_a.o \
./src/os/os_cpu_c.o \
./src/os/os_dbg.o \
./src/os/os_flag.o \
./src/os/os_task.o \
./src/os/os_time.o \
./src/os/os_tmr.o 

C_DEPS += \
./src/os/cpu_c.d \
./src/os/cpu_core.d \
./src/os/os_core.d \
./src/os/os_cpu_c.d \
./src/os/os_dbg.d \
./src/os/os_flag.d \
./src/os/os_task.d \
./src/os/os_time.d \
./src/os/os_tmr.d 


# Each subdirectory must supply rules for building sources it contributes
src/os/%.o: ../src/os/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__REDLIB__ -DDEBUG -D__CODE_RED -g3 -mcpu=cortex-m3 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/os/%.o: ../src/os/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\mcarino\Documents\LPCXpresso_5.0.14_1109\workspace\CMSISv2p00_LPC17xx\inc" -I"C:\Users\mcarino\Documents\LPCXpresso_5.0.14_1109\workspace\led_array_arm\src\os" -O2 -g -Wall -Werror -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fomit-frame-pointer -std=gnu99 -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/os/%.o: ../src/os/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__REDLIB__ -DDEBUG -D__CODE_RED -g3 -mcpu=cortex-m3 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


