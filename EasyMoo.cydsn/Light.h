/******************************************************************************
* File Name: Light.h
*
* Version: Alpha
*
* Description: This file contains the firmware for setting up communication
* between the PSoC and the AS73211 True Color Sensor using the I2C protocol.
*
* Related Document: TrueColor_LightSensor.pdf
* Hardware Dependency:  CY8CKIT-063-BLE PSoC 6 BLE Pioneer kit
*                       AS73211 True Color Sensor
*
* Author(s):
*	Yousef H. Akbar & and Cow Team
*	Dept. Electrical and Computer Engineering
*	University of California, Davis
*******************************************************************************
* Refer to Section 7.18 of TrueColor_LightSensor.pdf for I2C R/W Protocols.
*
* General I2C Procedure (7.21):
*  - After supplying power: device in CONF state, but Powered Down.
*  	- This is where we set control registers for options.
*  	- Check by reading those same control registers.
*  - Switch to MEAS state while specifying what mode you want.
*
* Figure 42 and 43 for example reading/writing.
* Section 8 contains register bank information.
******************************************************************************/

#include "project.h"
#include "stdio.h"

/* Slave addresses */
#define LIGHT_ADDRESS 0x74    // 1110100[0|1]

/* Control Register Bank */
#define OSR     0x00        // Operational State Register (default 0x42)
#define CREG1   0x06        // Config Register 1
#define CREG2   0x07        // Config Register 2
#define CREG3   0x08        // Config Register 3
#define TBREAK  0x09        // Break time between measurements

/* Output Register Bank */
#define TEMP    0x01        // Temperature (0h + 12 bit temp result)
#define MRES1   0x02        // Measurement X-Channel RED
#define MRES2   0x03        // Y-Channel GREEN
#define MRES3   0x04        // Z-Channel BLUE

/* Function Name: lightI2CRead
 *
 * Summary:
 * This function reads from the light sensor using the I2C protocol. The general
 * procedure for read sequences is detailed in 7.19 and Figure 40.
 *
 * Parameters:
 *	@reg:		The register from which you want to read data.
 *
 * Return:
 *	readBuf:	Buffer containing data read from register
 */
uint8_t lightI2CRead(uint8_t reg)
{
    volatile cy_en_scb_i2c_status_t ret0 = 0;
    volatile cy_en_scb_i2c_status_t ret1 = 0;
    volatile cy_en_scb_i2c_status_t ret2 = 0;
    volatile cy_en_scb_i2c_status_t ret3 = 0;
    volatile cy_en_scb_i2c_status_t ret4 = 0;
    uint8_t readBuf[1] = {0};
    volatile cy_en_scb_i2c_command_t ackNack = 1u;
    
    // Start condition and broadcast slave address + WRITE bit (0)
    ret0 = I2C_MasterSendStart(LIGHT_ADDRESS, CY_SCB_I2C_WRITE_XFER, 100);
    CyDelay(1);
    // Broadcast register requested from slave LIGHT_ADDRESS
    ret1 = I2C_MasterWriteByte(reg, 100);
    CyDelay(1);
    // Start repeat condition, broadcast slave address + READ bit (1)
    ret2 = I2C_MasterSendReStart(LIGHT_ADDRESS, CY_SCB_I2C_READ_XFER, 100);
    CyDelay(1);
    // Read from I2C device, put received byte in readBuf and send ack signal.
    ret3 = I2C_MasterReadByte(ackNack, readBuf, 100);
    CyDelay(1);
    // End I2C transaction
    ret4 = I2C_MasterSendStop(100);
    
    printf("SendStart: %X, WriteByte: %X, SendReStart: %X, ReadByte: %X, SendStop: %X\r\n", ret0, ret1, ret2, ret3, ret4);
    
    return readBuf[0];
}

/* Function Name: lightI2CWrite
 *
 * Summary:
 * This function writes to the light sensor using the I2C protocol. The general
 * procedure for write sequences is detailed in 7.18 and Figure 40.
 *
 * Parameters:
 *	@reg:	The register to which you want to write data.
 *	@val:	The value you would like to write to @reg
 *
 * Return:
 * 	None.
 */
void lightI2CWrite(uint8_t reg, uint8_t value)
{
    volatile cy_en_scb_i2c_status_t ret0 = 0;
    volatile cy_en_scb_i2c_status_t ret1 = 0;
    volatile cy_en_scb_i2c_status_t ret2 = 0;
    volatile cy_en_scb_i2c_status_t ret3 = 0;
    
    // Start I2C transaction
    ret0 = I2C_MasterSendStart(LIGHT_ADDRESS, CY_SCB_I2C_WRITE_XFER, 100);
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

/* Function Name: lightMeasure
 *
 * Summary:
 * This function performs a single measurement cycle for the light sensor by
 * transitioning the device state from power down to measurement, then after the
 * measurement is complete (64ms later), we save the results.  Lastly, we
 * transition back to the power down state for power reduction.
 *
 * Parameters:
 *	@xChannel, yChannel, zChannel:	The 3 RGB channels from photodiodes.
 *	@temperature:			On-board temperature sensor result.
 *
 * Return:
 *	None.
 */
void lightMeasure(uint8_t *xChannel, uint8_t *yChannel, uint8_t *zChannel,
		uint8_t *temperature)
{
    /* Transition to Measurement mode 0x83 */
    lightI2CWrite(OSR, 0x83);
    /* Wait for conversion to finish, defined by TCONV */
    CyDelay(64);

    /* Read completed conversions */
    *temperature    = lightI2CRead(TEMP);
    *xChannel       = lightI2CRead(MRES1);
    *yChannel       = lightI2CRead(MRES2);
    *zChannel       = lightI2CRead(MRES3);

    /* Transition back to PowerDown, for power reduction */
    lightI2CWrite(OSR, 0x42);
}

void lightPrint(uint8_t x, uint8_t y, uint8_t z, uint8_t t)
{
    printf("\r\n\r\nLight Sensor Data:\r\n"
        "Red Light: %d\r\n"
        "Green Light: %d\r\n"
        "Blue Light: %d\r\n"
        "Temperature: %d\r\n", x, y, z, t);
}