#include "stm32l1xx_nucleo.h"
#include "../includes/buzzer.h"
#include "../includes/ledstripe.h"
#include "../includes/prototypes.h"
#include "../includes/structures.h"

#include "../includes/displayLCD.h"

extern DISPLAYLCD DisplayLcd;

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