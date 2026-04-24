/*******************************************************************************
 * (c) Copyright 2011-2015 Microsemi SoC Products Group.  All rights reserved.
 * 
 * Register bit definitions for MII STA (station management entity) standard
 * interface. All basic MII register bits and enhanced capability register bits
 * are defined.
 * Complies with Clauses 22, 28, 37, 40 of IEEE RFC 802.3
 * 
 * SVN $Revision: 7577 $
 * SVN $Date: 2015-07-22 17:32:52 +0530 (Wed, 22 Jul 2015) $
 */
#ifndef PHY_H_
#define PHY_H_
#include "mss_ethernet_mac_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************/
/* Public definitions                                                     */
/**************************************************************************/
/*------------------------------------------------------------------------------
 * MII register definitions.
 */
/* Generic MII registers. */
#define MII_BMCR                0x00u       /* Basic mode control register */
#define MII_BMSR                0x01u       /* Basic mode status register  */
#define MII_PHYSID1             0x02u       /* PHYS ID 1                   */
#define MII_PHYSID2             0x03u       /* PHYS ID 2                   */
#define MII_ADVERTISE           0x04u       /* Advertisement control reg   */
#define MII_LPA                 0x05u       /* Link partner ability reg    */
#define MII_EXPANSION           0x06u       /* Expansion register          */
#define MII_NPAR                0x07u
#define MII_LPNPA               0x08u
#define MII_CTRL1000            0x09u       /* 1000BASE-T control          */
#define MII_STAT1000            0x0au       /* 1000BASE-T status           */
#define MII_MMD_CTRL            0x0du       /* MMD access - control        */
#define MII_MMD_REGDAT          0x0eu       /* MMD access - register/data  */
#define MII_ESTATUS             0x0fu       /* Extended Status             */
#define MII_LOOPBACK            0x11u       /* Remote loopback             */
#define MII_LINKMD              0x12u       /* LinkMD diagnostic           */
#define MII_FCSCOUNTER          0x13u       /* False carrier counter       */
#define MII_RERRCOUNTER         0x15u       /* Receive error counter       */
#define MII_TPISTATUS           0x1bu       /* TPI status for 10mbps       */
#define MII_NCONFIG             0x1cu       /* Network interface config    */
#define MII_PHYCTRL             0x1fu

/* Basic mode control register. */
#define BMCR_RESV               0x003fu     /* Unused...                   */
#define BMCR_SPEED1000          0x0040u     /* MSB of Speed (1000)         */
#define BMCR_CTST               0x0080u     /* Collision test              */
#define BMCR_FULLDPLX           0x0100u     /* Full duplex                 */
#define BMCR_ANRESTART          0x0200u     /* Auto negotiation restart    */
#define BMCR_ISOLATE            0x0400u     /* Disconnect DP83840 from MII */
#define BMCR_PDOWN              0x0800u     /* Powerdown the DP83840       */
#define BMCR_ANENABLE           0x1000u     /* Enable auto negotiation     */
#define BMCR_SPEED100           0x2000u     /* Select 100Mbps              */
#define BMCR_LOOPBACK           0x4000u     /* TXD loopback bits           */
#define BMCR_RESET              0x8000u     /* Reset the DP83840           */

/* Basic mode status register. */
#define BMSR_ERCAP              0x0001u     /* Ext-reg capability          */
#define BMSR_JCD                0x0002u     /* Jabber detected             */
#define BMSR_LSTATUS            0x0004u     /* Link status                 */
#define BMSR_ANEGCAPABLE        0x0008u     /* Able to do auto-negotiation */
#define BMSR_RFAULT             0x0010u     /* Remote fault detected       */
#define BMSR_ANEGCOMPLETE       0x0020u     /* Auto-negotiation complete   */
#define BMSR_RESV               0x00c0u     /* Unused...                   */
#define BMSR_ESTATEN            0x0100u     /* Extended Status in R15 */
#define BMSR_100HALF2           0x0200u     /* Can do 100BASE-T2 HDX */
#define BMSR_100FULL2           0x0400u     /* Can do 100BASE-T2 FDX */
#define BMSR_10HALF             0x0800u     /* Can do 10mbps, half-duplex  */
#define BMSR_10FULL             0x1000u     /* Can do 10mbps, full-duplex  */
#define BMSR_100HALF            0x2000u     /* Can do 100mbps, half-duplex */
#define BMSR_100FULL            0x4000u     /* Can do 100mbps, full-duplex */
#define BMSR_100BASE4           0x8000u     /* Can do 100mbps, 4k packets  */

/* Advertisement control register. */
#define ADVERTISE_10HALF        0x0020u     /* Try for 10mbps half-duplex  */
#define ADVERTISE_10FULL        0x0040u     /* Try for 10mbps full-duplex  */
#define ADVERTISE_100HALF       0x0080u     /* Try for 100mbps half-duplex */
#define ADVERTISE_100FULL       0x0100u     /* Try for 100mbps full-duplex */


/**************************************************************************/
/* Public function declarations                                           */
/**************************************************************************/

/***************************************************************************//**
 
 */
void MSS_MAC_phy_init(uint8_t phy_addr);

/***************************************************************************//**
 
 */
void MSS_MAC_phy_set_link_speed(uint32_t speed_duplex_select);

/***************************************************************************//**
 
 */
void MSS_MAC_phy_autonegotiate(void);

/***************************************************************************//**
 
 */
uint8_t MSS_MAC_phy_get_link_status
(
    mss_mac_speed_t * speed,
    uint8_t * fullduplex
);

void MSS_MAC_phy_dump(void);
#ifdef __cplusplus
}
#endif

#endif /* PHY_H_ */


