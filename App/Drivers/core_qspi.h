/**
  ******************************************************************************
  * @file           : core_qspi.h
  * @brief          : Header for core_qspi file.
  * @note           : Project code 82037801
  ******************************************************************************

  --------------------------------
  Features
  --------------------------------
  This QSPI driver provides the following features:
       - QSPI Master operations in 1-bit, 2-bit, 4-bit formats and extended
         operations
       - XIP operations
       - Configurable SPI mode0 and mode3
       - Programmable SPI clock

  ==============================================================================
  Theory of Operation
  ==============================================================================
  The CORE QSPI driver functions are grouped into the following categories.
    - Initialization and configuration functions
    - Polled transmit and receive functions
    - Interrupt driven transmit and receive functions

  --------------------------------
  Initialization and Configuration
  --------------------------------
  The CORE QSPI supports the following operations.
    - Normal SPI operations (1 bit)
    - Dual SPI operations   (2 bit)
    - Quad SPI operations   (4 bit)

  The CORE QSPI driver provides the CORE_QSPI_init() function to initialize the
  CORE QSPI hardware block. This initialization function must be called before
  any other CORE QSPI driver functions can be called.

  The CORE QSPI driver provides the CORE_QSPI_config() function to configure the
  CORE QSPI with desired configuration values. It also provides the
  CORE_QSPI_get_config() function to read back the current configurations of the
  CORE QSPI. You can use this function to retrieve the current configurations and
  then overwrite them with the application specific values, such as SPI mode, 
  SPI clock rate, SDI sampling, QSPI operation, XIP mode and XIP address bits. 
  All these configuration options are explained in detail in the API function 
  description of the respective function.

  --------------------------------------
  SPI master block transfer control
  --------------------------------------
  The driver can transmit and receive data when initialized and configured with 
  the desired configuration values. The CORE QSPI is designed to specifically
  work with SPI flash memories. It supports a single, active-low slave-select 
  output. Block transfers can be accomplished in the following ways.
    - Polled block transfer
    - Interrupt driven block transfer

  ---------------------------
  Polled block transfer
  ---------------------------
  The CORE_QSPI_polled_transfer_block() is provided to accomplish data transfers
  where no interrupt is used. This function polls the status register to know
  the current status of the on-going transfer. This is a blocking
  function. A CORE QSPI block transfer always has some amount of data to be
  transmitted (at least one command byte) but receiving useful data from target 
  memory device is optional. So, if the scheduled block transfer 
  is only transferring data (and not receiving any data), then this function 
  will exit after transmitting the required bytes. In a given transfer, if 
  there is data to be received from the target memory device, then this function 
  will exit when the expected data is received from the target memory device.

  --------------------------------
  Interrupt driven block transfer
  --------------------------------
  This block transfer can be accomplished using interrupts instead of polling 
  the status register. The Following functions are provided to support interrupt 
  driven block transfers.
            - CORE_QSPI_irq_transfer_block()
            - CORE_QSPI_set_status_handler()

  The CORE_QSPI_set_status_handler() function must be used to set a status handler
  call-back function with the driver. This function will be called-back by the
  driver at two different stages of the transfer. At the first stage, it will 
  be called when the required number of bytes are transmitted. At the second 
  stage, if there is data to be received from the target memory device then it 
  will be called again when the desired data is received. Appropriate status 
  value is passed by the driver as a parameter of this call-back function, so 
  that the application can infer the event occurred.

  -----------
  QSPI Status
  -----------
  The CORE_QSPI_read_status() function reads the current status of the CORE QSPI.
  This function can typically be used to know the status of the ongoing transfer. 
  This function returns the status register value and can be called at any time 
  after the CORE QSPI is initialized and configured.

  -------------
  Direct Access
  -------------
  CORE QSPI allows direct access to the QSPI interface pins to support access to
  non-standard SPI devices via direct CPU control.
  
  This driver provides following functions to read and write the direct access 
  register of the CORE QSPI.
                  - CORE_QSPI_read_direct_access_reg()
                  - CORE_QSPI_write_direct_access_reg()
  
  Using these functions, you can generate any sequence of binary transitions on 
  the QSPI pins which might be needed to communicate with non-standard target
  devices.

 ******************************************************************************/
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
#ifndef CORE_QSPI_H_
#define CORE_QSPI_H_             1

