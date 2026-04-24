/**
  ******************************************************************************
  * @file           : virtuallcd.h
  * @brief          : Header for virtuallcd file.
  * @note			: Project code 82037801
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
#ifndef VIRTUALLCD_H_
#define VIRTUALLCD_H_

//#include "typedefine.h"

#define		VL_LROW				40			// Display Rows
#define		VL_LCOL				20			// Display Columns

#define		VL_POLLING			0			// Polling tx
#define		VL_INTERRUPT		1			// Interrupt tx

#define		VL_LRXBUF			8			// Rx Buffer length
#define 	VL_LTXBUF			64			// Tx Buffer length

#define 	VL_LSTR				30			// Maximun string length

#define 	HD1					0x55		// special characters
#define 	HD2					0xAA
#define		STX					0x02
#define		K_F1				0x0E
#define		K_F2				0x0F
#define		K_F3				0x10
#define		K_F4				0x11
#define		K_F5				0x12
#define		K_F6				0x13
#define		K_F7				0x14
#define		K_F8				0x15
#define 	K_CR				0x0D
#define 	K_DEL				0x08
#define		K_PLUS				'+'
#define		K_MINUS				'-'
#define     K_SLASH				'/'
#define     K_BACKSLASH			0x5C		// '\'
#define     K_ASTERISK			'*'
#define		K_COMM				','
#define		K_DOT				'.'
#define		K_COLON				':'
#define		K_SEMICOLON			';'
#define		K_UNDER				'_'
#define		K_EQUAL				'='
#define		K_AT				'@'
#define		K_PIPE				'|'
#define		K_ESC				0x1B
#define		K_PGUP				0x21
#define		K_PGDW				0x22
#define		K_LEFT				0x25
#define		K_UP				0x26
#define		K_RIGHT				0x27
#define		K_DOWN				0x28

#define     K_EXCLAMATION       '!'
#define     K_QUOTATION         '"'
#define     K_HASH              '#'
#define     K_DOLLAR            '$'
#define     K_PERCENT           '%'
#define     K_AMPERSAND         '&'
#define     K_QUOTE             0x60        // '
#define     K_LRBRACKET         '('
#define     K_RRBRACKET         ')'
#define     K_LANGLE            '<'
#define     K_RANGLE            '>'
#define     K_QUESTION          '?'
#define     K_LSBRACKET         '['
#define     K_RSBRACKET         ']'
#define     K_LBRACE            '{'
#define     K_RBRACE            '}'
#define     K_TILDE             '~'
#define     K_RANGLE            '>'
#define     K_CARET             '^'

#define 	VL_CMD_CLEAR		0x01		// Serial Protocol commands
#define 	VL_CMD_CURS			0x02
#define 	VL_CMD_ENACURS		0x03
#define 	VL_CMD_DISCURS		0x04
#define 	VL_CMD_SFCOL		0x05
#define 	VL_CMD_PUTS			0x06
#define 	VL_CMD_SWCLEAR		0x07
#define 	VL_CMD_SWPUTS		0x08
#define 	VL_CMD_KEYB			0x10
#define 	VL_CMD_GRAPHCLR		0x20
#define 	VL_CMD_GRAPHINIT	0x21
#define 	VL_CMD_GRAPHSET		0x22
#define 	VL_CMD_GRAPHDAT		0x23
#define 	VL_CMD_GRAPHSET2	0x24

#define		BLACK				0		// Color codes
#define		BLUE				1
#define		GREEN				2
#define		YELLOW				3
#define		RED					4
#define		MAGENTA				5
#define		BROWN				6
#define		GREY				7
#define		CYAN				8
#define		ORANGE				9

#define		VL_TOUT_TX			100     // Tx send packet Timeout [msec]
#define		VL_TOUT_RX			50		// Rx packet Timeout [msec]

#define		VL_RXQUEUE_LEN		5		// Rx queue length


/* Prototypes ----------------------------------------------------------------*/

void    VL_timer_expired(uint32_t param);
void 	VL_Rx(uint8_t dat);
void 	VL_Init (void);
void 	VL_Send (uint8_t len);
void 	VL_Clear (void);
void 	VL_Curs (uint8_t row, uint8_t col);
void 	VL_EnableCurs (void);
void 	VL_DisableCurs (void);
void 	VL_SetForeColor(uint8_t n);
void 	VL_SwClear (void);
void 	VL_Puts (uint8_t *s);
void 	VL_SwPuts (uint8_t *s);
void 	VL_ClearGraph (void);
void 	VL_InitGraph (uint8_t *name_axisX, uint16_t max_X, uint16_t resol_X, uint8_t *name_axisY, uint16_t max_Y, int16_t min_Y);
void 	VL_SetGraph (uint8_t *name1, uint8_t color1, uint8_t *name2, uint8_t color2, uint8_t *name3, uint8_t color3);
void 	VL_SetGraph2 (uint8_t *name4, uint8_t color4, uint8_t *name5, uint8_t color5, uint8_t *name6, uint8_t color6);
void 	VL_DatoGraph (uint8_t series, uint16_t valX, signed int valY);
uint8_t VL_IsKey (void);
uint8_t VL_GetKey (void);
uint8_t VL_WaitKey (void);
uint8_t VL_GetByteValue (uint8_t par);
uint16_t    VL_GetWordValue (uint8_t par);
signed long VL_GetIntValue (uint8_t sign);
float 	VL_GetFloatValue (uint8_t sign);
void 	VL_GetString (uint8_t lmax, uint8_t *p);
uint8_t VL_GetOptString (uint8_t lmax, uint8_t *p);

#endif /* VIRTUALLCD_H_ */
/*EOF*/
