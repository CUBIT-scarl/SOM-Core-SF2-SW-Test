/**
  ******************************************************************************
  * @file           : IS25LP256D.c
  * @brief          : IS25LP256D QSPI driver.
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

/* Define Constants --------------------------------------------------------- */

core_qspi_config_t beforexip_qspi_config={0};
core_qspi_config_t g_qspi_config = {0};
core_qspi_config_t qspi_config_read={0};


/* Define Global variables -------------------------------------------------- */

volatile uint8_t g_rx_complete = 0u;
volatile uint8_t g_tx_complete = 0u;
volatile static uint8_t g_enh_v_val __attribute__ ((aligned (4))) = 0x0u;
static volatile uint32_t qspiTout;


/* Local Functions ---------------------------------------------------------- */

static void read_statusreg(uint8_t* rd_buf);
static void read_nv_cfgreg(uint8_t* rd_buf);
static void read_v_cfgreg(uint8_t* rd_buf);
static void read_enh_v_cfgreg(uint8_t* rd_buf);
static void read_flagstatusreg(uint8_t* rd_buf);
static void enable_4byte_addressing(void);
static void disable_4byte_addressing(void);
static void device_reset(void);
static void write_enh_v_confreg(uint8_t* enh_v_val);
static core_qspi_io_format probe_io_format(void);
static core_qspi_io_format update_io_format(core_qspi_io_format t_io_format);
static uint8_t program_page(uint8_t* buf,uint32_t page,uint32_t len);
static void enter_quad_io_mode (void);
static void exit_quad_io_mode (void);

/* Functions ---------------------------------------------------------------- */

#ifdef  USE_QSPI_INTERRUPT
#define QSPI_TRANSFER_BLOCK(num_addr_bytes, tx_buffer, tx_byte_size, rd_buffer, rd_byte_size, num_idle_cycles) \
        {\
            CORE_QSPI_irq_transfer_block((num_addr_bytes), (tx_buffer), (tx_byte_size), (rd_buffer), (rd_byte_size), (num_idle_cycles));\
            if((tx_buffer && !rd_buffer)) \
            {wait_for_tx_complete();} \
            if((rd_buffer && !tx_buffer)) \
            {wait_for_tx_complete();} \
            if((tx_buffer && rd_byte_size && rd_buffer && tx_byte_size)) \
              {wait_for_rx_complete();\
              wait_for_tx_complete(); \
              } \
        }
#else
#define QSPI_TRANSFER_BLOCK(num_addr_bytes, tx_buffer, tx_byte_size, rd_buffer, rd_byte_size, num_idle_cycles) \
    CORE_QSPI_polled_transfer_block((num_addr_bytes), (tx_buffer), (tx_byte_size), (rd_buffer), (rd_byte_size), (num_idle_cycles));
#endif

#ifdef USE_QSPI_INTERRUPT
void transfer_status_handler(uint32_t status)
{
    if (STTS_RDONE_MASK == (STTS_RDONE_MASK & status))
    {
        g_rx_complete = 1;
    }
    else if (STTS_TDONE_MASK == (STTS_TDONE_MASK & status))
    {
        g_tx_complete = 1;
    }
}

static void wait_for_tx_complete(void)
{
    while (0u == g_tx_complete);
    g_tx_complete = 0u;
}

static void wait_for_rx_complete(void)
{
    while (0u == g_rx_complete);
    g_rx_complete = 0u;
}
#endif

/**
  * @brief  QSPI Flash initialisation
  * @param  io_format SPI IO format that needs to be used 
  * @retval None
  */
