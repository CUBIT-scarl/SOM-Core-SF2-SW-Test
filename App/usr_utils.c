/**
  ******************************************************************************
  * @file           : usr_utils.c
  * @brief          : User utilities
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

extern gpio_instance_t g_gpio0;
extern IPstruct my_ip;


/* Define Constants --------------------------------------------------------- */

/* Define Global variables -------------------------------------------------- */

struct netif s_EMAC_if; // lwIP MAC configuration


/* User Utilities ----------------------------------------------------------- */

/**
  * @brief  Return state of USR_BTN#
  * @param  none
  * @retval 1 = pressed, 0 = released
  */
uint8_t isUSRBTNpressed (void)
{
    uint32_t dat;

    dat =  READ_USRBTN;
    dat &= USR_BTN_N_MASK;
    if (dat)                // Active low input
        return(0);
    return (1);
}


/* Ethernet Utilities ------------------------------------------------------- */

/**
  * @brief  Configure Ethernet Interface
  * @param  None
  * @retval None
  */
void ETHconfigureInterface(void * param)
{
    struct ip_addr xIpAddr, xNetMask, xGateway;
    extern err_t ethernetif_init( struct netif *netif );
    volatile err_t status;
    IPstruct *p = param;

    /* Parameters are not used - suppress compiler error. */
//    ( void ) param;

    /* Create and configure the EMAC interface. */
    if (p->address[0] == 0x00)                  // DCHP
    {
        IP4_ADDR( &xIpAddr, 0, 0, 0, 0 );
    }
    else                                        // Static IP
    {
        IP4_ADDR( &xIpAddr, p->address[0], p->address[1], p->address[2], p->address[3]);
        IP4_ADDR( &xNetMask, p->netmask[0], p->netmask[1], p->netmask[2], p->netmask[3]);
        IP4_ADDR( &xGateway, p->gateway[0], p->gateway[1], p->gateway[2], p->gateway[3]);
    }

    netif_add( &s_EMAC_if, &xIpAddr, &xNetMask, &xGateway, NULL, ethernetif_init, tcpip_input );

    /* bring it up */
    if (p->address[0] == 0x00)
        status = dhcp_start(&s_EMAC_if);    // DCHP
    else
        netif_set_up(&s_EMAC_if);           // static IP

    /* make it the default interface */
    netif_set_default(&s_EMAC_if);
}


/**
  * @brief  Return IP Address
  * @param  None
  * @retval IP address
  */
uint32_t get_ip_address(void)
{
    return (uint32_t)(s_EMAC_if.ip_addr.addr);
}


/**
  * @brief  Return NetMask
  * @param  None
  * @retval Netmask
  */
uint32_t get_netmask(void)
{
    return (uint32_t)(s_EMAC_if.netmask.addr);
}


/**
  * @brief  Return MAC address
  * @param  mac_addr = pointer to MAC address 6 bytes array
  * @retval none
  */
void get_mac_address(uint8_t * mac_addr)
{
    uint32_t inc;

    for(inc = 0; inc < 6; ++inc)
    {
        mac_addr[inc] = s_EMAC_if.hwaddr[inc];
    }
}


/* Update Image File Utilities ---------------------------------------------- */

/**
  * @brief  Erase Flash Memory reserved for the Application Program Update Image file
  * @param  len = file length. If len = 0 erase all Raw flash memory available
  * @retval 0 = NVM_SUCCESS = ok, otherwise = error
  */
nvm_status_t UPDFILEeraseFlash(uint32_t len)
{
    uint8_t ret;
    uint16_t sect, ndel, rem;

    /* Erase QSPI flash raw section optimised on File Length */
    if (len != 0)
    {
        ndel = len / IS25LP_SECTOR_SIZE;
        rem = len % IS25LP_SECTOR_SIZE;
        if (rem) ndel++;
        ndel++;                             // Erase also the Parameters sector
    }
    else
    {
        ndel = 8192 - QSPI_START_RAW_FLASH; // Erase all raw flash memory
    }

    sect = QSPI_APP_PARAMS;
    while (ndel--)
    {
        ret = QSPIFlash_sector_erase(sect++);
        if (ret != 0)
        {
            QSPIFlash_clr_flagstatusreg();
            return (ret);
        }
    }
    return (NVM_SUCCESS);
}


/**
  * @brief  Write Flash Memory reserved for the Application Program Update Image file
  * @param  buf  pointer to the buffer from which data will be written into the flash memory
  * @param  addr data write start address
  * @param  len  number of data bytes to write into the flash memory
  * @retval 0 = success, nonzero = error
  */
nvm_status_t UPDFILEwriteFlash(uint8_t* buf, uint32_t addr, uint32_t len)
{
    nvm_status_t status;

    status = QSPIFlash_program(buf, addr, len);
    return (status);
}


/**
  * @brief  Save Update Image File Crc and Length in QSPI_APP_PARAMS sector of the raw flash memory
  * @param  none
  * @retval 1 = error, 0 = ok
*/
uint8_t UPDFILEsetQSPIparams(uint32_t len, uint32_t crc)
{
    uint8_t status = 0;
    static uint8_t buf[8] ;

    status = QSPIFlash_sector_erase(QSPI_APP_PARAMS);
    if (status)
        return (status);

    buf[0] = (len & 0x000000ff);
    buf[1] = (len & 0x0000ff00) >>  8;
    buf[2] = (len & 0x00ff0000) >> 16;
    buf[3] = (len & 0xff000000) >> 24;

    buf[4] = (crc & 0x000000ff);
    buf[5] = (crc & 0x0000ff00) >>  8;
    buf[6] = (crc & 0x00ff0000) >> 16;
    buf[7] = (crc & 0xff000000) >> 24;

    status = QSPIFlash_program(buf, (QSPI_APP_PARAMS * IS25LP_SECTOR_SIZE), 8);
    return (status);
}

/*EOF*/
