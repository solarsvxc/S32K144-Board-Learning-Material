/**
 * @file main.c
 * @author duongnn (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-09-26
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "S32K144.h"

#define POTENTIOMETER_C 14
#define BLUE_D           0
#define GREEN_D    16
#define RED_D      15

uint32_t adcResultInMv_pot = 0;
uint32_t adcResultInMv_Vrefsh = 0;


uint8_t adc_complete(void)  {
  return ((IP_ADC0->SC1[0] & ADC_SC1_COCO_MASK)>>ADC_SC1_COCO_SHIFT); /* Wait for completion */
}
uint32_t read_adc_chx(void)  {
    uint16_t adc_result=0;
    adc_result=IP_ADC0->R[0];      /* For SW trigger mode, R[0] is used */
    return  (uint32_t) ((5000*adc_result)/0xFFF); /* Convert result to mv for 0-5V range */
}
/**
 * @brief
 *
 * @return
 */
int main(void)
{
    /*<======================ADC0-Init===========================>*/
    /* Disable clock */
    IP_PCC->PCCn[PCC_ADC0_INDEX] &=~ PCC_PCCn_CGC_MASK;
    /* Enable bus clock in ADC 	*/
    IP_PCC->PCCn[PCC_ADC0_INDEX] |= PCC_PCCn_CGC_MASK;
    /* ADCH=1F: Module is disabled for conversions	*/
    IP_ADC0->SC1[0] |= ADC_SC1_ADCH_MASK;
    /* CFG1 MODE = 00b -> 10 bit conversion */
    /* ADIV = 00b -> input by rate clock */
    IP_ADC0->CFG1   = ADC_CFG1_ADIV(0) | ADC_CFG1_MODE(0);
    /* AIEN disable */
    IP_ADC0->SC1[0] |= ADC_SC1_AIEN(0);
    /* SMPLTS default */
    IP_ADC0->CFG2   = ADC_CFG2_SMPLTS(0xC);
    /* */
    IP_ADC0->SC2    = 0x00000000;
    IP_ADC0->SC3    = 0x00000000;

    /*<======================GPIO-PORT Init===========================>*/
    /*<! Disable CGC on PORTC */
    IP_PCC->PCCn[PCC_PORTC_INDEX] &= ~PCC_PCCn_CGC_MASK;
    /*<! Enable CGC on PORTC */
    IP_PCC->PCCn[PCC_PORTC_INDEX]  |= PCC_PCCn_CGC_MASK;
    /*<! Disable CGC on PORTD */
    IP_PCC->PCCn[PCC_PORTD_INDEX] &= ~PCC_PCCn_CGC_MASK;
    /*<! Disable CGC on PORTD */
    IP_PCC->PCCn[PCC_PORTD_INDEX]  |= PCC_PCCn_CGC_MASK;

    IP_PORTC->PCR[POTENTIOMETER_C]    = PORT_PCR_MUX(0);

    IP_PORTD->PCR[GREEN_D]            = PORT_PCR_MUX(1);
    IP_PORTD->PCR[BLUE_D]             = PORT_PCR_MUX(1);
    IP_PORTD->PCR[RED_D]              = PORT_PCR_MUX(1);

    IP_PTD->PDDR                          |= (1U<<BLUE_D)  | (1U<<GREEN_D) | (1U<<RED_D);
    IP_PTD->PSOR                        |= (1U<<GREEN_D) | (1U<<BLUE_D)  | (1U<<RED_D);

    while (1)
    {
        /* Initiate new conversion by writing to ADC0_SC1A(ADCH) */
        /* ADCH = 12: External channel 12 as input */
        IP_ADC0->SC1[0] |= ADC_SC1_ADCH(0x11);
        /* Check SC1[0] value at sequence 0 compare with ADC_SC1_COCO_MASK <value at bit number 8 of register SC1>
        *  Then shift right value compared */
//        while (adc_complete()==0){};

        adcResultInMv_pot = IP_ADC0->R[0];

        if ( 0 <  adcResultInMv_pot && adcResultInMv_pot <= 341 )
        {
            IP_PTD->PTOR   = (1U<<RED_D);
        } else if (341 < adcResultInMv_pot && adcResultInMv_pot <= 682)
        {
            IP_PTD->PTOR   = (1U<<BLUE_D);
        } else if ( 682 < adcResultInMv_pot && adcResultInMv_pot <= 1023)
        {
            IP_PTD->PTOR   = (1U<<GREEN_D);
        }
        /* DELAY function */
        for (uint8_t i = 0; i < 100; i++){}
    }
}