void QSPIFlash_init(core_qspi_io_format io_format)
{
    volatile core_qspi_io_format t_io_format = CORE_QSPI_NORMAL;

    CORE_QSPI_init();

#ifdef USE_QSPI_INTERRUPT
    CORE_QSPI_set_status_handler(transfer_status_handler);
#endif

    g_qspi_config.clk_div =  CORE_QSPI_CLK_DIV_4;           // CUT Max clock speed 25MHz
    g_qspi_config.sample = CORE_QSPI_SAMPLE_POSAGE_SPICLK;
    g_qspi_config.spi_mode = CORE_QSPI_MODE3;
    g_qspi_config.xip = CORE_QSPI_DISABLE;
    g_qspi_config.io_format = CORE_QSPI_NORMAL;
    CORE_QSPI_configure(&g_qspi_config);

    device_reset();

    /* Find out the current mode of the flash memory device
     * and configure qspi controller to that mode.*/
    t_io_format = probe_io_format();

    g_qspi_config.io_format = t_io_format;
    CORE_QSPI_configure(&g_qspi_config);

    if (io_format != t_io_format)
    {
        if (io_format == CORE_QSPI_QUAD_FULL && t_io_format == CORE_QSPI_NORMAL)
            enter_quad_io_mode();
        else if (io_format == CORE_QSPI_NORMAL && t_io_format == CORE_QSPI_QUAD_FULL)
            exit_quad_io_mode();
    }
    g_qspi_config.io_format = io_format;
    CORE_QSPI_configure(&g_qspi_config);
    read_enh_v_cfgreg((uint8_t*)&g_enh_v_val);
    g_enh_v_val &= ~(0x0F << 3);
    g_enh_v_val |= (8 << 3);    // Dummy cycles
    write_enh_v_confreg((uint8_t*)&g_enh_v_val);
    read_enh_v_cfgreg((uint8_t*)&g_enh_v_val);
    enable_4byte_addressing();
    QSPIFlash_wait_msec(20);
}

/**
  * @brief  QSPI Flash read device 
  * @param  buf SPI pointer to the buffer in which the driver will copy the JEDEC ID data.
  *			The buffer must be at least 1 bytes long.
  * @retval None
  */ 
void QSPIFlash_readid(uint8_t* buf)
{
    uint8_t command_buf[1] __attribute__ ((aligned (4))) = {IS25LP_READ_ID_OPCODE};
    volatile core_qspi_io_format t_io_format;

    t_io_format = g_qspi_config.io_format;
    if ((t_io_format != CORE_QSPI_QUAD_FULL) && (t_io_format != CORE_QSPI_DUAL_FULL)) {
        t_io_format = update_io_format(CORE_QSPI_NORMAL);
        QSPI_TRANSFER_BLOCK(0, command_buf, 0, buf, 3, 0);
        update_io_format(t_io_format);
    } else {
        command_buf[0] = IS25LP_MIO_READ_ID_OPCODE;
        QSPI_TRANSFER_BLOCK(0, command_buf, 0, buf, 3, 0);
    }
}


/**
  * @brief  QSPI Flash read data
  * @param  buf  pointer to the buffer in which the driver will copy the data read from the flash memory 
  * @param  addr data read start address
  * @param  len  number of data bytes to read from the flash memory 
  * @retval None
  */
void QSPIFlash_read(uint8_t* buf, uint32_t addr, uint32_t len)
{
    uint8_t dummy_cycles = 0u;
    uint8_t command_buf[10] __attribute__ ((aligned (4))) = {0u};

    command_buf[1] = (addr >> 24u) & 0xFFu;
    command_buf[2] = (addr >> 16u) & 0xFFu;
    command_buf[3] = (addr >> 8u) & 0xFFu;
    command_buf[4] = addr & 0xFFu;

    switch(g_qspi_config.io_format)
    {
       case CORE_QSPI_NORMAL:
           command_buf[0] = IS25LP_4BYTE_FAST_READ;
           dummy_cycles = 8u;
           break;
       case CORE_QSPI_QUAD_FULL:
           command_buf[0] = IS25LP_4BYTE_FAST_READ;
           dummy_cycles = 8u;                              /* For Quad mode */
           break;
       default:
           command_buf[0] = IS25LP_4BYTE_FAST_READ;         // The same as CORE_QSPI_NORMAL
           dummy_cycles = 8u;
           break;
    }

    QSPI_TRANSFER_BLOCK(4, command_buf, 0, buf, len, dummy_cycles);
}


/**
  * @brief  QSPI Flash write data
  * @param  buf  pointer to the buffer from which data will be written into the flash memory 
  * @param  addr data write start address
  * @param  len  number of data bytes to write into the flash memory 
  * @retval 0 = success, nonzero = error
  */

