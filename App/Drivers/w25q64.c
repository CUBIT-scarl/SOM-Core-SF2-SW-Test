/**
  ******************************************************************************
  * @file           : w25q64.c
  * @brief          : SPI flash driver
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

/* Define Global variables -------------------------------------------------- */

uint8_t spi0TxBuffer[SPI0_TXRXBUFLEN];      // SPI0 tx buffer
uint8_t spi0RxBuffer[SPI0_TXRXBUFLEN];      // SPI0 rx buffer


/* Define Types ------------------------------------------------------------- */

/* Low Level Functions ------------------------------------------------------.*/

/**
  * @brief  W25Q64 read id
  * @param  None
  * @retval 0 = ok, 0xFF = error not found or unknown
  */
uint8_t W25Q64readid(void)
{
  uint8_t manufacturer;
  uint8_t memory;
  uint8_t capacity;

  // Chip select enable
  MSS_SPI_set_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);

  /* Send the "Read ID (RDID)" command */
  spi0TxBuffer[0] = W25Q64_RDID;
  spi0TxBuffer[1] = 0xFF;
  spi0TxBuffer[2] = 0xFF;
  spi0TxBuffer[3] = 0xFF;
  MSS_SPI_transfer_block(&g_mss_spi0,(uint8_t*)&spi0TxBuffer, 1, (uint8_t*)&spi0RxBuffer, 3);

  // Chip select disable
  MSS_SPI_clear_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);

  // Read answer
  manufacturer = spi0RxBuffer[0];
  memory       = spi0RxBuffer[1];
  capacity     = spi0RxBuffer[2];

  /* Check for a valid manufacturer and memory type */
  if (manufacturer == W25Q64_MANUFACTURER && memory == W25Q64_MEMORY_TYPE && capacity == W25Q64_CAPACITY)
      return (0);   // Ok

  return (0xFF);    // Error
}


/**
  * @brief  W25Q64 wait for write complete
  * @param  None
  * @retval None
  */
void W25Q64waitwritecomplete(void)
{
  uint8_t status;
  uint32_t cnt = 1000;

  while(cnt)
  {

      // Chip select enable
      MSS_SPI_set_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);

      /* Send "Read Status Register (RDSR)" command */
      spi0TxBuffer[0] = W25Q64_RDSR;
      spi0TxBuffer[1] = 0xFF;
      MSS_SPI_transfer_block(&g_mss_spi0,(uint8_t*)&spi0TxBuffer, 1, (uint8_t*)&spi0RxBuffer, 1);

      // Chip select disable
      MSS_SPI_clear_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);

      status = spi0RxBuffer[0];
      if ((status & W25Q64_SR_WIP) != 0)
      {
          Delay_us(1000);
      }
      else
        break;
      cnt--;
  }
}


/**
  * @brief  W25Q64 global unlock
  * @param  None
  * @retval None
  * @note   SST26 flashes are globally locked after startup. To allow writing this command must be sent once
  */

void W25Q64globalunlock(void)
{
    // Chip select enable
    MSS_SPI_set_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);

    /* Send "Global Unlock (ULBPR)" command */
    spi0TxBuffer[0] = W25Q64_ULBPR;
    MSS_SPI_transfer_block(&g_mss_spi0,(uint8_t*)&spi0TxBuffer, 1, 0, 0);

    // Chip select disable
    MSS_SPI_clear_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);
}


/**
  * @brief  W25Q64 write enable
  * @param  None
  * @retval None
  */
void W25Q64writeenable(void)
{
    // Chip select enable
    MSS_SPI_set_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);

    /* Send "Write Enable (WREN)" command */
    spi0TxBuffer[0] = W25Q64_WREN;
    MSS_SPI_transfer_block(&g_mss_spi0,(uint8_t*)&spi0TxBuffer, 1, 0, 0);

    // Chip select disable
    MSS_SPI_clear_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);
}


/**
  * @brief  W25Q64 write disable
  * @param  None
  * @retval None
  */
void W25Q64writedisable(void)
{
    // Chip select enable
    MSS_SPI_set_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);

    /* Send "Write Disable (WRDI)" command */
    spi0TxBuffer[0] = W25Q64_WRDI;
    MSS_SPI_transfer_block(&g_mss_spi0,(uint8_t*)&spi0TxBuffer, 1, 0, 0);

    // Chip select disable
    MSS_SPI_clear_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);
}


/**
  * @brief  W25Q64 sector erase
  * @param  sector = sector number to erase
  * @param  cmd = W25Q64_SE sector erase, W25Q64_BE32/BE64 block erase
  * @retval None
  */
