/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <DriverHeader/Driver_Gpio.h>
#include "DriverHeader/Driver_Port.h"
#include "S32K144.h"

#define RED 0
#define BLUE 16
#define GREEN 15

int main(void)
{
    PCC_Disable(PCC_PORTD_INDEX);
    PCC_Enable(PCC_PORTD_INDEX);
    
    PORTx_Select(IP_PORTD,IP_PTD);
    
    Driver_GPIO0.Setup(BLUE,NULL);
    Driver_GPIO0.SetDirection(BLUE,ARM_GPIO_OUTPUT);
}
