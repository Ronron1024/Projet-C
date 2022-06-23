#ifndef LEDSTRIPE_H_INCLUDED
#define LEDSTRIPE_H_INCLUDED

#include "stm32l1xx_nucleo.h"

#define ON 1
#define OFF 0

#define ANIMATION_MAX_FRAME_NBR 16
#define LED_NBR 8

// LEDs (bits position)
#define LED1 1
#define LED2 2
#define LED3 10
#define LED4 11
#define LED5 12
#define LED6 13
#define LED7 14
#define LED8 15

typedef enum Animation
{
	K2000, BLINK
} Animation;

typedef struct LedStripe
{
	void (*setLED)(uint8_t LED_state, uint8_t LED_position);
	void (*setLEDs)(uint8_t LED_state, uint8_t LED_number, ...);
	void (*setAnim)(Animation anim);
	void (*toggleAnim)();
} LedStripe;

#endif