void W25Q64sectorerase(off_t sector, uint8_t cmd)
{
  off_t offset;

  if (cmd != W25Q64_SE && cmd != W25Q64_BE32 && cmd != W25Q64_BE64)
      return;

  offset = sector << W25Q64_SECTOR_SHIFT;

  /* Send write enable instruction */
  W25Q64writeenable();

  // Chip select enable
  MSS_SPI_set_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);

  /* Send the "Sector Erase (SE)" or "Block Erase 32/64K (BE32, BE64)" */
  spi0TxBuffer[0] = cmd;
  spi0TxBuffer[1] = (offset >> 16) & 0xFF;
  spi0TxBuffer[2] = (offset >> 8) & 0xFF;
  spi0TxBuffer[3] =  offset & 0xFF;
  MSS_SPI_transfer_block(&g_mss_spi0,(uint8_t*)&spi0TxBuffer, 4, 0, 0);

  // Chip select disable
  MSS_SPI_clear_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);

  W25Q64waitwritecomplete();
}


/**
  * @brief  W25Q64 chip erase
  * @param  None
  * @retval None
  */
void W25Q64chiperase(void)
{
    /* Send write enable instruction */
    W25Q64writeenable();

    // Chip select enable
    MSS_SPI_set_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);

    /* Send the "Chip Erase (CE)" instruction */
    spi0TxBuffer[0] = W25Q64_CE;
    MSS_SPI_transfer_block(&g_mss_spi0,(uint8_t*)&spi0TxBuffer, 1, 0, 0);

    // Chip select disable
    MSS_SPI_clear_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);

    W25Q64waitwritecomplete();
}


/**
  * @brief  W25Q64 page write
  * @param  *buffer = pointer to data buffer
  * @param  len = number of data to write (max 256)
  * @param  page = page number to write
  * @retval Number of bytes written
  */
uint16_t W25Q64pagewrite(uint8_t *buffer, uint16_t len, off_t page)
{
    uint16_t i;

    off_t offset = page << W25Q64_PAGE_SHIFT;

    if (len > (1 << W25Q64_PAGE_SHIFT)) // len <= 256
        return (0);

    /* Send write enable instruction */
    W25Q64writeenable();

    // Chip select enable
    MSS_SPI_set_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);

    /* Send "Page Program (PP)" command */
    spi0TxBuffer[0] = W25Q64_PP;
    spi0TxBuffer[1] = (offset >> 16) & 0xFF;
    spi0TxBuffer[2] = (offset >> 8) & 0xFF;
    spi0TxBuffer[3] =  offset & 0xFF;
    for (i = 0; i < len; i++)
        spi0TxBuffer[4+i] = *buffer++;
    MSS_SPI_transfer_block(&g_mss_spi0,(uint8_t*)&spi0TxBuffer, len+4, 0, 0);

    // Chip select disable
    MSS_SPI_clear_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);

    W25Q64waitwritecomplete();
    return (len);
}


/**
  * @brief  W25Q64 byte write
  * @param  *buffer = pointer to data buffer
  * @param  len = number of data to write (max 256)
  * @param  offset = starting address
  * @retval Number of bytes writte
  */
uint16_t W25Q64bytewrite(uint8_t *buffer, uint16_t len, off_t offset)
{
    uint16_t i, nbytes;
    uint32_t dat, dat2;

    if (len > (1 << W25Q64_PAGE_SHIFT)) // len <= 256
         return (0);

    dat = offset / (1 << W25Q64_PAGE_SHIFT);
    dat2 = (offset+len-1) / (1 << W25Q64_PAGE_SHIFT);
    if (dat2 > dat)    // Page boundary not allowed
         return (0);

    /* Send write enable instruction */
    W25Q64writeenable();

    // Chip select enable
    MSS_SPI_set_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);

    /* Send "Page Program (PP)" command */
    spi0TxBuffer[0] = W25Q64_PP;
    spi0TxBuffer[1] = (offset >> 16) & 0xFF;
    spi0TxBuffer[2] = (offset >> 8) & 0xFF;
    spi0TxBuffer[3] =  offset & 0xFF;
    for (i = 0; i < len; i++)
        spi0TxBuffer[4+i] = *buffer++;
    MSS_SPI_transfer_block(&g_mss_spi0,(uint8_t*)&spi0TxBuffer, len+4, 0, 0);

    // Chip select disable
    MSS_SPI_clear_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);

    W25Q64waitwritecomplete();
    return(len);
}


/* Driver Functions---------------------------------------------------------- */

/**
  * @brief  W25Q64 initialisation on SPI0 port
  * @param  None
  * @retval 0 = ok + Device Unlocked; 0xFF = error not found or unknown
  */
uint8_t W25Q64init(void)
{
    uint8_t status;
    MSS_SPI_init(&g_mss_spi0);
    // Device slave 0 on spi0 port, 100MHz / 4 = 25MHz (Fmax SPI CLK = PCLK/2)
    MSS_SPI_configure_master_mode(&g_mss_spi0, MSS_SPI_SLAVE_0, MSS_SPI_MODE0, 4, MSS_SPI_BLOCK_TRANSFER_FRAME_SIZE);

    status = W25Q64readid();
    if (status == 0x00)
    {
        W25Q64writeenable();
        W25Q64globalunlock();
        W25Q64writedisable();
    }
    return (status);
}



