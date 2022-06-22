#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

#include "notes.h"

// Initialization
void initButton();
void initTIM2();
void initTIM3();
void initPWM();
void initBuzzer();

// Interrupts
void enableInterruptButton();
void enableInterruptTIM2();

// Buzzer
void toggleBuzzer();
void tone(Note note);
void setSheetMusic(Note music_sheet[], uint8_t music_sheet_length);

#endif