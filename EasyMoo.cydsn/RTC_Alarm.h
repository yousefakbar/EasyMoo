/******************************************************************************
* File Name: RTC_Alarm.h
*
* Version: Beta
*
* Description: This is the firmware for setting up the RTC counter clock. The
* RTC is used for waking up the CPU from deep sleep at a select interval. The
* interval can be adjusted by modifying the macros in this file.
*
* Related Document: CE218542_PSoC_Custom_TickTimer_RTC.pdf
* Hardware Dependency:  CY8CKIT-063-BLE PSoC 6 BLE Pioneer kit
*
* Author(s):
*	Adapted from the PSoC CE218542 Code Example
*
*	Yousef H. Akbar & and Cow Team
*	Dept. Electrical and Computer Engineering
*	University of California, Davis
******************************************************************************/

#include "project.h"

/* Macros */
#define MAX_ATTEMPTS        (500u)  /* Number of attempts for RTC operation */ 
#define INIT_DELAY          (5u)    /* Delay 5 milliseconds before each trial */

#define SECONDS_PER_MIN     (60u)   /* used to keep values in range */
#define MINUTES_PER_HOUR    (60u)

#define TICK_INTERVAL       (5u)    /* Seconds or minutes. 1-59 Range */
#define USE_SECONDS         (1u)    /* set to one to use, to zero to not use */
#define USE_MINUTES         (0u)    /* use seconds OR minutes, not both  */

/* The interrupt status variable */
static uint32_t alarmFlag = 0u;

/* 
    If an En field is set to CY_RTC_ALARM_DISABLE, the alarm
    function ignores the disabled field when looking for a match.
    Configured to ignore all matches but enable the alarm, and
    the alarm goes off once per second, because the RTC uses 
    one-second resolution. 
*/
cy_stc_rtc_alarm_t alarmConfig = 
{
    .sec            = RTC_INITIAL_DATE_SEC,
    .secEn          = CY_RTC_ALARM_DISABLE,
    .min            = RTC_INITIAL_DATE_MIN,
    .minEn          = CY_RTC_ALARM_DISABLE,
    .hour           = RTC_INITIAL_DATE_HOUR,
    .hourEn         = CY_RTC_ALARM_DISABLE,
    .dayOfWeek      = RTC_INITIAL_DATE_DOW,
    .dayOfWeekEn    = CY_RTC_ALARM_DISABLE,
    .date           = RTC_INITIAL_DATE_DOM,
    .dateEn         = CY_RTC_ALARM_DISABLE,
    .month          = RTC_INITIAL_DATE_MONTH,
    .monthEn        = CY_RTC_ALARM_DISABLE,
    .almEn          = CY_RTC_ALARM_ENABLE
};

/*****************************************************************************/
/*                      Function Prototypes                                  */
/*****************************************************************************/
cy_en_rtc_status_t RtcInit(void);
cy_en_rtc_status_t RtcAlarmConfig(void);
void RtcInterruptHandler(void);
void RtcStepAlarm(void);

/******************************************************************************
* Function Name: main
*******************************************************************************
*
* Summary: This is the system entrance point for Cortex-M4.
* This function generates a custom tick time interrupt using RTC alarm function.
*
* Parameters:
*  None
*
* Return:
*  int
*
* Side Effects:
*  None  
*
******************************************************************************/
void init_RTC(void)
{
    /* Init RTC - Configure the time and date */
    if(RtcInit() != CY_RTC_SUCCESS)
    {
        /* If operation fails, halt */
        CY_ASSERT(0u);
    }
    else  /* Configures the alarm to enable interrupt */
    {   
        /*
            To create a periodic alarm once per minute, enable the seconds match.
            Do not enable the minutes match, because all that matters is the
            seconds number. If it's zero, then every time the RTC second wraps
            around to zero, there is a match, and the alarm goes off.
        */
        if( (TICK_INTERVAL == 1u) && (USE_MINUTES == 1u))
        {
            alarmConfig.secEn = CY_RTC_ALARM_ENABLE;
        }

        /* Now configure the alarm */
        if(RtcAlarmConfig() != CY_RTC_SUCCESS)
        {
           /* If operation fails, halt */
           CY_ASSERT(0u);
        }
        else
        {
	        /* This CE uses Alarm2, enable that interrupt */
		    Cy_RTC_SetInterruptMask(CY_RTC_INTR_ALARM2);
        }
    }
    
    /* Enable RTC interrupt handler function */
    Cy_SysInt_Init(&RTC_RTC_IRQ_cfg, RtcInterruptHandler);
    NVIC_EnableIRQ(RTC_RTC_IRQ_cfg.intrSrc);
}

