################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/lwip_2_2_1/core/ipv4/acd.c \
../App/lwip_2_2_1/core/ipv4/autoip.c \
../App/lwip_2_2_1/core/ipv4/dhcp.c \
../App/lwip_2_2_1/core/ipv4/etharp.c \
../App/lwip_2_2_1/core/ipv4/icmp.c \
../App/lwip_2_2_1/core/ipv4/igmp.c \
../App/lwip_2_2_1/core/ipv4/ip4.c \
../App/lwip_2_2_1/core/ipv4/ip4_addr.c \
../App/lwip_2_2_1/core/ipv4/ip4_frag.c 

OBJS += \
./App/lwip_2_2_1/core/ipv4/acd.o \
./App/lwip_2_2_1/core/ipv4/autoip.o \
./App/lwip_2_2_1/core/ipv4/dhcp.o \
./App/lwip_2_2_1/core/ipv4/etharp.o \
./App/lwip_2_2_1/core/ipv4/icmp.o \
./App/lwip_2_2_1/core/ipv4/igmp.o \
./App/lwip_2_2_1/core/ipv4/ip4.o \
./App/lwip_2_2_1/core/ipv4/ip4_addr.o \
./App/lwip_2_2_1/core/ipv4/ip4_frag.o 

C_DEPS += \
./App/lwip_2_2_1/core/ipv4/acd.d \
./App/lwip_2_2_1/core/ipv4/autoip.d \
./App/lwip_2_2_1/core/ipv4/dhcp.d \
./App/lwip_2_2_1/core/ipv4/etharp.d \
./App/lwip_2_2_1/core/ipv4/icmp.d \
./App/lwip_2_2_1/core/ipv4/igmp.d \
./App/lwip_2_2_1/core/ipv4/ip4.d \
./App/lwip_2_2_1/core/ipv4/ip4_addr.d \
./App/lwip_2_2_1/core/ipv4/ip4_frag.d 


# Each subdirectory must supply rules for building sources it contributes
App/lwip_2_2_1/core/ipv4/%.o: ../App/lwip_2_2_1/core/ipv4/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I../hal -I../hal/CortexM3 -I../hal/CortexM3/GNU -I../CMSIS -I../CMSIS/startup_gcc -I../drivers/mss_uart -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\api" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\netif\ppp" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\core" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\core\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port\NoRTOS" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port\NoRTOS\M2SXXX" -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


