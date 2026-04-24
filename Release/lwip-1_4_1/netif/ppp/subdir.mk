################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip-1_4_1/netif/ppp/auth.c \
../lwip-1_4_1/netif/ppp/chap.c \
../lwip-1_4_1/netif/ppp/chpms.c \
../lwip-1_4_1/netif/ppp/fsm.c \
../lwip-1_4_1/netif/ppp/ipcp.c \
../lwip-1_4_1/netif/ppp/lcp.c \
../lwip-1_4_1/netif/ppp/magic.c \
../lwip-1_4_1/netif/ppp/md5.c \
../lwip-1_4_1/netif/ppp/pap.c \
../lwip-1_4_1/netif/ppp/ppp.c \
../lwip-1_4_1/netif/ppp/ppp_oe.c \
../lwip-1_4_1/netif/ppp/randm.c \
../lwip-1_4_1/netif/ppp/vj.c 

OBJS += \
./lwip-1_4_1/netif/ppp/auth.o \
./lwip-1_4_1/netif/ppp/chap.o \
./lwip-1_4_1/netif/ppp/chpms.o \
./lwip-1_4_1/netif/ppp/fsm.o \
./lwip-1_4_1/netif/ppp/ipcp.o \
./lwip-1_4_1/netif/ppp/lcp.o \
./lwip-1_4_1/netif/ppp/magic.o \
./lwip-1_4_1/netif/ppp/md5.o \
./lwip-1_4_1/netif/ppp/pap.o \
./lwip-1_4_1/netif/ppp/ppp.o \
./lwip-1_4_1/netif/ppp/ppp_oe.o \
./lwip-1_4_1/netif/ppp/randm.o \
./lwip-1_4_1/netif/ppp/vj.o 

C_DEPS += \
./lwip-1_4_1/netif/ppp/auth.d \
./lwip-1_4_1/netif/ppp/chap.d \
./lwip-1_4_1/netif/ppp/chpms.d \
./lwip-1_4_1/netif/ppp/fsm.d \
./lwip-1_4_1/netif/ppp/ipcp.d \
./lwip-1_4_1/netif/ppp/lcp.d \
./lwip-1_4_1/netif/ppp/magic.d \
./lwip-1_4_1/netif/ppp/md5.d \
./lwip-1_4_1/netif/ppp/pap.d \
./lwip-1_4_1/netif/ppp/ppp.d \
./lwip-1_4_1/netif/ppp/ppp_oe.d \
./lwip-1_4_1/netif/ppp/randm.d \
./lwip-1_4_1/netif/ppp/vj.d 


# Each subdirectory must supply rules for building sources it contributes
lwip-1_4_1/netif/ppp/%.o: ../lwip-1_4_1/netif/ppp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DNDEBUG -I../hal -I../hal/CortexM3 -I../hal/CortexM3/GNU -I../CMSIS -I../CMSIS/startup_gcc -I../drivers/mss_uart -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FreeRTOS" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FreeRTOS\include" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FreeRTOS\portable" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FreeRTOS\portable\GCC" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FreeRTOS\portable\GCC\ARM_CM3" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FreeRTOS\portable\MemMang" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\drivers\mss_ethernet_mac" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FF15a" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\FF15a\source" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\port" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\port\FreeRTOS" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\port\FreeRTOS\M2SXXX" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\api" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\core" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\core\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\core\snmp" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\include" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\include\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\include\ipv4\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\include\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\include\posix" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\include\posix\sys" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\lwip-1_4_1\netif\ppp" -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


