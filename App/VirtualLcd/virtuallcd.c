/**
  ******************************************************************************
  * @file           : virtuallcd.c
  * @brief          : "Virtual LCD" serial protocol
  * @note           : Project code 82037801
  *
  *
  ******************************************************************************
  * Serial Protocol format:

  * HD1,HD2,STX,CMD,LEN,DATA,CRC
  * HD1  0x55
  * HD2  0xAA
  * STX  0x02
  * CMD  Command Code
  * LEN  Data length
  * DATA Payload
  * CRC  Chacksum = 1 + sum of all chars from STX to last byte of DATA field
  *
  *
  * Text Display Commands description:
  *
  * VL_Clear(): Clear text display
  * 0x55 0xAA STX 0x01 0x00 crc
  *
  * VL_Curs(r,c): Cursor Position in the indicated row/column
  * 0x55 0xAA STX 0x02 0x02 row col crc
  *
  * VL_EnableCurs(): Cursor Enable
  * 0x55 0xAA STX 0x03 0x00 crc
  *
  * VL_DisableCurs(): Cursor Disable
  * 0x55 0xAA STX 0x04 0x00 crc
  *
  * VL_SetForeColor(n): Set Text color
  * 0x55 0xAA STX 0x05 0x01 n crc
  * n = color code (0 Black, 1 Blue, 2 Green, 3 Yellow, 4 Red, 5 Magenta,
  *                 6 Brown, 7 Grey, 8 Cyan,  9 Orange)
  *
  * VL_Puts(*s): Put string on text display
  * 0x55 0xAA STX 0x06 len <string> crc
  * Len = string length (note: termination char 0x00 included)
  *
  *
  * Text Display Commands description:
  *
  * VL_SwClear(): Clear scroll display
  * 0x55 0xAA STX 0x07 0x00 crc
  *
  * VL_SwPuts(*s): Put string on scroll display
  * 0x55 0xAA STX 0x08 len <string> crc
  * Len = string length (note: termination char 0x00 included)
  *
  *
  * Keyboard management (only key pressed, no repeat, no key released)
  *
  * Key pressed packet send by Virtual LCD:
  * STX 0x10 code crc
  * code = ASCII code.
  *     Simple ascii byte code of numeric, alfanumeric chasrs and some special chars,
  *     see virtuallcd.h file for list
  *
  *
  * Graphic Display commands description:
  *
  * VL_ClearGraph(): Clear graphic display
  * 0x55 0xAA STX 0x20 0x00 crc
  *
  * VL_InitGraph(Xaxe_name,max_X,resol_X,Yaxe_name,max_Y,resol_Y): Setup X and Y axes
  * 0x55 0xAA STX 0x21 len <x_axe_string_name><x_axe_max_value><x_axe_resolution>
  *                        <x_axe_string_name><x_axe_max_value><x_axe_min_value> crc
  * axe_string_name = ascii_string+0x00 termination included (max 16+1 chars)
  * axe_max_value  = 2 unsigned bytes (Little Endian)
  * axe_resolution = 2 unsigned bytes (Little Endian)
  * axe_min_valut  = 2 signed bytes (Little Endian)
  *
  * VL_SetGraph(string_name1,color1,string_name2,color2,stringa_name3,color3): Set name and color for data series 1,2,3
  * 0x55 0xAA STX 0x22 0x06 s1 c1 s2 c2 s3 c3 crc
  * string_name = ascii_string+0x00 termination included (max 10+1 chars)
  * color codes are the same of SetForeColor()
  *
  * VL_SetGraph2(string_name4,color4,string_name5,color5,stringa_name6,color6): Set name and color for data series 4,5,6
  * 0x55 0xAA STX 0x22 0x06 s4 c4 s5 c5 s6 c6 crc
  * string_name = ascii_string+0x00 termination included (max 10+1 chars)
  * color codes are the same of SetForeColor()
  *
  * VL_DatoGraph(series,valueX,valueY) : Set values X,Y values for the indicated series
  * 0x55 0xAA STX 0x23 0x05 series valueX valueY crc ETX
  * series: 0=series1, 1=series2, 2=series3, etc.
  * valueX = 2 bytes unsigned (Little Endian)
  * valueY = 2 bytes signed (Little endian)
  * If dataX = 0, X axe automatically increment of a step equal to <x_axe_resolution>, otherwise data will be drawn where indicated
  *
  * After a VL_Puts() the cursor is automatically incremented to the next horizontal free position
  * there is no control about horizontal overflow
  *
  * Graphic series1 (index 0) is the trigger for horizontal scrolling of the graphic area
  *
  * After a VL_Cleargraph() it is necessary to recall VL_SetGraph() and VLInitGraph()
  *
  * To install Virtual LCD in your software remember to
  *
  * 1. Call VL_timer_expired() in a TickTimer_interrupt_service_routine
  *
  * 2. Call VL_Rx() in a Uart_rx_char_service_routine
  * void vlcd_uart_callback (uart_callback_args_t * p_args)
  * {
  *     if (p_args->channel)
  *     {
  *         switch (p_args->event)
  *        {
  *             case UART_EVENT_RX_CHAR:
  *             VL_Rx((uint8_t)p_args->data);
  *             break;
  *         ....
  * }
  *
  * 3. Call VL_Init(); in the Main Program after peripherals initialisation (uart, time, etc.)
  * and before using any of the VL_xxxx functions();
  * */
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