#include "usr_global.h"
#include "core_qspi_regs.h"

/* Define I/O macros -------------------------------------------------------- */

/* Define Constants --------------------------------------------------------- */

/* The following constants can be used as input parameter value to configure the
 * event on which the SDI pin is sampled as shown below:
 *  qspi_config.sample = CORE_QSPI_SAMPLE_POSAGE_SPICLK;
 *  CORE_QSPI_configure(&qspi_config);
 *
 * */
/* The SDI pin is sampled at the rising edge off SPI CLOCK */
#define CORE_QSPI_SAMPLE_POSAGE_SPICLK       0x00u

/* The SDI pin is sampled on the last falling HCLK edge in the SPI clock period */
#define CORE_QSPI_SAMPLE_ACTIVE_SPICLK       0x01u

/* The SDI pin is sampled at the rising HCLK edge as SPICLK falls */
#define CORE_QSPI_SAMPLE_NEGAGE_SPICLK       0x02u

/* Public constant definitions
 * The following constants can be used to configure the CORE QSPI where a zero
 * or non-zero value such as enable or disable is to be provided as input 
 * parameter as shown below:
 *      qspi_config.xip = CORE_QSPI_DISABLE;
 *      CORE_QSPI_configure(&qspi_config);
 *
 * */
#define CORE_QSPI_ENABLE                     0x01u
#define CORE_QSPI_DISABLE                    0x00u


/* Define Types ------------------------------------------------------------- */

/**
   These values are used to program the io_format parameter of the configuration
   structure of this driver as shown below:
    qspi_config.io_format = CORE_QSPI_QUAD_FULL;
    CORE_QSPI_configure(&qspi_config);

|   Value            |                   Description                            |
|--------------------|----------------------------------------------------------|
|CORE_QSPI_NORMAL    |  1 bit Normal SPI operations                             |
|                    |  (single DQ0 TX and single  DQ1 RX lines)                |
|                    |                                                          |
|CORE_QSPI_DUAL_EX_RO|  2 bit SPI operations                                    |
|                    |  (command and address bytes on DQ0 only. Data on DQ[1:0])|
|                    |                                                          |
|CORE_QSPI_QUAD_EX_RO|  4 bit SPI operations                                    |
|                    |  (command and address bytes on DQ0 only. Data on DQ[3:0])|
|                    |                                                          |
|CORE_QSPI_DUAL_EX_RW|  2 bit SPI operations                                    |
|                    |  (command byte on DQ0 only. Address and Data on DQ[1:0]) |
|                    |                                                          |
|CORE_QSPI_QUAD_EX_RW|  4 bit SPI operations                                    |
|                    |  (command byte on DQ0 only. Address and Data on DQ[3:0]) |
|                    |                                                          |
|CORE_QSPI_DUAL_FULL |  2 bit SPI operations                                    |
|                    |  (command, address and Data on DQ[1:0])                  |
|                    |                                                          |
|CORE_QSPI_QUAD_FULL |  4 bit SPI operations                                    |
|                    |  (command, address and Data on DQ[3:0])                  |
|                    |                                                          |
*/
typedef enum core_qspi_io_format_t
{
    CORE_QSPI_NORMAL      = 0u,
    CORE_QSPI_DUAL_EX_RO  = 2u,
    CORE_QSPI_QUAD_EX_RO  = 3u,
    CORE_QSPI_DUAL_EX_RW  = 4u,
    CORE_QSPI_QUAD_EX_RW  = 5u,
    CORE_QSPI_DUAL_FULL   = 6u,
    CORE_QSPI_QUAD_FULL   = 7u

} core_qspi_io_format;


/**
   These values are used to program the spi_mode parameter of the configuration
   structure of this driver as shown below:
        qspi_config.spi_mode = CORE_QSPI_MODE0;
        CORE_QSPI_configure(&qspi_config);

|   Value           |                   Description                            |
|-------------------|----------------------------------------------------------|
|   CORE_QSPI_MODE0 | Set clock IDLE to low   (0)                              |
|   CORE_QSPI_MODE0 | Set clock IDLE to high  (1)                              |
*/
typedef enum core_qspi_protocol_mode_t
{
    CORE_QSPI_MODE0    = 0x0u,
    CORE_QSPI_MODE3    = 0x1u

} core_qspi_protocol_mode;


