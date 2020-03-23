/*******************************************************************************
* \file RTC.h
* \version 2.0
*
* This file provides the constants and parameter values for the RTC Component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(RTC_RTC_PDL_H)
#define RTC_RTC_PDL_H

#include "cyfitter.h"
#include "rtc/cy_rtc.h"

/* Initial interrupt state definition */
#define RTC_INITIAL_IRQ_STATUS        (1u)


/*******************************************************************************
*       Additional includes
*******************************************************************************/
#if (0u != RTC_INITIAL_IRQ_STATUS)
    #include "sysint/cy_sysint.h"
    #include "cyfitter_sysint.h"
    #include "cyfitter_sysint_cfg.h"
#endif /* (0u != RTC_INITIAL_IRQ_STATUS) */


/*******************************************************************************
*    Parameters definitions
*******************************************************************************/
/* Date Format setting constants */
#define RTC_MM_DD_YYYY                (0u)
#define RTC_DD_MM_YYYY                (1u)
#define RTC_YYYY_MM_DD                (2u)

/* Initial Date format definition */
#define RTC_INITIAL_DATA_FORMAT       (0u)

/* Time reset on start constant */
#define RTC_TIME_RESET_ON_START       (0u)

/* Initial Time and Date definitions */
#define RTC_INITIAL_DATE_SEC          (0u)
#define RTC_INITIAL_DATE_MIN          (0u)
#define RTC_INITIAL_DATE_HOUR         (9u)
#define RTC_INITIAL_DATE_HOUR_FORMAT  (CY_RTC_24_HOURS)
#define RTC_INITIAL_DATE_DOW          (2u)
#define RTC_INITIAL_DATE_DOM          (23u)
#define RTC_INITIAL_DATE_MONTH        (3u)
#define RTC_INITIAL_DATE_YEAR         (20u)

/* Initial DST definitions */
#define RTC_INITIAL_DST_STATUS        (0u)

#if(0u != RTC_INITIAL_DST_STATUS)
    
    #if(0u != RTC_TIME_RESET_ON_START)

        /* Definition of delay time which is required in Start function */
        #define RTC_DELAY_BEFORE_DST          (500u)
    #endif /* (0u != RTC_TIME_RESET_ON_START) */
    
    #define RTC_INITIAL_DST_DATE_TYPE     (0u)
    #define RTC_INITIAL_DST_START_MONTH   (3u)
    #define RTC_INITIAL_DST_START_WOM     (6u)
    #define RTC_INITIAL_DST_START_DOM     (22u)
    #define RTC_INITIAL_DST_START_DOW     (1u)
    #define RTC_INITIAL_DST_START_HRS     (0u)
    #define RTC_INITIAL_DST_STOP_MONTH    (10u)
    #define RTC_INITIAL_DST_STOP_DOM      (22u)
    #define RTC_INITIAL_DST_STOP_DOW      (1u)
    #define RTC_INITIAL_DST_STOP_WOM      (6u)
    #define RTC_INITIAL_DST_STOP_HRS      (0u)
#endif /* (0u != RTC_INITIAL_DST_STATUS) */

/*
* Definition of the date register fields. These macros are for creating a date
* value in a single word with the required date elements sequence.
*/
#if(RTC_INITIAL_DATA_FORMAT == RTC_MM_DD_YYYY)
    #define RTC_10_MONTH_OFFSET   (28u)
    #define RTC_MONTH_OFFSET      (24u)
    #define RTC_10_DAY_OFFSET     (20u)
    #define RTC_DAY_OFFSET        (16u)
    #define RTC_1000_YEAR_OFFSET  (12u)
    #define RTC_100_YEAR_OFFSET   (8u)
    #define RTC_10_YEAR_OFFSET    (4u)
    #define RTC_YEAR_OFFSET       (0u)
#elif(RTC_INITIAL_DATA_FORMAT == RTC_DD_MM_YYYY)
    #define RTC_10_MONTH_OFFSET   (20u)
    #define RTC_MONTH_OFFSET      (16u)
    #define RTC_10_DAY_OFFSET     (28u)
    #define RTC_DAY_OFFSET        (24u)
    #define RTC_1000_YEAR_OFFSET  (12u)
    #define RTC_100_YEAR_OFFSET   (8u)
    #define RTC_10_YEAR_OFFSET    (4u)
    #define RTC_YEAR_OFFSET       (0u)
