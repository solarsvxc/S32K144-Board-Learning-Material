#include <stdint.h>
#include <S32K144.h>
#include <driver_gpio.h>
//#include <core_cm4.h>

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
//    Driver_GPIOC.SetEventTrigger(PTC12,ARM_GPIO_EVENT_FALLING_EDGE);
    
    Driver_GPIOC.Setup(PTC13, NULL);
    Driver_GPIOC.SetDirection(PTC13, ARM_GPIO_INPUT);

//    NVIC_SetPriority(PORTC_IRQn,1);
//    NVIC_EnableIRQ(PORTC_IRQn);

    while (1)
    {
        uint32_t input_level_1 = Driver_GPIOC.GetInput(PTC12);
        uint32_t input_level_2 = Driver_GPIOC.GetInput(PTC13);

        if (input_level_1 != 0)
        {
            Driver_GPIOD.SetOutput(PTD0, 1);
        } else {
            Driver_GPIOD.SetOutput(PTD0, 0);
        }

        if (input_level_2 != 0)
        {
            Driver_GPIOD.SetOutput(PTD15, 1);
        } else {
            Driver_GPIOD.SetOutput(PTD15, 0);
        }

    }
    return 0;
}
