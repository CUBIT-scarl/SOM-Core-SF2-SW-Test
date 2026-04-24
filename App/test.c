/**
  ******************************************************************************
  * @file           : test.c
  * @brief          : Manual Test Procedures
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

extern gpio_instance_t g_gpio0, g_gpio1;

extern uint8_t BootSw       __attribute__((section(".infoboot4"))); // Boot strategy parameter

extern uint8_t kk[41];


/* Define Constants --------------------------------------------------------- */

/* Define Global variables -------------------------------------------------- */

/* Test Procedures ---------------------------------------------------------- */
static uint8_t my_probe_phy(void);

/**
  * @brief  Test not implemented
  * @param  None
  * @retval None
  */
void Test_Null(void)
{
    VL_Clear();
    VL_SetForeColor(BLUE);
    VL_Curs(0, 1);
    VL_Puts((uint8_t*)"TEST NOT YET IMPLEMENTED!");
    VL_Curs(19, 1);
    VL_Puts((uint8_t*)"Press a key to Exit...");
    VL_SetForeColor(BLACK);
    VL_WaitKey();
    VL_Clear();
}


/**
  * @brief  Test RESET
  * @param  None
  * @retval None
  */
void Test_RESET(void)
{
uint8_t c=0;

   VL_Clear();
   VL_SetForeColor(BLUE);
   VL_Curs(0,1);
   VL_Puts((uint8_t*)"[TEST RESET]");
   VL_Curs(16, 1);
   VL_Puts((uint8_t*)"Reset                   = F1");
   VL_Curs(17, 1);
   VL_Puts((uint8_t*)"Reset + Boot UART->NVM  = F2");
   VL_Curs(18, 1);
   VL_Puts((uint8_t*)"Reset + Boot UART->QSPI = F3");
   VL_Curs(19, 1);
   VL_Puts((uint8_t*)"ESC=Exit");
   VL_SetForeColor(BLACK);
   while (c != K_ESC)
   {
       c = 0;
       if (VL_IsKey())
       {
           c = VL_GetKey();
           if (c == K_F1)
           {
               VL_Curs(4, 1);
               VL_Puts((uint8_t*)"System Reset...");
               WaitMsec(1000);
               BootSw = BOOT_FROM_NOBOOT;
               NVIC_SystemReset();
               WaitMsec(1000);
           }
           else if (c == K_F2)
           {
               VL_Curs(4, 1);
               VL_Puts((uint8_t*)"Reset + BOOT from Uart to NVM");
               WaitMsec(1000);
               BootSw = BOOT_FROM_UART2NVM;
               NVIC_SystemReset();
               WaitMsec(1000);
           }
           else if (c == K_F3)
           {
               VL_Curs(4, 1);
               VL_Puts((uint8_t*)"Reset + BOOT from Uart to QSPI");
               WaitMsec(1000);
               BootSw = BOOT_FROM_UART2QSPI;
               NVIC_SystemReset();
               WaitMsec(1000);
           }
       }
   }
   VL_Clear();
}


/**
  * @brief  Test SPI Flash W25Q64 su SPI0
  * @param  None
  * @retval None
  */
uint8_t spiTxBuf[256];
uint8_t spiRxBuf[256];

void Test_SPI0(void)
{
    uint8_t c=0, i, status;
    uint32_t offset, sector;

    offset = 0x1000;                                // Test Address 0x1000
    sector = offset / W25Q64_SECTOR_LEN;            // Sector number = 1;

    VL_Clear();
    VL_SetForeColor(BLUE);
    VL_Curs(0, 1);
    VL_Puts((uint8_t*)"TEST W25Q64 (SPI0)");
    VL_Curs(18, 1);
     VL_Puts((uint8_t*)"F1=Wr1 F2=Wr2 F3=Rd ");
     VL_Curs(19, 1);
    VL_Puts((uint8_t*)"ESC=exit F4=Erase F5=EraseAll");
    VL_SetForeColor(BLACK);

    VL_Curs(2, 1);
    VL_Puts((uint8_t*)"SPI0 init...");
    status = W25Q64init();
    if (status == 0)
        VL_Puts((uint8_t*)"OK");
    else
    {
        VL_SetForeColor(RED);
        VL_Puts((uint8_t*)"ERROR");
        VL_SetForeColor(BLACK);
        WaitMsec(2000);
        goto esci;
    }
    while (c != K_ESC)
    {
        c = 0;
        if (VL_IsKey())
        {
            c = VL_GetKey();
            if (c == K_F1)
            {
                VL_Curs(5, 1);
                VL_Puts((uint8_t*)"                             ");
                VL_Curs(4, 1);
                VL_Puts((uint8_t*)"Write pattern1...            ");
                memcpy(spiTxBuf,(const uint8_t*)"1234567890",10);       // Write pattern1 to Tx Buffer
                memset(spiRxBuf,0x00,sizeof(spiRxBuf));                 // Clear Rx Buffer
                W25Q64write(offset, 10, spiTxBuf);
                VL_Curs(4, 18);
                VL_Puts((uint8_t*)"OK");
            }
            else if (c == K_F2)
            {
                VL_Curs(5, 1);
                VL_Puts((uint8_t*)"                             ");
                VL_Curs(4, 1);
                VL_Puts((uint8_t*)"Write pattern2...            ");
                memcpy(spiTxBuf,(const uint8_t*)"ABCDEFGHIL",10);       // Write pattern2 to Tx Buffer
                memset(spiRxBuf,0x00,sizeof(spiRxBuf));                 // Clear Rx Buffer
                W25Q64write(offset, 10, spiTxBuf);
                VL_Curs(4, 18);
                VL_Puts((uint8_t*)"OK");
            }
            else if (c == K_F3)
            {
                VL_Curs(5, 1);
                VL_Puts((uint8_t*)"                             ");
                VL_Curs(4, 1);
                VL_Puts((uint8_t*)"Read...                      ");
                memset(spiRxBuf,0x00,sizeof(spiRxBuf));                 // Clear Rx Buffer
                W25Q64read (offset, 10, spiRxBuf);
                VL_Curs(4, 15);
                VL_Puts((uint8_t*)"OK");
                VL_Curs(5, 1);
                VL_Puts((uint8_t*)"Rx: ");
                for (i=0; i < 10; i++)
                {
                    sprintf (kk,"%C ", spiRxBuf[i]);
                    VL_Puts(kk);
                }
            }
            else if (c == K_F4)
             {
                 VL_Curs(5, 1);
                 VL_Puts((uint8_t*)"                             ");
                 VL_Curs(4, 1);
                 VL_Puts((uint8_t*)"Erase Test Sector...         ");
                 W25Q64erase(sector, 1);
                 VL_Curs(4, 21);
                 VL_Puts((uint8_t*)"OK");
             }
            else if (c == K_F5)
             {
                 VL_Curs(5, 1);
                 VL_Puts((uint8_t*)"                             ");
                 VL_Curs(4, 1);
                 VL_Puts((uint8_t*)"Erase SPI Flash...           ");
                 W25Q64chiperase();
                 VL_Curs(4, 19);
                 VL_Puts((uint8_t*)"OK");
             }
        }
    }
esci:
    VL_SwClear();
    VL_Clear();
}


/**
  * @brief  Store in SPIflash SPI0 Fabric Auto Update Image and Golden Image
  * @param  None
  * @retval None
  */
#define AUTOUPDLEN  ((W25Q64_GOLDEN_SECT_END-W25Q64_GOLDEN_SECT_START) * W25Q64_SECTOR_LEN)

#pragma pack(1)
struct                              // SPI Flash Directory
{
    uint32_t GoldenImageAddress;    // Address where the Golden Image starts
    uint16_t GoldenImageVersion;    // Design version of the Golden Image
    uint32_t UpdateImageAddress;    // Address where the Update Image starts
    uint16_t UpdateImageVersion;    // Design version of the Update Image
} AUTOUPDstruct;
#pragma pack()

uint8_t AutoUpdBuf[AUTOUPDLEN] __attribute__((section(".lpddrram_gp0")));
uint8_t AutoUpdBuf2[AUTOUPDLEN] __attribute__((section(".lpddrram_gp0")));

