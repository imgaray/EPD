################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/common/Math.cpp 

OBJS += \
./src/common/Math.o 

CPP_DEPS += \
./src/common/Math.d 


# Each subdirectory must supply rules for building sources it contributes
src/common/%.o: ../src/common/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/pablo/workspace/C++/EPD/hdr" -O0 -g -pedantic -pedantic-errors -Wall -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


