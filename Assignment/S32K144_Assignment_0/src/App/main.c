#include <stdint.h>
#include <driver_gpio.h>
#include <HAL_gpio.h>
#include <stdio.h>

static ARM_DRIVER_GPIO Driver_GPIOD;
static ARM_DRIVER_GPIO Driver_GPIOC;

// typedef void (*ARM_GPIO_SignalEvent_t) (ARM_GPIO_Pin_t pin, uint32_t event);  /* Pointer to \ref ARM_GPIO_SignalEvent : Signal GPIO Event */

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

    Driver_GPIOC.Setup(PTC13, NULL);
    Driver_GPIOC.SetDirection(PTC13, ARM_GPIO_INPUT);
    
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
