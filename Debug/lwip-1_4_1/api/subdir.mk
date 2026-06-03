################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip-1_4_1/api/api_lib.c \
../lwip-1_4_1/api/api_msg.c \
../lwip-1_4_1/api/err.c \
../lwip-1_4_1/api/netbuf.c \
../lwip-1_4_1/api/netdb.c \
../lwip-1_4_1/api/netifapi.c \
../lwip-1_4_1/api/sockets.c \
../lwip-1_4_1/api/tcpip.c 

OBJS += \
./lwip-1_4_1/api/api_lib.o \
./lwip-1_4_1/api/api_msg.o \
./lwip-1_4_1/api/err.o \
./lwip-1_4_1/api/netbuf.o \
./lwip-1_4_1/api/netdb.o \
./lwip-1_4_1/api/netifapi.o \
./lwip-1_4_1/api/sockets.o \
./lwip-1_4_1/api/tcpip.o 

C_DEPS += \
./lwip-1_4_1/api/api_lib.d \
./lwip-1_4_1/api/api_msg.d \
./lwip-1_4_1/api/err.d \
./lwip-1_4_1/api/netbuf.d \
./lwip-1_4_1/api/netdb.d \
./lwip-1_4_1/api/netifapi.d \
./lwip-1_4_1/api/sockets.d \
./lwip-1_4_1/api/tcpip.d 


# Each subdirectory must supply rules for building sources it contributes
lwip-1_4_1/api/%.o: ../lwip-1_4_1/api/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I../hal -I../hal/CortexM3 -I../hal/CortexM3/GNU -I../CMSIS -I../CMSIS/startup_gcc -I../drivers/mss_uart -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FreeRTOS" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FreeRTOS\include" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FreeRTOS\portable" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FreeRTOS\portable\GCC" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FreeRTOS\portable\GCC\ARM_CM3" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FreeRTOS\portable\MemMang" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\port" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\port\FreeRTOS" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\port\FreeRTOS\M2SXXX" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\api" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\core" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\core\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\core\snmp" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\include" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\include\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\include\ipv4\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\include\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\include\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\include\posix" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\include\posix\sys" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\netif\ppp" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\drivers\mss_ethernet_mac" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FF15a" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FF15a\source" -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


