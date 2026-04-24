/**
  ******************************************************************************
  * @file           : uart0.h
  * @brief          : Header for driver_utils file.
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
#ifndef UART0_H_
#define UART0_H_

#include "usr_global.h"

/* Define I/O macros -------------------------------------------------------- */

/* Define Software macros --------------------------------------------------- */

/* Define Constants --------------------------------------------------------- */

#define UART0_RXBUFLEN      1024
#define UART0_TXBUFLEN      1024


/* Define Types ------------------------------------------------------------- */

/* Prototypes --------------------------------------------------------------- */

void 		UART0init(uint32_t baud);
void 		UART0startRx(void);
void 		UART0stopRx(void);
void 		UART0flushRxBuffer(void);
void 		UART0sendMsg (uint8_t *c,uint16_t size);
void 		UART0sendMsgPolling (uint8_t *c, uint16_t size);
uint8_t		UART0isTxEnd (void);
uint16_t	UART0isRxData (void);
uint8_t 	UART0receiveData(void);
void 		UART0enable_UserRx(void);
void 		UART0disable_UserRx(void);
void        uart0_rx_handler(mss_uart_instance_t *this_uart);

#endif /* UART2_H_ */
/*EOF*/
