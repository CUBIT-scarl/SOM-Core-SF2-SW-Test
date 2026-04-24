/**
  ******************************************************************************
  * @file           : w25q64.c
  * @brief          : Header file
  * @note           : Project code 82037801
  *
  * W25Q64JVZPIQ
  * 2,097,152 bytes
  * 512 sectors * 4,096 bytes
  * 8192 pages  * 256 bytes
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
#ifndef W25Q64_H_
#define W25Q64_H_

#include "usr_global.h"

/* Define I/O macros -------------------------------------------------------- */

/* Define Software macros --------------------------------------------------- */

/* Define Constants --------------------------------------------------------- */

#define SPI0_PAYLOAD    1024                // SPI0 TxRx Payload length
#define SPI0_TXRXBUFLEN (4+SPI0_PAYLOAD)    // SPI0 TxRx total buffer length

#define W25Q64_MANUFACTURER     0xEF
#define W25Q64_MEMORY_TYPE      0x40
#define W25Q64_CAPACITY         0x17    // 64Mbit

#define W25Q64_SECTOR_SHIFT     12      // Sector size 1 << 15 = 65,536
#define W25Q64_NSECTORS         512
#define W25Q64_PAGE_SHIFT       8       // Page size 1 << 8 = 256
#define W25Q64_NPAGES           8192
#define W25Q64_SECTOR_LEN       4096

/* Instructions */
#define W25Q64_RDSR             0x05    // Read Status Register
#define W25Q64_FAST_READ        0x0B    // Fast Read
#define W25Q64_RDID             0x9F    // Read Identification
#define W25Q64_WREN             0x06    // Write Enable
#define W25Q64_WRDI             0x04    // Write Disable
#define W25Q64_SE               0x20    // Sector Erase
#define W25Q64_BE32             0x52    // 32K Block Erase
#define W25Q64_BE64             0xd8    // 64K Block Erase
#define W25Q64_CE               0xc7    // Chip Erase
#define W25Q64_PP               0x02    // Page Program
#define W25Q64_ULBPR            0x98    // Global Block Protection unlock

/* Status register bit definitions */
#define W25Q64_SR_WIP       (1 << 0)    /* Bit 0: Write in progress */
#define W25Q64_SR_WEL       (1 << 1)    /* Bit 1: Write enable latch */
#define W25Q64_SR_WSE       (1 << 2)    /* Bit 2: Write Suspend-Erase Status */
#define W25Q64_SR_WSP       (1 << 3)    /* Bit 3: Write Suspend-Program Status */
#define W25Q64_SR_WPLD      (1 << 4)    /* Bit 4: Write Protection Lock-Down Status */
#define W25Q64_SR_SEC       (1 << 5)    /* Bit 5: Security ID status */
#define W25Q64_SR_RES       (1 << 6)    /* Bit 6: RFU */
#define W25Q64_SR_WIP2      (1 << 7)    /* Bit 7: Write in progress */


/* Define Types ------------------------------------------------------------- */


/* Prototypes --------------------------------------------------------------- */

uint8_t W25Q64readid(void);
void    W25Q64waitwritecomplete(void);
void    W25Q64globalunlock(void);
void    W25Q64writeenable(void);
void    W25Q64writedisable(void);
void    W25Q64sectorerase(off_t sector, uint8_t cmd);
void    W25Q64chiperase(void);
uint16_t W25Q64pagewrite(uint8_t *buffer, uint16_t len, off_t page);
uint16_t W25Q64bytewrite(uint8_t *buffer, uint16_t len, off_t offset);

uint8_t W25Q64init(void);
void    W25Q64erase(off_t startsect, size_t nsect);
uint32_t W25Q64bread(off_t startblock, size_t nblocks, uint8_t *buffer);
void    W25Q64bwrite (off_t startpage, size_t npages, uint8_t *buffer);
uint32_t W25Q64read (off_t offset, size_t nbytes, uint8_t *buffer);
void W25Q64write(off_t offset, size_t nbytes, uint8_t *buffer);

#endif /* W25Q64_H_ */

/*EOF*/