void Test_AutoUPD(void)
{
    uint8_t c=0, status, *p;
    uint32_t offset, Cnt, i;
    uint16_t Dat;

    VL_Clear();
    VL_SetForeColor(BLUE);
    VL_Curs(0, 1);
    VL_Puts((uint8_t*)"Store FPGA Fabric images SPIflash");
    VL_Curs(18, 1);
    VL_Puts((uint8_t*)"F3=ShowDIR  F4=ShowSectors");
    VL_Curs(19, 1);
    VL_Puts((uint8_t*)"ESC=exit F1=Golden F2=AutoUpd");
    VL_SetForeColor(BLACK);

    /* Set USR_BTN# as input */
    GPIO_config(&g_gpio0, USR_BTN_N, GPIO_INPUT_MODE);

    VL_Curs(2, 1);
    VL_Puts((uint8_t*)"SPI0 init...");
    status = W25Q64init();
    if (status == 0)
        VL_Puts((uint8_t*)"OK");
    else
    {
        VL_SetForeColor(RED);
        VL_Puts((uint8_t*)"ERROR");
        VL_SetForeColor(BLACK);
        WaitMsec(2000);
        goto esci;
    }

    while (c != K_ESC)
    {
        c = 0;
        if (VL_IsKey())
        {
            c = VL_GetKey();
            if (c == K_F1)
            {
                VL_Curs(2, 1);
                VL_Puts((uint8_t*)"Close VirtualLCD serial port and ");
                VL_Curs(3, 1);
                VL_Puts((uint8_t*)"download file at 115200,N,8,1 ");
                VL_Curs(4, 1);
                VL_Puts((uint8_t*)"Then reopen Virtual LCD serial port and");
                VL_Curs(5, 1);
                VL_Puts((uint8_t*)"press USR_BTN on the FPGA module");

                UART0disable_UserRx();
                UART0flushRxBuffer();
                Cnt = 0;
                while(Cnt < AUTOUPDLEN && !isUSRBTNpressed())
                {
                    if (UART0isRxData())
                    {
                        AutoUpdBuf[Cnt++] = UART0receiveData();
                    }
                }
                UART0enable_UserRx();
                if (Cnt == 0 || Cnt > AUTOUPDLEN)
                {
                    VL_Curs(7, 1);
                    VL_SetForeColor(RED);
                    VL_Puts((uint8_t*)"ERROR: No file or File too long");
                    VL_SetForeColor(BLACK);
                    WaitMsec(2000);
                    goto esci;
                }
                VL_Curs(7, 1);
                sprintf(kk,"Rx %d bytes", Cnt);
                VL_Puts(kk);
                VL_Curs(8,1);
                VL_Puts("Version: ");
                Dat = VL_GetWordValue(0);
                VL_Curs(9, 1);
                VL_Puts("Saving...");
                p = (uint8_t*)&AUTOUPDstruct;
                offset = W25Q64_DIR_SECT * W25Q64_SECTOR_LEN;
                W25Q64read(offset, sizeof(AUTOUPDstruct), p);               // Read Directory
                AUTOUPDstruct.GoldenImageVersion = Dat;
                W25Q64erase(W25Q64_DIR_SECT, 1);                        // Erase Directory sector
                W25Q64erase(W25Q64_GOLDEN_SECT_START, ((Cnt/W25Q64_SECTOR_LEN)+1));   // Erase Golden Image sector (optimized)
                AUTOUPDstruct.GoldenImageAddress =  W25Q64_GOLDEN_SECT_START * W25Q64_SECTOR_LEN;
                offset = W25Q64_DIR_SECT * W25Q64_SECTOR_LEN;
                W25Q64write(offset, sizeof(AUTOUPDstruct), p);              // Write Directory
                offset = W25Q64_GOLDEN_SECT_START * W25Q64_SECTOR_LEN;
                W25Q64write(offset, Cnt, AutoUpdBuf);                       // Write Golden Image File
                VL_Puts(" DONE");

                VL_Curs(10,1);
                VL_Puts("Verify...");
                offset = W25Q64_DIR_SECT * W25Q64_SECTOR_LEN;
                W25Q64read(offset, sizeof(AUTOUPDstruct), p);
                VL_SwPuts("DIR (Hex):\r\n");
                sprintf (kk,"%04X, %02X\r\n", AUTOUPDstruct.GoldenImageAddress, AUTOUPDstruct.GoldenImageVersion);
                VL_SwPuts(kk);
                sprintf (kk,"%04X, %02X\r\n", AUTOUPDstruct.UpdateImageAddress, AUTOUPDstruct.UpdateImageVersion);
                VL_SwPuts(kk);
                offset = W25Q64_GOLDEN_SECT_START * W25Q64_SECTOR_LEN;
                W25Q64read(offset, Cnt, AutoUpdBuf2);
                status = 0;
                for(i = 0; i < Cnt; i++)
                {
                  if (AutoUpdBuf2[i] != AutoUpdBuf[i])
                  {
                      status = 1;
                      break;
                  }
                }
                if (status == 1)
                {
                  VL_SetForeColor(RED);
                  sprintf(kk,"ERROR. Cnt= %d", i);
                  VL_Puts(kk);
                  VL_SetForeColor(BLACK);
                }
                else
                {
                  VL_Puts("OK");
                  VL_SwPuts("GOLDEN IMG. SECT (64bytes Hex):\r\n");
                  for (i = 0; i < 64; i+=4)
                  {
                      sprintf (kk,"%02X %02X %02X %02X\r\n", AutoUpdBuf2[i],AutoUpdBuf2[i+1],AutoUpdBuf2[i+2],AutoUpdBuf2[i+3]);
                      VL_SwPuts(kk);
                  }

                }
            }
            else if (c == K_F2)
            {
                VL_Curs(2, 1);
                VL_Puts((uint8_t*)"Close VirtualLCD serial port and ");
                VL_Curs(3, 1);
                VL_Puts((uint8_t*)"download file at 115200,N,8,1 ");
                VL_Curs(4, 1);
                VL_Puts((uint8_t*)"Then reopen Virtual LCD serial port and");
                VL_Curs(5, 1);
                VL_Puts((uint8_t*)"press USR_BTN on the FPGA module");

                UART0disable_UserRx();
                UART0flushRxBuffer();
                Cnt = 0;
                while(Cnt < AUTOUPDLEN && !isUSRBTNpressed())
                {
                     if (UART0isRxData())
                     {
                         AutoUpdBuf[Cnt++] = UART0receiveData();
                     }
                }
                UART0enable_UserRx();
                if (Cnt == 0 || Cnt > AUTOUPDLEN)
                {
                 VL_Curs(7, 1);
                 VL_SetForeColor(RED);
                 VL_Puts((uint8_t*)"ERROR: No file or File too long");
                 VL_SetForeColor(BLACK);
                 WaitMsec(2000);
                 goto esci;
                }
                VL_Curs(7, 1);
                sprintf(kk,"Rx %d bytes", Cnt);
                VL_Puts(kk);
                VL_Curs(8,1);
                VL_Puts("Version: ");
                Dat = VL_GetWordValue(0);
                VL_Curs(9, 1);
                VL_Puts("Saving...");
                p = (uint8_t*)&AUTOUPDstruct;
                offset = W25Q64_DIR_SECT * W25Q64_SECTOR_LEN;
                W25Q64read(offset, sizeof(AUTOUPDstruct), p);               // Read Directory
                AUTOUPDstruct.UpdateImageVersion = Dat;
                W25Q64erase(W25Q64_DIR_SECT, 1);                        // Erase Directory sector
                W25Q64erase(W25Q64_AUTOUPD_SECT_START, ((Cnt/W25Q64_SECTOR_LEN)+1));   // Erase Golden Image sector (optimized)
                AUTOUPDstruct.UpdateImageAddress =  W25Q64_AUTOUPD_SECT_START * W25Q64_SECTOR_LEN;
                offset = W25Q64_DIR_SECT * W25Q64_SECTOR_LEN;
                W25Q64write(offset, sizeof(AUTOUPDstruct), p);              // Write Directory
                offset = W25Q64_AUTOUPD_SECT_START * W25Q64_SECTOR_LEN;
                W25Q64write(offset, Cnt, AutoUpdBuf);                       // Write Golden Image File
                VL_Puts(" DONE");

                VL_Curs(10,1);
                VL_Puts("Verify...");
                offset = W25Q64_DIR_SECT * W25Q64_SECTOR_LEN;
                W25Q64read(offset, sizeof(AUTOUPDstruct), p);
                VL_SwPuts("DIR (Hex):\r\n");
                sprintf (kk,"%04X, %02X\r\n", AUTOUPDstruct.GoldenImageAddress, AUTOUPDstruct.GoldenImageVersion);
                VL_SwPuts(kk);
                sprintf (kk,"%04X, %02X\r\n", AUTOUPDstruct.UpdateImageAddress, AUTOUPDstruct.UpdateImageVersion);
                VL_SwPuts(kk);
                offset = W25Q64_AUTOUPD_SECT_START * W25Q64_SECTOR_LEN;
                W25Q64read(offset, Cnt, AutoUpdBuf2);
                status = 0;
                for(i = 0; i < Cnt; i++)
                {
                    if (AutoUpdBuf2[i] != AutoUpdBuf[i])
                    {
                        status = 1;
                        break;
                    }
                }
                if (status == 1)
                {
                    VL_SetForeColor(RED);
                    sprintf(kk,"ERROR. Cnt= %d", i);
                    VL_Puts(kk);
                    VL_SetForeColor(BLACK);
                }
                else
                {
                    VL_Puts("OK");
                    VL_SwPuts("AUTOUPD SECT (64bytes Hex):\r\n");
                    for (i = 0; i < 64; i+=4)
                    {
                        sprintf (kk,"%02X %02X %02X %02X\r\n", AutoUpdBuf2[i],AutoUpdBuf2[i+1],AutoUpdBuf2[i+2],AutoUpdBuf2[i+3]);
                        VL_SwPuts(kk);
                    }

                }
            }
            else if (c == K_F3)
            {
                offset = W25Q64_DIR_SECT * W25Q64_SECTOR_LEN;
                W25Q64read(offset, sizeof(AUTOUPDstruct), (uint8_t*) &AUTOUPDstruct);
                VL_SwPuts("DIR (Hex):\r\n");
                sprintf (kk,"%04X, %02X\r\n", AUTOUPDstruct.GoldenImageAddress, AUTOUPDstruct.GoldenImageVersion);
                VL_SwPuts(kk);
                sprintf (kk,"%04X, %02X\r\n", AUTOUPDstruct.UpdateImageAddress, AUTOUPDstruct.UpdateImageVersion);
                VL_SwPuts(kk);
            }
            else if (c == K_F4)
            {
                memset(AutoUpdBuf2,0xFF,sizeof(AutoUpdBuf2));
                offset = W25Q64_GOLDEN_SECT_START * W25Q64_SECTOR_LEN;
                W25Q64read(offset, 64, AutoUpdBuf2);
                VL_SwPuts("GOLDEN SECT (64bytes Hex):\r\n");
                for (i = 0; i < 64; i+=4)
                {
                    sprintf (kk,"%02X %02X %02X %02X\r\n", AutoUpdBuf2[i],AutoUpdBuf2[i+1],AutoUpdBuf2[i+2],AutoUpdBuf2[i+3]);
                    VL_SwPuts(kk);
                }
                memset(AutoUpdBuf2,0xFF,sizeof(AutoUpdBuf2));
                offset = W25Q64_AUTOUPD_SECT_START * W25Q64_SECTOR_LEN;
                W25Q64read(offset, 64, AutoUpdBuf2);
                VL_SwPuts("AUTOUPD SECT (64bytes Hex):\r\n");
                for (i = 0; i < 64; i+=4)
                {
                    sprintf (kk,"%02X %02X %02X %02X\r\n", AutoUpdBuf2[i],AutoUpdBuf2[i+1],AutoUpdBuf2[i+2],AutoUpdBuf2[i+3]);
                    VL_SwPuts(kk);
                }
            }
        }
    }
esci:
    VL_Clear();
}


