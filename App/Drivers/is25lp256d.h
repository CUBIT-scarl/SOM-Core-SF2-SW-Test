/**
  ******************************************************************************
  * @file           : IS25LP256D.h
  * @brief          : Header for IS25LP256D file.
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
#ifndef IS25LP256D_H_
#define IS25LP256D_H_

#include "usr_global.h"
#include "core_qspi.h"

/* Define I/O macros -------------------------------------------------------- */

/* Define Software macros --------------------------------------------------- */

/* Define Constants --------------------------------------------------------- */

//CUT #define USE_QSPI_INTERRUPT      1u	// Interrupt transfer mode. Comment for Polling mode (Interrupt mode not tested).

#define IS25LP_PAGE_LENGTH                      256u
#define IS25LP_SECTOR_SIZE                      4096u

#define IS25LP_RESET_ENABLE                     0x66
#define IS25LP_RESET_MEMORY                     0x99

#define IS25LP_READ_ID_OPCODE                   0x9F
#define IS25LP_MIO_READ_ID_OPCODE               0xAF

#define IS25LP_READ                             0x03
#define IS25LP_4BYTE_FAST_READ                  0x0C

#define IS25LP_WRITE_ENABLE                     0x06
#define IS25LP_WRITE_DISABLE                    0x04

#define IS25LP_READ_STATUS_REG                  0x05
#define IS25LP_READ_FLAG_STATUS_REG             0x81
#define IS25LP_READ_NV_CONFIG_REG               0xB5
#define IS25LP_READ_V_CONFIG_REG                0x61
#define IS25LP_READ_ENH_V_CONFIG_REG            0x61

#define IS25LP_WR_ENH_V_CONFIG_REG              0x65
#define IS25LP_CLR_FLAG_STATUS_REG              0x50

#define IS25LP_4BYTE_PAGE_PROG                  0x12    // 4PP
#define IS25LP_BULK_ERASE                       0xC7
#define IS25LP_4BYTE_4KB_SUBSECTOR_ERASE        0x21

#define IS25LP_ENTER_4BYTE_ADDR_MODE            0xB7
#define IS25LP_EXIT_4BYTE_ADDR_MODE             0xE9

#define IS25LP_ENTER_QUAD_IO_MODE               0x35
#define IS25LP_RESET_QUAD_IO_MODE               0xF5

#define IS25LP_JEDEC_ID                         0x9D

#define IS25LP_STATUS_OK                        0x00
#define I25LP_STATUS_BUSY_MASK                  0x01u
#define I25LP_STATUS_EFAIL_MASK                 0x08u
#define I25LP_STATUS_PFAIL_MASK                 0x04u


/* Define Types ------------------------------------------------------------- */

/* Prototypes --------------------------------------------------------------- */

void	QSPIFlash_init(core_qspi_io_format io_format);
void 	QSPIFlash_readid(uint8_t* buf);
void 	QSPIFlash_read(uint8_t* buf, uint32_t addr, uint32_t len);
uint8_t QSPIFlash_erase(void);
uint8_t QSPIFlash_sector_erase(uint16_t sect);
uint8_t QSPIFlash_program(uint8_t* buf, uint32_t addr, uint32_t len);
void 	QSPIFlash_read_status_regs(uint8_t *buf);
void 	QSPIFlash_clr_flagstatusreg(void);
void    QSPIFlash_timeout(uint32_t t);
void    QSPIFlash_wait_msec(uint32_t t);

#endif /* IS25LP256D_H_*/

/*EOF*/
