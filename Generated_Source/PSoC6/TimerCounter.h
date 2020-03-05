/*******************************************************************************
* File Name: TimerCounter.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the TimerCounter
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(TimerCounter_CY_TCPWM_COUNTER_PDL_H)
#define TimerCounter_CY_TCPWM_COUNTER_PDL_H

#include "cyfitter.h"
#include "tcpwm/cy_tcpwm_counter.h"

   
/*******************************************************************************
* Variables
*******************************************************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t  TimerCounter_initVar;
extern cy_stc_tcpwm_counter_config_t const TimerCounter_config;
/** @} group_globals */


/***************************************
*  Conditional Compilation Parameters
***************************************/

#define TimerCounter_INIT_COMPARE_OR_CAPTURE    (2UL)


/***************************************
*        Function Prototypes
****************************************/
/**
* \addtogroup group_general
* @{
*/
void TimerCounter_Start(void);
__STATIC_INLINE cy_en_tcpwm_status_t TimerCounter_Init(cy_stc_tcpwm_counter_config_t const *config);
__STATIC_INLINE void TimerCounter_DeInit(void);
__STATIC_INLINE void TimerCounter_Enable(void);
__STATIC_INLINE void TimerCounter_Disable(void);
__STATIC_INLINE uint32_t TimerCounter_GetStatus(void);

#if(CY_TCPWM_COUNTER_MODE_CAPTURE == TimerCounter_INIT_COMPARE_OR_CAPTURE)
    __STATIC_INLINE uint32_t TimerCounter_GetCapture(void);
    __STATIC_INLINE uint32_t TimerCounter_GetCaptureBuf(void);
#else
    __STATIC_INLINE void TimerCounter_SetCompare0(uint32_t compare0);
    __STATIC_INLINE uint32_t TimerCounter_GetCompare0(void);
    __STATIC_INLINE void TimerCounter_SetCompare1(uint32_t compare1);
    __STATIC_INLINE uint32_t TimerCounter_GetCompare1(void);
    __STATIC_INLINE void TimerCounter_EnableCompareSwap(bool enable);
#endif /* (CY_TCPWM_COUNTER_MODE_CAPTURE == TimerCounter_INIT_COMPARE_OR_CAPTURE) */

__STATIC_INLINE void TimerCounter_SetCounter(uint32_t count);
__STATIC_INLINE uint32_t TimerCounter_GetCounter(void);
__STATIC_INLINE void TimerCounter_SetPeriod(uint32_t period);
__STATIC_INLINE uint32_t TimerCounter_GetPeriod(void);
__STATIC_INLINE void TimerCounter_TriggerStart(void);
__STATIC_INLINE void TimerCounter_TriggerReload(void);
__STATIC_INLINE void TimerCounter_TriggerStop(void);
__STATIC_INLINE void TimerCounter_TriggerCapture(void);
__STATIC_INLINE uint32_t TimerCounter_GetInterruptStatus(void);
__STATIC_INLINE void TimerCounter_ClearInterrupt(uint32_t source);
__STATIC_INLINE void TimerCounter_SetInterrupt(uint32_t source);
__STATIC_INLINE void TimerCounter_SetInterruptMask(uint32_t mask);
__STATIC_INLINE uint32_t TimerCounter_GetInterruptMask(void);
__STATIC_INLINE uint32_t TimerCounter_GetInterruptStatusMasked(void);
/** @} general */


/***************************************
*           API Constants
***************************************/

/**
* \addtogroup group_macros
* @{
*/
/** This is a ptr to the base address of the TCPWM instance */
#define TimerCounter_HW                 (TimerCounter_TCPWM__HW)

/** This is a ptr to the base address of the TCPWM CNT instance */
#define TimerCounter_CNT_HW             (TimerCounter_TCPWM__CNT_HW)

/** This is the counter instance number in the selected TCPWM */
#define TimerCounter_CNT_NUM            (TimerCounter_TCPWM__CNT_IDX)

