/**
 * @file main.c
 * @author duongnn
 * @brief
 * @version 0.1
 * @date 2025-09-24
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "S32K144.h"  
#include "driver_header/driver_nvic.h" 
#include "driver_header/driver_clock.h" 
#define BLUE     0
#define GREEN    16
#define RED      15

uint32_t count_flag = 0;
uint32_t led_state = 0;

/**
 * @brief i dont know, but on S32k cookbook always have this 
 * 
 */
void WDOG_disable (void)
{
    IP_WDOG->CNT = 0xD928C520;     			/* Unlock watchdog */
    IP_WDOG->TOVAL = 0x0000FFFF;   			/* Maximum timeout value */
    IP_WDOG->CS = 0x00002100;    			    /* Disable watchdog */
}

/**
 * @brief LPIT0 CHANNEL 0 init
 * 
 *  
 */
void init_LPIT0_CHn0(void)
{
    /* Enable clock source of SPLL_DIV2_CLK */
    IP_PCC->PCCn[PCC_LPIT_INDEX]   = PCC_PCCn_PCS(6);
    /* Enable Clock gating for LPIT PCC */
    IP_PCC->PCCn[PCC_LPIT_INDEX]   |= PCC_PCCn_CGC_MASK;

    /* Wait 4 clock cycles. How i know exactly ??! */
    for (int i = 0; i < 100; i++){} 
    IP_LPIT0->MCR |= LPIT_MCR_M_CEN_MASK;
    /* DBG_EN   = 0: Timer channels stop in Debug mode */
    /* DOZE_EN  = 0: Timer channels are stopped in DOZE mode */
    /* SW_RST   = 0: SW reset does not reset timer channels and registers */
    /* M_CEN    = 1: Enable module clock (allows writing other LPIT0 registers) */
    /* MODE     = 0: 32-bit Periodic Counter */
    /* CHAIN    = 0: Chainning disable */
    /* TIE1     = 1: Channel 0 Timer Interrupt Enable       */
    /* TSOT     = 0: Timer Start On Trigger  for Channel 0  */
    /* TSOI     = 0: Timer Stop On Interrupt for Channel 0  */
    /* TROT     = 0: Timer Reload On Trigger for Channel 0  Timer will not reload on the selected trigger */
    /* TRG_SRC  = 0: Trigger Source - Selects external triggers */
    /* TRG_SEL  = 0: Trigger Select - Timer channel 0 - 3 trigger source is selected */
    IP_LPIT0->TMR[0].TVAL = 40000000;
    /* T_EN = 1: Timer channel is enabled */
    IP_LPIT0->TMR[0].TCTRL |= LPIT_TMR_TCTRL_T_EN_MASK;
}   

int main(void)
{
    WDOG_disable();

    IP_PCC->PCCn[PCC_PORTD_INDEX]  &= ~PCC_PCCn_CGC_MASK;
    IP_PCC->PCCn[PCC_PORTD_INDEX]  |=  PCC_PCCn_CGC_MASK;
    
    IP_PORTD->PCR[BLUE]             = PORT_PCR_MUX(1);
    IP_PORTD->PCR[RED]              = PORT_PCR_MUX(1);
    IP_PORTD->PCR[GREEN]            = PORT_PCR_MUX(1);
    
    IP_PTD->PDDR                    |= (1U<<GREEN) | (1U<<BLUE) | (1U<<RED);
    IP_PTD->PSOR                    |= (1U<<GREEN) | (1U<<BLUE) | (1U<<RED);
    
    init_SOSC_8MHz();
    init_SPLL_160Mhz();
    normal_SPLL_run_80MHz();
    init_LPIT0_CHn0();

    while (1)
    {
        /* code */
        while (0==(IP_LPIT0->MSR & LPIT_MSR_TIF0_MASK)){}
        count_flag++;
        IP_PTD->PTOR |= (1U<<BLUE);
        IP_LPIT0->MSR |= LPIT_MSR_TIF0_MASK;
    }
}
