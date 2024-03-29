/*-----------------------------------------------------------------------------
 * @file     | BOSCH_BMI160.H
 *-----------+-----------------------------------------------------------------
 * @function | BOSCH_BMI160
 *-----------+-----------------------------------------------------------------
 * @model    | Sensors
 * @version  | 1.0.0.0
 * @author   | ec.Michael.Kuo@gmail.com
 * @note     | Copyright(c)2016-2016, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef _BOSCH_BMI160_H_
#define _BOSCH_BMI160_H_

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/
/***************************************************************/
/**\name    BUS READ AND WRITE FUNCTION POINTERS        */
/***************************************************************/
#define BMI160_I2C_ADDR1                    (0x68)
/**< I2C Address needs to be changed */
#define BMI160_I2C_ADDR2                    (0x69)
 /**< I2C Address needs to be changed */
#define BMI160_AUX_BMM150_I2C_ADDRESS       (0x10)
/**< I2C address of BMM150*/
#define BMI160_AUX_YAS532_I2C_ADDRESS       (0x2E)
/**< I2C address of YAS532*/
#define BMI160_AUX_AKM09911_I2C_ADDR_1      (0x0C)
/**< I2C address of AKM09911*/
#define BMI160_AUX_AKM09911_I2C_ADDR_2      (0x0D)
/**< I2C address of AKM09911*/
#define BMI160_AUX_AKM09912_I2C_ADDR_1      (0x0C)
/**< I2C address of AKM09912*/
#define BMI160_AUX_AKM09912_I2C_ADDR_2      (0x0D)
/**< I2C address of AKM09912*/
#define BMI160_AUX_AKM09912_I2C_ADDR_3      (0x0E)
/**< I2C address of AKM09912*/
#define BMI160_AUX_AKM09912_I2C_ADDR_4      (0x0F)
/**< I2C address of AKM09912*/
/*******************************************/
/**\name    CONSTANTS        */
/******************************************/
#define  BMI160_INIT_VALUE                  (0)
#define  BMI160_ASSIGN_DATA                 (1)
#define  BMI160_GEN_READ_WRITE_DATA_LENGTH  (1)
#define  BMI160_MAXIMUM_TIMEOUT             (10)

/* output data rate condition check*/
#define  BMI160_OUTPUT_DATA_RATE0   (0)
#define  BMI160_OUTPUT_DATA_RATE1   (1)
#define  BMI160_OUTPUT_DATA_RATE2   (2)
#define  BMI160_OUTPUT_DATA_RATE3   (3)
#define  BMI160_OUTPUT_DATA_RATE4   (4)
#define  BMI160_OUTPUT_DATA_RATE5   (5)
#define  BMI160_OUTPUT_DATA_RATE6   (14)
#define  BMI160_OUTPUT_DATA_RATE7   (15)

/*unmap significant motion*/
#define V_ANY_MOTION_INTR_STAT   (4)
#define V_ANY_MOTION_AXIS_STAT   (7)

/* accel range check*/
#define BMI160_ACCEL_RANGE0  (3)
#define BMI160_ACCEL_RANGE1  (5)
#define BMI160_ACCEL_RANGE3  (8)
#define BMI160_ACCEL_RANGE4  (12)

/* check the status of registers*/
#define  BMI160_FOC_STAT_HIGH           (1)
#define  BMI160_SIG_MOTION_STAT_HIGH    (1)
#define  BMI160_STEP_DET_STAT_HIGH      (1)

/*condition check for reading and writing data*/
#define BMI160_MAX_VALUE_SIGNIFICANT_MOTION      (1)
#define BMI160_MAX_VALUE_FIFO_FILTER    (1)
#define BMI160_MAX_VALUE_FIFO_TIME      (1)
#define BMI160_MAX_VALUE_FIFO_INTR      (1)
#define BMI160_MAX_VALUE_FIFO_HEADER    (1)
#define BMI160_MAX_VALUE_FIFO_MAG       (1)
#define BMI160_MAX_VALUE_FIFO_ACCEL     (1)
#define BMI160_MAX_VALUE_FIFO_GYRO      (1)
#define BMI160_MAX_VALUE_SOURCE_INTR    (1)
#define BMI160_MAX_VALUE_LOW_G_MODE     (1)
#define BMI160_MAX_VALUE_NO_MOTION      (1)
#define BMI160_MAX_VALUE_TAP_SHOCK      (1)
#define BMI160_MAX_VALUE_TAP_QUIET      (1)
#define BMI160_MAX_VALUE_ORIENT_UD      (1)
#define BMI160_MAX_VALUE_ORIENT_AXES    (1)
#define BMI160_MAX_VALUE_NVM_PROG       (1)
#define BMI160_MAX_VALUE_SPI3           (1)
#define BMI160_MAX_VALUE_PAGE           (1)
#define BMI160_MAX_VALUE_I2C_WDT        (1)
#define BMI160_MAX_VALUE_SLEEP_STATE    (1)
#define BMI160_MAX_VALUE_WAKEUP_INTR    (1)
#define BMI160_MAX_VALUE_SELFTEST_SIGN  (1)
#define BMI160_MAX_VALUE_SELFTEST_AMP   (1)
#define BMI160_MAX_VALUE_SELFTEST_START (1)

#define BMI160_MAX_GYRO_WAKEUP_TRIGGER      (3)
#define BMI160_MAX_ACCEL_SELFTEST_AXIS      (3)
#define BMI160_MAX_GYRO_STEP_COUNTER        (1)
#define BMI160_MAX_GYRO_BW                  (3)
#define BMI160_MAX_ACCEL_BW                 (7)
#define BMI160_MAX_ORIENT_MODE              (3)
#define BMI160_MAX_ORIENT_BLOCKING          (3)
#define BMI160_MAX_FLAT_HOLD                (3)
#define BMI160_MAX_ACCEL_FOC                (3)
#define BMI160_MAX_IF_MODE                  (3)
#define BMI160_MAX_TARGET_PAGE              (3)
#define BMI160_MAX_GYRO_RANGE               (4)
#define BMI160_MAX_GYRO_SLEEP_TIGGER        (7)
#define BMI160_MAX_TAP_TURN                 (7)
#define BMI160_MAX_UNDER_SAMPLING           (1)
#define BMI160_MAX_UNDER_SIG_MOTION         (3)
#define BMI160_MAX_ACCEL_OUTPUT_DATA_RATE   (12)
#define BMI160_MAX_LATCH_INTR               (15)
#define BMI160_MAX_FLAT_HYST                (15)
#define BMI160_MAX_ORIENT_THETA             (63)
#define BMI160_MAX_FLAT_THETA               (63)

#ifdef FIFO_ENABLE
/* FIFO index definitions*/
#define BMI160_FIFO_X_LSB_DATA          (0)
#define BMI160_FIFO_X_MSB_DATA          (1)
#define BMI160_FIFO_Y_LSB_DATA          (2)
#define BMI160_FIFO_Y_MSB_DATA          (3)
#define BMI160_FIFO_Z_LSB_DATA          (4)
#define BMI160_FIFO_Z_MSB_DATA          (5)
#define BMI160_FIFO_R_LSB_DATA          (6)
#define BMI160_FIFO_R_MSB_DATA          (7)
/* FIFO gyro definition*/
#define BMI160_GA_FIFO_G_X_LSB      (0)
#define BMI160_GA_FIFO_G_X_MSB      (1)
#define BMI160_GA_FIFO_G_Y_LSB      (2)
#define BMI160_GA_FIFO_G_Y_MSB      (3)
#define BMI160_GA_FIFO_G_Z_LSB      (4)
#define BMI160_GA_FIFO_G_Z_MSB      (5)
#define BMI160_GA_FIFO_A_X_LSB      (6)
#define BMI160_GA_FIFO_A_X_MSB      (7)
#define BMI160_GA_FIFO_A_Y_LSB      (8)
#define BMI160_GA_FIFO_A_Y_MSB      (9)
#define BMI160_GA_FIFO_A_Z_LSB      (10)
#define BMI160_GA_FIFO_A_Z_MSB      (11)
/* FIFO mag/gyro/accel definition*/
#define BMI160_MGA_FIFO_M_X_LSB     (0)
#define BMI160_MGA_FIFO_M_X_MSB     (1)
#define BMI160_MGA_FIFO_M_Y_LSB     (2)
#define BMI160_MGA_FIFO_M_Y_MSB     (3)
#define BMI160_MGA_FIFO_M_Z_LSB     (4)
#define BMI160_MGA_FIFO_M_Z_MSB     (5)
#define BMI160_MGA_FIFO_M_R_LSB     (6)
#define BMI160_MGA_FIFO_M_R_MSB     (7)
#define BMI160_MGA_FIFO_G_X_LSB     (8)
#define BMI160_MGA_FIFO_G_X_MSB     (9)
#define BMI160_MGA_FIFO_G_Y_LSB     (10)
#define BMI160_MGA_FIFO_G_Y_MSB     (11)
#define BMI160_MGA_FIFO_G_Z_LSB     (12)
#define BMI160_MGA_FIFO_G_Z_MSB     (13)
#define BMI160_MGA_FIFO_A_X_LSB     (14)
#define BMI160_MGA_FIFO_A_X_MSB     (15)
#define BMI160_MGA_FIFO_A_Y_LSB     (16)
#define BMI160_MGA_FIFO_A_Y_MSB     (17)
#define BMI160_MGA_FIFO_A_Z_LSB     (18)
#define BMI160_MGA_FIFO_A_Z_MSB     (19)
/* FIFO mag definition*/
#define BMI160_MA_FIFO_M_X_LSB      (0)
#define BMI160_MA_FIFO_M_X_MSB      (1)
#define BMI160_MA_FIFO_M_Y_LSB      (2)
#define BMI160_MA_FIFO_M_Y_MSB      (3)
#define BMI160_MA_FIFO_M_Z_LSB      (4)
#define BMI160_MA_FIFO_M_Z_MSB      (5)
#define BMI160_MA_FIFO_M_R_LSB      (6)
#define BMI160_MA_FIFO_M_R_MSB      (7)
#define BMI160_MA_FIFO_A_X_LSB      (8)
#define BMI160_MA_FIFO_A_X_MSB      (9)
#define BMI160_MA_FIFO_A_Y_LSB      (10)
#define BMI160_MA_FIFO_A_Y_MSB      (11)
#define BMI160_MA_FIFO_A_Z_LSB      (12)
#define BMI160_MA_FIFO_A_Z_MSB      (13)
/* FIFO mag/gyro definition*/
#define BMI160_MG_FIFO_M_X_LSB      (0)
#define BMI160_MG_FIFO_M_X_MSB      (1)
#define BMI160_MG_FIFO_M_Y_LSB      (2)
#define BMI160_MG_FIFO_M_Y_MSB      (3)
#define BMI160_MG_FIFO_M_Z_LSB      (4)
#define BMI160_MG_FIFO_M_Z_MSB      (5)
#define BMI160_MG_FIFO_M_R_LSB      (6)
#define BMI160_MG_FIFO_M_R_MSB      (7)
#define BMI160_MG_FIFO_G_X_LSB      (8)
#define BMI160_MG_FIFO_G_X_MSB      (9)
#define BMI160_MG_FIFO_G_Y_LSB      (10)
#define BMI160_MG_FIFO_G_Y_MSB      (11)
#define BMI160_MG_FIFO_G_Z_LSB      (12)
#define BMI160_MG_FIFO_G_Z_MSB      (13)
/* FIFO length definitions*/
#define BMI160_FIFO_SENSOR_TIME_LSB     (0)
#define BMI160_FIFO_SENSOR_TIME_XLSB    (1)
#define BMI160_FIFO_SENSOR_TIME_MSB     (2)
#define BMI160_FIFO_SENSOR_TIME_LENGTH  (3)
#define BMI160_FIFO_A_LENGTH            (6)
#define BMI160_FIFO_G_LENGTH            (6)
#define BMI160_FIFO_M_LENGTH            (8)
#define BMI160_FIFO_AG_LENGTH           (12)
#define BMI160_FIFO_AMG_LENGTH          (20)
#define BMI160_FIFO_MA_OR_MG_LENGTH     (14)
#define BMI160_FIFO_LENGTH_LSB_BYTE    (0)
#define BMI160_FIFO_LENGTH_MSB_BYTE    (1)

#endif

/* bus read and write length for mag, accel and gyro*/
#define BMI160_MAG_X_DATA_LENGTH     (2)
#define BMI160_MAG_Y_DATA_LENGTH     (2)
#define BMI160_MAG_Z_DATA_LENGTH     (2)
#define BMI160_MAG_R_DATA_LENGTH     (2)
#define BMI160_MAG_XYZ_DATA_LENGTH   (6)
#define BMI160_MAG_XYZR_DATA_LENGTH  (8)
#define BMI160_MAG_YAS_DATA_LENGTH   (8)
#define BMI160_GYRO_DATA_LENGTH      (2)
#define BMI160_GYRO_XYZ_DATA_LENGTH  (6)
#define BMI160_ACCEL_DATA_LENGTH     (2)
#define BMI160_ACCEL_XYZ_DATA_LENGTH (6)
#define BMI160_TEMP_DATA_LENGTH      (2)
#define BMI160_FIFO_DATA_LENGTH      (2)
#define BMI160_STEP_COUNTER_LENGTH   (2)
#define BMI160_SENSOR_TIME_LENGTH    (3)

/* Delay definitions*/
#define BMI160_SEC_INTERFACE_GEN_READ_WRITE_DELAY    (5)
#define BMI160_BMM150_WAKEUP_DELAY1                  (2)
#define BMI160_BMM150_WAKEUP_DELAY2                  (3)
#define BMI160_BMM150_WAKEUP_DELAY3                  (1)
#define BMI160_YAS532_OFFSET_DELAY                   (2)
#define BMI160_GEN_READ_WRITE_DELAY                  (1)
#define BMI160_YAS532_MEASUREMENT_DELAY              (25)
#define BMI160_YAS_ACQ_COMMAND_DELAY                 (50)
#define BMI160_YAS532_SET_INITIAL_VALUE_DELAY        (200)
#define BMI160_AKM_INIT_DELAY                        (60)
/****************************************************/
/**\name    ARRAY SIZE DEFINITIONS      */
/***************************************************/
#define BMI160_ACCEL_X_DATA_SIZE   (2)
#define BMI160_ACCEL_Y_DATA_SIZE   (2)
#define BMI160_ACCEL_Z_DATA_SIZE   (2)
#define BMI160_ACCEL_XYZ_DATA_SIZE (6)

#define BMI160_GYRO_X_DATA_SIZE    (2)
#define BMI160_GYRO_Y_DATA_SIZE    (2)
#define BMI160_GYRO_Z_DATA_SIZE    (2)
#define BMI160_GYRO_XYZ_DATA_SIZE  (6)

#define BMI160_MAG_X_DATA_SIZE      (2)
#define BMI160_MAG_Y_DATA_SIZE      (2)
#define BMI160_MAG_Z_DATA_SIZE      (2)
#define BMI160_MAG_R_DATA_SIZE      (2)
#define BMI160_MAG_XYZ_DATA_SIZE    (6)
#define BMI160_MAG_XYZR_DATA_SIZE   (8)
#define BMI160_MAG_TRIM_DATA_SIZE   (16)


#define BMI160_TEMP_DATA_SIZE       (2)
#define BMI160_FIFO_DATA_SIZE       (2)
#define BMI160_STEP_COUNT_DATA_SIZE (2)

#define BMI160_SENSOR_TIME_DATA_SIZE      (3)
#define BMI160_AKM_SENSITIVITY_DATA_SIZE  (3)
#define BMI160_HARD_OFFSET_DATA_SIZE      (3)
#define BMI160_YAS_XY1Y2_DATA_SIZE        (3)
#define BMI160_YAS_FLAG_DATA_SIZE         (3)
#define BMI160_YAS_TEMP_DATA_SIZE         (3)
#define BMI160_YAS_H_DATA_SIZE            (3)
#define BMI160_YAS_S_DATA_SIZE            (3)
#define BMI160_YAS_CORRECT_DATA_SIZE      (5)
#define BMI160_YAS_XY1Y2T_DATA_SIZE       (8)
#define BMI160_YAS537_CALIB_DATA_SIZE     (17)
#define BMI160_YAS532_CALIB_DATA_SIZE     (14)
#define BMI160_GYRO_ACCEL_SENSORTIME_DATA_SIZE      (15)
#define BMI160_ACCEL_SENSORTIME_DATA_SIZE           (9)


#define BMI160_GYRO_ACCEL_SENSORTIME_DATA (1)
#define BMI160_ACCEL_SENSORTIME_DATA (0)



/****************************************************/
/**\name    ARRAY PARAMETER DEFINITIONS      */
/***************************************************/
#define BMI160_SENSOR_TIME_MSB_BYTE   (2)
#define BMI160_SENSOR_TIME_XLSB_BYTE  (1)
#define BMI160_SENSOR_TIME_LSB_BYTE   (0)

#define BMI160_MAG_X_LSB_BYTE             (0)
#define BMI160_MAG_X_MSB_BYTE              (1)
#define BMI160_MAG_Y_LSB_BYTE              (0)
#define BMI160_MAG_Y_MSB_BYTE              (1)
#define BMI160_MAG_Z_LSB_BYTE              (0)
#define BMI160_MAG_Z_MSB_BYTE              (1)
#define BMI160_MAG_R_LSB_BYTE              (0)
#define BMI160_MAG_R_MSB_BYTE              (1)
#define BMI160_DATA_FRAME_MAG_X_LSB_BYTE   (0)
#define BMI160_DATA_FRAME_MAG_X_MSB_BYTE   (1)
#define BMI160_DATA_FRAME_MAG_Y_LSB_BYTE   (2)
#define BMI160_DATA_FRAME_MAG_Y_MSB_BYTE   (3)
#define BMI160_DATA_FRAME_MAG_Z_LSB_BYTE   (4)
#define BMI160_DATA_FRAME_MAG_Z_MSB_BYTE   (5)
#define BMI160_DATA_FRAME_MAG_R_LSB_BYTE   (6)
#define BMI160_DATA_FRAME_MAG_R_MSB_BYTE   (7)

#define BMI160_GYRO_X_LSB_BYTE              (0)
#define BMI160_GYRO_X_MSB_BYTE              (1)
#define BMI160_GYRO_Y_LSB_BYTE              (0)
#define BMI160_GYRO_Y_MSB_BYTE              (1)
#define BMI160_GYRO_Z_LSB_BYTE              (0)
#define BMI160_GYRO_Z_MSB_BYTE              (1)
#define BMI160_DATA_FRAME_GYRO_X_LSB_BYTE   (0)
#define BMI160_DATA_FRAME_GYRO_X_MSB_BYTE   (1)
#define BMI160_DATA_FRAME_GYRO_Y_LSB_BYTE   (2)
#define BMI160_DATA_FRAME_GYRO_Y_MSB_BYTE   (3)
#define BMI160_DATA_FRAME_GYRO_Z_LSB_BYTE   (4)
#define BMI160_DATA_FRAME_GYRO_Z_MSB_BYTE   (5)

#define BMI160_ACCEL_X_LSB_BYTE              (0)
#define BMI160_ACCEL_X_MSB_BYTE              (1)
#define BMI160_ACCEL_Y_LSB_BYTE              (0)
#define BMI160_ACCEL_Y_MSB_BYTE              (1)
#define BMI160_ACCEL_Z_LSB_BYTE              (0)
#define BMI160_ACCEL_Z_MSB_BYTE              (1)
#define BMI160_DATA_FRAME_ACCEL_X_LSB_BYTE   (0)
#define BMI160_DATA_FRAME_ACCEL_X_MSB_BYTE   (1)
#define BMI160_DATA_FRAME_ACCEL_Y_LSB_BYTE   (2)
#define BMI160_DATA_FRAME_ACCEL_Y_MSB_BYTE   (3)
#define BMI160_DATA_FRAME_ACCEL_Z_LSB_BYTE   (4)
#define BMI160_DATA_FRAME_ACCEL_Z_MSB_BYTE   (5)

#define BMI160_TEMP_LSB_BYTE    (0)
#define BMI160_TEMP_MSB_BYTE    (1)
#define BMI160_STEP_COUNT_LSB_BYTE    (0)
#define BMI160_STEP_COUNT_MSB_BYTE    (1)
/****************************************************/
/**\name    ERROR CODES       */
/***************************************************/

//#define E_BMI160_NULL_PTR           ((s8)-127)
//#define E_BMI160_COMM_RES           ((s8)-1)
//#define E_BMI160_OUT_OF_RANGE       ((s8)-2)
//#define E_BMI160_BUSY               ((s8)-3)
//#define SUCCESS                     ((u8)0)
//#define ERROR                       ((s8)-1)

/* Constants */
#define BMI160_NULL                     (0)
#define BMI160_DELAY_SETTLING_TIME      (5)
/*This refers BMI160 return type as s8 */
//#define BMI160_RETURN_FUNCTION_TYPE     s8
/****************************************************/
/**\name    REGISTER DEFINITIONS       */
/***************************************************/
/*******************/
/**\name CHIP ID */
/*******************/
#define BMI160_USER_CHIP_ID_ADDR                (0x00)
/*******************/
/**\name ERROR STATUS */
/*******************/
#define BMI160_USER_ERROR_ADDR                  (0x02)
/*******************/
/**\name POWER MODE STATUS */
/*******************/
#define BMI160_USER_PMU_STAT_ADDR               (0x03)
/*******************/
/**\name MAG DATA REGISTERS */
/*******************/
#define BMI160_USER_DATA_0_ADDR                 (0x04)
#define BMI160_USER_DATA_1_ADDR                 (0x05)
#define BMI160_USER_DATA_2_ADDR                 (0x06)
#define BMI160_USER_DATA_3_ADDR                 (0x07)
#define BMI160_USER_DATA_4_ADDR                 (0x08)
#define BMI160_USER_DATA_5_ADDR                 (0x09)
#define BMI160_USER_DATA_6_ADDR                 (0x0A)
#define BMI160_USER_DATA_7_ADDR                 (0x0B)
/*******************/
/**\name GYRO DATA REGISTERS */
/*******************/
#define BMI160_USER_DATA_8_ADDR                 (0x0C)
#define BMI160_USER_DATA_9_ADDR                 (0x0D)
#define BMI160_USER_DATA_10_ADDR                (0x0E)
#define BMI160_USER_DATA_11_ADDR                (0x0F)
#define BMI160_USER_DATA_12_ADDR                (0x10)
#define BMI160_USER_DATA_13_ADDR                (0x11)
/*******************/
/**\name ACCEL DATA REGISTERS */
/*******************/
#define BMI160_USER_DATA_14_ADDR                (0x12)
#define BMI160_USER_DATA_15_ADDR                (0x13)
#define BMI160_USER_DATA_16_ADDR                (0x14)
#define BMI160_USER_DATA_17_ADDR                (0x15)
#define BMI160_USER_DATA_18_ADDR                (0x16)
#define BMI160_USER_DATA_19_ADDR                (0x17)
/*******************/
/**\name SENSOR TIME REGISTERS */
/*******************/
#define BMI160_USER_SENSORTIME_0_ADDR           (0x18)
#define BMI160_USER_SENSORTIME_1_ADDR           (0x19)
#define BMI160_USER_SENSORTIME_2_ADDR           (0x1A)
/*******************/
/**\name STATUS REGISTER FOR SENSOR STATUS FLAG */
/*******************/
#define BMI160_USER_STAT_ADDR                   (0x1B)
/*******************/
/**\name INTERRUPY STATUS REGISTERS */
/*******************/
#define BMI160_USER_INTR_STAT_0_ADDR            (0x1C)
#define BMI160_USER_INTR_STAT_1_ADDR            (0x1D)
#define BMI160_USER_INTR_STAT_2_ADDR            (0x1E)
#define BMI160_USER_INTR_STAT_3_ADDR            (0x1F)
/*******************/
/**\name TEMPERATURE REGISTERS */
/*******************/
#define BMI160_USER_TEMPERATURE_0_ADDR          (0x20)
#define BMI160_USER_TEMPERATURE_1_ADDR          (0x21)
/*******************/
/**\name FIFO REGISTERS */
/*******************/
#define BMI160_USER_FIFO_LENGTH_0_ADDR          (0x22)
#define BMI160_USER_FIFO_LENGTH_1_ADDR          (0x23)
#define BMI160_USER_FIFO_DATA_ADDR              (0x24)
/***************************************************/
/**\name ACCEL CONFIG REGISTERS  FOR ODR, BANDWIDTH AND UNDERSAMPLING*/
/******************************************************/
#define BMI160_USER_ACCEL_CONFIG_ADDR           (0x40)
/*******************/
/**\name ACCEL RANGE */
/*******************/
#define BMI160_USER_ACCEL_RANGE_ADDR            (0x41)
/***************************************************/
/**\name GYRO CONFIG REGISTERS  FOR ODR AND BANDWIDTH */
/******************************************************/
#define BMI160_USER_GYRO_CONFIG_ADDR            (0x42)
/*******************/
/**\name GYRO RANGE */
/*******************/
#define BMI160_USER_GYRO_RANGE_ADDR             (0x43)
/***************************************************/
/**\name MAG CONFIG REGISTERS  FOR ODR*/
/******************************************************/
#define BMI160_USER_MAG_CONFIG_ADDR             (0x44)
#ifdef FIFO_ENABLE
/***************************************************/
/**\name REGISTER FOR GYRO AND ACCEL DOWNSAMPLING RATES FOR FIFO*/
/******************************************************/
#define BMI160_USER_FIFO_DOWN_ADDR              (0x45)
/***************************************************/
/**\name FIFO CONFIG REGISTERS*/
/******************************************************/
#define BMI160_USER_FIFO_CONFIG_0_ADDR          (0x46)
#define BMI160_USER_FIFO_CONFIG_1_ADDR          (0x47)
#endif

