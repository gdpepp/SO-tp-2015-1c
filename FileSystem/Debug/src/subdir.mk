################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/FileSystem.c \
../src/conexionConNodos.c \
../src/consola.c \
../src/opcion1.c \
../src/opcion2.c \
../src/opcion3.c \
../src/thread_escuchas.c \
../src/thread_pedidosmarta.c 

OBJS += \
./src/FileSystem.o \
./src/conexionConNodos.o \
./src/consola.o \
./src/opcion1.o \
./src/opcion2.o \
./src/opcion3.o \
./src/thread_escuchas.o \
./src/thread_pedidosmarta.o 

C_DEPS += \
./src/FileSystem.d \
./src/conexionConNodos.d \
./src/consola.d \
./src/opcion1.d \
./src/opcion2.d \
./src/opcion3.d \
./src/thread_escuchas.d \
./src/thread_pedidosmarta.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/ezeyuske/workspace/tp-2015-1c-compilopordinero/cxd-commons" -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


