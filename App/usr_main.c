/**
  ******************************************************************************
  * @file           : usr_main.c
  * @brief          : User program body
  * @note           : Project code 82037801
  *
  * vers. 0.01  Preliminary version
  * 08/05/25
  *
  * vers. 0.05  First version. All peripherals running.
  * 27/06/25
  *
  * vers. 0.06  Renamed phy .c file, optimisation in Test_ETH(), Test_LinkMD(),
  * 01/08/25    is25lp256d.h. New test menu.
  *
  * vers. 0.07  Run and debug application software in NVM or External RAM depending
  * 01/09/25    on .ld files and debugger parameters. Added ram section '.lpddrram_gp0'
  *             mapped in the last 8M of 64M LPDDR for general purpose use.
  *             Changed SPF flash sst26vf016.c with w25q64jvzpiq.c
  *             Added test for Fabric AutoUpdate and Golden Image.
  *
  * vers. 0.08  Bug fixing in Ethernet UDP test.
  * 27/11/25
  *
  * vers. 0.09  Update FreeRTOS to 10.2.1
  * 29/05/26
  *
  * Flash memory map:
  * Total NVM       0x00000000..0x0003FFFF      256KB
  * Boot            0x00000000..0x00007BFF       31KB
  * Boot Params     0x00007C00..0x00007FFF        1KB
  * App. Program    0x00080000..0x0003FFFF      224KB
  *
  * SRAM memory map:
  * User ESRAM      0x20000000..0x2000FFFF       64KB
  * Recycled ESRAM0 0x20010000..0x20011FFF        8KB (no init)
  * Recycled ESRAM1 0x20012000..0x20012FFF        8KB (no init)
  *
  * Reserved locations in ESRAM1 for Bootloader:
  * BootBoard       0x20012000
  * BootCode        0x2001200C
  * BootVer         0x20012018
  * BootSw          0x2001201D
  *
  * sSoftCode[9] Application Program Code
  * sSoftVer[5]  Application Program Version
  *
  * Use of the Perspectives:
  *
  * Debug           Software Debug in NVW without Bootloader:
  *                  Select debug-in-microsemi-smartfusion2-envm-NOBOOT.ld
  *                  Build in Debug mode and start Debugger
  *
  *                 Software Debug in EXTFLASH (with NVM Bootloader installed):
  *                  Select production-in-microsemi-smartfusion2-external-ram-BOOT.ld
  *                  Go to menu 'Debug Configuration...'
  *                  Go To 'Startup'
  *                  Disable 'Load Executable' option
  *                  In the Project Properties menu select Cross ARM GNU Create File Image - General
  *                  Select 'Output file format' as Raw Binary
  *                  load .bin image with CubitFlashProgrammer.exe
  *                  start Debugger
  *                  press Resume (Play/F8) two or three times to enter in the Application main program
  *
  * Release         Application software in NVM (with NVM Bootloader installed):
  *                  Select production-in-microsemi-smartfusion2-envm-BOOT.ld
  *                  Build in Release mode and load .bin image with CubitFlashProgrammer.exe
  *
  *                 Application software executed from EXTRAM (with NVM Bootloader installed):
  *                  Select production-in-microsemi-smartfusion2-external-ram-BOOT.ld
  *                  Build in Release mode and load .bin image with CubitFlashProgrammer.exe
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

extern uint8_t BootBoard[9] __attribute__((section(".infoboot1"))); // SOM Board Code
extern uint8_t BootCode[9]  __attribute__((section(".infoboot2"))); // BOOT SW Code
extern uint8_t BootVer[5]   __attribute__((section(".infoboot3"))); // BOOT version


/* Define Constants --------------------------------------------------------- */

const char SoftCode[9] = {"82037801"};				// Program code
const char SoftVer[5]  = {"0.09"};					// Program Version


/* Define Global variables -------------------------------------------------- */

uint8_t kk[41];             // Global generic Buffer typically used for 'sprintf' on virtualLCD


/* User Program Callbacks ----------------------------------------------------*/

/**
  * @brief  sysTickTimer User Callback
  * @param  t = tick timer period [msec]
  * @retval None
  */
void USRtickTimer (uint32_t t)
{
    VL_timer_expired(t);
}


/**
  * @brief  Uart0 Rx Interrupt Callback
  * @param  dat = received data
  * @retval None
  */

/* Uart0 Rx interrupt */

void USRuart0Rx(uint8_t dat)
{
	VL_Rx(dat);     // VirtualLCD Rx callback
}


/* User Program ------------------------------------------------------------- */

/**
  * @brief  Manual Test program
  * @param  None
  * @retval None
  */
uint8_t dato;

void USRmain(void *pvParameter)
{
    uint8_t c;

    UART0init(MSS_UART_115200_BAUD);
    UART0startRx();

    VL_Init ();
    BootBoard[8] = 0x00;
    BootCode[8]  = 0x00;
    BootVer[4]   = 0x00;

/* Main program */
    while (1)
    {
        VL_Clear();                                 // Clear text display
        VL_SwClear();                               // Clear scroll display
        VL_ClearGraph();                            // Clear graphic area
        VL_DisableCurs();

        VL_Curs(0,7);                               // First screen
        VL_SetForeColor(BLUE);
        VL_Puts((uint8_t*)"## FPGA Manual Test ##");
        VL_SetForeColor(BLACK);

        VL_Curs(2,1);
        VL_Puts((uint8_t*)"Board   : ");
        VL_Puts((uint8_t*)BootBoard);
        VL_Curs(3,1);
        VL_Puts((uint8_t*)"Boot    : ");
        VL_Puts((uint8_t*)BootCode);
        VL_Puts((uint8_t*)" ");
        VL_Puts((uint8_t*)BootVer);
        VL_Curs(4,1);
        VL_Puts((uint8_t*)"Test    : ");
        VL_Puts((uint8_t*)SoftCode);
        VL_Puts((uint8_t*)" ");
        VL_Puts((uint8_t*)SoftVer);

        VL_Curs(19,1);
        VL_Puts((uint8_t*)"Press a key...");
        VL_WaitKey();

        while(1)
        {
            VL_Clear();                                // Main Menu
            VL_DisableCurs();
            VL_Curs(0,14);
            VL_Puts((uint8_t*)"TEST MENU");
            VL_Curs(2,1);
            VL_Puts((uint8_t*)" 1. RESET          2. GPIO        ");
            VL_Curs(3,1);
            VL_Puts((uint8_t*)" 3. SPIFLASH       4. AutoUPD     ");
            VL_Curs(4,1);
            VL_Puts((uint8_t*)" 5. LPDDR          6. VARIOUS     ");
            VL_Curs(5,1);
            VL_Puts((uint8_t*)" 7. QSPI           8. QSPI FAT32  ");
            VL_Curs(6,1);
            VL_Puts((uint8_t*)" 9. ETH LinkMD     A. ETH UDP     ");

            c = VL_WaitKey();
            VL_Clear();
            switch (c)
            {
            	case '1':
            	    Test_RESET();
                   break;

               case '2':
                   Test_GPIO();
                   break;

               case '3':
                   Test_SPI0();
                   break;

               case '4':
                   Test_AutoUPD();
                   break;

               case '5':
                   Test_LPDDR();
                   break;

               case '6':
                   Test_VARIOUS();
                   break;

               case '7':
                   Test_QSPI();
                   break;

               case '8':
                   Test_FAT32();
                   break;

               case '9':
                   Test_LinkMD();
                   break;

               case 'a':
               case 'A':
                   Test_ETH_UDP();
                   break;

               default:
                   break;
            }
        }
    }
}

/*EOF*/