/***************************************************/
/**\name MAG INTERFACE REGISTERS*/
/******************************************************/
#define BMI160_USER_MAG_IF_0_ADDR               (0x4B)
#define BMI160_USER_MAG_IF_1_ADDR               (0x4C)
#define BMI160_USER_MAG_IF_2_ADDR               (0x4D)
#define BMI160_USER_MAG_IF_3_ADDR               (0x4E)
#define BMI160_USER_MAG_IF_4_ADDR               (0x4F)
/***************************************************/
/**\name INTERRUPT ENABLE REGISTERS*/
/******************************************************/
#define BMI160_USER_INTR_ENABLE_0_ADDR          (0x50)
#define BMI160_USER_INTR_ENABLE_1_ADDR          (0x51)
#define BMI160_USER_INTR_ENABLE_2_ADDR          (0x52)
#define BMI160_USER_INTR_OUT_CTRL_ADDR          (0x53)
/***************************************************/
/**\name LATCH DURATION REGISTERS*/
/******************************************************/
#define BMI160_USER_INTR_LATCH_ADDR             (0x54)
/***************************************************/
/**\name MAP INTERRUPT 1 and 2 REGISTERS*/
/******************************************************/
#define BMI160_USER_INTR_MAP_0_ADDR             (0x55)
#define BMI160_USER_INTR_MAP_1_ADDR             (0x56)
#define BMI160_USER_INTR_MAP_2_ADDR             (0x57)
/***************************************************/
/**\name DATA SOURCE REGISTERS*/
/******************************************************/
#define BMI160_USER_INTR_DATA_0_ADDR            (0x58)
#define BMI160_USER_INTR_DATA_1_ADDR            (0x59)
/***************************************************/
/**\name
INTERRUPT THRESHOLD, HYSTERESIS, DURATION, MODE CONFIGURATION REGISTERS*/
/******************************************************/
#define BMI160_USER_INTR_LOWHIGH_0_ADDR         (0x5A)
#define BMI160_USER_INTR_LOWHIGH_1_ADDR         (0x5B)
#define BMI160_USER_INTR_LOWHIGH_2_ADDR         (0x5C)
#define BMI160_USER_INTR_LOWHIGH_3_ADDR         (0x5D)
#define BMI160_USER_INTR_LOWHIGH_4_ADDR         (0x5E)
#define BMI160_USER_INTR_MOTION_0_ADDR          (0x5F)
#define BMI160_USER_INTR_MOTION_1_ADDR          (0x60)
#define BMI160_USER_INTR_MOTION_2_ADDR          (0x61)
#define BMI160_USER_INTR_MOTION_3_ADDR          (0x62)
#define BMI160_USER_INTR_TAP_0_ADDR             (0x63)
#define BMI160_USER_INTR_TAP_1_ADDR             (0x64)
#define BMI160_USER_INTR_ORIENT_0_ADDR          (0x65)
#define BMI160_USER_INTR_ORIENT_1_ADDR          (0x66)
#define BMI160_USER_INTR_FLAT_0_ADDR            (0x67)
#define BMI160_USER_INTR_FLAT_1_ADDR            (0x68)
/***************************************************/
/**\name FAST OFFSET CONFIGURATION REGISTER*/
/******************************************************/
#define BMI160_USER_FOC_CONFIG_ADDR             (0x69)
/***************************************************/
/**\name MISCELLANEOUS CONFIGURATION REGISTER*/
/******************************************************/
#define BMI160_USER_CONFIG_ADDR                 (0x6A)
/***************************************************/
/**\name SERIAL INTERFACE SETTINGS REGISTER*/
/******************************************************/
#define BMI160_USER_IF_CONFIG_ADDR              (0x6B)
/***************************************************/
/**\name GYRO POWER MODE TRIGGER REGISTER */
/******************************************************/
#define BMI160_USER_PMU_TRIGGER_ADDR            (0x6C)
/***************************************************/
/**\name SELF_TEST REGISTER*/
/******************************************************/
#define BMI160_USER_SELF_TEST_ADDR              (0x6D)
/***************************************************/
/**\name SPI,I2C SELECTION REGISTER*/
/******************************************************/
#define BMI160_USER_NV_CONFIG_ADDR              (0x70)
/***************************************************/
/**\name ACCEL AND GYRO OFFSET REGISTERS*/
/******************************************************/
#define BMI160_USER_OFFSET_0_ADDR               (0x71)
#define BMI160_USER_OFFSET_1_ADDR               (0x72)
#define BMI160_USER_OFFSET_2_ADDR               (0x73)
#define BMI160_USER_OFFSET_3_ADDR               (0x74)
#define BMI160_USER_OFFSET_4_ADDR               (0x75)
#define BMI160_USER_OFFSET_5_ADDR               (0x76)
#define BMI160_USER_OFFSET_6_ADDR               (0x77)
/***************************************************/
/**\name STEP COUNTER INTERRUPT REGISTERS*/
/******************************************************/
#define BMI160_USER_STEP_COUNT_0_ADDR           (0x78)
#define BMI160_USER_STEP_COUNT_1_ADDR           (0x79)
/***************************************************/
/**\name STEP COUNTER CONFIGURATION REGISTERS*/
/******************************************************/
#define BMI160_USER_STEP_CONFIG_0_ADDR          (0x7A)
#define BMI160_USER_STEP_CONFIG_1_ADDR          (0x7B)
/***************************************************/
/**\name COMMAND REGISTER*/
/******************************************************/
#define BMI160_CMD_COMMANDS_ADDR                (0x7E)
/***************************************************/
/**\name PAGE REGISTERS*/
/******************************************************/
#define BMI160_CMD_EXT_MODE_ADDR                (0x7F)
#define BMI160_COM_C_TRIM_FIVE_ADDR             (0x05)

/****************************************************/
/**\name    SHIFT VALUE DEFINITION       */
/***************************************************/
#define BMI160_SHIFT_BIT_POSITION_BY_01_BIT      (1)
#define BMI160_SHIFT_BIT_POSITION_BY_02_BITS     (2)
#define BMI160_SHIFT_BIT_POSITION_BY_03_BITS     (3)
#define BMI160_SHIFT_BIT_POSITION_BY_04_BITS     (4)
#define BMI160_SHIFT_BIT_POSITION_BY_05_BITS     (5)
#define BMI160_SHIFT_BIT_POSITION_BY_06_BITS     (6)
#define BMI160_SHIFT_BIT_POSITION_BY_07_BITS     (7)
#define BMI160_SHIFT_BIT_POSITION_BY_08_BITS     (8)
#define BMI160_SHIFT_BIT_POSITION_BY_09_BITS     (9)
#define BMI160_SHIFT_BIT_POSITION_BY_12_BITS     (12)
#define BMI160_SHIFT_BIT_POSITION_BY_13_BITS     (13)
#define BMI160_SHIFT_BIT_POSITION_BY_14_BITS     (14)
#define BMI160_SHIFT_BIT_POSITION_BY_15_BITS     (15)
#define BMI160_SHIFT_BIT_POSITION_BY_16_BITS     (16)

/****************************************************/
/**\name     DEFINITIONS USED FOR YAMAHA-YAS532 */
/***************************************************/
#define YAS532_MAG_STATE_NORMAL             (0)
#define YAS532_MAG_STATE_INIT_COIL          (1)
#define YAS532_MAG_STATE_MEASURE_OFFSET     (2)
#define YAS532_MAG_INITCOIL_TIMEOUT         (1000)
#define YAS532_MAG_NOTRANS_POSITION         (3)
#define YAS532_DEFAULT_SENSOR_DELAY         (50)
#define YAS532_DATA_OVERFLOW                (8190)
#define YAS532_DATA_UNDERFLOW               (0)
#define YAS532_MAG_TEMPERATURE_LOG          (10)
#define YAS532_TEMP20DEGREE_TYPICAL         (390)
#define YAS532_VERSION_AC_COEF_X            (850)
#define YAS532_VERSION_AC_COEF_Y1           (750)
#define YAS532_VERSION_AC_COEF_Y2           (750)
#define YAS532_DATA_CENTER                  (4096)
/****************************************************/
/**\name    YAMAHA-YAS532 OFFSET DEFINITION */
/***************************************************/
#if 0
static const s8 INVALID_OFFSET[] = {0x7f, 0x7f, 0x7f};
#define set_vector(to, from) \
    {int _l; for (_l = 0; _l < 3; _l++) (to)[_l] = (from)[_l]; }
#define is_valid_offset(a) \
    (((a)[0] <= 31) && ((a)[1] <= 31) && ((a)[2] <= 31) \
        && (-31 <= (a)[0]) && (-31 <= (a)[1]) && (-31 <= (a)[2]))
#endif
/**************************************************/
/**\name    YAS532 CALIB DATA DEFINITIONS  */
/*************************************************/


/* register address of YAS532*/
#define BMI160_YAS532_TESTR1            (0x88)
#define BMI160_YAS532_TESTR2            (0x89)
#define BMI160_YAS532_RCOIL             (0x81)
#define BMI160_YAS532_COMMAND_REGISTER  (0x82)
#define BMI160_YAS532_DATA_REGISTER     (0xB0)
/* calib data register definition*/
#define BMI160_YAS532_CALIB_CX          (0x90)
#define BMI160_YAS532_CALIB_CY1         (0x91)
#define BMI160_YAS532_CALIB_CY2         (0x92)
#define BMI160_YAS532_CALIB1            (0x93)
#define BMI160_YAS532_CALIB2            (0x94)
#define BMI160_YAS532_CALIB3            (0x95)
#define BMI160_YAS532_CALIB4            (0x96)
#define BMI160_YAS532_CALIB5            (0x97)
#define BMI160_YAS532_CLAIB6            (0x98)
#define BMI160_YAS532_CALIB7            (0x99)
#define BMI160_YAS532_CALIB8            (0x9A)
#define BMI160_YAS532_CALIIB9           (0x9B)
#define BMI160_YAS532_CALIB10           (0x9C)
#define BMI160_YAS532_CALIB11           (0x9D)
/* offset definition */
#define BMI160_YAS532_OFFSET_X          (0x85)
#define BMI160_YAS532_OFFSET_Y          (0x86)
#define BMI160_YAS532_OFFSET_Z          (0x87)
/* data to write register for yas532*/
#define BMI160_YAS532_WRITE_TESTR1      (0x00)
#define BMI160_YAS532_WRITE_TESTR2      (0x00)
#define BMI160_YAS532_WRITE_RCOIL       (0x00)
/**************************************************/
/**\name    YAS537 DEFINITION  */
/*************************************************/

#define YAS537_SRSTR_DATA               (0x02)
#define YAS537_WRITE_A_D_CONVERTER      (0x03)
#define YAS537_WRITE_A_D_CONVERTER2     (0xF8)
#define YAS537_WRITE_FILTER             (0x08)
#define YAS537_WRITE_CONFR              (0x08)
#define YAS537_WRITE_TEMP_CALIB         (0xFF)
#define YAS537_SET_COMMAND_REGISTER     (0x01)

/**************************************************/
/**\name    YAS537 REGISTER DEFINITION  */
/*************************************************/
#define YAS537_REG_SRSTR                (0x90)
#define YAS537_REG_CALR_C0              (0xC0)
#define YAS537_REG_CALR_C1              (0xC1)
#define YAS537_REG_CALR_C2              (0xC2)
#define YAS537_REG_CALR_C3              (0xC3)
#define YAS537_REG_CALR_C4              (0xC4)
#define YAS537_REG_CALR_C5              (0xC5)
#define YAS537_REG_CALR_C6              (0xC6)
#define YAS537_REG_CALR_C7              (0xC7)
#define YAS537_REG_CALR_C8              (0xC8)
#define YAS537_REG_CALR_C9              (0xC9)
#define YAS537_REG_CALR_CA              (0xCA)
#define YAS537_REG_CALR_CB              (0xCB)
#define YAS537_REG_CALR_CC              (0xCC)
#define YAS537_REG_CALR_CD              (0xCD)
#define YAS537_REG_CALR_CE              (0xCE)
#define YAS537_REG_CALR_CF              (0xCF)
#define YAS537_REG_CALR_DO              (0xD0)
#define YAS537_REG_MTCR                 (0x93)
#define YAS537_REG_CONFR                (0x82)
#define BMI160_REG_YAS537_CMDR          (0x81)
#define YAS537_REG_OXR                  (0x84)
#define YAS537_REG_AVRR                 (0x87)
#define YAS537_REG_HCKR                 (0x88)
#define YAS537_REG_LCKR                 (0x89)
#define YAS537_REG_ADCCALR              (0x91)
#define YAS537_REG_ADCCALR_ONE          (0x92)
#define YAS537_REG_OCR                  (0x9E)
#define YAS537_REG_TRMR                 (0x9F)
#define YAS537_REG_TEMPERATURE_0        (0xB0)
#define YAS537_REG_TEMPERATURE_1        (0xB1)
#define YAS537_REG_DATA_X_0             (0xB2)
#define YAS537_REG_DATA_X_1             (0xB3)
#define YAS537_REG_DATA_Y1_0            (0xB4)
#define YAS537_REG_DATA_Y1_1            (0xB5)
#define YAS537_REG_DATA_Y2_0            (0xB6)
#define YAS537_REG_DATA_Y2_1            (0xB7)
#define YAS537_MAG_STATE_NORMAL         (0)
#define YAS537_MAG_STATE_INIT_COIL      (1)
#define YAS537_MAG_STATE_RECORD_DATA    (2)
#define YAS537_DATA_UNDERFLOW           (0)
#define YAS537_DATA_OVERFLOW            (16383)
/****************************************************/
/**\name    YAS537_set vector */
/***************************************************/
#if 0
#define yas537_set_vector(to, from) \
    {int _l; for (_l = 0; _l < 3; _l++) (to)[_l] = (from)[_l]; }

#ifndef ABS
#define ABS(a)      ((a) > 0 ? (a) : -(a)) /*!< Absolute value */
#endif
#endif
/****************************************************/
/**\name    AKM09911 AND AKM09912 DEFINITION */
/***************************************************/
#define AKM09912_SENSITIVITY_DIV    (256)
#define AKM09912_SENSITIVITY        (128)
#define AKM09911_SENSITIVITY_DIV    (128)
#define AKM_ASAX    (0)
#define AKM_ASAY    (1)
#define AKM_ASAZ    (2)
#define AKM_POWER_DOWN_MODE_DATA        (0x00)
#define AKM_FUSE_ROM_MODE               (0x1F)
#define AKM_POWER_MODE_REG              (0x31)
#define AKM_SINGLE_MEASUREMENT_MODE     (0x01)
#define AKM_DATA_REGISTER               (0x11)
/*! AKM09912 Register definition */
#define AKM_CHIP_ID_REG         (0x01)
/****************************************************/
/**\name    BMM150 DEFINITION */
/***************************************************/
#define BMI160_BMM150_SET_POWER_CONTROL (0x01)
#define BMI160_BMM150_MAX_RETRY_WAKEUP  (5)
#define BMI160_BMM150_POWER_ON          (0x01)
#define BMI160_BMM150_POWER_OFF         (0x00)
#define BMI160_BMM150_FORCE_MODE        (0x02)
#define BMI160_BMM150_POWER_ON_SUCCESS  (0)
#define BMI160_BMM150_POWER_ON_FAIL     ((s8)-1)

#define BMI160_BMM150_DIG_X1            (0)
#define BMI160_BMM150_DIG_Y1            (1)
#define BMI160_BMM150_DIG_X2            (2)
#define BMI160_BMM150_DIG_Y3            (3)
#define BMI160_BMM150_DIG_XY1           (4)
#define BMI160_BMM150_DIG_XY2           (5)
#define BMI160_BMM150_DIG_Z1_LSB        (6)
#define BMI160_BMM150_DIG_Z1_MSB        (7)
#define BMI160_BMM150_DIG_Z2_LSB        (8)
#define BMI160_BMM150_DIG_Z2_MSB        (9)
#define BMI160_BMM150_DIG_DIG_Z3_LSB    (10)
#define BMI160_BMM150_DIG_DIG_Z3_MSB    (11)
#define BMI160_BMM150_DIG_DIG_Z4_LSB    (12)
#define BMI160_BMM150_DIG_DIG_Z4_MSB    (13)
#define BMI160_BMM150_DIG_DIG_XYZ1_LSB  (14)
#define BMI160_BMM150_DIG_DIG_XYZ1_MSB  (15)
#define BMI160_FIFO_FRAME_CNT           (146)
#define BMI160_FRAME_COUNT              (1)


/**************************************************************/
/**\name    CHIP ID LENGTH, POSITION AND MASK    */
/**************************************************************/
/* Chip ID Description - Reg Addr --> (0x00), Bit --> 0...7 */
#define BMI160_USER_CHIP_ID__POS             (0)
#define BMI160_USER_CHIP_ID__MSK            (0xFF)
#define BMI160_USER_CHIP_ID__LEN             (8)
#define BMI160_USER_CHIP_ID__REG             (BMI160_USER_CHIP_ID_ADDR)
/**************************************************************/
/**\name    ERROR STATUS LENGTH, POSITION AND MASK    */
/**************************************************************/
/* Error Description - Reg Addr --> (0x02), Bit --> 0 */
#define BMI160_USER_ERR_STAT__POS               (0)
#define BMI160_USER_ERR_STAT__LEN               (8)
#define BMI160_USER_ERR_STAT__MSK               (0xFF)
#define BMI160_USER_ERR_STAT__REG               (BMI160_USER_ERROR_ADDR)

#define BMI160_USER_FATAL_ERR__POS               (0)
#define BMI160_USER_FATAL_ERR__LEN               (1)
#define BMI160_USER_FATAL_ERR__MSK               (0x01)
#define BMI160_USER_FATAL_ERR__REG               (BMI160_USER_ERROR_ADDR)

/* Error Description - Reg Addr --> (0x02), Bit --> 1...4 */
#define BMI160_USER_ERR_CODE__POS               (1)
#define BMI160_USER_ERR_CODE__LEN               (4)
#define BMI160_USER_ERR_CODE__MSK               (0x1E)
#define BMI160_USER_ERR_CODE__REG               (BMI160_USER_ERROR_ADDR)

/* Error Description - Reg Addr --> (0x02), Bit --> 5 */
#define BMI160_USER_I2C_FAIL_ERR__POS               (5)
#define BMI160_USER_I2C_FAIL_ERR__LEN               (1)
#define BMI160_USER_I2C_FAIL_ERR__MSK               (0x20)
#define BMI160_USER_I2C_FAIL_ERR__REG               (BMI160_USER_ERROR_ADDR)

/* Error Description - Reg Addr --> (0x02), Bit --> 6 */
#define BMI160_USER_DROP_CMD_ERR__POS              (6)
#define BMI160_USER_DROP_CMD_ERR__LEN              (1)
#define BMI160_USER_DROP_CMD_ERR__MSK              (0x40)
#define BMI160_USER_DROP_CMD_ERR__REG              (BMI160_USER_ERROR_ADDR)
/**************************************************************/
/**\name    MAG DATA READY LENGTH, POSITION AND MASK    */
/**************************************************************/
/* Error Description - Reg Addr --> (0x02), Bit --> 7 */
#define BMI160_USER_MAG_DATA_RDY_ERR__POS               (7)
#define BMI160_USER_MAG_DATA_RDY_ERR__LEN               (1)
#define BMI160_USER_MAG_DATA_RDY_ERR__MSK               (0x80)
#define BMI160_USER_MAG_DATA_RDY_ERR__REG               (BMI160_USER_ERROR_ADDR)
/**************************************************************/
/**\name    MAG POWER MODE LENGTH, POSITION AND MASK    */
/**************************************************************/
/* PMU_Status Description of MAG - Reg Addr --> (0x03), Bit --> 1..0 */
#define BMI160_USER_MAG_POWER_MODE_STAT__POS        (0)
#define BMI160_USER_MAG_POWER_MODE_STAT__LEN        (2)
#define BMI160_USER_MAG_POWER_MODE_STAT__MSK        (0x03)
#define BMI160_USER_MAG_POWER_MODE_STAT__REG        \
(BMI160_USER_PMU_STAT_ADDR)
/**************************************************************/
/**\name    GYRO POWER MODE LENGTH, POSITION AND MASK    */
/**************************************************************/
/* PMU_Status Description of GYRO - Reg Addr --> (0x03), Bit --> 3...2 */
#define BMI160_USER_GYRO_POWER_MODE_STAT__POS               (2)
#define BMI160_USER_GYRO_POWER_MODE_STAT__LEN               (2)
#define BMI160_USER_GYRO_POWER_MODE_STAT__MSK               (0x0C)
#define BMI160_USER_GYRO_POWER_MODE_STAT__REG             \
(BMI160_USER_PMU_STAT_ADDR)
/**************************************************************/
/**\name    ACCEL POWER MODE LENGTH, POSITION AND MASK    */
/**************************************************************/
/* PMU_Status Description of ACCEL - Reg Addr --> (0x03), Bit --> 5...4 */
#define BMI160_USER_ACCEL_POWER_MODE_STAT__POS               (4)
#define BMI160_USER_ACCEL_POWER_MODE_STAT__LEN               (2)
#define BMI160_USER_ACCEL_POWER_MODE_STAT__MSK               (0x30)
#define BMI160_USER_ACCEL_POWER_MODE_STAT__REG          \
(BMI160_USER_PMU_STAT_ADDR)
/**************************************************************/
/**\name    MAG DATA XYZ LENGTH, POSITION AND MASK    */
/**************************************************************/
/* Mag_X(LSB) Description - Reg Addr --> (0x04), Bit --> 0...7 */
#define BMI160_USER_DATA_0_MAG_X_LSB__POS           (0)
#define BMI160_USER_DATA_0_MAG_X_LSB__LEN           (8)
#define BMI160_USER_DATA_0_MAG_X_LSB__MSK          (0xFF)
#define BMI160_USER_DATA_0_MAG_X_LSB__REG          (BMI160_USER_DATA_0_ADDR)

/* Mag_X(LSB) Description - Reg Addr --> (0x04), Bit --> 3...7 */
#define BMI160_USER_DATA_MAG_X_LSB__POS           (3)
#define BMI160_USER_DATA_MAG_X_LSB__LEN           (5)
#define BMI160_USER_DATA_MAG_X_LSB__MSK          (0xF8)
#define BMI160_USER_DATA_MAG_X_LSB__REG          (BMI160_USER_DATA_0_ADDR)

/* Mag_X(MSB) Description - Reg Addr --> (0x05), Bit --> 0...7 */
#define BMI160_USER_DATA_1_MAG_X_MSB__POS           (0)
#define BMI160_USER_DATA_1_MAG_X_MSB__LEN           (8)
#define BMI160_USER_DATA_1_MAG_X_MSB__MSK          (0xFF)
#define BMI160_USER_DATA_1_MAG_X_MSB__REG          (BMI160_USER_DATA_1_ADDR)

/* Mag_Y(LSB) Description - Reg Addr --> (0x06), Bit --> 0...7 */
#define BMI160_USER_DATA_2_MAG_Y_LSB__POS           (0)
#define BMI160_USER_DATA_2_MAG_Y_LSB__LEN           (8)
#define BMI160_USER_DATA_2_MAG_Y_LSB__MSK          (0xFF)
#define BMI160_USER_DATA_2_MAG_Y_LSB__REG          (BMI160_USER_DATA_2_ADDR)

/* Mag_Y(LSB) Description - Reg Addr --> (0x06), Bit --> 3...7 */
#define BMI160_USER_DATA_MAG_Y_LSB__POS           (3)
#define BMI160_USER_DATA_MAG_Y_LSB__LEN           (5)
#define BMI160_USER_DATA_MAG_Y_LSB__MSK          (0xF8)
#define BMI160_USER_DATA_MAG_Y_LSB__REG          (BMI160_USER_DATA_2_ADDR)

/* Mag_Y(MSB) Description - Reg Addr --> (0x07), Bit --> 0...7 */
#define BMI160_USER_DATA_3_MAG_Y_MSB__POS           (0)
#define BMI160_USER_DATA_3_MAG_Y_MSB__LEN           (8)
#define BMI160_USER_DATA_3_MAG_Y_MSB__MSK          (0xFF)
#define BMI160_USER_DATA_3_MAG_Y_MSB__REG          (BMI160_USER_DATA_3_ADDR)

