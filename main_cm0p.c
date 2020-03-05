/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"

//int i = 0;
int examplePower = 0; // 0=>off     1=>on
/*
void PressedHandler()
{
    //plan: start timer here after button is clicked once, and then handle there.
    if (examplePower==1) {
        examplePower=0;
    }
    else {
        examplePower=1;
    }
    NVIC_ClearPendingIRQ(Pressed_IRQ_cfg.intrSrc);
}*/
int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    /* Enable CM4.  CY_CORTEX_M4_APPL_ADDR must be updated if CM4 memory layout is changed. */
    Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR); 

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    //int exampleVoltage = 25;

    //UART_Start();

    for(;;)
    {/*
        Cy_SysInt_Init(&Pressed_IRQ_cfg, PressedHandler);
        NVIC_EnableIRQ(Pressed_IRQ_cfg.intrSrc);
        
        printf("POWER = %d", examplePower);*/
    }
}

/* [] END OF FILE */
