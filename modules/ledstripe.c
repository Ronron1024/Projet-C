#include <stdio.h>
#include <stdarg.h>
#include "../includes/ledstripe.h"
#include "../includes/prototypes.h"

uint8_t LEDs_state[LED_NBR] = {OFF};
uint8_t LEDs_position[LED_NBR] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8};
uint8_t animation_length = 0;
uint8_t animation_cursor = 0;
uint8_t animation_frames[ANIMATION_MAX_FRAME_NBR][LED_NBR] = {OFF};

void setLED(uint8_t state, uint8_t led)
{
    // Set bit number "led" to "state" in GPIOB Output Data Register
    if (state)
        setBitTo1(&GPIOB->ODR, sizeof(GPIOB->ODR), led);
    else
        setBitTo0(&GPIOB->ODR, sizeof(GPIOB->ODR), led);
}

// set n LEDs to "state"
void setLEDs(uint8_t state, uint8_t n, ...)
{
    va_list valist;
    va_start(valist, n);
    
    for (uint8_t i = 0; i < n; i++)
        setLED(state, va_arg(valist, int));
      
    va_end(valist);
}

void animNextFrame()
{	
	animation_cursor++;
	animation_cursor %= animation_length;
	
	for (uint8_t i = 0; i < LED_NBR; i++)
		LEDs_state[i] = animation_frames[animation_cursor][i];
}

void setAnim(Animation anim)
{
	switch (anim)
	{
		case K2000:
			animation_length = LED_NBR;
			
			for (uint8_t i = 0; i < LED_NBR; i++)
			{
				for (uint8_t j = 0; j < LED_NBR; j++)
					animation_frames[i][j] = j == i ? ON : OFF;
			}
			
			break;
			
		case BLINK:
			animation_length = 2;
			
			for (uint8_t i = 0; i < LED_NBR; i++)
				animation_frames[0][i] = ON;
			
			for (uint8_t i = 0; i < LED_NBR; i++)
				animation_frames[1][i] = OFF;
			
			break;
	}
	
	animation_cursor = 0;
}

void toggleAnim()
{
	if (TIM4->CR1 & 1)
		TIM4->CR1 &= ~1;
	else
		TIM4->CR1 |= 1;
}

LedStripe InitLedStripe()
{
	initLEDs(8, LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8);
	setLEDs(OFF, 8, LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8);
	initTIM4();
	enableInterruptTIM4();
	
	LedStripe ledstripe;
	ledstripe.setLED = setLED;
	ledstripe.setLEDs = setLEDs;
	ledstripe.setAnim = setAnim;
	ledstripe.toggleAnim = toggleAnim;
	
	return ledstripe;
};