#include "main.h"

BTN button1;
BTN button2;
BTN button3;
BTN button4;

DISPLAYLCD DisplayLcd;

Buzzer buzzer;
extern uint8_t LEDs_position[LED_NBR];
LedStripe ledstripe;

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


extern Note moonlight[11];

//Note* musicSheet = 0 ;


void init_ADC(void);
void enable_interupt_adc(void);


/*

  while(1)
  {
   //ADC enable On active le CAN
    ADC1->CR2 |= (1<<0);
    
    while( (ADC1->SR & ADC_FLAG_ADONS) == 0 ); //Pas de début de conversion
    
    ADC1->CR2 |= (1<<30);       //Start conversion SWSTART
    
    while( (ADC1->SR & ADC_FLAG_EOC) == 0 ); //Fin de conversion
    
      //Configuration du raport cyclique
    //TIM3->CCR1 = 20; //duty cycle
    TIM3->CCR1 = 39*(ADC1->DR)/4094;
}

}

*/
//RV1 pa1 //RV0 pa0
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

void enable_interupt_adc(void){

  NVIC->ISER[0] |= 1 << 18;



}








int main(void)
{
	initLCD(&DisplayLcd);         //Init structure & config
	initButtons(&button1, &button2, &button3, &button4); //Init structure
	enable_interrupt_ext_buttons();                      //Init interruption ext button;
        init_ADC();
        enable_interupt_adc();
	
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
	
	Note noteButton1[1] = { {G4, quaver} };
	Note noteButton2[1] = { {A5, quaver} };
	Note noteButton3[1] = { {B5, quaver} };
	Note noteButton4[1] = { {D5, quaver} };
	
	int cursor=0 ;
	uint8_t life = 4;
	uint8_t note_to_play = 3;
	int game = 1;
	int has_demo = 0;
        
        
        

         //ADC enable On active le CAN
         ADC1->CR2 |= (1<<0);
       
        while( (ADC1->SR & ADC_FLAG_ADONS) == 0 ); //Pas de début de conversion
    
         ADC1->CR2 |= (1<<30);       //Start conversion SWSTART
    
        while( (ADC1->SR & ADC_FLAG_EOC) == 0 ); //Fin de conversion
    
        
        while(button1.status != 1 ){

         
}

  
        
        
	
	while (1)
	{		
		while(game && !buzzer.is_playing)
		{
			
			if (!has_demo)
			{
				demo(note_to_play);
				has_demo = 1;
				continue; // Cannot play during demo
			}
			
			if(button1.status == 1)
			{
				buzzer.setSheetMusic(noteButton1 ,1);
				buzzer.toggleBuzzer();
				buzzer.is_playing = 1;
				if ( checkNote(noteButton1[0],moonlight[cursor]) )
				{        
					printDigit(&DisplayLcd,4, '0');
					cursor++;
				}
				else 
				{          
					printDigit(&DisplayLcd,4, '1');
					life--;          
				}
			}
			
			if(button2.status == 1){
				buzzer.setSheetMusic(noteButton2 ,1);
				buzzer.toggleBuzzer();
				buzzer.is_playing = 1;
				if ( checkNote(noteButton2[0],moonlight[cursor]) )
				{
					printDigit(&DisplayLcd,4, '0');
					cursor++;       
				}
				else 
				{
					printDigit(&DisplayLcd,4, '1');
					life--;
				}
			}
			
			if(button3.status == 1)
			{
				buzzer.setSheetMusic(noteButton3 ,1);
				buzzer.toggleBuzzer();
				buzzer.is_playing = 1;
				if ( checkNote(noteButton3[0],moonlight[cursor]) )
				{
					printDigit(&DisplayLcd,4, '0');
					cursor++;       
				}
				else 
				{
					printDigit(&DisplayLcd,4, '1');
					//life--;
				}
				button3.status = 0;
			}
			
			if(button4.status == 1){
				buzzer.setSheetMusic(noteButton4 ,1);
				buzzer.toggleBuzzer();
				buzzer.is_playing = 1;
				if ( checkNote(noteButton4[0],moonlight[cursor]) )
				{
					printDigit(&DisplayLcd,4, '0');
					cursor++;       
				}
				else 
				{
					printDigit(&DisplayLcd,4, '1');
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
			
			if (cursor == 11)
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
} // �C while

  initLCD(&DisplayLcd);         //Init structure & config
  
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

  Note noteButton1[1] = { {G4, quaver} };
  Note noteButton2[1] = { {A5, quaver} };
  Note noteButton3[1] = { {B5, quaver} };
  Note noteButton4[1] = { {D5, quaver} };

int cursor=0 ;

uint8_t life = 4;

demo(11);

int game =1;

  while (1)
  {

   while(game && !buzzer.is_playing){
    
      if(button1.status == 1){
        
        buzzer.setSheetMusic(noteButton1 ,1);
        buzzer.toggleBuzzer();
        buzzer.is_playing = 1;
        if ( checkNote(noteButton1[0],moonlight[cursor]) ){
        
        printDigit(&DisplayLcd,4, '0');
        cursor++;
        
        
        }
        
        else {
          
          printDigit(&DisplayLcd,4, '1');
          life--;
          
        }
        
      }
      
      if(button2.status == 1){
      
           buzzer.setSheetMusic(noteButton2 ,1);
           buzzer.toggleBuzzer();
           buzzer.is_playing = 1;
           if ( checkNote(noteButton2[0],moonlight[cursor]) ){
           
              printDigit(&DisplayLcd,4, '0');
              cursor++;       
           }
            
           else {
              
             printDigit(&DisplayLcd,4, '1');
             life--;
              
           }
        
       
      
      }
      
      if(button3.status == 1){

           buzzer.setSheetMusic(noteButton3 ,1);
           buzzer.toggleBuzzer();
           buzzer.is_playing = 1;
           if ( checkNote(noteButton3[0],moonlight[cursor]) ){
           
              printDigit(&DisplayLcd,4, '0');
              cursor++;       
           }
            
           else {
              
             printDigit(&DisplayLcd,4, '1');
             life--;
              
           }
       
      
      
       button3.status = 0;
       
      
      }
      
      if(button4.status == 1){
      
           buzzer.setSheetMusic(noteButton4 ,1);
           buzzer.toggleBuzzer();
           buzzer.is_playing = 1;
           if ( checkNote(noteButton4[0],moonlight[cursor]) ){
           
              printDigit(&DisplayLcd,4, '0');
              cursor++;       
           }
            
           else {
              
             printDigit(&DisplayLcd,4, '1');
             life--;
              
           }
           
           
       button4.status = 0;
       
      
      }
      
      if (life == 0 || cursor == 11)
        game = 0;
      
      // Display health bar
      for (uint8_t i = 0; i < LED_NBR; i++)
      {
          if (i < life * 2)
            ledstripe.setLED(ON, LEDs_position[i]);
          else
            ledstripe.setLED(OFF, LEDs_position[i]);
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
  }

}
