/**
  ******************************************************************************
  * @file           : core_qspi.c
  * @brief          : core QSPI driver.
  * @note           : Project code 82037801
  *
  * @note   call CORE_QSPI_timer_expired() into the SysTickTimerCallback() service routine
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

/* Define Constants --------------------------------------------------------- */

/* Define Local variables --------------------------------------------------- */

static volatile uint32_t g_irq_rd_byte_size = 0u;
static void * g_rd_buffer;
static volatile core_qspi_status_handler_t g_handler;
static volatile uint32_t qspiTout;


/* Local Functions ---------------------------------------------------------- */

static void default_status_hanlder(uint32_t value);


/* Functions ---------------------------------------------------------------- */

/**
 * @brief   CORE_QSPI_init() function initializes and enables the CORE QSPI.
 * @param   None
 * @return  None
*/
void CORE_QSPI_init(void)
{
    g_handler = default_status_hanlder;

    QSPI->CONTROL = CTRL_EN_MASK |
                    CTRL_SAMPLE_SCK |
                    (0x1u << CTRL_CLKRATE) | CTRL_CLKIDL_MASK ;

    QSPI->INTENABLE = 0x0u;
}


/**
 * @brief   CORE_QSPI_configure() function configures the CORE QSPI to desired
 *          configuration values.
 * @param   config = config parameter is a pointer to the core_qspi_config_t structure,
 *          which provides new configuration values. See the core_qspi_config_t
 *          section for details.
 * @return  None
 */
void CORE_QSPI_configure(const core_qspi_config_t* config)
{
    QSPI->CONTROL = (uint32_t)(config->sample << CTRL_SAMPLE)    |
                    (uint32_t)(config->io_format << CTRL_QMODE0) |
                    (uint32_t)(config->clk_div << CTRL_CLKRATE)  |
                    (uint32_t)(config->xip << CTRL_XIP)          |
                    (uint32_t)(config->xip_addr << CTRL_XIPADDR) |
                    (uint32_t)(config->spi_mode << CTRL_CLKIDL)  |
                    CTRL_EN_MASK;
}


/**
 * @brief   CORE_QSPI_get_config() function reads-back the current configurations of
 *          the CORE QSPI. This function can be used when you want to read the
 *          current configurations, modify the configuration values of your choice
 *          and reconfigure the CORE QSPI hardware, using CORE_QSPI_configure() function.
 * @param   config = The config parameter is a pointer to an core_qspi_config_t
 *          structure in which the current configuration values of the CORE QSPI
 *          are returned.See description of core_qspi_config_t for more details.
 * @return  None
  */
void CORE_QSPI_get_config(core_qspi_config_t* config)
{
   volatile uint32_t reg =0;

   reg = QSPI->CONTROL;

   config->spi_mode = ((reg & CTRL_CLKIDL_MASK) >> CTRL_CLKIDL);

   config->clk_div = (core_qspi_clk_div)((reg & CTRL_CLKRATE_MASK)
                                                               >> CTRL_CLKRATE);
   config->xip = (uint8_t)((reg & CTRL_XIP_MASK) >> CTRL_XIP);
   config->xip_addr = (uint8_t)((reg & CTRL_XIPADDR_MASK) >> CTRL_XIPADDR);
   config->sample = (uint8_t)((reg & CTRL_SAMPLE_MASK) >> CTRL_SAMPLE);

   reg = reg & (uint32_t )((uint32_t )CTRL_QMODE12_MASK | (uint32_t )CTRL_QMODE0_MASK);
   reg = reg >> CTRL_QMODE0;

   config->io_format = (core_qspi_io_format)reg;
}