#define	VL_MODOTX		VL_INTERRUPT	// VL_POLLING or VL_INTERRUPT: Polling Tx or interrupt Tx


/* Define Global variables -------------------------------------------------- */

static uint8_t VLrxBuf[VL_LRXBUF];      // Receive Buffer
static volatile uint8_t VLrxIdx;        // Rx Buffer index

static uint8_t VLtxBuf[VL_LTXBUF];		// Transmit Buffer
static volatile uint8_t VLtxTout;		// Tx Packet Timeout

static uint8_t VLtxData[VL_LTXBUF];		// Tx Packet Buffer
static uint8_t VLlenTxData;				// Tx Packet Length
static uint8_t VLcrc;					// Crc
static volatile uint8_t VLrxTout;		// Rx Packet Timeout

static uint8_t VLcursRow;				// Cursor Row
static uint8_t VLcursCol;				// Cursor column

static volatile uint8_t key;

volatile uint8_t VLflagTxRun;           // 1 = Tx running 0 = no Tx or Tx end


/* Low Level functions -------------------------------------------------------*/

/**
  * @brief  Timeout manage
  * @param  param, TickTimer period in msec
  * @retval None
  */

void VL_timer_expired(uint32_t param)
{
 if (VLtxTout >= param) VLtxTout -= param;  // Tx Timeout
 else VLtxTout = 0;

 if (VLrxTout >= param) VLrxTout -= param;  // Rx Packet Timeout
 else VLrxTout = 0;
}


/**
  * @brief  Packet Rx State machine (interrupt)
  * @param  dat, Uart rx data
  * @retval None
  * @note   if VLrxIdx >= 4 means valid Rx packet
  */

void VL_Rx(uint8_t dat)
{
 if (VLrxTout == 0 && VLrxIdx) VLrxIdx = 0;	// If Rx packet Timeout, reset Rx protocol
 switch (VLrxIdx)
 {
	case 0:
		if (dat == STX) 
		{
			VLrxBuf[VLrxIdx++] = dat;
			VLrxTout = VL_TOUT_RX;
		}
		break;

	case 1:
		if (dat == VL_CMD_KEYB) VLrxBuf[VLrxIdx++] = dat;
		break;
 
   case 2:
		VLrxBuf[VLrxIdx++] = dat;
		break;
		
	case 3:
		VLrxBuf[VLrxIdx] = dat;
		dat = 1;
		dat += VLrxBuf[0];
		dat += VLrxBuf[1];
		dat += VLrxBuf[2];
		if (dat == VLrxBuf[VLrxIdx]) VLrxIdx++; // Crc ok
		else VLrxIdx = 0;						// Rx Protocol Reset
		break;

	default:
		break;
 }
}


/* Funzioni principali ------------------------------------------------------- */

/**
  * @brief  VirtualLCD initialisation
  * @param  none
  * @retval None
  * @note   Reset Tx and Rx buffer indexes, Rx interrupt enabled,
  * @note   Uart peripheral, Tx and Rx port pins and baud rate must be initialised in the Main Program
  */
void VL_Init (void)
{
 VLrxIdx = 0; 
 VLflagTxRun = 0;
 VLlenTxData = 0;

 UART0enable_UserRx();
}