/* Mag_Z(LSB) Description - Reg Addr --> (0x08), Bit --> 0...7 */
#define BMI160_USER_DATA_4_MAG_Z_LSB__POS           (0)
#define BMI160_USER_DATA_4_MAG_Z_LSB__LEN           (8)
#define BMI160_USER_DATA_4_MAG_Z_LSB__MSK          (0xFF)
#define BMI160_USER_DATA_4_MAG_Z_LSB__REG          (BMI160_USER_DATA_4_ADDR)

/* Mag_X(LSB) Description - Reg Addr --> (0x08), Bit --> 3...7 */
#define BMI160_USER_DATA_MAG_Z_LSB__POS           (1)
#define BMI160_USER_DATA_MAG_Z_LSB__LEN           (7)
#define BMI160_USER_DATA_MAG_Z_LSB__MSK          (0xFE)
#define BMI160_USER_DATA_MAG_Z_LSB__REG          (BMI160_USER_DATA_4_ADDR)

/* Mag_Z(MSB) Description - Reg Addr --> (0x09), Bit --> 0...7 */
#define BMI160_USER_DATA_5_MAG_Z_MSB__POS           (0)
#define BMI160_USER_DATA_5_MAG_Z_MSB__LEN           (8)
#define BMI160_USER_DATA_5_MAG_Z_MSB__MSK          (0xFF)
#define BMI160_USER_DATA_5_MAG_Z_MSB__REG          (BMI160_USER_DATA_5_ADDR)

/* RHALL(LSB) Description - Reg Addr --> (0x0A), Bit --> 0...7 */
#define BMI160_USER_DATA_6_RHALL_LSB__POS           (0)
#define BMI160_USER_DATA_6_RHALL_LSB__LEN           (8)
#define BMI160_USER_DATA_6_RHALL_LSB__MSK          (0xFF)
#define BMI160_USER_DATA_6_RHALL_LSB__REG          (BMI160_USER_DATA_6_ADDR)

/* Mag_R(LSB) Description - Reg Addr --> (0x0A), Bit --> 3...7 */
#define BMI160_USER_DATA_MAG_R_LSB__POS           (2)
#define BMI160_USER_DATA_MAG_R_LSB__LEN           (6)
#define BMI160_USER_DATA_MAG_R_LSB__MSK          (0xFC)
#define BMI160_USER_DATA_MAG_R_LSB__REG          (BMI160_USER_DATA_6_ADDR)

/* RHALL(MSB) Description - Reg Addr --> (0x0B), Bit --> 0...7 */
#define BMI160_USER_DATA_7_RHALL_MSB__POS           (0)
#define BMI160_USER_DATA_7_RHALL_MSB__LEN           (8)
#define BMI160_USER_DATA_7_RHALL_MSB__MSK          (0xFF)
#define BMI160_USER_DATA_7_RHALL_MSB__REG          (BMI160_USER_DATA_7_ADDR)
/**************************************************************/
/**\name    GYRO DATA XYZ LENGTH, POSITION AND MASK    */
/**************************************************************/
/* GYR_X (LSB) Description - Reg Addr --> (0x0C), Bit --> 0...7 */
#define BMI160_USER_DATA_8_GYRO_X_LSB__POS           (0)
#define BMI160_USER_DATA_8_GYRO_X_LSB__LEN           (8)
#define BMI160_USER_DATA_8_GYRO_X_LSB__MSK          (0xFF)
#define BMI160_USER_DATA_8_GYRO_X_LSB__REG          (BMI160_USER_DATA_8_ADDR)

/* GYR_X (MSB) Description - Reg Addr --> (0x0D), Bit --> 0...7 */
#define BMI160_USER_DATA_9_GYRO_X_MSB__POS           (0)
#define BMI160_USER_DATA_9_GYRO_X_MSB__LEN           (8)
#define BMI160_USER_DATA_9_GYRO_X_MSB__MSK          (0xFF)
#define BMI160_USER_DATA_9_GYRO_X_MSB__REG          (BMI160_USER_DATA_9_ADDR)

/* GYR_Y (LSB) Description - Reg Addr --> 0x0E, Bit --> 0...7 */
#define BMI160_USER_DATA_10_GYRO_Y_LSB__POS           (0)
#define BMI160_USER_DATA_10_GYRO_Y_LSB__LEN           (8)
#define BMI160_USER_DATA_10_GYRO_Y_LSB__MSK          (0xFF)
#define BMI160_USER_DATA_10_GYRO_Y_LSB__REG          (BMI160_USER_DATA_10_ADDR)

/* GYR_Y (MSB) Description - Reg Addr --> (0x0F), Bit --> 0...7 */
#define BMI160_USER_DATA_11_GYRO_Y_MSB__POS           (0)
#define BMI160_USER_DATA_11_GYRO_Y_MSB__LEN           (8)
#define BMI160_USER_DATA_11_GYRO_Y_MSB__MSK          (0xFF)
#define BMI160_USER_DATA_11_GYRO_Y_MSB__REG          (BMI160_USER_DATA_11_ADDR)

/* GYR_Z (LSB) Description - Reg Addr --> (0x10), Bit --> 0...7 */
#define BMI160_USER_DATA_12_GYRO_Z_LSB__POS           (0)
#define BMI160_USER_DATA_12_GYRO_Z_LSB__LEN           (8)
#define BMI160_USER_DATA_12_GYRO_Z_LSB__MSK          (0xFF)
#define BMI160_USER_DATA_12_GYRO_Z_LSB__REG          (BMI160_USER_DATA_12_ADDR)

/* GYR_Z (MSB) Description - Reg Addr --> (0x11), Bit --> 0...7 */
#define BMI160_USER_DATA_13_GYRO_Z_MSB__POS           (0)
#define BMI160_USER_DATA_13_GYRO_Z_MSB__LEN           (8)
#define BMI160_USER_DATA_13_GYRO_Z_MSB__MSK          (0xFF)
#define BMI160_USER_DATA_13_GYRO_Z_MSB__REG          (BMI160_USER_DATA_13_ADDR)
/**************************************************************/
/**\name    ACCEL DATA XYZ LENGTH, POSITION AND MASK    */
/**************************************************************/
/* ACC_X (LSB) Description - Reg Addr --> (0x12), Bit --> 0...7 */
#define BMI160_USER_DATA_14_ACCEL_X_LSB__POS           (0)
#define BMI160_USER_DATA_14_ACCEL_X_LSB__LEN           (8)
#define BMI160_USER_DATA_14_ACCEL_X_LSB__MSK          (0xFF)
#define BMI160_USER_DATA_14_ACCEL_X_LSB__REG          (BMI160_USER_DATA_14_ADDR)

/* ACC_X (MSB) Description - Reg Addr --> 0x13, Bit --> 0...7 */
#define BMI160_USER_DATA_15_ACCEL_X_MSB__POS           (0)
#define BMI160_USER_DATA_15_ACCEL_X_MSB__LEN           (8)
#define BMI160_USER_DATA_15_ACCEL_X_MSB__MSK          (0xFF)
#define BMI160_USER_DATA_15_ACCEL_X_MSB__REG          (BMI160_USER_DATA_15_ADDR)

/* ACC_Y (LSB) Description - Reg Addr --> (0x14), Bit --> 0...7 */
#define BMI160_USER_DATA_16_ACCEL_Y_LSB__POS           (0)
#define BMI160_USER_DATA_16_ACCEL_Y_LSB__LEN           (8)
#define BMI160_USER_DATA_16_ACCEL_Y_LSB__MSK          (0xFF)
#define BMI160_USER_DATA_16_ACCEL_Y_LSB__REG          (BMI160_USER_DATA_16_ADDR)

/* ACC_Y (MSB) Description - Reg Addr --> (0x15), Bit --> 0...7 */
#define BMI160_USER_DATA_17_ACCEL_Y_MSB__POS           (0)
#define BMI160_USER_DATA_17_ACCEL_Y_MSB__LEN           (8)
#define BMI160_USER_DATA_17_ACCEL_Y_MSB__MSK          (0xFF)
#define BMI160_USER_DATA_17_ACCEL_Y_MSB__REG          (BMI160_USER_DATA_17_ADDR)

/* ACC_Z (LSB) Description - Reg Addr --> 0x16, Bit --> 0...7 */
#define BMI160_USER_DATA_18_ACCEL_Z_LSB__POS           (0)
#define BMI160_USER_DATA_18_ACCEL_Z_LSB__LEN           (8)
#define BMI160_USER_DATA_18_ACCEL_Z_LSB__MSK          (0xFF)
#define BMI160_USER_DATA_18_ACCEL_Z_LSB__REG          (BMI160_USER_DATA_18_ADDR)

/* ACC_Z (MSB) Description - Reg Addr --> (0x17), Bit --> 0...7 */
#define BMI160_USER_DATA_19_ACCEL_Z_MSB__POS           (0)
#define BMI160_USER_DATA_19_ACCEL_Z_MSB__LEN           (8)
#define BMI160_USER_DATA_19_ACCEL_Z_MSB__MSK          (0xFF)
#define BMI160_USER_DATA_19_ACCEL_Z_MSB__REG          (BMI160_USER_DATA_19_ADDR)
/**************************************************************/
/**\name    SENSOR TIME LENGTH, POSITION AND MASK    */
/**************************************************************/
/* SENSORTIME_0 (LSB) Description - Reg Addr --> (0x18), Bit --> 0...7 */
#define BMI160_USER_SENSORTIME_0_SENSOR_TIME_LSB__POS           (0)
#define BMI160_USER_SENSORTIME_0_SENSOR_TIME_LSB__LEN           (8)
#define BMI160_USER_SENSORTIME_0_SENSOR_TIME_LSB__MSK          (0xFF)
#define BMI160_USER_SENSORTIME_0_SENSOR_TIME_LSB__REG          \
        (BMI160_USER_SENSORTIME_0_ADDR)

/* SENSORTIME_1 (MSB) Description - Reg Addr --> (0x19), Bit --> 0...7 */
#define BMI160_USER_SENSORTIME_1_SENSOR_TIME_MSB__POS           (0)
#define BMI160_USER_SENSORTIME_1_SENSOR_TIME_MSB__LEN           (8)
#define BMI160_USER_SENSORTIME_1_SENSOR_TIME_MSB__MSK          (0xFF)
#define BMI160_USER_SENSORTIME_1_SENSOR_TIME_MSB__REG          \
        (BMI160_USER_SENSORTIME_1_ADDR)

/* SENSORTIME_2 (MSB) Description - Reg Addr --> (0x1A), Bit --> 0...7 */
#define BMI160_USER_SENSORTIME_2_SENSOR_TIME_MSB__POS           (0)
#define BMI160_USER_SENSORTIME_2_SENSOR_TIME_MSB__LEN           (8)
#define BMI160_USER_SENSORTIME_2_SENSOR_TIME_MSB__MSK          (0xFF)
#define BMI160_USER_SENSORTIME_2_SENSOR_TIME_MSB__REG          \
        (BMI160_USER_SENSORTIME_2_ADDR)
/**************************************************************/
/**\name    GYRO SELF TEST LENGTH, POSITION AND MASK    */
/**************************************************************/
/* Status Description - Reg Addr --> 0x1B, Bit --> 1 */
#define BMI160_USER_STAT_GYRO_SELFTEST_OK__POS          (1)
#define BMI160_USER_STAT_GYRO_SELFTEST_OK__LEN          (1)
#define BMI160_USER_STAT_GYRO_SELFTEST_OK__MSK          (0x02)
#define BMI160_USER_STAT_GYRO_SELFTEST_OK__REG         \
        (BMI160_USER_STAT_ADDR)
/**************************************************************/
/**\name    MAG MANUAL OPERATION LENGTH, POSITION AND MASK    */
/**************************************************************/
/* Status Description - Reg Addr --> 0x1B, Bit --> 2 */
#define BMI160_USER_STAT_MAG_MANUAL_OPERATION__POS          (2)
#define BMI160_USER_STAT_MAG_MANUAL_OPERATION__LEN          (1)
#define BMI160_USER_STAT_MAG_MANUAL_OPERATION__MSK          (0x04)
#define BMI160_USER_STAT_MAG_MANUAL_OPERATION__REG          \
        (BMI160_USER_STAT_ADDR)
/**************************************************************/
/**\name    FOC STATUS LENGTH, POSITION AND MASK    */
/**************************************************************/
/* Status Description - Reg Addr --> 0x1B, Bit --> 3 */
#define BMI160_USER_STAT_FOC_RDY__POS          (3)
#define BMI160_USER_STAT_FOC_RDY__LEN          (1)
#define BMI160_USER_STAT_FOC_RDY__MSK          (0x08)
#define BMI160_USER_STAT_FOC_RDY__REG          (BMI160_USER_STAT_ADDR)
/**************************************************************/
/**\name    NVM READY LENGTH, POSITION AND MASK    */
/**************************************************************/
/* Status Description - Reg Addr --> 0x1B, Bit --> 4 */
#define BMI160_USER_STAT_NVM_RDY__POS           (4)
#define BMI160_USER_STAT_NVM_RDY__LEN           (1)
#define BMI160_USER_STAT_NVM_RDY__MSK           (0x10)
#define BMI160_USER_STAT_NVM_RDY__REG           (BMI160_USER_STAT_ADDR)
/**************************************************************/
/**\name    DATA READY LENGTH, POSITION AND MASK FOR ACCEL, MAG AND GYRO*/
/**************************************************************/
/* Status Description - Reg Addr --> 0x1B, Bit --> 5 */
#define BMI160_USER_STAT_DATA_RDY_MAG__POS           (5)
#define BMI160_USER_STAT_DATA_RDY_MAG__LEN           (1)
#define BMI160_USER_STAT_DATA_RDY_MAG__MSK           (0x20)
#define BMI160_USER_STAT_DATA_RDY_MAG__REG           (BMI160_USER_STAT_ADDR)

/* Status Description - Reg Addr --> 0x1B, Bit --> 6 */
#define BMI160_USER_STAT_DATA_RDY_GYRO__POS           (6)
#define BMI160_USER_STAT_DATA_RDY_GYRO__LEN           (1)
#define BMI160_USER_STAT_DATA_RDY_GYRO__MSK           (0x40)
#define BMI160_USER_STAT_DATA_RDY_GYRO__REG           (BMI160_USER_STAT_ADDR)

/* Status Description - Reg Addr --> 0x1B, Bit --> 7 */
#define BMI160_USER_STAT_DATA_RDY_ACCEL__POS           (7)
#define BMI160_USER_STAT_DATA_RDY_ACCEL__LEN           (1)
#define BMI160_USER_STAT_DATA_RDY_ACCEL__MSK           (0x80)
#define BMI160_USER_STAT_DATA_RDY_ACCEL__REG           (BMI160_USER_STAT_ADDR)
/**************************************************************/
/**\name    INTERRUPT STATUS LENGTH, POSITION AND MASK    */
/**************************************************************/
/* Int_Status_0 Description - Reg Addr --> 0x1C, Bit --> 0 */
#define BMI160_USER_INTR_STAT_0_STEP_INTR__POS           (0)
#define BMI160_USER_INTR_STAT_0_STEP_INTR__LEN           (1)
#define BMI160_USER_INTR_STAT_0_STEP_INTR__MSK          (0x01)
#define BMI160_USER_INTR_STAT_0_STEP_INTR__REG          \
        (BMI160_USER_INTR_STAT_0_ADDR)
/**************************************************************/
/**\name    SIGNIFICANT INTERRUPT STATUS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_0 Description - Reg Addr --> 0x1C, Bit --> 1 */
#define BMI160_USER_INTR_STAT_0_SIGNIFICANT_INTR__POS       (1)
#define BMI160_USER_INTR_STAT_0_SIGNIFICANT_INTR__LEN       (1)
#define BMI160_USER_INTR_STAT_0_SIGNIFICANT_INTR__MSK       (0x02)
#define BMI160_USER_INTR_STAT_0_SIGNIFICANT_INTR__REG       \
        (BMI160_USER_INTR_STAT_0_ADDR)
/**************************************************************/
/**\name    ANY_MOTION INTERRUPT STATUS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_0 Description - Reg Addr --> 0x1C, Bit --> 2 */
#define BMI160_USER_INTR_STAT_0_ANY_MOTION__POS           (2)
#define BMI160_USER_INTR_STAT_0_ANY_MOTION__LEN           (1)
#define BMI160_USER_INTR_STAT_0_ANY_MOTION__MSK          (0x04)
#define BMI160_USER_INTR_STAT_0_ANY_MOTION__REG          \
        (BMI160_USER_INTR_STAT_0_ADDR)
/**************************************************************/
/**\name    PMU TRIGGER INTERRUPT STATUS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_0 Description - Reg Addr --> 0x1C, Bit --> 3 */
#define BMI160_USER_INTR_STAT_0_PMU_TRIGGER__POS           3
#define BMI160_USER_INTR_STAT_0_PMU_TRIGGER__LEN           (1)
#define BMI160_USER_INTR_STAT_0_PMU_TRIGGER__MSK          (0x08)
#define BMI160_USER_INTR_STAT_0_PMU_TRIGGER__REG          \
        (BMI160_USER_INTR_STAT_0_ADDR)
/**************************************************************/
/**\name    DOUBLE TAP INTERRUPT STATUS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_0 Description - Reg Addr --> 0x1C, Bit --> 4 */
#define BMI160_USER_INTR_STAT_0_DOUBLE_TAP_INTR__POS           4
#define BMI160_USER_INTR_STAT_0_DOUBLE_TAP_INTR__LEN           (1)
#define BMI160_USER_INTR_STAT_0_DOUBLE_TAP_INTR__MSK          (0x10)
#define BMI160_USER_INTR_STAT_0_DOUBLE_TAP_INTR__REG          \
        (BMI160_USER_INTR_STAT_0_ADDR)
/**************************************************************/
/**\name    SINGLE TAP INTERRUPT STATUS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_0 Description - Reg Addr --> 0x1C, Bit --> 5 */
#define BMI160_USER_INTR_STAT_0_SINGLE_TAP_INTR__POS           5
#define BMI160_USER_INTR_STAT_0_SINGLE_TAP_INTR__LEN           (1)
#define BMI160_USER_INTR_STAT_0_SINGLE_TAP_INTR__MSK          (0x20)
#define BMI160_USER_INTR_STAT_0_SINGLE_TAP_INTR__REG          \
        (BMI160_USER_INTR_STAT_0_ADDR)
/**************************************************************/
/**\name    ORIENT INTERRUPT STATUS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_0 Description - Reg Addr --> 0x1C, Bit --> 6 */
#define BMI160_USER_INTR_STAT_0_ORIENT__POS           (6)
#define BMI160_USER_INTR_STAT_0_ORIENT__LEN           (1)
#define BMI160_USER_INTR_STAT_0_ORIENT__MSK          (0x40)
#define BMI160_USER_INTR_STAT_0_ORIENT__REG          \
        (BMI160_USER_INTR_STAT_0_ADDR)
/**************************************************************/
/**\name    FLAT INTERRUPT STATUS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_0 Description - Reg Addr --> 0x1C, Bit --> 7 */
#define BMI160_USER_INTR_STAT_0_FLAT__POS           (7)
#define BMI160_USER_INTR_STAT_0_FLAT__LEN           (1)
#define BMI160_USER_INTR_STAT_0_FLAT__MSK          (0x80)
#define BMI160_USER_INTR_STAT_0_FLAT__REG          \
        (BMI160_USER_INTR_STAT_0_ADDR)
/**************************************************************/
/**\name    HIGH_G INTERRUPT STATUS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_1 Description - Reg Addr --> 0x1D, Bit --> 2 */
#define BMI160_USER_INTR_STAT_1_HIGH_G_INTR__POS               (2)
#define BMI160_USER_INTR_STAT_1_HIGH_G_INTR__LEN               (1)
#define BMI160_USER_INTR_STAT_1_HIGH_G_INTR__MSK              (0x04)
#define BMI160_USER_INTR_STAT_1_HIGH_G_INTR__REG              \
        (BMI160_USER_INTR_STAT_1_ADDR)
/**************************************************************/
/**\name    LOW_G INTERRUPT STATUS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_1 Description - Reg Addr --> 0x1D, Bit --> 3 */
#define BMI160_USER_INTR_STAT_1_LOW_G_INTR__POS               (3)
#define BMI160_USER_INTR_STAT_1_LOW_G_INTR__LEN               (1)
#define BMI160_USER_INTR_STAT_1_LOW_G_INTR__MSK              (0x08)
#define BMI160_USER_INTR_STAT_1_LOW_G_INTR__REG              \
        (BMI160_USER_INTR_STAT_1_ADDR)
/**************************************************************/
/**\name    DATA READY INTERRUPT STATUS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_1 Description - Reg Addr --> 0x1D, Bit --> 4 */
#define BMI160_USER_INTR_STAT_1_DATA_RDY_INTR__POS               (4)
#define BMI160_USER_INTR_STAT_1_DATA_RDY_INTR__LEN               (1)
#define BMI160_USER_INTR_STAT_1_DATA_RDY_INTR__MSK               (0x10)
#define BMI160_USER_INTR_STAT_1_DATA_RDY_INTR__REG               \
        (BMI160_USER_INTR_STAT_1_ADDR)
/**************************************************************/
/**\name    FIFO FULL INTERRUPT STATUS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_1 Description - Reg Addr --> 0x1D, Bit --> 5 */
#define BMI160_USER_INTR_STAT_1_FIFO_FULL_INTR__POS               (5)
#define BMI160_USER_INTR_STAT_1_FIFO_FULL_INTR__LEN               (1)
#define BMI160_USER_INTR_STAT_1_FIFO_FULL_INTR__MSK               (0x20)
#define BMI160_USER_INTR_STAT_1_FIFO_FULL_INTR__REG               \
        (BMI160_USER_INTR_STAT_1_ADDR)
/**************************************************************/
/**\name FIFO WATERMARK INTERRUPT STATUS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_1 Description - Reg Addr --> 0x1D, Bit --> 6 */
#define BMI160_USER_INTR_STAT_1_FIFO_WM_INTR__POS               (6)
#define BMI160_USER_INTR_STAT_1_FIFO_WM_INTR__LEN               (1)
#define BMI160_USER_INTR_STAT_1_FIFO_WM_INTR__MSK               (0x40)
#define BMI160_USER_INTR_STAT_1_FIFO_WM_INTR__REG               \
        (BMI160_USER_INTR_STAT_1_ADDR)
/**************************************************************/
/**\name    NO MOTION INTERRUPT STATUS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_1 Description - Reg Addr --> 0x1D, Bit --> 7 */
#define BMI160_USER_INTR_STAT_1_NOMOTION_INTR__POS               (7)
#define BMI160_USER_INTR_STAT_1_NOMOTION_INTR__LEN               (1)
#define BMI160_USER_INTR_STAT_1_NOMOTION_INTR__MSK               (0x80)
#define BMI160_USER_INTR_STAT_1_NOMOTION_INTR__REG               \
        (BMI160_USER_INTR_STAT_1_ADDR)
/**************************************************************/
/**\name    ANY MOTION-XYZ AXIS INTERRUPT STATUS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_2 Description - Reg Addr --> 0x1E, Bit --> 0 */
#define BMI160_USER_INTR_STAT_2_ANY_MOTION_FIRST_X__POS               (0)
#define BMI160_USER_INTR_STAT_2_ANY_MOTION_FIRST_X__LEN               (1)
#define BMI160_USER_INTR_STAT_2_ANY_MOTION_FIRST_X__MSK               (0x01)
#define BMI160_USER_INTR_STAT_2_ANY_MOTION_FIRST_X__REG               \
        (BMI160_USER_INTR_STAT_2_ADDR)

/* Int_Status_2 Description - Reg Addr --> 0x1E, Bit --> 1 */
#define BMI160_USER_INTR_STAT_2_ANY_MOTION_FIRST_Y__POS               (1)
#define BMI160_USER_INTR_STAT_2_ANY_MOTION_FIRST_Y__LEN               (1)
#define BMI160_USER_INTR_STAT_2_ANY_MOTION_FIRST_Y__MSK               (0x02)
#define BMI160_USER_INTR_STAT_2_ANY_MOTION_FIRST_Y__REG               \
        (BMI160_USER_INTR_STAT_2_ADDR)

/* Int_Status_2 Description - Reg Addr --> 0x1E, Bit --> 2 */
#define BMI160_USER_INTR_STAT_2_ANY_MOTION_FIRST_Z__POS               (2)
#define BMI160_USER_INTR_STAT_2_ANY_MOTION_FIRST_Z__LEN               (1)
#define BMI160_USER_INTR_STAT_2_ANY_MOTION_FIRST_Z__MSK               (0x04)
#define BMI160_USER_INTR_STAT_2_ANY_MOTION_FIRST_Z__REG               \
        (BMI160_USER_INTR_STAT_2_ADDR)
