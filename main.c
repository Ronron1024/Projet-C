#include "main.h"

BTN button1;
BTN button2;
BTN button3;
BTN button4;

void init_ADC(void){
	
	//activation de l' horloge sur le periphérique ADC sur bus APB2
	RCC->APB2ENR |= (1<<9);
	
	RCC->CR |= (1<<0);  //HSI clock enable ==> 16MHz ?
	
	ADC->CCR &= ~(1<<16); //prescaler set 0x00  => HSI divided by 1?  //Echantillonage // Temps de conversion 
	ADC->CCR &= ~(1<<17);
	
	//ADC1->CR1 |= 1 << 24 | 1 << 25; // 6 bits resolution
	ADC1->CR1 &= ~(1 << 24) & ~(1 << 25); // 12 bits resolution
	
	//Lien avec GPIO -> ADC
	//RI->ASCR1 |= (1<<0); // Close switch to ADC: A0 =>  ADC1_IN0  //RV2
	RI->ASCR1 |= (1<<1); // Close switch to ADC: A1 =>  ADC_IN1
	
	//ADC1->SQR1 &= ~(1 << 24 | 1 << 23 | 1 << 22 | 1 << 21 | 1 << 20); // Canal choice, 1 conversion (p. 301)
	ADC1->SQR1 &= ~(1 << 24 | 1 << 23 | 1 << 22 | 1 << 21 | 1 << 20); // Canal choice, 1 conversion (p. 301)
	
	//ADC1->SQR5 &= ~(1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4); //  A0 //RV2
	ADC1->SQR5 |= (1<<0);
	ADC1->SQR5 &= ~ ((1<<1)|(1<<2)|(1<<3)|(1<<4));  
	
	ADC1->CR2 |= 1 << 1; // Continuous conversion mode
	
}


DISPLAYLCD DisplayLcd;

Buzzer buzzer;
extern uint8_t LEDs_position[LED_NBR];
LedStripe ledstripe;

int choice = 0;
extern Note pop_corn[29];
extern int pop_corn_digit[29];
extern Note jacquot[32];
extern int jacquot_digit[32];
extern Note moonlight[11];
extern int moonlight_digit[11];
int length = 29;
Note* musicSheet = pop_corn;
int* music_digit = pop_corn_digit;
Note one_note[1];
int cursor=0 ;

int main(void)
{
	initLCD(&DisplayLcd);         //Init structure & config
	//init_ADC();
	initButtons(&button1, &button2, &button3, &button4); //Init structure
	enable_interrupt_ext_buttons();                      //Init interruption ext button;
	
	buzzer = InitBuzzer();
	//buzzer.setSheetMusic(pop_corn, 32);
	
	ledstripe = InitLedStripe();
	ledstripe.setAnim(K2000);
	
	statusLCD(&DisplayLcd,ON);    //ON ou OFF LCD
	IntensityLCD(&DisplayLcd,0);  //Between 0 to 15
	
	//uint8_t rondBas;
	//uint8_t rondHaut;
	//uint8_t empty;
	
	//createDigit(&rondBas,4, M1, M0,L0,R0);  //=> define.h
	//createDigit(&rondHaut,4, M1, M2,L1,R1);
	//createDigit(&empty,0);
	
	//printfDigit(&DisplayLcd,"ABCDEFGHIJKLMNOPQRSTUWXYZ!. 0123456789", NORMAL);
	//printfDigit(&DisplayLcd,"01234", NORMAL);
	//blinkingLCD(&DisplayLcd, FAST);
	//eraseLCD(&DisplayLcd);
	
	//Note note = {A5, crotchet};
	//playNote(note);
	
	/* Infinite loop */
	
	uint8_t life = 4;
	uint8_t note_to_play = 3;
	int game = 1;
	int has_demo = 0;
	
	//ADC enable On active le CAN
	/*ADC1->CR2 |= (1<<0);
	
	while( (ADC1->SR & ADC_FLAG_ADONS) == 0 ); //Pas de début de conversion
	
	ADC1->CR2 |= (1<<30);       //Start conversion SWSTART
	
	while( (ADC1->SR & ADC_FLAG_EOC) == 0 ); //Fin de conversion
	
	while(!choice){
		if(ADC1->DR < 1365 ){
			
			musicSheet = pop_corn ;
			music_digit = pop_corn_digit;
			length = 29;
			
			printfDigit(&DisplayLcd,"1- POP CORN ", NORMAL);
		}
		
		if(ADC1->DR > 1365 && ADC1->DR < 2730)  {
			
			musicSheet = jacquot ;
			music_digit = jacquot_digit;
			length = 32;
			printfDigit(&DisplayLcd,"2- JACQUOT ", NORMAL);
		}
		
		if(ADC1->DR > 2730){
			
			musicSheet = moonlight ;
			music_digit = moonlight_digit;
			length = 11;
			printfDigit(&DisplayLcd,"3- MOONLIGHT ", NORMAL);
			
		}
	}*/
	
	demo(length, musicSheet);
	
	while (1)
	{		
		while(game && !buzzer.is_playing)
		{
			
			if (!has_demo)
			{
				demo(note_to_play, musicSheet);
				has_demo = 1;
				continue; // Cannot play during demo
			}
			
			if(button1.status == 1)
			{
				one_note[0] = musicSheet[cursor];
				buzzer.setSheetMusic(one_note ,1);
				buzzer.toggleBuzzer();
				buzzer.is_playing = 1;
				if ( music_digit[cursor] == 1 )
				{        
					cursor++;
				}
				else 
				{          
					life--;          
				}
			}
			
			if(button2.status == 1){
				one_note[0] = musicSheet[cursor];
				buzzer.setSheetMusic(one_note ,1);
				buzzer.toggleBuzzer();
				buzzer.is_playing = 1;
				if ( music_digit[cursor] == 2 )
				{
					cursor++;       
				}
				else 
				{
					life--;
				}
			}
			
			if(button3.status == 1)
			{
				one_note[0] = musicSheet[cursor];
				buzzer.setSheetMusic(one_note ,1);
				buzzer.toggleBuzzer();
				buzzer.is_playing = 1;
				if ( music_digit[cursor] == 3 )
				{
					cursor++;       
				}
				else 
				{
					//life--;
				}
				button3.status = 0;
			}
			
			if(button4.status == 1){
				one_note[0] = musicSheet[cursor];
				buzzer.setSheetMusic(one_note ,1);
				buzzer.toggleBuzzer();
				buzzer.is_playing = 1;
				if ( music_digit[cursor] == 4 )
				{
					cursor++;       
				}
				else 
				{
					life--;
				}
				button4.status = 0;
			}
			
			// Display health bar
			for (uint8_t i = 0; i < LED_NBR; i++)
			{
				if (i < life * 2)
					ledstripe.setLED(ON, LEDs_position[i]);
				else
					ledstripe.setLED(OFF, LEDs_position[i]);
			}
			
			if (life == 0)
			{
				game = 0;
				break; // End game, lose
			}
			
			if (cursor == length)
			{
				game = 0;
				break; // End game, win
			}
			
			if (cursor == note_to_play)
			{
				note_to_play++;
				cursor = 0;
				has_demo = 0;
				break; // Next turn
			}
		}
		
		if (!game)
		{
			if (!life)
			{
				printfDigit(&DisplayLcd,"YOU LOSE !", NORMAL);
				blinkingLCD(&DisplayLcd, FAST);
			}
			else
			{
				printfDigit(&DisplayLcd,"YOU WIN !", NORMAL);
				blinkingLCD(&DisplayLcd, FAST);
			}
		}
		
	} // game while
} // µC while
