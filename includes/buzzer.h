#ifndef BUZZER_H_INCLUDED
#define BUZZER_H_INCLUDED

#include "notes.h"

typedef struct Buzzer
{
	void (*toggleBuzzer)(void);
	void (*setSheetMusic)(Note[], uint8_t);
} Buzzer;

#endif