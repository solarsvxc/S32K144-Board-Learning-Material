#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdint.h>
#include <driver_gpio.h>

typedef struct {
    PORT_Type   *port;
    GPIO_Type   *gpio;
    uint32_t    pcc_index;
    uint32_t    pin_number;
} HAL_GPIO_PinConfig_t;

void HAL_GPIO_Init(int pin_number);
void HAL_GPIO_Dir(int pin_number, ARM_GPIO_DIRECTION direction);
void HAL_GPIO_Resistor(int pin_number,ARM_GPIO_PULL_RESISTOR resistor);
void HAL_GPIO_Ouput_level(int pin_number, uint32_t val);
uint32_t HAL_GPIO_Input_level(int pin_number);
#endif /* HAL_GPIO_H */