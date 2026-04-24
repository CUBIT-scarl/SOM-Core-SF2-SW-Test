################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/lwip-1_4_1/src/core/def.c \
../App/lwip-1_4_1/src/core/dhcp.c \
../App/lwip-1_4_1/src/core/dns.c \
../App/lwip-1_4_1/src/core/init.c \
../App/lwip-1_4_1/src/core/mem.c \
../App/lwip-1_4_1/src/core/memp.c \
../App/lwip-1_4_1/src/core/netif.c \
../App/lwip-1_4_1/src/core/pbuf.c \
../App/lwip-1_4_1/src/core/raw.c \
../App/lwip-1_4_1/src/core/stats.c \
../App/lwip-1_4_1/src/core/sys.c \
../App/lwip-1_4_1/src/core/tcp.c \
../App/lwip-1_4_1/src/core/tcp_in.c \
../App/lwip-1_4_1/src/core/tcp_out.c \
../App/lwip-1_4_1/src/core/timers.c \
../App/lwip-1_4_1/src/core/udp.c 

OBJS += \
./App/lwip-1_4_1/src/core/def.o \
./App/lwip-1_4_1/src/core/dhcp.o \
./App/lwip-1_4_1/src/core/dns.o \
./App/lwip-1_4_1/src/core/init.o \
./App/lwip-1_4_1/src/core/mem.o \
./App/lwip-1_4_1/src/core/memp.o \
./App/lwip-1_4_1/src/core/netif.o \
./App/lwip-1_4_1/src/core/pbuf.o \
./App/lwip-1_4_1/src/core/raw.o \
./App/lwip-1_4_1/src/core/stats.o \
./App/lwip-1_4_1/src/core/sys.o \
./App/lwip-1_4_1/src/core/tcp.o \
./App/lwip-1_4_1/src/core/tcp_in.o \
./App/lwip-1_4_1/src/core/tcp_out.o \
./App/lwip-1_4_1/src/core/timers.o \
./App/lwip-1_4_1/src/core/udp.o 

C_DEPS += \
./App/lwip-1_4_1/src/core/def.d \
./App/lwip-1_4_1/src/core/dhcp.d \
./App/lwip-1_4_1/src/core/dns.d \
./App/lwip-1_4_1/src/core/init.d \
./App/lwip-1_4_1/src/core/mem.d \
./App/lwip-1_4_1/src/core/memp.d \
./App/lwip-1_4_1/src/core/netif.d \
./App/lwip-1_4_1/src/core/pbuf.d \
./App/lwip-1_4_1/src/core/raw.d \
./App/lwip-1_4_1/src/core/stats.d \
./App/lwip-1_4_1/src/core/sys.d \
./App/lwip-1_4_1/src/core/tcp.d \
./App/lwip-1_4_1/src/core/tcp_in.d \
./App/lwip-1_4_1/src/core/tcp_out.d \
./App/lwip-1_4_1/src/core/timers.d \
./App/lwip-1_4_1/src/core/udp.d 


# Each subdirectory must supply rules for building sources it contributes
App/lwip-1_4_1/src/core/%.o: ../App/lwip-1_4_1/src/core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I../hal -I../hal/CortexM3 -I../hal/CortexM3/GNU -I../CMSIS -I../CMSIS/startup_gcc -I../drivers/mss_uart -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\api" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\core" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\core\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\core\snmp" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\ipv4\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\posix" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\posix\sys" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\netif\ppp" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\port" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\port\NoRTOS" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\port\NoRTOS\M2SXXX" -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