//uint8_t buf2[256];
uint8_t QSPIFlash_program(uint8_t* buf, uint32_t addr, uint32_t len)
{
    int32_t remaining_length = (int32_t)len;
    uint32_t target_offset = addr, i;
    uint8_t status = 0xFF;

    while(remaining_length > 0)
    {
        uint32_t page_length;

        if(remaining_length >= IS25LP_PAGE_LENGTH)
        {
            page_length = IS25LP_PAGE_LENGTH;
        }
        else
        {
            page_length = remaining_length;
        }

        status = program_page(buf, target_offset, page_length);
// CUT Uncomment for debugging
//        QSPIFlash_read(buf2, target_offset,page_length);
//        for (i = 0; i < page_length; i++)
//        {
//            if (buf[i] != buf2[i])
//                WaitMsec(10);
//        }

        remaining_length -= page_length;
        target_offset += page_length;
        buf += page_length;
    }

    return (status);
}


/**
  * @brief  QSPI Flash complete device erase
  * @param  None
  * @retval 0 = success, nonzero = error
  */
uint8_t QSPIFlash_erase(void)
{
    uint8_t status = 0xFFu;
    uint8_t command_buf[5] __attribute__ ((aligned (4))) = {IS25LP_WRITE_ENABLE};
    /*Both Write enable and Die erase can work in all modes*/

    /* Write enable command must be executed before erase
     * WRITE ENABLE 06h, no dummy cycles.
     * */
    volatile core_qspi_io_format t_io_format;

    t_io_format = update_io_format(CORE_QSPI_NORMAL);

    QSPI_TRANSFER_BLOCK(0, command_buf, 0, (uint8_t*)0, 0,0);

    /* Erase the die. This will write 1 to all bits
     * DIE ERASE C4h, no dummy cycles
     * */
    command_buf[0] = IS25LP_BULK_ERASE;
    QSPI_TRANSFER_BLOCK(0, command_buf, 0, (uint8_t*)0, 0,0);
    update_io_format(t_io_format);
    QSPIFlash_wait_msec(20);

    while (1){
        read_flagstatusreg(&status);
        if ((status & I25LP_STATUS_BUSY_MASK) == 0)
            break;
    }
    status &= I25LP_STATUS_EFAIL_MASK;
    return(status);
}


/**
  * @brief  QSPI Flash 4K sector erase
  * @param  sect = sector number to erase
  * @retval 0 = success, nonzero = error
  */
uint8_t QSPIFlash_sector_erase(uint16_t sect)
{
    uint8_t status = 0xFFu;
    uint8_t command_buf[5] __attribute__ ((aligned (4))) = {IS25LP_WRITE_ENABLE};
    uint32_t addr;

    addr = sect * IS25LP_SECTOR_SIZE;
    command_buf[1] = (addr >> 24u) & 0xFFu;
    command_buf[2] = (addr >> 16u) & 0xFFu;
    command_buf[3] = (addr >> 8u) & 0xFFu;
    command_buf[4] =  addr & 0xFFu;

    /* Write enable command must be executed before erase
     * WRITE ENABLE 06h, no dummy cycles.
     * */
    volatile core_qspi_io_format t_io_format;

    t_io_format = update_io_format(CORE_QSPI_NORMAL);

    QSPI_TRANSFER_BLOCK(0, command_buf, 0, (uint8_t*)0, 0,0);

    /* 4K Sector Erase. This will write 1 to all bits
     * 4K SECTOR ERASE 21h, no dummy cycles
     * */
    command_buf[0] = IS25LP_4BYTE_4KB_SUBSECTOR_ERASE;
    QSPI_TRANSFER_BLOCK(4, command_buf, 0, (uint8_t*)0, 0, 0);
    update_io_format(t_io_format);

    while (1){
        read_flagstatusreg(&status);
        if ((status & I25LP_STATUS_BUSY_MASK) == 0)
            break;
    }
    status &= I25LP_STATUS_EFAIL_MASK;
    return(status);
}


/**
  * @brief  Reads all three status registers
  * @param buf
  * The buf parameter is a pointer to the buffer in which the driver will
  * copy the status register values. The buffer should be large enough to store 6
  * 8-bit bytes. The sequence is
  *  - Status register
  *  - Non-volatile configuration registers (2 bytes)
  *  - Volatile configuration registers
  *  - Enhanced volatile configuration register
  *  - Flag status register
  * @retval None
*/
void QSPIFlash_read_status_regs(uint8_t* buf)
{
    read_statusreg(&buf[0]);
    read_nv_cfgreg(&buf[1]); /* 2bytes */
    read_v_cfgreg(&buf[3]);
    read_enh_v_cfgreg(&buf[4]);
    read_flagstatusreg(&buf[5]);
}


