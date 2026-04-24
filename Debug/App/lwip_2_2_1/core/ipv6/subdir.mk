################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/lwip_2_2_1/core/ipv6/dhcp6.c \
../App/lwip_2_2_1/core/ipv6/ethip6.c \
../App/lwip_2_2_1/core/ipv6/icmp6.c \
../App/lwip_2_2_1/core/ipv6/inet6.c \
../App/lwip_2_2_1/core/ipv6/ip6.c \
../App/lwip_2_2_1/core/ipv6/ip6_addr.c \
../App/lwip_2_2_1/core/ipv6/ip6_frag.c \
../App/lwip_2_2_1/core/ipv6/mld6.c \
../App/lwip_2_2_1/core/ipv6/nd6.c 

OBJS += \
./App/lwip_2_2_1/core/ipv6/dhcp6.o \
./App/lwip_2_2_1/core/ipv6/ethip6.o \
./App/lwip_2_2_1/core/ipv6/icmp6.o \
./App/lwip_2_2_1/core/ipv6/inet6.o \
./App/lwip_2_2_1/core/ipv6/ip6.o \
./App/lwip_2_2_1/core/ipv6/ip6_addr.o \
./App/lwip_2_2_1/core/ipv6/ip6_frag.o \
./App/lwip_2_2_1/core/ipv6/mld6.o \
./App/lwip_2_2_1/core/ipv6/nd6.o 

C_DEPS += \
./App/lwip_2_2_1/core/ipv6/dhcp6.d \
./App/lwip_2_2_1/core/ipv6/ethip6.d \
./App/lwip_2_2_1/core/ipv6/icmp6.d \
./App/lwip_2_2_1/core/ipv6/inet6.d \
./App/lwip_2_2_1/core/ipv6/ip6.d \
./App/lwip_2_2_1/core/ipv6/ip6_addr.d \
./App/lwip_2_2_1/core/ipv6/ip6_frag.d \
./App/lwip_2_2_1/core/ipv6/mld6.d \
./App/lwip_2_2_1/core/ipv6/nd6.d 


# Each subdirectory must supply rules for building sources it contributes
App/lwip_2_2_1/core/ipv6/%.o: ../App/lwip_2_2_1/core/ipv6/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I../hal -I../hal/CortexM3 -I../hal/CortexM3/GNU -I../CMSIS -I../CMSIS/startup_gcc -I../drivers/mss_uart -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\api" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\netif\ppp" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\core" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\core\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port\NoRTOS" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port\NoRTOS\M2SXXX" -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


