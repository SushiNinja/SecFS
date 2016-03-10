################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/common.c \
../src/enc.c \
../src/main.c \
../src/mnt.c 

OBJS += \
./src/common.o \
./src/enc.o \
./src/main.o \
./src/mnt.o 

C_DEPS += \
./src/common.d \
./src/enc.d \
./src/main.d \
./src/mnt.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -o "$@" "$<" -I/usr/local/ssl/include -O0 -g3 -Wall -c -fmessage-length=0 -D_FILE_OFFSET_BITS=64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)"
	@echo 'Finished building: $<'
	@echo ' '