/**
 * @brief   CORE_QSPI_polled_transfer_block() function is used to carry out a QSPI
 *          transfer with the target memory device using polling method of data transfer.
 *          The QSPI transfer characteristics are configured every time a new transfer
 *          is initiated. This is a blocking function.
 * @param   num_addr_bytes = indicates the number of address bytes to be
 *          used while transacting with the target memory device. Depending on the
 *          target memory device, the address within the target memory device can be
 *          either 3 or 4 bytes long. You must make sure that you provide the exact same
 *          number with which the target memory device is configured.
 *
 *   Note: Few command opcodes do not require specified addresses. For example
 *   READ_ID. For such commands the num_addr_bytes parameter must be set to 0x0.
 *
 * @param   target_mem_addr = memory address in the target memory device on which
 *          the read/write operation is to be carried out.
 * @param   tx_buffer =  pointer to the buffer from which the data needs to transmitted
 *          to the target memory device.
 * @param   tx_byte_size= exact number of bytes that needs to be transmitted to
 *          the target memory device.
 *
 *   Note: This parameter must not consider the command opcode and address bytes
 *   as part of the data that needs to be transmitted.
 *
 * @param   rd_buffer = pointer to the buffer where the data returned by the
 *          target memory device is to be stored.
 * @param   rd_byte_size =  exact number of bytes that needs to be received from
 *          the target memory device.
 * @param   num_idle_cycles =  number of Idle cycles/dummy clock  edges that
 *          must be generated after the address bytes are transmitted and
 *          before target memory device starts sending data. This must be correctly
 *          set based on the target memory device and the SPI command being used
 *          – this may also vary based on SPI clock and the way the target memory
 *          device is configured.
 * @return  nONE
  */
void CORE_QSPI_polled_transfer_block(uint8_t num_addr_bytes, const void * const tx_buffer,
                                    uint32_t tx_byte_size,  const void * const rd_buffer,
                                    uint32_t rd_byte_size, uint8_t num_idle_cycles)
{
    uint32_t idx;
    uint8_t* buf8 = (uint8_t*)tx_buffer;
    uint32_t* buf32 = (uint32_t*)tx_buffer;
    volatile uint32_t skips;
    uint32_t cbytes;
    uint32_t total_byte_cnt;
    uint32_t words = 0u;

    cbytes = 1u + tx_byte_size + num_addr_bytes;
    total_byte_cnt = 1u + tx_byte_size + num_addr_bytes + rd_byte_size;

    QSPI->INTENABLE = 0u;

    while ((QSPI->STATUS & STTS_READY_MASK) == 0u){};

    /*bit16 to 31 define the number of Upper bytes when count is >65535
    Write to lower 16 bit is ignored*/
    QSPI->FRAMESUP = total_byte_cnt & FRMS_UBYTES_MASK;

    num_idle_cycles = (num_idle_cycles << 3u);

    skips  = (total_byte_cnt & 0x0000FFFFu);
    skips |= (cbytes << FRMS_CBYTES);
    skips |= (((QSPI->CONTROL & CTRL_QMODE12_MASK)? 1u:0u) << FRMS_QSPI);
    skips |= ((uint32_t)num_idle_cycles) << 23u;
    skips |= FRMS_FWORD_MASK;

    QSPI->FRAMES = (uint32_t)skips;

    QSPI->CONTROL |= CTRL_FLAGSX4_MASK;

    words = cbytes / (uint32_t)4u;

    for (idx = 0u; idx < words; ++idx)
    {
        while (QSPI->STATUS & STTS_TFFULL_MASK){};

        QSPI->TXDATAX4 = (uint32_t)buf32[idx];
    }

    QSPI->CONTROL &= ~CTRL_FLAGSX4_MASK;

    /*
     * This delay is needed only for the EXT_RO and EXT_RW modes
     * with out this delay the TXDATAX1 FIFO is not getting updated
     * with proper data.
     * Ex: if the bytes to send are 267 then the last 3 bytes that
     * are getting written into the TXDATAX1 FIFO are not properly
     * written.
     * Where as this delay is not needed for other modes like NORMAL,
     * FULL_QUAD/FULL_DUAL.
     */
    //CORE_QSPI_wait_msec(20);
    for (idx = (cbytes - (cbytes % 4u)); idx < cbytes; ++idx)
    {
        while (QSPI->STATUS & STTS_TFFULL_MASK){};

        QSPI->TXDATAX1 = (uint8_t)buf8[idx];
    }

    buf32 = (uint32_t*)rd_buffer;
    buf8 = (uint8_t*)rd_buffer;

    if (rd_byte_size)
    {
        words = rd_byte_size / 4u;

        QSPI->CONTROL |= CTRL_FLAGSX4_MASK;

        for (idx = 0u; idx < words; ++idx)
        {
            while (QSPI->STATUS & STTS_RFEMPTY_MASK){};
            buf32[idx] = QSPI->RXDATAX4;
        }

        QSPI->CONTROL &= ~CTRL_FLAGSX4_MASK;

        for (idx = (rd_byte_size - (rd_byte_size % 4u));
                                                      idx < rd_byte_size; ++idx)
        {
            while (QSPI->STATUS & STTS_RFEMPTY_MASK){};
            buf8[idx] = QSPI->RXDATAX1;
        }

        while (0u == (QSPI->STATUS & STTS_RDONE_MASK))
        {
            skips = (uint64_t)((QSPI->STATUS & STTS_FLAGSX4_MASK) ?
                                               QSPI->RXDATAX4 : QSPI->RXDATAX1);
        }
     }
}