/**************************************************************/
/**\name    ANY MOTION SIGN LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_2 Description - Reg Addr --> 0x1E, Bit --> 3 */
#define BMI160_USER_INTR_STAT_2_ANY_MOTION_SIGN__POS               (3)
#define BMI160_USER_INTR_STAT_2_ANY_MOTION_SIGN__LEN               (1)
#define BMI160_USER_INTR_STAT_2_ANY_MOTION_SIGN__MSK               (0x08)
#define BMI160_USER_INTR_STAT_2_ANY_MOTION_SIGN__REG               \
        (BMI160_USER_INTR_STAT_2_ADDR)
/**************************************************************/
/**\name    TAP_XYZ AND SIGN LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_2 Description - Reg Addr --> 0x1E, Bit --> 4 */
#define BMI160_USER_INTR_STAT_2_TAP_FIRST_X__POS               (4)
#define BMI160_USER_INTR_STAT_2_TAP_FIRST_X__LEN               (1)
#define BMI160_USER_INTR_STAT_2_TAP_FIRST_X__MSK               (0x10)
#define BMI160_USER_INTR_STAT_2_TAP_FIRST_X__REG               \
        (BMI160_USER_INTR_STAT_2_ADDR)

/* Int_Status_2 Description - Reg Addr --> 0x1E, Bit --> 5 */
#define BMI160_USER_INTR_STAT_2_TAP_FIRST_Y__POS               (5)
#define BMI160_USER_INTR_STAT_2_TAP_FIRST_Y__LEN               (1)
#define BMI160_USER_INTR_STAT_2_TAP_FIRST_Y__MSK               (0x20)
#define BMI160_USER_INTR_STAT_2_TAP_FIRST_Y__REG               \
        (BMI160_USER_INTR_STAT_2_ADDR)

/* Int_Status_2 Description - Reg Addr --> 0x1E, Bit --> 6 */
#define BMI160_USER_INTR_STAT_2_TAP_FIRST_Z__POS               (6)
#define BMI160_USER_INTR_STAT_2_TAP_FIRST_Z__LEN               (1)
#define BMI160_USER_INTR_STAT_2_TAP_FIRST_Z__MSK               (0x40)
#define BMI160_USER_INTR_STAT_2_TAP_FIRST_Z__REG               \
        (BMI160_USER_INTR_STAT_2_ADDR)

/* Int_Status_2 Description - Reg Addr --> 0x1E, Bit --> 7 */
#define BMI160_USER_INTR_STAT_2_TAP_SIGN__POS               (7)
#define BMI160_USER_INTR_STAT_2_TAP_SIGN__LEN               (1)
#define BMI160_USER_INTR_STAT_2_TAP_SIGN__MSK               (0x80)
#define BMI160_USER_INTR_STAT_2_TAP_SIGN__REG               \
        (BMI160_USER_INTR_STAT_2_ADDR)
/**************************************************************/
/**\name    INTERRUPT SATAUS FOR WHOLE 0x1E LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_2 Description - Reg Addr --> 0x1E, Bit --> 0...7 */
#define BMI160_USER_INTR_STAT_2__POS               (0)
#define BMI160_USER_INTR_STAT_2__LEN               (8)
#define BMI160_USER_INTR_STAT_2__MSK               (0xFF)
#define BMI160_USER_INTR_STAT_2__REG               \
        (BMI160_USER_INTR_STAT_2_ADDR)
/**************************************************************/
/**\name    HIGH_G-XYZ AND SIGN LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_3 Description - Reg Addr --> (0x1F), Bit --> 0 */
#define BMI160_USER_INTR_STAT_3_HIGH_G_FIRST_X__POS               (0)
#define BMI160_USER_INTR_STAT_3_HIGH_G_FIRST_X__LEN               (1)
#define BMI160_USER_INTR_STAT_3_HIGH_G_FIRST_X__MSK               (0x01)
#define BMI160_USER_INTR_STAT_3_HIGH_G_FIRST_X__REG               \
        (BMI160_USER_INTR_STAT_3_ADDR)

/* Int_Status_3 Description - Reg Addr --> 0x1E, Bit --> 1 */
#define BMI160_USER_INTR_STAT_3_HIGH_G_FIRST_Y__POS               (1)
#define BMI160_USER_INTR_STAT_3_HIGH_G_FIRST_Y__LEN               (1)
#define BMI160_USER_INTR_STAT_3_HIGH_G_FIRST_Y__MSK               (0x02)
#define BMI160_USER_INTR_STAT_3_HIGH_G_FIRST_Y__REG               \
        (BMI160_USER_INTR_STAT_3_ADDR)

/* Int_Status_3 Description - Reg Addr --> (0x1F), Bit --> 2 */
#define BMI160_USER_INTR_STAT_3_HIGH_G_FIRST_Z__POS               (2)
#define BMI160_USER_INTR_STAT_3_HIGH_G_FIRST_Z__LEN               (1)
#define BMI160_USER_INTR_STAT_3_HIGH_G_FIRST_Z__MSK               (0x04)
#define BMI160_USER_INTR_STAT_3_HIGH_G_FIRST_Z__REG               \
        (BMI160_USER_INTR_STAT_3_ADDR)

/* Int_Status_3 Description - Reg Addr --> (0x1F), Bit --> 3 */
#define BMI160_USER_INTR_STAT_3_HIGH_G_SIGN__POS               (3)
#define BMI160_USER_INTR_STAT_3_HIGH_G_SIGN__LEN               (1)
#define BMI160_USER_INTR_STAT_3_HIGH_G_SIGN__MSK               (0x08)
#define BMI160_USER_INTR_STAT_3_HIGH_G_SIGN__REG               \
        (BMI160_USER_INTR_STAT_3_ADDR)
/**************************************************************/
/**\name    ORIENT XY and Z AXIS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_3 Description - Reg Addr --> (0x1F), Bit --> 4...5 */
#define BMI160_USER_INTR_STAT_3_ORIENT_XY__POS               (4)
#define BMI160_USER_INTR_STAT_3_ORIENT_XY__LEN               (2)
#define BMI160_USER_INTR_STAT_3_ORIENT_XY__MSK               (0x30)
#define BMI160_USER_INTR_STAT_3_ORIENT_XY__REG               \
        (BMI160_USER_INTR_STAT_3_ADDR)

/* Int_Status_3 Description - Reg Addr --> (0x1F), Bit --> 6 */
#define BMI160_USER_INTR_STAT_3_ORIENT_Z__POS               (6)
#define BMI160_USER_INTR_STAT_3_ORIENT_Z__LEN               (1)
#define BMI160_USER_INTR_STAT_3_ORIENT_Z__MSK               (0x40)
#define BMI160_USER_INTR_STAT_3_ORIENT_Z__REG               \
        (BMI160_USER_INTR_STAT_3_ADDR)
/**************************************************************/
/**\name    FLAT LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_3 Description - Reg Addr --> (0x1F), Bit --> 7 */
#define BMI160_USER_INTR_STAT_3_FLAT__POS               (7)
#define BMI160_USER_INTR_STAT_3_FLAT__LEN               (1)
#define BMI160_USER_INTR_STAT_3_FLAT__MSK               (0x80)
#define BMI160_USER_INTR_STAT_3_FLAT__REG               \
        (BMI160_USER_INTR_STAT_3_ADDR)
/**************************************************************/
/**\name    (0x1F) LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Status_3 Description - Reg Addr --> (0x1F), Bit --> 0...7 */
#define BMI160_USER_INTR_STAT_3__POS               (0)
#define BMI160_USER_INTR_STAT_3__LEN               (8)
#define BMI160_USER_INTR_STAT_3__MSK               (0xFF)
#define BMI160_USER_INTR_STAT_3__REG               \
        (BMI160_USER_INTR_STAT_3_ADDR)
/**************************************************************/
/**\name    TEMPERATURE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Temperature Description - LSB Reg Addr --> (0x20), Bit --> 0...7 */
#define BMI160_USER_TEMP_LSB_VALUE__POS               (0)
#define BMI160_USER_TEMP_LSB_VALUE__LEN               (8)
#define BMI160_USER_TEMP_LSB_VALUE__MSK               (0xFF)
#define BMI160_USER_TEMP_LSB_VALUE__REG               \
        (BMI160_USER_TEMPERATURE_0_ADDR)

/* Temperature Description - LSB Reg Addr --> 0x21, Bit --> 0...7 */
#define BMI160_USER_TEMP_MSB_VALUE__POS               (0)
#define BMI160_USER_TEMP_MSB_VALUE__LEN               (8)
#define BMI160_USER_TEMP_MSB_VALUE__MSK               (0xFF)
#define BMI160_USER_TEMP_MSB_VALUE__REG               \
        (BMI160_USER_TEMPERATURE_1_ADDR)

#ifdef FIFO_ENABLE
/**************************************************************/
/**\name    FIFO BYTE COUNTER LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Fifo_Length0 Description - Reg Addr --> 0x22, Bit --> 0...7 */
#define BMI160_USER_FIFO_BYTE_COUNTER_LSB__POS           (0)
#define BMI160_USER_FIFO_BYTE_COUNTER_LSB__LEN           (8)
#define BMI160_USER_FIFO_BYTE_COUNTER_LSB__MSK          (0xFF)
#define BMI160_USER_FIFO_BYTE_COUNTER_LSB__REG          \
        (BMI160_USER_FIFO_LENGTH_0_ADDR)

/*Fifo_Length1 Description - Reg Addr --> 0x23, Bit --> 0...2 */
#define BMI160_USER_FIFO_BYTE_COUNTER_MSB__POS           (0)
#define BMI160_USER_FIFO_BYTE_COUNTER_MSB__LEN           3
#define BMI160_USER_FIFO_BYTE_COUNTER_MSB__MSK          (0x07)
#define BMI160_USER_FIFO_BYTE_COUNTER_MSB__REG          \
        (BMI160_USER_FIFO_LENGTH_1_ADDR)

/**************************************************************/
/**\name    FIFO DATA LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Fifo_Data Description - Reg Addr --> 0x24, Bit --> 0...7 */
#define BMI160_USER_FIFO_DATA__POS           (0)
#define BMI160_USER_FIFO_DATA__LEN           (8)
#define BMI160_USER_FIFO_DATA__MSK          (0xFF)
#define BMI160_USER_FIFO_DATA__REG          (BMI160_USER_FIFO_DATA_ADDR)
#endif
/**************************************************************/
/**\name    ACCEL CONFIGURATION LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Acc_Conf Description - Reg Addr --> (0x40), Bit --> 0...3 */
#define BMI160_USER_ACCEL_CONFIG_OUTPUT_DATA_RATE__POS               (0)
#define BMI160_USER_ACCEL_CONFIG_OUTPUT_DATA_RATE__LEN               (4)
#define BMI160_USER_ACCEL_CONFIG_OUTPUT_DATA_RATE__MSK               (0x0F)
#define BMI160_USER_ACCEL_CONFIG_OUTPUT_DATA_RATE__REG             \
(BMI160_USER_ACCEL_CONFIG_ADDR)

/* Acc_Conf Description - Reg Addr --> (0x40), Bit --> 4...6 */
#define BMI160_USER_ACCEL_CONFIG_ACCEL_BW__POS               (4)
#define BMI160_USER_ACCEL_CONFIG_ACCEL_BW__LEN               (3)
#define BMI160_USER_ACCEL_CONFIG_ACCEL_BW__MSK               (0x70)
#define BMI160_USER_ACCEL_CONFIG_ACCEL_BW__REG  (BMI160_USER_ACCEL_CONFIG_ADDR)

/* Acc_Conf Description - Reg Addr --> (0x40), Bit --> 7 */
#define BMI160_USER_ACCEL_CONFIG_ACCEL_UNDER_SAMPLING__POS           (7)
#define BMI160_USER_ACCEL_CONFIG_ACCEL_UNDER_SAMPLING__LEN           (1)
#define BMI160_USER_ACCEL_CONFIG_ACCEL_UNDER_SAMPLING__MSK           (0x80)
#define BMI160_USER_ACCEL_CONFIG_ACCEL_UNDER_SAMPLING__REG  \
(BMI160_USER_ACCEL_CONFIG_ADDR)

/* Acc_Range Description - Reg Addr --> 0x41, Bit --> 0...3 */
#define BMI160_USER_ACCEL_RANGE__POS               (0)
#define BMI160_USER_ACCEL_RANGE__LEN               (4)
#define BMI160_USER_ACCEL_RANGE__MSK               (0x0F)
#define BMI160_USER_ACCEL_RANGE__REG              \
(BMI160_USER_ACCEL_RANGE_ADDR)
/**************************************************************/
/**\name    GYRO CONFIGURATION LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Gyro_Conf Description - Reg Addr --> (0x42), Bit --> 0...3 */
#define BMI160_USER_GYRO_CONFIG_OUTPUT_DATA_RATE__POS               (0)
#define BMI160_USER_GYRO_CONFIG_OUTPUT_DATA_RATE__LEN               (4)
#define BMI160_USER_GYRO_CONFIG_OUTPUT_DATA_RATE__MSK               (0x0F)
#define BMI160_USER_GYRO_CONFIG_OUTPUT_DATA_RATE__REG               \
(BMI160_USER_GYRO_CONFIG_ADDR)

/* Gyro_Conf Description - Reg Addr --> (0x42), Bit --> 4...5 */
#define BMI160_USER_GYRO_CONFIG_BW__POS               (4)
#define BMI160_USER_GYRO_CONFIG_BW__LEN               (2)
#define BMI160_USER_GYRO_CONFIG_BW__MSK               (0x30)
#define BMI160_USER_GYRO_CONFIG_BW__REG               \
(BMI160_USER_GYRO_CONFIG_ADDR)

/* Gyr_Range Description - Reg Addr --> 0x43, Bit --> 0...2 */
#define BMI160_USER_GYRO_RANGE__POS               (0)
#define BMI160_USER_GYRO_RANGE__LEN               (3)
#define BMI160_USER_GYRO_RANGE__MSK               (0x07)
#define BMI160_USER_GYRO_RANGE__REG               (BMI160_USER_GYRO_RANGE_ADDR)
/**************************************************************/
/**\name    MAG CONFIGURATION LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Mag_Conf Description - Reg Addr --> (0x44), Bit --> 0...3 */
#define BMI160_USER_MAG_CONFIG_OUTPUT_DATA_RATE__POS               (0)
#define BMI160_USER_MAG_CONFIG_OUTPUT_DATA_RATE__LEN               (4)
#define BMI160_USER_MAG_CONFIG_OUTPUT_DATA_RATE__MSK               (0x0F)
#define BMI160_USER_MAG_CONFIG_OUTPUT_DATA_RATE__REG               \
(BMI160_USER_MAG_CONFIG_ADDR)

#ifdef FIFO_ENABLE
/**************************************************************/
/**\name    FIFO DOWNS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Fifo_Downs Description - Reg Addr --> 0x45, Bit --> 0...2 */
#define BMI160_USER_FIFO_DOWN_GYRO__POS               (0)
#define BMI160_USER_FIFO_DOWN_GYRO__LEN               (3)
#define BMI160_USER_FIFO_DOWN_GYRO__MSK               (0x07)
#define BMI160_USER_FIFO_DOWN_GYRO__REG (BMI160_USER_FIFO_DOWN_ADDR)
/**************************************************************/
/**\name    FIFO FILTER FOR ACCEL AND GYRO LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Fifo_filt Description - Reg Addr --> 0x45, Bit --> 3 */
#define BMI160_USER_FIFO_FILTER_GYRO__POS               (3)
#define BMI160_USER_FIFO_FILTER_GYRO__LEN               (1)
#define BMI160_USER_FIFO_FILTER_GYRO__MSK               (0x08)
#define BMI160_USER_FIFO_FILTER_GYRO__REG     (BMI160_USER_FIFO_DOWN_ADDR)

/* Fifo_Downs Description - Reg Addr --> 0x45, Bit --> 4...6 */
#define BMI160_USER_FIFO_DOWN_ACCEL__POS               (4)
#define BMI160_USER_FIFO_DOWN_ACCEL__LEN               (3)
#define BMI160_USER_FIFO_DOWN_ACCEL__MSK               (0x70)
#define BMI160_USER_FIFO_DOWN_ACCEL__REG    (BMI160_USER_FIFO_DOWN_ADDR)

/* Fifo_FILT Description - Reg Addr --> 0x45, Bit --> 7 */
#define BMI160_USER_FIFO_FILTER_ACCEL__POS               (7)
#define BMI160_USER_FIFO_FILTER_ACCEL__LEN               (1)
#define BMI160_USER_FIFO_FILTER_ACCEL__MSK               (0x80)
#define BMI160_USER_FIFO_FILTER_ACCEL__REG  (BMI160_USER_FIFO_DOWN_ADDR)
/**************************************************************/
/**\name    FIFO WATER MARK LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Fifo_Config_0 Description - Reg Addr --> 0x46, Bit --> 0...7 */
#define BMI160_USER_FIFO_WM__POS               (0)
#define BMI160_USER_FIFO_WM__LEN               (8)
#define BMI160_USER_FIFO_WM__MSK               (0xFF)
#define BMI160_USER_FIFO_WM__REG    (BMI160_USER_FIFO_CONFIG_0_ADDR)
/**************************************************************/
/**\name    FIFO TIME LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Fifo_Config_1 Description - Reg Addr --> 0x47, Bit --> 1 */
#define BMI160_USER_FIFO_TIME_ENABLE__POS               (1)
#define BMI160_USER_FIFO_TIME_ENABLE__LEN               (1)
#define BMI160_USER_FIFO_TIME_ENABLE__MSK               (0x02)
#define BMI160_USER_FIFO_TIME_ENABLE__REG   (BMI160_USER_FIFO_CONFIG_1_ADDR)
/**************************************************************/
/**\name    FIFO TAG INTERRUPT LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Fifo_Config_1 Description - Reg Addr --> 0x47, Bit --> 2 */
#define BMI160_USER_FIFO_TAG_INTR2_ENABLE__POS               (2)
#define BMI160_USER_FIFO_TAG_INTR2_ENABLE__LEN               (1)
#define BMI160_USER_FIFO_TAG_INTR2_ENABLE__MSK               (0x04)
#define BMI160_USER_FIFO_TAG_INTR2_ENABLE__REG  (BMI160_USER_FIFO_CONFIG_1_ADDR)

/* Fifo_Config_1 Description - Reg Addr --> 0x47, Bit --> 3 */
#define BMI160_USER_FIFO_TAG_INTR1_ENABLE__POS               (3)
#define BMI160_USER_FIFO_TAG_INTR1_ENABLE__LEN               (1)
#define BMI160_USER_FIFO_TAG_INTR1_ENABLE__MSK               (0x08)
#define BMI160_USER_FIFO_TAG_INTR1_ENABLE__REG  (BMI160_USER_FIFO_CONFIG_1_ADDR)
/**************************************************************/
/**\name    FIFO HEADER LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Fifo_Config_1 Description - Reg Addr --> 0x47, Bit --> 4 */
#define BMI160_USER_FIFO_HEADER_ENABLE__POS               (4)
#define BMI160_USER_FIFO_HEADER_ENABLE__LEN               (1)
#define BMI160_USER_FIFO_HEADER_ENABLE__MSK               (0x10)
#define BMI160_USER_FIFO_HEADER_ENABLE__REG              \
(BMI160_USER_FIFO_CONFIG_1_ADDR)
/**************************************************************/
/**\name    FIFO MAG ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Fifo_Config_1 Description - Reg Addr --> 0x47, Bit --> 5 */
#define BMI160_USER_FIFO_MAG_ENABLE__POS               (5)
#define BMI160_USER_FIFO_MAG_ENABLE__LEN               (1)
#define BMI160_USER_FIFO_MAG_ENABLE__MSK               (0x20)
#define BMI160_USER_FIFO_MAG_ENABLE__REG             \
(BMI160_USER_FIFO_CONFIG_1_ADDR)
/**************************************************************/
/**\name    FIFO ACCEL ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Fifo_Config_1 Description - Reg Addr --> 0x47, Bit --> 6 */
#define BMI160_USER_FIFO_ACCEL_ENABLE__POS               (6)
#define BMI160_USER_FIFO_ACCEL_ENABLE__LEN               (1)
#define BMI160_USER_FIFO_ACCEL_ENABLE__MSK               (0x40)
#define BMI160_USER_FIFO_ACCEL_ENABLE__REG              \
(BMI160_USER_FIFO_CONFIG_1_ADDR)
/**************************************************************/
/**\name    FIFO GYRO ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Fifo_Config_1 Description - Reg Addr --> 0x47, Bit --> 7 */
#define BMI160_USER_FIFO_GYRO_ENABLE__POS               (7)
#define BMI160_USER_FIFO_GYRO_ENABLE__LEN               (1)
#define BMI160_USER_FIFO_GYRO_ENABLE__MSK               (0x80)
#define BMI160_USER_FIFO_GYRO_ENABLE__REG              \
(BMI160_USER_FIFO_CONFIG_1_ADDR)
#endif
/**************************************************************/
/**\name    MAG I2C ADDRESS SELECTION LENGTH, POSITION AND MASK*/
/**************************************************************/

/* Mag_IF_0 Description - Reg Addr --> 0x4b, Bit --> 1...7 */
#define BMI160_USER_I2C_DEVICE_ADDR__POS               (1)
#define BMI160_USER_I2C_DEVICE_ADDR__LEN               (7)
#define BMI160_USER_I2C_DEVICE_ADDR__MSK               (0xFE)
#define BMI160_USER_I2C_DEVICE_ADDR__REG    (BMI160_USER_MAG_IF_0_ADDR)
/**************************************************************/
/**\name MAG CONFIGURATION FOR SECONDARY
    INTERFACE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Mag_IF_1 Description - Reg Addr --> 0x4c, Bit --> 0...1 */
#define BMI160_USER_MAG_BURST__POS               (0)
#define BMI160_USER_MAG_BURST__LEN               (2)
#define BMI160_USER_MAG_BURST__MSK               (0x03)
#define BMI160_USER_MAG_BURST__REG               (BMI160_USER_MAG_IF_1_ADDR)

/* Mag_IF_1 Description - Reg Addr --> 0x4c, Bit --> 2...5 */
#define BMI160_USER_MAG_OFFSET__POS               (2)
#define BMI160_USER_MAG_OFFSET__LEN               (4)
#define BMI160_USER_MAG_OFFSET__MSK               (0x3C)
#define BMI160_USER_MAG_OFFSET__REG               (BMI160_USER_MAG_IF_1_ADDR)

/* Mag_IF_1 Description - Reg Addr --> 0x4c, Bit --> 7 */
#define BMI160_USER_MAG_MANUAL_ENABLE__POS               (7)
#define BMI160_USER_MAG_MANUAL_ENABLE__LEN               (1)
#define BMI160_USER_MAG_MANUAL_ENABLE__MSK               (0x80)
#define BMI160_USER_MAG_MANUAL_ENABLE__REG               \
(BMI160_USER_MAG_IF_1_ADDR)

/* Mag_IF_2 Description - Reg Addr --> 0x4d, Bit -->0... 7 */
#define BMI160_USER_READ_ADDR__POS               (0)
#define BMI160_USER_READ_ADDR__LEN               (8)
#define BMI160_USER_READ_ADDR__MSK               (0xFF)
#define BMI160_USER_READ_ADDR__REG               (BMI160_USER_MAG_IF_2_ADDR)

/* Mag_IF_3 Description - Reg Addr --> 0x4e, Bit -->0... 7 */
#define BMI160_USER_WRITE_ADDR__POS               (0)
#define BMI160_USER_WRITE_ADDR__LEN               (8)
#define BMI160_USER_WRITE_ADDR__MSK               (0xFF)
#define BMI160_USER_WRITE_ADDR__REG               (BMI160_USER_MAG_IF_3_ADDR)

/* Mag_IF_4 Description - Reg Addr --> 0x4f, Bit -->0... 7 */
#define BMI160_USER_WRITE_DATA__POS               (0)
#define BMI160_USER_WRITE_DATA__LEN               (8)
#define BMI160_USER_WRITE_DATA__MSK               (0xFF)
#define BMI160_USER_WRITE_DATA__REG               (BMI160_USER_MAG_IF_4_ADDR)
/**************************************************************/
/**\name    ANY MOTION XYZ AXIS ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_En_0 Description - Reg Addr --> 0x50, Bit -->0 */
#define BMI160_USER_INTR_ENABLE_0_ANY_MOTION_X_ENABLE__POS               (0)
#define BMI160_USER_INTR_ENABLE_0_ANY_MOTION_X_ENABLE__LEN               (1)
#define BMI160_USER_INTR_ENABLE_0_ANY_MOTION_X_ENABLE__MSK               (0x01)
#define BMI160_USER_INTR_ENABLE_0_ANY_MOTION_X_ENABLE__REG                \
(BMI160_USER_INTR_ENABLE_0_ADDR)

