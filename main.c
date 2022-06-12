#include "stm32l1xx_nucleo.h"
#include "displayLCD.h"

int main(void)
{

  DISPLAYLCD DisplayLcd;
  
  initLCD(&DisplayLcd);
  
  statusLCD(&DisplayLcd,ON);    //ON ou OFF LCD
  
  IntensityLCD(&DisplayLcd,0);  //Between 0 to 15

  uint8_t rondBas[N];
  uint8_t rondHaut[N];
  uint8_t empty[N];
  
  ArrayDigit(rondBas,4, M1, M0,L0,R0);  //=> define.h
  ArrayDigit(rondHaut,4, M1, M2,L1,R1);
  ArrayDigit(empty,0);
  
  

  
    /* Infinite loop */
  while (1)
  {
  
    for(int i=1;i<5;i++){       
 
    if (i == 1 || i ==3)
      DisplayArrayDigit(&DisplayLcd, i, rondBas);
    else
      DisplayArrayDigit(&DisplayLcd, i, rondHaut); 
      Delay(100000);
      DisplayArrayDigit(&DisplayLcd, i, empty);
   
    }

  }
}