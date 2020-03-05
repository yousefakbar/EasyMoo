/*******************************************************************************
* File Name: MCWDT_0.h
* Version 1.10
*
* Description:
*  This file provides constants and parameter values for the MCWDT_0
*  component.
*
********************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(MCWDT_0_CY_MCWDT_PDL_H)
#define MCWDT_0_CY_MCWDT_PDL_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "cyfitter.h"
#include "mcwdt/cy_mcwdt.h"

/*******************************************************************************
*   Variables
*******************************************************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t  MCWDT_0_initVar;
extern const cy_stc_mcwdt_config_t MCWDT_0_config;
/** @} group_globals */

/***************************************
*   Conditional Compilation Parameters
****************************************/
#define MCWDT_0_C0_CLEAR_ON_MATCH  (0U)
#define MCWDT_0_C1_CLEAR_ON_MATCH  (0U)
#define MCWDT_0_CASCADE_C0C1       (1U)
#define MCWDT_0_CASCADE_C1C2       (0U)
#define MCWDT_0_C0_MATCH           (32768U)
#define MCWDT_0_C0_MODE            (0U)
#define MCWDT_0_C1_MATCH           (32768U)
#define MCWDT_0_C1_MODE            (0U)
#define MCWDT_0_C2_PERIOD          (16U)
#define MCWDT_0_C2_MODE            (0U)

#if (0u == 1U)
    #define MCWDT_0_CTR0_EN_MASK   0UL
#else
    #define MCWDT_0_CTR0_EN_MASK   CY_MCWDT_CTR0
#endif
#if (0u == 1U)
    #define MCWDT_0_CTR1_EN_MASK   0UL
#else
    #define MCWDT_0_CTR1_EN_MASK   CY_MCWDT_CTR1
#endif
#if (0u == 1U)
    #define MCWDT_0_CTR2_EN_MASK   0UL
#else
    #define MCWDT_0_CTR2_EN_MASK   CY_MCWDT_CTR2
#endif

#define MCWDT_0_ENABLED_CTRS_MASK  (MCWDT_0_CTR0_EN_MASK |\
                                             MCWDT_0_CTR1_EN_MASK |\
                                             MCWDT_0_CTR2_EN_MASK)
											 
#if (1U == MCWDT_0_C0_MODE) || (3U == MCWDT_0_C0_MODE)
    #define MCWDT_0_CTR0_INT_MASK   CY_MCWDT_CTR0
#else
    #define MCWDT_0_CTR0_INT_MASK   0UL
#endif
#if (1U == MCWDT_0_C1_MODE) || (3U == MCWDT_0_C1_MODE)
    #define MCWDT_0_CTR1_INT_MASK   CY_MCWDT_CTR1
#else
    #define MCWDT_0_CTR1_INT_MASK   0UL
#endif
#if (1U == MCWDT_0_C2_MODE)
    #define MCWDT_0_CTR2_INT_MASK   CY_MCWDT_CTR2
#else
    #define MCWDT_0_CTR2_INT_MASK   0UL
#endif 

#define MCWDT_0_CTRS_INT_MASK      (MCWDT_0_CTR0_INT_MASK |\
                                             MCWDT_0_CTR1_INT_MASK |\
                                             MCWDT_0_CTR2_INT_MASK)										 

/***************************************
*        Registers Constants
***************************************/

/* This is a ptr to the base address of the MCWDT instance. */
#define MCWDT_0_HW                 (MCWDT_0_MCWDT__HW)

#if (0u == MCWDT_0_MCWDT__IDX)
    #define MCWDT_0_RESET_REASON   CY_SYSLIB_RESET_SWWDT0
#else
    #define MCWDT_0_RESET_REASON   CY_SYSLIB_RESET_SWWDT1
#endif 

#define MCWDT_0_TWO_LF_CLK_CYCLES_DELAY (62u)


/*******************************************************************************
*        Function Prototypes
*******************************************************************************/
/**
* \addtogroup group_general
* @{
*/
                void     MCWDT_0_Start(void);
                void     MCWDT_0_Stop(void);