/**
 * @brief   CORE_QSPI_irq_transfer_block() function is used to carry out a QSPI transfer
 *          with the target memory device using interrupt method of data transfers.
 *          The QSPI transfer characteristics are configured every time a new transfer is
 *          initiated. This is non-blocking function. You must configure the interrupt
 *          handler function, before calling this function.It will enable the interrupts
 *          and start transmitting as many bytes as requested. You will get an indication
 *          when the actual SPI transmit operation is complete when The transmit-done
 *          interrupt event occurs and this driver calls-back the interrupt handler
 *          function that you previously provided. If the transfer includes receiving
 *          data from the target memory device then the receive-available and receive-done
 *          interrupts are also enabled by this function. The data will be received in the
 *          interrupt routine. The interrupt handler provided by you will be called-back
 *          again when the receive-done interrupt event occurs.
 *
 * @param   num_addr_bytes = indicates the number of address bytes to be
 *          used while transacting with the target memory device. Depending on the the
 *          target memory device, the address within the target memory device can be
 *          either 3 or 4 bytes long.  You must make sure that you provide the exact
 *          same number with which the target memory device is configured.
 *
 *   Note: There will be some command opcodes for which no address needs to be
 *   specified. e.g. READ_ID. For such commands the num_addr_bytes parameter
 *   must be set to 0x0.
 *
 * @param   target_mem_addr =  memory address in the target memory device on which
 *          the read/write operation is to be carried out.
 * @param   tx_buffer =  pointer to the buffer from which the data  needs to transmitted
 *          to the target QSPI memory.
 * @param   tx_byte_size =  exact number of bytes that needs to be transmitted to
 *          target memory device.
 *
 *   Note: This parameter must not consider the command opcode and address bytes
 *   as part of the data that needs to be transmitted.
 *
 * @param   rd_buffer = pointer to the buffer where the data returned
 *          by the target memory device is to be stored. This must be correctly set
 *          based on the transfer i.e. for the status, readid and other configuration
 *          read commands this must be set and for the configuration write commands
 *          this will be NULL.
 * @param   rd_byte_size = exact number of bytes that needs to be received from
 *          the target memory device.
 * @param   num_idle_cycles = indicates the The number of IDLE/dummy clock
 *          edges that must be generated after the address bytes are transmitted and
 *          before target memory device starts sending data. This must be correctly set
 *          based on the target memory device and the SPI command being used – this may
 *          also vary based on SPI clock and the way the target memory device is
 *          configured.
 * @return  None
 */