/* Int_En_0 Description - Reg Addr --> 0x50, Bit -->1 */
#define BMI160_USER_INTR_ENABLE_0_ANY_MOTION_Y_ENABLE__POS               (1)
#define BMI160_USER_INTR_ENABLE_0_ANY_MOTION_Y_ENABLE__LEN               (1)
#define BMI160_USER_INTR_ENABLE_0_ANY_MOTION_Y_ENABLE__MSK               (0x02)
#define BMI160_USER_INTR_ENABLE_0_ANY_MOTION_Y_ENABLE__REG            \
(BMI160_USER_INTR_ENABLE_0_ADDR)

/* Int_En_0 Description - Reg Addr --> 0x50, Bit -->2 */
#define BMI160_USER_INTR_ENABLE_0_ANY_MOTION_Z_ENABLE__POS               (2)
#define BMI160_USER_INTR_ENABLE_0_ANY_MOTION_Z_ENABLE__LEN               (1)
#define BMI160_USER_INTR_ENABLE_0_ANY_MOTION_Z_ENABLE__MSK               (0x04)
#define BMI160_USER_INTR_ENABLE_0_ANY_MOTION_Z_ENABLE__REG              \
(BMI160_USER_INTR_ENABLE_0_ADDR)
/**************************************************************/
/**\name    DOUBLE TAP ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_En_0 Description - Reg Addr --> 0x50, Bit -->4 */
#define BMI160_USER_INTR_ENABLE_0_DOUBLE_TAP_ENABLE__POS               (4)
#define BMI160_USER_INTR_ENABLE_0_DOUBLE_TAP_ENABLE__LEN               (1)
#define BMI160_USER_INTR_ENABLE_0_DOUBLE_TAP_ENABLE__MSK               (0x10)
#define BMI160_USER_INTR_ENABLE_0_DOUBLE_TAP_ENABLE__REG            \
(BMI160_USER_INTR_ENABLE_0_ADDR)
/**************************************************************/
/**\name    SINGLE TAP ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_En_0 Description - Reg Addr --> 0x50, Bit -->5 */
#define BMI160_USER_INTR_ENABLE_0_SINGLE_TAP_ENABLE__POS               (5)
#define BMI160_USER_INTR_ENABLE_0_SINGLE_TAP_ENABLE__LEN               (1)
#define BMI160_USER_INTR_ENABLE_0_SINGLE_TAP_ENABLE__MSK               (0x20)
#define BMI160_USER_INTR_ENABLE_0_SINGLE_TAP_ENABLE__REG           \
(BMI160_USER_INTR_ENABLE_0_ADDR)
/**************************************************************/
/**\name    ORIENT ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_En_0 Description - Reg Addr --> 0x50, Bit -->6 */
#define BMI160_USER_INTR_ENABLE_0_ORIENT_ENABLE__POS               (6)
#define BMI160_USER_INTR_ENABLE_0_ORIENT_ENABLE__LEN               (1)
#define BMI160_USER_INTR_ENABLE_0_ORIENT_ENABLE__MSK               (0x40)
#define BMI160_USER_INTR_ENABLE_0_ORIENT_ENABLE__REG               \
(BMI160_USER_INTR_ENABLE_0_ADDR)
/**************************************************************/
/**\name    FLAT ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_En_0 Description - Reg Addr --> 0x50, Bit -->7 */
#define BMI160_USER_INTR_ENABLE_0_FLAT_ENABLE__POS               (7)
#define BMI160_USER_INTR_ENABLE_0_FLAT_ENABLE__LEN               (1)
#define BMI160_USER_INTR_ENABLE_0_FLAT_ENABLE__MSK               (0x80)
#define BMI160_USER_INTR_ENABLE_0_FLAT_ENABLE__REG             \
(BMI160_USER_INTR_ENABLE_0_ADDR)
/**************************************************************/
/**\name    HIGH_G XYZ ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_En_1 Description - Reg Addr --> (0x51), Bit -->0 */
#define BMI160_USER_INTR_ENABLE_1_HIGH_G_X_ENABLE__POS               (0)
#define BMI160_USER_INTR_ENABLE_1_HIGH_G_X_ENABLE__LEN               (1)
#define BMI160_USER_INTR_ENABLE_1_HIGH_G_X_ENABLE__MSK               (0x01)
#define BMI160_USER_INTR_ENABLE_1_HIGH_G_X_ENABLE__REG             \
(BMI160_USER_INTR_ENABLE_1_ADDR)

/* Int_En_1 Description - Reg Addr --> (0x51), Bit -->1 */
#define BMI160_USER_INTR_ENABLE_1_HIGH_G_Y_ENABLE__POS               (1)
#define BMI160_USER_INTR_ENABLE_1_HIGH_G_Y_ENABLE__LEN               (1)
#define BMI160_USER_INTR_ENABLE_1_HIGH_G_Y_ENABLE__MSK               (0x02)
#define BMI160_USER_INTR_ENABLE_1_HIGH_G_Y_ENABLE__REG             \
(BMI160_USER_INTR_ENABLE_1_ADDR)

/* Int_En_1 Description - Reg Addr --> (0x51), Bit -->2 */
#define BMI160_USER_INTR_ENABLE_1_HIGH_G_Z_ENABLE__POS               (2)
#define BMI160_USER_INTR_ENABLE_1_HIGH_G_Z_ENABLE__LEN               (1)
#define BMI160_USER_INTR_ENABLE_1_HIGH_G_Z_ENABLE__MSK               (0x04)
#define BMI160_USER_INTR_ENABLE_1_HIGH_G_Z_ENABLE__REG             \
(BMI160_USER_INTR_ENABLE_1_ADDR)
/**************************************************************/
/**\name    LOW_G ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_En_1 Description - Reg Addr --> (0x51), Bit -->3 */
#define BMI160_USER_INTR_ENABLE_1_LOW_G_ENABLE__POS               (3)
#define BMI160_USER_INTR_ENABLE_1_LOW_G_ENABLE__LEN               (1)
#define BMI160_USER_INTR_ENABLE_1_LOW_G_ENABLE__MSK               (0x08)
#define BMI160_USER_INTR_ENABLE_1_LOW_G_ENABLE__REG           \
(BMI160_USER_INTR_ENABLE_1_ADDR)
/**************************************************************/
/**\name    DATA READY ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_En_1 Description - Reg Addr --> (0x51), Bit -->4 */
#define BMI160_USER_INTR_ENABLE_1_DATA_RDY_ENABLE__POS               (4)
#define BMI160_USER_INTR_ENABLE_1_DATA_RDY_ENABLE__LEN               (1)
#define BMI160_USER_INTR_ENABLE_1_DATA_RDY_ENABLE__MSK               (0x10)
#define BMI160_USER_INTR_ENABLE_1_DATA_RDY_ENABLE__REG              \
(BMI160_USER_INTR_ENABLE_1_ADDR)

#ifdef FIFO_ENABLE
/**************************************************************/
/**\name    FIFO FULL AND WATER MARK ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_En_1 Description - Reg Addr --> (0x51), Bit -->5 */
#define BMI160_USER_INTR_ENABLE_1_FIFO_FULL_ENABLE__POS               (5)
#define BMI160_USER_INTR_ENABLE_1_FIFO_FULL_ENABLE__LEN               (1)
#define BMI160_USER_INTR_ENABLE_1_FIFO_FULL_ENABLE__MSK               (0x20)
#define BMI160_USER_INTR_ENABLE_1_FIFO_FULL_ENABLE__REG               \
(BMI160_USER_INTR_ENABLE_1_ADDR)

/* Int_En_1 Description - Reg Addr --> (0x51), Bit -->6 */
#define BMI160_USER_INTR_ENABLE_1_FIFO_WM_ENABLE__POS               (6)
#define BMI160_USER_INTR_ENABLE_1_FIFO_WM_ENABLE__LEN               (1)
#define BMI160_USER_INTR_ENABLE_1_FIFO_WM_ENABLE__MSK               (0x40)
#define BMI160_USER_INTR_ENABLE_1_FIFO_WM_ENABLE__REG              \
(BMI160_USER_INTR_ENABLE_1_ADDR)
#endif
/**************************************************************/
/**\name    NO MOTION XYZ ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_En_2 Description - Reg Addr --> (0x52), Bit -->0 */
#define BMI160_USER_INTR_ENABLE_2_NOMOTION_X_ENABLE__POS               (0)
#define BMI160_USER_INTR_ENABLE_2_NOMOTION_X_ENABLE__LEN               (1)
#define BMI160_USER_INTR_ENABLE_2_NOMOTION_X_ENABLE__MSK               (0x01)
#define BMI160_USER_INTR_ENABLE_2_NOMOTION_X_ENABLE__REG      \
(BMI160_USER_INTR_ENABLE_2_ADDR)

/* Int_En_2 Description - Reg Addr --> (0x52), Bit -->1 */
#define BMI160_USER_INTR_ENABLE_2_NOMOTION_Y_ENABLE__POS               (1)
#define BMI160_USER_INTR_ENABLE_2_NOMOTION_Y_ENABLE__LEN               (1)
#define BMI160_USER_INTR_ENABLE_2_NOMOTION_Y_ENABLE__MSK               (0x02)
#define BMI160_USER_INTR_ENABLE_2_NOMOTION_Y_ENABLE__REG      \
(BMI160_USER_INTR_ENABLE_2_ADDR)

/* Int_En_2 Description - Reg Addr --> (0x52), Bit -->2 */
#define BMI160_USER_INTR_ENABLE_2_NOMOTION_Z_ENABLE__POS               (2)
#define BMI160_USER_INTR_ENABLE_2_NOMOTION_Z_ENABLE__LEN               (1)
#define BMI160_USER_INTR_ENABLE_2_NOMOTION_Z_ENABLE__MSK               (0x04)
#define BMI160_USER_INTR_ENABLE_2_NOMOTION_Z_ENABLE__REG      \
(BMI160_USER_INTR_ENABLE_2_ADDR)
/**************************************************************/
/**\name    STEP DETECTOR ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_En_2 Description - Reg Addr --> (0x52), Bit -->3 */
#define BMI160_USER_INTR_ENABLE_2_STEP_DETECTOR_ENABLE__POS               (3)
#define BMI160_USER_INTR_ENABLE_2_STEP_DETECTOR_ENABLE__LEN               (1)
#define BMI160_USER_INTR_ENABLE_2_STEP_DETECTOR_ENABLE__MSK               (0x08)
#define BMI160_USER_INTR_ENABLE_2_STEP_DETECTOR_ENABLE__REG   \
(BMI160_USER_INTR_ENABLE_2_ADDR)
/**************************************************************/
/**\name    EDGE CONTROL ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Out_Ctrl Description - Reg Addr --> 0x53, Bit -->0 */
#define BMI160_USER_INTR1_EDGE_CTRL__POS               (0)
#define BMI160_USER_INTR1_EDGE_CTRL__LEN               (1)
#define BMI160_USER_INTR1_EDGE_CTRL__MSK               (0x01)
#define BMI160_USER_INTR1_EDGE_CTRL__REG        \
(BMI160_USER_INTR_OUT_CTRL_ADDR)
/**************************************************************/
/**\name    LEVEL CONTROL ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Out_Ctrl Description - Reg Addr --> 0x53, Bit -->1 */
#define BMI160_USER_INTR1_LEVEL__POS               (1)
#define BMI160_USER_INTR1_LEVEL__LEN               (1)
#define BMI160_USER_INTR1_LEVEL__MSK               (0x02)
#define BMI160_USER_INTR1_LEVEL__REG               \
(BMI160_USER_INTR_OUT_CTRL_ADDR)
/**************************************************************/
/**\name    OUTPUT TYPE ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Out_Ctrl Description - Reg Addr --> 0x53, Bit -->2 */
#define BMI160_USER_INTR1_OUTPUT_TYPE__POS               (2)
#define BMI160_USER_INTR1_OUTPUT_TYPE__LEN               (1)
#define BMI160_USER_INTR1_OUTPUT_TYPE__MSK               (0x04)
#define BMI160_USER_INTR1_OUTPUT_TYPE__REG               \
(BMI160_USER_INTR_OUT_CTRL_ADDR)
/**************************************************************/
/**\name    OUTPUT TYPE ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Out_Ctrl Description - Reg Addr --> 0x53, Bit -->3 */
#define BMI160_USER_INTR1_OUTPUT_ENABLE__POS               (3)
#define BMI160_USER_INTR1_OUTPUT_ENABLE__LEN               (1)
#define BMI160_USER_INTR1_OUTPUT_ENABLE__MSK               (0x08)
#define BMI160_USER_INTR1_OUTPUT_ENABLE__REG        \
(BMI160_USER_INTR_OUT_CTRL_ADDR)
/**************************************************************/
/**\name    EDGE CONTROL ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Out_Ctrl Description - Reg Addr --> 0x53, Bit -->4 */
#define BMI160_USER_INTR2_EDGE_CTRL__POS               (4)
#define BMI160_USER_INTR2_EDGE_CTRL__LEN               (1)
#define BMI160_USER_INTR2_EDGE_CTRL__MSK               (0x10)
#define BMI160_USER_INTR2_EDGE_CTRL__REG        \
(BMI160_USER_INTR_OUT_CTRL_ADDR)
/**************************************************************/
/**\name    LEVEL CONTROL ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Out_Ctrl Description - Reg Addr --> 0x53, Bit -->5 */
#define BMI160_USER_INTR2_LEVEL__POS               (5)
#define BMI160_USER_INTR2_LEVEL__LEN               (1)
#define BMI160_USER_INTR2_LEVEL__MSK               (0x20)
#define BMI160_USER_INTR2_LEVEL__REG               \
(BMI160_USER_INTR_OUT_CTRL_ADDR)
/**************************************************************/
/**\name    OUTPUT TYPE ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Out_Ctrl Description - Reg Addr --> 0x53, Bit -->6 */
#define BMI160_USER_INTR2_OUTPUT_TYPE__POS               (6)
#define BMI160_USER_INTR2_OUTPUT_TYPE__LEN               (1)
#define BMI160_USER_INTR2_OUTPUT_TYPE__MSK               (0x40)
#define BMI160_USER_INTR2_OUTPUT_TYPE__REG               \
(BMI160_USER_INTR_OUT_CTRL_ADDR)

/* Int_Out_Ctrl Description - Reg Addr --> 0x53, Bit -->7 */
#define BMI160_USER_INTR2_OUTPUT_EN__POS               (7)
#define BMI160_USER_INTR2_OUTPUT_EN__LEN               (1)
#define BMI160_USER_INTR2_OUTPUT_EN__MSK               (0x80)
#define BMI160_USER_INTR2_OUTPUT_EN__REG        \
(BMI160_USER_INTR_OUT_CTRL_ADDR)
/**************************************************************/
/**\name    LATCH INTERRUPT LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Latch Description - Reg Addr --> 0x54, Bit -->0...3 */
#define BMI160_USER_INTR_LATCH__POS               (0)
#define BMI160_USER_INTR_LATCH__LEN               (4)
#define BMI160_USER_INTR_LATCH__MSK               (0x0F)
#define BMI160_USER_INTR_LATCH__REG               (BMI160_USER_INTR_LATCH_ADDR)
/**************************************************************/
/**\name    INPUT ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Latch Description - Reg Addr --> 0x54, Bit -->4 */
#define BMI160_USER_INTR1_INPUT_ENABLE__POS               (4)
#define BMI160_USER_INTR1_INPUT_ENABLE__LEN               (1)
#define BMI160_USER_INTR1_INPUT_ENABLE__MSK               (0x10)
#define BMI160_USER_INTR1_INPUT_ENABLE__REG               \
(BMI160_USER_INTR_LATCH_ADDR)

/* Int_Latch Description - Reg Addr --> 0x54, Bit -->5*/
#define BMI160_USER_INTR2_INPUT_ENABLE__POS               (5)
#define BMI160_USER_INTR2_INPUT_ENABLE__LEN               (1)
#define BMI160_USER_INTR2_INPUT_ENABLE__MSK               (0x20)
#define BMI160_USER_INTR2_INPUT_ENABLE__REG              \
(BMI160_USER_INTR_LATCH_ADDR)
/**************************************************************/
/**\name    INTERRUPT1 MAPPIONG OF LOW_G LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_0 Description - Reg Addr --> 0x55, Bit -->0 */
#define BMI160_USER_INTR_MAP_0_INTR1_LOW_G__POS               (0)
#define BMI160_USER_INTR_MAP_0_INTR1_LOW_G__LEN               (1)
#define BMI160_USER_INTR_MAP_0_INTR1_LOW_G__MSK               (0x01)
#define BMI160_USER_INTR_MAP_0_INTR1_LOW_G__REG (BMI160_USER_INTR_MAP_0_ADDR)
/**************************************************************/
/**\name    INTERRUPT1 MAPPIONG OF HIGH_G LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_0 Description - Reg Addr --> 0x55, Bit -->1 */
#define BMI160_USER_INTR_MAP_0_INTR1_HIGH_G__POS               (1)
#define BMI160_USER_INTR_MAP_0_INTR1_HIGH_G__LEN               (1)
#define BMI160_USER_INTR_MAP_0_INTR1_HIGH_G__MSK               (0x02)
#define BMI160_USER_INTR_MAP_0_INTR1_HIGH_G__REG    \
(BMI160_USER_INTR_MAP_0_ADDR)
/**************************************************************/
/**\name    INTERRUPT MAPPIONG OF ANY MOTION_G LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_0 Description - Reg Addr --> 0x55, Bit -->2 */
#define BMI160_USER_INTR_MAP_0_INTR1_ANY_MOTION__POS               (2)
#define BMI160_USER_INTR_MAP_0_INTR1_ANY_MOTION__LEN               (1)
#define BMI160_USER_INTR_MAP_0_INTR1_ANY_MOTION__MSK               (0x04)
#define BMI160_USER_INTR_MAP_0_INTR1_ANY_MOTION__REG            \
(BMI160_USER_INTR_MAP_0_ADDR)
/**************************************************************/
/**\name    INTERRUPT1 MAPPIONG OF NO MOTION LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_0 Description - Reg Addr --> 0x55, Bit -->3 */
#define BMI160_USER_INTR_MAP_0_INTR1_NOMOTION__POS               (3)
#define BMI160_USER_INTR_MAP_0_INTR1_NOMOTION__LEN               (1)
#define BMI160_USER_INTR_MAP_0_INTR1_NOMOTION__MSK               (0x08)
#define BMI160_USER_INTR_MAP_0_INTR1_NOMOTION__REG (BMI160_USER_INTR_MAP_0_ADDR)
/**************************************************************/
/**\name    INTERRUPT1 MAPPIONG OF DOUBLE TAP LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_0 Description - Reg Addr --> 0x55, Bit -->4 */
#define BMI160_USER_INTR_MAP_0_INTR1_DOUBLE_TAP__POS               (4)
#define BMI160_USER_INTR_MAP_0_INTR1_DOUBLE_TAP__LEN               (1)
#define BMI160_USER_INTR_MAP_0_INTR1_DOUBLE_TAP__MSK               (0x10)
#define BMI160_USER_INTR_MAP_0_INTR1_DOUBLE_TAP__REG    \
(BMI160_USER_INTR_MAP_0_ADDR)
/**************************************************************/
/**\name    INTERRUPT1 MAPPIONG OF SINGLE TAP LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_0 Description - Reg Addr --> 0x55, Bit -->5 */
#define BMI160_USER_INTR_MAP_0_INTR1_SINGLE_TAP__POS               (5)
#define BMI160_USER_INTR_MAP_0_INTR1_SINGLE_TAP__LEN               (1)
#define BMI160_USER_INTR_MAP_0_INTR1_SINGLE_TAP__MSK               (0x20)
#define BMI160_USER_INTR_MAP_0_INTR1_SINGLE_TAP__REG          \
(BMI160_USER_INTR_MAP_0_ADDR)
/**************************************************************/
/**\name    INTERRUPT1 MAPPIONG OF ORIENT LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_0 Description - Reg Addr --> 0x55, Bit -->6 */
#define BMI160_USER_INTR_MAP_0_INTR1_ORIENT__POS               (6)
#define BMI160_USER_INTR_MAP_0_INTR1_ORIENT__LEN               (1)
#define BMI160_USER_INTR_MAP_0_INTR1_ORIENT__MSK               (0x40)
#define BMI160_USER_INTR_MAP_0_INTR1_ORIENT__REG              \
(BMI160_USER_INTR_MAP_0_ADDR)
/**************************************************************/
/**\name    INTERRUPT MAPPIONG OF FLAT LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_0 Description - Reg Addr --> 0x56, Bit -->7 */
#define BMI160_USER_INTR_MAP_0_INTR1_FLAT__POS               (7)
#define BMI160_USER_INTR_MAP_0_INTR1_FLAT__LEN               (1)
#define BMI160_USER_INTR_MAP_0_INTR1_FLAT__MSK               (0x80)
#define BMI160_USER_INTR_MAP_0_INTR1_FLAT__REG  (BMI160_USER_INTR_MAP_0_ADDR)
/**************************************************************/
/**\name    INTERRUPT1 MAPPIONG OF PMU TRIGGER LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_1 Description - Reg Addr --> 0x56, Bit -->0 */
#define BMI160_USER_INTR_MAP_1_INTR2_PMU_TRIG__POS               (0)
#define BMI160_USER_INTR_MAP_1_INTR2_PMU_TRIG__LEN               (1)
#define BMI160_USER_INTR_MAP_1_INTR2_PMU_TRIG__MSK               (0x01)
#define BMI160_USER_INTR_MAP_1_INTR2_PMU_TRIG__REG (BMI160_USER_INTR_MAP_1_ADDR)

#ifdef FIFO_ENABLE
/**************************************************************/
/**\name    INTERRUPT1 MAPPIONG OF FIFO FULL AND
    WATER MARK LENGTH, POSITION AND MASK*/
/**************************************************************/

/* Int_Map_1 Description - Reg Addr --> 0x56, Bit -->1 */
#define BMI160_USER_INTR_MAP_1_INTR2_FIFO_FULL__POS               (1)
#define BMI160_USER_INTR_MAP_1_INTR2_FIFO_FULL__LEN               (1)
#define BMI160_USER_INTR_MAP_1_INTR2_FIFO_FULL__MSK               (0x02)
#define BMI160_USER_INTR_MAP_1_INTR2_FIFO_FULL__REG          \
(BMI160_USER_INTR_MAP_1_ADDR)

/* Int_Map_1 Description - Reg Addr --> 0x56, Bit -->2 */
#define BMI160_USER_INTR_MAP_1_INTR2_FIFO_WM__POS               (2)
#define BMI160_USER_INTR_MAP_1_INTR2_FIFO_WM__LEN               (1)
#define BMI160_USER_INTR_MAP_1_INTR2_FIFO_WM__MSK               (0x04)
#define BMI160_USER_INTR_MAP_1_INTR2_FIFO_WM__REG            \
(BMI160_USER_INTR_MAP_1_ADDR)
#endif
/**************************************************************/
/**\name    INTERRUPT1 MAPPIONG OF DATA READY LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_1 Description - Reg Addr --> 0x56, Bit -->3 */
#define BMI160_USER_INTR_MAP_1_INTR2_DATA_RDY__POS               (3)
#define BMI160_USER_INTR_MAP_1_INTR2_DATA_RDY__LEN               (1)
#define BMI160_USER_INTR_MAP_1_INTR2_DATA_RDY__MSK               (0x08)
#define BMI160_USER_INTR_MAP_1_INTR2_DATA_RDY__REG        \
(BMI160_USER_INTR_MAP_1_ADDR)
/**************************************************************/
/**\name    INTERRUPT1 MAPPIONG OF PMU TRIGGER LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_1 Description - Reg Addr --> 0x56, Bit -->4 */
#define BMI160_USER_INTR_MAP_1_INTR1_PMU_TRIG__POS               (4)
#define BMI160_USER_INTR_MAP_1_INTR1_PMU_TRIG__LEN               (1)
#define BMI160_USER_INTR_MAP_1_INTR1_PMU_TRIG__MSK               (0x10)
#define BMI160_USER_INTR_MAP_1_INTR1_PMU_TRIG__REG (BMI160_USER_INTR_MAP_1_ADDR)
/**************************************************************/
/**\name    INTERRUPT1 MAPPIONG OF FIFO FULL AND
    WATER MARK LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_1 Description - Reg Addr --> 0x56, Bit -->5 */
#define BMI160_USER_INTR_MAP_1_INTR1_FIFO_FULL__POS               (5)
#define BMI160_USER_INTR_MAP_1_INTR1_FIFO_FULL__LEN               (1)
#define BMI160_USER_INTR_MAP_1_INTR1_FIFO_FULL__MSK               (0x20)
#define BMI160_USER_INTR_MAP_1_INTR1_FIFO_FULL__REG        \
(BMI160_USER_INTR_MAP_1_ADDR)