/**
 * These values are used to program the spi_mode parameter of the configuration
   structure of this driver as shown below:
        qspi_config.clk_div =  CORE_QSPI_CLK_DIV_2;
        CORE_QSPI_configure(&qspi_config);

|        Value           |        Description        |
|------------------------|---------------------------|
|   CORE_QSPI_CLK_DIV_2  |  Set SPI clock to HCLK/2  |
|   CORE_QSPI_CLK_DIV_4  |  Set SPI clock to HCLK/4  |
|   CORE_QSPI_CLK_DIV_6  |  Set SPI clock to HCLK/6  |
|   CORE_QSPI_CLK_DIV_8  |  Set SPI clock to HCLK/8  |
|   CORE_QSPI_CLK_DIV_10 |  Set SPI clock to HCLK/10 |
|   CORE_QSPI_CLK_DIV_12 |  Set SPI clock to HCLK/12 |
|   CORE_QSPI_CLK_DIV_14 |  Set SPI clock to HCLK/14 |
|   CORE_QSPI_CLK_DIV_16 |  Set SPI clock to HCLK/16 |
|   CORE_QSPI_CLK_DIV_18 |  Set SPI clock to HCLK/18 |
|   CORE_QSPI_CLK_DIV_20 |  Set SPI clock to HCLK/20 |
|   CORE_QSPI_CLK_DIV_22 |  Set SPI clock to HCLK/22 |
|   CORE_QSPI_CLK_DIV_24 |  Set SPI clock to HCLK/24 |
|   CORE_QSPI_CLK_DIV_26 |  Set SPI clock to HCLK/26 |
|   CORE_QSPI_CLK_DIV_28 |  Set SPI clock to HCLK/28 |
|   CORE_QSPI_CLK_DIV_30 |  Set SPI clock to HCLK/30 |
*/
typedef enum core_qspi_clk_div_t
{
    CORE_QSPI_CLK_DIV_2     = 0x1u,
    CORE_QSPI_CLK_DIV_4     = 0x2u,
    CORE_QSPI_CLK_DIV_6     = 0x3u,
    CORE_QSPI_CLK_DIV_8     = 0x4u,
    CORE_QSPI_CLK_DIV_10    = 0x5u,
    CORE_QSPI_CLK_DIV_12    = 0x6u,
    CORE_QSPI_CLK_DIV_14    = 0x7u,
    CORE_QSPI_CLK_DIV_16    = 0x8u,
    CORE_QSPI_CLK_DIV_18    = 0x9u,
    CORE_QSPI_CLK_DIV_20    = 0xAu,
    CORE_QSPI_CLK_DIV_22    = 0xBu,
    CORE_QSPI_CLK_DIV_24    = 0xCu,
    CORE_QSPI_CLK_DIV_26    = 0xDu,
    CORE_QSPI_CLK_DIV_28    = 0xEu,
    CORE_QSPI_CLK_DIV_30    = 0xFu

} core_qspi_clk_div;


/**
   This prototype defines the function prototype that must be followed by CORE QSPI
   status handler functions. This function is registered with the CORE QSPI driver
   through a call to the CORE_QSPI_set_status_handler() function.

   Declaring and Implementing Status Handler Function:
   Slave frame receive handler functions should follow the following prototype.
        void transfer_status_handler(uint32_t status);
 
   The actual name of the status handler is unimportant. You can use any name
   of your choice. The status parameter will contain a value indicating which
   of the TX-DONE, RX-DONE event has caused the interrupt.
*/
typedef void (*core_qspi_status_handler_t)(uint32_t status);


/**
   CORE QSPI configuration structure.
   This is structure definition for CORE QSPI configuration instance. It defines
   the configuration data to be exchanged by the application with the driver.

   Configuration options for CORE QSPI

|  Parameter  |                         Description                            |
|-------------|----------------------------------------------------------------|
|   xip       |  Enable or disable XIP mode                                    |
|   xip_addr  |  Number of address bytes used in XIP mode                      |
|   spi_mode  |  Select either Motorola mode0 or mode3                         |
|   clk_div   |  HCLK Clock divider for generating SPI clock                   |
|   io_format |  QSPI transfer format, extended,dual,quad etc.                 |
|   sample    |  Select the event on which the QSPI samples the incoming data  |
*/
typedef struct core_qspi_config{
    uint8_t                 xip;
    uint8_t                 xip_addr;
    core_qspi_protocol_mode  spi_mode;   /*clkidl mode0 or mode3*/
    core_qspi_clk_div        clk_div;
    core_qspi_io_format      io_format;
    uint8_t                 sample;
}core_qspi_config_t;