uint8_t CORE_QSPI_irq_transfer_block(uint8_t num_addr_bytes, const void * const tx_buffer,
                                    uint32_t tx_byte_size, const void * const rd_buffer,
                                    uint32_t rd_byte_size, uint8_t num_idle_cycles)
{
    uint32_t idx;
    uint32_t cbytes;
    uint32_t total_byte_cnt;
    const uint8_t* buf8 = tx_buffer;
    const uint32_t* buf32 = tx_buffer;
    volatile uint32_t skips = 0;
    uint8_t returnval = 0u;
    uint32_t words = 0u;
    uint32_t enable = 0u;

    g_rd_buffer = (uint32_t*)rd_buffer;
    cbytes = 1u + tx_byte_size + num_addr_bytes;
    total_byte_cnt = 1u + tx_byte_size + num_addr_bytes + rd_byte_size;
    while ((QSPI->STATUS & STTS_READY_MASK) == 0u){};

    enable = INTE_TDONE_MASK;
    /*bit16 to 31 define the number of Upper bytes when count is >65535
     Write to lower 16 bit is ignored*/
    QSPI->FRAMESUP = total_byte_cnt & FRMS_UBYTES_MASK;
    skips  = (total_byte_cnt & 0x0000FFFFu);
    skips |= (cbytes << FRMS_CBYTES);
    skips |= (((QSPI->CONTROL & CTRL_QMODE12_MASK)? 1u:0u) << FRMS_QSPI);
    skips |= ((uint32_t)num_idle_cycles) << 26u;

    if (rd_buffer)
    {
        skips |= FRMS_FBYTE_MASK;
        QSPI->FRAMES = skips;
        QSPI->CONTROL &= ~CTRL_FLAGSX4_MASK;
        for (idx = 0u; idx < cbytes; ++idx)
        {
             while (QSPI->STATUS & STTS_TFFULL_MASK){};
             QSPI->TXDATAX1 = (uint8_t)buf8[idx];
        }

    }
    else
    {
        skips |= FRMS_FWORD_MASK;
        QSPI->FRAMES = skips;
        QSPI->CONTROL |= CTRL_FLAGSX4_MASK;
        words = cbytes / (uint32_t)4u;
        for (idx = 0u; idx < words; ++idx)
        {
            while (QSPI->STATUS & STTS_TFFULL_MASK){};
            QSPI->TXDATAX4 = (uint32_t)buf32[idx];
        }
        QSPI->CONTROL &= ~CTRL_FLAGSX4_MASK;

        /*
         * This delay is needed only for the EXT_RO and EXT_RW modes
         * with out this delay the TXDATAX1 FIFO is not getting updated
         * with proper data.
         * Ex: if the bytes to send are 267 then the last 3 bytes that
         * are getting written into the TXDATAX1 FIFO are not properly
         * written.
         * Where as this delay is not needed for other modes like SPI,
         * FULL_QUAD/FULL_DUAL.
         */
        CORE_QSPI_wait_msec(20);
        for (idx = (cbytes - (cbytes % 4u)); idx < cbytes; ++idx)
        {
            while (QSPI->STATUS & STTS_TFFULL_MASK){};
            QSPI->TXDATAX1 = (uint8_t)buf8[idx];
        }
    }

    if (rd_byte_size)
    {
        g_irq_rd_byte_size = rd_byte_size;
        enable |= (uint32_t )(INTE_RDONE_MASK | INTE_RAVLB_MASK);
    }

    QSPI->INTENABLE = enable;

    /*
     * This delay is needed to get proper data into the RXFIFOs
     * With out this delay, once the RX_AVAILABLE bit is set
     * the data available in RXFIFO is incorrect.
     */
    if (rd_byte_size != 0)
        CORE_QSPI_wait_msec(20);

    return 0;
}


