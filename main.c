#include "main.h"

BTN button1;
BTN button2;
BTN button3;
BTN button4;

Buzzer buzzer;
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

 int main(void)
{

  DISPLAYLCD DisplayLcd;

  initLCD(&DisplayLcd);         //Init structure & config
  
  initButtons(&button1, &button2, &button3, &button4); //Init structure
  enable_interrupt_ext_buttons();                      //Init interruption ext button;
  
  
  buzzer = InitBuzzer();
  buzzer.setSheetMusic(pop_corn, 32);
  
  ledstripe = InitLedStripe();
  ledstripe.setAnim(K2000);

  statusLCD(&DisplayLcd,ON);    //ON ou OFF LCD
  
  IntensityLCD(&DisplayLcd,0);  //Between 0 to 15

  uint8_t rondBas;
  uint8_t rondHaut;
  uint8_t empty;
  
  createDigit(&rondBas,4, M1, M0,L0,R0);  //=> define.h
  createDigit(&rondHaut,4, M1, M2,L1,R1);
  createDigit(&empty,0);

  printfDigit(&DisplayLcd,"ABCDEFGHIJKLMNOPQRSTUWXYZ!. 0123456789", NORMAL);
  //printfDigit(&DisplayLcd,"01234", NORMAL);
  blinkingLCD(&DisplayLcd, FAST);
  eraseLCD(&DisplayLcd);

    /* Infinite loop */
  while (1)
  {

     if (button1.status ==1){
      printIntDigit(&DisplayLcd,button1.count, NORMAL);
     }
     
     if (button2.status ==1)
       buzzer.toggleBuzzer();
     
     if (button3.status ==1)
       ledstripe.toggleAnim();

   
  }

}