/** This is the bit field representing the counter instance in the selected TCPWM */
#define TimerCounter_CNT_MASK           (1UL << TimerCounter_CNT_NUM)
/** @} group_macros */

#define TimerCounter_INPUT_MODE_MASK    (0x3U)
#define TimerCounter_INPUT_DISABLED     (7U)


/*******************************************************************************
* Function Name: TimerCounter_Init
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_tcpwm_status_t TimerCounter_Init(cy_stc_tcpwm_counter_config_t const *config)
{
    return(Cy_TCPWM_Counter_Init(TimerCounter_HW, TimerCounter_CNT_NUM, config));
}


/*******************************************************************************
* Function Name: TimerCounter_DeInit
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TimerCounter_DeInit(void)                   
{
    Cy_TCPWM_Counter_DeInit(TimerCounter_HW, TimerCounter_CNT_NUM, &TimerCounter_config);
}

/*******************************************************************************
* Function Name: TimerCounter_Enable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Enable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TimerCounter_Enable(void)                   
{
    Cy_TCPWM_Enable_Multiple(TimerCounter_HW, TimerCounter_CNT_MASK);
}


/*******************************************************************************
* Function Name: TimerCounter_Disable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Disable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TimerCounter_Disable(void)                  
{
    Cy_TCPWM_Disable_Multiple(TimerCounter_HW, TimerCounter_CNT_MASK);
}


/*******************************************************************************
* Function Name: TimerCounter_GetStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_GetStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t TimerCounter_GetStatus(void)                
{
    return(Cy_TCPWM_Counter_GetStatus(TimerCounter_HW, TimerCounter_CNT_NUM));
}


#if(CY_TCPWM_COUNTER_MODE_CAPTURE == TimerCounter_INIT_COMPARE_OR_CAPTURE)
    /*******************************************************************************
    * Function Name: TimerCounter_GetCapture
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_GetCapture() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE uint32_t TimerCounter_GetCapture(void)               
    {
        return(Cy_TCPWM_Counter_GetCapture(TimerCounter_HW, TimerCounter_CNT_NUM));
    }


    /*******************************************************************************
    * Function Name: TimerCounter_GetCaptureBuf
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_GetCaptureBuf() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE uint32_t TimerCounter_GetCaptureBuf(void)            
    {
        return(Cy_TCPWM_Counter_GetCaptureBuf(TimerCounter_HW, TimerCounter_CNT_NUM));
    }
#else
    /*******************************************************************************
    * Function Name: TimerCounter_SetCompare0
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_SetCompare0() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE void TimerCounter_SetCompare0(uint32_t compare0)      
    {
        Cy_TCPWM_Counter_SetCompare0(TimerCounter_HW, TimerCounter_CNT_NUM, compare0);
    }


    /*******************************************************************************
    * Function Name: TimerCounter_GetCompare0
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_GetCompare0() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE uint32_t TimerCounter_GetCompare0(void)              
    {
        return(Cy_TCPWM_Counter_GetCompare0(TimerCounter_HW, TimerCounter_CNT_NUM));
    }


    /*******************************************************************************
    * Function Name: TimerCounter_SetCompare1
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_SetCompare1() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE void TimerCounter_SetCompare1(uint32_t compare1)      
    {
        Cy_TCPWM_Counter_SetCompare1(TimerCounter_HW, TimerCounter_CNT_NUM, compare1);
    }


    /*******************************************************************************
    * Function Name: TimerCounter_GetCompare1
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_GetCompare1() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE uint32_t TimerCounter_GetCompare1(void)              
    {
        return(Cy_TCPWM_Counter_GetCompare1(TimerCounter_HW, TimerCounter_CNT_NUM));
    }


    /*******************************************************************************
    * Function Name: TimerCounter_EnableCompareSwap
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_EnableCompareSwap() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE void TimerCounter_EnableCompareSwap(bool enable)  
    {
        Cy_TCPWM_Counter_EnableCompareSwap(TimerCounter_HW, TimerCounter_CNT_NUM, enable);
    }
#endif /* (CY_TCPWM_COUNTER_MODE_CAPTURE == TimerCounter_INIT_COMPARE_OR_CAPTURE) */