/**
  * @brief  Clear flag status register
  * @param  None
  * @retval None
  * @note 	The Flash_clr_flagstatusreg() function can be used in case there were errors
  *			in erase/program operations. This function will clear the error status so that
  *			subsequent erase/program operations can be initiated.
*/
void QSPIFlash_clr_flagstatusreg (void)
{
    const uint8_t command_buf[1] __attribute__ ((aligned (4))) = {IS25LP_CLR_FLAG_STATUS_REG};
    volatile core_qspi_io_format t_io_format;

    t_io_format = update_io_format(CORE_QSPI_NORMAL);

    QSPI_TRANSFER_BLOCK(0, command_buf, 0, 0, 0,0);
    update_io_format(t_io_format);
}


/**
 * @brief   QSPIFlash_timeout() must be called in the SysTickTimerCallback() interrupt handler
 *          to allow the decrement of the software timer associated to the QSPI driver
 * @param   t = timer period [msec]
 * @return  None
 */
void QSPIFlash_timeout(uint32_t t)
{
    if (qspiTout >= t) qspiTout -= t;
    else qspiTout = 0;
}


/**
 * @brief   QSPIFlash_wait_msec() function is a passive wait for n milliseconds
 *          This function must be called in the SystTickTimer interrupt handler
 * @param   t = interrupt handler function of the type core_qspi_status_handler_t
 *          which needs to be registered.
 * @return  None
 */
void QSPIFlash_wait_msec(uint32_t t)
{
    qspiTout = t;
    while (qspiTout);
}


/* Local functions --------------------------------------------------------- */

static void read_statusreg (uint8_t* rd_buf)
{
    const uint8_t command_buf[1] __attribute__ ((aligned (4))) = {IS25LP_READ_STATUS_REG};
    volatile core_qspi_io_format t_io_format;

    t_io_format = update_io_format(CORE_QSPI_NORMAL);

    QSPI_TRANSFER_BLOCK(0, command_buf, 0, rd_buf, 1,0);
    update_io_format(t_io_format);
}


static void enable_4byte_addressing (void)
{
    uint8_t command_buf[1] __attribute__ ((aligned (4))) = {IS25LP_WRITE_ENABLE};
    volatile core_qspi_io_format t_io_format;

    t_io_format = update_io_format(CORE_QSPI_NORMAL);

    /* Write enable command must be executed before writing extended addr reg. */
    QSPI_TRANSFER_BLOCK(0, command_buf, 0, (uint8_t*)0, 0, 0);

    command_buf[0] =  IS25LP_ENTER_4BYTE_ADDR_MODE;

    /* This command works for all modes. No Dummy cycles */
    QSPI_TRANSFER_BLOCK(0, command_buf, 0, (uint8_t*)0, 0, 0);
    update_io_format(t_io_format);
}


static void disable_4byte_addressing (void)
{
    uint8_t command_buf[2] __attribute__ ((aligned (4))) = {IS25LP_WRITE_ENABLE};
    volatile core_qspi_io_format t_io_format;

    t_io_format = update_io_format(CORE_QSPI_NORMAL);

    /* Write enable command must be executed before writing extended addr reg. */
    QSPI_TRANSFER_BLOCK(0, command_buf, 0, (uint8_t*)0, 0, 0);

    command_buf[0] =  IS25LP_EXIT_4BYTE_ADDR_MODE;

    /* This command works for all modes. No Dummy cycles */
    QSPI_TRANSFER_BLOCK(0, command_buf, 0, (uint8_t*)0, 0, 0);
    update_io_format(t_io_format);

}


static void device_reset(void)
{
    uint8_t command_buf[1] __attribute__ ((aligned (4))) = {IS25LP_RESET_ENABLE};

    QSPI_TRANSFER_BLOCK(0, (void *)command_buf, 0, 0, 0,0);
    for(volatile uint32_t idx =0u; idx < 1000u ; idx++);    /* delay */

    command_buf[0] = IS25LP_RESET_MEMORY;
    QSPI_TRANSFER_BLOCK(0, (void *)command_buf, 0, 0, 0,0);
    for(volatile uint32_t idx =0u; idx < 1000u ; idx++);    /* delay */
}


