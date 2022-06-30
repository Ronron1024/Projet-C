#include "stm32l1xx_nucleo.h"
#include "../includes/buzzer.h"
#include "../includes/ledstripe.h"
#include "../includes/prototypes.h"
#include "../includes/structures.h"

#include "../includes/displayLCD.h"

extern DISPLAYLCD DisplayLcd;

extern  BTN button1;
extern  BTN button2;
extern  BTN button3;
extern  BTN button4;

Note moonlight[11] =
{ 
    {G4, crotchet},
    {G4, crotchet}, 
    {G4, crotchet},
    {A5, crotchet},
    {B5, minim},
    {A5, minim},
    {G4, crotchet},
    {B5, crotchet},
    {A5, crotchet},
    {A5, crotchet},
    {G4, semibreve}
};

int length = 11; 


//function verification
int checkNote(Note user, Note expected){
  
  return user.name == expected.name;
  
}

//functionplay

Note basic[3] = {
      {G4, crotchet},
      {A5, crotchet},
      {B5, crotchet}
};


extern Buzzer buzzer;
void demo(uint8_t to_play)
{  
  buzzer.setSheetMusic(moonlight, to_play);
  buzzer.toggleBuzzer();
  buzzer.is_playing = 1;
 
}





void  checkParttion(uint8_t* life, int numberNote )  {
  
  Note noteButton1[1] = { {G4, quaver} };
  Note noteButton2[1] = { {A5, quaver} };
  Note noteButton3[1] = { {B5, quaver} };
  Note noteButton4[1] = { {D5, quaver} };

int cursor=0 ;

while(cursor != numberNote){


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
          *life--;
          
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
             *life--;
              
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
             *life--;
              
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
             *life--;
              
           }
           
           
       button4.status = 0;
       
      
      }


}

buzzer.is_playing = 0;


}








