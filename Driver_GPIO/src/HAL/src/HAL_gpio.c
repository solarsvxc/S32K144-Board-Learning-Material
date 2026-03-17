#include "HAL_gpio.h"
#include <driver_gpio.h>
#include <S32K144.h>

/* DMA Request */
#define IRQC_DMA_RISING              (0x1U)  // DMA on Rising Edge
#define IRQC_DMA_FALLING             (0x2U)  // DMA on Falling Edge
#define IRQC_DMA_EITHER              (0x3U)  // DMA on Either Edge (Rising & Falling)

/* Interrupt Request */
#define IRQC_INT_LOGIC_0             (0x8U)  // Interrupt when Logic 0
#define IRQC_INT_RISING              (0x9U)  // Interrupt on Rising Edge 
#define IRQC_INT_FALLING             (0xAU)  // Interrupt on Falling Edge 
#define IRQC_INT_EITHER              (0xBU)  // Interrupt on Either Edge 
#define IRQC_INT_LOGIC_1             (0xCU)  // Interrupt when Logic 1

/**
 * @brief Set the pin index based on the pin number
 * 
 * @param pin_number The GPIO pin number
 * @param pin_config Pointer to HAL_GPIO_PinConfig_t structure to be filled
 * @example  IP_PORTA->PCR[config_resistor.pin_number] |= PORT_PCR_PE_MASK;
 */
static void HAL_Pin_Set(int pin_number, HAL_GPIO_PinConfig_t *pin_config) 
{
    switch (pin_number)
    {
        case PTA0: case PTB0: case PTC0: case PTD0: case PTE0:
            pin_config->pin_number = 0;
            break;
        case PTA1: case PTB1: case PTC1: case PTD1: case PTE1:
            pin_config->pin_number = 1;
            break;
        case PTA2: case PTB2: case PTC2: case PTD2: case PTE2:
            pin_config->pin_number = 2;
            break;
        case PTA3: case PTB3: case PTC3: case PTD3: case PTE3:
            pin_config->pin_number = 3;
            break;
        case PTA4: case PTB4: case PTC4: case PTD4: case PTE4:
            pin_config->pin_number = 4;
            break;
        case PTA5: case PTB5: case PTC5: case PTD5: case PTE5:
            pin_config->pin_number = 5;
            break;
        case PTA6: case PTB6: case PTC6: case PTD6: case PTE6:
            pin_config->pin_number = 6;
            break;
        case PTA7: case PTB7: case PTC7: case PTD7: case PTE7:
            pin_config->pin_number = 7;
            break;
        case PTA8: case PTB8: case PTC8: case PTD8: case PTE8: 
            pin_config->pin_number = 8;
            break;
        case PTA9: case PTB9: case PTC9: case PTD9: case PTE9:
            pin_config->pin_number = 9;
            break;
        case PTA10: case PTB10: case PTC10: case PTD10: case PTE10:
            pin_config->pin_number = 10;
            break;
        case PTA11: case PTB11: case PTC11: case PTD11: case PTE11:
            pin_config->pin_number = 11;
            break;
        case PTA12: case PTB12: case PTC12: case PTD12: case PTE12:
            pin_config->pin_number = 12;
            break;
        case PTA13: case PTB13: case PTC13: case PTD13: case PTE13:
            pin_config->pin_number = 13;
            break;
        case PTA14: case PTB14: case PTC14: case PTD14: case PTE14:
            pin_config->pin_number = 14;
            break;
        case PTA15: case PTB15: case PTC15: case PTD15: case PTE15:
            pin_config->pin_number = 15;
            break;
        case PTA16: case PTB16: case PTC16: case PTD16: case PTE16:
            pin_config->pin_number = 16;
            break;
        case PTA17: case PTB17: case PTC17: case PTD17:
            pin_config->pin_number = 17;
            break;
    default:
            pin_config->pin_number = -1;
        break;
    }

    switch (pin_number)
    {
        case PTA0: case PTA1: case PTA2: case PTA3: case PTA4: case PTA5:
        case PTA6: case PTA7: case PTA8: case PTA9: case PTA10: case PTA11:
        case PTA12: case PTA13: case PTA14: case PTA15: case PTA16: case PTA17:
            pin_config->port = IP_PORTA;
            pin_config->gpio = IP_PTA;
            pin_config->pcc_index = PCC_PORTA_INDEX;
            break;

        case PTB0: case PTB1: case PTB2: case PTB3: case PTB4: case PTB5:
        case PTB6: case PTB7: case PTB8: case PTB9: case PTB10: case PTB11:
        case PTB12: case PTB13: case PTB14: case PTB15: case PTB16: case PTB17:
            pin_config->port = IP_PORTB;
            pin_config->gpio = IP_PTB;
            pin_config->pcc_index = PCC_PORTB_INDEX;
            break;

        case PTC0: case PTC1: case PTC2: case PTC3: case PTC4: case PTC5:
        case PTC6: case PTC7: case PTC8: case PTC9: case PTC10: case PTC11:
        case PTC12: case PTC13: case PTC14: case PTC15: case PTC16: case PTC17:
            pin_config->port = IP_PORTC;
            pin_config->gpio = IP_PTC;
            pin_config->pcc_index = PCC_PORTC_INDEX;
            break;

        case PTD0:  case PTD1:  case PTD2: case PTD3: case PTD4:  case PTD5:
        case PTD6:  case PTD7:  case PTD8: case PTD9: case PTD10: case PTD11:
        case PTD12: case PTD13: case PTD14: case PTD15: case PTD16: case PTD17:
            pin_config->port = IP_PORTD;
            pin_config->gpio = IP_PTD;
            pin_config->pcc_index = PCC_PORTD_INDEX;
            break;

        case PTE0: case PTE1: case PTE2: case PTE3: case PTE4: case PTE5:
        case PTE6: case PTE7: case PTE8: case PTE9: case PTE10: case PTE11:
        case PTE12: case PTE13: case PTE14: case PTE15: case PTE16:
            pin_config->port = IP_PORTE;
            pin_config->gpio = IP_PTE;
            pin_config->pcc_index = PCC_PORTE_INDEX;
            break;
    default:
        break;
    }
}

