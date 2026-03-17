################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Driver/src/driver_gpio.c 

OBJS += \
./src/Driver/src/driver_gpio.o 

C_DEPS += \
./src/Driver/src/driver_gpio.d 


# Each subdirectory must supply rules for building sources it contributes
src/Driver/src/%.o: ../src/Driver/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/Driver/src/driver_gpio.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