/**
 * @brief   CORE_QSPI_set_status_handler() function registers an interrupt handler
 *          function with this driver which is used to indicate the interrupt status back
 *          to the application. This status handler function is called by this driver in
 *          two events. First, when the transmission of required bytes is completed
 *          (Transmit-Done). Second, if data is to be received from the target memory
 *          device then this function is called again when required data is received
 *          (Receive-Done).
 * @param   handler = interrupt handler function of the type core_qspi_status_handler_t
 *          which needs to be registered.
 * @return  None
 */
void CORE_QSPI_set_status_handler(core_qspi_status_handler_t handler)
{
    if ((core_qspi_status_handler_t)0 != handler)
    {
        g_handler = handler;
    }
}


static void qspi_isr(void)
{
    uint32_t idx;
    static uint32_t empty = 0u;
    static uint32_t tx_fifo_full = 0u;
    uint32_t status = 0;
    uint32_t skips = 0;

    status = QSPI->STATUS;

    if (STTS_TDONE_MASK == (uint32_t)(status & STTS_TDONE_MASK))
    {
        g_handler(STTS_TDONE_MASK);
        QSPI->STATUS |= STTS_TDONE_MASK;
    }

    if (STTS_RAVLB_MASK == (uint32_t)(status & STTS_RAVLB_MASK))
    {
        QSPI->STATUS |= STTS_RAVLB_MASK;
        uint8_t* buf8 = g_rd_buffer;
        uint32_t* buf32 = g_rd_buffer;
        uint32_t words = 0u;

        if (g_irq_rd_byte_size >= 4)
        {
           words = g_irq_rd_byte_size / 4u;
           QSPI->CONTROL |= CTRL_FLAGSX4_MASK;

           for (idx = 0u; idx < words; ++idx)
           {
               while (QSPI->STATUS & STTS_RFEMPTY_MASK){};
               buf32[idx] = QSPI->RXDATAX4;
           }
        }

        QSPI->CONTROL &= ~CTRL_FLAGSX4_MASK;
        for (idx = (g_irq_rd_byte_size - (g_irq_rd_byte_size % 4u));
                                        idx < g_irq_rd_byte_size; ++idx)
        {
           while (QSPI->STATUS & STTS_RFEMPTY_MASK){};
           buf8[idx] = QSPI->RXDATAX1;
        }
    }

    if (STTS_RDONE_MASK == (uint32_t)(status & STTS_RDONE_MASK))
    {
        /*This means receive transfer is now complete. invoke the callback
         * function*/
        g_handler(STTS_RDONE_MASK);
        /*disable RXDONE, RXEMPTY, RXAVLBL interrupt*/
        QSPI->INTENABLE &= ~(INTE_RDONE_MASK | INTE_RAVLB_MASK);
        QSPI->STATUS |= STTS_RDONE_MASK;
    }
}


/** QSPI interrupt default handler function */
static void default_status_hanlder(uint32_t value)
{
    /*Take some default interrupt handling action here*/
}


/** QSPI interrupt handler function */
uint8_t qspi_plic_IRQHandler(void)
{
    qspi_isr();
    return(0);      // ex return (uint8_t)EXT_IRQ_KEEP_ENABLED;
}


/**
 * @brief   CORE_QSPI_timer_expired() must be called in the SysTickTimerCallback() interrupt handler
 *          to allow the decrement of the software timer associated to the QSPI driver
 * @param   t = timer period [msec]
 * @return  None
 */
void CORE_QSPI_timer_expired(uint32_t t)
{
    if (qspiTout >= t) qspiTout -= t;
    else qspiTout = 0;
}


/**
 * @brief   CORE_QSPI_wait_msec() function is a passive wait for n milliseconds
 *          This function must be called in the SystTickTimer interrupt handler
 * @param   t = interrupt handler function of the type core_qspi_status_handler_t
 *          which needs to be registered.
 * @return  None
 */
void CORE_QSPI_wait_msec(uint32_t t)
{
    qspiTout = t;
    while (qspiTout);
}

/* EOF */