/**
  * @brief  Test GPIO Short Circuits integrity
  * @param  None
  * @retval None
  * @note   All GPIO pins (except the ones with external pull-down) must have pull-up enabled
  *         (see I/O constraints in FPGA Fabric project)
  * @note   Pins with external or internal pull-down are excluded (masked) from this test
  *
  * @note   For reliable results leave the SOM module not connected to any board
  */

#define PULL_DOWN_PINS_MASK (GPIO_13_MASK|GPIO_14_MASK) // ETH_RES# and UART0_MUX = pull-down

typedef struct
{
    uint32_t    num;
    uint32_t    mask;
    char        name[4];
    char        label[12];
} gpio_matrix;

#define GPIO0_NUM  32
#define GPIO1_NUM  26
#define GPIO_NUM  (GPIO0_NUM + GPIO1_NUM)

gpio_matrix gpio_map[GPIO_NUM] = {
        GPIO_0,  GPIO_0_MASK,  "E5 ",    "GP40",
        GPIO_1,  GPIO_1_MASK,  "F1 ",    "GP32",
        GPIO_2,  GPIO_2_MASK,  "F3 ",    "GP34",
        GPIO_3,  GPIO_3_MASK,  "F4 ",    "GP38",
        GPIO_4,  GPIO_4_MASK,  "F5 ",    "GP30",
        GPIO_5,  GPIO_5_MASK,  "F6 ",    "GP24",
        GPIO_6,  GPIO_6_MASK,  "F7 ",    "GP22",
        GPIO_7,  GPIO_7_MASK,  "G1 ",    "GP28",
        GPIO_8,  GPIO_8_MASK,  "G2 ",    "GP26",
        GPIO_9,  GPIO_9_MASK,  "G3 ",    "GP16",
        GPIO_10, GPIO_10_MASK, "G4 ",    "GP12",
        GPIO_11, GPIO_11_MASK, "A19",    "I2C0_SCL",
        GPIO_12, GPIO_12_MASK, "A20",    "I2C0_SDA",
        GPIO_13, GPIO_13_MASK, "C1 ",    "ETH_RES#",
        GPIO_14, GPIO_14_MASK, "C2 ",    "UART0_MUX",
        GPIO_15, GPIO_15_MASK, "D2 ",    "USR_BTN#",
        GPIO_16, GPIO_16_MASK, "E1 ",    "USR_LED#",
        GPIO_17, GPIO_17_MASK, "E2 ",    "GP36",
        GPIO_18, GPIO_18_MASK, "E3 ",    "SOM_READY#",
        GPIO_19, GPIO_19_MASK, "F18",    "UART1_RXD",
        GPIO_20, GPIO_20_MASK, "G6 ",    "GP14",
        GPIO_21, GPIO_21_MASK, "G16",    "UART1_TXD",
        GPIO_22, GPIO_22_MASK, "G17",    "SPI0_CS1#",
        GPIO_23, GPIO_23_MASK, "H4 ",    "GP8",
        GPIO_24, GPIO_24_MASK, "H5 ",    "GP6",
        GPIO_25, GPIO_25_MASK, "H6 ",    "GP10",
        GPIO_26, GPIO_26_MASK, "J7 ",    "GP21",
        GPIO_27, GPIO_27_MASK, "J20",    "SPI1_CS#",
        GPIO_28, GPIO_28_MASK, "K20",    "SPI1_DO",
        GPIO_29, GPIO_29_MASK, "L15",    "SPI1_CLK",
        GPIO_30, GPIO_30_MASK, "L16",    "SPI1_DI",
        GPIO_31, GPIO_31_MASK, "M17",    "I2C1_SCL",
        GPIO_0,  GPIO_0_MASK,  "M19",    "n.c.",
        GPIO_1,  GPIO_1_MASK,  "N16",    "I2C1_SDA",
        GPIO_2,  GPIO_2_MASK,  "N20",    "CAN_RX",
        GPIO_3,  GPIO_3_MASK,  "R12",    "GP23",
        GPIO_4,  GPIO_4_MASK,  "R13",    "GP25",
        GPIO_5,  GPIO_5_MASK,  "R15",    "CAN_TX",
        GPIO_6,  GPIO_6_MASK,  "T13",    "GP29",
        GPIO_7,  GPIO_7_MASK,  "T14",    "GP27",
        GPIO_8,  GPIO_8_MASK,  "T15",    "GP5",
        GPIO_9,  GPIO_9_MASK,  "U11",    "GP13",
        GPIO_10, GPIO_10_MASK, "U12",    "GP7",
        GPIO_11, GPIO_11_MASK, "U13",    "GP15",
        GPIO_12, GPIO_12_MASK, "U14",    "GP9",
        GPIO_13, GPIO_13_MASK, "V11",    "GP11",
        GPIO_14, GPIO_14_MASK, "V12",    "GP31",
        GPIO_15, GPIO_15_MASK, "V14",    "GP33",
        GPIO_16, GPIO_16_MASK, "V15",    "GP37",
        GPIO_17, GPIO_17_MASK, "W10",    "GP35",
        GPIO_18, GPIO_18_MASK, "W13",    "GP46",
        GPIO_19, GPIO_19_MASK, "W14",    "GP45",
        GPIO_20, GPIO_20_MASK, "W15",    "GP43",
        GPIO_21, GPIO_21_MASK, "Y10",    "GP44",
        GPIO_22, GPIO_22_MASK, "Y12",    "GP48",
        GPIO_23, GPIO_23_MASK, "Y13",    "GP42",
        GPIO_24, GPIO_24_MASK, "Y15",    "GP41",
        GPIO_25, GPIO_25_MASK, "Y16",    "GP39"
};

void Test_GPIO(void)
{
    uint8_t c=0, i, j, pinerr;
    uint64_t gpio_inputs, pinmask;
    gpio_instance_t *p;

    VL_Clear();
    VL_SetForeColor(BLUE);
    VL_Curs(0, 1);
    VL_Puts((uint8_t*)"TEST GPIO short circuits");
    VL_Curs(2, 1);
    VL_Puts((uint8_t*)"For reilable results keep the SOM");
    VL_Curs(3, 1);
    VL_Puts((uint8_t*)"disconnected from any other board");
    VL_Curs(19, 1);
    VL_Puts((uint8_t*)"ESC=exit  F1=Start");
    VL_SetForeColor(BLACK);

    VL_Curs(5, 1);
    VL_Puts((uint8_t*)"GPIO Test init...");
    GPIO_set_outputs( &g_gpio0, 0);                                         // Set all out pin ports to logic 0
    GPIO_set_outputs( &g_gpio1, 0);
    for (i = 0; i < GPIO0_NUM; i++)
        GPIO_config(&g_gpio0, gpio_map[i].num, GPIO_INPUT_MODE);            // Set all GPIO0 port pins as input (pull-up)
    for (i = 0; i < GPIO1_NUM; i++)
        GPIO_config(&g_gpio1, gpio_map[i+GPIO0_NUM].num, GPIO_INPUT_MODE);  // Set all GPIO1 port pins as input (pull-up)
    VL_Puts((uint8_t*)"OK");

    while (c != K_ESC)
    {
        c = 0;
        if (VL_IsKey())
        {
            c = VL_GetKey();
            if (c == K_F1)
            {
                pinerr = 255;        // No error
                VL_Curs(7,1);
                VL_Puts((uint8_t*)"                                      ");
                VL_Curs(8,1);
                VL_Puts((uint8_t*)"                                      ");
                VL_Curs(9,1);
                VL_Puts((uint8_t*)"                                      ");
                VL_Curs(7,1);
                VL_Puts((uint8_t*)"Check short circuits: ");
                for (i = 0; i < GPIO_NUM; i++)
                {
                    if (i < 32)
                        p = &g_gpio0;
                    else
                        p = &g_gpio1;
                    GPIO_config(p, gpio_map[i].num, GPIO_OUTPUT_MODE);      // Set pin as output
                    GPIO_set_output(p,gpio_map[i].num, 0);                  // Set pin logic state to zero
                    WaitMsec(20);                                           // A short delay..
                    gpio_inputs = GPIO_get_inputs(&g_gpio1);                // Read input pins
                    gpio_inputs <<= 32;
                    gpio_inputs |= GPIO_get_inputs(&g_gpio0);               // Read input pins
                    GPIO_config(p,gpio_map[i].num, GPIO_INPUT_MODE);        // Set pin as input

                    gpio_inputs |= PULL_DOWN_PINS_MASK;                     // Invalidate test from pins with pull-down resistor

                    pinmask = 0x01;                                         // Check if there are input pins to 0 (except the one set in output)
                    for (j = 0; j < GPIO_NUM; j++)
                    {
                        if ((i < 32 && (pinmask & gpio_map[i].mask) == 0) || ((i >=32 && ((pinmask>>32) & gpio_map[i].mask) == 0)))
                        {
                            if ((gpio_inputs & pinmask) == 0)
                            {
                                pinerr= j;              // Error
                                j = GPIO_NUM;           // Exit from check loop
                            }
                        }
                        pinmask <<= 1;
                    }
                    if (pinerr != 255)                                     // If error exit from test loop
                        break;
                }

                if (pinerr != 255)
                {
                    VL_Puts("ERROR");
                    VL_Curs(8,1);
                    sprintf(kk,"PINS  : %s-%s", gpio_map[i].name, gpio_map[pinerr].name);
                    VL_Puts((uint8_t*)kk);
                    VL_Curs(9,1);
                    sprintf(kk,"LABELS: %s-%s", gpio_map[i].label, gpio_map[pinerr].label);
                    VL_Puts((uint8_t*)kk);
                }
                else
                {
                    VL_Puts((uint8_t*)"OK");
                }
            }
         }
    }
    VL_Clear();
}


