################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include lwip-1_4_1/port/FreeRTOS/M2SXXX/subdir.mk
-include lwip-1_4_1/netif/ppp/subdir.mk
-include lwip-1_4_1/netif/subdir.mk
-include lwip-1_4_1/core/snmp/subdir.mk
-include lwip-1_4_1/core/ipv4/subdir.mk
-include lwip-1_4_1/core/subdir.mk
-include lwip-1_4_1/api/subdir.mk
-include hal/CortexM3/GNU/subdir.mk
-include hal/CortexM3/subdir.mk
-include drivers_config/sys_config/subdir.mk
-include drivers/mss_uart/subdir.mk
-include drivers/mss_sys_services/subdir.mk
-include drivers/mss_spi/subdir.mk
-include drivers/mss_nvm/subdir.mk
-include drivers/mss_hpdma/subdir.mk
-include drivers/mss_ethernet_mac/subdir.mk
-include drivers/CoreGPIO/subdir.mk
-include FreeRTOS/portable/MemMang/subdir.mk
-include FreeRTOS/portable/GCC/ARM_CM3/subdir.mk
-include FreeRTOS/subdir.mk
-include FF15a/source/subdir.mk
-include CMSIS/startup_gcc/subdir.mk
-include CMSIS/subdir.mk
-include App/VirtualLcd/subdir.mk
-include App/Drivers/subdir.mk
-include App/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
PRJ82037801_Test_Manuale.bin \

SECONDARY_SIZE += \
PRJ82037801_Test_Manuale.siz \


# All Target
all: PRJ82037801_Test_Manuale.elf secondary-outputs

# Tool invocations
PRJ82037801_Test_Manuale.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\CMSIS\startup_gcc\debug-in-microsemi-smartfusion2-envm-NOBOOT.ld" -Xlinker --gc-sections -Wl,-Map,"PRJ82037801_Test_Manuale.map" -o "PRJ82037801_Test_Manuale.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

PRJ82037801_Test_Manuale.bin: PRJ82037801_Test_Manuale.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary "PRJ82037801_Test_Manuale.elf"  "PRJ82037801_Test_Manuale.bin"
	@echo 'Finished building: $@'
	@echo ' '

PRJ82037801_Test_Manuale.siz: PRJ82037801_Test_Manuale.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "PRJ82037801_Test_Manuale.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) PRJ82037801_Test_Manuale.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