/**
 * @brief Initialize GPIO pin
 * 
 * @param pin_number The GPIO pin number
 */
void HAL_GPIO_Init(int pin_number)
{
    HAL_GPIO_PinConfig_t config_init;
    HAL_Pin_Set(pin_number, &config_init);

    /* Enable clock for the port */
    IP_PCC->PCCn[config_init.pcc_index] |= PCC_PCCn_CGC_MASK;
    /* Configure the pin as GPIO */
    config_init.port->PCR[config_init.pin_number] = PORT_PCR_MUX(1U);
}

/**
 * @brief Set GPIO pin as output
 * 
 * @param pin_number The GPIO pin number
 */
void HAL_GPIO_Dir(int pin_number, ARM_GPIO_DIRECTION direction)
{
    HAL_GPIO_PinConfig_t config_direction;

    switch (direction)
    {
        case ARM_GPIO_INPUT:
            HAL_Pin_Set(pin_number, &config_direction);
            config_direction.gpio->PDDR &= ~(1U << config_direction.pin_number); /* Set the pin as input */
            break;
        case ARM_GPIO_OUTPUT:
            HAL_Pin_Set(pin_number, &config_direction);
            config_direction.gpio->PDDR |= (1U << config_direction.pin_number); /* Set the pin as output */
            break;
        default:
            /* DO NOT THING */
            break;
    }
}

/**
 * @brief Set GPIO pin pull resistor
 * 
 * @param pin_number The GPIO pin number
 * @param resistor The pull resistor to set (none, pull-up, or pull-down)
 */