/******************************************************************************
* Function Name: RtcInit
*******************************************************************************
*
* Summary: 
*  This function configures the RTC registers.
*
* Parameters:
*  None
*
* Return:
*  cy_en_rtc_status_t
*       CY_RTC_SUCCESS      : Time and date configuration is successfully done.
*       CY_RTC_BAD_PARAM    : Date values are not valid.
*       CY_RTC_INVALID_STATE: RTC is busy state
*
******************************************************************************/
cy_en_rtc_status_t RtcInit(void)
{
    uint32_t attempts = MAX_ATTEMPTS;
    cy_en_rtc_status_t result;
    
    /* Setting the time and date can fail. For example the RTC might be busy.
       Check the result and try again, if necessary.  */
    do
    {
        result = Cy_RTC_Init(&RTC_config);
        attempts--;
        
        Cy_SysLib_Delay(INIT_DELAY);
    } while(( result != CY_RTC_SUCCESS) && (attempts != 0u));
    
	return (result);
}

/******************************************************************************
* Function Name: RtcAlarmConfig
*******************************************************************************
*
* Summary: 
*  This function configures the custom RTC alarm to utilize the custom tick
*  timer interrupt.
*
* Parameters:
*  None
*
* Return:
*  cy_en_rtc_status_t
*       CY_RTC_SUCCESS      : Time and date configuration is successfully done.
*       CY_RTC_BAD_PARAM    : Date values are not valid.
*       CY_RTC_INVALID_STATE: RTC is busy state
*
******************************************************************************/
cy_en_rtc_status_t RtcAlarmConfig(void)
{
    uint32_t attempts = MAX_ATTEMPTS;
    cy_en_rtc_status_t result;

    /* 
       Setting the alarm can fail. For example the RTC might be busy. 
       Check the result and try again, if necessary.
    */
    do
	{
		result = Cy_RTC_SetAlarmDateAndTime((cy_stc_rtc_alarm_t const
					*)&alarmConfig, CY_RTC_ALARM_2);
		attempts--;
        
		Cy_SysLib_Delay(INIT_DELAY);
    } while(( result != CY_RTC_SUCCESS) && (attempts != 0u));
    
	return (result);
}

/******************************************************************************
* Function Name: RtcInterruptHandler
*******************************************************************************
*
* Summary: 
*  This is the general RTC interrupt handler in CPU NVIC.
*  It calls the Alarm2 interrupt handler if that is the interrupt that occurs.
*
* Parameters:
*  None
*
* Return:
*  None
*
******************************************************************************/
void RtcInterruptHandler(void)
{
    /* No DST parameters are required for the custom tick. */
    Cy_RTC_Interrupt(NULL, false);
}

/******************************************************************************
* Function Name: Cy_RTC_Alarm2Interrupt
*******************************************************************************
*
* Summary: 
*  The function overrides the __WEAK Cy_RTC_Alarm2Interrupt() in cy_rtc.c to 
*  handle CY_RTC_ALARM_2 interrupt.
*
* Parameters:
*  None
*
* Return:
*  None
*
******************************************************************************/
void Cy_RTC_Alarm2Interrupt(void)
{
    /* the interrupt has fired, meaning time expired and the alarm went off */
	alarmFlag = 1u;  

}

/******************************************************************************
* Function Name: RtcStepAlarm
*******************************************************************************
*
* Summary: 
*  This function sets the time for CY_RTC_ALARM_2, and configures the interrupt.
*  The available periods are one second to sixty seconds and one minute to sixty 
*  minutes. 
*
* Parameters:
*  None
*
* Return:
*  None
*
******************************************************************************/
void RtcStepAlarm(void)
{
    /* Don't set next time, if the interval is one second or one minute */
    if(TICK_INTERVAL != 1u)
    {
        if (USE_MINUTES)  /* match minutes, and advance by minutes */
    	{
		/*
		Enable the correct matches. This is a periodic interrupt, but
		happens every two or more minutes. Because we are stepping by
		minutes, we need to match the minutes number. We also match the
		seconds number so the alarm only goes off when both the seconds
		and minutes match. Because we are not changing the value of the
		seconds in the alarm, the alarm happens only once when the
		minutes match.
		*/
            alarmConfig.secEn = CY_RTC_ALARM_ENABLE;
            alarmConfig.minEn = CY_RTC_ALARM_ENABLE;

    		/* advance the minute by the specified interval */
    		alarmConfig.min += TICK_INTERVAL;

            /* keep it in range, 0-59 */
            alarmConfig.min = alarmConfig.min % MINUTES_PER_HOUR;
    	}
    	else   /* USE_SECONDS, alarm when the seconds match */
    	{
    		/* 
                Enable the correct matches. Because we are stepping by seconds, 
                we need to match just the seconds number.
            */
            alarmConfig.secEn = CY_RTC_ALARM_ENABLE;

    		/* advance the second by the specified interval */
    		alarmConfig.sec += TICK_INTERVAL;

            /* keep it in range, 0-59 */
            alarmConfig.sec = alarmConfig.sec % SECONDS_PER_MIN;
    	}
    	
    	/* update the alarm configuration */
    	if(RtcAlarmConfig() != CY_RTC_SUCCESS)
    	{
    	   /* If the operation fails, halt */
    	   CY_ASSERT(0u);
    	}
    }
}

/* [] END OF FILE */
