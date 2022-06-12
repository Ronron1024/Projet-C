#include "stm32l1xx_nucleo.h"
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

void EXTI15_10_IRQHandler()
{
	if (EXTI->PR & (1 << 11))
	{
		EXTI->PR |= 1 << 11;
		toggleBuzzer();
	}
}

extern Note playing;
void TIM2_IRQHandler()
{
	TIM2->SR &= ~1;
	playing++;
	playing %= 11;
	tone(playing);
}