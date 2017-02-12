################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project_Settings/Startup_Code/startup.c \
../Project_Settings/Startup_Code/system_MKL46Z4.c 

S_UPPER_SRCS += \
../Project_Settings/Startup_Code/startup_MKL46Z4.S 

OBJS += \
./Project_Settings/Startup_Code/startup.o \
./Project_Settings/Startup_Code/startup_MKL46Z4.o \
./Project_Settings/Startup_Code/system_MKL46Z4.o 

C_DEPS += \
./Project_Settings/Startup_Code/startup.d \
./Project_Settings/Startup_Code/system_MKL46Z4.d 

S_UPPER_DEPS += \
./Project_Settings/Startup_Code/startup_MKL46Z4.d 


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/%.o: ../Project_Settings/Startup_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D"CPU_MKL46Z256VLH4" -I"../Sources" -I../board/inc -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"..//home/gmuro/dev/projects/KSDK_1.3.0/platform/hal/inc" -I"..//home/gmuro/dev/projects/KSDK_1.3.0/platform/system/src/clock/MKL46Z4" -I"..//home/gmuro/dev/projects/KSDK_1.3.0/platform/hal/src/sim/MKL46Z4" -I"..//home/gmuro/dev/projects/KSDK_1.3.0/platform/system/inc" -I"..//home/gmuro/dev/projects/KSDK_1.3.0/platform/osa/inc" -I"/home/gmuro/dev/projects/KSDK_1.3.0/platform/hal/inc" -I"/home/gmuro/dev/projects/KSDK_1.3.0/platform/system/src/clock/MKL46Z4" -I"/home/gmuro/dev/projects/KSDK_1.3.0/platform/hal/src/sim/MKL46Z4" -I"/home/gmuro/dev/projects/KSDK_1.3.0/platform/system/inc" -I"/home/gmuro/dev/projects/KSDK_1.3.0/platform/osa/inc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Project_Settings/Startup_Code/%.o: ../Project_Settings/Startup_Code/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


