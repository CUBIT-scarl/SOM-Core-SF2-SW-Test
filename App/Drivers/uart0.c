/**
  ******************************************************************************
  * @file           : uart0.c
  * @brief          : Uart0 management
  * @note           : Project code 82037801
  *
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
#include "usr_global.h"

/* Define External Variables ------------------------------------------------ */

/* Define Constants --------------------------------------------------------- */

/* Define Global variables -------------------------------------------------- */

uint8_t     uart0TxBuffer[UART0_TXBUFLEN];		// Buffer di trasmissione
uint16_t 	uart0TxIndex;				        // Indice Tx buffer
uint16_t 	uart0LenTxMsg = 0;			        // Lunghezza pacchetto da trasmettere

uint8_t     uart0RxByte;                        // Byte ricevuto su seriale
uint8_t 	uart0RxBuffer[UART0_RXBUFLEN];		// Buffer di ricezione
uint16_t	uart0ps,uart0pl;			        // Puntatori Rx Buffer

uint8_t	    uart0_enable_UserRx = 0;		    // Flag abilitazione funzione Utente


/* Functions ---------------------------------------------------------------- */

/**
  * @brief  Uart0 Driver Init
  * @param  baud = baud rate (MSS_UART_110_BAUD..MSS_UART_19200_BAUD...MSS_UART_921600_BAUD)
  * @note   Fixed Uart configuration baud,N,8,1
  * @note   User Rx callback must be enabled in Main Program
  * @retval None
  */
void UART0init(uint32_t baud)
{
  uint16_t i;
  
  for (i = 0; i < UART0_RXBUFLEN; i++) uart0RxBuffer[i] = 0;
  for (i = 0; i < UART0_TXBUFLEN; i++) uart0TxBuffer[i] = 0;
  uart0TxIndex = uart0LenTxMsg = 0;
  uart0ps = uart0pl = 0;
  
  MSS_UART_init(&g_mss_uart0, baud, MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
  MSS_UART_set_rx_handler(&g_mss_uart0, uart0_rx_handler, MSS_UART_FIFO_SINGLE_BYTE);
}


/**
  * @brief  Uart0 rx enable
  * @param  none
  * @retval None
  */
void UART0startRx(void)
{
    MSS_UART_set_rx_handler(&g_mss_uart0, uart0_rx_handler, MSS_UART_FIFO_SINGLE_BYTE);
}


/**
  * @brief  Uart0 rx disanable
  * @param  none
  * @retval None
  */
void UART0stopRx(void)
{
    MSS_UART_disable_irq(&g_mss_uart0,MSS_UART_RBF_IRQ);
}


/**
  * @brief  Uart0 flush rx buffer
  * @param  none
  * @retval None
  */
void UART0flushRxBuffer(void)
{
  uart0ps = uart0pl = 0;
}


/**
  * @brief  Uart0 send message (interrupt)
  * @param  c = pointer to send message buffer
  *         size = message length
  * @retval None
  */
void UART0sendMsg (uint8_t *c, uint16_t size)
{
  uint16_t i = 0;

  while (!UART0isTxEnd());				// Wait for previous Tx end

  while (i < size)					    // Message copy in Tx local Buffer
  {
    uart0TxBuffer[i]=c[i];
    i++;
  }
  MSS_UART_irq_tx (&g_mss_uart0, (uint8_t*)uart0TxBuffer, size);	// Start Tx
}


/**
  * @brief  Uart0 send message (polling)
  * @param  c = pointer to send message buffer
  *         size = message length
  * @retval None
  */
void UART0sendMsgPolling (uint8_t *c, uint16_t size)
{
    MSS_UART_polled_tx(&g_mss_uart0, c, size);      // Polling Tx
}


/**
  * @brief  Return Tx message end flag
  * @param  None
  * @retval 0 = Tx running, 1 = tx end
  */
uint8_t UART0isTxEnd (void)
{
    return (MSS_UART_tx_complete(&g_mss_uart0));
}


/**
  * @brief  Return Rx buffer status
  * @param  None
  * @retval n = number of Rx bytes
  */
uint16_t UART0isRxData (void)
{
 if (uart0ps == uart0pl) return (0);

 if (uart0ps > uart0pl)  return (uart0ps-uart0pl);
 else 			 return (UART0_RXBUFLEN-uart0pl+uart0ps);
}


/**
  * @brief  Return one byte from Rx buffer
  * @param  None
  * @retval Byte read
  * @note   Main program must check the availability of data in Rx buffer before call this function
  */
uint8_t UART0receiveData(void)
{
 uint8_t dat;

 if (uart0ps != uart0pl)
 {
  dat = uart0RxBuffer[uart0pl++];
  if (uart0pl >= UART0_RXBUFLEN) uart0pl = 0;		// Buffer circolare
  return(dat);
 }
 return(0);
}


/**
  * @brief  User Rx callback enable
  * @param  None
  * @retval None
  */
void UART0enable_UserRx(void)
{
 uart0_enable_UserRx = 1;
}


/**
  * @brief  User Rx callback disable
  * @param  None
  * @retval None
  */
void UART0disable_UserRx(void)
{
 uart0_enable_UserRx = 0;
}


/* Interrupts --------------------------------------------------------------- */

/**
  * @brief  Uart0 Rx IRQ
  * @param  None
  * @retval None
  */
void uart0_rx_handler(mss_uart_instance_t *this_uart)
{
    MSS_UART_get_rx(this_uart, &uart0RxByte, sizeof(uart0RxBuffer));
    uart0RxBuffer[uart0ps] = uart0RxByte;						// Write received byte to rx buffer

    uart0ps++;									                // Increment write pointer
    if (uart0ps >= UART0_RXBUFLEN) uart0ps = 0;					// Check circular buffer
    if (uart0ps == uart0pl)							            // If buffer full, overwrite last byte
    {
        uart0ps--;
        if (uart0ps == 0xFFFF) uart0ps = UART0_RXBUFLEN-1;
    }
    if (uart0_enable_UserRx) USRuart0Rx(uart0RxByte);			// Call user callback
}

/*EOF*/
