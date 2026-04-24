/**
  ******************************************************************************
  * @file           : driver_utils.c
  * @brief          : Utilities and various I/O management.
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
#include "usr_global.h"


/* Define External Variables ------------------------------------------------ */

extern volatile uint32_t tickCounter;


/* Define Constants --------------------------------------------------------- */

/* Define Global variables -------------------------------------------------- */

/* General purpose Main Program Software Timer ------------------------------ */

/**
  * @brief  Passive wait for n milliseconds
  * @param  t = waiting time [ms]
  * @retval None
  */
void WaitMsec(uint32_t t)
{
    tickCounter = t;
    while (tickCounter);
}

/**
  * @brief  Initialise a waiting time for n milliseconds
  * @param  t = waiting time [ms]
  * @retval None
  */
void SetMsec (uint16_t t)
{
 tickCounter = t;
}


/**
  * @brief  check for waiting time elapsed
  * @param  None
  * @retval 0 = Still running, 1 = elapsed
  */
uint8_t isWaitEnd (void)
{
  if (tickCounter) return(0);
  return(1);
}


/**
  * @brief  Passive wait for n microseconds
  * @param  t = waiting time [us]
  * @retval None
  */
void Delay_us(uint32_t t)
{
  volatile uint32_t counter;

  counter = t * (SystemCoreClock/1000000)/25;

  // Decrement the counter for approximate waiting
  while (counter--);
}

/* EOF */
