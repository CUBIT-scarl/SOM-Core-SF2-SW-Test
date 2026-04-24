/**
  ******************************************************************************
  * @file           : driver_utils.h
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
#ifndef DRIVER_UTILS_H_
#define DRIVER_UTILS_H_

/* Define I/O macros -------------------------------------------------------- */

/* Define Software macros --------------------------------------------------- */

/* Define Constants --------------------------------------------------------- */

/* Define Types ------------------------------------------------------------- */

/* Prototypes --------------------------------------------------------------- */

void    WaitMsec(uint32_t t);
void    SetMsec (uint16_t t);
uint8_t isWaitEnd (void);
void    Delay_us(uint32_t t);

#endif /* DRIVER_UTILS_H_ */

/*EOF*/
