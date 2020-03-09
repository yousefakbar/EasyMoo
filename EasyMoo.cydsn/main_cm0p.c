/******************************************************************************
* File Name: main_cm0p.c
*
* Version: Beta
*
* Description: This is the main firmware file for the EasyMoo capstone project.
* This PSoC project is for a cow physical health monitor product, utilizing SoC
* circuitry, including sensors and a battery powered module.
*
* Related Document: TrueColor_LightSensor.pdf
* Hardware Dependency:  CY8CKIT-063-BLE PSoC 6 BLE Pioneer kit
*                       AS73211 True Color Sensor
*
* Author(s):
*	Yousef H. Akbar & and Cow Team
*	Dept. Electrical and Computer Engineering
*	University of California, Davis
******************************************************************************/
#include "project.h"
#include "stdio.h"

/* Project Firmware Dependencies */
#include "BLE.h"
#include "Light.h"
#include "Accelerometer.h"
#include "RTC_Alarm.h"

/* Global Variables */
uint16_t xChannel, yChannel, zChannel, temperature;	// Light Sensor Vars
uint16_t accX, accY, accZ;				// Accelerometer
uint16_t gyroX, gyroY, gyroZ;				// Gyroscope

/* The interrupt status variable */

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR);

    /* UART Initialization */
    UART_Start();
    setvbuf(stdin,NULL,_IONBF,0);
    
    /* initiate I2C */
    I2C_Start();
    
    CyDelay(5000);
    
    init_RTC();
    
    for(;;)
    {
        lightMeasure(&xChannel, &yChannel, &zChannel, &temperature);
        lightPrint(xChannel, yChannel, zChannel);
        
        CyDelay(1000);
        
        /* If the alarm flag is set, clear it, toggle the LED, and step */
        if(alarmFlag)  /* the flag is set, meaning time has expired */
        {
			/* We have handled this alarm */
			alarmFlag = 0u;	
            
            /* Configure the next RTC alarm, add the interval to the time
               for the next alarm */
            RtcStepAlarm();
        }

        /* Go to Deep Sleep mode until next interrupt  */
        Cy_SysPm_DeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
    }
}
