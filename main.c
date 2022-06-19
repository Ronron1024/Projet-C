#include "stm32l1xx_nucleo.h"
#include "displayLCD.h"
#include "buttons.h"
#include "stm32l1xx_it.h"

BTN button1;
BTN button2;
BTN button3;
BTN button4;

 int main(void)
{

  DISPLAYLCD DisplayLcd;

  initLCD(&DisplayLcd);         //Init structure & config
  
  initButtons(&button1, &button2, &button3, &button4); //Init structure
  enable_interrupt_ext_buttons();                      //Init interruption ext button;


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
      //Delay(1000000);
     }
  
  
    //else 
     // DisplayDigit(&DisplayLcd, 1, rondBas);
    /*for(int i=1;i<5;i++){       
 
    if (i == 1 || i ==3)
      DisplayDigit(&DisplayLcd, i, rondBas);
    else
      DisplayDigit(&DisplayLcd, i, rondHaut); 
      Delay(100000);
      DisplayDigit(&DisplayLcd, i, empty);

*/
   
  }

}