/**
  * @brief  W25Q64 erase (sector sized)
  * @param  startsect = first sector number to delete
  * @param  nsect = number of 4K sectors to delete
  * @retval None
  */
void W25Q64erase(off_t startsect, size_t nsect)
{
  while (nsect > 0)
    {
      W25Q64sectorerase(startsect, W25Q64_SE);
      startsect++;
      nsect--;
    }
}


/**
  * @brief  W25Q64 block read (page size)
  * @param  startsect = first sector number to delete
  * @param  nsect = number of 256 bytes pages to read
  * @param  *buffer = pointer to read data buffer
  * @retval Number of pages read
  */
uint32_t W25Q64bread(off_t startblock, size_t nblocks, uint8_t *buffer)
{
  uint32_t nbytes;

  /* On this device, we can handle the block read just like the byte-oriented read */
  nbytes = W25Q64read(startblock << W25Q64_PAGE_SHIFT, nblocks << W25Q64_PAGE_SHIFT, buffer);
  if (nbytes > 0)
  {
      return (nbytes >> W25Q64_PAGE_SHIFT);
  }
  return (nbytes);
}


/**
  * @brief  W25Q64 block write (page size)
  * @param  startsect = first page number to write
  * @param  nsect = number of 256 bytes pages to write
  * @param  *buffer = pointer to write data buffer
  * @retval None
  */
void W25Q64bwrite (off_t startpage, size_t npages, uint8_t *buffer)
{
  size_t pagesize = 1 << W25Q64_PAGE_SHIFT;

  while (npages-- > 0)
  {
      W25Q64pagewrite(buffer, pagesize, startpage);
      buffer += pagesize;
      startpage++;
  }
}


/**
  * @brief  W25Q64 data read (byte size)
  * @param  offset = first address to read
  * @param  nbytes = number of bytes to read
  * @param  *buffer = pointer to read data buffer
  * @retval Number of bytes read
  */
uint32_t W25Q64read (off_t offset, size_t nbytes, uint8_t *buffer)
{
    uint16_t i, chunk;
    size_t cnt;

    cnt = nbytes;
    if (cnt > 1024)
        chunk = 1024;
    else
        chunk = cnt;

    while (cnt)
    {
        // Chip select enable
        MSS_SPI_set_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);

        /* Send "Page Program (PP)" command */
        spi0TxBuffer[0] = W25Q64_FAST_READ;
        spi0TxBuffer[1] = (offset >> 16) & 0xFF;
        spi0TxBuffer[2] = (offset >> 8) & 0xFF;
        spi0TxBuffer[3] =  offset & 0xFF;
        spi0TxBuffer[4] = 0xFF;

        /* Send "Read from Memory " instruction */
        MSS_SPI_transfer_block(&g_mss_spi0,(uint8_t*)&spi0TxBuffer, 5, (uint8_t*)&spi0RxBuffer, chunk);
        // Chip select disable
        MSS_SPI_clear_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);

        for (i = 0; i < chunk; i++)
            *buffer++ = spi0RxBuffer[i];

        if (cnt >= chunk)
            cnt -= chunk;
        else
        {
            chunk = cnt;
        }
        offset += chunk;
    }
    return nbytes;
}


/**
  * @brief  W25Q64 data write (byte size)
  * @param  offset = first address to write
  * @param  nbytes = number of bytes to write
  * @param  *buffer = pointer to write data buffer
  * @retval None
  */
void W25Q64write(off_t offset, size_t nbytes, uint8_t *buffer)
{
  uint32_t  startpage;
  uint32_t  endpage;
  uint32_t  count;
  uint32_t  index;
  uint32_t  pagesize;
  uint32_t  bytestowrite;

  /* We must test if the offset + count crosses one or more pages
   * and perform individual writes.  The devices can only write in
   * page increments.
   */

  startpage = offset / (1 << W25Q64_PAGE_SHIFT);
  endpage = (offset + nbytes) / (1 << W25Q64_PAGE_SHIFT);

  if (startpage == endpage)
  {
      /* All bytes within one programmable page.  Just do the write. */
      W25Q64bytewrite(buffer, nbytes, offset);
  }
  else
  {
      /* Write the 1st partial-page */

      count = nbytes;
      pagesize = (1 << W25Q64_PAGE_SHIFT);
      bytestowrite = pagesize - (offset & (pagesize-1));
      W25Q64bytewrite(buffer, bytestowrite, offset);

      /* Update offset and count */
      offset += bytestowrite;
      count -=  bytestowrite;
      index = bytestowrite;

      /* Write full pages */
      while (count >= pagesize)
      {
          W25Q64bytewrite(&buffer[index], pagesize, offset);

          /* Update offset and count */
          offset += pagesize;
          count -= pagesize;
          index += pagesize;
      }

      /* Now write any partial page at the end */
      if (count > 0)
      {
          W25Q64bytewrite(&buffer[index], count, offset);
      }
  }
}


/*EOF*/