/* Int_Map_1 Description - Reg Addr --> 0x56, Bit -->6 */
#define BMI160_USER_INTR_MAP_1_INTR1_FIFO_WM__POS               (6)
#define BMI160_USER_INTR_MAP_1_INTR1_FIFO_WM__LEN               (1)
#define BMI160_USER_INTR_MAP_1_INTR1_FIFO_WM__MSK               (0x40)
#define BMI160_USER_INTR_MAP_1_INTR1_FIFO_WM__REG   \
(BMI160_USER_INTR_MAP_1_ADDR)
/**************************************************************/
/**\name    INTERRUPT1 MAPPIONG OF DATA READY LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_1 Description - Reg Addr --> 0x56, Bit -->7 */
#define BMI160_USER_INTR_MAP_1_INTR1_DATA_RDY__POS               (7)
#define BMI160_USER_INTR_MAP_1_INTR1_DATA_RDY__LEN               (1)
#define BMI160_USER_INTR_MAP_1_INTR1_DATA_RDY__MSK               (0x80)
#define BMI160_USER_INTR_MAP_1_INTR1_DATA_RDY__REG  \
(BMI160_USER_INTR_MAP_1_ADDR)
/**************************************************************/
/**\name    INTERRUPT2 MAPPIONG OF LOW_G LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_2 Description - Reg Addr --> 0x57, Bit -->0 */
#define BMI160_USER_INTR_MAP_2_INTR2_LOW_G__POS               (0)
#define BMI160_USER_INTR_MAP_2_INTR2_LOW_G__LEN               (1)
#define BMI160_USER_INTR_MAP_2_INTR2_LOW_G__MSK               (0x01)
#define BMI160_USER_INTR_MAP_2_INTR2_LOW_G__REG (BMI160_USER_INTR_MAP_2_ADDR)
/**************************************************************/
/**\name    INTERRUPT2 MAPPIONG OF HIGH_G LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_2 Description - Reg Addr --> 0x57, Bit -->1 */
#define BMI160_USER_INTR_MAP_2_INTR2_HIGH_G__POS               (1)
#define BMI160_USER_INTR_MAP_2_INTR2_HIGH_G__LEN               (1)
#define BMI160_USER_INTR_MAP_2_INTR2_HIGH_G__MSK               (0x02)
#define BMI160_USER_INTR_MAP_2_INTR2_HIGH_G__REG    \
(BMI160_USER_INTR_MAP_2_ADDR)
/**************************************************************/
/**\name    INTERRUPT2 MAPPIONG OF ANY MOTION LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_2 Description - Reg Addr --> 0x57, Bit -->2 */
#define BMI160_USER_INTR_MAP_2_INTR2_ANY_MOTION__POS      (2)
#define BMI160_USER_INTR_MAP_2_INTR2_ANY_MOTION__LEN      (1)
#define BMI160_USER_INTR_MAP_2_INTR2_ANY_MOTION__MSK     (0x04)
#define BMI160_USER_INTR_MAP_2_INTR2_ANY_MOTION__REG     \
(BMI160_USER_INTR_MAP_2_ADDR)
/**************************************************************/
/**\name    INTERRUPT2 MAPPIONG OF NO MOTION LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_2 Description - Reg Addr --> 0x57, Bit -->3 */
#define BMI160_USER_INTR_MAP_2_INTR2_NOMOTION__POS               (3)
#define BMI160_USER_INTR_MAP_2_INTR2_NOMOTION__LEN               (1)
#define BMI160_USER_INTR_MAP_2_INTR2_NOMOTION__MSK               (0x08)
#define BMI160_USER_INTR_MAP_2_INTR2_NOMOTION__REG (BMI160_USER_INTR_MAP_2_ADDR)
/**************************************************************/
/**\name    INTERRUPT2 MAPPIONG OF DOUBLE TAP LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_2 Description - Reg Addr --> 0x57, Bit -->4 */
#define BMI160_USER_INTR_MAP_2_INTR2_DOUBLE_TAP__POS               (4)
#define BMI160_USER_INTR_MAP_2_INTR2_DOUBLE_TAP__LEN               (1)
#define BMI160_USER_INTR_MAP_2_INTR2_DOUBLE_TAP__MSK               (0x10)
#define BMI160_USER_INTR_MAP_2_INTR2_DOUBLE_TAP__REG    \
(BMI160_USER_INTR_MAP_2_ADDR)
/**************************************************************/
/**\name    INTERRUPT2 MAPPIONG OF SINGLE TAP LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_2 Description - Reg Addr --> 0x57, Bit -->5 */
#define BMI160_USER_INTR_MAP_2_INTR2_SINGLE_TAP__POS               (5)
#define BMI160_USER_INTR_MAP_2_INTR2_SINGLE_TAP__LEN               (1)
#define BMI160_USER_INTR_MAP_2_INTR2_SINGLE_TAP__MSK               (0x20)
#define BMI160_USER_INTR_MAP_2_INTR2_SINGLE_TAP__REG    \
(BMI160_USER_INTR_MAP_2_ADDR)
/**************************************************************/
/**\name    INTERRUPT2 MAPPIONG OF ORIENT LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_2 Description - Reg Addr --> 0x57, Bit -->6 */
#define BMI160_USER_INTR_MAP_2_INTR2_ORIENT__POS               (6)
#define BMI160_USER_INTR_MAP_2_INTR2_ORIENT__LEN               (1)
#define BMI160_USER_INTR_MAP_2_INTR2_ORIENT__MSK               (0x40)
#define BMI160_USER_INTR_MAP_2_INTR2_ORIENT__REG    \
(BMI160_USER_INTR_MAP_2_ADDR)
/**************************************************************/
/**\name    INTERRUPT2 MAPPIONG OF FLAT LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Map_2 Description - Reg Addr --> 0x57, Bit -->7 */
#define BMI160_USER_INTR_MAP_2_INTR2_FLAT__POS               (7)
#define BMI160_USER_INTR_MAP_2_INTR2_FLAT__LEN               (1)
#define BMI160_USER_INTR_MAP_2_INTR2_FLAT__MSK               (0x80)
#define BMI160_USER_INTR_MAP_2_INTR2_FLAT__REG  (BMI160_USER_INTR_MAP_2_ADDR)

/**************************************************************/
/**\name    TAP SOURCE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Data_0 Description - Reg Addr --> 0x58, Bit --> 3 */
#define BMI160_USER_INTR_DATA_0_INTR_TAP_SOURCE__POS               (3)
#define BMI160_USER_INTR_DATA_0_INTR_TAP_SOURCE__LEN               (1)
#define BMI160_USER_INTR_DATA_0_INTR_TAP_SOURCE__MSK               (0x08)
#define BMI160_USER_INTR_DATA_0_INTR_TAP_SOURCE__REG               \
(BMI160_USER_INTR_DATA_0_ADDR)

/**************************************************************/
/**\name    HIGH SOURCE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Data_0 Description - Reg Addr --> 0x58, Bit --> 7 */
#define BMI160_USER_INTR_DATA_0_INTR_LOW_HIGH_SOURCE__POS           (7)
#define BMI160_USER_INTR_DATA_0_INTR_LOW_HIGH_SOURCE__LEN           (1)
#define BMI160_USER_INTR_DATA_0_INTR_LOW_HIGH_SOURCE__MSK           (0x80)
#define BMI160_USER_INTR_DATA_0_INTR_LOW_HIGH_SOURCE__REG            \
(BMI160_USER_INTR_DATA_0_ADDR)

/**************************************************************/
/**\name    MOTION SOURCE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Data_1 Description - Reg Addr --> 0x59, Bit --> 7 */
#define BMI160_USER_INTR_DATA_1_INTR_MOTION_SOURCE__POS               (7)
#define BMI160_USER_INTR_DATA_1_INTR_MOTION_SOURCE__LEN               (1)
#define BMI160_USER_INTR_DATA_1_INTR_MOTION_SOURCE__MSK               (0x80)
#define BMI160_USER_INTR_DATA_1_INTR_MOTION_SOURCE__REG               \
        (BMI160_USER_INTR_DATA_1_ADDR)
/**************************************************************/
/**\name    LOW HIGH DURATION LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_LowHigh_0 Description - Reg Addr --> 0x5a, Bit --> 0...7 */
#define BMI160_USER_INTR_LOWHIGH_0_INTR_LOW_DURN__POS               (0)
#define BMI160_USER_INTR_LOWHIGH_0_INTR_LOW_DURN__LEN               (8)
#define BMI160_USER_INTR_LOWHIGH_0_INTR_LOW_DURN__MSK               (0xFF)
#define BMI160_USER_INTR_LOWHIGH_0_INTR_LOW_DURN__REG               \
        (BMI160_USER_INTR_LOWHIGH_0_ADDR)
/**************************************************************/
/**\name    LOW THRESHOLD LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_LowHigh_1 Description - Reg Addr --> 0x5b, Bit --> 0...7 */
#define BMI160_USER_INTR_LOWHIGH_1_INTR_LOW_THRES__POS               (0)
#define BMI160_USER_INTR_LOWHIGH_1_INTR_LOW_THRES__LEN               (8)
#define BMI160_USER_INTR_LOWHIGH_1_INTR_LOW_THRES__MSK               (0xFF)
#define BMI160_USER_INTR_LOWHIGH_1_INTR_LOW_THRES__REG               \
        (BMI160_USER_INTR_LOWHIGH_1_ADDR)
/**************************************************************/
/**\name    LOW HYSTERESIS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_LowHigh_2 Description - Reg Addr --> 0x5c, Bit --> 0...1 */
#define BMI160_USER_INTR_LOWHIGH_2_INTR_LOW_G_HYST__POS               (0)
#define BMI160_USER_INTR_LOWHIGH_2_INTR_LOW_G_HYST__LEN               (2)
#define BMI160_USER_INTR_LOWHIGH_2_INTR_LOW_G_HYST__MSK               (0x03)
#define BMI160_USER_INTR_LOWHIGH_2_INTR_LOW_G_HYST__REG               \
        (BMI160_USER_INTR_LOWHIGH_2_ADDR)
/**************************************************************/
/**\name    LOW MODE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_LowHigh_2 Description - Reg Addr --> 0x5c, Bit --> 2 */
#define BMI160_USER_INTR_LOWHIGH_2_INTR_LOW_G_MODE__POS               (2)
#define BMI160_USER_INTR_LOWHIGH_2_INTR_LOW_G_MODE__LEN               (1)
#define BMI160_USER_INTR_LOWHIGH_2_INTR_LOW_G_MODE__MSK               (0x04)
#define BMI160_USER_INTR_LOWHIGH_2_INTR_LOW_G_MODE__REG               \
        (BMI160_USER_INTR_LOWHIGH_2_ADDR)
/**************************************************************/
/**\name    HIGH_G HYSTERESIS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_LowHigh_2 Description - Reg Addr --> 0x5c, Bit --> 6...7 */
#define BMI160_USER_INTR_LOWHIGH_2_INTR_HIGH_G_HYST__POS               (6)
#define BMI160_USER_INTR_LOWHIGH_2_INTR_HIGH_G_HYST__LEN               (2)
#define BMI160_USER_INTR_LOWHIGH_2_INTR_HIGH_G_HYST__MSK               (0xC0)
#define BMI160_USER_INTR_LOWHIGH_2_INTR_HIGH_G_HYST__REG               \
        (BMI160_USER_INTR_LOWHIGH_2_ADDR)
/**************************************************************/
/**\name    HIGH_G DURATION LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_LowHigh_3 Description - Reg Addr --> 0x5d, Bit --> 0...7 */
#define BMI160_USER_INTR_LOWHIGH_3_INTR_HIGH_G_DURN__POS               (0)
#define BMI160_USER_INTR_LOWHIGH_3_INTR_HIGH_G_DURN__LEN               (8)
#define BMI160_USER_INTR_LOWHIGH_3_INTR_HIGH_G_DURN__MSK               (0xFF)
#define BMI160_USER_INTR_LOWHIGH_3_INTR_HIGH_G_DURN__REG               \
        (BMI160_USER_INTR_LOWHIGH_3_ADDR)
/**************************************************************/
/**\name    HIGH_G THRESHOLD LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_LowHigh_4 Description - Reg Addr --> 0x5e, Bit --> 0...7 */
#define BMI160_USER_INTR_LOWHIGH_4_INTR_HIGH_THRES__POS               (0)
#define BMI160_USER_INTR_LOWHIGH_4_INTR_HIGH_THRES__LEN               (8)
#define BMI160_USER_INTR_LOWHIGH_4_INTR_HIGH_THRES__MSK               (0xFF)
#define BMI160_USER_INTR_LOWHIGH_4_INTR_HIGH_THRES__REG               \
        (BMI160_USER_INTR_LOWHIGH_4_ADDR)
/**************************************************************/
/**\name    ANY MOTION DURATION LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Motion_0 Description - Reg Addr --> 0x5f, Bit --> 0...1 */
#define BMI160_USER_INTR_MOTION_0_INTR_ANY_MOTION_DURN__POS               (0)
#define BMI160_USER_INTR_MOTION_0_INTR_ANY_MOTION_DURN__LEN               (2)
#define BMI160_USER_INTR_MOTION_0_INTR_ANY_MOTION_DURN__MSK               (0x03)
#define BMI160_USER_INTR_MOTION_0_INTR_ANY_MOTION_DURN__REG               \
        (BMI160_USER_INTR_MOTION_0_ADDR)
/**************************************************************/
/**\name    SLOW/NO MOTION DURATION LENGTH, POSITION AND MASK*/
/**************************************************************/
    /* Int_Motion_0 Description - Reg Addr --> 0x5f, Bit --> 2...7 */
#define BMI160_USER_INTR_MOTION_0_INTR_SLOW_NO_MOTION_DURN__POS      (2)
#define BMI160_USER_INTR_MOTION_0_INTR_SLOW_NO_MOTION_DURN__LEN      (6)
#define BMI160_USER_INTR_MOTION_0_INTR_SLOW_NO_MOTION_DURN__MSK      (0xFC)
#define BMI160_USER_INTR_MOTION_0_INTR_SLOW_NO_MOTION_DURN__REG       \
        (BMI160_USER_INTR_MOTION_0_ADDR)
/**************************************************************/
/**\name    ANY MOTION THRESHOLD LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Motion_1 Description - Reg Addr --> (0x60), Bit --> 0...7 */
#define BMI160_USER_INTR_MOTION_1_INTR_ANY_MOTION_THRES__POS      (0)
#define BMI160_USER_INTR_MOTION_1_INTR_ANY_MOTION_THRES__LEN      (8)
#define BMI160_USER_INTR_MOTION_1_INTR_ANY_MOTION_THRES__MSK      (0xFF)
#define BMI160_USER_INTR_MOTION_1_INTR_ANY_MOTION_THRES__REG               \
        (BMI160_USER_INTR_MOTION_1_ADDR)
/**************************************************************/
/**\name    SLOW/NO MOTION THRESHOLD LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Motion_2 Description - Reg Addr --> 0x61, Bit --> 0...7 */
#define BMI160_USER_INTR_MOTION_2_INTR_SLOW_NO_MOTION_THRES__POS       (0)
#define BMI160_USER_INTR_MOTION_2_INTR_SLOW_NO_MOTION_THRES__LEN       (8)
#define BMI160_USER_INTR_MOTION_2_INTR_SLOW_NO_MOTION_THRES__MSK       (0xFF)
#define BMI160_USER_INTR_MOTION_2_INTR_SLOW_NO_MOTION_THRES__REG       \
        (BMI160_USER_INTR_MOTION_2_ADDR)
/**************************************************************/
/**\name    SLOW/NO MOTION SELECT LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Motion_3 Description - Reg Addr --> (0x62), Bit --> 0 */
#define BMI160_USER_INTR_MOTION_3_INTR_SLOW_NO_MOTION_SELECT__POS   (0)
#define BMI160_USER_INTR_MOTION_3_INTR_SLOW_NO_MOTION_SELECT__LEN   (1)
#define BMI160_USER_INTR_MOTION_3_INTR_SLOW_NO_MOTION_SELECT__MSK   (0x01)
#define BMI160_USER_INTR_MOTION_3_INTR_SLOW_NO_MOTION_SELECT__REG   \
(BMI160_USER_INTR_MOTION_3_ADDR)
/**************************************************************/
/**\name    SIGNIFICANT MOTION SELECT LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Motion_3 Description - Reg Addr --> (0x62), Bit --> 1 */
#define BMI160_USER_INTR_SIGNIFICATION_MOTION_SELECT__POS       (1)
#define BMI160_USER_INTR_SIGNIFICATION_MOTION_SELECT__LEN       (1)
#define BMI160_USER_INTR_SIGNIFICATION_MOTION_SELECT__MSK       (0x02)
#define BMI160_USER_INTR_SIGNIFICATION_MOTION_SELECT__REG       \
        (BMI160_USER_INTR_MOTION_3_ADDR)

/* Int_Motion_3 Description - Reg Addr --> (0x62), Bit --> 3..2 */
#define BMI160_USER_INTR_SIGNIFICANT_MOTION_SKIP__POS       (2)
#define BMI160_USER_INTR_SIGNIFICANT_MOTION_SKIP__LEN       (2)
#define BMI160_USER_INTR_SIGNIFICANT_MOTION_SKIP__MSK       (0x0C)
#define BMI160_USER_INTR_SIGNIFICANT_MOTION_SKIP__REG       \
        (BMI160_USER_INTR_MOTION_3_ADDR)

/* Int_Motion_3 Description - Reg Addr --> (0x62), Bit --> 5..4 */
#define BMI160_USER_INTR_SIGNIFICANT_MOTION_PROOF__POS      (4)
#define BMI160_USER_INTR_SIGNIFICANT_MOTION_PROOF__LEN      (2)
#define BMI160_USER_INTR_SIGNIFICANT_MOTION_PROOF__MSK      (0x30)
#define BMI160_USER_INTR_SIGNIFICANT_MOTION_PROOF__REG      \
        (BMI160_USER_INTR_MOTION_3_ADDR)
/**************************************************************/
/**\name    TAP DURATION LENGTH, POSITION AND MASK*/
/**************************************************************/
/* INT_TAP_0 Description - Reg Addr --> (0x63), Bit --> 0..2*/
#define BMI160_USER_INTR_TAP_0_INTR_TAP_DURN__POS               (0)
#define BMI160_USER_INTR_TAP_0_INTR_TAP_DURN__LEN               (3)
#define BMI160_USER_INTR_TAP_0_INTR_TAP_DURN__MSK               (0x07)
#define BMI160_USER_INTR_TAP_0_INTR_TAP_DURN__REG   \
(BMI160_USER_INTR_TAP_0_ADDR)
/**************************************************************/
/**\name    TAP SHOCK LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Tap_0 Description - Reg Addr --> (0x63), Bit --> 6 */
#define BMI160_USER_INTR_TAP_0_INTR_TAP_SHOCK__POS               (6)
#define BMI160_USER_INTR_TAP_0_INTR_TAP_SHOCK__LEN               (1)
#define BMI160_USER_INTR_TAP_0_INTR_TAP_SHOCK__MSK               (0x40)
#define BMI160_USER_INTR_TAP_0_INTR_TAP_SHOCK__REG (BMI160_USER_INTR_TAP_0_ADDR)
/**************************************************************/
/**\name    TAP QUIET LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Tap_0 Description - Reg Addr --> (0x63), Bit --> 7 */
#define BMI160_USER_INTR_TAP_0_INTR_TAP_QUIET__POS               (7)
#define BMI160_USER_INTR_TAP_0_INTR_TAP_QUIET__LEN               (1)
#define BMI160_USER_INTR_TAP_0_INTR_TAP_QUIET__MSK               (0x80)
#define BMI160_USER_INTR_TAP_0_INTR_TAP_QUIET__REG (BMI160_USER_INTR_TAP_0_ADDR)
/**************************************************************/
/**\name    TAP THRESHOLD LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Tap_1 Description - Reg Addr --> (0x64), Bit --> 0...4 */
#define BMI160_USER_INTR_TAP_1_INTR_TAP_THRES__POS               (0)
#define BMI160_USER_INTR_TAP_1_INTR_TAP_THRES__LEN               (5)
#define BMI160_USER_INTR_TAP_1_INTR_TAP_THRES__MSK               (0x1F)
#define BMI160_USER_INTR_TAP_1_INTR_TAP_THRES__REG (BMI160_USER_INTR_TAP_1_ADDR)
/**************************************************************/
/**\name    ORIENT MODE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Orient_0 Description - Reg Addr --> (0x65), Bit --> 0...1 */
#define BMI160_USER_INTR_ORIENT_0_INTR_ORIENT_MODE__POS               (0)
#define BMI160_USER_INTR_ORIENT_0_INTR_ORIENT_MODE__LEN               (2)
#define BMI160_USER_INTR_ORIENT_0_INTR_ORIENT_MODE__MSK               (0x03)
#define BMI160_USER_INTR_ORIENT_0_INTR_ORIENT_MODE__REG               \
        (BMI160_USER_INTR_ORIENT_0_ADDR)
/**************************************************************/
/**\name    ORIENT BLOCKING LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Orient_0 Description - Reg Addr --> (0x65), Bit --> 2...3 */
#define BMI160_USER_INTR_ORIENT_0_INTR_ORIENT_BLOCKING__POS               (2)
#define BMI160_USER_INTR_ORIENT_0_INTR_ORIENT_BLOCKING__LEN               (2)
#define BMI160_USER_INTR_ORIENT_0_INTR_ORIENT_BLOCKING__MSK               (0x0C)
#define BMI160_USER_INTR_ORIENT_0_INTR_ORIENT_BLOCKING__REG               \
        (BMI160_USER_INTR_ORIENT_0_ADDR)
/**************************************************************/
/**\name    ORIENT HYSTERESIS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Orient_0 Description - Reg Addr --> (0x65), Bit --> 4...7 */
#define BMI160_USER_INTR_ORIENT_0_INTR_ORIENT_HYST__POS               (4)
#define BMI160_USER_INTR_ORIENT_0_INTR_ORIENT_HYST__LEN               (4)
#define BMI160_USER_INTR_ORIENT_0_INTR_ORIENT_HYST__MSK               (0xF0)
#define BMI160_USER_INTR_ORIENT_0_INTR_ORIENT_HYST__REG               \
        (BMI160_USER_INTR_ORIENT_0_ADDR)
/**************************************************************/
/**\name    ORIENT THETA LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Orient_1 Description - Reg Addr --> 0x66, Bit --> 0...5 */
#define BMI160_USER_INTR_ORIENT_1_INTR_ORIENT_THETA__POS               (0)
#define BMI160_USER_INTR_ORIENT_1_INTR_ORIENT_THETA__LEN               (6)
#define BMI160_USER_INTR_ORIENT_1_INTR_ORIENT_THETA__MSK               (0x3F)
#define BMI160_USER_INTR_ORIENT_1_INTR_ORIENT_THETA__REG               \
        (BMI160_USER_INTR_ORIENT_1_ADDR)
/**************************************************************/
/**\name    ORIENT UD LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Orient_1 Description - Reg Addr --> 0x66, Bit --> 6 */
#define BMI160_USER_INTR_ORIENT_1_INTR_ORIENT_UD_ENABLE__POS         (6)
#define BMI160_USER_INTR_ORIENT_1_INTR_ORIENT_UD_ENABLE__LEN         (1)
#define BMI160_USER_INTR_ORIENT_1_INTR_ORIENT_UD_ENABLE__MSK         (0x40)
#define BMI160_USER_INTR_ORIENT_1_INTR_ORIENT_UD_ENABLE__REG          \
        (BMI160_USER_INTR_ORIENT_1_ADDR)
/**************************************************************/
/**\name    ORIENT AXIS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Orient_1 Description - Reg Addr --> 0x66, Bit --> 7 */
#define BMI160_USER_INTR_ORIENT_1_INTR_ORIENT_AXES_EX__POS               (7)
#define BMI160_USER_INTR_ORIENT_1_INTR_ORIENT_AXES_EX__LEN               (1)
#define BMI160_USER_INTR_ORIENT_1_INTR_ORIENT_AXES_EX__MSK               (0x80)
#define BMI160_USER_INTR_ORIENT_1_INTR_ORIENT_AXES_EX__REG               \
        (BMI160_USER_INTR_ORIENT_1_ADDR)
/**************************************************************/
/**\name    FLAT THETA LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Flat_0 Description - Reg Addr --> 0x67, Bit --> 0...5 */
#define BMI160_USER_INTR_FLAT_0_INTR_FLAT_THETA__POS               (0)
#define BMI160_USER_INTR_FLAT_0_INTR_FLAT_THETA__LEN               (6)
#define BMI160_USER_INTR_FLAT_0_INTR_FLAT_THETA__MSK               (0x3F)
#define BMI160_USER_INTR_FLAT_0_INTR_FLAT_THETA__REG  \
        (BMI160_USER_INTR_FLAT_0_ADDR)
