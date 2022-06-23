#include "stm32l1xx_nucleo.h"
#include "main.h"

Buzzer buzzer;
LedStripe ledstripe;

void main()
{
	initButton();
	enableInterruptButton();
	
	Note pop_corn[29] = 
	{
		{A5, quaver}, {G5, quaver}, {A5, quaver}, {E5, quaver}, {C5, quaver}, {E5, quaver}, {A4, crotchet},
		{A5, quaver}, {G5, quaver}, {A5, quaver}, {E5, quaver}, {C5, quaver}, {E5, quaver}, {A4, crotchet},
		{A5, quaver}, {B5, quaver}, {C6, quaver}, {B5, quaver}, {C6, quaver}, {A5, quaver}, {B5, quaver}, {A5, quaver}, {B5, quaver}, {G5, quaver}, {A5, quaver}, {G5, quaver}, {A5, quaver}, {F5, quaver}, {A5, crotchet}
	};
	
	Note jacquot[32] = 
	{
		{C5, crotchet}, {D5, crotchet}, {E5, crotchet}, {C5, crotchet}, {C5, crotchet}, {D5, crotchet}, {E5, crotchet}, {C5, crotchet},
		{E5, crotchet}, {F5, crotchet}, {G5, minim}, {E5, crotchet}, {F5, crotchet}, {G5, minim},
		{G5, quaver}, {A5, quaver}, {G5, quaver}, {F5, quaver}, {E5, crotchet}, {C5, crotchet}, {G5, quaver}, {A5, quaver}, {G5, quaver}, {F5, quaver}, {E5, crotchet}, {C5, crotchet},
		{C5, crotchet}, {G4, crotchet}, {C5, minim}, {C5, crotchet}, {G4, crotchet}, {C5, minim}
	};
	
	buzzer = InitBuzzer();
	buzzer.setSheetMusic(pop_corn, 29);
	buzzer.setSheetMusic(jacquot, 32);
	
	ledstripe = InitLedStripe();
	ledstripe.setAnim(BLINK);
	ledstripe.setLEDs(ON, 4, LED1, LED3, LED5, LED7);
	
    while (1)
    {
		
    }
}