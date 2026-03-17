#include <stdint.h>
#include <S32K144.h>
// #define BTN1_PIN        12U
// #define BTN2_PIN        13U

#define BLUE_LED_PIN    0U
#define GREEN_LED_PIN   16U
#define POT_A           6U

int main(void)
{
//    uint32_t vref = 0;
    uint32_t value = 0;

    IP_PCC->PCCn[PCC_PORTD_INDEX] &=~ PCC_PCCn_CGC_MASK;
    IP_PCC->PCCn[PCC_PORTA_INDEX] &=~ PCC_PCCn_CGC_MASK;
    IP_PCC->PCCn[PCC_ADC0_INDEX]  &=~ PCC_PCCn_CGC_MASK;

    IP_PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;
    IP_PCC->PCCn[PCC_PORTA_INDEX] |= PCC_PCCn_CGC_MASK;

    IP_PORTD->PCR[BLUE_LED_PIN]   |= PORT_PCR_MUX(1);
    IP_PORTD->PCR[GREEN_LED_PIN]  |= PORT_PCR_MUX(1);

    IP_PORTA->PCR[POT_A] &=~ PORT_PCR_MUX_MASK;

    IP_PTD->PDDR |= (1 << BLUE_LED_PIN) | (1 << GREEN_LED_PIN);
    IP_PTD->PCOR = (1 << BLUE_LED_PIN);
	IP_PTD->PCOR = (1 << GREEN_LED_PIN);

//    IP_SCG->FIRCCSR  &=~ SCG_FIRCCSR_FIRCEN_MASK;

    IP_SCG->SOSCCFG |= SCG_SOSCCFG_EREFS(1); /* external osc */
    IP_SCG->SOSCCFG |= SCG_SOSCCFG_RANGE(0b10); /* Range error: auto set High range  */

    IP_SCG->SOSCCSR |= SCG_SOSCCSR_SOSCEN(1);
    while (!(IP_SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK)){}
    
    IP_SCG->SOSCDIV &=~ SCG_SOSCDIV_SOSCDIV1_MASK;
    IP_SCG->SOSCDIV |= SCG_SOSCDIV_SOSCDIV2(1);
    
    IP_SCG->RCCR    &=~ SCG_RCCR_SCS_MASK;
    IP_SCG->RCCR    |= SCG_RCCR_SCS(1); /* System OSC (SOSC_CLK) */  

    // while (((IP_SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT) != 1);

    IP_PCC->PCCn[PCC_ADC0_INDEX] |= PCC_PCCn_PCS(1);
    IP_PCC->PCCn[PCC_ADC0_INDEX] |= PCC_PCCn_CGC_MASK;
    
    IP_ADC0->CFG1 &=~ ADC_CFG1_ADICLK_MASK;
    IP_ADC0->CFG1 &=~ ADC_CFG1_ADIV_MASK;
    IP_ADC0->CFG1 |=  ADC_CFG1_MODE(1);

    IP_ADC0->SC2  &=~ ADC_SC2_REFSEL_MASK; 
    IP_ADC0->SC2  &=~ ADC_SC2_ADTRG_MASK;

    
    IP_ADC0->CFG2    = ADC_CFG2_SMPLTS(20);
    
    while (1)
    {
        IP_ADC0->SC1[0] &= ~ADC_SC1_ADCH_MASK;
        IP_ADC0->SC1[0] |= ADC_SC1_ADCH(12);

        while((IP_ADC0->SC1[0] & ADC_SC1_COCO_MASK)>>ADC_SC1_COCO_SHIFT){}
        
        value = IP_ADC0->R[0];
        if (1000 <= value && value <= 2000)
        {
            IP_PTD->PSOR = (1<<BLUE_LED_PIN);
        } else {
            
            IP_PTD->PCOR = (1<<BLUE_LED_PIN);
        }

        if (2000 <= value)
        {
            IP_PTD ->PSOR = (1<<GREEN_LED_PIN);
        } else {
            IP_PTD ->PCOR = (1<<GREEN_LED_PIN);
        }
    }
    return 0;
}
