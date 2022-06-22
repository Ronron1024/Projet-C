#include "stm32l1xx_nucleo.h"
#include "main.h"

void main()
{
	initButton();
	initTIM2();
    initTIM3();
    initPWM();
    initBuzzer();
	enableInterruptButton();
	enableInterruptTIM2();
	
	Note pop_corn[29] = 
	{
		{A5, quaver}, {G5, quaver}, {A5, quaver}, {E5, quaver}, {C5, quaver}, {E5, quaver}, {A4, crotchet},
		{A5, quaver}, {G5, quaver}, {A5, quaver}, {E5, quaver}, {C5, quaver}, {E5, quaver}, {A4, crotchet},
		{A5, quaver}, {B5, quaver}, {C6, quaver}, {B5, quaver}, {C6, quaver}, {A5, quaver}, {B5, quaver}, {A5, quaver}, {B5, quaver}, {G5, quaver}, {A5, quaver}, {G5, quaver}, {A5, quaver}, {F5, quaver}, {A5, crotchet}
	};
    setSheetMusic(pop_corn, 29);
	
    while (1)
    {
		
    }
}