/* Core QSPI registers map */
typedef struct
{
    volatile uint32_t CONTROL;
    volatile uint32_t FRAMES;
    volatile uint32_t RESERVED1;
    volatile uint32_t INTENABLE;
    volatile uint32_t STATUS;
    volatile uint32_t DIRECT;
    volatile uint8_t ADDRUP;
    volatile uint8_t ADDRUP_R1;
    volatile uint8_t ADDRUP_R2;
    volatile uint8_t ADDRUP_R3;
    volatile uint32_t RESERVED2[9];
    volatile uint8_t RXDATAX1;
    volatile uint8_t RXDATAX1_R1;
    volatile uint8_t RXDATAX1_R2;
    volatile uint8_t RXDATAX1_R3;
    volatile uint8_t TXDATAX1;
    volatile uint8_t TXDATAX1_R1;
    volatile uint8_t TXDATAX1_R2;
    volatile uint8_t TXDATAX1_R3;
    volatile uint32_t RXDATAX4;
    volatile uint32_t TXDATAX4;
    volatile uint32_t FRAMESUP;

} QSPI_TypeDef;

/* Core QSPI base memory address*/
#define QSPI_BASE               QSPI_0

/* Core QSPI hardware instance*/
#define QSPI                    ((QSPI_TypeDef *) QSPI_BASE)


/* Define Software macros --------------------------------------------------- */

/**
 * @brief   CORE_QSPI_enable() function enables the CORE QSPI hardware block.
 * @param   None
 * @return  None
 */
static inline void CORE_QSPI_enable(void)
{
    QSPI->CONTROL |= CTRL_EN_MASK;
}


/**
 * @brief   CORE_QSPI_disable() function disables the CORE QSPI hardware block.
 * @param   None
 * @return  None
 */
static inline void CORE_QSPI_disable(void)
{
    QSPI->CONTROL &= ~CTRL_EN_MASK;
}


/**
 * @brief   CORE_QSPI_read_direct_access_reg() reads the current value of the direct
 *          access register(DAR) of the CORE QSPI. DAR allows direct access to the QSPI
 *          interface pins to support access to non-standard SPI devices through direct
 *          CPU control.
 * @param   None
 * @return  None
 */
static inline uint32_t CORE_QSPI_read_direct_access_reg(void)
{
    return(QSPI->DIRECT);
}


/**
 * @brief   CORE_QSPI_write_direct_access_reg() to write a value of the DAR of the
 *          CORE QSPI. DAR allows direct access to the QSPI interface pins, to support
 *          access to non-standard SPI devices through direct CPU control.
 * @param   None
 * @return  None
 */
static inline void CORE_QSPI_write_direct_access_reg(uint32_t value)
{
    QSPI->DIRECT = value;
}


/**
 * @brief   CORE_QSPI_read_status() is used to read the status of the CORE QSPI.
 *          This function returns the status register value and can be called any
 *          time after the CORE QSPI is initialized and configured.
 * @param   None
 * @return  None
 */
static inline uint32_t CORE_QSPI_read_status(void)
{
    return(QSPI->STATUS);
}


/* Prototypes --------------------------------------------------------------- */

void CORE_QSPI_init (void);
void CORE_QSPI_configure(const core_qspi_config_t* config);
void CORE_QSPI_get_config(core_qspi_config_t* config);
void CORE_QSPI_polled_transfer_block(uint8_t num_addr_bytes, const void * const tx_buffer,
    uint32_t tx_byte_size, const void * const rd_buffer, uint32_t rd_byte_size, uint8_t num_idle_cycles);
uint8_t CORE_QSPI_irq_transfer_block(uint8_t num_addr_bytes, const void * const tx_buffer,
    uint32_t tx_byte_size, const void * const rd_buffer, uint32_t rd_byte_size, uint8_t num_idle_cycles);
void CORE_QSPI_set_status_handler(core_qspi_status_handler_t handler);
void CORE_QSPI_timer_expired(uint32_t t);
void CORE_QSPI_wait_msec(uint32_t t);

#endif /* CORE_QSPI_H_*/

/*EOF*/
