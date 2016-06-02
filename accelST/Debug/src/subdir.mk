################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/I2c.cpp \
../src/Lsm303d.cpp \
../src/SocketNode.cpp \
../src/accelST.cpp 

OBJS += \
./src/I2c.o \
./src/Lsm303d.o \
./src/SocketNode.o \
./src/accelST.o 

CPP_DEPS += \
./src/I2c.d \
./src/Lsm303d.d \
./src/SocketNode.d \
./src/accelST.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


