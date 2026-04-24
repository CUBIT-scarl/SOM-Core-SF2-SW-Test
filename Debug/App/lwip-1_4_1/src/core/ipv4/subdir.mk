################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/lwip-1_4_1/src/core/ipv4/autoip.c \
../App/lwip-1_4_1/src/core/ipv4/icmp.c \
../App/lwip-1_4_1/src/core/ipv4/igmp.c \
../App/lwip-1_4_1/src/core/ipv4/inet.c \
../App/lwip-1_4_1/src/core/ipv4/inet_chksum.c \
../App/lwip-1_4_1/src/core/ipv4/ip.c \
../App/lwip-1_4_1/src/core/ipv4/ip_addr.c \
../App/lwip-1_4_1/src/core/ipv4/ip_frag.c 

OBJS += \
./App/lwip-1_4_1/src/core/ipv4/autoip.o \
./App/lwip-1_4_1/src/core/ipv4/icmp.o \
./App/lwip-1_4_1/src/core/ipv4/igmp.o \
./App/lwip-1_4_1/src/core/ipv4/inet.o \
./App/lwip-1_4_1/src/core/ipv4/inet_chksum.o \
./App/lwip-1_4_1/src/core/ipv4/ip.o \
./App/lwip-1_4_1/src/core/ipv4/ip_addr.o \
./App/lwip-1_4_1/src/core/ipv4/ip_frag.o 

C_DEPS += \
./App/lwip-1_4_1/src/core/ipv4/autoip.d \
./App/lwip-1_4_1/src/core/ipv4/icmp.d \
./App/lwip-1_4_1/src/core/ipv4/igmp.d \
./App/lwip-1_4_1/src/core/ipv4/inet.d \
./App/lwip-1_4_1/src/core/ipv4/inet_chksum.d \
./App/lwip-1_4_1/src/core/ipv4/ip.d \
./App/lwip-1_4_1/src/core/ipv4/ip_addr.d \
./App/lwip-1_4_1/src/core/ipv4/ip_frag.d 


# Each subdirectory must supply rules for building sources it contributes
App/lwip-1_4_1/src/core/ipv4/%.o: ../App/lwip-1_4_1/src/core/ipv4/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I../hal -I../hal/CortexM3 -I../hal/CortexM3/GNU -I../CMSIS -I../CMSIS/startup_gcc -I../drivers/mss_uart -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\api" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\core" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\core\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\core\snmp" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\ipv4\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\posix" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\posix\sys" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\netif\ppp" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\port" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\port\NoRTOS" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\port\NoRTOS\M2SXXX" -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


