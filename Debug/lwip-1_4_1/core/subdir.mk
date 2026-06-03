################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip-1_4_1/core/def.c \
../lwip-1_4_1/core/dhcp.c \
../lwip-1_4_1/core/dns.c \
../lwip-1_4_1/core/init.c \
../lwip-1_4_1/core/lwip_timers.c \
../lwip-1_4_1/core/mem.c \
../lwip-1_4_1/core/memp.c \
../lwip-1_4_1/core/netif.c \
../lwip-1_4_1/core/pbuf.c \
../lwip-1_4_1/core/raw.c \
../lwip-1_4_1/core/stats.c \
../lwip-1_4_1/core/sys.c \
../lwip-1_4_1/core/tcp.c \
../lwip-1_4_1/core/tcp_in.c \
../lwip-1_4_1/core/tcp_out.c \
../lwip-1_4_1/core/udp.c 

OBJS += \
./lwip-1_4_1/core/def.o \
./lwip-1_4_1/core/dhcp.o \
./lwip-1_4_1/core/dns.o \
./lwip-1_4_1/core/init.o \
./lwip-1_4_1/core/lwip_timers.o \
./lwip-1_4_1/core/mem.o \
./lwip-1_4_1/core/memp.o \
./lwip-1_4_1/core/netif.o \
./lwip-1_4_1/core/pbuf.o \
./lwip-1_4_1/core/raw.o \
./lwip-1_4_1/core/stats.o \
./lwip-1_4_1/core/sys.o \
./lwip-1_4_1/core/tcp.o \
./lwip-1_4_1/core/tcp_in.o \
./lwip-1_4_1/core/tcp_out.o \
./lwip-1_4_1/core/udp.o 

C_DEPS += \
./lwip-1_4_1/core/def.d \
./lwip-1_4_1/core/dhcp.d \
./lwip-1_4_1/core/dns.d \
./lwip-1_4_1/core/init.d \
./lwip-1_4_1/core/lwip_timers.d \
./lwip-1_4_1/core/mem.d \
./lwip-1_4_1/core/memp.d \
./lwip-1_4_1/core/netif.d \
./lwip-1_4_1/core/pbuf.d \
./lwip-1_4_1/core/raw.d \
./lwip-1_4_1/core/stats.d \
./lwip-1_4_1/core/sys.d \
./lwip-1_4_1/core/tcp.d \
./lwip-1_4_1/core/tcp_in.d \
./lwip-1_4_1/core/tcp_out.d \
./lwip-1_4_1/core/udp.d 


# Each subdirectory must supply rules for building sources it contributes
lwip-1_4_1/core/%.o: ../lwip-1_4_1/core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I../hal -I../hal/CortexM3 -I../hal/CortexM3/GNU -I../CMSIS -I../CMSIS/startup_gcc -I../drivers/mss_uart -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FreeRTOS" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FreeRTOS\include" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FreeRTOS\portable" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FreeRTOS\portable\GCC" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FreeRTOS\portable\GCC\ARM_CM3" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FreeRTOS\portable\MemMang" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\port" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\port\FreeRTOS" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\port\FreeRTOS\M2SXXX" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\api" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\core" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\core\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\core\snmp" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\include" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\include\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\include\ipv4\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\include\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\include\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\include\posix" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\include\posix\sys" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\netif\ppp" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\drivers\mss_ethernet_mac" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FF15a" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FF15a\source" -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


