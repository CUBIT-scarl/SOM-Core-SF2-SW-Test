/**
  ******************************************************************************
  * @file           : usr_global.h
  * @brief          : global include file
  * @note           : Project code 82037801
  ******************************************************************************
  */
 /******************************************************************************
 * # License
 * <b>Copyright 2026 CUBIT scarl http://www.cubitlab.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Cubit scarl has no
 * obligation to support this Software. Cubit scarl is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Cubit scarl will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/
#ifndef USR_GLOBAL_H_
#define USR_GLOBAL_H_

#define TRUE	1
#define FALSE	0

#include "../drivers/CoreGPIO/core_gpio.h"
#include "../drivers/mss_uart/mss_uart.h"
#include "../drivers/mss_spi/mss_spi.h"
#include "../drivers/mss_nvm/mss_nvm.h"
#include "../drivers/mss_timer/mss_timer.h"
#include "../drivers/mss_sys_services/mss_sys_services.h"
#include "../drivers/mss_ethernet_mac/mss_ethernet_mac.h"
#include "../DesignTop_hw_platform.h"

#include "system_m2sxxx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "..\FreeRTOSConfig.h"
#include "..\FreeRTOS\include\FreeRTOS.h"
#include "..\FreeRTOS\include\timers.h"
#include "..\FreeRTOS\include\task.h"
#include "..\FreeRTOS\include\queue.h"

#include "lwip/tcpip.h"
#include "lwip/dhcp.h"
#include "lwip/udp.h"

#include "FF15a/source/ffconf.h"
#include "FF15a/source/ff.h"

#include "main.h"

#include "Drivers\driver_utils.h"
#include "Drivers\w25q64.h"
#include "Drivers\uart0.h"
#include "Drivers\is25lp256d.h"
#include "Drivers\core_qspi.h"
#include "Drivers\core_qspi_regs.h"

#include "VirtualLcd\virtuallcd.h"

#include "usr_main.h"
#include "usr_utils.h"
#include "test.h"

#endif /* USR_GLOBAL_H_ */

/*EOF*/
