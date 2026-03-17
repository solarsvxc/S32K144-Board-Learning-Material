################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/HAL/src/HAL_gpio.c 

OBJS += \
./src/HAL/src/HAL_gpio.o 

C_DEPS += \
./src/HAL/src/HAL_gpio.d 


# Each subdirectory must supply rules for building sources it contributes
src/HAL/src/%.o: ../src/HAL/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/HAL/src/HAL_gpio.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