/**
  * @brief  Send command on Uart port
  * @param  len, packet length
  * @retval None
  * @note   inp: VLtxData[] command packet without headers and crc
  * @note   out: Tx packet
  * @note   out: VLtxIdx = 0 at Tx packet end
  */
void VL_Send (uint8_t len)
{
 uint16_t i;

 VLtxTout = VL_TOUT_TX;						// Tx Timeout (no infinite loop)
 
 while (VLflagTxRun && VLtxTout);			// Wait until timeout expired or Tx Buffer busy...
 
 VLtxBuf[0] = HD1;							// Preparing Tx buffer
 VLtxBuf[1] = HD2;
 VLtxBuf[2] = STX;
 VLcrc = 1 + STX;
 for (i=0; i< len; i++) 					// Copy Command code+payload
 {
	VLtxBuf[3+i] = VLtxData[i];
	VLcrc += VLtxData[i];	
 }
 VLtxBuf[3+i] = VLcrc;
 VLlenTxData = len + 4;						// Total packet length

 UART0sendMsgPolling (VLtxBuf, VLlenTxData);// Send msg in polling
 VLflagTxRun = 0;							// Reset Tx busy flag
}


/**
  * @brief  LCD claer
  * @param  None
  * @retval None
  */
void VL_Clear (void)
{
 VLcursRow = 0;
 VLcursCol = 0;
 VLtxData[0] = VL_CMD_CLEAR;
 VLtxData[1] = 0;
 VL_Send(2);
}


/**
  * @brief  Set cursor in the selected row/column
  * @param  row, row index
  * @param  col, column index
  * @retval None
  */
void VL_Curs (uint8_t row, uint8_t col)
{
 VLcursRow = row;
 VLcursCol = col;
 VLtxData[0] = VL_CMD_CURS;
 VLtxData[1] = 2;
 VLtxData[2] = row;
 VLtxData[3] = col;
 VL_Send(4);
}


/**
  * @brief  Display Cursor Enable
  * @param  None
  * @retval None
  */
void VL_EnableCurs (void) 
{
 VLtxData[0] = VL_CMD_ENACURS;
 VLtxData[1] = 0;
 VL_Send(2);
}


/**
  * @brief  Display Cursor Disable
  * @param  None
  * @retval None
  */
void VL_DisableCurs (void) 
{
 VLtxData[0] = VL_CMD_DISCURS;
 VLtxData[1] = 0;
 VL_Send(2);
}


/**
  * @brief  Set Text color
  * @param  n, color code
  * @retval None
  */
void VL_SetForeColor(uint8_t n)
{
 VLtxData[0] = VL_CMD_SFCOL;
 VLtxData[1] = 1;
 VLtxData[2] = n;
 VL_Send(3);
}


/**
  * @brief  Scrolling Display Clear
  * @param  None
  * @retval None
  */
void VL_SwClear (void)
{
 VLtxData[0] = VL_CMD_SWCLEAR;
 VLtxData[1] = 0;
 VL_Send(2);
}


/**
  * @brief  Text Display Send string
  * @param  s, pointer to ASCII string to display
  * @retval None
  */
void VL_Puts (uint8_t *s)
{
 uint8_t len, i, dat;

 len = (uint8_t)strlen((const char*)s) + 1;
 VLtxData[0] = VL_CMD_PUTS;
 VLtxData[1] = len;
 for (i = 0; i < len; i++) 
 {
	VLtxData[i+2] = *s; 
	s++;
 }
 VL_Send(len+2);
 dat = VLcursCol+len-1;  
 if (dat >= VL_LROW)										// Cursor column overflow
 {
	if (VLcursRow == VL_LCOL)  dat = VL_LROW -1;			// If Cursor display overflow, set it to the last row/column
	else													// else set next row
	{
		dat = 0;
		VLcursRow++;
	}
 }
 VL_Curs(VLcursRow,dat);						            // Cursor increment in Horizontal (column) only
}


/**
  * @brief  Scrolling Display Send string
  * @param  s, pointer to ASCII string to display
  * @retval None
  */
void VL_SwPuts (uint8_t *s)
{
 uint8_t len, i;

 len = strlen((const char*)s) + 1;
 VLtxData[0] = VL_CMD_SWPUTS;
 VLtxData[1] = len;
 for (i = 0; i < len; i++) 
 {
	VLtxData[i+2] = *s; 
	s++;
 }
 VL_Send(len+2);
}


