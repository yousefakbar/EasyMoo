/******************************************************************************
* File Name: Accelerometer.h
*
* Version: Beta
*
* Description: This file contains the firmware for setting up communication
* between the PSoC and the 9-axis accelerometer sensor using the I2C protocol.
*
* Related Document: Sensor-Nine-Axis.pdf
* Hardware Dependency:  CY8CKIT-063-BLE PSoC 6 BLE Pioneer kit
*                       ICM-20948 Nine-Axis Low Power Sensor
*
* Author(s):
*	Yousef H. Akbar & and Cow Team
*	Dept. Electrical and Computer Engineering
*	University of California, Davis
*******************************************************************************
* Refer to Section 6.1 to 6.4 of Sensor-Nine-Axis.pdf for I2C protocol specs.
******************************************************************************/

#include "project.h"
#include "stdio.h"

/* Slave addresses */
#define ACC_ADDRESS 0x68    // 1101000[0|1]

/* Output Register Bank */
#define WHOAMI      0x00
#define INT_ENABLE  0x01
#define XACCEL_H    0x2D
#define YACCEL_H    0x2F
#define ZACCEL_H    0x31
#define XGYRO_H     0x33
#define YGYRO_H     0x35
#define ZGYRO_H     0x37

uint16_t accI2CRead(uint8_t reg)
{
    volatile cy_en_scb_i2c_status_t ret0 = 0;
    volatile cy_en_scb_i2c_status_t ret1 = 0;
    volatile cy_en_scb_i2c_status_t ret2 = 0;
    volatile cy_en_scb_i2c_status_t ret3 = 0;
    volatile cy_en_scb_i2c_status_t ret4 = 0;
    volatile cy_en_scb_i2c_status_t ret5 = 0;
    uint8_t readBuf[2] = {0, 0};
    
    // Start condition and broadcast slave address + WRITE bit (0)
    ret0 = I2C_MasterSendStart(ACC_ADDRESS, CY_SCB_I2C_WRITE_XFER, 100);
    CyDelay(1);
    // Broadcast register requested from slave ACC_ADDRESS
    ret1 = I2C_MasterWriteByte(reg, 100);
    CyDelay(1);
    // Start repeat condition, broadcast slave address + READ bit (1)
    ret2 = I2C_MasterSendReStart(ACC_ADDRESS, CY_SCB_I2C_READ_XFER, 100);
    CyDelay(1);
    // Read from I2C device, put received byte in readBuf and send ack signal.
    ret3 = I2C_MasterReadByte(CY_SCB_I2C_ACK, &(readBuf[1]), 100);
    CyDelay(1);
    ret5 = I2C_MasterReadByte(CY_SCB_I2C_NAK, &(readBuf[0]), 100);
    CyDelay(1);
    // End I2C transaction
    ret4 = I2C_MasterSendStop(100);
    
    printf("SendStart: %X,"
		    "WriteByte: %X,"
		    "SendReStart: %X,"
		    "ReadByte: %X,"
            "ReadByte2: %X"
		    "SendStop: %X\r\n", ret0, ret1, ret2, ret3, ret5, ret4);
    
    //Start_Number = (Start_Number_High << 8) | (Start_Number_Low & 0xff);
    return (readBuf[1] << 8) | (readBuf[0] & 0xff);
}

void accI2CWrite(uint8_t reg, uint8_t value)
{
    volatile cy_en_scb_i2c_status_t ret0 = 0;
    volatile cy_en_scb_i2c_status_t ret1 = 0;
    volatile cy_en_scb_i2c_status_t ret2 = 0;
    volatile cy_en_scb_i2c_status_t ret3 = 0;
    
    // Start I2C transaction
    ret0 = I2C_MasterSendStart(ACC_ADDRESS, CY_SCB_I2C_WRITE_XFER, 100);
    CyDelay(1);
    //Write to I2C device
    ret1 = I2C_MasterWriteByte(reg, 100);
    ret2 = I2C_MasterWriteByte(value, 100);
    CyDelay(1);
    // End I2C transaction
    ret3 = I2C_MasterSendStop(100);
    
    printf("SendStart: %X, WriteByte: %X,%X, SendStop: %X\r\n", ret0, ret1,
		    ret2, ret3);
}

void accMeasure(uint16_t *accX, uint16_t *accY, uint16_t *accZ)
{
    /* Read completed conversions */
    *accX       = accI2CRead(XACCEL_H);
    *accY       = accI2CRead(YACCEL_H);
    *accZ       = accI2CRead(ZACCEL_H);
}

void gyroMeasure(uint16_t *gyroX, uint16_t *gyroY, uint16_t *gyroZ)
{
    /* Read completed conversions */
    *gyroX       = accI2CRead(XGYRO_H);
    *gyroY       = accI2CRead(YGYRO_H);
    *gyroZ       = accI2CRead(ZGYRO_H);
}