/**
  * @brief  Test LPDDR RAM
  * @param  None
  * @retval None
  */
void Test_LPDDR(void)
{
    uint8_t c=0, dat;
    uint16_t i;
    uint8_t *p, *q;
    uint16_t *wp;
    uint32_t *lp;

    VL_Clear();
    VL_SetForeColor(BLUE);
    VL_Curs(0, 1);
    VL_Puts((uint8_t*)"TEST LPDDR RAM");
    VL_Curs(19, 1);
    VL_Puts((uint8_t*)"ESC=exit F1=Test");
    VL_SetForeColor(BLACK);

    while (c != K_ESC)
    {
        c = 0;
        if (VL_IsKey())
        {
            c = VL_GetKey();
            if (c == K_F1)
            {
                VL_Curs(4, 1);
                VL_Puts((uint8_t*)"                                    ");
                VL_Curs(4, 1);
                VL_Puts((uint8_t*)"Test Write/Read pattern a..z :");
                p = (uint8_t*)LPDDR_BASE_ADDRESS+0x7FFF00;      // Write at the end of 8Mbyte memory space
                dat = 'a';
                for (i = 0; i < 26; i++)
                    *p++ = dat++;
                p = (uint8_t*)LPDDR_BASE_ADDRESS+0x7FFF00;
                dat = 'a';
                for (i = 0; i < 26; i++)
                {
                    sprintf((char*)kk,"%c\r\n",*p);
                    VL_SwPuts((uint8_t*)kk);
                    if (*p == dat)
                    {
                        p++;
                        dat++;
                    }
                    else
                        break;
                }
                VL_SwPuts("\r\n");
                if (i < 26)
                {
                    VL_SetForeColor(RED);
                    VL_Puts((uint8_t*)"ERROR");
                    VL_SetForeColor(BLACK);
                }
                else
                {
                    VL_Puts((uint8_t*)"PASSED");
                }

            }
        }
    }
    VL_SwClear();
    VL_Clear();
}


/**
  * @brief  Test VARIOUS and local I/O
  * @param  None
  * @retval None
  */

uint16_t design_ver;
uint8_t serial_number[16];
uint8_t mux = 0;

void Test_VARIOUS(void)
{
    uint8_t c=0, status, i, led = 0;
    uint32_t aaa;

    VL_Clear();
    VL_SetForeColor(BLUE);
    VL_Curs(0, 1);
    VL_Puts((uint8_t*)"TEST VARIOUS+I/O");
    VL_Curs(19, 1);
    VL_Puts((uint8_t*)"ESC=exit F1=LED F2=UART0_MUX");
    VL_SetForeColor(BLACK);

    MSS_SYS_init(MSS_SYS_NO_EVENT_HANDLER);

    /* Set USR_LED# as output */
    GPIO_config(&g_gpio0, USR_LED_N, GPIO_OUTPUT_MODE);
    USR_LED_OFF;
	/* Set USR_BTN# as input */
    GPIO_config(&g_gpio0, USR_BTN_N, GPIO_INPUT_MODE);

    VL_Curs(2, 1);
    VL_Puts((uint8_t*)"Design Ver: ");
    status = MSS_SYS_get_design_version ((uint8_t*)&design_ver);
    if (status == MSS_SYS_SUCCESS)
    {
        sprintf (kk," %02d", design_ver);
        VL_Puts((uint8_t*)kk);
    }
    else
    {
        sprintf (kk," ERROR %d", status);
        VL_Puts((uint8_t*)kk);
    }

    VL_Curs(3, 1);
    VL_Puts((uint8_t*)"S/N: ");
    status = MSS_SYS_get_serial_number ((uint8_t*)&serial_number);
    if (status == MSS_SYS_SUCCESS)
    {
        for (i = 0; i < 16; i++)
        {
            sprintf (kk,"%02X", serial_number[i]);
            VL_Puts((uint8_t*)kk);
        }
    }
    else
    {
        sprintf (kk," ERROR %d", status);
        VL_Puts((uint8_t*)kk);
    }

    VL_Curs(5, 1);
    VL_Puts((uint8_t*)"LED: OFF");
    VL_Curs(6, 1);
    VL_Puts((uint8_t*)"KEY: ");
    VL_Curs(7, 1);
    VL_Puts((uint8_t*)"UART0_MUX: ");
     while (c != K_ESC)
    {
        c = 0;
        if (VL_IsKey())
        {
            c = VL_GetKey();
            if (c == K_F1)
            {
                if (led == 0)
                {
                    led = 1;
                    USR_LED_ON;
                    VL_Curs(5, 6);
                    VL_Puts((uint8_t*)"ON ");
                }
                else
                {
                    led = 0;
                    USR_LED_OFF;
                    VL_Curs(5, 6);
                    VL_Puts((uint8_t*)"OFF");
                }
            }
            else if (c == K_F2)
            {
                if (mux == 0)
                {
                    mux = 1;
                    VL_Curs(7, 11);
                    VL_Puts((uint8_t*)"Switched to I/O");
                    WaitMsec(20);
                    UART0_MUX_IO;
                }
                else
                {
                    mux = 0;
                    VL_Curs(7, 11);
                    VL_Puts((uint8_t*)"Switched to USB");
                    WaitMsec(20);
                    UART0_MUX_USB;
                }
            }

        }
        if (isUSRBTNpressed())              // Raw check of USR_BTN# (without debounce)
        {
            VL_Curs(6, 6);
            VL_Puts((uint8_t*)"Pressed ");
        }
        else
        {
            VL_Curs(6, 6);
            VL_Puts((uint8_t*)"Released");
        }
    }
    USR_LED_OFF;
    VL_Clear();
}


/**
  * @brief  Test Ethernet
  * @param  None
  * @retval None
  */
uint32_t ip_addr, netmask_addr;
uint16_t dest_port;
struct ip_addr dest_ip;
IPstruct my_ip;

struct udp_pcb *udp0;
struct pbuf *pb;
uint8_t udp0TxBuf[24];
uint8_t udp0RxBuf[24];