/**
  * @brief  Graphic Area Clear
  * @param  None
  * @retval None
  * @note   After VL_ClearGraph () is mandatory to (re)call  VL_SetGraph() and  VLInitGraph()
  */
void VL_ClearGraph (void)
{
 VLtxData[0] = VL_CMD_GRAPHCLR;
 VLtxData[1] = 0;
 VL_Send(2);

}


/**
  * @brief  Graphic Area exes config
  * @param  name_axisX, horiziontal axis name (ascii string)
  * @param  max_X, horizontal axis maximum value
  * @param  resol_X, horiziontal axis resolution interval
  * @param  name_axisY, vertical axis name (ascii string)
  * @param  max_Y, vertical axis maximum value
  * @param  min_Y, vertical axis minimum value
  * @retval None
  * @note   The total length of name_axisX and name_axisY must not exceed 40 chars
  */
void VL_InitGraph (uint8_t *name_axisX, uint16_t max_X, uint16_t resol_X, uint8_t *name_axisY, uint16_t max_Y, int16_t min_Y)
{
 uint8_t i;

 VLtxData[0] = VL_CMD_GRAPHINIT;
 i = 2;
 while (*name_axisX) VLtxData[i++] = *name_axisX++; 
 VLtxData[i++] = 0x00;
 VLtxData[i++] = (uint8_t) max_X;
 VLtxData[i++] = (uint8_t) (max_X >> 8);
 VLtxData[i++] = (uint8_t) resol_X;
 VLtxData[i++] = (uint8_t) (resol_X >> 8);
 while (*name_axisY) VLtxData[i++] = *name_axisY++;
 VLtxData[i++] = 0x00;
 VLtxData[i++] = (uint8_t) max_Y;
 VLtxData[i++] = (uint8_t) (max_Y >> 8);
 VLtxData[i++] = (uint8_t) min_Y;
 VLtxData[i++] = (uint8_t) (min_Y >> 8);
 VLtxData[1] = i;
 VL_Send(i+2);
}


/**
  * @brief  Graphic Area data series name and color
  * @param  name1,  1st data series name (ascii string)
  * @param  color1, 1st data series color code
  * @param  name2,  2nd data series name (ascii string)
  * @param  color2, 2nd data series color code
  * @param  name3,  3rd data series name (ascii string)
  * @param  color3, 3rd data series color code
  * @retval None
  * @note   The total length of name1, name2, name3 must not exceed 40 chars
  */
void VL_SetGraph (uint8_t *name1, uint8_t color1, uint8_t *name2, uint8_t color2, uint8_t *name3, uint8_t color3)
{
 uint8_t i;

 VLtxData[0] = VL_CMD_GRAPHSET;
 i = 2;
 while (*name1) VLtxData[i++] = *name1++; 
 VLtxData[i++] = 0x00;
 VLtxData[i++] = color1;
 while (*name2) VLtxData[i++] = *name2++; 
 VLtxData[i++] = 0x00;
 VLtxData[i++] = color2;
 while (*name3) VLtxData[i++] = *name3++; 
 VLtxData[i++] = 0x00;
 VLtxData[i++] = color3;
 VLtxData[1] = i;
 VL_Send(i+2);
}


/**
  * @brief  Graphic Area data series name and color
  * @param  name4,  4th data series name (ascii string)
  * @param  color4, 4th data series color code
  * @param  name5,  5th data series name (ascii string)
  * @param  color5, 5th data series color code
  * @param  name6,  6th data series name (ascii string)
  * @param  color6, 6th data series color code
  * @retval None
  * @note   The total length of name4, name5, name6 must not exceed 40 chars
  */
void VL_SetGraph2 (uint8_t *name4, uint8_t color4, uint8_t *name5, uint8_t color5, uint8_t *name6, uint8_t color6)
{
 uint8_t i;

 VLtxData[0] = VL_CMD_GRAPHSET2;
 i = 2;
 while (*name4) VLtxData[i++] = *name4++; 
 VLtxData[i++] = 0x00;
 VLtxData[i++] = color4;
 while (*name5) VLtxData[i++] = *name5++; 
 VLtxData[i++] = 0x00;
 VLtxData[i++] = color5;
 while (*name6) VLtxData[i++] = *name6++; 
 VLtxData[i++] = 0x00;
 VLtxData[i++] = color6;
 VLtxData[1] = i;
 VL_Send(i+2);
}

