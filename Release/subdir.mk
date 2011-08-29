################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../main.cpp 

OBJS += \
./main.o 

CPP_DEPS += \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/cairo -I/usr/lib/glib-2.0/include -I/usr/include/glib-2.0 -I/usr/include/atk-1.0 -I/usr/include/pango-1.0 -I/usr/include/gtk-2.0 -I/usr/lib/gtk-2.0/include -I/usr/include/gdk-pixbuf-2.0 -L../../MPOST_Linux/Release -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


