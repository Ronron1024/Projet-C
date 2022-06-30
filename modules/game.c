#include "stm32l1xx_nucleo.h"
#include "../includes/buzzer.h"
#include "../includes/ledstripe.h"
#include "../includes/prototypes.h"
#include "../includes/structures.h"

#include "../includes/displayLCD.h"

extern DISPLAYLCD DisplayLcd;

Note demo_song[6] =
{
  {C4, quaver}, {E4, quaver}, {G4, quaver}, {E4, quaver}, {G4, quaver}, {C4, quaver}
};
int demo_song_digit[6] =
{
  1, 2, 4, 3, 4, 1
};

Note pop_corn[29] = 
{
	{A5, quaver}, {G5, quaver}, {A5, quaver}, {E5, quaver}, {C5, quaver}, {E5, quaver}, {A4, crotchet},
	{A5, quaver}, {G5, quaver}, {A5, quaver}, {E5, quaver}, {C5, quaver}, {E5, quaver}, {A4, crotchet},
	{A5, quaver}, {B5, quaver}, {C6, quaver}, {B5, quaver}, {C6, quaver}, {A5, quaver}, {B5, quaver}, {A5, quaver}, {B5, quaver}, {G5, quaver}, {A5, quaver}, {G5, quaver}, {A5, quaver}, {F5, quaver}, {A5, crotchet}
};
int pop_corn_digit[29] = 
{
	4, 3, 4, 2, 1, 2, 1, 4, 3, 4, 2, 1, 2, 1, 1, 2, 4, 3, 4, 2, 4, 3, 4, 1, 4, 3, 4, 2, 4
};

Note jacquot[32] = 
{
	{C5, crotchet}, {D5, crotchet}, {E5, crotchet}, {C5, crotchet}, {C5, crotchet}, {D5, crotchet}, {E5, crotchet}, {C5, crotchet},
	{E5, crotchet}, {F5, crotchet}, {G5, minim}, {E5, crotchet}, {F5, crotchet}, {G5, minim},
	{G5, quaver}, {A5, quaver}, {G5, quaver}, {F5, quaver}, {E5, crotchet}, {C5, crotchet}, {G5, quaver}, {A5, quaver}, {G5, quaver}, {F5, quaver}, {E5, crotchet}, {C5, crotchet},
	{C5, crotchet}, {G4, crotchet}, {C5, minim}, {C5, crotchet}, {G4, crotchet}, {C5, minim}
};
int jacquot_digit[32] = 
{
	1, 2, 3, 1, 1, 2, 3, 1, 2, 3, 4, 2, 3, 4, 3, 4, 3, 2, 1, 1, 3, 4, 3, 2, 1, 1, 3, 1, 2, 3, 1, 2
};


//function verification
int checkNote(Note user, Note expected)
{
	return user.name == expected.name;
}


extern Buzzer buzzer;
void demo(uint8_t to_play, Note* music_sheet)
{  
	buzzer.setSheetMusic(music_sheet, to_play);
	buzzer.toggleBuzzer();
	buzzer.is_playing = 1;
}