static void read_nv_cfgreg (uint8_t* rd_buf)
{
    uint8_t command_buf[1] __attribute__ ((aligned (4))) = {IS25LP_READ_NV_CONFIG_REG};
    volatile core_qspi_io_format t_io_format;

    t_io_format = update_io_format(CORE_QSPI_NORMAL);

    /*This command works for all modes. No Dummy cycles*/
    QSPI_TRANSFER_BLOCK(0, command_buf, 0, rd_buf, 2,0);
    update_io_format(t_io_format);
}


static void read_v_cfgreg(uint8_t* rd_buf)
{
    uint8_t command_buf[1] __attribute__ ((aligned (4))) = {IS25LP_READ_V_CONFIG_REG};
    volatile core_qspi_io_format t_io_format;

    t_io_format = update_io_format(CORE_QSPI_NORMAL);

    /*This command works for all modes. No Dummy cycles*/
    QSPI_TRANSFER_BLOCK(0, command_buf, 0, rd_buf, 2,0);
    update_io_format(t_io_format);
}


static void read_enh_v_cfgreg(uint8_t* rd_buf)
{
    const uint8_t command_buf[1] __attribute__ ((aligned (4))) = {IS25LP_READ_ENH_V_CONFIG_REG};
    volatile core_qspi_io_format t_io_format;

    t_io_format = update_io_format(CORE_QSPI_NORMAL);

    /*This command works for all modes. No Dummy cycles*/
    QSPI_TRANSFER_BLOCK(0, command_buf, 0, rd_buf, 1,0);

    update_io_format(t_io_format);
}


static void write_enh_v_confreg(uint8_t* enh_v_val)
{
    uint8_t command_buf[2] __attribute__ ((aligned (4))) = {IS25LP_WRITE_ENABLE};
    volatile core_qspi_io_format t_io_format;

    t_io_format = update_io_format(CORE_QSPI_NORMAL);
    /*execute Write enable command again for writing the data*/
    QSPI_TRANSFER_BLOCK(0, command_buf, 0, (uint8_t*)0, 0, 0);
    command_buf[0] =  IS25LP_WR_ENH_V_CONFIG_REG;
    command_buf[1] =  *enh_v_val;

    /*This command works for all modes. No Dummy cycles*/
    QSPI_TRANSFER_BLOCK(0, command_buf, 1, (uint8_t*)0, 0, 0);
    update_io_format(t_io_format);

}


static void read_flagstatusreg(uint8_t* rd_buf)
{
    const uint8_t command_buf[1] __attribute__ ((aligned (4))) = {IS25LP_READ_FLAG_STATUS_REG};
    volatile core_qspi_io_format t_io_format;

    t_io_format = update_io_format(CORE_QSPI_NORMAL);

    /*This command works for all modes. No Dummy cycles*/
    QSPI_TRANSFER_BLOCK(0, command_buf, 0, rd_buf, 1,0);
    update_io_format(t_io_format);
}


static core_qspi_io_format update_io_format (core_qspi_io_format io_format)
{
    volatile core_qspi_io_format t_io_format;
    t_io_format = g_qspi_config.io_format;

    if ((t_io_format != CORE_QSPI_QUAD_FULL) && (t_io_format != CORE_QSPI_DUAL_FULL)) {
        if (t_io_format != io_format) {
            g_qspi_config.io_format = io_format;
            CORE_QSPI_configure(&g_qspi_config);
        }
    }

    return t_io_format;
}


static core_qspi_io_format probe_io_format(void)
{
    volatile uint8_t device_id[3] __attribute__ ((aligned (4))) = {0x0u,0x0u,0x0u};

    g_qspi_config.io_format = CORE_QSPI_QUAD_FULL;
    CORE_QSPI_configure(&g_qspi_config);
    QSPIFlash_readid((uint8_t*)device_id);
    if (IS25LP_JEDEC_ID == device_id[0])
        return(g_qspi_config.io_format);

    g_qspi_config.io_format = CORE_QSPI_NORMAL;
    CORE_QSPI_configure(&g_qspi_config);
    QSPIFlash_readid((uint8_t*)device_id);
    if (IS25LP_JEDEC_ID == device_id[0])
        return(g_qspi_config.io_format);

    return(CORE_QSPI_NORMAL);
}


