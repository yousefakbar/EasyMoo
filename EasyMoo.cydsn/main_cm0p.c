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
#include "FSM.h"
#include "BLE.h"
#include "Light.h"
#include "Accelerometer.h"
#include "RTC_Alarm.h"
#include "Queue.h"

/* Happy Score Benchmarks */
#define TARG_LIGHT_AVG  (8)
#define TARG_TEMP_AVG   (25)

/* Global Variables */
uint16_t xChannel, yChannel, zChannel, temperature;	// Light Sensor Vars
uint16_t accX, accY, accZ;				// Accelerometer
uint16_t gyroX, gyroY, gyroZ;				// Gyroscope
int tempFlag    = 0;
int accInactive = 0;
int lightFlag   = 0;
queue_t light_queue = NULL;
queue_t temp_queue  = NULL;
queue_t acc_queue   = NULL;
queue_t gyro_queue  = NULL;

void update_happy_score(void)
{
    int avg_light_score = 0;
    int avg_temp_score  = 0;
    int count           = queue_length(light_queue);
    int *tmp            = 0;
    
    while (queue_length(light_queue) > 0) {
        queue_dequeue(light_queue, (void**)&tmp);
        avg_light_score += *tmp;
        queue_dequeue(temp_queue, (void**)&tmp);
        avg_temp_score += *tmp;
    }
    
    avg_light_score = avg_light_score / count;
    avg_temp_score  = avg_temp_score / count;
    
    /* TODO: calculate deviation for happy score (avg - targ_avg) */
}

int main(void)
{ /* TODO: fsm details */
    __enable_irq(); /* Enable global interrupts. */
    Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR);

    /* UART Initialization */
    UART_Start();
    setvbuf(stdin,NULL,_IONBF,0);
    
    /* initiate I2C */
    I2C_Start();
    
    CyDelay(5000);
    
    init_RTC();
    
    light_queue = queue_create();
    temp_queue  = queue_create();
    acc_queue   = queue_create();
    gyro_queue  = queue_create();
    int *lightdata;
    int data_count = 0;
    
    for(;;)
    {
        lightMeasure(&xChannel, &yChannel, &zChannel, &temperature);
        lightPrint(xChannel, yChannel, zChannel);
        light_process_data(xChannel, yChannel, zChannel, temp_queue, light_queue);
        data_count++;

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

        update_happy_score();
        //updateFSM(&fsm, accInactive, lightFlag, tempFlag);
        /* Go to Deep Sleep mode until next interrupt  */
        Cy_SysPm_DeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
    }
}
