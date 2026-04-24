/*******************************************************************************
 * (c) Copyright 2011-2015 Microsemi SoC Products Group.  All rights reserved.
 *
 * Microchip KSZ9031MNL PHY interface driver implementation.
 *
 */
#include "phy.h"
#include "mss_ethernet_mac_types.h"
#include "mss_ethernet_mac.h"
#include "../../CMSIS/mss_assert.h"

#ifdef __cplusplus
extern "C" {
#endif
/**************************************************************************/
/* Preprocessor Macros                                                    */
/**************************************************************************/

#define BMSR_AUTO_NEGOTIATION_COMPLETE  0x0020u

/***************************************************************************//**
 * Address of the PHY on the MII management interface.
 */
static uint8_t g_phy_addr = 0u;

/**************************************************************************//**
 * 
 */
#define ANEG_REQUESTED          0x80000000u
#define FORCED_CFG_REQUESTED    0x40000000u


/**************************************************************************//**
 * PHY initialisation and Errata workaround

https://www.oryx-embedded.com/doc/ksz9031__driver_8c_source.html
   Workaround:
   After device power-up/reset, change the FLP interval to 16ms using the following programming sequence to set
   MMD - Device Address 0h, Register 4h = 0x0006 and MMD - Device Address 0h, Register 3h = 0x1A80:

   a) Write Register Dh = 0x0000 //Set up register address for MMD - Device Address 0h
   b) Write Register Eh = 0x0004 //Select Register 4h of MMD - Device Address 0h
   c) Write Register Dh = 0x4000 //Select register data for MMD - Device Address 0h, Register 4h
   d) Write Register Eh = 0x0006 //Write value 0x0006 to MMD - Device Address 0h, Register 4h
   e) Write Register Dh = 0x0000 //Set up register address for MMD - Device Address 0h
   f) Write Register Eh = 0x0003 //Select Register 3h of MMD - Device Address 0h
   g) Write Register Dh = 0x4000 //Select register data for MMD - Device Address 0h, Register 3h
   h) Write Register Eh = 0x1A80 //Write value 0x1A80 to MMD - Device Address 0h, Register 3h

   Then restart Auto-Negotiation for the 16ms FLP interval setting to take effect.
 */


void MSS_MAC_phy_init(uint8_t phy_addr)
{
    uint8_t i;

    g_phy_addr = phy_addr;

    //Reset PHY transceiver
    MSS_MAC_write_phy_reg(g_phy_addr, MII_BMCR, BMCR_RESET);
    //Wait for the reset to complete
    while(MSS_MAC_read_phy_reg(g_phy_addr, MII_BMCR) & BMCR_RESET);

    //Change the FLP interval to 16ms (silicon errata workaround 5)
    MSS_MAC_write_phy_reg(g_phy_addr, MII_MMD_CTRL,   0x0000);
    MSS_MAC_write_phy_reg(g_phy_addr, MII_MMD_REGDAT, 0x0004);
    MSS_MAC_write_phy_reg(g_phy_addr, MII_MMD_CTRL,   0x4000);
    MSS_MAC_write_phy_reg(g_phy_addr, MII_MMD_REGDAT, 0x0006);
    MSS_MAC_write_phy_reg(g_phy_addr, MII_MMD_CTRL,   0x0000);
    MSS_MAC_write_phy_reg(g_phy_addr, MII_MMD_REGDAT, 0x0003);
    MSS_MAC_write_phy_reg(g_phy_addr, MII_MMD_CTRL,   0x4000);
    MSS_MAC_write_phy_reg(g_phy_addr, MII_MMD_REGDAT, 0x1A80);

    //MSS_MAC_phy_dump();
}


/**************************************************************************//**
 * 
 */
void MSS_MAC_phy_set_link_speed(uint32_t speed_duplex_select)
{
    uint16_t phy_reg;
    uint32_t inc;
    uint32_t speed_select;
    const uint16_t mii_advertise_bits[4] = {ADVERTISE_10FULL, ADVERTISE_10HALF,
                                            ADVERTISE_100FULL, ADVERTISE_100HALF};
    
    /* Set auto-negotiation advertisement. */
    
    /* Set 10Mbps and 100Mbps advertisement. */
    phy_reg = MSS_MAC_read_phy_reg(g_phy_addr, MII_ADVERTISE);
    phy_reg &= ~(ADVERTISE_10HALF | ADVERTISE_10FULL |
                 ADVERTISE_100HALF | ADVERTISE_100FULL);
                 
    speed_select = speed_duplex_select;
    for(inc = 0u; inc < 4u; ++inc)
    {
        uint32_t advertise;
        advertise = speed_select & 0x00000001u;
        if(advertise != 0u)
        {
            phy_reg |= mii_advertise_bits[inc];
        }
        speed_select = speed_select >> 1u;
    }
    
    MSS_MAC_write_phy_reg(g_phy_addr, MII_ADVERTISE, phy_reg);
}

/**************************************************************************//**
 * 
 */
void MSS_MAC_phy_autonegotiate(void)
{
    uint16_t phy_reg, dat;
    uint16_t autoneg_complete;
    volatile uint32_t copper_aneg_timeout = 2000000u;
    
    /* Enable auto-negotiation. */
    phy_reg = 0x1300;
    MSS_MAC_write_phy_reg(g_phy_addr, MII_BMCR, phy_reg);
    
    /* Wait for copper auto-negotiation to complete. */
    do {
        phy_reg = MSS_MAC_read_phy_reg(g_phy_addr, MII_BMSR);
        autoneg_complete = phy_reg & BMSR_AUTO_NEGOTIATION_COMPLETE;
        --copper_aneg_timeout;
    } while((!autoneg_complete && (copper_aneg_timeout != 0u)) || (0xFFFF == phy_reg));

   // MSS_MAC_phy_dump();
}

/**************************************************************************//**
 * 
 */
uint8_t MSS_MAC_phy_get_link_status
(
    mss_mac_speed_t * speed,
    uint8_t *     fullduplex
)
{
    uint16_t phy_reg;
    uint16_t link_up;
    uint8_t link_status;

    phy_reg = MSS_MAC_read_phy_reg(g_phy_addr, MII_BMSR);
    link_up = phy_reg & BMSR_LSTATUS;
    
    if(link_up != MSS_MAC_LINK_DOWN)
    {
        uint16_t op_mode;
        
        /* Link is up. */
        link_status = MSS_MAC_LINK_UP;
        
        phy_reg = MSS_MAC_read_phy_reg(g_phy_addr, MII_PHYCTRL);

        if (phy_reg & 0x0008)
            *fullduplex = MSS_MAC_FULL_DUPLEX;
        else
            *fullduplex = MSS_MAC_HALF_DUPLEX;

        op_mode = phy_reg & 0x0070u;
        op_mode >>= 4;
        switch(op_mode)
        {
            case 1:
                *speed = MSS_MAC_10MBPS;
            break;
            
            case 2:
                *speed = MSS_MAC_100MBPS;
            break;
            
            case 4:
                *speed = MSS_MAC_1000MBPS;
            break;

            default:
                link_status = MSS_MAC_LINK_DOWN;
            break;
        }
    }
    else
    {
        /* Link is down. */
        link_status = MSS_MAC_LINK_DOWN;
    }
    
    return link_status;
}


/* Debug utilities */

//uint16_t phyregs[32];       // PHY registers dump buffer
//
//void MSS_MAC_phy_dump(void)
//{
//    uint8_t i;
//
//    for (i = 0; i < 32; i++)
//    {
//        phyregs[i] = MSS_MAC_read_phy_reg(g_phy_addr, i);
//    }
//}


#ifdef __cplusplus
}
#endif

/******************************** END OF FILE ******************************/