#else
    #define RTC_10_MONTH_OFFSET   (12u)
    #define RTC_MONTH_OFFSET      (8u)
    #define RTC_10_DAY_OFFSET     (4u)
    #define RTC_DAY_OFFSET        (0u)
    #define RTC_1000_YEAR_OFFSET  (28u)
    #define RTC_100_YEAR_OFFSET   (24u)
    #define RTC_10_YEAR_OFFSET    (20u)
    #define RTC_YEAR_OFFSET       (16u)
#endif /* (RTC_INITIAL_DATA_FORMAT == RTC_MM_DD_YYYY) */


/*******************************************************************************
*    Global Variables
*******************************************************************************/
extern uint8_t RTC_initVar;
/**
* \addtogroup group_globals
* \{
*/
extern bool RTC_rtcDstStatus;
extern cy_stc_rtc_dst_t const RTC_dstConfig;
extern cy_stc_rtc_config_t const RTC_config;
/** \} group_globals */


/*******************************************************************************
*    Function Prototypes
*******************************************************************************/
void RTC_Start(void);

__STATIC_INLINE cy_en_rtc_status_t RTC_Init(cy_stc_rtc_config_t const *config);
__STATIC_INLINE cy_en_rtc_status_t RTC_SetDateAndTime(cy_stc_rtc_config_t const *dateTime);
__STATIC_INLINE cy_en_rtc_status_t RTC_SetDateAndTimeDirect(uint32_t sec, uint32_t min, uint32_t hour, 
                                                                  uint32_t date, uint32_t month, uint32_t year);
__STATIC_INLINE void RTC_GetDateAndTime(cy_stc_rtc_config_t *dateTime);

__STATIC_INLINE cy_en_rtc_status_t RTC_SetAlarmDateAndTime(cy_stc_rtc_alarm_t const *alarmDateTime,
                                                                        cy_en_rtc_alarm_t alarmIndex);
__STATIC_INLINE void RTC_GetAlarmDateAndTime(cy_stc_rtc_alarm_t *alarmDateTime,
                                                               cy_en_rtc_alarm_t alarmIndex);
__STATIC_INLINE cy_en_rtc_status_t RTC_SetAlarmDateAndTimeDirect(uint32_t sec, uint32_t min, 
                                                                              uint32_t hour, uint32_t date, 
                                                                              uint32_t month, cy_en_rtc_alarm_t alarmIndex);

__STATIC_INLINE cy_en_rtc_hours_format_t RTC_GetHoursFormat(void);
__STATIC_INLINE cy_en_rtc_status_t RTC_SetHoursFormat(cy_en_rtc_hours_format_t hourMode);
__STATIC_INLINE void RTC_SelectFrequencyPrescaler(cy_en_rtc_clock_freq_t clkSel);

__STATIC_INLINE uint32_t RTC_GetInterruptStatus(void);
__STATIC_INLINE void RTC_ClearInterrupt(uint32_t interruptMask);
__STATIC_INLINE void RTC_SetInterrupt(uint32_t interruptMask);
__STATIC_INLINE uint32_t RTC_GetInterruptMask(void);
__STATIC_INLINE void RTC_SetInterruptMask(uint32_t interruptMask);

#if(0u != RTC_INITIAL_IRQ_STATUS)

    __STATIC_INLINE void RTC_Interrupt(void);
    __STATIC_INLINE void RTC_DstInterrupt(cy_stc_rtc_dst_t const *dstTime);

    #if(0u != RTC_INITIAL_DST_STATUS)

        __STATIC_INLINE cy_en_rtc_status_t RTC_EnableDstTime(cy_stc_rtc_dst_t const *dstTime, 
                                                                          cy_stc_rtc_config_t const *timeDate);
        __STATIC_INLINE cy_en_rtc_status_t RTC_SetNextDstTime(cy_stc_rtc_dst_format_t const *nextDst);
        __STATIC_INLINE bool RTC_GetDstStatus(cy_stc_rtc_dst_t const *dstTime, 
                                                           cy_stc_rtc_config_t const *timeDate);
    #endif /* (0u != RTC_INITIAL_DST_STATUS) */
