/**
  ******************************************************************************
  * @file           : main.h
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
#ifndef MAIN_H_
#define MAIN_H_

/* Define I/O macros -------------------------------------------------------- */

/* GPIO Label -> GPIO_number */
#define ETH_RES_N           GPIO_13
#define UART0_MUX           GPIO_14
#define USR_BTN_N           GPIO_15
#define USR_LED_N           GPIO_16
#define SOM_READY_N         GPIO_18

/* GPIO Mask -> GPIO_number_mask */
#define ETH_RES_N_MASK      GPIO_13_MASK
#define UART0_MUX_MASK      GPIO_14_MASK
#define USR_BTN_N_MASK      GPIO_15_MASK
#define USR_LED_N_MASK      GPIO_16_MASK
#define SOM_READY_N_MASK    GPIO_18_MASK

/* Read pin macro */
#define READ_USRBTN     GPIO_get_inputs(&g_gpio0)

/* Set out pin macro */
#define ETH_RES_ON      GPIO_set_output(&g_gpio0,ETH_RES_N, 0)
#define ETH_RES_OFF     GPIO_set_output(&g_gpio0,ETH_RES_N, 1)

#define UART0_MUX_USB   GPIO_set_output(&g_gpio0,UART0_MUX, 0)
#define UART0_MUX_IO    GPIO_set_output(&g_gpio0,UART0_MUX, 1)

#define USR_LED_ON      GPIO_set_output(&g_gpio0,USR_LED_N, 0)
#define USR_LED_OFF     GPIO_set_output(&g_gpio0,USR_LED_N, 1)

#define SOM_READY_ON    GPIO_set_output(&g_gpio0,SOM_READY_N, 0)
#define SOM_READY_OFF   GPIO_set_output(&g_gpio0,SOM_READY_N, 1)


/* Define Software macros --------------------------------------------------- */

/* Define Constants --------------------------------------------------------- */

// These Constants must be the same as those defined in BOOT Software
#define COREGPIO_BASE_ADDRESS0      COREGPIO_C1_0_0
#define COREGPIO_BASE_ADDRESS1      COREGPIO_C1_0

// These Constants must be the same as those defined in BOOT Software
#define LPDDR_BASE_ADDRESS          0xA0000000

#define LPDDR_16MB_LAST_ADDR        (LPDDR_BASE_ADDRESS + 0xFFFFFF)
#define LPDDR_32MB_LAST_ADDR        (LPDDR_BASE_ADDRESS + 0x1FFFFFF)
#define LPDDR_64MB_LAST_ADDR        (LPDDR_BASE_ADDRESS + 0x3FFFFFF)

// These Constants must be the same as those defined in BOOT Software
#define QSPI_FAT32_NUM_SECTORS      6192                        // QSPI num.sectors for FAT32 partition (max 8192)
#define QSPI_START_RAW_FLASH        (QSPI_FAT32_NUM_SECTORS+1)  // QSPI raw flash memory start sector
#define QSPI_APP_PARAMS             QSPI_START_RAW_FLASH        // QSPI raw flash memory App Sw parameters sector
#define QSPI_APP_START              (QSPI_APP_PARAMS+1)         // QSPI raw flash memory App Sw start sector

#define QSPI_ADDR_PROGLENGTH        ((QSPI_APP_PARAMS * IS25LP_SECTOR_SIZE)+4)  // Location for QSPI App software  length (4 Bytes)
#define QSPI_ADDR_PROGCRC           ((QSPI_APP_PARAMS * IS25LP_SECTOR_SIZE)+8)  // Location for QSPI App software  Checksum (4 Bytes)

// These Constants must be the same as those defined in BOOT Software
#define BOOT_FROM_NOBOOT                0x00                        // Normal Bootstrap sequence
#define BOOT_FROM_UART2NVM              0x01                        // BOOT rx from Uart0 to update NVM (App running in the internal flash)
#define BOOT_FROM_UART2QSPI             0x02                        // BOOT rx from Uart0 to update QSPI (App running in external RAM)
#define BOOT_FROM_QSPI2NVM              0x03                        // BOOT read from QSPI to update NVM (App running in the internal flash)
#define BOOT_FROM_QSPI2EXTRAM           0x04                        // BOOT read from QSPI (App running in external RAM)
#define BOOT_FROM_END                   0x05                        // End of Boot options

// Constants about SPIflash as storage for FPGA Fabric Golden Image and Auto Update
#define W25Q64_DIR_SECT                 0           // Directory sector
#define W25Q64_GOLDEN_SECT_START        1           // Start sector for Fabric Golden Image
#define W25Q64_GOLDEN_SECT_END          257         // End sector for Fabric Golden Image   (1MB)
#define W25Q64_AUTOUPD_SECT_START       258         // Start sector for Fabric Auto Update
#define W25Q64_AUTOUPD_SECT_END         514         // End sector for Fabric Auto Update    (1MB)
#define W25Q64_USER_SECT_START          515         // Start sector for User Program
#define W25Q64_USER_SECT_END            2047        // End sector for User Program          (6MB)


/* Define Types ------------------------------------------------------------- */

/* Prototypes --------------------------------------------------------------- */

#endif /* MAIN_H_ */
/*EOF*/
