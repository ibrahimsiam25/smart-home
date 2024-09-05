################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/functions/auth.c \
../APP/functions/control_leds.c \
../APP/functions/control_motor.c \
../APP/functions/control_temp.c \
../APP/functions/show_options.c 

OBJS += \
./APP/functions/auth.o \
./APP/functions/control_leds.o \
./APP/functions/control_motor.o \
./APP/functions/control_temp.o \
./APP/functions/show_options.o 

C_DEPS += \
./APP/functions/auth.d \
./APP/functions/control_leds.d \
./APP/functions/control_motor.d \
./APP/functions/control_temp.d \
./APP/functions/show_options.d 


# Each subdirectory must supply rules for building sources it contributes
APP/functions/%.o: ../APP/functions/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


