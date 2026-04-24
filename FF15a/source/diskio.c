/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "usr_global.h"

struct {
    uint16_t sect_num;
    uint16_t sect_size;
} QSPIstruct;


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive number to identify the drive */
)
{
	switch (pdrv) {
	case FFDEV_QSPI :
		return 0;
	}
	return STA_NOINIT;
}


/*-----------------------------------------------------------------------*/
/* Initialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive number to identify the drive */
)
{
    uint8_t buf[4];

    QSPIstruct.sect_num = 0;
    QSPIstruct.sect_size = 0;
    switch (pdrv) {
	case FFDEV_QSPI :
		QSPIFlash_init(CORE_QSPI_QUAD_FULL);
		QSPIFlash_readid(buf);
		 // ISSI = 0x9D, IS25LP256D = 0x18, MemType = 0x60, Capacity = 0x19
		if (buf[0] == IS25LP_JEDEC_ID)
		{
		    QSPIstruct.sect_num = QSPI_FAT32_NUM_SECTORS;     // Max. 8192;
		    QSPIstruct.sect_size = 4096;
		    return 0;
		}
		else
		    return STA_NOINIT;
	}
	return STA_NOINIT;
}


/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive number to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	uint32_t Addr, Len;

	switch (pdrv) {
	case FFDEV_QSPI :
	    Addr = sector * QSPIstruct.sect_size;
	    Len = count * QSPIstruct.sect_size;
	    QSPIFlash_read(buff, Addr, Len);
	    return RES_OK;
	}
	return RES_PARERR;
}


/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive number to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	uint8_t result, i;
	uint32_t Addr, Len;

	switch (pdrv) {
	case FFDEV_QSPI :
        Addr = sector * QSPIstruct.sect_size;
        Len = count * QSPIstruct.sect_size;
        // Erase sectors before write
        for(i = 0; i < count; i++)
        {
            result = QSPIFlash_sector_erase(sector+i);
            if (result)
                return RES_ERROR;
        }
        // Write Flash
	    result = QSPIFlash_program((uint8_t*)buff, Addr, Len);
	    if (result)
	        return RES_ERROR;
		return RES_OK;
	}

	return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive number (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case FFDEV_QSPI :
	    if (cmd == CTRL_SYNC)
	        return RES_OK;
	    else if (cmd == GET_SECTOR_COUNT)
	    {
	        *((WORD *) buff) = QSPIstruct.sect_num;
	        return RES_OK;
	    }
        else if (cmd == GET_SECTOR_SIZE)
        {
            *((WORD *) buff) = QSPIstruct.sect_size;
            return RES_OK;
        }
        else if (cmd == GET_BLOCK_SIZE)
        {
            *((WORD *) buff) = 1;
            return RES_OK;
        }
        else
            return RES_ERROR;
	}

	return RES_PARERR;
}


/* See "FF_FS_NORTC" definition before use
uint32_t get_fattime (void)
{
    time_t t;
    struct tm *stm;

    t = time(0);                // RTC read
    stm = localtime(&t);

    return (DWORD)(stm->tm_year - 80) << 25 |
          (DWORD)(stm->tm_mon + 1) << 21 |
          (DWORD)stm->tm_mday << 16 |
          (DWORD)stm->tm_hour << 11 |
          (DWORD)stm->tm_min << 5 |
          (DWORD)stm->tm_sec >> 1;
} */

/*EOF*/
