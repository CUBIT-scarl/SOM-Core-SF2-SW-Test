################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/lwip_2_2_1/apps/snmp/snmp_asn1.c \
../App/lwip_2_2_1/apps/snmp/snmp_core.c \
../App/lwip_2_2_1/apps/snmp/snmp_mib2.c \
../App/lwip_2_2_1/apps/snmp/snmp_mib2_icmp.c \
../App/lwip_2_2_1/apps/snmp/snmp_mib2_interfaces.c \
../App/lwip_2_2_1/apps/snmp/snmp_mib2_ip.c \
../App/lwip_2_2_1/apps/snmp/snmp_mib2_snmp.c \
../App/lwip_2_2_1/apps/snmp/snmp_mib2_system.c \
../App/lwip_2_2_1/apps/snmp/snmp_mib2_tcp.c \
../App/lwip_2_2_1/apps/snmp/snmp_mib2_udp.c \
../App/lwip_2_2_1/apps/snmp/snmp_msg.c \
../App/lwip_2_2_1/apps/snmp/snmp_netconn.c \
../App/lwip_2_2_1/apps/snmp/snmp_pbuf_stream.c \
../App/lwip_2_2_1/apps/snmp/snmp_raw.c \
../App/lwip_2_2_1/apps/snmp/snmp_scalar.c \
../App/lwip_2_2_1/apps/snmp/snmp_snmpv2_framework.c \
../App/lwip_2_2_1/apps/snmp/snmp_snmpv2_usm.c \
../App/lwip_2_2_1/apps/snmp/snmp_table.c \
../App/lwip_2_2_1/apps/snmp/snmp_threadsync.c \
../App/lwip_2_2_1/apps/snmp/snmp_traps.c \
../App/lwip_2_2_1/apps/snmp/snmpv3.c \
../App/lwip_2_2_1/apps/snmp/snmpv3_mbedtls.c 

OBJS += \
./App/lwip_2_2_1/apps/snmp/snmp_asn1.o \
./App/lwip_2_2_1/apps/snmp/snmp_core.o \
./App/lwip_2_2_1/apps/snmp/snmp_mib2.o \
./App/lwip_2_2_1/apps/snmp/snmp_mib2_icmp.o \
./App/lwip_2_2_1/apps/snmp/snmp_mib2_interfaces.o \
./App/lwip_2_2_1/apps/snmp/snmp_mib2_ip.o \
./App/lwip_2_2_1/apps/snmp/snmp_mib2_snmp.o \
./App/lwip_2_2_1/apps/snmp/snmp_mib2_system.o \
./App/lwip_2_2_1/apps/snmp/snmp_mib2_tcp.o \
./App/lwip_2_2_1/apps/snmp/snmp_mib2_udp.o \
./App/lwip_2_2_1/apps/snmp/snmp_msg.o \
./App/lwip_2_2_1/apps/snmp/snmp_netconn.o \
./App/lwip_2_2_1/apps/snmp/snmp_pbuf_stream.o \
./App/lwip_2_2_1/apps/snmp/snmp_raw.o \
./App/lwip_2_2_1/apps/snmp/snmp_scalar.o \
./App/lwip_2_2_1/apps/snmp/snmp_snmpv2_framework.o \
./App/lwip_2_2_1/apps/snmp/snmp_snmpv2_usm.o \
./App/lwip_2_2_1/apps/snmp/snmp_table.o \
./App/lwip_2_2_1/apps/snmp/snmp_threadsync.o \
./App/lwip_2_2_1/apps/snmp/snmp_traps.o \
./App/lwip_2_2_1/apps/snmp/snmpv3.o \
./App/lwip_2_2_1/apps/snmp/snmpv3_mbedtls.o 

C_DEPS += \
./App/lwip_2_2_1/apps/snmp/snmp_asn1.d \
./App/lwip_2_2_1/apps/snmp/snmp_core.d \
./App/lwip_2_2_1/apps/snmp/snmp_mib2.d \
./App/lwip_2_2_1/apps/snmp/snmp_mib2_icmp.d \
./App/lwip_2_2_1/apps/snmp/snmp_mib2_interfaces.d \
./App/lwip_2_2_1/apps/snmp/snmp_mib2_ip.d \
./App/lwip_2_2_1/apps/snmp/snmp_mib2_snmp.d \
./App/lwip_2_2_1/apps/snmp/snmp_mib2_system.d \
./App/lwip_2_2_1/apps/snmp/snmp_mib2_tcp.d \
./App/lwip_2_2_1/apps/snmp/snmp_mib2_udp.d \
./App/lwip_2_2_1/apps/snmp/snmp_msg.d \
./App/lwip_2_2_1/apps/snmp/snmp_netconn.d \
./App/lwip_2_2_1/apps/snmp/snmp_pbuf_stream.d \
./App/lwip_2_2_1/apps/snmp/snmp_raw.d \
./App/lwip_2_2_1/apps/snmp/snmp_scalar.d \
./App/lwip_2_2_1/apps/snmp/snmp_snmpv2_framework.d \
./App/lwip_2_2_1/apps/snmp/snmp_snmpv2_usm.d \
./App/lwip_2_2_1/apps/snmp/snmp_table.d \
./App/lwip_2_2_1/apps/snmp/snmp_threadsync.d \
./App/lwip_2_2_1/apps/snmp/snmp_traps.d \
./App/lwip_2_2_1/apps/snmp/snmpv3.d \
./App/lwip_2_2_1/apps/snmp/snmpv3_mbedtls.d 


# Each subdirectory must supply rules for building sources it contributes
App/lwip_2_2_1/apps/snmp/%.o: ../App/lwip_2_2_1/apps/snmp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I../hal -I../hal/CortexM3 -I../hal/CortexM3/GNU -I../CMSIS -I../CMSIS/startup_gcc -I../drivers/mss_uart -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\api" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\netif\ppp" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\core" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\core\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port\NoRTOS" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port\NoRTOS\M2SXXX" -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


