################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/bodies/Circle.cpp \
../src/bodies/Polygon.cpp \
../src/bodies/Shape.cpp 

OBJS += \
./src/bodies/Circle.o \
./src/bodies/Polygon.o \
./src/bodies/Shape.o 

CPP_DEPS += \
./src/bodies/Circle.d \
./src/bodies/Polygon.d \
./src/bodies/Shape.d 


# Each subdirectory must supply rules for building sources it contributes
src/bodies/%.o: ../src/bodies/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/pablo/workspace/C++/EPD/hdr" -O0 -g -pedantic -pedantic-errors -Wall -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


