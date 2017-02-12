################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/main.c 

OBJS += \
./Sources/main.o 

C_DEPS += \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D"CPU_MKL46Z256VLH4" -I"../Sources" -I../board/inc -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"..//home/gmuro/dev/projects/KSDK_1.3.0/platform/hal/inc" -I"..//home/gmuro/dev/projects/KSDK_1.3.0/platform/system/src/clock/MKL46Z4" -I"..//home/gmuro/dev/projects/KSDK_1.3.0/platform/hal/src/sim/MKL46Z4" -I"..//home/gmuro/dev/projects/KSDK_1.3.0/platform/system/inc" -I"..//home/gmuro/dev/projects/KSDK_1.3.0/platform/osa/inc" -I"/home/gmuro/dev/projects/KSDK_1.3.0\platform\hal\inc" -I"/home/gmuro/dev/projects/KSDK_1.3.0\platform\system\src\clock\MKL46Z4" -I"/home/gmuro/dev/projects/KSDK_1.3.0\platform\hal\src\sim\MKL46Z4" -I"/home/gmuro/dev/projects/KSDK_1.3.0\platform\system\inc" -I"/home/gmuro/dev/projects/KSDK_1.3.0\platform\osa\inc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