void HAL_GPIO_Resistor(int pin_number, ARM_GPIO_PULL_RESISTOR resistor) 
{
    HAL_GPIO_PinConfig_t config_resistor;

    switch (resistor)
    {
        case ARM_GPIO_PULL_NONE:
            HAL_Pin_Set(pin_number, &config_resistor);
            config_resistor.port->PCR[config_resistor.pin_number] &= ~PORT_PCR_PE_MASK; /* Disable pull resistor */
            break;
        case ARM_GPIO_PULL_UP:
            HAL_Pin_Set(pin_number, &config_resistor);
            config_resistor.port->PCR[config_resistor.pin_number] |= PORT_PCR_PE_MASK;  /* Enable pull resistor */
            config_resistor.port->PCR[config_resistor.pin_number] |= PORT_PCR_PS_MASK;  /* Set pull-up resistor */
            break;
        case ARM_GPIO_PULL_DOWN:
            HAL_Pin_Set(pin_number, &config_resistor);
            config_resistor.port->PCR[config_resistor.pin_number] |= PORT_PCR_PE_MASK;  /* Enable pull resistor */
            config_resistor.port->PCR[config_resistor.pin_number] &= ~PORT_PCR_PS_MASK; /* Set pull-down resistor */
            break;
        default:
            /* DO NOT THING */
            break;
    }
}

/**
 * @brief Set GPIO pin event trigger
 * 
 * @param pin_number The GPIO pin number
 * @param trigger_event The event trigger to set (none, rising edge, falling edge, or either edge)
 */
void HAL_GPIO_Trigger_Event(int pin_number, ARM_GPIO_EVENT_TRIGGER trigger_event) 
{
    // IP_PORTA->PCR[5] |= PORT_PCR_IRQC(0xA); /* PTA5: Interrupt on either edge */
    HAL_GPIO_PinConfig_t config_event;

    switch (trigger_event) 
        {
            case ARM_GPIO_TRIGGER_NONE:
                HAL_Pin_Set(pin_number, &config_event);
                config_event.port->PCR[config_event.pin_number] &= ~PORT_PCR_IRQC_MASK; /* Disable interrupt */
                
                break;
            case ARM_GPIO_TRIGGER_RISING_EDGE:
                HAL_Pin_Set(pin_number, &config_event);
                config_event.port->PCR[config_event.pin_number] |= PORT_PCR_IRQC(IRQC_INT_RISING);
                break;
            case ARM_GPIO_TRIGGER_FALLING_EDGE:
                HAL_Pin_Set(pin_number, &config_event);
                config_event.port->PCR[config_event.pin_number] |= PORT_PCR_IRQC(IRQC_INT_FALLING);
                break;
            case ARM_GPIO_TRIGGER_EITHER_EDGE:
                HAL_Pin_Set(pin_number, &config_event);
                config_event.port->PCR[config_event.pin_number] |= PORT_PCR_IRQC(IRQC_INT_EITHER);
                break;

            default:
                /* DO NOT THING */
                break;
        }
}

/**
 * @brief Set GPIO pin output level
 * 
 * @param pin_number The GPIO pin number
 * @param val The output level to set (0 or 1)
 */ 
void HAL_GPIO_Ouput_level(int pin_number, uint32_t val) 
{
    HAL_GPIO_PinConfig_t config_level;
    HAL_Pin_Set(pin_number,&config_level);

    switch (val)
    {
    case 0:
        config_level.gpio->PCOR =(1<<config_level.pin_number);
        break;
    case 1:
        config_level.gpio->PSOR =(1<<config_level.pin_number);
        break;
    default:
        /* DO NOT THING */
        break;
    }
}

/**
 * @brief Get GPIO pin input level
 * 
 * @param pin_number The GPIO pin number
 * @return uint32_t The input level of the pin (0 or 1)
 */
uint32_t HAL_GPIO_Input_level(int pin_number) 
{
    HAL_GPIO_PinConfig_t config_level;
    HAL_Pin_Set(pin_number,&config_level);
    uint32_t getInput = ((config_level.gpio->PDIR) & (1U<<config_level.pin_number));

    return (getInput != 0) ? 1U : 0U;
}