/**
  * @brief  Set X and Y axis value for the selected data series
  * @param  series,  series index 0,1,2,3,4,5
  * @param  valX, 0 = auto increment from the previous value, n = set dot on 'n' position of X axis
  * @param  valY, n = set dot on n position of Y axis
  * @retval None
  * @note   None
  */
void VL_DatoGraph (uint8_t series, uint16_t valX, signed int valY)
{
 VLtxData[0] = VL_CMD_GRAPHDAT;
 VLtxData[1] = 5;
 VLtxData[2] = series;
 VLtxData[3] = (uint8_t) valX;
 VLtxData[4] = (uint8_t) (valX >> 8);
 VLtxData[5] = (uint8_t) valY;
 VLtxData[6] = (uint8_t) (valY >> 8);
 VL_Send(7);
}


/**
  * @brief  Check if there is a key pressed Rx packet
  * @param  None
  * @retval 0 = not pressed, 1 = key pressed
  * @note   None
  */
uint8_t VL_IsKey (void)
{
  if (VLrxIdx >= 4) return (1);
  return (0);
}


/**
  * @brief  Return the code of the pressed key
  * @param  None
  * @retval Key code
  * @note   None
  */
uint8_t VL_GetKey (void)
{
 uint8_t dat;

	dat = VLrxBuf[2];
	VLrxIdx = 0;
	return (dat);
}


/**
  * @brief  Blocking Wait for a key to be pressed
  * @param  None
  * @retval Key code
  * @note   None
  */
uint8_t VL_WaitKey (void)
{
 while (!VL_IsKey());
 return (VL_GetKey());	
}


/**
  * @brief  Gets an unsigned 8-bit integer value
  * @param  par = 0, accepts 3 integer digits + CR with mandatory entry (no empty CR)
  * @param  par = 1, accepts 2 hexadecimal digits + CR with mandatory entry (no empty CR)
  * @retval 8-bit unsigned value
  * @note   None
  */
uint8_t VL_GetByteValue (uint8_t par)
{
 uint8_t i;
 uint8_t kb[8];
 uint8_t kk[2];
 uint16_t byDat;

 i = 0;
 key = 0;
 while(key != K_CR)
 {
	key = VL_WaitKey();
	if (i && key == K_DEL)											// Delete last digit
	{
		i--;
		kb[i] = 0x00;
		kk[0] = ' ';
		kk[1] = 0x00;
		VLcursCol--;
		VL_Curs(VLcursRow,VLcursCol);
		VL_Puts(kk);
		VLcursCol--;
		VL_Curs(VLcursRow,VLcursCol);	}
	else
	{
		if (i == 0 && key == K_CR) key = 0;							// Empty CR not allowed
		if (par == 0 && i < 3 && (key >= '0' && key <= '9'))		// Accepts a maximum of 3 numeric digits
		{
			kb[i++] = key;
			kk[0] = key;
			kk[1] = 0x00;
			VL_Puts(kk);	// Send digit to the Text Display
		}
		if (par == 1 && i < 2 && ((key >= '0' && key <= '9') || key == 'A' || key == 'a'  ||
											key == 'B' || key == 'b'  || key == 'C' || key == 'c'  ||
											key == 'D' || key == 'd'  || key == 'E' || key == 'e'  ||
											key == 'F' || key == 'f'    ))	// Accepts a maximum of 2 hex. digits
		{
			kb[i++] = key;
			kk[0] = key;
			kk[1] = 0x00;
			VL_Puts(kk);	// Send digit to the Text Display
		}
	}

 }
 kb[i] = 0x00;			    // Replace CR with a 0x00
 if      (par == 0)  byDat = (uint8_t) atoi((const char*)kb);		// Converts string to number
 else if (par == 1)	 sscanf((const char*)kb,"%2x",&byDat);

 return (byDat);
}


/**
  * @brief  Gets an unsigned 16-bit integer value
  * @param  par = 0, accepts 5 integer digits + CR with mandatory entry (no empty CR)
  * @param  par = 1, accepts 4 hexadecimal digits + CR with mandatory entry (no empty CR)
  * @retval 16-bit unsigned Value
  * @note   None
  */
