################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/lwip-1_4_1/src/netif/ppp/auth.c \
../App/lwip-1_4_1/src/netif/ppp/chap.c \
../App/lwip-1_4_1/src/netif/ppp/chpms.c \
../App/lwip-1_4_1/src/netif/ppp/fsm.c \
../App/lwip-1_4_1/src/netif/ppp/ipcp.c \
../App/lwip-1_4_1/src/netif/ppp/lcp.c \
../App/lwip-1_4_1/src/netif/ppp/magic.c \
../App/lwip-1_4_1/src/netif/ppp/md5.c \
../App/lwip-1_4_1/src/netif/ppp/pap.c \
../App/lwip-1_4_1/src/netif/ppp/ppp.c \
../App/lwip-1_4_1/src/netif/ppp/ppp_oe.c \
../App/lwip-1_4_1/src/netif/ppp/randm.c \
../App/lwip-1_4_1/src/netif/ppp/vj.c 

OBJS += \
./App/lwip-1_4_1/src/netif/ppp/auth.o \
./App/lwip-1_4_1/src/netif/ppp/chap.o \
./App/lwip-1_4_1/src/netif/ppp/chpms.o \
./App/lwip-1_4_1/src/netif/ppp/fsm.o \
./App/lwip-1_4_1/src/netif/ppp/ipcp.o \
./App/lwip-1_4_1/src/netif/ppp/lcp.o \
./App/lwip-1_4_1/src/netif/ppp/magic.o \
./App/lwip-1_4_1/src/netif/ppp/md5.o \
./App/lwip-1_4_1/src/netif/ppp/pap.o \
./App/lwip-1_4_1/src/netif/ppp/ppp.o \
./App/lwip-1_4_1/src/netif/ppp/ppp_oe.o \
./App/lwip-1_4_1/src/netif/ppp/randm.o \
./App/lwip-1_4_1/src/netif/ppp/vj.o 

C_DEPS += \
./App/lwip-1_4_1/src/netif/ppp/auth.d \
./App/lwip-1_4_1/src/netif/ppp/chap.d \
./App/lwip-1_4_1/src/netif/ppp/chpms.d \
./App/lwip-1_4_1/src/netif/ppp/fsm.d \
./App/lwip-1_4_1/src/netif/ppp/ipcp.d \
./App/lwip-1_4_1/src/netif/ppp/lcp.d \
./App/lwip-1_4_1/src/netif/ppp/magic.d \
./App/lwip-1_4_1/src/netif/ppp/md5.d \
./App/lwip-1_4_1/src/netif/ppp/pap.d \
./App/lwip-1_4_1/src/netif/ppp/ppp.d \
./App/lwip-1_4_1/src/netif/ppp/ppp_oe.d \
./App/lwip-1_4_1/src/netif/ppp/randm.d \
./App/lwip-1_4_1/src/netif/ppp/vj.d 


# Each subdirectory must supply rules for building sources it contributes
App/lwip-1_4_1/src/netif/ppp/%.o: ../App/lwip-1_4_1/src/netif/ppp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I../hal -I../hal/CortexM3 -I../hal/CortexM3/GNU -I../CMSIS -I../CMSIS/startup_gcc -I../drivers/mss_uart -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\api" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\core" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\core\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\core\snmp" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\ipv4\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\posix" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\posix\sys" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\netif\ppp" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\port" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\port\NoRTOS" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\port\NoRTOS\M2SXXX" -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


