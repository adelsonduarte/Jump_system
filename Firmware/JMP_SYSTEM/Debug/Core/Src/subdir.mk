################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Apagar_component.c \
../Core/Src/Configuracao_component.c \
../Core/Src/Consulta_component.c \
../Core/Src/Data.c \
../Core/Src/DataProcessing.c \
../Core/Src/DisplayMessages.c \
../Core/Src/Display_module.c \
../Core/Src/Exportar_component.c \
../Core/Src/INICIAR_Component.c \
../Core/Src/IO_interface.c \
../Core/Src/LCDHW.c \
../Core/Src/LiquidCrystal.c \
../Core/Src/SDMEMORYHW.c \
../Core/Src/SD_module.c \
../Core/Src/SENSORHW.c \
../Core/Src/SubMenu.c \
../Core/Src/TimerHW.c \
../Core/Src/UARTHW.c \
../Core/Src/comunicacao.c \
../Core/Src/fatfs_sd.c \
../Core/Src/flash_v1.0.c \
../Core/Src/main.c \
../Core/Src/menu_module.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c 

OBJS += \
./Core/Src/Apagar_component.o \
./Core/Src/Configuracao_component.o \
./Core/Src/Consulta_component.o \
./Core/Src/Data.o \
./Core/Src/DataProcessing.o \
./Core/Src/DisplayMessages.o \
./Core/Src/Display_module.o \
./Core/Src/Exportar_component.o \
./Core/Src/INICIAR_Component.o \
./Core/Src/IO_interface.o \
./Core/Src/LCDHW.o \
./Core/Src/LiquidCrystal.o \
./Core/Src/SDMEMORYHW.o \
./Core/Src/SD_module.o \
./Core/Src/SENSORHW.o \
./Core/Src/SubMenu.o \
./Core/Src/TimerHW.o \
./Core/Src/UARTHW.o \
./Core/Src/comunicacao.o \
./Core/Src/fatfs_sd.o \
./Core/Src/flash_v1.0.o \
./Core/Src/main.o \
./Core/Src/menu_module.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o 

C_DEPS += \
./Core/Src/Apagar_component.d \
./Core/Src/Configuracao_component.d \
./Core/Src/Consulta_component.d \
./Core/Src/Data.d \
./Core/Src/DataProcessing.d \
./Core/Src/DisplayMessages.d \
./Core/Src/Display_module.d \
./Core/Src/Exportar_component.d \
./Core/Src/INICIAR_Component.d \
./Core/Src/IO_interface.d \
./Core/Src/LCDHW.d \
./Core/Src/LiquidCrystal.d \
./Core/Src/SDMEMORYHW.d \
./Core/Src/SD_module.d \
./Core/Src/SENSORHW.d \
./Core/Src/SubMenu.d \
./Core/Src/TimerHW.d \
./Core/Src/UARTHW.d \
./Core/Src/comunicacao.d \
./Core/Src/fatfs_sd.d \
./Core/Src/flash_v1.0.d \
./Core/Src/main.d \
./Core/Src/menu_module.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Apagar_component.d ./Core/Src/Apagar_component.o ./Core/Src/Apagar_component.su ./Core/Src/Configuracao_component.d ./Core/Src/Configuracao_component.o ./Core/Src/Configuracao_component.su ./Core/Src/Consulta_component.d ./Core/Src/Consulta_component.o ./Core/Src/Consulta_component.su ./Core/Src/Data.d ./Core/Src/Data.o ./Core/Src/Data.su ./Core/Src/DataProcessing.d ./Core/Src/DataProcessing.o ./Core/Src/DataProcessing.su ./Core/Src/DisplayMessages.d ./Core/Src/DisplayMessages.o ./Core/Src/DisplayMessages.su ./Core/Src/Display_module.d ./Core/Src/Display_module.o ./Core/Src/Display_module.su ./Core/Src/Exportar_component.d ./Core/Src/Exportar_component.o ./Core/Src/Exportar_component.su ./Core/Src/INICIAR_Component.d ./Core/Src/INICIAR_Component.o ./Core/Src/INICIAR_Component.su ./Core/Src/IO_interface.d ./Core/Src/IO_interface.o ./Core/Src/IO_interface.su ./Core/Src/LCDHW.d ./Core/Src/LCDHW.o ./Core/Src/LCDHW.su ./Core/Src/LiquidCrystal.d ./Core/Src/LiquidCrystal.o ./Core/Src/LiquidCrystal.su ./Core/Src/SDMEMORYHW.d ./Core/Src/SDMEMORYHW.o ./Core/Src/SDMEMORYHW.su ./Core/Src/SD_module.d ./Core/Src/SD_module.o ./Core/Src/SD_module.su ./Core/Src/SENSORHW.d ./Core/Src/SENSORHW.o ./Core/Src/SENSORHW.su ./Core/Src/SubMenu.d ./Core/Src/SubMenu.o ./Core/Src/SubMenu.su ./Core/Src/TimerHW.d ./Core/Src/TimerHW.o ./Core/Src/TimerHW.su ./Core/Src/UARTHW.d ./Core/Src/UARTHW.o ./Core/Src/UARTHW.su ./Core/Src/comunicacao.d ./Core/Src/comunicacao.o ./Core/Src/comunicacao.su ./Core/Src/fatfs_sd.d ./Core/Src/fatfs_sd.o ./Core/Src/fatfs_sd.su ./Core/Src/flash_v1.0.d ./Core/Src/flash_v1.0.o ./Core/Src/flash_v1.0.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/menu_module.d ./Core/Src/menu_module.o ./Core/Src/menu_module.su ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su

.PHONY: clean-Core-2f-Src

