################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/lwip_2_2_1/netif/bridgeif.c \
../App/lwip_2_2_1/netif/bridgeif_fdb.c \
../App/lwip_2_2_1/netif/ethernet.c \
../App/lwip_2_2_1/netif/lowpan6.c \
../App/lwip_2_2_1/netif/lowpan6_ble.c \
../App/lwip_2_2_1/netif/lowpan6_common.c \
../App/lwip_2_2_1/netif/slipif.c \
../App/lwip_2_2_1/netif/zepif.c 

OBJS += \
./App/lwip_2_2_1/netif/bridgeif.o \
./App/lwip_2_2_1/netif/bridgeif_fdb.o \
./App/lwip_2_2_1/netif/ethernet.o \
./App/lwip_2_2_1/netif/lowpan6.o \
./App/lwip_2_2_1/netif/lowpan6_ble.o \
./App/lwip_2_2_1/netif/lowpan6_common.o \
./App/lwip_2_2_1/netif/slipif.o \
./App/lwip_2_2_1/netif/zepif.o 

C_DEPS += \
./App/lwip_2_2_1/netif/bridgeif.d \
./App/lwip_2_2_1/netif/bridgeif_fdb.d \
./App/lwip_2_2_1/netif/ethernet.d \
./App/lwip_2_2_1/netif/lowpan6.d \
./App/lwip_2_2_1/netif/lowpan6_ble.d \
./App/lwip_2_2_1/netif/lowpan6_common.d \
./App/lwip_2_2_1/netif/slipif.d \
./App/lwip_2_2_1/netif/zepif.d 


# Each subdirectory must supply rules for building sources it contributes
App/lwip_2_2_1/netif/%.o: ../App/lwip_2_2_1/netif/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I../hal -I../hal/CortexM3 -I../hal/CortexM3/GNU -I../CMSIS -I../CMSIS/startup_gcc -I../drivers/mss_uart -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\api" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\netif\ppp" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\core" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\core\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port\NoRTOS" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port\NoRTOS\M2SXXX" -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