/**************************************************************/
/**\name    FLAT HYSTERESIS LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Flat_1 Description - Reg Addr --> (0x68), Bit --> 0...3 */
#define BMI160_USER_INTR_FLAT_1_INTR_FLAT_HYST__POS     (0)
#define BMI160_USER_INTR_FLAT_1_INTR_FLAT_HYST__LEN     (4)
#define BMI160_USER_INTR_FLAT_1_INTR_FLAT_HYST__MSK     (0x0F)
#define BMI160_USER_INTR_FLAT_1_INTR_FLAT_HYST__REG  \
(BMI160_USER_INTR_FLAT_1_ADDR)
/**************************************************************/
/**\name    FLAT HOLD LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Int_Flat_1 Description - Reg Addr --> (0x68), Bit --> 4...5 */
#define BMI160_USER_INTR_FLAT_1_INTR_FLAT_HOLD__POS                (4)
#define BMI160_USER_INTR_FLAT_1_INTR_FLAT_HOLD__LEN                (2)
#define BMI160_USER_INTR_FLAT_1_INTR_FLAT_HOLD__MSK                (0x30)
#define BMI160_USER_INTR_FLAT_1_INTR_FLAT_HOLD__REG  \
(BMI160_USER_INTR_FLAT_1_ADDR)
/**************************************************************/
/**\name    FOC ACCEL XYZ LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Foc_Conf Description - Reg Addr --> (0x69), Bit --> 0...1 */
#define BMI160_USER_FOC_ACCEL_Z__POS               (0)
#define BMI160_USER_FOC_ACCEL_Z__LEN               (2)
#define BMI160_USER_FOC_ACCEL_Z__MSK               (0x03)
#define BMI160_USER_FOC_ACCEL_Z__REG               (BMI160_USER_FOC_CONFIG_ADDR)

/* Foc_Conf Description - Reg Addr --> (0x69), Bit --> 2...3 */
#define BMI160_USER_FOC_ACCEL_Y__POS               (2)
#define BMI160_USER_FOC_ACCEL_Y__LEN               (2)
#define BMI160_USER_FOC_ACCEL_Y__MSK               (0x0C)
#define BMI160_USER_FOC_ACCEL_Y__REG               (BMI160_USER_FOC_CONFIG_ADDR)

/* Foc_Conf Description - Reg Addr --> (0x69), Bit --> 4...5 */
#define BMI160_USER_FOC_ACCEL_X__POS               (4)
#define BMI160_USER_FOC_ACCEL_X__LEN               (2)
#define BMI160_USER_FOC_ACCEL_X__MSK               (0x30)
#define BMI160_USER_FOC_ACCEL_X__REG               (BMI160_USER_FOC_CONFIG_ADDR)
/**************************************************************/
/**\name    FOC GYRO LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Foc_Conf Description - Reg Addr --> (0x69), Bit --> 6 */
#define BMI160_USER_FOC_GYRO_ENABLE__POS               (6)
#define BMI160_USER_FOC_GYRO_ENABLE__LEN               (1)
#define BMI160_USER_FOC_GYRO_ENABLE__MSK               (0x40)
#define BMI160_USER_FOC_GYRO_ENABLE__REG               \
(BMI160_USER_FOC_CONFIG_ADDR)
/**************************************************************/
/**\name    NVM PROGRAM LENGTH, POSITION AND MASK*/
/**************************************************************/
/* CONF Description - Reg Addr --> (0x6A), Bit --> 1 */
#define BMI160_USER_CONFIG_NVM_PROG_ENABLE__POS               (1)
#define BMI160_USER_CONFIG_NVM_PROG_ENABLE__LEN               (1)
#define BMI160_USER_CONFIG_NVM_PROG_ENABLE__MSK               (0x02)
#define BMI160_USER_CONFIG_NVM_PROG_ENABLE__REG               \
(BMI160_USER_CONFIG_ADDR)

/*IF_CONF Description - Reg Addr --> (0x6B), Bit --> 0 */

#define BMI160_USER_IF_CONFIG_SPI3__POS               (0)
#define BMI160_USER_IF_CONFIG_SPI3__LEN               (1)
#define BMI160_USER_IF_CONFIG_SPI3__MSK               (0x01)
#define BMI160_USER_IF_CONFIG_SPI3__REG               \
(BMI160_USER_IF_CONFIG_ADDR)

/*IF_CONF Description - Reg Addr --> (0x6B), Bit --> 5..4 */
#define BMI160_USER_IF_CONFIG_IF_MODE__POS               (4)
#define BMI160_USER_IF_CONFIG_IF_MODE__LEN               (2)
#define BMI160_USER_IF_CONFIG_IF_MODE__MSK               (0x30)
#define BMI160_USER_IF_CONFIG_IF_MODE__REG      \
(BMI160_USER_IF_CONFIG_ADDR)
/**************************************************************/
/**\name    GYRO SLEEP CONFIGURATION LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Pmu_Trigger Description - Reg Addr --> 0x6c, Bit --> 0...2 */
#define BMI160_USER_GYRO_SLEEP_TRIGGER__POS               (0)
#define BMI160_USER_GYRO_SLEEP_TRIGGER__LEN               (3)
#define BMI160_USER_GYRO_SLEEP_TRIGGER__MSK               (0x07)
#define BMI160_USER_GYRO_SLEEP_TRIGGER__REG (BMI160_USER_PMU_TRIGGER_ADDR)

/* Pmu_Trigger Description - Reg Addr --> 0x6c, Bit --> 3...4 */
#define BMI160_USER_GYRO_WAKEUP_TRIGGER__POS               (3)
#define BMI160_USER_GYRO_WAKEUP_TRIGGER__LEN               (2)
#define BMI160_USER_GYRO_WAKEUP_TRIGGER__MSK               (0x18)
#define BMI160_USER_GYRO_WAKEUP_TRIGGER__REG    (BMI160_USER_PMU_TRIGGER_ADDR)

/* Pmu_Trigger Description - Reg Addr --> 0x6c, Bit --> 5 */
#define BMI160_USER_GYRO_SLEEP_STATE__POS               (5)
#define BMI160_USER_GYRO_SLEEP_STATE__LEN               (1)
#define BMI160_USER_GYRO_SLEEP_STATE__MSK               (0x20)
#define BMI160_USER_GYRO_SLEEP_STATE__REG   (BMI160_USER_PMU_TRIGGER_ADDR)

/* Pmu_Trigger Description - Reg Addr --> 0x6c, Bit --> 6 */
#define BMI160_USER_GYRO_WAKEUP_INTR__POS               (6)
#define BMI160_USER_GYRO_WAKEUP_INTR__LEN               (1)
#define BMI160_USER_GYRO_WAKEUP_INTR__MSK               (0x40)
#define BMI160_USER_GYRO_WAKEUP_INTR__REG   (BMI160_USER_PMU_TRIGGER_ADDR)
/**************************************************************/
/**\name    ACCEL SELF TEST LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Self_Test Description - Reg Addr --> 0x6d, Bit --> 0...1 */
#define BMI160_USER_ACCEL_SELFTEST_AXIS__POS               (0)
#define BMI160_USER_ACCEL_SELFTEST_AXIS__LEN               (2)
#define BMI160_USER_ACCEL_SELFTEST_AXIS__MSK               (0x03)
#define BMI160_USER_ACCEL_SELFTEST_AXIS__REG    (BMI160_USER_SELF_TEST_ADDR)

/* Self_Test Description - Reg Addr --> 0x6d, Bit --> 2 */
#define BMI160_USER_ACCEL_SELFTEST_SIGN__POS               (2)
#define BMI160_USER_ACCEL_SELFTEST_SIGN__LEN               (1)
#define BMI160_USER_ACCEL_SELFTEST_SIGN__MSK               (0x04)
#define BMI160_USER_ACCEL_SELFTEST_SIGN__REG    (BMI160_USER_SELF_TEST_ADDR)

/* Self_Test Description - Reg Addr --> 0x6d, Bit --> 3 */
#define BMI160_USER_SELFTEST_AMP__POS               (3)
#define BMI160_USER_SELFTEST_AMP__LEN               (1)
#define BMI160_USER_SELFTEST_AMP__MSK               (0x08)
#define BMI160_USER_SELFTEST_AMP__REG       (BMI160_USER_SELF_TEST_ADDR)
/**************************************************************/
/**\name    GYRO SELF TEST LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Self_Test Description - Reg Addr --> 0x6d, Bit --> 4 */
#define BMI160_USER_GYRO_SELFTEST_START__POS               (4)
#define BMI160_USER_GYRO_SELFTEST_START__LEN               (1)
#define BMI160_USER_GYRO_SELFTEST_START__MSK               (0x10)
#define BMI160_USER_GYRO_SELFTEST_START__REG            \
(BMI160_USER_SELF_TEST_ADDR)
/**************************************************************/
/**\name    NV_CONFIG LENGTH, POSITION AND MASK*/
/**************************************************************/
/* NV_CONF Description - Reg Addr --> (0x70), Bit --> 0 */
#define BMI160_USER_NV_CONFIG_SPI_ENABLE__POS               (0)
#define BMI160_USER_NV_CONFIG_SPI_ENABLE__LEN               (1)
#define BMI160_USER_NV_CONFIG_SPI_ENABLE__MSK               (0x01)
#define BMI160_USER_NV_CONFIG_SPI_ENABLE__REG    (BMI160_USER_NV_CONFIG_ADDR)

/*IF_CONF Description - Reg Addr --> (0x70), Bit --> 1 */
#define BMI160_USER_IF_CONFIG_I2C_WDT_SELECT__POS               (1)
#define BMI160_USER_IF_CONFIG_I2C_WDT_SELECT__LEN               (1)
#define BMI160_USER_IF_CONFIG_I2C_WDT_SELECT__MSK               (0x02)
#define BMI160_USER_IF_CONFIG_I2C_WDT_SELECT__REG       \
(BMI160_USER_NV_CONFIG_ADDR)

/*IF_CONF Description - Reg Addr --> (0x70), Bit --> 2 */
#define BMI160_USER_IF_CONFIG_I2C_WDT_ENABLE__POS               (2)
#define BMI160_USER_IF_CONFIG_I2C_WDT_ENABLE__LEN               (1)
#define BMI160_USER_IF_CONFIG_I2C_WDT_ENABLE__MSK               (0x04)
#define BMI160_USER_IF_CONFIG_I2C_WDT_ENABLE__REG       \
(BMI160_USER_NV_CONFIG_ADDR)

/* NV_CONF Description - Reg Addr --> (0x70), Bit --> 3 */
#define BMI160_USER_NV_CONFIG_SPARE0__POS               (3)
#define BMI160_USER_NV_CONFIG_SPARE0__LEN               (1)
#define BMI160_USER_NV_CONFIG_SPARE0__MSK               (0x08)
#define BMI160_USER_NV_CONFIG_SPARE0__REG   (BMI160_USER_NV_CONFIG_ADDR)

/* NV_CONF Description - Reg Addr --> (0x70), Bit --> 4...7 */
#define BMI160_USER_NV_CONFIG_NVM_COUNTER__POS               (4)
#define BMI160_USER_NV_CONFIG_NVM_COUNTER__LEN               (4)
#define BMI160_USER_NV_CONFIG_NVM_COUNTER__MSK               (0xF0)
#define BMI160_USER_NV_CONFIG_NVM_COUNTER__REG  (BMI160_USER_NV_CONFIG_ADDR)
/**************************************************************/
/**\name    ACCEL MANUAL OFFSET LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Offset_0 Description - Reg Addr --> (0x71), Bit --> 0...7 */
#define BMI160_USER_OFFSET_0_ACCEL_OFF_X__POS               (0)
#define BMI160_USER_OFFSET_0_ACCEL_OFF_X__LEN               (8)
#define BMI160_USER_OFFSET_0_ACCEL_OFF_X__MSK               (0xFF)
#define BMI160_USER_OFFSET_0_ACCEL_OFF_X__REG   (BMI160_USER_OFFSET_0_ADDR)

/* Offset_1 Description - Reg Addr --> 0x72, Bit --> 0...7 */
#define BMI160_USER_OFFSET_1_ACCEL_OFF_Y__POS               (0)
#define BMI160_USER_OFFSET_1_ACCEL_OFF_Y__LEN               (8)
#define BMI160_USER_OFFSET_1_ACCEL_OFF_Y__MSK               (0xFF)
#define BMI160_USER_OFFSET_1_ACCEL_OFF_Y__REG   (BMI160_USER_OFFSET_1_ADDR)

/* Offset_2 Description - Reg Addr --> 0x73, Bit --> 0...7 */
#define BMI160_USER_OFFSET_2_ACCEL_OFF_Z__POS               (0)
#define BMI160_USER_OFFSET_2_ACCEL_OFF_Z__LEN               (8)
#define BMI160_USER_OFFSET_2_ACCEL_OFF_Z__MSK               (0xFF)
#define BMI160_USER_OFFSET_2_ACCEL_OFF_Z__REG   (BMI160_USER_OFFSET_2_ADDR)
/**************************************************************/
/**\name    GYRO MANUAL OFFSET LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Offset_3 Description - Reg Addr --> 0x74, Bit --> 0...7 */
#define BMI160_USER_OFFSET_3_GYRO_OFF_X__POS               (0)
#define BMI160_USER_OFFSET_3_GYRO_OFF_X__LEN               (8)
#define BMI160_USER_OFFSET_3_GYRO_OFF_X__MSK               (0xFF)
#define BMI160_USER_OFFSET_3_GYRO_OFF_X__REG    (BMI160_USER_OFFSET_3_ADDR)

/* Offset_4 Description - Reg Addr --> 0x75, Bit --> 0...7 */
#define BMI160_USER_OFFSET_4_GYRO_OFF_Y__POS               (0)
#define BMI160_USER_OFFSET_4_GYRO_OFF_Y__LEN               (8)
#define BMI160_USER_OFFSET_4_GYRO_OFF_Y__MSK               (0xFF)
#define BMI160_USER_OFFSET_4_GYRO_OFF_Y__REG    (BMI160_USER_OFFSET_4_ADDR)

/* Offset_5 Description - Reg Addr --> 0x76, Bit --> 0...7 */
#define BMI160_USER_OFFSET_5_GYRO_OFF_Z__POS               (0)
#define BMI160_USER_OFFSET_5_GYRO_OFF_Z__LEN               (8)
#define BMI160_USER_OFFSET_5_GYRO_OFF_Z__MSK               (0xFF)
#define BMI160_USER_OFFSET_5_GYRO_OFF_Z__REG    (BMI160_USER_OFFSET_5_ADDR)


/* Offset_6 Description - Reg Addr --> 0x77, Bit --> 0..1 */
#define BMI160_USER_OFFSET_6_GYRO_OFF_X__POS               (0)
#define BMI160_USER_OFFSET_6_GYRO_OFF_X__LEN               (2)
#define BMI160_USER_OFFSET_6_GYRO_OFF_X__MSK               (0x03)
#define BMI160_USER_OFFSET_6_GYRO_OFF_X__REG    (BMI160_USER_OFFSET_6_ADDR)

/* Offset_6 Description - Reg Addr --> 0x77, Bit --> 2...3 */
#define BMI160_USER_OFFSET_6_GYRO_OFF_Y__POS               (2)
#define BMI160_USER_OFFSET_6_GYRO_OFF_Y__LEN               (2)
#define BMI160_USER_OFFSET_6_GYRO_OFF_Y__MSK               (0x0C)
#define BMI160_USER_OFFSET_6_GYRO_OFF_Y__REG    (BMI160_USER_OFFSET_6_ADDR)

/* Offset_6 Description - Reg Addr --> 0x77, Bit --> 4...5 */
#define BMI160_USER_OFFSET_6_GYRO_OFF_Z__POS               (4)
#define BMI160_USER_OFFSET_6_GYRO_OFF_Z__LEN               (2)
#define BMI160_USER_OFFSET_6_GYRO_OFF_Z__MSK               (0x30)
#define BMI160_USER_OFFSET_6_GYRO_OFF_Z__REG     (BMI160_USER_OFFSET_6_ADDR)
/**************************************************************/
/**\name    ACCEL OFFSET  ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Offset_6 Description - Reg Addr --> 0x77, Bit --> 6 */
#define BMI160_USER_OFFSET_6_ACCEL_OFF_ENABLE__POS               (6)
#define BMI160_USER_OFFSET_6_ACCEL_OFF_ENABLE__LEN               (1)
#define BMI160_USER_OFFSET_6_ACCEL_OFF_ENABLE__MSK               (0x40)
#define BMI160_USER_OFFSET_6_ACCEL_OFF_ENABLE__REG   \
(BMI160_USER_OFFSET_6_ADDR)
/**************************************************************/
/**\name    GYRO OFFSET  ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Offset_6 Description - Reg Addr --> 0x77, Bit -->  7 */
#define BMI160_USER_OFFSET_6_GYRO_OFF_EN__POS               (7)
#define BMI160_USER_OFFSET_6_GYRO_OFF_EN__LEN               (1)
#define BMI160_USER_OFFSET_6_GYRO_OFF_EN__MSK               (0x80)
#define BMI160_USER_OFFSET_6_GYRO_OFF_EN__REG    (BMI160_USER_OFFSET_6_ADDR)
/**************************************************************/
/**\name    STEP COUNTER LENGTH, POSITION AND MASK*/
/**************************************************************/
/* STEP_CNT_0  Description - Reg Addr --> 0x78, Bit -->  0 to 7 */
#define BMI160_USER_STEP_COUNT_LSB__POS               (0)
#define BMI160_USER_STEP_COUNT_LSB__LEN               (7)
#define BMI160_USER_STEP_COUNT_LSB__MSK               (0xFF)
#define BMI160_USER_STEP_COUNT_LSB__REG  (BMI160_USER_STEP_COUNT_0_ADDR)

/* STEP_CNT_1  Description - Reg Addr --> 0x79, Bit -->  0 to 7 */
#define BMI160_USER_STEP_COUNT_MSB__POS               (0)
#define BMI160_USER_STEP_COUNT_MSB__LEN               (7)
#define BMI160_USER_STEP_COUNT_MSB__MSK               (0xFF)
#define BMI160_USER_STEP_COUNT_MSB__REG  (BMI160_USER_STEP_COUNT_1_ADDR)
/**************************************************************/
/**\name    STEP COUNTER CONFIGURATION LENGTH, POSITION AND MASK*/
/**************************************************************/
/* STEP_CONFIG_0  Description - Reg Addr --> 0x7A, Bit -->  0 to 7 */
#define BMI160_USER_STEP_CONFIG_ZERO__POS               (0)
#define BMI160_USER_STEP_CONFIG_ZERO__LEN               (7)
#define BMI160_USER_STEP_CONFIG_ZERO__MSK               (0xFF)
#define BMI160_USER_STEP_CONFIG_ZERO__REG    \
(BMI160_USER_STEP_CONFIG_0_ADDR)


/* STEP_CONFIG_1  Description - Reg Addr --> 0x7B, Bit -->  0 to 2 and
4 to 7 */
#define BMI160_USER_STEP_CONFIG_ONE_CNF1__POS               (0)
#define BMI160_USER_STEP_CONFIG_ONE_CNF1__LEN               (3)
#define BMI160_USER_STEP_CONFIG_ONE_CNF1__MSK               (0x07)
#define BMI160_USER_STEP_CONFIG_ONE_CNF1__REG    \
(BMI160_USER_STEP_CONFIG_1_ADDR)

#define BMI160_USER_STEP_CONFIG_ONE_CNF2__POS               (4)
#define BMI160_USER_STEP_CONFIG_ONE_CNF2__LEN               (4)
#define BMI160_USER_STEP_CONFIG_ONE_CNF2__MSK               (0xF0)
#define BMI160_USER_STEP_CONFIG_ONE_CNF2__REG    \
(BMI160_USER_STEP_CONFIG_1_ADDR)
/**************************************************************/
/**\name    STEP COUNTER ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* STEP_CONFIG_1  Description - Reg Addr --> 0x7B, Bit -->  0 to 2 */
#define BMI160_USER_STEP_CONFIG_1_STEP_COUNT_ENABLE__POS        (3)
#define BMI160_USER_STEP_CONFIG_1_STEP_COUNT_ENABLE__LEN        (1)
#define BMI160_USER_STEP_CONFIG_1_STEP_COUNT_ENABLE__MSK        (0x08)
#define BMI160_USER_STEP_CONFIG_1_STEP_COUNT_ENABLE__REG    \
(BMI160_USER_STEP_CONFIG_1_ADDR)

/* USER REGISTERS DEFINITION END */
/**************************************************************************/
/* CMD REGISTERS DEFINITION START */
/**************************************************************/
/**\name    COMMAND REGISTER LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Command description address - Reg Addr --> 0x7E, Bit -->  0....7 */
#define BMI160_CMD_COMMANDS__POS              (0)
#define BMI160_CMD_COMMANDS__LEN              (8)
#define BMI160_CMD_COMMANDS__MSK              (0xFF)
#define BMI160_CMD_COMMANDS__REG     (BMI160_CMD_COMMANDS_ADDR)
/**************************************************************/
/**\name    PAGE ENABLE LENGTH, POSITION AND MASK*/
/**************************************************************/
/* Target page address - Reg Addr --> 0x7F, Bit -->  4....5 */
#define BMI160_CMD_TARGET_PAGE__POS           (4)
#define BMI160_CMD_TARGET_PAGE__LEN           (2)
#define BMI160_CMD_TARGET_PAGE__MSK           (0x30)
#define BMI160_CMD_TARGET_PAGE__REG  (BMI160_CMD_EXT_MODE_ADDR)

/* Target page address - Reg Addr --> 0x7F, Bit -->  4....5 */
#define BMI160_CMD_PAGING_EN__POS           (7)
#define BMI160_CMD_PAGING_EN__LEN           (1)
#define BMI160_CMD_PAGING_EN__MSK           (0x80)
#define BMI160_CMD_PAGING_EN__REG       (BMI160_CMD_EXT_MODE_ADDR)

/* Target page address - Reg Addr --> 0x7F, Bit -->  4....5 */
#define BMI160_COM_C_TRIM_FIVE__POS           (0)
#define BMI160_COM_C_TRIM_FIVE__LEN           (8)
#define BMI160_COM_C_TRIM_FIVE__MSK           (0xFF)
#define BMI160_COM_C_TRIM_FIVE__REG     (BMI160_COM_C_TRIM_FIVE_ADDR)

/**************************************************************************/
/* CMD REGISTERS DEFINITION END */
#ifdef FIFO_ENABLE
/**************************************************/
/**\name    FIFO FRAME COUNT DEFINITION           */
/*************************************************/
#define FIFO_FRAME              (1024)
#define FIFO_CONFIG_CHECK1      (0x00)
#define FIFO_CONFIG_CHECK2      (0x80)
#endif
/**************************************************/
/**\name    MAG SENSOR SELECT          */
/*************************************************/
#define BST_BMM     (0)
#define BST_AKM     (1)
#define BMI160_YAS537_I2C_ADDRESS   (0x2E)
/**************************************************/
/**\name    ACCEL RANGE          */
/*************************************************/
#define BMI160_ACCEL_RANGE_2G           (0x03)
#define BMI160_ACCEL_RANGE_4G           (0x05)
#define BMI160_ACCEL_RANGE_8G           (0x08)
#define BMI160_ACCEL_RANGE_16G          (0x0C)
/**************************************************/
/**\name    ACCEL ODR          */
/*************************************************/
#define BMI160_ACCEL_OUTPUT_DATA_RATE_RESERVED       (0x00)
#define BMI160_ACCEL_OUTPUT_DATA_RATE_0_78HZ         (0x01)
#define BMI160_ACCEL_OUTPUT_DATA_RATE_1_56HZ         (0x02)
#define BMI160_ACCEL_OUTPUT_DATA_RATE_3_12HZ         (0x03)
#define BMI160_ACCEL_OUTPUT_DATA_RATE_6_25HZ         (0x04)
#define BMI160_ACCEL_OUTPUT_DATA_RATE_12_5HZ         (0x05)
#define BMI160_ACCEL_OUTPUT_DATA_RATE_25HZ           (0x06)
#define BMI160_ACCEL_OUTPUT_DATA_RATE_50HZ           (0x07)
#define BMI160_ACCEL_OUTPUT_DATA_RATE_100HZ          (0x08)
#define BMI160_ACCEL_OUTPUT_DATA_RATE_200HZ          (0x09)
#define BMI160_ACCEL_OUTPUT_DATA_RATE_400HZ          (0x0A)
#define BMI160_ACCEL_OUTPUT_DATA_RATE_800HZ          (0x0B)
#define BMI160_ACCEL_OUTPUT_DATA_RATE_1600HZ         (0x0C)
#define BMI160_ACCEL_OUTPUT_DATA_RATE_RESERVED0      (0x0D)
#define BMI160_ACCEL_OUTPUT_DATA_RATE_RESERVED1      (0x0E)
#define BMI160_ACCEL_OUTPUT_DATA_RATE_RESERVED2      (0x0F)
/**************************************************/
/**\name    ACCEL BANDWIDTH PARAMETER         */
/*************************************************/
#define BMI160_ACCEL_OSR4_AVG1          (0)
#define BMI160_ACCEL_OSR2_AVG2          (1)
#define BMI160_ACCEL_NORMAL_AVG4        (2)
#define BMI160_ACCEL_CIC_AVG8           (3)
#define BMI160_ACCEL_RES_AVG2           (4)
#define BMI160_ACCEL_RES_AVG4           (5)
#define BMI160_ACCEL_RES_AVG8           (6)
#define BMI160_ACCEL_RES_AVG16          (7)
#define BMI160_ACCEL_RES_AVG32          (8)
#define BMI160_ACCEL_RES_AVG64          (9)
#define BMI160_ACCEL_RES_AVG128         (10)

