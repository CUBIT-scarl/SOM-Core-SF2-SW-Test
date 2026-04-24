################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/lwip-1_4_1/src/api/api_lib.c \
../App/lwip-1_4_1/src/api/api_msg.c \
../App/lwip-1_4_1/src/api/err.c \
../App/lwip-1_4_1/src/api/netbuf.c \
../App/lwip-1_4_1/src/api/netdb.c \
../App/lwip-1_4_1/src/api/netifapi.c \
../App/lwip-1_4_1/src/api/sockets.c \
../App/lwip-1_4_1/src/api/tcpip.c 

OBJS += \
./App/lwip-1_4_1/src/api/api_lib.o \
./App/lwip-1_4_1/src/api/api_msg.o \
./App/lwip-1_4_1/src/api/err.o \
./App/lwip-1_4_1/src/api/netbuf.o \
./App/lwip-1_4_1/src/api/netdb.o \
./App/lwip-1_4_1/src/api/netifapi.o \
./App/lwip-1_4_1/src/api/sockets.o \
./App/lwip-1_4_1/src/api/tcpip.o 

C_DEPS += \
./App/lwip-1_4_1/src/api/api_lib.d \
./App/lwip-1_4_1/src/api/api_msg.d \
./App/lwip-1_4_1/src/api/err.d \
./App/lwip-1_4_1/src/api/netbuf.d \
./App/lwip-1_4_1/src/api/netdb.d \
./App/lwip-1_4_1/src/api/netifapi.d \
./App/lwip-1_4_1/src/api/sockets.d \
./App/lwip-1_4_1/src/api/tcpip.d 


# Each subdirectory must supply rules for building sources it contributes
App/lwip-1_4_1/src/api/%.o: ../App/lwip-1_4_1/src/api/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I../hal -I../hal/CortexM3 -I../hal/CortexM3/GNU -I../CMSIS -I../CMSIS/startup_gcc -I../drivers/mss_uart -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\api" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\core" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\core\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\core\snmp" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\ipv4\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\posix" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\include\posix\sys" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\src\netif\ppp" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\port" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\port\NoRTOS" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip-1_4_1\port\NoRTOS\M2SXXX" -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


