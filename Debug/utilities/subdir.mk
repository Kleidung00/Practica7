################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_debug_console.c 

OBJS += \
./utilities/fsl_debug_console.o 

C_DEPS += \
./utilities/fsl_debug_console.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DDEBUG -DPRINTF_FLOAT_ENABLE=0 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DFRDM_KL25Z -DFREEDOM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -I"C:\Users\claud\Documents\MCUXpressoIDE_11.5.0_7232\workspace\HELLO_demo_apps_hello_world\board" -I"C:\Users\claud\Documents\MCUXpressoIDE_11.5.0_7232\workspace\HELLO_demo_apps_hello_world\source" -I"C:\Users\claud\Documents\MCUXpressoIDE_11.5.0_7232\workspace\HELLO_demo_apps_hello_world" -I"C:\Users\claud\Documents\MCUXpressoIDE_11.5.0_7232\workspace\HELLO_demo_apps_hello_world\CMSIS" -I"C:\Users\claud\Documents\MCUXpressoIDE_11.5.0_7232\workspace\HELLO_demo_apps_hello_world\drivers" -I"C:\Users\claud\Documents\MCUXpressoIDE_11.5.0_7232\workspace\HELLO_demo_apps_hello_world\utilities" -I"C:\Users\claud\Documents\MCUXpressoIDE_11.5.0_7232\workspace\HELLO_demo_apps_hello_world\startup" -O0 -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


