/**
  ******************************************************************************
  * @file           : usr_utils.h
  * @brief          : Header file.
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
#ifndef USR_UTILS_H_
#define USR_UTILS_H_

/* Define I/O macros -------------------------------------------------------- */

/* Define Software macros --------------------------------------------------- */

/* Define the macro for building IPv4 addresses.  */
#define IP_ADDRESS(a, b, c, d)  ((((uint32_t)a) << 24) | (((uint32_t)b) << 16) | (((uint32_t)c) << 8) | ((uint32_t)d))

/* Define Constants --------------------------------------------------------- */

/* Define Types ------------------------------------------------------------- */

/* Prototypes --------------------------------------------------------------- */

uint8_t isUSRBTNpressed (void);

void ETHconfigureInterface(void * param);
uint32_t get_ip_address(void);
uint32_t get_netmask(void);
void get_mac_address(uint8_t * mac_addr);

nvm_status_t UPDFILEeraseFlash(uint32_t len);
nvm_status_t UPDFILEwriteFlash(uint8_t* buf, uint32_t addr, uint32_t len);
uint8_t UPDFILEsetQSPIparams(uint32_t len, uint32_t crc);

#endif /* USR_UTILS_H_ */
/*EOF*/
