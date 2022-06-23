#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

#include <stdio.h>
#include "stm32l1xx_nucleo.h"
#include "notes.h"
#include "buzzer.h"
#include "ledstripe.h"

// µC basic functions
void setBitTo1(volatile void* reg, size_t reg_size, uint8_t n);
void setBitsTo1(volatile void* reg, size_t reg_size, uint8_t n, ...);
void setBitTo0(volatile void* reg, size_t reg_size, uint8_t n);
void setBitsTo0(volatile void* reg, size_t reg_size, uint8_t n, ...);

// Initialization
void initButton();
void initTIM2();
void initTIM3();
void initTIM4();
void initPWM();
void initBuzzer();
void initLEDs(uint8_t n, ...);

// Interrupts
void enableInterruptButton();
void enableInterruptTIM2();
void enableInterruptTIM4();

// Buzzer
Buzzer InitBuzzer();
void toggleBuzzer();
void tone(Note note);
void setSheetMusic(Note music_sheet[], uint8_t music_sheet_length);

// LEDStripe
LedStripe InitLedStripe();
void setLED(uint8_t state, uint8_t led);
void setLEDs(uint8_t state, uint8_t n, ...);
void animNextFrame();

#endif