void Test_ETH_UDP(void)
{
    uint8_t c=0, status, i, aa[8];
    uint8_t f1 = 0;
    uint8_t link_up = 0;
    uint8_t ip_received = 0;
    uint8_t fullduplex;
    mss_mac_speed_t speed;
    err_t ret;

    memset(udp0TxBuf,0x00,sizeof(udp0TxBuf));
    memset(udp0RxBuf,0x00,sizeof(udp0RxBuf));
    VL_Clear();
    VL_SetForeColor(BLUE);
    VL_Curs(0, 1);
    VL_Puts((uint8_t*)"TEST ETH");
    VL_Curs(19, 1);
    VL_Puts((uint8_t*)"ESC=exit F1=start");
    VL_SetForeColor(BLACK);

    /* Set USR_BTN# as input */  // NIK togliere
    GPIO_config(&g_gpio0, USR_BTN_N, GPIO_INPUT_MODE);

    ETH_RES_OFF;    // PHY exit from reset
    WaitMsec(50);

    while (c != K_ESC)
    {
        c = 0;
        if (VL_IsKey())
        {
            c = VL_GetKey();
            if (c == K_F1 && f1 == 0)
            {
                f1 = 1;
                VL_Curs(2,1);
                VL_Puts("IP Static? (y/n):");
                while (c != 'y' && c != 'Y' && c != 'n' && c != 'N')  {if (VL_IsKey()) c = VL_GetKey();}
                if (c == 'y' || c == 'Y')
                {
                   VL_Curs(2,1);
                   VL_Puts((uint8_t*)"LOCAL IP address     :    .   .   .   ");
                   for (i = 0; i < 4; i++)
                   {
                       VL_Curs(2,24+(i*4));
                       VL_GetString(3,kk);
                       my_ip.address[i] = atoi((const char*)kk);
                   }
                   VL_Curs(3,1);
                   VL_Puts((uint8_t*)"NETMASK              :    .   .   .   ");
                   for (i = 0; i < 4; i++)
                   {
                       VL_Curs(3,24+(i*4));
                       VL_GetString(3,kk);
                       my_ip.netmask[i] = atoi((const char*)kk);
                   }
                   VL_Curs(4,1);
                   VL_Puts((uint8_t*)"GATEWAY              :    .   .   .   ");
                   for (i = 0; i < 4; i++)
                   {
                       VL_Curs(4,24+(i*4));
                       VL_GetString(3,kk);
                       my_ip.gateway[i] = atoi((const char*)kk);
                   }
                   VL_Curs(2,1);
                   VL_Puts("                                      ");
                   VL_Curs(3,1);
                   VL_Puts("                                      ");
                   VL_Curs(4,1);
                   VL_Puts("                                      ");
                }
                else
                {
                   VL_Curs(2,1);
                   VL_Puts((uint8_t*)"Init ETH - DHCP...");
                   my_ip.address[0] = 0x00;
                }

                VL_Curs(4, 1);
                VL_Puts((uint8_t*)"Start Thread...");
                tcpip_init(ETHconfigureInterface, (void*) &my_ip);
                SetMsec(20000);
                while(ip_received == 0 && !isWaitEnd())
                {
                    link_up = MSS_MAC_get_link_status((mss_mac_speed_t *)&speed, (uint8_t *)&fullduplex);
                    if(link_up == 1)
                    {
                        ip_addr = get_ip_address();
                        if (ip_addr != 0)
                        {
                            ip_received  = 1;
                            my_ip.address[3] = ((uint16_t)((ip_addr >> 24u) & 0x000000FFu));
                            my_ip.address[2] = ((int)((ip_addr >> 16u) & 0x000000FFu));
                            my_ip.address[1] = ((int)((ip_addr >> 8u) & 0x000000FFu));
                            my_ip.address[0] = ((int)((ip_addr ) & 0x000000FFu));

                            netmask_addr = get_netmask();
                            my_ip.netmask[3] = ((uint16_t)((netmask_addr >> 24u) & 0x000000FFu));
                            my_ip.netmask[2] = ((int)((netmask_addr >> 16u) & 0x000000FFu));
                            my_ip.netmask[1] = ((int)((netmask_addr >> 8u) & 0x000000FFu));
                            my_ip.netmask[0] = ((int)((netmask_addr ) & 0x000000FFu));
                        }
                     }
                     vTaskDelay(500 / portTICK_RATE_MS);
                     VL_Curs(4,1);
                }

                if (isWaitEnd())
                {
                    VL_SetForeColor(RED);
                    VL_Puts((uint8_t*)"TIMEOUT");
                    VL_SetForeColor(BLACK);
                    WaitMsec(2000);
                    goto esci;
                }

                if      (speed == 0x00) VL_SwPuts("Speed: 10M\r\n");
                else if (speed == 0x01) VL_SwPuts("Speed: 100M\r\n");
                else if (speed == 0x02) VL_SwPuts("Speed: 1000M\r\n");
                else                    VL_SwPuts("Speed: Unknown\r\n");

                if      (fullduplex == 0x00) VL_SwPuts("Duplex: Half\r\n");
                else if (fullduplex == 0x01) VL_SwPuts("Duplex: Full\r\n");
                else                         VL_SwPuts("Duplex: Unknown\r\n");

                VL_Curs(5,1);
                sprintf((char*)kk,"IP address           : %03d.%03d.%03d.%03d",(uint8_t)my_ip.address[0],(uint8_t)my_ip.address[1],(uint8_t)my_ip.address[2],(uint8_t)my_ip.address[3]);
                VL_Puts((uint8_t*)kk);
                VL_Curs(6,1);
                sprintf((char*)kk,"NETMASK              : %03d.%03d.%03d.%03d",(uint8_t)my_ip.netmask[0],(uint8_t)my_ip.netmask[1],(uint8_t)my_ip.netmask[2],(uint8_t)my_ip.netmask[3]);
                VL_Puts((uint8_t*)kk);

                VL_Curs(7,1);
                dest_ip.addr = 0;
                dest_port = 0;
                VL_Puts((uint8_t*)"DEST. IP address     :    .   .   .   ");
                for (i = 0; i < 4; i++)
                {
                   VL_Curs(7,24+(i*4));
                   VL_GetString(3,kk);
                   aa[i] = atoi((const char*)kk);
                }
                IP4_ADDR(&dest_ip,aa[0],aa[1],aa[2],aa[3]);
                VL_Curs(8,1);
                VL_Puts((uint8_t*)"Dest Port            : ");
                dest_port = VL_GetWordValue(0);

                udp0 = udp_new();
                VL_Curs(9,1);
                if (udp0 == NULL)
                {
                   VL_SetForeColor(RED);
                   VL_Puts((uint8_t*)"Socket Creating Error");
                   VL_SetForeColor(BLACK);
                   WaitMsec(2000);
                   goto chiudi;
                }

                ret = udp_bind(udp0, (ip_addr_t*)&ip_addr, 3000);  // my port: 3000
                if (ret != ERR_OK)
                {
                   VL_SetForeColor(RED);
                   VL_Puts((uint8_t*)"Socket Binding Error");
                   VL_SetForeColor(BLACK);
                   WaitMsec(2000);
                   goto chiudi;
                }

                udp_recv(udp0, (udp_recv_fn)udp0RxCallback, NULL);
                ret = udp_connect(udp0, (ip_addr_t*)&dest_ip.addr, dest_port);
                if (ret != ERR_OK)
                {
                   VL_SetForeColor(RED);
                   VL_Puts((uint8_t*)"Socket Connect Error");
                   VL_SetForeColor(BLACK);
                   WaitMsec(2000);
                   goto chiudi;
                }

                VL_Puts((uint8_t*)"Ready");
                VL_Curs(19,29);
                VL_SetForeColor(BLUE);
                VL_Puts((uint8_t*)"F3=Send");
                VL_SetForeColor(BLACK);
                c = 0;
            }
            else if (c == K_F3 && (link_up == 1))
            {
                VL_Curs(10,1);
                VL_Puts((uint8_t*)"                                       ");
                VL_Curs(11,1);
                VL_Puts((uint8_t*)"                                       ");
                VL_Curs(10,1);
                VL_Puts((uint8_t*)"Tx (max.20 chars): ");
                VL_GetOptString(20,udp0TxBuf);
                pb = pbuf_alloc(PBUF_TRANSPORT, 32, PBUF_REF);
                pb->payload = udp0TxBuf;
                pb->len = pb->tot_len = strlen(udp0TxBuf);
                ret = udp_sendto(udp0, pb, (ip_addr_t*)&dest_ip.addr, dest_port);
                pbuf_free(pb);
                memset(udp0TxBuf,0x00,sizeof(udp0TxBuf));
                VL_Curs(11,1);
                if (ret != ERR_OK)
                {
                    VL_SetForeColor(RED);
                    sprintf((char*)kk,"Error %08lx",ret);
                    VL_Puts((uint8_t*)kk);
                    VL_SetForeColor(BLACK);
                }
                else
                {
                    VL_Puts((uint8_t*)"Send Ok");
                }
                c = 0;
             }
        }
        if (f1 == 1)
        {
            if (link_up == 1)
            {
                VL_Curs(9,1);
                VL_Puts((uint8_t*)"              ");
                if (udp0RxBuf[0] != 0x00)
                {
                    VL_Curs(13,1);
                    VL_Puts((uint8_t*)"                                       ");
                    VL_Curs(13,1);
                    VL_Puts((uint8_t*)"Rx data packet   : ");
                    VL_Puts((uint8_t*)udp0RxBuf);
                    memset(udp0RxBuf,0x00,sizeof(udp0RxBuf));
                }
            }
            else
            {
                VL_SetForeColor(RED);
                VL_Curs(9,1);
                VL_Puts((uint8_t*)"NOT CONNECTED ");
                VL_SetForeColor(BLACK);
            }
        }
        vTaskDelay(100 / portTICK_RATE_MS);
    }
chiudi:
    udp_disconnect(udp0);   // Remove the socket but Thread remains
    udp_remove(udp0);
esci:
    VL_SwClear();
    VL_Clear();
}


/**
  * @brief  UDP0 receive callback
  * @param  *arg =  User argument (udp_recv `arg` parameter)
  * @param  *upcb = Receiving Protocol Control Block
  * @param  *p =    Pointer to Datagram
  * @param  *addr = Address of sender
  * @param  port =  Sender port
  * @retval None
  */
void udp0RxCallback(void* arg, struct udp_pcb* upcb, struct pbuf* p, const ip_addr_t* addr, u16_t port)
{
    if (((uint32_t)(addr->addr) == dest_ip.addr) && (port == dest_port))  // Check Sender IP and port
    {
        memcpy(udp0RxBuf,p->payload,p->tot_len);
    }

    // Must free receive pbuf before return
    pbuf_free(p);
}


/**
  * @brief  Test QSPI Flash IS25LP256D on core QSPI
  * @param  None
  * @retval None
  */
uint8_t qspiTxBuf[256];
uint8_t qspiRxBuf[256];


