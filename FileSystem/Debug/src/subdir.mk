################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/FileSystem.c \
../src/conexionConNodos.c \
../src/consola.c 

OBJS += \
./src/FileSystem.o \
./src/conexionConNodos.o \
./src/consola.o 

C_DEPS += \
./src/FileSystem.d \
./src/conexionConNodos.d \
./src/consola.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/utnso/workspace/commons" -I"/home/utnso/workspace/tp-2015-1c-compilopordinero/cxd-commons" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


