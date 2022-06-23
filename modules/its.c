#include "stm32l1xx_nucleo.h"
#include "../includes/buzzer.h"
#include "../includes/ledstripe.h"
#include "../includes/prototypes.h"

void enableInterruptButton()
{
	RCC->APB2ENR |= 1;
	
	NVIC->ISER[1] |= 1 << 8;
	
	EXTI->IMR |= 1 << 11;
	
	EXTI->FTSR |= 1 << 11;
	
	SYSCFG->EXTICR[2] &= ~(1 << 12 | 1 << 13 | 1 << 14 | 1 << 15);
}

void enableInterruptTIM2()
{
	NVIC->ISER[0] |= 1 << 28;
	TIM2->DIER |= 1;
}

void enableInterruptTIM4()
{
	NVIC->ISER[0] |= 1 << 30;
	TIM4->DIER |= 1;
}

extern Buzzer buzzer;
extern LedStripe ledstripe;
void EXTI15_10_IRQHandler()
{
	if (EXTI->PR & (1 << 11))
	{
		EXTI->PR |= 1 << 11;
		buzzer.toggleBuzzer();
		//ledstripe.toggleAnim();
	}
}

extern uint8_t music_sheet_cursor;
extern Note* music_sheet;
extern uint8_t music_sheet_length;
void TIM2_IRQHandler()
{
	TIM2->SR &= ~1;
	music_sheet_cursor++;
	music_sheet_cursor %= music_sheet_length;
	tone(music_sheet[music_sheet_cursor]);
}

extern uint8_t LEDs_state[LED_NBR];
extern uint8_t LEDs_position[LED_NBR];
void TIM4_IRQHandler()
{
	TIM4->SR &= ~1;
	
	for (uint8_t i = 0; i < LED_NBR; i++)
		ledstripe.setLED(LEDs_state[i], LEDs_position[i]);
	animNextFrame();
}