/*******************************************************************************
* Function Name: TimerCounter_SetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_SetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TimerCounter_SetCounter(uint32_t count)          
{
    Cy_TCPWM_Counter_SetCounter(TimerCounter_HW, TimerCounter_CNT_NUM, count);
}


/*******************************************************************************
* Function Name: TimerCounter_GetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_GetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t TimerCounter_GetCounter(void)               
{
    return(Cy_TCPWM_Counter_GetCounter(TimerCounter_HW, TimerCounter_CNT_NUM));
}


/*******************************************************************************
* Function Name: TimerCounter_SetPeriod
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_SetPeriod() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TimerCounter_SetPeriod(uint32_t period)          
{
    Cy_TCPWM_Counter_SetPeriod(TimerCounter_HW, TimerCounter_CNT_NUM, period);
}


/*******************************************************************************
* Function Name: TimerCounter_GetPeriod
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_GetPeriod() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t TimerCounter_GetPeriod(void)                
{
    return(Cy_TCPWM_Counter_GetPeriod(TimerCounter_HW, TimerCounter_CNT_NUM));
}


/*******************************************************************************
* Function Name: TimerCounter_TriggerStart
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TimerCounter_TriggerStart(void)             
{
    Cy_TCPWM_TriggerStart(TimerCounter_HW, TimerCounter_CNT_MASK);
}


/*******************************************************************************
* Function Name: TimerCounter_TriggerReload
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerReloadOrIndex() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TimerCounter_TriggerReload(void)     
{
    Cy_TCPWM_TriggerReloadOrIndex(TimerCounter_HW, TimerCounter_CNT_MASK);
}


/*******************************************************************************
* Function Name: TimerCounter_TriggerStop
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStopOrKill() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TimerCounter_TriggerStop(void)
{
    Cy_TCPWM_TriggerStopOrKill(TimerCounter_HW, TimerCounter_CNT_MASK);
}


/*******************************************************************************
* Function Name: TimerCounter_TriggerCapture
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerCaptureOrSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TimerCounter_TriggerCapture(void)     
{
    Cy_TCPWM_TriggerCaptureOrSwap(TimerCounter_HW, TimerCounter_CNT_MASK);
}


/*******************************************************************************
* Function Name: TimerCounter_GetInterruptStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t TimerCounter_GetInterruptStatus(void)       
{
    return(Cy_TCPWM_GetInterruptStatus(TimerCounter_HW, TimerCounter_CNT_NUM));
}


/*******************************************************************************
* Function Name: TimerCounter_ClearInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_ClearInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TimerCounter_ClearInterrupt(uint32_t source)     
{
    Cy_TCPWM_ClearInterrupt(TimerCounter_HW, TimerCounter_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: TimerCounter_SetInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TimerCounter_SetInterrupt(uint32_t source)
{
    Cy_TCPWM_SetInterrupt(TimerCounter_HW, TimerCounter_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: TimerCounter_SetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TimerCounter_SetInterruptMask(uint32_t mask)     
{
    Cy_TCPWM_SetInterruptMask(TimerCounter_HW, TimerCounter_CNT_NUM, mask);
}


/*******************************************************************************
* Function Name: TimerCounter_GetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t TimerCounter_GetInterruptMask(void)         
{
    return(Cy_TCPWM_GetInterruptMask(TimerCounter_HW, TimerCounter_CNT_NUM));
}


/*******************************************************************************
* Function Name: TimerCounter_GetInterruptStatusMasked
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatusMasked() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t TimerCounter_GetInterruptStatusMasked(void)
{
    return(Cy_TCPWM_GetInterruptStatusMasked(TimerCounter_HW, TimerCounter_CNT_NUM));
}

#endif /* TimerCounter_CY_TCPWM_COUNTER_PDL_H */


/* [] END OF FILE */
