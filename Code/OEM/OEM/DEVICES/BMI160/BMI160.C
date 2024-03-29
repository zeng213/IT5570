/*-----------------------------------------------------------------------------
 * @file     | BOSCH_BMI160.C
 *-----------+-----------------------------------------------------------------
 * @function | BOSCH_BMI160
 *-----------+-----------------------------------------------------------------
 * @model    | Sensors
 * @version  | 1.0.0.0
 * @author   | ec.Michael.Kuo@gmail.com
 * @note     | Copyright(c)2016-2016, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
// Include all header file
#include "..\include.h"


/*-----------------------------------------------------------------------------
 * Local Parameter Definition
 *---------------------------------------------------------------------------*/
#define DEBUG_BOSCH_BMI160      TRUE

/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_BOSCH_BMI160
#define BMI160_RamDebug(x)      RamDebug(x)
#else
#define BMI160_RamDebug(x)      {}
#endif

/*-----------------------------------------------------------------------------
 * Local Parameter Process Definition
 *---------------------------------------------------------------------------*/

#if 1
/*-----------------------------------------------------------------------------
 * @subroutine - I2C_CH1_WrToRdStream
 * @function - I2C Channel-1 Write to Read Stream data
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
BYTE I2C_CH1_WrToRdStream(BYTE I2C_Addr, XBYTE *Var, WORD Count, BYTE WrDly,
                                    XBYTE *Var2, WORD Count2)
{
    BYTE    j, t;

    HOSTA_B = 0xFE;
    HOCTL2_B = (I2C_EN | SMHEN);
    TRASLA_B = (I2C_Addr & 0xFE);
    HOBDB_B = *Var;
    HOCTL_B = (SMbusEXT | HOCTL_SRT);

    t = 0;
    while(1)
    {
        j = HOSTA_B;
        if ((j & HOSTA_BDS) != 0x00)
        {
            Count--;
            if (Count == 0)
            {
                break;
            }
            while(1)
            {
                if (WrDly > 0)
                {
                    WrDly--;
                    WNCKR = 0x00;   /* Delay 15.26 us */
                }
                else
                {
                    break;
                }
            }
            Var++;
            HOBDB_B = *Var;
            HOSTA_B = 0xFE;
            t = 0;
            continue;
        }
        WNCKR = 0x00;   /* Delay 15.26 us */
        t++;
        if (t > 250)
        {
            HOSTA_B = 0xFE;
            HOCTL_B = HOCTL_KILL;
            HOCTL_B = 0;
            return FALSE;
        }
    }
    /* Check Write Stream Only */
    if (Count2 == 0)
    {
        HOCTL2_B = SMHEN;
        HOSTA_B = HOSTA_BDS;
        WNCKR = 0x00;
        j = HOSTA_B;
        WNCKR = 0x00;
        HOCTL_B = 0;
        return TRUE;
    }
    /* Repeat Start + Address Read */
    HOCTL2_B |= (I2C_SW_EN + I2C_SW_WAIT);
    HOSTA_B = 0xFE;
    HOCTL2_B &= (~I2C_SW_WAIT);

    if (Count2 == 0x01)  HOCTL_B |= HOCTL_LABY;

    t = 0;
    while(1)
    {
        j = HOSTA_B;
        if ((j & HOSTA_BDS) != 0x00)
        {
            Count2--;
            if (Count2 == 0)
            {
                *Var2 = HOBDB_B;
                break;
            }
            if (Count2 == 0x01)
            {
                HOCTL_B |= HOCTL_LABY;
            }
            *Var2 = HOBDB_B;
            Var2++;
            HOSTA_B = 0xFE;
            t = 0;
            continue;
        }
        WNCKR = 0x00;   /* Delay 15.26 us */
        t++;
        if (t > 250)
        {
            HOSTA_B = 0xFE;
            HOCTL_B = HOCTL_KILL;
            HOCTL_B = 0;
            return FALSE;
        }
    }
    HOCTL2_B = SMHEN;
    HOSTA_B = HOSTA_BDS;
    WNCKR = 0x00;
    j = HOSTA_B;
    WNCKR = 0x00;
    HOCTL_B = 0;
    return TRUE;
}
#endif

/*-----------------------------------------------------------------------------
 * @subroutine - BMI160_WriteRegister
 * @function - BMI160_WriteRegister
 * @upstream -
 * @input    -
 * @return   -
 * @note     -
 */