void Test_QSPI(void)
{
    uint8_t c=0, status = 0, buf[8];
    uint16_t i, sect;
    uint32_t address;

    VL_Clear();
    VL_SetForeColor(BLUE);
    VL_Curs(0, 1);
    VL_Puts((uint8_t*)"TEST IS25LP256D (QSPI)");
    VL_Curs(18, 1);
     VL_Puts((uint8_t*)"F1=Wr1 F2=Wr2 F3=Rd F4=Erase");
     VL_Curs(19, 1);
    VL_Puts((uint8_t*)"ESC=exit F5=EraseAll");
    VL_SetForeColor(BLACK);

    VL_Curs(2, 1);
    VL_Puts((uint8_t*)"WARNING: QSPI flash Low level Test");

    VL_Curs(4, 1);
    VL_Puts((uint8_t*)"QSPI init...");
    QSPIFlash_init(CORE_QSPI_QUAD_FULL);
    if (status == 0)
    {
        VL_Puts((uint8_t*)"OK");
        QSPIFlash_read_status_regs(buf);
        sprintf(kk,"Status Reg   : %02X\r\n", buf[0]);
        VL_SwPuts(kk);
        sprintf(kk,"NV Cfg Reg   : %02X%02X\r\n", buf[1],buf[2]);
        VL_SwPuts(kk);
        sprintf(kk,"V  Cfg Reg   : %02X\r\n", buf[3]);
        VL_SwPuts(kk);
        sprintf(kk,"Enh V Cfg Reg: %02X\r\n", buf[4]);
        VL_SwPuts(kk);
        sprintf(kk,"Flag St Reg  : %02X\r\n", buf[5]);
        VL_SwPuts(kk);
    }
    else
    {
        VL_SetForeColor(RED);
        VL_Puts((uint8_t*)"ERROR");
        VL_SetForeColor(BLACK);
        WaitMsec(2000);
        goto esci;
    }

    VL_Curs(5, 1);
    VL_Puts((uint8_t*)"QSPI ID: ");
    memset(buf,0x00,sizeof(buf));
    QSPIFlash_readid(buf);
    sprintf (kk,"%02X %02X %02X %02X", buf[0], buf[1], buf[2], buf[3]);
    VL_Puts(kk);

    while (c != K_ESC)
    {
        c = 0;
        if (VL_IsKey())
        {
            c = VL_GetKey();
            if (c == K_F1)
            {
                VL_Curs(7, 1);
                VL_Puts((uint8_t*)"                             ");
                VL_Curs(8, 1);
                VL_Puts((uint8_t*)"                             ");
                VL_Curs(9, 1);
                VL_Puts((uint8_t*)"                             ");
                VL_Curs(7, 1);
                sprintf (kk,"Sect.num (%d..8191): ",QSPI_START_RAW_FLASH);
                VL_Puts((uint8_t*)kk);
                sect = VL_GetIntValue(0);
                if (sect > 8191 || sect < QSPI_START_RAW_FLASH) sect = QSPI_START_RAW_FLASH;
                address = sect * 4096;
                VL_Curs(8, 1);
                VL_Puts((uint8_t*)"Write pattern1...            ");
                memcpy(qspiTxBuf,(const uint8_t*)"1234567890",10);      // Write pattern1 to Tx Buffer
                memset(qspiRxBuf,0x00,sizeof(qspiRxBuf));               // Clear Rx Buffer
                status = QSPIFlash_program(qspiTxBuf, address, 10);
                VL_Curs(8, 19);
                if (status == IS25LP_STATUS_OK)
                    VL_Puts((uint8_t*)"OK");
                else
                {
                    VL_Puts((uint8_t*)"ERROR");
                    QSPIFlash_clr_flagstatusreg();
                }
            }
            else if (c == K_F2)
            {
                VL_Curs(7, 1);
                VL_Puts((uint8_t*)"                             ");
                VL_Curs(8, 1);
                VL_Puts((uint8_t*)"                             ");
                VL_Curs(9, 1);
                VL_Puts((uint8_t*)"                             ");
                VL_Curs(7, 1);
                sprintf (kk,"Sect.num (%d..8191): ",QSPI_START_RAW_FLASH);
                VL_Puts((uint8_t*)kk);
                sect = VL_GetIntValue(0);
                if (sect > 8191 || sect < QSPI_START_RAW_FLASH) sect = QSPI_START_RAW_FLASH;
                address = sect * 4096;
                VL_Curs(8, 1);
                VL_Puts((uint8_t*)"Write pattern2...            ");
                memcpy(qspiTxBuf,(const uint8_t*)"ABCDEFGHIL",10);      // Write pattern2 to Tx Buffer
                memset(qspiRxBuf,0x00,sizeof(qspiRxBuf));               // Clear Rx Buffer
                status = QSPIFlash_program(qspiTxBuf, address, 10);
                VL_Curs(8, 19);
                if (status == IS25LP_STATUS_OK)
                    VL_Puts((uint8_t*)"OK");
                else
                {
                    VL_Puts((uint8_t*)"ERROR");
                    QSPIFlash_clr_flagstatusreg();
                }
            }
            else if (c == K_F3)
            {
                VL_Curs(7, 1);
                VL_Puts((uint8_t*)"                             ");
                VL_Curs(8, 1);
                VL_Puts((uint8_t*)"                             ");
                VL_Curs(9, 1);
                VL_Puts((uint8_t*)"                             ");
                VL_Curs(7, 1);
                sprintf (kk,"Sect.num (%d..8191): ",QSPI_START_RAW_FLASH);
                VL_Puts((uint8_t*)kk);
                sect = VL_GetIntValue(0);
                if (sect > 8191 || sect < QSPI_START_RAW_FLASH) sect = QSPI_START_RAW_FLASH;
                address = sect * 4096;
                VL_Curs(8, 1);
                VL_Puts((uint8_t*)"Read...                      ");
                memset(qspiRxBuf,0x00,sizeof(qspiRxBuf));               // Clear Rx Buffer
                QSPIFlash_read(qspiRxBuf, address, 10);
                VL_Curs(8, 15);
                VL_Puts((uint8_t*)"OK");
                VL_Curs(9, 1);
                VL_Puts((uint8_t*)"Rx: ");
                for (i=0; i < 10; i++)
                {
                    sprintf (kk,"%C ", qspiRxBuf[i]);
                    VL_Puts(kk);
                }
            }
            else if (c == K_F4)
            {
                VL_Curs(7, 1);
                VL_Puts((uint8_t*)"                             ");
                VL_Curs(8, 1);
                VL_Puts((uint8_t*)"                             ");
                VL_Curs(9, 1);
                VL_Puts((uint8_t*)"                             ");
                VL_Curs(7, 1);
                sprintf (kk,"Sect.num (%d..8191): ",QSPI_START_RAW_FLASH);
                VL_Puts((uint8_t*)kk);
                sect = VL_GetIntValue(0);
                if (sect > 8191 || sect < QSPI_START_RAW_FLASH) sect = QSPI_START_RAW_FLASH;
                address = sect * 4096;
                VL_Curs(8, 1);
                VL_Puts((uint8_t*)"Erase QSPI Flash...          ");
                status = QSPIFlash_sector_erase(address/IS25LP_SECTOR_SIZE);
                VL_Curs(8, 19);
                if (status == IS25LP_STATUS_OK)
                    VL_Puts((uint8_t*)"OK");
                else
                {
                    VL_Puts((uint8_t*)"ERROR");
                    QSPIFlash_clr_flagstatusreg();
                }
            }
            else if (c == K_F5)
            {
                VL_Curs(7, 1);
                VL_Puts((uint8_t*)"                             ");
                VL_Curs(8, 1);
                VL_Puts((uint8_t*)"                             ");
                VL_Curs(9, 1);
                VL_Puts((uint8_t*)"                             ");
                VL_Curs(7, 1);
                VL_Puts((uint8_t*)"Are you sure? (Y/N) ");
                while (c != 'y' && c != 'Y' && c != 'n' && c != 'N')  {if (VL_IsKey()) c = VL_GetKey();}
                if (c == 'y' || c == 'Y')
                {
                    VL_Curs(8, 1);
                    VL_Puts((uint8_t*)"Bulk Erase QSPI Flash...      ");
                    status = QSPIFlash_erase();
                    VL_Curs(8, 24);
                    if (status == IS25LP_STATUS_OK)
                        VL_Puts((uint8_t*)"OK");
                    else
                    {
                        VL_Puts((uint8_t*)"ERROR");
                        QSPIFlash_clr_flagstatusreg();
                    }
                }
                else
                {
                    VL_Curs(7, 1);
                    VL_Puts((uint8_t*)"                             ");
                }
            }
         }
    }
esci:
    VL_SwClear();
    VL_Clear();
}


/**
  * @brief  Test FAT32 file system on QSPI Flash IS25LP256D
  * @param  None
  * @retval None
  */
FATFS  g_fat_media0;
FATFS *p_fat_media0;
static BYTE work[FF_MAX_SS];

