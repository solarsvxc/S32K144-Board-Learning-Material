#include <driver_gpio.h>
#include <HAL_gpio.h>

// Pin mapping
#define GPIO_MAX_PINS           100U
#define PIN_IS_AVAILABLE(n)     ((n) < GPIO_MAX_PINS)

static ARM_GPIO_SignalEvent_t GPIO_Callback_Table[GPIO_MAX_PINS] = {NULL};

/**
 * @brief  Setup GPIO Interface.
 * 
 * @param pin The GPIO pin number
 * @param cb_event Pointer to the callback function for GPIO events
 * @return int32_t Status of the operation
 */ 
static int32_t GPIO_Setup (ARM_GPIO_Pin_t pin, ARM_GPIO_SignalEvent_t cb_event) 
{
    int32_t result = ARM_DRIVER_OK;

    if (PIN_IS_AVAILABLE(pin)) 
    {
        HAL_GPIO_Init(pin);
        /* Test */
        GPIO_Callback_Table[pin] = cb_event;
        /* Test */
        cb_event(pin,1); 
    } else {
        result = ARM_GPIO_ERROR_PIN;
    }
    return result;
}

/**
 * @brief  Set GPIO Direction.
 * 
 * @param pin The GPIO pin number
 * @param direction The direction to set (input or output)
 * @return int32_t Status of the operation
 */
static int32_t GPIO_SetDirection (ARM_GPIO_Pin_t pin, ARM_GPIO_DIRECTION direction) 
{
    int32_t result = ARM_DRIVER_OK;

    if (PIN_IS_AVAILABLE(pin)) 
    {
    switch (direction) 
    {
        case ARM_GPIO_INPUT:
            HAL_GPIO_Dir(pin, ARM_GPIO_INPUT);
            break;
        case ARM_GPIO_OUTPUT:
            HAL_GPIO_Dir(pin, ARM_GPIO_OUTPUT);
            break;
        default:
            result = ARM_DRIVER_ERROR_PARAMETER;
            break;
    }
    } else {
        result = ARM_GPIO_ERROR_PIN;
    }
    return result;
}

/**
 * @brief  Set GPIO Output Mode.
 * 
 * @param pin The GPIO pin number
 * @param mode The output mode to set (push-pull or open-drain)
 * @return int32_t Status of the operation
 */
static int32_t GPIO_SetOutputMode (ARM_GPIO_Pin_t pin, ARM_GPIO_OUTPUT_MODE mode) 
{
    int32_t result = ARM_DRIVER_OK;

    if (PIN_IS_AVAILABLE(pin)) 
    {
    switch (mode) {
        case ARM_GPIO_PUSH_PULL:
            break;
        case ARM_GPIO_OPEN_DRAIN:
            break;
        default:
            result = ARM_DRIVER_ERROR_PARAMETER;
            break;
    }
    } else {
        result = ARM_GPIO_ERROR_PIN;
    }
    return result;
}

/**
 * @brief  Set GPIO Pull Resistor.
 * 
 * @param pin The GPIO pin number
 * @param resistor The pull resistor to set (none, pull-up, or pull-down)
 * @return int32_t Status of the operation
 */
static int32_t GPIO_SetPullResistor (ARM_GPIO_Pin_t pin, ARM_GPIO_PULL_RESISTOR resistor) 
{
    int32_t result = ARM_DRIVER_OK;

    if (PIN_IS_AVAILABLE(pin)) 
    {
        switch (resistor) 
        {
            case ARM_GPIO_PULL_NONE:
                HAL_GPIO_Resistor(pin,ARM_GPIO_PULL_NONE);
                break;
                case ARM_GPIO_PULL_UP:
                HAL_GPIO_Resistor(pin,ARM_GPIO_PULL_UP);
                break;
            case ARM_GPIO_PULL_DOWN:
                HAL_GPIO_Resistor(pin,ARM_GPIO_PULL_DOWN);
                break;
            default:
                result = ARM_DRIVER_ERROR_PARAMETER;
                break;
        }
    } else {
        result = ARM_GPIO_ERROR_PIN;
    }

    return result;
}

/**
 * @brief  Set GPIO Event Trigger.
 * 
 * @param pin The GPIO pin number
 * @param trigger The event trigger to set (none, rising edge, falling edge, or either edge)
 * @return int32_t Status of the operation
 */
static int32_t GPIO_SetEventTrigger (ARM_GPIO_Pin_t pin, ARM_GPIO_EVENT_TRIGGER trigger) {
    int32_t result = ARM_DRIVER_OK;

    if (PIN_IS_AVAILABLE(pin)) 
    {
        switch (trigger) 
        {
            case ARM_GPIO_TRIGGER_NONE:
                break;
            case ARM_GPIO_TRIGGER_RISING_EDGE:
                break;
            case ARM_GPIO_TRIGGER_FALLING_EDGE:
                break;
            case ARM_GPIO_TRIGGER_EITHER_EDGE:
                break;
            default:
                result = ARM_DRIVER_ERROR_PARAMETER;
                break;
        }
    } else {
        result = ARM_GPIO_ERROR_PIN;
    }

    return result;
}

/**
 * @brief  Set GPIO Output Level.
 * 
 * @param pin The GPIO pin number
 * @param val The output value to set (0 or 1)
 */
static void GPIO_SetOutput (ARM_GPIO_Pin_t pin, uint32_t val) {

    if (PIN_IS_AVAILABLE(pin)) {
        HAL_GPIO_Ouput_level(pin, val);
    } else {
        /* DO NOT THING */
    }
}

/**
 * @brief  Get GPIO Input Level.
 * 
 * @param pin The GPIO pin number
 * @return uint32_t The input value (0 or 1)
 */
static uint32_t GPIO_GetInput (ARM_GPIO_Pin_t pin) 
{
    uint32_t val = 0U;

    if (PIN_IS_AVAILABLE(pin)) 
    {
        val = HAL_GPIO_Input_level(pin);
    } else
    {
        /* DO NOT THING*/
    }

    return val;
}

/**
 * @brief GPIO Driver access structure
 * 
 */
ARM_DRIVER_GPIO Driver_GPIO0 = {
    GPIO_Setup,
    GPIO_SetDirection,
    GPIO_SetOutputMode,
    GPIO_SetPullResistor,
    GPIO_SetEventTrigger,
    GPIO_SetOutput,
    GPIO_GetInput
};
