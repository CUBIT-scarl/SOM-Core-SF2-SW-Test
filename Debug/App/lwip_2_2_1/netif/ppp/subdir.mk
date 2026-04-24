################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/lwip_2_2_1/netif/ppp/auth.c \
../App/lwip_2_2_1/netif/ppp/ccp.c \
../App/lwip_2_2_1/netif/ppp/chap-md5.c \
../App/lwip_2_2_1/netif/ppp/chap-new.c \
../App/lwip_2_2_1/netif/ppp/chap_ms.c \
../App/lwip_2_2_1/netif/ppp/demand.c \
../App/lwip_2_2_1/netif/ppp/eap.c \
../App/lwip_2_2_1/netif/ppp/ecp.c \
../App/lwip_2_2_1/netif/ppp/eui64.c \
../App/lwip_2_2_1/netif/ppp/fsm.c \
../App/lwip_2_2_1/netif/ppp/ipcp.c \
../App/lwip_2_2_1/netif/ppp/ipv6cp.c \
../App/lwip_2_2_1/netif/ppp/lcp.c \
../App/lwip_2_2_1/netif/ppp/magic.c \
../App/lwip_2_2_1/netif/ppp/mppe.c \
../App/lwip_2_2_1/netif/ppp/multilink.c \
../App/lwip_2_2_1/netif/ppp/ppp.c \
../App/lwip_2_2_1/netif/ppp/pppapi.c \
../App/lwip_2_2_1/netif/ppp/pppcrypt.c \
../App/lwip_2_2_1/netif/ppp/pppoe.c \
../App/lwip_2_2_1/netif/ppp/pppol2tp.c \
../App/lwip_2_2_1/netif/ppp/pppos.c \
../App/lwip_2_2_1/netif/ppp/upap.c \
../App/lwip_2_2_1/netif/ppp/utils.c \
../App/lwip_2_2_1/netif/ppp/vj.c 

OBJS += \
./App/lwip_2_2_1/netif/ppp/auth.o \
./App/lwip_2_2_1/netif/ppp/ccp.o \
./App/lwip_2_2_1/netif/ppp/chap-md5.o \
./App/lwip_2_2_1/netif/ppp/chap-new.o \
./App/lwip_2_2_1/netif/ppp/chap_ms.o \
./App/lwip_2_2_1/netif/ppp/demand.o \
./App/lwip_2_2_1/netif/ppp/eap.o \
./App/lwip_2_2_1/netif/ppp/ecp.o \
./App/lwip_2_2_1/netif/ppp/eui64.o \
./App/lwip_2_2_1/netif/ppp/fsm.o \
./App/lwip_2_2_1/netif/ppp/ipcp.o \
./App/lwip_2_2_1/netif/ppp/ipv6cp.o \
./App/lwip_2_2_1/netif/ppp/lcp.o \
./App/lwip_2_2_1/netif/ppp/magic.o \
./App/lwip_2_2_1/netif/ppp/mppe.o \
./App/lwip_2_2_1/netif/ppp/multilink.o \
./App/lwip_2_2_1/netif/ppp/ppp.o \
./App/lwip_2_2_1/netif/ppp/pppapi.o \
./App/lwip_2_2_1/netif/ppp/pppcrypt.o \
./App/lwip_2_2_1/netif/ppp/pppoe.o \
./App/lwip_2_2_1/netif/ppp/pppol2tp.o \
./App/lwip_2_2_1/netif/ppp/pppos.o \
./App/lwip_2_2_1/netif/ppp/upap.o \
./App/lwip_2_2_1/netif/ppp/utils.o \
./App/lwip_2_2_1/netif/ppp/vj.o 

C_DEPS += \
./App/lwip_2_2_1/netif/ppp/auth.d \
./App/lwip_2_2_1/netif/ppp/ccp.d \
./App/lwip_2_2_1/netif/ppp/chap-md5.d \
./App/lwip_2_2_1/netif/ppp/chap-new.d \
./App/lwip_2_2_1/netif/ppp/chap_ms.d \
./App/lwip_2_2_1/netif/ppp/demand.d \
./App/lwip_2_2_1/netif/ppp/eap.d \
./App/lwip_2_2_1/netif/ppp/ecp.d \
./App/lwip_2_2_1/netif/ppp/eui64.d \
./App/lwip_2_2_1/netif/ppp/fsm.d \
./App/lwip_2_2_1/netif/ppp/ipcp.d \
./App/lwip_2_2_1/netif/ppp/ipv6cp.d \
./App/lwip_2_2_1/netif/ppp/lcp.d \
./App/lwip_2_2_1/netif/ppp/magic.d \
./App/lwip_2_2_1/netif/ppp/mppe.d \
./App/lwip_2_2_1/netif/ppp/multilink.d \
./App/lwip_2_2_1/netif/ppp/ppp.d \
./App/lwip_2_2_1/netif/ppp/pppapi.d \
./App/lwip_2_2_1/netif/ppp/pppcrypt.d \
./App/lwip_2_2_1/netif/ppp/pppoe.d \
./App/lwip_2_2_1/netif/ppp/pppol2tp.d \
./App/lwip_2_2_1/netif/ppp/pppos.d \
./App/lwip_2_2_1/netif/ppp/upap.d \
./App/lwip_2_2_1/netif/ppp/utils.d \
./App/lwip_2_2_1/netif/ppp/vj.d 


# Each subdirectory must supply rules for building sources it contributes
App/lwip_2_2_1/netif/ppp/%.o: ../App/lwip_2_2_1/netif/ppp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I../hal -I../hal/CortexM3 -I../hal/CortexM3/GNU -I../CMSIS -I../CMSIS/startup_gcc -I../drivers/mss_uart -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\api" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\netif\ppp" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\core" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\core\ipv4" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\lwip" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\include\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\netif" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port\NoRTOS" -I"C:\Microchip\SoftConsole-v2021.3-7.0.0.599\extras\workspace.examples\PRJ82037801_Test_Manuale\App\lwip_2_2_1\port\NoRTOS\M2SXXX" -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