uint16_t VL_GetWordValue (uint8_t par)
{
 uint8_t i;
 uint8_t kb[8];
 uint8_t kk[2];
 uint16_t wDat;

 i = 0;
 key = 0;
 while(key != K_CR)										
 {
	key = VL_WaitKey();
	if (i && key == K_DEL)											// Delete last digit
	{
		i--;
		kb[i] = 0x00;
		kk[0] = ' ';
		kk[1] = 0x00;
		VLcursCol--;
		VL_Curs(VLcursRow,VLcursCol);
		VL_Puts(kk);
		VLcursCol--;
		VL_Curs(VLcursRow,VLcursCol);	}
	else
	{
		if (i == 0 && key == K_CR) key = 0;							// Empty CR not allowed
		if (par == 0 && i < 5 && (key >= '0' && key <= '9'))	    // Accepts a maximum of 5 numeric digits
		{
			kb[i++] = key;	
			kk[0] = key;
			kk[1] = 0x00;
			VL_Puts(kk);	// Send digit to the Text Display
		}
		if (par == 1 && i < 4 && ((key >= '0' && key <= '9') || key == 'A' || key == 'a'  ||
											key == 'B' || key == 'b'  || key == 'C' || key == 'c'  ||
											key == 'D' || key == 'd'  || key == 'E' || key == 'e'  ||
											key == 'F' || key == 'f'    ))	// Accetto solo 4 cifre esadecimali
		{
			kb[i++] = key;	
			kk[0] = key;
			kk[1] = 0x00;
			VL_Puts(kk);	// Send digit to the Text Display
		}
	}

 }
 kb[i] = 0x00;			    // Replace CR with a 0x00
 if      (par == 0)  wDat = (uint16_t) atoi((const char*)kb);		// Converts string to number
 else if (par == 1)	 sscanf((const char*)kb,"%4x",&wDat);

 return (wDat);	
}


/**
  * @brief  Gets a signed 32-bit integer value
  * @param  sign = 0, accepts 10 integer digits + CR with mandatory entry (no empty CR)
  * @param  sign = K_MINUS, accepts also negative values
  * @retval 32-bit signed value
  * @note   None
  */
signed long VL_GetIntValue (uint8_t sign)
{
 uint8_t i;
 uint8_t kb[12];
 uint8_t kk[2];
 signed long lDat;

 i = 0;
 key = 0;
 while(key != K_CR)
 {
	key = VL_WaitKey();
	if (i && key == K_DEL)									// Delete last digit
	{
		i--;
		kb[i] = 0x00;
		kk[0] = ' ';
		kk[1] = 0x00;
		VLcursCol--;
		VL_Curs(VLcursRow,VLcursCol);
		VL_Puts(kk);
		VLcursCol--;
		VL_Curs(VLcursRow,VLcursCol);
	}
	else
	{
		if (i == 0 && key == K_CR) key = 0;					// Empty CR not allowed
		if (i < 10 && ((key >=  '0' && key <= '9') || 		// Accepts a maximum of 10 numeric digits with
					   (key == sign && i == 0))) 			// minus '-' in first position
		{
			kb[i++] = key;		
			kk[0] = key;
			kk[1] = 0x00;
			VL_Puts(kk);					// Send digit to the Text Display
		}
	}
 }
 kb[i] = 0x00;								// Replace CR with a 0x00
 lDat = (signed long)atoi((const char*)kb);	// Converts string to number
 return (lDat);	
}


/**
  * @brief  Gets a signed floatr value
  * @param  sign = 0, accepts 16 integer digits + CR with mandatory entry (no empty CR)
  * @param  sign = K_MINUS, accepts also negative values
  * @retval single precision 32-bit float value
  * @note   None
  */
