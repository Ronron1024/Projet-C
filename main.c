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

int testButton1(void);
int testButton2(void);
int testButton3(void);
int testButton4(void);
void diseable_interrupt_ext(void);

int testButton1(){
	
	if(button1.status == 1  && Delay(300000) == 0 )
		return 1;
	else
		return 0;
	
}

int testButton2(){
	
	if(button2.status == 1  && Delay(300000) == 0)
		return 1;
	else
		return 0;
	
}

int testButton3(){
	
	if(button3.status == 1  && Delay(300000) == 0 && button4.status == 0)
		return 1;
	else
		return 0;
	
}

int testButton4(){
	
	if(button4.status == 1  && Delay(300000) == 0 && button3.status == 0)
		return 1;
	else
		return 0;
	
}


void diseable_interrupt_ext(void){
  
  EXTI->IMR &= ~(1<<11);    
  EXTI->IMR &= ~(1<<12);    
  EXTI->IMR &= ~(1<<6);    
  EXTI->IMR &= ~(1<<5);    
                             
  button1.status = 0;
  button2.status = 0;
  button3.status = 0;
  button4.status = 0;

}




DISPLAYLCD DisplayLcd;

Buzzer buzzer;
extern uint8_t LEDs_position[LED_NBR];
LedStripe ledstripe;

int choice = 0;
extern Note demo_song[6];
extern int demo_song_digit[6];
extern Note pop_corn[29];
extern int pop_corn_digit[29];
extern Note jacquot[32];
extern int jacquot_digit[32];
int length = 0;
Note* musicSheet = 0;
int* music_digit = 0;
Note one_note[1];
int cursor=0 ;