/* Any address within the page is valid.
 * If len -> IS25LP_PAGE_LENGTH :
 *       Bytes more than IS25LP_PAGE_LENGTH are ignored
 * If addr -> page start addr and len > more than remaining bytes in the page :
 *       Bytes overflowing the page boundary are ignored
 * if len < pag_size :
 *       Only len bytes are modified, rest remain unchanged.
 */
static uint8_t program_page(uint8_t* buf, uint32_t addr, uint32_t len)
{
    uint8_t status = 0u;
    uint8_t command_buf[300] __attribute__ ((aligned (4))) = {0};
    uint32_t length = len;
    uint32_t offset = addr % IS25LP_PAGE_LENGTH;
    uint32_t cnt;

    if (len > IS25LP_PAGE_LENGTH)
    {
        length = IS25LP_PAGE_LENGTH;
    }

    if (offset && ((length + offset) > IS25LP_PAGE_LENGTH))
    {
        length = IS25LP_PAGE_LENGTH - offset;
    }
    volatile core_qspi_io_format t_io_format;

    t_io_format = update_io_format(CORE_QSPI_NORMAL);

    /*execute Write enable command again for writing the data*/
    command_buf[0] = IS25LP_WRITE_ENABLE;
    QSPI_TRANSFER_BLOCK(0, command_buf, 0, (uint8_t*)0, 0,0);
    update_io_format(t_io_format);

    command_buf[1] = (addr >> 24) & 0xFFu;
    command_buf[2] = (addr >> 16) & 0xFFu;
    command_buf[3] = (addr >> 8) & 0xFFu;
    command_buf[4] = addr & 0xFFu;

    for (uint16_t idx=0; idx< length;idx++)
    {
        command_buf[5 + idx] = *(uint8_t*)(buf+idx);
    }

    /* Dummy cycles for all program commands are 0.
     * DUAL EX_RO and DUAL EX_RW, QUAD_EX_RW are not implemented */
    switch(g_qspi_config.io_format)
    {
       case CORE_QSPI_NORMAL     :
           command_buf[0] = IS25LP_4BYTE_PAGE_PROG;                     // 4PP 1-1-1
           break;
       case CORE_QSPI_QUAD_FULL  :
           command_buf[0] = IS25LP_4BYTE_PAGE_PROG;                     // 4PP 4-4-4 (if Quad mode enabled)
           break;
       default:
           command_buf[0] = IS25LP_4BYTE_PAGE_PROG;     // The same as CORE_QSPI_NORMAL
           break;
    }

    QSPI_TRANSFER_BLOCK(4, command_buf, length, (uint8_t*)0u, 0u, 0u);

    cnt = 1000;
    while (cnt){
        read_flagstatusreg(&status);
        if ((status & I25LP_STATUS_BUSY_MASK) == 0)
            break;
        cnt--;
    }
    if (cnt == 0) status |= I25LP_STATUS_PFAIL_MASK;
    return(status & I25LP_STATUS_PFAIL_MASK);
}


static void enter_quad_io_mode (void)
{
    uint8_t command_buf[1] __attribute__ ((aligned (4))) = {IS25LP_WRITE_ENABLE};
    volatile core_qspi_io_format t_io_format;

    t_io_format = update_io_format(CORE_QSPI_NORMAL);

    /* Write enable command must be executed before writing extended addr reg. */
    QSPI_TRANSFER_BLOCK(0, command_buf, 0, (uint8_t*)0, 0, 0);

    command_buf[0] =  IS25LP_ENTER_QUAD_IO_MODE;

    /* This command works for all modes. No Dummy cycles */
    QSPI_TRANSFER_BLOCK(0, command_buf, 0, (uint8_t*)0, 0, 0);
    update_io_format(t_io_format);
}


static void exit_quad_io_mode (void)
{
    uint8_t command_buf[1] __attribute__ ((aligned (4))) = {IS25LP_WRITE_ENABLE};
    volatile core_qspi_io_format t_io_format;

    t_io_format = update_io_format(CORE_QSPI_NORMAL);

    /* Write enable command must be executed before writing extended addr reg. */
    QSPI_TRANSFER_BLOCK(0, command_buf, 0, (uint8_t*)0, 0, 0);

    command_buf[0] =  IS25LP_RESET_QUAD_IO_MODE;

    /* This command works for all modes. No Dummy cycles */
    QSPI_TRANSFER_BLOCK(0, command_buf, 0, (uint8_t*)0, 0, 0);
    update_io_format(t_io_format);
}

/*EOF*/