__STATIC_INLINE cy_en_mcwdt_status_t MCWDT_0_Init(const cy_stc_mcwdt_config_t *config);
__STATIC_INLINE void     MCWDT_0_DeInit(void);
__STATIC_INLINE void     MCWDT_0_Enable(uint32_t counters, uint16_t waitUs);
__STATIC_INLINE void     MCWDT_0_Disable(uint32_t counters, uint16_t waitUs);
__STATIC_INLINE uint32_t MCWDT_0_GetEnabledStatus(cy_en_mcwdtctr_t counter);
__STATIC_INLINE void     MCWDT_0_Lock(void);
__STATIC_INLINE void     MCWDT_0_Unlock(void);
__STATIC_INLINE uint32_t MCWDT_0_GetLockedStatus(void);
__STATIC_INLINE void     MCWDT_0_SetMode(cy_en_mcwdtctr_t counter, cy_en_mcwdtmode_t mode);
__STATIC_INLINE cy_en_mcwdtmode_t MCWDT_0_GetMode(cy_en_mcwdtctr_t counter);
__STATIC_INLINE void     MCWDT_0_SetClearOnMatch(cy_en_mcwdtctr_t counter, uint32_t enable);
__STATIC_INLINE uint32_t MCWDT_0_GetClearOnMatch(cy_en_mcwdtctr_t counter);
__STATIC_INLINE void     MCWDT_0_SetCascade(cy_en_mcwdtcascade_t cascade);
__STATIC_INLINE cy_en_mcwdtcascade_t MCWDT_0_GetCascade(void);
__STATIC_INLINE void     MCWDT_0_SetMatch(cy_en_mcwdtctr_t counter, uint32_t match, uint16_t waitUs);
__STATIC_INLINE uint32_t MCWDT_0_GetMatch(cy_en_mcwdtctr_t counter);
__STATIC_INLINE void     MCWDT_0_SetToggleBit(uint32_t bit);
__STATIC_INLINE uint32_t MCWDT_0_GetToggleBit(void);
__STATIC_INLINE uint32_t MCWDT_0_GetCount(cy_en_mcwdtctr_t counter);
__STATIC_INLINE void     MCWDT_0_ResetCounters(uint32_t counters, uint16_t waitUs);
__STATIC_INLINE uint32_t MCWDT_0_GetInterruptStatus(void);
__STATIC_INLINE void     MCWDT_0_ClearInterrupt(uint32_t counters);
__STATIC_INLINE void     MCWDT_0_SetInterrupt(uint32_t counters);
__STATIC_INLINE uint32_t MCWDT_0_GetInterruptMask(void);
__STATIC_INLINE void     MCWDT_0_SetInterruptMask(uint32_t counters);
__STATIC_INLINE uint32_t MCWDT_0_GetInterruptStatusMasked(void);
__STATIC_INLINE uint32_t MCWDT_0_GetCountCascaded(void);
/** @} general */


