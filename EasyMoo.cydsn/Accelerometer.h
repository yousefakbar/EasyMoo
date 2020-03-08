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
