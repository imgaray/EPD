################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/dynamics/Body.cpp \
../src/dynamics/Fluid.cpp \
../src/dynamics/Force.cpp \
../src/dynamics/Joint.cpp \
../src/dynamics/Torque.cpp 

OBJS += \
./src/dynamics/Body.o \
./src/dynamics/Fluid.o \
./src/dynamics/Force.o \
./src/dynamics/Joint.o \
./src/dynamics/Torque.o 

CPP_DEPS += \
./src/dynamics/Body.d \
./src/dynamics/Fluid.d \
./src/dynamics/Force.d \
./src/dynamics/Joint.d \
./src/dynamics/Torque.d 


# Each subdirectory must supply rules for building sources it contributes
src/dynamics/%.o: ../src/dynamics/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/pablo/workspace/C++/EPD/hdr" -O0 -g -pedantic -pedantic-errors -Wall -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