#endif /* (0u != RTC_INITIAL_IRQ_STATUS) */


/*******************************************************************************
* Function Name: RTC_Init
****************************************************************************//**
*
* Invokes the Cy_RTC_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_rtc_status_t RTC_Init(cy_stc_rtc_config_t const *config)
{
    return(Cy_RTC_Init(config));
}


/*******************************************************************************
* Function Name: RTC_GetHoursFormat
****************************************************************************//**
*
* Invokes the Cy_RTC_GetHoursFormat() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_rtc_hours_format_t RTC_GetHoursFormat(void)
{
    return(Cy_RTC_GetHoursFormat());
}


/*******************************************************************************
* Function Name: RTC_SetHoursFormat
****************************************************************************//**
*
* Invokes the Cy_RTC_SetHoursFormat() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_rtc_status_t RTC_SetHoursFormat(cy_en_rtc_hours_format_t hourMode)
{
    return(Cy_RTC_SetHoursFormat(hourMode));
}


/*******************************************************************************
* Function Name: RTC_SelectFrequencyPrescaler()
****************************************************************************//**
*
* Invokes the Cy_RTC_SelectFrequencyPrescaler() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RTC_SelectFrequencyPrescaler(cy_en_rtc_clock_freq_t clkSel)
{
    Cy_RTC_SelectFrequencyPrescaler(clkSel);
}


/*******************************************************************************
* Function Name: RTC_SetDateAndTime
****************************************************************************//**
*
* Invokes the Cy_RTC_SetDateAndTime() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_rtc_status_t RTC_SetDateAndTime(cy_stc_rtc_config_t const *dateTime)
{
    return(Cy_RTC_SetDateAndTime(dateTime));
}


/*******************************************************************************
* Function Name: RTC_GetDateAndTime
****************************************************************************//**
*
* Invokes the Cy_RTC_GetDateAndTime() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RTC_GetDateAndTime(cy_stc_rtc_config_t *dateTime)
{
    Cy_RTC_GetDateAndTime(dateTime);
}

/*******************************************************************************
* Function Name: RTC_SetAlarmDateAndTime
****************************************************************************//**
*
* Invokes the Cy_RTC_SetAlarmDateAndTime() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_rtc_status_t RTC_SetAlarmDateAndTime(cy_stc_rtc_alarm_t const *alarmDateTime,
                                                                        cy_en_rtc_alarm_t alarmIndex)
{
    return(Cy_RTC_SetAlarmDateAndTime(alarmDateTime, alarmIndex));
}


/*******************************************************************************
* Function Name: RTC_GetAlarmDateAndTime
****************************************************************************//**
*
* Invokes the Cy_RTC_GetAlarmDateAndTime() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RTC_GetAlarmDateAndTime(cy_stc_rtc_alarm_t *alarmDateTime, 
                                                          cy_en_rtc_alarm_t alarmIndex)
{
    Cy_RTC_GetAlarmDateAndTime(alarmDateTime, alarmIndex);
}


/*******************************************************************************
* Function Name: RTC_SetDateAndTimeDirect
****************************************************************************//**
*
* Invokes the Cy_RTC_SetDateAndTimeDirect() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_rtc_status_t RTC_SetDateAndTimeDirect(uint32_t sec, uint32_t min, uint32_t hour, 
                                                                         uint32_t date, uint32_t month, uint32_t year)
{
    return(Cy_RTC_SetDateAndTimeDirect(sec, min, hour, date, month, year));
}


/*******************************************************************************
* Function Name: RTC_SetAlarmDateAndTimeDirect
****************************************************************************//**
*
* Invokes the Cy_RTC_SetAlarmDateAndTimeDirect() PDL driver function.
*
*******************************************************************************/

__STATIC_INLINE cy_en_rtc_status_t RTC_SetAlarmDateAndTimeDirect(uint32_t sec, uint32_t min, 
                                                                              uint32_t hour, uint32_t date,
                                                                              uint32_t month, 
                                                                              cy_en_rtc_alarm_t alarmIndex)
{
    return(Cy_RTC_SetAlarmDateAndTimeDirect(sec, min, hour, date, month, alarmIndex));
}

