#include "stm32l1xx_nucleo.h"
#include "includes/prototypes.h"

void main()
{
	initButton();
	initTIM2();
    initTIM3();
    initPWM();
    initBuzzer();
	enableInterruptButton();
	enableInterruptTIM2();
	
    while (1)
    {
        
    }
}