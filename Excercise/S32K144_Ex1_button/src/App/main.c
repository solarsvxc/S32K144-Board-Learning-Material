#include <stdint.h>
#include <S32K144.h>

#define BLUE_LED_PIN    0U
#define GREEN_LED_PIN   16U

#define BTN1_PIN        12U
#define BTN2_PIN        13U

int main(void)
{
    // set gpio
    IP_PCC->PCCn[PCC_PORTD_INDEX] &=~ PCC_PCCn_CGC_MASK;
    IP_PCC->PCCn[PCC_PORTC_INDEX] &=~ PCC_PCCn_CGC_MASK;

    IP_PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;
    IP_PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC_MASK;

    IP_PORTD->PCR[BLUE_LED_PIN]     = PORT_PCR_MUX(1);
    IP_PORTD->PCR[GREEN_LED_PIN]    = PORT_PCR_MUX(1);
    //
    
    //
    IP_PORTC->PCR[BTN1_PIN]         = PORT_PCR_MUX(1);
    IP_PORTC->PCR[BTN2_PIN]         = PORT_PCR_MUX(1);
    
    IP_PTD->PDDR |= (1 << BLUE_LED_PIN);
    IP_PTD->PDDR |= (1 << GREEN_LED_PIN);

    IP_PTC->PDDR &= ~(1 << BTN1_PIN);
    IP_PTC->PDDR &= ~(1 << BTN2_PIN);

    while (1)
    {
        uint32_t status_btn1 = (IP_PTC->PDIR & (1 << BTN1_PIN));
        uint32_t status_btn2 = (IP_PTC->PDIR & (1 << BTN2_PIN));

        if (status_btn1 != 0)
        {
            IP_PTD->PSOR |= (1 << BLUE_LED_PIN);
        }
        else
        {
            IP_PTD->PCOR |= (1 << BLUE_LED_PIN);
        }

        if (status_btn2 != 0)
        {
            IP_PTD->PSOR |= (1 << GREEN_LED_PIN);
        }
        else
        {
            IP_PTD->PCOR |= (1 << GREEN_LED_PIN);
        }
    }
    return 0;
}