/*******************************************************************************
* Function Name: MCWDT_0_Init
****************************************************************************//**
*
* Invokes the Cy_MCWDT_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_mcwdt_status_t MCWDT_0_Init(const cy_stc_mcwdt_config_t *config)
{
    return (Cy_MCWDT_Init(MCWDT_0_HW, config));
}


/*******************************************************************************
* Function Name: MCWDT_0_DeInit
****************************************************************************//**
*
* Invokes the Cy_MCWDT_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void MCWDT_0_DeInit(void)
{
    Cy_MCWDT_DeInit(MCWDT_0_HW);
}


/*******************************************************************************
* Function Name: MCWDT_0_Enable
****************************************************************************//**
*
* Invokes the Cy_MCWDT_Enable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void MCWDT_0_Enable(uint32_t counters, uint16_t waitUs)
{
    Cy_MCWDT_Enable(MCWDT_0_HW, counters, waitUs);
}


/*******************************************************************************
* Function Name: MCWDT_0_Disable
****************************************************************************//**
*
* Invokes the Cy_MCWDT_Disable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void MCWDT_0_Disable(uint32_t counters, uint16_t waitUs)
{
    Cy_MCWDT_Disable(MCWDT_0_HW, counters, waitUs);
}


/*******************************************************************************
* Function Name: MCWDT_0_GetEnabledStatus
****************************************************************************//**
*
* Invokes the Cy_MCWDT_GetEnabledStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t MCWDT_0_GetEnabledStatus(cy_en_mcwdtctr_t counter)
{
    return (Cy_MCWDT_GetEnabledStatus(MCWDT_0_HW, counter));
}


/*******************************************************************************
* Function Name: MCWDT_0_Lock
****************************************************************************//**
*
* Invokes the Cy_MCWDT_Lock() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void MCWDT_0_Lock(void)
{
    Cy_MCWDT_Lock(MCWDT_0_HW);
}


/*******************************************************************************
* Function Name: MCWDT_0_Unlock
****************************************************************************//**
*
* Invokes the Cy_MCWDT_Unlock() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void MCWDT_0_Unlock(void)
{
   Cy_MCWDT_Unlock(MCWDT_0_HW);
}


/*******************************************************************************
* Function Name: MCWDT_0_GetLockStatus
****************************************************************************//**
*
* Invokes the Cy_MCWDT_GetLockedStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t MCWDT_0_GetLockedStatus(void)
{
    return (Cy_MCWDT_GetLockedStatus(MCWDT_0_HW));
}


/*******************************************************************************
* Function Name: MCWDT_0_SetMode
****************************************************************************//**
*
* Invokes the Cy_MCWDT_SetMode() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void MCWDT_0_SetMode(cy_en_mcwdtctr_t counter, cy_en_mcwdtmode_t mode)
{
    Cy_MCWDT_SetMode(MCWDT_0_HW, counter, mode);
}


/*******************************************************************************
* Function Name: MCWDT_0_GetMode
****************************************************************************//**
*
* Invokes the Cy_MCWDT_GetMode() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_mcwdtmode_t MCWDT_0_GetMode(cy_en_mcwdtctr_t counter)
{
    return (Cy_MCWDT_GetMode(MCWDT_0_HW, counter));
}


/*******************************************************************************
* Function Name: MCWDT_0_SetClearOnMatch
****************************************************************************//**
*
* Invokes the Cy_MCWDT_SetClearOnMatch() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void MCWDT_0_SetClearOnMatch(cy_en_mcwdtctr_t counter, uint32_t enable)
{
    Cy_MCWDT_SetClearOnMatch(MCWDT_0_HW, counter, enable);
}


/*******************************************************************************
* Function Name: MCWDT_0_GetClearOnMatch
****************************************************************************//**
*
* Invokes the Cy_MCWDT_GetClearOnMatch() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t MCWDT_0_GetClearOnMatch(cy_en_mcwdtctr_t counter)
{
    return (Cy_MCWDT_GetClearOnMatch(MCWDT_0_HW, counter));
}


/*******************************************************************************
* Function Name: MCWDT_0_SetCascade
****************************************************************************//**
*
* Invokes the Cy_MCWDT_SetCascade() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void MCWDT_0_SetCascade(cy_en_mcwdtcascade_t cascade)
{
    Cy_MCWDT_SetCascade(MCWDT_0_HW, cascade);
}


/*******************************************************************************
* Function Name: MCWDT_0_GetCascade
****************************************************************************//**
*
* Invokes the Cy_MCWDT_GetCascade() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_mcwdtcascade_t MCWDT_0_GetCascade(void)
{
    return (Cy_MCWDT_GetCascade(MCWDT_0_HW));
}


/*******************************************************************************
* Function Name: MCWDT_0_SetMatch
****************************************************************************//**
*
* Invokes the Cy_MCWDT_SetMatch() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void MCWDT_0_SetMatch(cy_en_mcwdtctr_t counter, uint32_t match, uint16_t waitUs)
{
    Cy_MCWDT_SetMatch(MCWDT_0_HW, counter, match, waitUs);
}


/*******************************************************************************
* Function Name: MCWDT_0_GetMatch
****************************************************************************//**
*
* Invokes the Cy_MCWDT_GetMatch() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t MCWDT_0_GetMatch(cy_en_mcwdtctr_t counter)
{
    return (Cy_MCWDT_GetMatch(MCWDT_0_HW, counter));
}


/*******************************************************************************
* Function Name: MCWDT_0_SetToggleBit
****************************************************************************//**
*
* Invokes the Cy_MCWDT_SetToggleBit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void MCWDT_0_SetToggleBit(uint32_t bit)
{
    Cy_MCWDT_SetToggleBit(MCWDT_0_HW, bit);
}

/*******************************************************************************
* Function Name: MCWDT_0_GetToggleBit
****************************************************************************//**
*
* Invokes the Cy_MCWDT_GetToggleBit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t MCWDT_0_GetToggleBit(void)
{
    return (Cy_MCWDT_GetToggleBit(MCWDT_0_HW));
}


/*******************************************************************************
* Function Name: MCWDT_0_GetCount
****************************************************************************//**
*
* Invokes the Cy_MCWDT_GetCount() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t MCWDT_0_GetCount(cy_en_mcwdtctr_t counter)
{
    return (Cy_MCWDT_GetCount(MCWDT_0_HW, counter));
}


/*******************************************************************************
* Function Name: MCWDT_0_ResetCounters
****************************************************************************//**
*
* Invokes the Cy_MCWDT_ResetCounters() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void MCWDT_0_ResetCounters(uint32_t counters, uint16_t waitUs)
{
    Cy_MCWDT_ResetCounters(MCWDT_0_HW, counters, waitUs);
}


/*******************************************************************************
* Function Name: MCWDT_0_GetInterruptStatus
****************************************************************************//**
*
* Invokes the Cy_MCWDT_GetInterruptStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t MCWDT_0_GetInterruptStatus(void)
{
    return (Cy_MCWDT_GetInterruptStatus(MCWDT_0_HW));
}


/*******************************************************************************
* Function Name: MCWDT_0_ClearInterrupt
****************************************************************************//**
*
* Invokes the Cy_MCWDT_ClearInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void MCWDT_0_ClearInterrupt(uint32_t counters)
{
    Cy_MCWDT_ClearInterrupt(MCWDT_0_HW, counters);
}


/*******************************************************************************
* Function Name: MCWDT_0_SetInterrupt
****************************************************************************//**
*
* Invokes the Cy_MCWDT_SetInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void MCWDT_0_SetInterrupt(uint32_t counters)
{
    Cy_MCWDT_SetInterrupt(MCWDT_0_HW, counters);
}


/*******************************************************************************
* Function Name: MCWDT_0_GetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_MCWDT_GetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t MCWDT_0_GetInterruptMask(void)
{
    return (Cy_MCWDT_GetInterruptMask(MCWDT_0_HW));
}


/*******************************************************************************
* Function Name: MCWDT_0_SetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_MCWDT_SetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void MCWDT_0_SetInterruptMask(uint32_t counters)
{
    Cy_MCWDT_SetInterruptMask(MCWDT_0_HW, counters);
}


/*******************************************************************************
* Function Name: MCWDT_0_GetInterruptStatusMasked
****************************************************************************//**
* Invokes the Cy_MCWDT_GetInterruptStatusMasked() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t MCWDT_0_GetInterruptStatusMasked(void)
{
    return (Cy_MCWDT_GetInterruptStatusMasked(MCWDT_0_HW));
}


/*******************************************************************************
* Function Name: MCWDT_0_GetCountCascaded
****************************************************************************//**
* Invokes the Cy_MCWDT_GetCountCascaded() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t MCWDT_0_GetCountCascaded(void)
{
    return (Cy_MCWDT_GetCountCascaded(MCWDT_0_HW));
}

#if defined(__cplusplus)
}
#endif

#endif /* MCWDT_0_CY_MCWDT_PDL_H */


/* [] END OF FILE */