#if(0u != RTC_INITIAL_IRQ_STATUS)
    /*******************************************************************************
    * Function Name: RTC_Interrupt
    ****************************************************************************//**
    *
    * RTC interrupt handler function. 
    * Invokes the Cy_RTC_Interrupt() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE void RTC_Interrupt(void)
    {
        Cy_RTC_Interrupt(&RTC_dstConfig, RTC_rtcDstStatus);
    }


    /*******************************************************************************
    * Function Name: RTC_DstInterrupt
    ****************************************************************************//**
    * 
    * Invokes the RTC_DstInterrupt() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE void RTC_DstInterrupt(cy_stc_rtc_dst_t const *dstTime)
    {
        Cy_RTC_DstInterrupt(dstTime);
    }


    #if(0u != RTC_INITIAL_DST_STATUS)
        /*******************************************************************************
        * Function Name: RTC_EnableDstTime
        ****************************************************************************//**
        * 
        * Invokes the Cy_RTC_EnableDstTime() PDL driver function.
        *
        *******************************************************************************/
        __STATIC_INLINE cy_en_rtc_status_t RTC_EnableDstTime(cy_stc_rtc_dst_t const *dstTime, 
                                                                          cy_stc_rtc_config_t const *timeDate)
        {
            return(Cy_RTC_EnableDstTime(dstTime, timeDate));
        }


        /*******************************************************************************
        * Function Name: Cy_RTC_SetNextDstTime
        ****************************************************************************//**
        *
        * Invokes the Cy_RTC_SetNextDstTime() PDL driver function.
        *
        *******************************************************************************/
        __STATIC_INLINE cy_en_rtc_status_t RTC_SetNextDstTime(cy_stc_rtc_dst_format_t const *nextDst)
        {
            return(Cy_RTC_SetNextDstTime(nextDst));
        }

        /*******************************************************************************
        * Function Name: RTC_GetDstStatus
        ****************************************************************************//**
        *
        * Invokes the Cy_RTC_GetDstStatus() PDL driver function.
        *
        *******************************************************************************/
        __STATIC_INLINE bool RTC_GetDstStatus(cy_stc_rtc_dst_t const *dstTime, 
                                                           cy_stc_rtc_config_t const *timeDate)
        {
            return(Cy_RTC_GetDstStatus(dstTime, timeDate));
        }
    #endif /* (0u != RTC_INITIAL_DST_STATUS) */

#endif /* (0u != RTC_INITIAL_IRQ_STATUS) */



/*******************************************************************************
* Function Name: RTC_GetInterruptStatus
****************************************************************************//**
*
* Invokes the Cy_RTC_GetInterruptStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t RTC_GetInterruptStatus(void)
{
    return(Cy_RTC_GetInterruptStatus());
}


/*******************************************************************************
* Function Name: RTC_ClearInterrupt
****************************************************************************//**
*
* Invokes the Cy_RTC_ClearInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RTC_ClearInterrupt(uint32_t interruptMask)
{
    Cy_RTC_ClearInterrupt(interruptMask);
}


/*******************************************************************************
* Function Name: RTC_SetInterrupt
****************************************************************************//**
*
* Invokes the Cy_RTC_SetInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RTC_SetInterrupt(uint32_t interruptMask)
{
    Cy_RTC_SetInterrupt(interruptMask);
}


/*******************************************************************************
* Function Name: RTC_GetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_RTC_GetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t RTC_GetInterruptMask(void)
{
    return(Cy_RTC_GetInterruptMask());
}


/*******************************************************************************
* Function Name: RTC_SetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_RTC_SetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RTC_SetInterruptMask(uint32_t interruptMask)
{
    Cy_RTC_SetInterruptMask(interruptMask);
}


/*******************************************************************************
* Function Name: RTC_IsExternalResetOccurred
****************************************************************************//**
*
* Invokes the Cy_RTC_IsExternalResetOccurred() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE bool RTC_IsExternalResetOccurred(void)
{
    return(Cy_RTC_IsExternalResetOccurred());
}

#endif /* RTC_RTC_PDL_H */


/* [] END OF FILE */
