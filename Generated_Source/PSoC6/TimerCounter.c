/*******************************************************************************
* File Name: TimerCounter.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the TimerCounter
*  component
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "TimerCounter.h"

/** Indicates whether or not the TimerCounter has been initialized. 
*  The variable is initialized to 0 and set to 1 the first time 
*  TimerCounter_Start() is called. This allows the Component to 
*  restart without reinitialization after the first call to 
*  the TimerCounter_Start() routine.
*/
uint8_t TimerCounter_initVar = 0U;

/** The instance-specific configuration structure. This should be used in the 
*  associated TimerCounter_Init() function.
*/ 
cy_stc_tcpwm_counter_config_t const TimerCounter_config =
{
        .period = 1000UL,
        .clockPrescaler = 0UL,
        .runMode = 0UL,
        .countDirection = 1UL,
        .compareOrCapture = 2UL,
        .compare0 = 16384UL,
        .compare1 = 16384UL,
        .enableCompareSwap = false,
        .interruptSources = 0UL,
        .captureInputMode = 3UL,
        .captureInput = CY_TCPWM_INPUT_CREATOR,
        .reloadInputMode = 3UL,
        .reloadInput = CY_TCPWM_INPUT_CREATOR,
        .startInputMode = 3UL,
        .startInput = CY_TCPWM_INPUT_CREATOR,
        .stopInputMode = 3UL,
        .stopInput = CY_TCPWM_INPUT_CREATOR,
        .countInputMode = 1UL,
        .countInput = CY_TCPWM_INPUT_CREATOR,
};


/*******************************************************************************
* Function Name: TimerCounter_Start
****************************************************************************//**
*
*  Calls the TimerCounter_Init() when called the first time and enables 
*  the TimerCounter. For subsequent calls the configuration is left 
*  unchanged and the component is just enabled.
*
* \globalvars
*  \ref TimerCounter_initVar
*
*******************************************************************************/
void TimerCounter_Start(void)
{
    if (0U == TimerCounter_initVar)
    {
        (void)Cy_TCPWM_Counter_Init(TimerCounter_HW, TimerCounter_CNT_NUM, &TimerCounter_config); 

        TimerCounter_initVar = 1U;
    }

    Cy_TCPWM_Enable_Multiple(TimerCounter_HW, TimerCounter_CNT_MASK);
    
    #if (TimerCounter_INPUT_DISABLED == 7UL)
        Cy_TCPWM_TriggerStart(TimerCounter_HW, TimerCounter_CNT_MASK);
    #endif /* (TimerCounter_INPUT_DISABLED == 7UL) */    
}


/* [] END OF FILE */
