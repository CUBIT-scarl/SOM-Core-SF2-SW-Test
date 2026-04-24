/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : SmartFusion2 system startup
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
#include "usr_global.h"


/* Interrupt Handlers --------------------------------------------------------*/

/* Define Constants ----------------------------------------------------------*/

#define MAIN_THREAD_STACK_SIZE  2048 // ex 4096

/* Priorities used by the various different tasks. */
#define mainuIP_TASK_PRIORITY      (tskIDLE_PRIORITY + 2)


/* Define Variables ----------------------------------------------------------*/

gpio_instance_t g_gpio0, g_gpio1;

xTimerHandle xSysTickTimer;

volatile uint32_t tickCounter;
uint32_t tickCadenza;

// WARNING:
// Infoboot sector variables must be declared in the same way and same sequence
// as done in BOOT software to obtain the same absolute addressing:
// 0x20012000                BootBoard
// 0x2001200C                BootCode
// 0x2001201D                BootVer
// 0x2001201E                BootSw

uint8_t BootBoard[9] __attribute__((section(".infoboot1"))); // SOM Board Code
uint8_t BootCode[9]  __attribute__((section(".infoboot2"))); // BOOT SW Code
uint8_t BootVer[5]   __attribute__((section(".infoboot3"))); // BOTT version
uint8_t BootSw       __attribute__((section(".infoboot4"))); // Boot strategy parameter


/* Private functions ---------------------------------------------------------*/

void SysTickTimerCallback(xTimerHandle xTimer);


/* MAIN ----------------------------------------------------------------------*/

/* main function */
int main()
{
    /* Turn off the watchdog */
    SYSREG->WDOG_CR = 0;
    
    /* Initialise and Start SysTick Timer 10msec for bare-metal Sw implementations */
    //SysTick_Config(1000000);    // Ntick = Fclk * Cadenza = 100MHz * 10msec = 10^8 * 10^-2 = 10^6
    tickCadenza = 10;           // 10msec

    /* Initialise GPIO port 0 and 1 */
    GPIO_init(&g_gpio0, COREGPIO_BASE_ADDRESS0, GPIO_APB_32_BITS_BUS );
    GPIO_init(&g_gpio1, COREGPIO_BASE_ADDRESS1, GPIO_APB_32_BITS_BUS );

    /* Set output pins (default output value = 0)*/
    GPIO_config(&g_gpio0, USR_LED_N,   GPIO_OUTPUT_MODE);     // USR_LED on
    GPIO_config(&g_gpio0, ETH_RES_N,   GPIO_OUTPUT_MODE);
    GPIO_config(&g_gpio0, UART0_MUX,   GPIO_OUTPUT_MODE);
    GPIO_config(&g_gpio0, SOM_READY_N, GPIO_OUTPUT_MODE);

    /* Initialise MSS UART0 */
    UART0init(MSS_UART_115200_BAUD);

    xSysTickTimer = xTimerCreate("SysTickTimer", pdMS_TO_TICKS(tickCadenza), TRUE, 0, SysTickTimerCallback);
    xTimerStart(xSysTickTimer,0);

    /* Create main task. */
    xTaskCreate(USRmain, (signed char*) "USRmainTest", MAIN_THREAD_STACK_SIZE, NULL, mainuIP_TASK_PRIORITY, NULL );

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    /* Loop */
    while (1);
    return 0;
}


/* TickTimer Handler ---------------------------------------------------------*/

void SysTickTimerCallback(xTimerHandle xTimer)
{
    if (tickCounter > tickCadenza) tickCounter -= tickCadenza;
    else
        tickCounter = 0;
    CORE_QSPI_timer_expired(tickCadenza);
    QSPIFlash_timeout(tickCadenza);
    USRtickTimer(tickCadenza);
}


/* ---------------------------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
    /* Called if a call to pvPortMalloc() fails because there is insufficient
    free memory available in the FreeRTOS heap.  pvPortMalloc() is called
    internally by FreeRTOS API functions that create tasks, queues, software
    timers, and semaphores.  The size of the FreeRTOS heap is set by the
    configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
    for( ;; );
}

/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;

    /* Run time stack overflow checking is performed if
    configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected. */
    taskDISABLE_INTERRUPTS();
    for( ;; );
}

/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
    volatile size_t xFreeStackSpace;

    /* This function is called on each cycle of the idle task.  In this case it
    does nothing useful, other than report the amount of FreeRTOS heap that
    remains unallocated. */
    xFreeStackSpace = xPortGetFreeHeapSize();

    if( xFreeStackSpace > 100 )
    {
        /* By now, the kernel has allocated everything it is going to, so
        if there is a lot of heap remaining unallocated then
        the value of configTOTAL_HEAP_SIZE in FreeRTOSConfig.h can be
        reduced accordingly. */
    }
}

/*-----------------------------------------------------------*/

void vMainConfigureTimerForRunTimeStats( void )
{
    const unsigned long ulMax32BitValue = 0xffffffffUL;

    MSS_TIM64_init( MSS_TIMER_PERIODIC_MODE );
    MSS_TIM64_load_immediate( ulMax32BitValue, ulMax32BitValue );
    MSS_TIM64_start();
}

/*-----------------------------------------------------------*/

unsigned long ulGetRunTimeCounterValue( void )
{
    unsigned long long ullCurrentValue = 0u;
    const unsigned long long ulMax64BitValue = 0xffffffffffffffffULL;
    unsigned long *pulHighWord, *pulLowWord;

    pulHighWord = ( unsigned long * ) &ullCurrentValue;
    pulLowWord = pulHighWord++;

    MSS_TIM64_get_current_value( ( uint32_t * ) pulHighWord, ( uint32_t * ) pulLowWord );

    //Convert the down count into an upcount.
    ullCurrentValue = ulMax64BitValue - ullCurrentValue;

    //  Scale to a 32bit number of suitable frequency.
    ullCurrentValue >>= 13;

    // Just return 32 bits.
    return ( unsigned long ) ullCurrentValue;
}

/*EOF*/


