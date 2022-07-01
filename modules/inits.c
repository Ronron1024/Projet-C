#include <stdio.h>
#include <stdarg.h>
#include "stm32l1xx_nucleo.h"

// Used to set the bit n to 1 in reg
void setBitTo1(volatile void* reg, size_t reg_size, uint8_t n)
{
    if (reg_size == sizeof(uint16_t))
        *(uint16_t*) reg |= 1 << n;
    else if (reg_size == sizeof(uint32_t))
        *(uint32_t*) reg |= 1 << n;
}

// Variable arguments function, set n bit to 1 in reg
void setBitsTo1(volatile void* reg, size_t reg_size, uint8_t n, ...)
{
    va_list valist;
    va_start(valist, n);
    
    for (uint8_t i = 0; i < n; i++)
        setBitTo1(reg, reg_size, va_arg(valist, int));
    
    va_end(valist);
}

// Used to set the bit n to 0 in reg
void setBitTo0(volatile void* reg, size_t reg_size, uint8_t n, ...)
{
    if (reg_size == sizeof(uint16_t))
        *(uint16_t*) reg &= ~(1 << n);
    else if (reg_size == sizeof(uint16_t))
        *(uint16_t*) reg &= ~(1 << n);
}

// Variable arguments function, set n bit to 0 in reg
void setBitsTo0(volatile void* reg, size_t reg_size, uint8_t n, ...)
{
    va_list valist;
    va_start(valist, n);
    
    for (uint8_t i = 0; i < n; i++)
        setBitTo0(reg, reg_size, va_arg(valist, int));
    
    va_end(valist);
}

// Init n LEDs
void initLEDs(uint8_t n, ...)
{
    va_list valist;
    va_start(valist, n);
  
    setBitTo1(&RCC->AHBENR, sizeof(RCC->AHBENR), 1); // Enable clock for Port B
    
    uint8_t led = 0;
    for (uint8_t i = 0; i < n; i++)
    {
        led = va_arg(valist, int);
        
        // Set LED to General purpose output mode : 0b01
        setBitTo1(&GPIOB->MODER, sizeof(GPIOB->MODER), 2*led);
        setBitTo0(&GPIOB->MODER, sizeof(GPIOB->MODER), 2*led+1);
        
        // Set LED to push-pull : 0
        setBitTo0(&GPIOB->OTYPER, sizeof(GPIOB->OTYPER), led);
    }
    
    va_end(valist);
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

void initTIM4()
{
	RCC->APB1ENR |= 1 << 2;
	
	TIM4->PSC = 15999;
	
	// Configure counter mode
    TIM4->CR1 &= ~(1 << 4 | 1 << 5 | 1 << 6); // DIR up, CMS 0b00
    
    // Configure start value
    TIM4->ARR = 99; // + 1 (count from 0) FCK = 2Hz
    
    TIM4->CR1 |= 1 << 7; // ARR buffered
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