#define BMI160_US_DISABLE               (0)
#define BMI160_US_ENABLE                (1)
/**************************************************/
/**\name    GYRO ODR         */
/*************************************************/
#define BMI160_GYRO_OUTPUT_DATA_RATE_RESERVED       (0x00)
#define BMI160_GYRO_OUTPUT_DATA_RATE_25HZ           (0x06)
#define BMI160_GYRO_OUTPUT_DATA_RATE_50HZ           (0x07)
#define BMI160_GYRO_OUTPUT_DATA_RATE_100HZ          (0x08)
#define BMI160_GYRO_OUTPUT_DATA_RATE_200HZ          (0x09)
#define BMI160_GYRO_OUTPUT_DATA_RATE_400HZ          (0x0A)
#define BMI160_GYRO_OUTPUT_DATA_RATE_800HZ          (0x0B)
#define BMI160_GYRO_OUTPUT_DATA_RATE_1600HZ         (0x0C)
#define BMI160_GYRO_OUTPUT_DATA_RATE_3200HZ         (0x0D)
/**************************************************/
/**\name    GYRO BANDWIDTH PARAMETER         */
/*************************************************/
#define BMI160_GYRO_OSR4_MODE       (0x00)
#define BMI160_GYRO_OSR2_MODE       (0x01)
#define BMI160_GYRO_NORMAL_MODE     (0x02)
#define BMI160_GYRO_CIC_MODE        (0x03)
/**************************************************/
/**\name    GYROSCOPE RANGE PARAMETER         */
/*************************************************/
#define BMI160_GYRO_RANGE_2000_DEG_SEC  (0x00)
#define BMI160_GYRO_RANGE_1000_DEG_SEC  (0x01)
#define BMI160_GYRO_RANGE_500_DEG_SEC   (0x02)
#define BMI160_GYRO_RANGE_250_DEG_SEC   (0x03)
#define BMI160_GYRO_RANGE_125_DEG_SEC   (0x04)
/**************************************************/
/**\name    MAG ODR         */
/*************************************************/
#define BMI160_MAG_OUTPUT_DATA_RATE_RESERVED       (0x00)
#define BMI160_MAG_OUTPUT_DATA_RATE_0_78HZ         (0x01)
#define BMI160_MAG_OUTPUT_DATA_RATE_1_56HZ         (0x02)
#define BMI160_MAG_OUTPUT_DATA_RATE_3_12HZ         (0x03)
#define BMI160_MAG_OUTPUT_DATA_RATE_6_25HZ         (0x04)
#define BMI160_MAG_OUTPUT_DATA_RATE_12_5HZ         (0x05)
#define BMI160_MAG_OUTPUT_DATA_RATE_25HZ           (0x06)
#define BMI160_MAG_OUTPUT_DATA_RATE_50HZ           (0x07)
#define BMI160_MAG_OUTPUT_DATA_RATE_100HZ          (0x08)
#define BMI160_MAG_OUTPUT_DATA_RATE_200HZ          (0x09)
#define BMI160_MAG_OUTPUT_DATA_RATE_400HZ          (0x0A)
#define BMI160_MAG_OUTPUT_DATA_RATE_800HZ          (0x0B)
#define BMI160_MAG_OUTPUT_DATA_RATE_1600HZ         (0x0C)
#define BMI160_MAG_OUTPUT_DATA_RATE_RESERVED0      (0x0D)
#define BMI160_MAG_OUTPUT_DATA_RATE_RESERVED1      (0x0E)
#define BMI160_MAG_OUTPUT_DATA_RATE_RESERVED2      (0x0F)

/**************************************************/
/**\name    ENABLE/DISABLE SELECTIONS        */
/*************************************************/

/* Enable accel and gyro offset */
#define ACCEL_OFFSET_ENABLE     (0x01)
#define GYRO_OFFSET_ENABLE      (0x01)

/* command register definition */
#define START_FOC_ACCEL_GYRO    (0x03)

 /* INT ENABLE 1 */
#define BMI160_ANY_MOTION_X_ENABLE       (0)
#define BMI160_ANY_MOTION_Y_ENABLE       (1)
#define BMI160_ANY_MOTION_Z_ENABLE       (2)
#define BMI160_DOUBLE_TAP_ENABLE         (4)
#define BMI160_SINGLE_TAP_ENABLE         (5)
#define BMI160_ORIENT_ENABLE             (6)
#define BMI160_FLAT_ENABLE               (7)

/* INT ENABLE 1 */
#define BMI160_HIGH_G_X_ENABLE       (0)
#define BMI160_HIGH_G_Y_ENABLE       (1)
#define BMI160_HIGH_G_Z_ENABLE       (2)
#define BMI160_LOW_G_ENABLE          (3)
#define BMI160_DATA_RDY_ENABLE       (4)
#define BMI160_FIFO_FULL_ENABLE      (5)
#define BMI160_FIFO_WM_ENABLE        (6)

/* INT ENABLE 2 */
#define  BMI160_NOMOTION_X_ENABLE   (0)
#define  BMI160_NOMOTION_Y_ENABLE   (1)
#define  BMI160_NOMOTION_Z_ENABLE   (2)

/* FOC axis selection for accel*/
#define FOC_X_AXIS      (0)
#define FOC_Y_AXIS      (1)
#define FOC_Z_AXIS      (2)

/* IN OUT CONTROL */
#define BMI160_INTR1_EDGE_CTRL          (0)
#define BMI160_INTR2_EDGE_CTRL          (1)
#define BMI160_INTR1_LEVEL              (0)
#define BMI160_INTR2_LEVEL              (1)
#define BMI160_INTR1_OUTPUT_TYPE        (0)
#define BMI160_INTR2_OUTPUT_TYPE        (1)
#define BMI160_INTR1_OUTPUT_ENABLE      (0)
#define BMI160_INTR2_OUTPUT_ENABLE      (1)

#define BMI160_INTR1_INPUT_ENABLE   (0)
#define BMI160_INTR2_INPUT_ENABLE   (1)

/*  INTERRUPT MAPS    */
#define BMI160_INTR1_MAP_LOW_G          (0)
#define BMI160_INTR2_MAP_LOW_G          (1)
#define BMI160_INTR1_MAP_HIGH_G         (0)
#define BMI160_INTR2_MAP_HIGH_G         (1)
#define BMI160_INTR1_MAP_ANY_MOTION     (0)
#define BMI160_INTR2_MAP_ANY_MOTION     (1)
#define BMI160_INTR1_MAP_NOMO           (0)
#define BMI160_INTR2_MAP_NOMO           (1)
#define BMI160_INTR1_MAP_DOUBLE_TAP     (0)
#define BMI160_INTR2_MAP_DOUBLE_TAP     (1)
#define BMI160_INTR1_MAP_SINGLE_TAP     (0)
#define BMI160_INTR2_MAP_SINGLE_TAP     (1)
#define BMI160_INTR1_MAP_ORIENT         (0)
#define BMI160_INTR2_MAP_ORIENT         (1)
#define BMI160_INTR1_MAP_FLAT           (0)
#define BMI160_INTR2_MAP_FLAT           (1)
#define BMI160_INTR1_MAP_DATA_RDY       (0)
#define BMI160_INTR2_MAP_DATA_RDY       (1)
#define BMI160_INTR1_MAP_FIFO_WM        (0)
#define BMI160_INTR2_MAP_FIFO_WM        (1)
#define BMI160_INTR1_MAP_FIFO_FULL      (0)
#define BMI160_INTR2_MAP_FIFO_FULL      (1)
#define BMI160_INTR1_MAP_PMUTRIG        (0)
#define BMI160_INTR2_MAP_PMUTRIG        (1)

/* Interrupt mapping*/
#define BMI160_MAP_INTR1        (0)
#define BMI160_MAP_INTR2        (1)
/**************************************************/
/**\name     TAP DURATION         */
/*************************************************/
#define BMI160_TAP_DURN_50MS     (0x00)
#define BMI160_TAP_DURN_100MS    (0x01)
#define BMI160_TAP_DURN_150MS    (0x02)
#define BMI160_TAP_DURN_200MS    (0x03)
#define BMI160_TAP_DURN_250MS    (0x04)
#define BMI160_TAP_DURN_375MS    (0x05)
#define BMI160_TAP_DURN_500MS    (0x06)
#define BMI160_TAP_DURN_700MS    (0x07)
/**************************************************/
/**\name    TAP SHOCK         */
/*************************************************/
#define BMI160_TAP_SHOCK_50MS   (0x00)
#define BMI160_TAP_SHOCK_75MS   (0x01)
/**************************************************/
/**\name    TAP QUIET        */
/*************************************************/
#define BMI160_TAP_QUIET_30MS   (0x00)
#define BMI160_TAP_QUIET_20MS   (0x01)
/**************************************************/
/**\name    STEP DETECTION SELECTION MODES      */
/*************************************************/
#define BMI160_STEP_NORMAL_MODE         (0)
#define BMI160_STEP_SENSITIVE_MODE      (1)
#define BMI160_STEP_ROBUST_MODE         (2)
/**************************************************/
/**\name    STEP CONFIGURATION SELECT MODE    */
/*************************************************/
#define STEP_CONFIG_NORMAL      (0x315)
#define STEP_CONFIG_SENSITIVE   (0x2D)
#define STEP_CONFIG_ROBUST      (0x71D)
/**************************************************/
/**\name    BMM150 TRIM DATA DEFINITIONS      */
/*************************************************/
#define BMI160_MAG_DIG_X1                      (0x5D)
#define BMI160_MAG_DIG_Y1                      (0x5E)
#define BMI160_MAG_DIG_Z4_LSB                  (0x62)
#define BMI160_MAG_DIG_Z4_MSB                  (0x63)
#define BMI160_MAG_DIG_X2                      (0x64)
#define BMI160_MAG_DIG_Y2                      (0x65)
#define BMI160_MAG_DIG_Z2_LSB                  (0x68)
#define BMI160_MAG_DIG_Z2_MSB                  (0x69)
#define BMI160_MAG_DIG_Z1_LSB                  (0x6A)
#define BMI160_MAG_DIG_Z1_MSB                  (0x6B)
#define BMI160_MAG_DIG_XYZ1_LSB                (0x6C)
#define BMI160_MAG_DIG_XYZ1_MSB                (0x6D)
#define BMI160_MAG_DIG_Z3_LSB                  (0x6E)
#define BMI160_MAG_DIG_Z3_MSB                  (0x6F)
#define BMI160_MAG_DIG_XY2                     (0x70)
#define BMI160_MAG_DIG_XY1                     (0x71)
/**************************************************/
/**\name    BMM150 PRE-SET MODE DEFINITIONS     */
/*************************************************/
#define BMI160_MAG_PRESETMODE_LOWPOWER                 (1)
#define BMI160_MAG_PRESETMODE_REGULAR                  (2)
#define BMI160_MAG_PRESETMODE_HIGHACCURACY             (3)
#define BMI160_MAG_PRESETMODE_ENHANCED                 (4)
/**************************************************/
/**\name    BMM150 PRESET MODES - DATA RATES    */
/*************************************************/
#define BMI160_MAG_LOWPOWER_DR                       (0x02)
#define BMI160_MAG_REGULAR_DR                        (0x02)
#define BMI160_MAG_HIGHACCURACY_DR                   (0x2A)
#define BMI160_MAG_ENHANCED_DR                       (0x02)
/**************************************************/
/**\name    BMM150 PRESET MODES - REPETITIONS-XY RATES */
/*************************************************/
#define BMI160_MAG_LOWPOWER_REPXY                    (1)
#define BMI160_MAG_REGULAR_REPXY                     (4)
#define BMI160_MAG_HIGHACCURACY_REPXY                (23)
#define BMI160_MAG_ENHANCED_REPXY                    (7)
/**************************************************/
/**\name    BMM150 PRESET MODES - REPETITIONS-Z RATES */
/*************************************************/
#define BMI160_MAG_LOWPOWER_REPZ                     (2)
#define BMI160_MAG_REGULAR_REPZ                      (14)
#define BMI160_MAG_HIGHACCURACY_REPZ                 (82)
#define BMI160_MAG_ENHANCED_REPZ                     (26)
#define BMI160_MAG_NOAMRL_SWITCH_TIMES               (5)
#define MAG_INTERFACE_PMU_ENABLE                     (1)
#define MAG_INTERFACE_PMU_DISABLE                    (0)
/**************************************************/
/**\name    USED FOR MAG OVERFLOW CHECK FOR BMM150  */
/*************************************************/
#define BMI160_MAG_OVERFLOW_OUTPUT          ((s16)-32768)
#define BMI160_MAG_OVERFLOW_OUTPUT_S32      ((s32)(-2147483647-1))
#define BMI160_MAG_NEGATIVE_SATURATION_Z   ((s16)-32767)
#define BMI160_MAG_POSITIVE_SATURATION_Z   ((u16)32767)
#define BMI160_MAG_FLIP_OVERFLOW_ADCVAL     ((s16)-4096)
#define BMI160_MAG_HALL_OVERFLOW_ADCVAL     ((s16)-16384)
/**************************************************/
/**\name    BMM150 REGISTER DEFINITION */
/*************************************************/
#define BMI160_BMM150_CHIP_ID           (0x40)
#define BMI160_BMM150_POWE_CONTROL_REG  (0x4B)
#define BMI160_BMM150_POWE_MODE_REG     (0x4C)
#define BMI160_BMM150_DATA_REG          (0x42)
#define BMI160_BMM150_XY_REP            (0x51)
#define BMI160_BMM150_Z_REP             (0x52)
/**************************************************/
/**\name    AKM COMPENSATING DATA REGISTERS     */
/*************************************************/
#define BMI160_BST_AKM_ASAX     (0x60)
#define BMI160_BST_AKM_ASAY     (0x61)
#define BMI160_BST_AKM_ASAZ     (0x62)
/**************************************************/
/**\name    AKM POWER MODE SELECTION     */
/*************************************************/
#define AKM_POWER_DOWN_MODE         (0)
#define AKM_SINGLE_MEAS_MODE        (1)
#define FUSE_ROM_MODE               (2)
/**************************************************/
/**\name    SECONDARY_MAG POWER MODE SELECTION    */
/*************************************************/
#define BMI160_MAG_FORCE_MODE       (0)
#define BMI160_MAG_SUSPEND_MODE     (1)
/**************************************************/
/**\name    MAG POWER MODE SELECTION    */
/*************************************************/
#define FORCE_MODE      (0)
#define SUSPEND_MODE    (1)
#define NORMAL_MODE     (2)
#define MAG_SUSPEND_MODE (1)

#ifdef FIFO_ENABLE
/**************************************************/
/**\name    FIFO CONFIGURATIONS    */
/*************************************************/
#define FIFO_HEADER_ENABLE          (0x01)
#define FIFO_MAG_ENABLE             (0x01)
#define FIFO_ACCEL_ENABLE           (0x01)
#define FIFO_GYRO_ENABLE            (0x01)
#define FIFO_TIME_ENABLE            (0x01)
#define FIFO_STOPONFULL_ENABLE      (0x01)
#define FIFO_WM_INTERRUPT_ENABLE    (0x01)
#define BMI160_FIFO_INDEX_LENGTH    (1)
#define BMI160_FIFO_TAG_INTR_MASK   (0xFC)

/* FIFO definitions*/
#define FIFO_HEAD_A        (0x84)
#define FIFO_HEAD_G        (0x88)
#define FIFO_HEAD_M        (0x90)

#define FIFO_HEAD_G_A   (0x8C)
#define FIFO_HEAD_M_A   (0x94)
#define FIFO_HEAD_M_G   (0x98)

#define FIFO_HEAD_M_G_A     (0x9C)

#define FIFO_HEAD_SENSOR_TIME           (0x44)
#define FIFO_HEAD_INPUT_CONFIG          (0x48)
#define FIFO_HEAD_SKIP_FRAME            (0x40)
#define FIFO_HEAD_OVER_READ_LSB         (0x80)
#define FIFO_HEAD_OVER_READ_MSB         (0x00)


/* FIFO 1024 byte, max fifo frame count not over 150 */

#define FIFO_INPUT_CONFIG_OVER_LEN  ((s8)-11)
#define FIFO_OVER_READ_RETURN       ((s8)-10)
#define FIFO_SENSORTIME_RETURN      ((s8)-9)
#define FIFO_SKIP_OVER_LEN          ((s8)-8)
#define FIFO_M_G_A_OVER_LEN         ((s8)-7)
#define FIFO_M_G_OVER_LEN           ((s8)-6)
#define FIFO_M_A_OVER_LEN           ((s8)-5)
#define FIFO_G_A_OVER_LEN           ((s8)-4)
#define FIFO_M_OVER_LEN             ((s8)-3)
#define FIFO_G_OVER_LEN             ((s8)-2)
#define FIFO_A_OVER_LEN             ((s8)-1)
#endif
/**************************************************/
/**\name    ACCEL POWER MODE    */
/*************************************************/
#define ACCEL_MODE_NORMAL   (0x11)
#define ACCEL_LOWPOWER      (0x12)
#define ACCEL_SUSPEND       (0x10)
/* BMI160 Accel power modes*/
#define BMI160_ACCEL_SUSPEND        0
#define BMI160_ACCEL_NORMAL_MODE    1
#define BMI160_ACCEL_LOW_POWER      2
/**************************************************/
/**\name    GYRO POWER MODE    */
/*************************************************/
#define GYRO_MODE_SUSPEND       (0x14)
#define GYRO_MODE_NORMAL        (0x15)
#define GYRO_MODE_FASTSTARTUP   (0x17)
/**************************************************/
/**\name    MAG POWER MODE    */
/*************************************************/
#define MAG_MODE_SUSPEND    (0x18)
#define MAG_MODE_NORMAL     (0x19)
#define MAG_MODE_LOWPOWER   (0x1A)
/**************************************************/
/**\name    ENABLE/DISABLE BIT VALUES    */
/*************************************************/
#define BMI160_ENABLE   (0x01)
#define BMI160_DISABLE  (0x00)
/**************************************************/
/**\name    INTERRUPT EDGE TRIGGER ENABLE    */
/*************************************************/
#define BMI160_EDGE     (0x01)
#define BMI160_LEVEL    (0x00)
/**************************************************/
/**\name    INTERRUPT LEVEL ENABLE    */
/*************************************************/
#define BMI160_LEVEL_LOW        (0x00)
#define BMI160_LEVEL_HIGH       (0x01)
/**************************************************/
/**\name    INTERRUPT OUTPUT ENABLE    */
/*************************************************/
#define BMI160_OPEN_DRAIN   (0x01)
#define BMI160_PUSH_PULL    (0x00)

/* interrupt output enable*/
#define BMI160_INPUT    (0x01)
#define BMI160_OUTPUT   (0x00)

/**************************************************/
/**\name    INTERRUPT TAP SOURCE ENABLE    */
/*************************************************/
#define FILTER_DATA     (0x00)
#define UNFILTER_DATA   (0x01)
/**************************************************/
/**\name    SLOW MOTION/ NO MOTION SELECT   */
/*************************************************/
#define SLOW_MOTION     (0x00)
#define NO_MOTION       (0x01)
/**************************************************/
/**\name    SIGNIFICANT MOTION SELECTION   */
/*************************************************/
#define ANY_MOTION          (0x00)
#define SIGNIFICANT_MOTION  (0x01)
/**************************************************/
/**\name    LATCH DURATION   */
/*************************************************/
#define BMI160_LATCH_DUR_NONE               (0x00)
#define BMI160_LATCH_DUR_312_5_MICRO_SEC    (0x01)
#define BMI160_LATCH_DUR_625_MICRO_SEC      (0x02)
#define BMI160_LATCH_DUR_1_25_MILLI_SEC     (0x03)
#define BMI160_LATCH_DUR_2_5_MILLI_SEC      (0x04)
#define BMI160_LATCH_DUR_5_MILLI_SEC        (0x05)
#define BMI160_LATCH_DUR_10_MILLI_SEC       (0x06)
#define BMI160_LATCH_DUR_20_MILLI_SEC       (0x07)
#define BMI160_LATCH_DUR_40_MILLI_SEC       (0x08)
#define BMI160_LATCH_DUR_80_MILLI_SEC       (0x09)
#define BMI160_LATCH_DUR_160_MILLI_SEC      (0x0A)
#define BMI160_LATCH_DUR_320_MILLI_SEC      (0x0B)
#define BMI160_LATCH_DUR_640_MILLI_SEC      (0x0C)
#define BMI160_LATCH_DUR_1_28_SEC           (0x0D)
#define BMI160_LATCH_DUR_2_56_SEC           (0x0E)
#define BMI160_LATCHED                      (0x0F)
/**************************************************/
/**\name    GYRO OFFSET MASK DEFINITION   */
/*************************************************/
#define BMI160_GYRO_MANUAL_OFFSET_0_7   (0x00FF)
#define BMI160_GYRO_MANUAL_OFFSET_8_9   (0x0300)
/**************************************************/
/**\name    STEP CONFIGURATION MASK DEFINITION   */
/*************************************************/
#define BMI160_STEP_CONFIG_0_7      (0x00FF)
#define BMI160_STEP_CONFIG_8_10     (0x0700)
#define BMI160_STEP_CONFIG_11_14    (0xF000)
/**************************************************/
/**\name    DEFINITION USED FOR DIFFERENT WRITE   */
/*************************************************/
#define BMI160_WRITE_TARGET_PAGE0   (0x00)
#define BMI160_WRITE_TARGET_PAGE1   (0x01)
#define BMI160_WRITE_ENABLE_PAGE1   (0x01)
#define BMI160_MANUAL_DISABLE       (0x00)
#define BMI160_MANUAL_ENABLE        (0x01)
#define BMI160_YAS_DISABLE_RCOIL    (0x00)
#define BMI160_ENABLE_MAG_IF_MODE   (0x02)
#define BMI160_ENABLE_ANY_MOTION_INTR1  (0x04)
#define BMI160_ENABLE_ANY_MOTION_INTR2  (0x04)
#define BMI160_MAG_DATA_READ_REG        (0x04)
#define BMI160_BMM_POWER_MODE_REG       (0x06)
#define BMI160_ENABLE_ANY_MOTION_AXIS   (0x07)
#define BMI160_ENABLE_LOW_G             (0x08)
#define BMI160_YAS532_ACQ_START         (0x11)
#define BMI160_YAS_DEVICE_ID_REG        (0x80)
#define BMI160_FIFO_GYRO_ENABLE         (0x80)
#define BMI160_SIG_MOTION_INTR_ENABLE   (0x01)
#define BMI160_STEP_DETECT_INTR_ENABLE  (0x01)
#define BMI160_LOW_G_INTR_STAT          (0x01)
#define BMI160_PULL_UP_DATA             (0x30)
#define BMI160_FIFO_M_G_A_ENABLE        (0xE0)
#define BMI160_FIFO_M_G_ENABLE          (0xA0)
#define BMI160_FIFO_M_A_ENABLE          (0x60)
#define BMI160_FIFO_G_A_ENABLE          (0xC0)
#define BMI160_FIFO_A_ENABLE            (0x40)
#define BMI160_FIFO_M_ENABLE            (0x20)

#define BMI160_SEC_IF_BMM150    (0)
#define BMI160_SEC_IF_AKM09911  (1)
#define BMI160_SEC_IF_AKM09912  (2)
#define BMI160_SEC_IF_YAS532    (3)
#define BMI160_SEC_IF_YAS537    (4)
/**************************************************/
/**\name    MAG INIT DEFINITION  */
/*************************************************/
#define BMI160_COMMAND_REG_ONE      (0x37)
#define BMI160_COMMAND_REG_TWO      (0x9A)
#define BMI160_COMMAND_REG_THREE    (0xC0)
#define RESET_STEP_COUNTER          (0xB2)
/**************************************************/
/**\name    BIT SLICE GET AND SET FUNCTIONS  */
/*************************************************/
#define BMI160_GET_BITSLICE(regvar, bitname)\
        ((regvar & bitname##__MSK) >> bitname##__POS)


#define BMI160_SET_BITSLICE(regvar, bitname, val)\
        ((regvar & ~bitname##__MSK) | \
        ((val<<bitname##__POS)&bitname##__MSK))

/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void BMI160_Initial(void);
extern BYTE BMI160_WriteRegister(BYTE v_command, BYTE v_data);
extern BYTE BMI160_set_command_register(BYTE v_command);

//-----------------------------------------------------------------------------
#endif  //_BOSCH_BMI160_H_
/*-----------------------------------------------------------------------------
 * End of BOSCH_BMI160.H */
