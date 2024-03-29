/*-----------------------------------------------------------------------------
* @file     | UPDFW_ITE.H
*-----------+-----------------------------------------------------------------
* @function | UPDFW_ITE.C Function prototype include definition
*-----------+-----------------------------------------------------------------
* @model    | ITE Embedded Controller Firmware
* @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
* @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
* @note     | Copyright(c)2010-2021, ITE Tech. Inc. All rights reserved.
*---------------------------------------------------------------------------*/
#ifndef __UPDFW_ITE_H
#define __UPDFW_ITE_H

/*-----------------------------------------------------------------------------
 * External Resources Prototype
 *---------------------------------------------------------------------------*/
//0extern XBYTE    xPD1_i2c_addr;

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/

#define _ITE_I2C_READ_SPI_SIZE      0x10
#define _ITE_I2C_WRITE_SPI_SIZE     0x10
#define _SKIP_SIGN                  0
#define _PROG_SIGN                  1

#define _ITE_PD1_FLASH_I2C_ADDR     0x40<<1
#define _ITE_PD2_FLASH_I2C_ADDR     0x42<<1

#define _ITE_PD1_I2C_ADDR	      	0x4C<<1
#define _ITE_PD2_I2C_ADDR		    0x4E<<1

#define EC_PD1_WrToRdStream EC_PD_CH0_WrToRdStream
#define EC_PD2_WrToRdStream EC_PD_CH0_WrToRdStream

/*-----------------------------------------------------------------------------
 * Data Type & Data Structure Prototype
 *---------------------------------------------------------------------------*/
enum ITE_FLASH_STEP
{
    _ITE_FLASH_ERASE_1K     = 1,
    _ITE_FLASH_LOAD_BIN256B = 2,
    _ITE_FLASH_WRITE_256B   = 3,
    _ITE_FLASH_VERIFY_256B  = 4,
    _ITE_FLASH_WRITE_SIG    = 5,
    _ITE_FLASH_VERIFY_SIG   = 6,
    _ITE_FLASH_READ_SIG     = 7,
    _ITE_FLASH_EXITFOLLOW   = 8,
    _ITE_FLASH_WDT          = 9,
    _ITE_FLASH_FINISH       = 10,
};

enum I2SPI_CMD_TABLE
{
    _SPI_CMD_READ_ID        = 0x02,
    _SPI_CMD_WRITE_ENABLE   = 0x04,
    _SPI_CMD_WRITE_DISABLE  = 0x05,
    _SPI_CMD_SECTOR_ERASE   = 0x06,
    _SPI_CMD_CHIP_ERASE     = 0x07,
    _SPI_CMD_READ_STATUS    = 0x09,
    _SPI_CMD_QUAL_DT_READ   = 0x13,
    _SPI_CMD_AAIW_PROGRAM   = 0x16
};

enum ITE_UPD_APP_CMD
{
    _ITE_UPD_APP_GET_BUF_ADDR       = 0xC0,
    _ITE_UPD_APP_GET_FW_VER         = 0xC1,    
    _ITE_UPD_APP_SPECIAL_WAVE       = 0xC2, 
    _ITE_UPD_APP_STOP_CPU           = 0xC3,     
    _ITE_UPD_APP_ENTER_FOLLOW_MODE  = 0xC4,    
    _ITE_UPD_APP_EXIT_FOLLOW_MODE   = 0xC5,    
    _ITE_UPD_APP_SECTOR_ERASE       = 0xC6,    
    _ITE_UPD_APP_WRITE_256B         = 0xC7,   
    _ITE_UPD_APP_VERIFY_256B        = 0xC8, 
    _ITE_UPD_APP_WRITE_SIGN         = 0xC9,
    _ITE_UPD_APP_VERIFY_SIGN        = 0xCA,     
    _ITE_UPD_APP_CMD_CB             = 0xCB,  
    _ITE_UPD_APP_CMD_CC             = 0xCC,      
    _ITE_UPD_APP_REG_READ           = 0xCD,
    _ITE_UPD_APP_REG_WRITE          = 0xCE,
    _ITE_UPD_APP_CMD_CF             = 0xCF,
    _ITE_UPD_APP_Finish             = 0xD0,  
};


//*****************************************************************************
/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
//*****************************************************************************
extern BYTE ITEi2c_FlashProgress(BYTE PdI2cAddr);
extern void ITE_PD_FlashUtility(void);
extern BYTE ITEi2c_TurnOn_5V(void);							   
extern BYTE ITEi2c_TurnOff_5V(void);
extern BYTE PDFW_GetVersion(void);


BYTE EC_PD_CH0_WrToRdStream(BYTE I2C_Addr, XBYTE *Var, BYTE WrLen, BYTE WrDly,
                        XBYTE *Var2, BYTE RdLen);
BYTE EC_PD_CH1_WrToRdStream(BYTE I2C_Addr, XBYTE *Var, BYTE WrLen, BYTE WrDly,
                        XBYTE *Var2, BYTE RdLen);
BYTE EC_PD_CH2_WrToRdStream(BYTE I2C_Addr, XBYTE *Var, BYTE WrLen, BYTE WrDly,
                        XBYTE *Var2, BYTE RdLen);
BYTE EC_PD_CH3_WrToRdStream(BYTE I2C_Addr, XBYTE *Var, BYTE WrLen, BYTE WrDly,
                        XBYTE *Var2, BYTE RdLen);

//-----------------------------------------------------------------------------
#endif  //__UPDFW_ITE_H
/*-----------------------------------------------------------------------------
 * End of UPDFW_ITE.H */