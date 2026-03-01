#ifndef DRIVER_GPIO_H_
#define DRIVER_GPIO_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "driver_common.h"
#include <S32K144.h>

typedef enum {
    PTA0=79,
    PTA1=78,
    PTA2=73,
    PTA3=72,
    PTA4=98,
    PTA5=97,
    PTA6=58,
    PTA7=57,
    PTA8=100,
    PTA9=99,
    PTA10=92,
    PTA11=91,
    PTA12=90,
    PTA13=89,
    PTA14=88,
    PTA15=83,
    PTA16=82,
    PTA17=62,
} PORTA_Pin_t;

typedef enum {
    PTB0=54,
    PTB1=53,
    PTB2=48,
    PTB3=47,
    PTB4=28,
    PTB5=27,
    PTB6=16,
    PTB7=15,
    PTB8=77,
    PTB9=76,
    PTB10=75,
    PTB11=74,
    PTB12=68,
    PTB13=67,
    PTB14=66,
    PTB15=65,
    PTB16=64,
    PTB17=63,
} PORTB_Pin_t;

typedef enum {
    PTC0=40,
    PTC1=39,
    PTC2=30,
    PTC3=29,
    PTC4=96,
    PTC5=95,
    PTC6=81,
    PTC7=80,
    PTC8=56,
    PTC9=55,
    PTC10=52,
    PTC11=51,
    PTC12=50,
    PTC13=49,
    PTC14=46,
    PTC15=45,
    PTC16=44,
    PTC17=43,
} PORTC_Pin_t;

typedef enum {
    PTD0=4,
    PTD1=3,
    PTD2=71,
    PTD3=70,
    PTD4=69,
    PTD5=33,
    PTD6=32,
    PTD7=31,
    PTD8=42,
    PTD9=41,
    PTD10=36,
    PTD11=35,
    PTD12=34,
    PTD13=25,
    PTD14=24,
    PTD15=22,
    PTD16=21,
    PTD17=20,
} PORTD_Pin_t;

typedef enum {
    PTE0=94,
    PTE1=93,
    PTE2=85,
    PTE3=18,
    PTE4=9,
    PTE5=8,
    PTE6=84,
    PTE7=59,
    PTE8=26,
    PTE9=23,
    PTE10=6,
    PTE11=5,
    PTE12=19,
    PTE13=7,
    PTE14=17,
    PTE15=2,
    PTE16=1,
} PORTE_Pin_t;

/**
\brief GPIO Pin
*/
typedef uint32_t ARM_GPIO_Pin_t;

/**
\brief GPIO Direction
*/
typedef enum {
  ARM_GPIO_INPUT,                       ///< Input (default)
  ARM_GPIO_OUTPUT                       ///< Output
} ARM_GPIO_DIRECTION;

/**
\brief GPIO Output Mode
*/
typedef enum {
  ARM_GPIO_PUSH_PULL,                   ///< Push-pull (default)
  ARM_GPIO_OPEN_DRAIN                   ///< Open-drain
} ARM_GPIO_OUTPUT_MODE;

/**
\brief GPIO Pull Resistor
*/
typedef enum {
  ARM_GPIO_PULL_NONE,                   ///< None (default)
  ARM_GPIO_PULL_UP,                     ///< Pull-up
  ARM_GPIO_PULL_DOWN                    ///< Pull-down
} ARM_GPIO_PULL_RESISTOR;

/**
\brief GPIO Event Trigger
*/
typedef enum {
  ARM_GPIO_TRIGGER_NONE,                ///< None (default)
  ARM_GPIO_TRIGGER_RISING_EDGE,         ///< Rising-edge
  ARM_GPIO_TRIGGER_FALLING_EDGE,        ///< Falling-edge
  ARM_GPIO_TRIGGER_EITHER_EDGE          ///< Either edge (rising and falling)
} ARM_GPIO_EVENT_TRIGGER;

/****** GPIO Event *****/
#define ARM_GPIO_EVENT_RISING_EDGE      (1UL << 0)  ///< Rising-edge detected
#define ARM_GPIO_EVENT_FALLING_EDGE     (1UL << 1)  ///< Falling-edge detected
#define ARM_GPIO_EVENT_EITHER_EDGE      (1UL << 2)  ///< Either edge detected (only when hardware cannot distinguish between rising and falling edge)


/****** GPIO specific error codes *****/
#define ARM_GPIO_ERROR_PIN              (ARM_DRIVER_ERROR_SPECIFIC - 1) ///< Specified Pin not available