void Test_FAT32(void)
{
    uint8_t i, c,aa[40],bb[40], filename[40], dat, retry;
    uint16_t cnt;
    uint32_t free_clust, free_sect, tot_sect, dir_attributes;
    UINT num;
    FIL fat_file;
    DIR fat_dir;
    FRESULT res;
    FILINFO fno;

    VL_Clear();
    VL_SetForeColor(BLUE);
    VL_Curs(0, 1);
    VL_Puts((uint8_t*)"[TEST QSPI FAT32]");
    VL_Curs(18, 1);
    VL_Puts((uint8_t*)"F1=Wr     F2=Rd     F3=Del  F4=ChgDir");
    VL_Curs(19, 1);
    VL_Puts((uint8_t*)"ESC=Exit  F5=NewDir F6=Dir  F7=Format");
    VL_SetForeColor(BLACK);

    VL_Curs(3, 1);
    VL_Puts((uint8_t*)"FAT32 Open.");
    retry = 2;
    while(retry)
    {
        VL_Puts((uint8_t*)".");
        /* Register working area */
        p_fat_media0 = &g_fat_media0;
        res = f_mount(p_fat_media0, "0:", 1);
        if(res != FR_OK)
        {
            retry--;
            WaitMsec(1000);
        }
        else
            break;
    }
    if(retry == 0)
    {
        VL_SetForeColor(RED);
        sprintf(kk, "ERROR %d", res);
        VL_Puts (kk);
        VL_SetForeColor(BLACK);
format:
        VL_Curs(4, 1);
        VL_Puts((uint8_t*)"                                     ");
        VL_Curs(4, 1);
        VL_Puts((uint8_t*)"FORMAT QSPI? (Y/N): ");
        while (c != 'y' && c != 'Y' && c != 'n' && c != 'N')  {if (VL_IsKey()) c = VL_GetKey();}
        VL_Curs(4, 1);
        VL_Puts((uint8_t*)"                      ");
        if (c == 'y' || c == 'Y')
        {
            VL_Curs(4, 1);
            VL_Puts((uint8_t*)"FORMAT  : ... ");
            res = f_mkfs("0:", 0, work, sizeof(work));
            if (res == FR_OK)
                VL_Puts((uint8_t*)"OK");
            else
            {
                VL_SetForeColor(RED);
                sprintf (kk,"ERROR %d", res);
                VL_SetForeColor(BLACK);
                VL_Puts(kk);
            }
            WaitMsec(2000);
            goto esci;
        }
    }
    VL_Puts((uint8_t*)"OK");

    /* Get the available usable space */
    res = f_getfree("0:", &free_clust, &p_fat_media0);
    if (res != FR_OK)
    {
        sprintf (kk,"GetFree() Error %d\r\n", res);
        VL_SwPuts(kk);
        WaitMsec(2000);
        goto end;
    }
    tot_sect = (p_fat_media0->n_fatent - 2) * p_fat_media0->csize;
    free_sect = free_clust * p_fat_media0->csize;
    VL_Curs(4, 1);
    sprintf((char*)kk,"Total: %lu sectors - Free: %lu", tot_sect, free_sect);
    VL_Puts((uint8_t*)kk);
    VL_Curs(4, 1);

    c = 0;
    while (c != K_ESC)
    {
        c = 0;
        if (VL_IsKey())
        {
            c = VL_GetKey();
            if (c == K_F1)
            {
                VL_Curs(7, 1);
                VL_Puts((uint8_t*)"                                  ");
                VL_Curs(8, 1);
                VL_Puts((uint8_t*)"                                  ");
                VL_Curs(9, 1);
                VL_Puts((uint8_t*)"                                  ");

                VL_Curs(7, 1);
                VL_Puts((uint8_t*)"WR FileName  : ");
                VL_GetString(13, aa);
                VL_Curs(8, 1);
                VL_Puts((uint8_t*)"WR: ");
                VL_GetString(30, bb);

                res = f_unlink (aa);                    // Delete file
                if (res != FR_OK && res != FR_NO_FILE)
                {
                    sprintf (kk,"Delete Error %d\r\n", res);
                    VL_SwPuts(kk);
                    WaitMsec(2000);
                    goto end;
                }

                res = f_open(&fat_file, aa, FA_WRITE | FA_OPEN_ALWAYS);   // Create file and open in write mode
                if (res != FR_OK)
                {
                    sprintf (kk,"Create Error %d\r\n", res);
                    VL_SwPuts(kk);
                    WaitMsec(2000);
                    goto end;
                }

                res = f_write(&fat_file, bb, strlen(bb), &num); // Write data to file..
                if (res != FR_OK || num < strlen(bb))
                {
                    sprintf (kk,"Write Error %d\r\n", res);
                    VL_SwPuts(kk);
                    f_close(&fat_file);
                    WaitMsec(2000);
                    goto end;
                }
                f_close(&fat_file);                             // Close File
                VL_Curs(9, 1);
                VL_Puts((uint8_t*)"Write OK");

            }
            else if (c == K_F2)
            {
                VL_Curs(7, 1);
                VL_Puts((uint8_t*)"                                  ");
                VL_Curs(8, 1);
                VL_Puts((uint8_t*)"                                  ");
                VL_Curs(9, 1);
                VL_Puts((uint8_t*)"                                  ");

                VL_Curs(7, 1);
                VL_Puts((uint8_t*)"RD File : ");
                VL_GetString(13, aa);
                VL_Curs(8, 1);
                VL_Puts((uint8_t*)"RD: ");

                res = f_open(&fat_file, aa, FA_READ);   // Open file in read mode
                if (res != FR_OK)
                {
                    sprintf (kk,"Open Error %d\r\n", res);
                    VL_SwPuts(kk);
                    WaitMsec(500);
                    VL_Curs(7, 1);
                    VL_Puts((uint8_t*)"                                  ");
                    VL_Curs(8, 1);
                    VL_Puts((uint8_t*)"                                  ");                }
                else
                {
                    res = f_read(&fat_file, bb, 30, &num);
                    if (res != FR_OK)
                    {
                        sprintf (kk,"Read Error %d\r\n", res);
                        VL_SwPuts(kk);
                        WaitMsec(500);
                        VL_Curs(7, 1);
                        VL_Puts((uint8_t*)"                                  ");
                        VL_Curs(8, 1);
                        VL_Puts((uint8_t*)"                                  ");
                    }
                    else
                    {
                        bb[num] = 0x00;         // Set ASCII string termination char
                        VL_Puts(bb);
                        VL_Curs(9, 1);
                        VL_Puts((uint8_t*)"Read OK");
                    }
                }
                f_close(&fat_file);                             // Close File
            }
            else if (c == K_F3)
            {
                VL_Curs(7, 1);
                VL_Puts((uint8_t*)"                                  ");
                VL_Curs(8, 1);
                VL_Puts((uint8_t*)"                                  ");
                VL_Curs(9, 1);
                VL_Puts((uint8_t*)"                                  ");

                VL_Curs(7, 1);
                VL_Puts((uint8_t*)"DEL FileName  : ");
                VL_GetString(13, aa);
                VL_Curs(8, 1);
                res = f_unlink (aa);                    // Delete file
                if (res != FR_OK)
                {
                    sprintf (kk,"Delete Error %d\r\n", res);
                    VL_SwPuts(kk);
                    WaitMsec(500);
                    VL_Curs(7, 1);
                    VL_Puts((uint8_t*)"                                  ");                }
                else
                {
                    VL_Puts((uint8_t*)"Delete OK");
                    f_close(&fat_file);                              // Close File
                }
            }
            else if (c == K_F4)
            {
               VL_Curs(7, 1);
               VL_Puts((uint8_t*)"                                  ");
               VL_Curs(8, 1);
               VL_Puts((uint8_t*)"                                  ");
               VL_Curs(9, 1);
               VL_Puts((uint8_t*)"                                  ");

               VL_Curs(7, 1);
               VL_Puts((uint8_t*)"Change DIR : ");
               VL_GetString(20, aa);


               res = f_chdir (aa);                          // Change Dir
               if (res != FR_OK)
               {
                   VL_SetForeColor(RED);
                   sprintf((char*)kk," ERROR (%ld)", res);
                   VL_Puts((uint8_t*)kk);
                   VL_SetForeColor(BLACK);
               }
               else
               {
                   VL_SetForeColor(GREEN);
                   sprintf((char*)kk," OK");
                   VL_Puts((uint8_t*)kk);
                   VL_SetForeColor(BLACK);
                   sprintf((char*)kk,"Change DIR: %s",aa);
                   VL_SwPuts(kk);
               }
               WaitMsec(1000);
               VL_Curs(7, 1);
               VL_Puts((uint8_t*)"                                 ");
               VL_Curs(8, 1);
               VL_Puts((uint8_t*)"                                 ");
            }
            else if (c == K_F5)
            {
               VL_Curs(7, 1);
               VL_Puts((uint8_t*)"                                  ");
               VL_Curs(8, 1);
               VL_Puts((uint8_t*)"                                  ");
               VL_Curs(9, 1);
               VL_Puts((uint8_t*)"                                  ");

               VL_Curs(7, 1);
               VL_Puts((uint8_t*)"New DIR : ");
               VL_GetString(20, aa);

               res = f_mkdir(aa);
               if (res != FR_OK)
               {
                   VL_SetForeColor(RED);
                   sprintf((char*)kk," ERROR (%ld)",res);
                   VL_Puts((uint8_t*)kk);
                   VL_SetForeColor(BLACK);
               }
               else
               {
                   VL_SetForeColor(GREEN);
                   sprintf((char*)kk," OK");
                   VL_Puts((uint8_t*)kk);
                   VL_SetForeColor(BLACK);
               }
               WaitMsec(1000);
               VL_Curs(7, 1);
               VL_Puts((uint8_t*)"                                 ");
               VL_Curs(8, 1);
               VL_Puts((uint8_t*)"                                 ");
            }
            else if (c == K_F6)
            {
                VL_Curs(7, 1);
                VL_Puts((uint8_t*)"                                  ");
                VL_Curs(8, 1);
                VL_Puts((uint8_t*)"                                  ");
                VL_Curs(9, 1);
                VL_Puts((uint8_t*)"                                  ");
                VL_SwClear();

                VL_Curs(7, 1);
                VL_Puts((uint8_t*)"DIR     : ...");
                VL_SwPuts((uint8_t*)"DIR     : ");

                res = f_opendir(&fat_dir, ".");
                while(1)
                {
                    res = f_readdir(&fat_dir, &fno);
                    if ((res != FR_OK) || (fno.fname[0] == 0x00))
                        break;
                    if (fno.fattrib & AM_DIR)
                    {
                        sprintf (kk,"<DIR> %s\r\n", fno.fname);
                        VL_SwPuts(kk);
                    }
                    else
                    {
                        sprintf (kk,"      %s\r\n", fno.fname);
                        VL_SwPuts(kk);
                    }
                }
                res = f_closedir(&fat_dir);
            }
            else if (c == K_F7)
                goto format;
        }
    }
end:
    /* Unregister working area */
     f_mount(0, "", 0);
esci:
    VL_SwClear();
    VL_Clear();
}


/**
  * @brief  Test LinkMd for Ethernet PHY
  * @param  None
  * @retval None
  *
  * @note   Useful link: https://microchip.my.site.com/s/article/How-to-test-the-4-differential-pairs-between-KSZ9031-Gigabit-Ethernet-PHY-and-RJ-45-connector-for-opens-and-shorts
  */
#include "phy.h"
struct netif test_EMAC_if;

