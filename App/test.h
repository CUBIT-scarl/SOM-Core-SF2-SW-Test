/**
  ******************************************************************************
  * @file           : test.h
  * @brief          : Header file
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
#ifndef TEST_H_
#define TEST_H_

/* Define I/O macros -------------------------------------------------------- */

/* Define Software macros --------------------------------------------------- */

/* Define Constants --------------------------------------------------------- */

/* Define Types ------------------------------------------------------------- */

typedef struct
{
  uint8_t address[4];
  uint8_t netmask[4];
  uint8_t gateway[4];
} IPstruct;


/* Prototypes --------------------------------------------------------------- */

void Test_Null(void);
void Test_RESET(void);
void Test_SPI0(void);
void Test_GPIO(void);
void Test_LPDDR(void);
void Test_VARIOUS(void);
void Test_ETH_UDP(void);
void udp0RxCallback(void* arg, struct udp_pcb* upcb, struct pbuf* p, const ip_addr_t* addr, u16_t port);
void Test_QSPI(void);
void Test_FAT32(void);
void Test_LinkMD(void);

uint8_t	StrToHex (uint8_t *p);

#endif /* TEST_H_ */

/*EOF*/
