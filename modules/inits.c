#include "stm32l1xx_nucleo.h"

void initButton()
{
	RCC->AHBENR |= 1;
	
	GPIOA->MODER &= ~(1 << 22 | 1 << 23);
	
	GPIOA->PUPDR &= ~(1 << 22 | 1 << 23);
}

void initTIM2()
{
	RCC->APB1ENR |= 1;
	
	TIM2->PSC = 15999;
	TIM2->ARR = 499;
    
    TIM2->CR1 &= ~(1 << 5 | 1 << 6);
    TIM2->CR1 &= ~(1 << 4);
	
	//TIM2->CR1 |= 1;
}

void initTIM3()
{
    RCC->APB1ENR |= 1 << 1;
    
    TIM3->PSC = 15;
    TIM3->ARR = 2271;
    
    TIM3->CR1 &= ~(1 << 5 | 1 << 6);
    TIM3->CR1 &= ~(1 << 4);
	
	//TIM3->CR1 |= 1;
}

void initPWM()
{
    TIM3->CCMR1 &= ~(1 << 9 | 1 << 8);
    
    TIM3->CCMR1 |= 1 << 13 | 1 << 14;
    TIM3->CCMR1 &= ~(1 << 12);
    
    TIM3->CCR2 = 1136;
	
	//TIM3->CCER |= 1 << 4;
}

void initBuzzer()
{
    RCC->AHBENR |= 1 << 2;
    
    GPIOC->MODER |= 1 << 15;
    GPIOC->MODER &= ~(1 << 14);
    
    GPIOC->OTYPER |= 1 << 7;
    
    GPIOC->AFR[0] |= 1 << 29;
    GPIOC->AFR[0] &= ~(1 << 28 | 1 << 30 | 1 << 31);
}