float VL_GetFloatValue (uint8_t sign)
{
 uint8_t i;
 uint8_t kb[18];
 uint8_t kk[2];
 float flDat;

 i = 0;
 key = 0;
 while(key != K_CR)
 {
	key = VL_WaitKey();
	if (i && key == K_DEL)									// Delete last digit
	{
		i--;
		kb[i] = 0x00;
		kk[0] = ' ';
		kk[1] = 0x00;
		VLcursCol--;
		VL_Curs(VLcursRow,VLcursCol);
		VL_Puts(kk);
		VLcursCol--;
		VL_Curs(VLcursRow,VLcursCol);
	}
	else
	{
		if (i == 0 && key == K_CR) key = 0;					// Empty CR not allowed
		if (i < 16 && ((key >= '0' && key <= '9') || 	    // Accepts a maximum of 10 numeric digits with
			 (key == sign && i == 0)   ||					// minus '-' in first position
			 (key == K_DOT && i ))) 					    // decimal dot '.' not allowed in first position
		{
			kb[i++] = key;		
			kk[0] = key;
			kk[1] = 0x00;
			VL_Puts(kk);	    // Send digit to the Text Display
		}
	}
 }
 kb[i] = 0x00;			        // Replace CR with a 0x00
 flDat = atof((const char*)kb);	// Converts string to number
 return (flDat);	
}


/**
  * @brief  Gets an alphanumeric string + CR with mandatory entry (no empty CR)
  * @param  lmax = maximum string length (excluding the ternminator char) accepts 16 integer digits + CR with mandatory entry (no empty CR)
  * @param  p    = pointer to input ascii string of length lmax+1 (0x00 terminato char)
  * @retval None
  * @note   Maximum string length must not exceed VL_LSTR
  */
void VL_GetString (uint8_t lmax, uint8_t *p)
{
 uint8_t i;
 uint8_t kk[2];
 
 i = 0;
 key = 0;
 lmax++;                                            // Increment lmax to add the terminator 0x00
 if (lmax == 0 || lmax > VL_LSTR) lmax = VL_LSTR;
 while(key != K_CR)
 {
	key = VL_WaitKey();
	if (i && key == K_DEL)							// Delete last char
	{
		i--;
	   p--;
		*p = 0x00;
		kk[0] = ' ';
		kk[1] = 0x00;
		VLcursCol--;
		VL_Curs(VLcursRow,VLcursCol);
		VL_Puts(kk);
		VLcursCol--;
		VL_Curs(VLcursRow,VLcursCol);
	}
	else
	{
		if (i == 0 && key == K_CR) key = 0;		    // Empty CR not allowed
		if (i < lmax)
		{
			i++;
			*p++ = key;		
			kk[0] = key;
			kk[1] = 0x00;
			if (kk[0] != K_CR) VL_Puts(kk);		    // Send string to the Text Display (CR excluded)
		}
	}
 }
 if (i <= lmax) p--;
 *p = 0x00;				                            // Replace CR with 0x00 to obtain an ascii string
}


/**
  * @brief  Gets an optional alphanumeric string (empty CR allowed, ESC allowed )
  * @param  lmax = maximum string length (excluding the ternminator char) accepts 16 integer digits
  * @param  p    = pointer to input ascii string of length lmax+1 (0x00 terminato char)
  * @retval String length
  * @note   if exit after an ESC or empty CR the string destination buffer is not modified
  */
uint8_t VL_GetOptString (uint8_t lmax, uint8_t *p)
{
 uint8_t i;
 uint8_t kk[2];
 
 i = 0;
 key = 0;
 //if (lmax == 0 || lmax > VL_LSTR) lmax = VL_LSTR;
 while(key != K_CR )
 {
	key = VL_WaitKey();
 	if (i && key == K_DEL)							// Delete last char
	{
   		i--;
	    p--;
		*p = 0x00;
		kk[0] = ' ';
		kk[1] = 0x00;
		VLcursCol--;
		VL_Curs(VLcursRow,VLcursCol);
		VL_Puts(kk);
		VLcursCol--;
		VL_Curs(VLcursRow,VLcursCol);
	}
	else
	{
		if (key == K_ESC) return(0);				// if ESC, exit from routine
		if (key == K_CR && i == 0) return(1);	    // if CR, exit from routine (empty filed allowed)
		if (i < lmax)
		{
			i++;
			*p++ = key;		
			kk[0] = key;
			kk[1] = 0x00;
			if (kk[0] != K_CR) VL_Puts(kk);		    // Send string to Text Display
		}
	}
 }
 if (i <= lmax) {p--; i--;}
 *p = 0x00;				                            // Replace CR with 0x00 to obtain an ascii string
 return(i+1);
}

/*EOF*/
