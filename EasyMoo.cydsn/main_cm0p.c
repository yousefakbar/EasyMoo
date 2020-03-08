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

/* Global Variables */
uint8_t xChannel, yChannel, zChannel, temperature;

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    /* Enable CM4.  CY_CORTEX_M4_APPL_ADDR must be updated if CM4 memory layout is changed. */
    Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR); 

    /* UART Initialization */
    UART_Start();
    setvbuf(stdin,NULL,_IONBF,0);
    
    /* initiate I2C */
    I2C_Start();
    
    /* TODO: BLE Broadcast Trial */
    //cy_stc_ble_gap_bonded_device_list_info_t bonded_list;
    //broadcastBLE();
    CyDelay(5000);
    
    for(;;)
    {
        /* TODO: BLE Broadcast Trial */
        //cy_en_ble_api_result_t bondres = Cy_BLE_GAP_GetBondList(&bonded_list);
        //printf("Result: %d\r\n", bondres);
        //printf("%d Connected Devices\r\n", bonded_list.noOfDevices);
        lightMeasure(&xChannel, &yChannel, &zChannel, &temperature);
        lightPrint(xChannel, yChannel, zChannel, temperature);
        CyDelay(1000);
    }
}