BYTE BMI160_WriteRegister(BYTE v_command, BYTE v_data)
{
    I2C_WRITE_BUFFER[0] = v_command;
    I2C_WRITE_BUFFER[1] = v_data;
    if (!I2C_CH1_WrToRdStream(0xD0,
                              &I2C_WRITE_BUFFER[0],
                              2,
                              0,
                              &I2C_READ_BUFFER[0],
                              0))
    {
        ;
    }
    return TRUE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - BMI160_ReadRegister
 * @function - BMI160_ReadRegister
 * @upstream -
 * @input    -
 * @return   -
 * @note     -
 */
BYTE BMI160_ReadRegister(BYTE v_command)
{
    I2C_WRITE_BUFFER[0] = v_command;
    if (!I2C_CH1_WrToRdStream(0xD0,
                              &I2C_WRITE_BUFFER[0],
                              1,
                              0,
                              &I2C_READ_BUFFER[0],
                              1))
    {
        ;
    }
    return I2C_READ_BUFFER[0];
}

/*-----------------------------------------------------------------------------
 * @subroutine - BMI160_set_command_register
 * @function - BMI160_set_command_register
 * @upstream -
 * @input    -
 * @return   -
 * @note     -
 */
BYTE BMI160_set_command_register(BYTE v_command)
{
    I2C_WRITE_BUFFER[0] = BMI160_CMD_COMMANDS_ADDR;
    I2C_WRITE_BUFFER[1] = v_command;
    if (!I2C_CH1_WrToRdStream(0xD0,
                              &I2C_WRITE_BUFFER[0],
                              2,
                              0,
                              &I2C_READ_BUFFER[0],
                              0))
    {
        ;
    }
    return TRUE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - BMI160_Initial
 * @function - BMI160_Initial
 * @upstream -
 * @input    -
 * @return   -
 * @note     -
 */
void BMI160_Initial(void)
{
    /* read Chip Id */
    BMI160_ReadRegister(BMI160_USER_CHIP_ID_ADDR);
    /* To avoid gyro wakeup it is required to write 0x00 to 0x6C*/
    BMI160_WriteRegister(BMI160_USER_PMU_TRIGGER_ADDR, 0x00);
    Delay1MS(30);

    /* Set the accel bandwidth as Normal */
    /*Set the accel mode as Normal write in the register 0x7E*/
    BMI160_set_command_register(ACCEL_MODE_NORMAL);
    /* bmi160_delay_ms in ms*/
    Delay1MS(30);
#if 1  //2G
    /* Selection of accelerometer g-range: +/-2G */
    BMI160_WriteRegister(BMI160_USER_ACCEL_RANGE_ADDR, 0x03);
    /* set accel data rate as 12.5 Hz*/
    BMI160_WriteRegister(BMI160_USER_ACCEL_CONFIG_ADDR, 0x25);
    Delay1MS(1);
#endif
#if 0  //4G
    /* Selection of accelerometer g-range: +/-4G */
    BMI160_WriteRegister(BMI160_USER_ACCEL_RANGE_ADDR, 0x05);
    /* set accel data rate as 12.5 Hz*/
    BMI160_WriteRegister(BMI160_USER_ACCEL_CONFIG_ADDR, 0x25);
    Delay1MS(1);
#endif
#if 0  //8G
    /* Selection of accelerometer g-range: +/-8G */
    BMI160_WriteRegister(BMI160_USER_ACCEL_RANGE_ADDR, 0x08);
    /* set accel data rate as 12.5 Hz*/
    BMI160_WriteRegister(BMI160_USER_ACCEL_CONFIG_ADDR, 0x25);
    Delay1MS(1);
#endif
#if 0  //16G
    /* Selection of accelerometer g-range: +/-16G */
    BMI160_WriteRegister(BMI160_USER_ACCEL_RANGE_ADDR, 0x0C);
    /* set accel data rate as 12.5 Hz*/
    BMI160_WriteRegister(BMI160_USER_ACCEL_CONFIG_ADDR, 0x25);
    Delay1MS(1);
#endif
    /*Set the gyro mode as Normal write in the register 0x7E*/
    BMI160_set_command_register(GYRO_MODE_NORMAL);
    /* bmi160_delay_ms in ms*/
    Delay1MS(30);
    //BMI160_WriteRegister(BMI160_USER_GYRO_RANGE_ADDR, 0x03);
    Delay1MS(1);
    /* Set the gryo bandwidth as Normal */
    /* set gyro data rate as 12.5 Hz*/
    BMI160_WriteRegister(BMI160_USER_GYRO_CONFIG_ADDR, 0x26);
    Delay1MS(1);
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of BOSCH_BMI160.C */
