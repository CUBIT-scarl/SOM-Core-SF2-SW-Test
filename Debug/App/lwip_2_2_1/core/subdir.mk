################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/lwip_2_2_1/core/altcp.c \
../App/lwip_2_2_1/core/altcp_alloc.c \
../App/lwip_2_2_1/core/altcp_tcp.c \
../App/lwip_2_2_1/core/def.c \
../App/lwip_2_2_1/core/dns.c \
../App/lwip_2_2_1/core/inet_chksum.c \
../App/lwip_2_2_1/core/init.c \
../App/lwip_2_2_1/core/ip.c \
../App/lwip_2_2_1/core/mem.c \
../App/lwip_2_2_1/core/memp.c \
../App/lwip_2_2_1/core/netif.c \
../App/lwip_2_2_1/core/pbuf.c \
../App/lwip_2_2_1/core/raw.c \
../App/lwip_2_2_1/core/stats.c \
../App/lwip_2_2_1/core/sys.c \
../App/lwip_2_2_1/core/tcp.c \
../App/lwip_2_2_1/core/tcp_in.c \
../App/lwip_2_2_1/core/tcp_out.c \
../App/lwip_2_2_1/core/timeouts.c \
../App/lwip_2_2_1/core/udp.c 

OBJS += \
./App/lwip_2_2_1/core/altcp.o \
./App/lwip_2_2_1/core/altcp_alloc.o \
./App/lwip_2_2_1/core/altcp_tcp.o \
./App/lwip_2_2_1/core/def.o \
./App/lwip_2_2_1/core/dns.o \
./App/lwip_2_2_1/core/inet_chksum.o \
./App/lwip_2_2_1/core/init.o \
./App/lwip_2_2_1/core/ip.o \
./App/lwip_2_2_1/core/mem.o \
./App/lwip_2_2_1/core/memp.o \
./App/lwip_2_2_1/core/netif.o \
./App/lwip_2_2_1/core/pbuf.o \
./App/lwip_2_2_1/core/raw.o \
./App/lwip_2_2_1/core/stats.o \
./App/lwip_2_2_1/core/sys.o \
./App/lwip_2_2_1/core/tcp.o \
./App/lwip_2_2_1/core/tcp_in.o \
./App/lwip_2_2_1/core/tcp_out.o \
./App/lwip_2_2_1/core/timeouts.o \
./App/lwip_2_2_1/core/udp.o 

C_DEPS += \
./App/lwip_2_2_1/core/altcp.d \
./App/lwip_2_2_1/core/altcp_alloc.d \
./App/lwip_2_2_1/core/altcp_tcp.d \
./App/lwip_2_2_1/core/def.d \
./App/lwip_2_2_1/core/dns.d \
./App/lwip_2_2_1/core/inet_chksum.d \
./App/lwip_2_2_1/core/init.d \
./App/lwip_2_2_1/core/ip.d \
./App/lwip_2_2_1/core/mem.d \
./App/lwip_2_2_1/core/memp.d \
./App/lwip_2_2_1/core/netif.d \
./App/lwip_2_2_1/core/pbuf.d \
./App/lwip_2_2_1/core/raw.d \
./App/lwip_2_2_1/core/stats.d \
./App/lwip_2_2_1/core/sys.d \
./App/lwip_2_2_1/core/tcp.d \
./App/lwip_2_2_1/core/tcp_in.d \
./App/lwip_2_2_1/core/tcp_out.d \
./App/lwip_2_2_1/core/timeouts.d \
./App/lwip_2_2_1/core/udp.d 


# Each subdirectory must supply rules for building sources it contributes
App/lwip_2_2_1/core/%.o: ../App/lwip_2_2_1/core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I../hal -I../hal/CortexM3 -I../hal/CortexM3/GNU -I../CMSIS -I../CMSIS/startup_gcc -I../drivers/mss_uart -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\api" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\netif\ppp" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\core" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\core\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port\NoRTOS" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port\NoRTOS\M2SXXX" -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


