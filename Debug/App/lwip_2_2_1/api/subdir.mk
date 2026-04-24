################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/lwip_2_2_1/api/api_lib.c \
../App/lwip_2_2_1/api/api_msg.c \
../App/lwip_2_2_1/api/err.c \
../App/lwip_2_2_1/api/if_api.c \
../App/lwip_2_2_1/api/netbuf.c \
../App/lwip_2_2_1/api/netdb.c \
../App/lwip_2_2_1/api/netifapi.c \
../App/lwip_2_2_1/api/sockets.c \
../App/lwip_2_2_1/api/tcpip.c 

OBJS += \
./App/lwip_2_2_1/api/api_lib.o \
./App/lwip_2_2_1/api/api_msg.o \
./App/lwip_2_2_1/api/err.o \
./App/lwip_2_2_1/api/if_api.o \
./App/lwip_2_2_1/api/netbuf.o \
./App/lwip_2_2_1/api/netdb.o \
./App/lwip_2_2_1/api/netifapi.o \
./App/lwip_2_2_1/api/sockets.o \
./App/lwip_2_2_1/api/tcpip.o 

C_DEPS += \
./App/lwip_2_2_1/api/api_lib.d \
./App/lwip_2_2_1/api/api_msg.d \
./App/lwip_2_2_1/api/err.d \
./App/lwip_2_2_1/api/if_api.d \
./App/lwip_2_2_1/api/netbuf.d \
./App/lwip_2_2_1/api/netdb.d \
./App/lwip_2_2_1/api/netifapi.d \
./App/lwip_2_2_1/api/sockets.d \
./App/lwip_2_2_1/api/tcpip.d 


# Each subdirectory must supply rules for building sources it contributes
App/lwip_2_2_1/api/%.o: ../App/lwip_2_2_1/api/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I../hal -I../hal/CortexM3 -I../hal/CortexM3/GNU -I../CMSIS -I../CMSIS/startup_gcc -I../drivers/mss_uart -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\api" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\netif\ppp" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\core" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\core\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port\NoRTOS" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port\NoRTOS\M2SXXX" -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