int main(void)
{
	initLCD(&DisplayLcd);         //Init structure & config
	init_ADC();
	initButtons(&button1, &button2, &button3, &button4); //Init structure
	enable_interrupt_ext_buttons();                      //Init interruption ext button;
	
	buzzer = InitBuzzer();
	//buzzer.setSheetMusic(pop_corn, 32);
	
	ledstripe = InitLedStripe();
        ledstripe.setAnim(BLINK);
	//ledstripe.setAnim(K2000);
	
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
	ADC1->CR2 |= (1<<0);
	
	while( (ADC1->SR & ADC_FLAG_ADONS) == 0 ); //Pas de début de conversion
	
	ADC1->CR2 |= (1<<30);       //Start conversion SWSTART
	
	while( (ADC1->SR & ADC_FLAG_EOC) == 0 ); //Fin de conversion
	
	while(!choice){
		
		
		if(ADC1->DR >= 1365 && ADC1->DR < 2730)  {
			musicSheet = pop_corn ;
			music_digit = pop_corn_digit;
			length = 29;
			
			printDigit(&DisplayLcd, 1, 'C');
			printDigit(&DisplayLcd, 2, 'O');
			printDigit(&DisplayLcd, 3, 'R');
			printDigit(&DisplayLcd, 4, 'N');
			
		}
		
		if(ADC1->DR < 1365){
			
			musicSheet = demo_song ;
			music_digit = demo_song_digit;
			length = 6;

			printDigit(&DisplayLcd, 1, 'D');
			printDigit(&DisplayLcd, 2, 'E');
			printDigit(&DisplayLcd, 3, 'M');
			printDigit(&DisplayLcd, 4, 'O');
                        
		}
		
		if (ADC1->DR >= 2730)
		{
			musicSheet = jacquot;
			music_digit = jacquot_digit;
			length = 32;
			
			printDigit(&DisplayLcd, 1, 'J');
			printDigit(&DisplayLcd, 2, 'A');
			printDigit(&DisplayLcd, 3, 'C');
			printDigit(&DisplayLcd, 4, 'Q');
		}
	}
        
        diseable_interrupt_ext();
	
	eraseLCD(&DisplayLcd);
	Delay(200000);
	
	printDigit(&DisplayLcd, 1, 'D');
	printDigit(&DisplayLcd, 2, 'E');
	printDigit(&DisplayLcd, 3, 'M');
	printDigit(&DisplayLcd, 4, 'O');
        
        eraseLCD(&DisplayLcd);
	Delay(200000);
	
	demo(length, musicSheet);
	
	while (1)
	{		
          
          
             if (!game)
		{
			if (!life)
			{
                          
                                IntensityLCD(&DisplayLcd,0);  //Between 0 to 15
                                
                                eraseLCD(&DisplayLcd);

				printfDigit(&DisplayLcd,"LOSE", NORMAL);
			}
			else
			{

                                eraseLCD(&DisplayLcd);
                      printDigit(&DisplayLcd, 1, 'W');
                      printDigit(&DisplayLcd, 2, 'I');
                      printDigit(&DisplayLcd, 3, 'N');
				blinkingLCD(&DisplayLcd, FAST);
			}
		}
          
          
		while(game && !buzzer.is_playing)
		{
			
			
		IntensityLCD(&DisplayLcd,0);

                        
    		
			if (!has_demo)
                
			{
                          
                          diseable_interrupt_ext();
                          
				eraseLCD(&DisplayLcd);
                                ;
				Delay(100000);
				printDigit(&DisplayLcd, 1, 'G');
				printDigit(&DisplayLcd, 2, 'O');
				printDigit(&DisplayLcd, 3, '!');
                            
				Delay(1000000);
                                eraseLCD(&DisplayLcd);
                                Delay(1000000);
						
				demo(note_to_play, musicSheet);
				has_demo = 1;
				continue; // Cannot play during demo
			}
			
                        
                        enable_interrupt_ext_buttons();
                        
                        
			//if(button1.status == 1 )
			if( testButton1() == 1 && testButton2() == 0 && testButton3() == 0 && testButton4() == 0)
			{
				one_note[0] = musicSheet[cursor];
                                one_note[0].duration = quaver;
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
                                       
                                        ledstripe.toggleAnim();
                                        Delay(1000000);
                                        ledstripe.toggleAnim();
				}
                                
                                
                                //button2.status = 0;
                                //button3.status = 0;
                                //button4.status = 0;
                                
                                eraseLCD(&DisplayLcd);
			}
			
			//if(button2.status == 1){
			if( testButton1() == 0 && testButton2() == 1 && testButton3() == 0 && testButton4() == 0)
			{
				
				one_note[0] = musicSheet[cursor];
                                one_note[0].duration = quaver;
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
                                       
                                        ledstripe.toggleAnim();
                                        Delay(1000000);
                                        ledstripe.toggleAnim();
				}
                                
                                //button1.status = 0;
                                //button3.status = 0;
                                //button4.status = 0;
                                
                                eraseLCD(&DisplayLcd);
			}
			
			//if(button3.status == 1  && Delay(300000) == 0)
			if( testButton1() == 0 && testButton2() == 0 && testButton3() == 1 && testButton4() == 0 )
			{
				
				one_note[0] = musicSheet[cursor];
                                one_note[0].duration = quaver;
				buzzer.setSheetMusic(one_note ,1);
				buzzer.toggleBuzzer();
				buzzer.is_playing = 1;
				if ( music_digit[cursor] == 3 )
				{
					cursor++;       
				}
				else 
				{
					life--;
                                       
                                        ledstripe.toggleAnim();
                                        Delay(1000000);
                                        ledstripe.toggleAnim();
				}
				//button3.status = 0;
                                //button2.status = 0;
                                //button3.status = 0;
                                //button4.status = 0;
                                
                                eraseLCD(&DisplayLcd);
			}
			
			if( testButton1() == 0 && testButton2() == 0 && testButton3() == 0 && testButton4() == 1)
			{
				one_note[0] = musicSheet[cursor];
                                one_note[0].duration = quaver;
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
                                       
                                        ledstripe.toggleAnim();
                                        Delay(1000000);
                                        ledstripe.toggleAnim();
				}
				
                               	//button3.status = 0;
                                //button2.status = 0;
                                //button3.status = 0;
                                //button4.status = 0;
                                eraseLCD(&DisplayLcd);
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
                                Delay(1000000);
				cursor = 0;
				has_demo = 0;
				break; // Next turn
			}
		}
		

		
	} // game while
} // µC while