// Function documentation
/**
  \fn          int32_t ARM_GPIO_Setup (ARM_GPIO_Pin_t pin, ARM_GPIO_SignalEvent_t cb_event)
  \brief       Setup GPIO Interface.
  \param[in]   pin  GPIO Pin
  \param[in]   cb_event  Pointer to \ref ARM_GPIO_SignalEvent
  \return      \ref execution_status

  \fn          int32_t ARM_GPIO_SetDirection (ARM_GPIO_Pin_t pin, ARM_GPIO_DIRECTION direction)
  \brief       Set GPIO Direction.
  \param[in]   pin  GPIO Pin
  \param[in]   direction  \ref ARM_GPIO_DIRECTION
  \return      \ref execution_status

  \fn          int32_t ARM_GPIO_SetOutputMode (ARM_GPIO_Pin_t pin, ARM_GPIO_OUTPUT_MODE mode)
  \brief       Set GPIO Output Mode.
  \param[in]   pin  GPIO Pin
  \param[in]   mode  \ref ARM_GPIO_OUTPUT_MODE
  \return      \ref execution_status

  \fn          int32_t ARM_GPIO_SetPullResistor (ARM_GPIO_Pin_t pin, ARM_GPIO_PULL_RESISTOR resistor)
  \brief       Set GPIO Pull Resistor.
  \param[in]   pin  GPIO Pin
  \param[in]   resistor  \ref ARM_GPIO_PULL_RESISTOR
  \return      \ref execution_status

  \fn          int32_t ARM_GPIO_SetEventTrigger (ARM_GPIO_Pin_t pin, ARM_GPIO_EVENT_TRIGGER trigger)
  \brief       Set GPIO Event Trigger.
  \param[in]   pin  GPIO Pin
  \param[in]   trigger  \ref ARM_GPIO_EVENT_TRIGGER
  \return      \ref execution_status

  \fn          void ARM_GPIO_SetOutput (ARM_GPIO_Pin_t pin, uint32_t val)
  \brief       Set GPIO Output Level.
  \param[in]   pin  GPIO Pin
  \param[in]   val  GPIO Pin Level (0 or 1)

  \fn          uint32_t ARM_GPIO_GetInput (ARM_GPIO_Pin_t pin)
  \brief       Get GPIO Input Level.
  \param[in]   pin  GPIO Pin
  \return      GPIO Pin Level (0 or 1)

  \fn          void ARM_GPIO_SignalEvent (ARM_GPIO_Pin_t pin, uint32_t event)
  \brief       Signal GPIO Events.
  \param[in]   pin    GPIO Pin on which event occurred
  \param[in]   event  \ref GPIO_events notification mask
*/

typedef void (*ARM_GPIO_SignalEvent_t) (ARM_GPIO_Pin_t pin, uint32_t event);  /* Pointer to \ref ARM_GPIO_SignalEvent : Signal GPIO Event */


/**
\brief Access structure of the GPIO Driver.
*/
typedef struct _ARM_DRIVER_GPIO {
  int32_t  (*Setup)           (ARM_GPIO_Pin_t pin, ARM_GPIO_SignalEvent_t cb_event); ///< Pointer to \ref ARM_GPIO_Setup : Setup GPIO Interface.
  int32_t  (*SetDirection)    (ARM_GPIO_Pin_t pin, ARM_GPIO_DIRECTION direction);    ///< Pointer to \ref ARM_GPIO_SetDirection : Set GPIO Direction.
  int32_t  (*SetOutputMode)   (ARM_GPIO_Pin_t pin, ARM_GPIO_OUTPUT_MODE mode);       ///< Pointer to \ref ARM_GPIO_SetOutputMode : Set GPIO Output Mode.
  int32_t  (*SetPullResistor) (ARM_GPIO_Pin_t pin, ARM_GPIO_PULL_RESISTOR resistor); ///< Pointer to \ref ARM_GPIO_SetPullResistor : Set GPIO Pull Resistor.
  int32_t  (*SetEventTrigger) (ARM_GPIO_Pin_t pin, ARM_GPIO_EVENT_TRIGGER trigger);  ///< Pointer to \ref ARM_GPIO_SetEventTrigger : Set GPIO Event Trigger.
  void     (*SetOutput)       (ARM_GPIO_Pin_t pin, uint32_t val);                    ///< Pointer to \ref ARM_GPIO_SetOutput : Set GPIO Output Level.
  uint32_t (*GetInput)        (ARM_GPIO_Pin_t pin);                                  ///< Pointer to \ref ARM_GPIO_GetInput : Get GPIO Input Level.
} const ARM_DRIVER_GPIO;

#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_GPIO_H_ */