void Test_LinkMD(void)
{
    uint8_t c=0, phy_addr;
    uint16_t phy_reg;

    VL_Clear();
    VL_SetForeColor(BLUE);
    VL_Curs(0, 1);
    VL_Puts((uint8_t*)"TEST LinkMD");
    VL_Curs(19, 1);
    VL_Puts((uint8_t*)"ESC=exit F1=Open F2=Short");
    VL_SetForeColor(BLACK);

    ETH_RES_ON;
    WaitMsec(50);
    ETH_RES_OFF;            // PHY exit from reset
    WaitMsec(50);
    phy_addr = 0x00;        // PHY address
    ethernetif_init(&test_EMAC_if);

    while (c != K_ESC)
    {
        c = 0;
        if (VL_IsKey())
        {
            c = VL_GetKey();
            if (c == K_F1)
            {
                VL_Curs(2, 1);
                VL_Puts((uint8_t*)"                                      ");
                VL_Curs(3, 1);
                VL_Puts((uint8_t*)"                                      ");
                VL_Curs(4, 1);
                VL_Puts((uint8_t*)"                                      ");
                VL_Curs(2, 1);
                VL_Puts((uint8_t*)"Test Open circuit (no cable)");
                VL_Curs(3, 1);
                VL_Puts((uint8_t*)"Disconnect cable and press a key...");
                VL_WaitKey();
                VL_Puts((uint8_t*)"RUN");
                VL_SwPuts("Test Open Circuit:\r\n");

                // PHY Reset
                MSS_MAC_phy_init(phy_addr);
                // Disable auto-negotiation and set speed to 1000Base-T mode
                MSS_MAC_write_phy_reg(phy_addr, MII_BMCR, 0x0140);
                // Disable auto MDI/MDI-X
                MSS_MAC_write_phy_reg(phy_addr, MII_NCONFIG, 0x0040);
                // Enable manual Master/Slave config. and select Slave mode
                MSS_MAC_write_phy_reg(phy_addr, MII_CTRL1000, 0x1000);

                // Test differential pair A
                MSS_MAC_write_phy_reg(phy_addr, MII_LINKMD, 0x8000);
                while(MSS_MAC_read_phy_reg(phy_addr, MII_LINKMD) & 0x8000);
                phy_reg = MSS_MAC_read_phy_reg(phy_addr, MII_LINKMD);

                VL_SwPuts("pair A: ");
                if ((phy_reg & 0x3300) == 0x0100)
                    VL_SwPuts("Normal. ");
                else
                    VL_SwPuts("Fault.  ");
                sprintf (kk," Len = %d\r\n", (phy_reg & 0x00FF));
                VL_SwPuts(kk);

                // Test differential pair B
                MSS_MAC_write_phy_reg(phy_addr, MII_LINKMD, 0x9000);
                while(MSS_MAC_read_phy_reg(phy_addr, MII_LINKMD) & 0x8000);
                phy_reg = MSS_MAC_read_phy_reg(phy_addr, MII_LINKMD);
                VL_SwPuts("pair B: ");
                if ((phy_reg & 0x3300) == 0x1100)
                    VL_SwPuts("Normal. ");
                else
                    VL_SwPuts("Fault.  ");
                sprintf (kk," Len = %d\r\n", (phy_reg & 0x00FF));
                VL_SwPuts(kk);

                // Test differential pair C
                MSS_MAC_write_phy_reg(phy_addr, MII_LINKMD, 0xA000);
                while(MSS_MAC_read_phy_reg(phy_addr, MII_LINKMD) & 0x8000);
                phy_reg = MSS_MAC_read_phy_reg(phy_addr, MII_LINKMD);
                VL_SwPuts("pair C: ");
                if ((phy_reg & 0x3300) == 0x2100)
                    VL_SwPuts("Normal. ");
                else
                    VL_SwPuts("Fault.  ");
                sprintf (kk," Len = %d\r\n", (phy_reg & 0x00FF));
                VL_SwPuts(kk);

                // Test differential pair D
                MSS_MAC_write_phy_reg(phy_addr, MII_LINKMD, 0xB000);
                while(MSS_MAC_read_phy_reg(phy_addr, MII_LINKMD) & 0x8000);
                phy_reg = MSS_MAC_read_phy_reg(phy_addr, MII_LINKMD);
                VL_SwPuts("pair D: ");
                if ((phy_reg & 0x3300) == 0x3100)
                    VL_SwPuts("Normal. ");
                else
                    VL_SwPuts("Fault.  ");
                sprintf (kk," Len = %d\r\n", (phy_reg & 0x00FF));
                VL_SwPuts(kk);

            }
            else if (c == K_F2)
            {
                VL_Curs(2, 1);
                VL_Puts((uint8_t*)"                                      ");
                VL_Curs(3, 1);
                VL_Puts((uint8_t*)"                                      ");
                VL_Curs(4, 1);
                VL_Puts((uint8_t*)"                                      ");
                VL_Curs(2, 1);
                VL_Puts((uint8_t*)"Test Short circuit");
                VL_Curs(3, 1);
                VL_Puts((uint8_t*)"Insert test Cable and press a key...");
                VL_WaitKey();
                VL_Puts((uint8_t*)"RUN");
                VL_SwPuts("Test Short Circuit:\r\n");

                // PHY Reset
                MSS_MAC_phy_init(phy_addr);
                // Disable auto-negotiation and set speed to 1000Base-T mode
                MSS_MAC_write_phy_reg(phy_addr, MII_BMCR, 0x0140);
                // Disable auto MDI/MDI-X
                MSS_MAC_write_phy_reg(phy_addr, MII_NCONFIG, 0x0040);
                // Enable manual Master/Slave config. and select Slave mode
                MSS_MAC_write_phy_reg(phy_addr, MII_CTRL1000, 0x1000);

                VL_Curs(4, 1);
                VL_Puts((uint8_t*)"Short pair A and press a key...");
                VL_WaitKey();
                // Test differential pair A
                MSS_MAC_write_phy_reg(phy_addr, MII_LINKMD, 0x8000);
                while(MSS_MAC_read_phy_reg(phy_addr, MII_LINKMD) & 0x8000);
                phy_reg = MSS_MAC_read_phy_reg(phy_addr, MII_LINKMD);

                VL_SwPuts("pair A: ");
                if ((phy_reg & 0x3300) == 0x0200)
                    VL_SwPuts("Normal. ");
                else
                    VL_SwPuts("Fault.  ");
                sprintf (kk," Len = %d\r\n", (phy_reg & 0x00FF));
                VL_SwPuts(kk);

                VL_Curs(4, 1);
                VL_Puts((uint8_t*)"Short pair B and press a key...");
                VL_WaitKey();
                // Test differential pair B
                MSS_MAC_write_phy_reg(phy_addr, MII_LINKMD, 0x9000);
                while(MSS_MAC_read_phy_reg(phy_addr, MII_LINKMD) & 0x8000);
                phy_reg = MSS_MAC_read_phy_reg(phy_addr, MII_LINKMD);
                VL_SwPuts("pair B: ");
                if ((phy_reg & 0x3300) == 0x1200)
                    VL_SwPuts("Normal. ");
                else
                    VL_SwPuts("Fault.  ");
                sprintf (kk," Len = %d\r\n", (phy_reg & 0x00FF));
                VL_SwPuts(kk);

                VL_Curs(4, 1);
                VL_Puts((uint8_t*)"Short pair C and press a key...");
                VL_WaitKey();
                // Test differential pair C
                MSS_MAC_write_phy_reg(phy_addr, MII_LINKMD, 0xA000);
                while(MSS_MAC_read_phy_reg(phy_addr, MII_LINKMD) & 0x8000);
                phy_reg = MSS_MAC_read_phy_reg(phy_addr, MII_LINKMD);
                VL_SwPuts("pair C: ");
                if ((phy_reg & 0x3300) == 0x2200)
                    VL_SwPuts("Normal. ");
                else
                    VL_SwPuts("Fault.  ");
                sprintf (kk," Len = %d\r\n", (phy_reg & 0x00FF));
                VL_SwPuts(kk);

                VL_Curs(4, 1);
                VL_Puts((uint8_t*)"Short pair D and press a key...");
                VL_WaitKey();
                // Test differential pair D
                MSS_MAC_write_phy_reg(phy_addr, MII_LINKMD, 0xB000);
                while(MSS_MAC_read_phy_reg(phy_addr, MII_LINKMD) & 0x8000);
                phy_reg = MSS_MAC_read_phy_reg(phy_addr, MII_LINKMD);
                VL_SwPuts("pair D: ");
                if ((phy_reg & 0x3300) == 0x3200)
                    VL_SwPuts("Normal. ");
                else
                    VL_SwPuts("Fault.  ");
                sprintf (kk," Len = %d\r\n", (phy_reg & 0x00FF));
                VL_SwPuts(kk);
            }
        }

        vTaskDelay(10 / portTICK_RATE_MS);
    }
    VL_SwClear();
    VL_Clear();
}


/**
  * @brief  converts from 2 char string to hexadecimal
  * @param  p = string to convert
  * @retval Converted byte value
  * @note   Invalid chars will be converted to zero
  * @note   i.e.:   "12" = 0x12
  * @note           "A4" = 0xA4
  * @note           "g5" = 0x05
*/
uint8_t StrToHex(uint8_t *p)
{
    uint8_t dat = 0;

    if (*p >= '0' && *p <= '9')
        dat = ((*p << 4) & 0xF0);
    if (*p == 'A' || *p == 'a')
        dat = 0xA0;
    else if (*p == 'B' || *p == 'b')
        dat = 0xB0;
    else if (*p == 'C' || *p == 'c')
        dat = 0xC0;
    else if (*p == 'D' || *p == 'd')
        dat = 0xD0;
    else if (*p == 'E' || *p == 'e')
        dat = 0xE0;
    else if (*p == 'F' || *p == 'f')
        dat = 0xF0;
    p++;
    if (*p >= '0' && *p <= '9')
        dat |= (*p & 0x0F);
    if (*p == 'A' || *p == 'a')
        dat |= 0x0A;
    else if (*p == 'B' || *p == 'b')
        dat |= 0x0B;
    else if (*p == 'C' || *p == 'c')
        dat |= 0x0C;
    else if (*p == 'D' || *p == 'd')
        dat |= 0x0D;
    else if (*p == 'E' || *p == 'e')
        dat |= 0x0E;
    else if (*p == 'F' || *p == 'f')
        dat |= 0x0F;
    return (dat);
}

/*EOF*/
