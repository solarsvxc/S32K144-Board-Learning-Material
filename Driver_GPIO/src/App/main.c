#include <stdint.h>
#include <S32K144.h>
#include <driver_gpio.h>
#include <core_cm4.h>
/*NOTE: IP_MPU -> SYS_IP_MPU s32k144.h*/

void PORTC_IRQHandler(void) 
{
    uint32_t isfr_flag = IP_PORTC->ISFR;

    static uint8_t state_PTD15 = 1;
    static uint8_t state_PTD0 = 1;

    if ((isfr_flag & (1U<<12)) != 0)
    {
        IP_PORTC->ISFR = (1U<<12);
        state_PTD15 = !state_PTD15;
        Driver_GPIOD.SetOutput(PTD15, state_PTD15);
    }

    if ((isfr_flag & (1U<<13)) != 0)
    {
        IP_PORTC->ISFR = (1U<<13);
        state_PTD0 = !state_PTD0;
        Driver_GPIOD.SetOutput(PTD0, state_PTD0);
    }
}


int main(void)
{
    Driver_GPIOD.Setup(PTD0, NULL);
    Driver_GPIOD.SetDirection(PTD0, ARM_GPIO_OUTPUT);
    Driver_GPIOD.SetOutput(PTD0, 1);

    Driver_GPIOD.Setup(PTD15, NULL);
    Driver_GPIOD.SetDirection(PTD15, ARM_GPIO_OUTPUT);
    Driver_GPIOD.SetOutput(PTD15, 1);

    Driver_GPIOD.Setup(PTD16, NULL);
    Driver_GPIOD.SetDirection(PTD16, ARM_GPIO_OUTPUT);
    Driver_GPIOD.SetOutput(PTD16, 1);

    Driver_GPIOC.Setup(PTC12, NULL);
    Driver_GPIOC.SetDirection(PTC12, ARM_GPIO_INPUT);   
    Driver_GPIOC.SetEventTrigger(PTC12,ARM_GPIO_EVENT_RISING_EDGE);
    
    Driver_GPIOC.Setup(PTC13, NULL);
    Driver_GPIOC.SetDirection(PTC13, ARM_GPIO_INPUT);
    Driver_GPIOC.SetEventTrigger(PTC13,ARM_GPIO_EVENT_RISING_EDGE);

    NVIC_SetPriority(PORTC_IRQn,1);
    NVIC_EnableIRQ(PORTC_IRQn);

    while (1)
    {

    }
    return 0;
}
