#include <stdlib.h>
#include "stm32l1xx_nucleo.h"
#include "../includes/prototypes.h"
#include "../includes/notes.h"
#include "../includes/buzzer.h"

#define SILENCE_DURATION  50 // milliseconds

float all_frequencies[64] = {
	C0_FREQ, D0_FREQ, E0_FREQ, F0_FREQ, G0_FREQ, A0_FREQ, B0_FREQ,
	C1_FREQ, D1_FREQ, E1_FREQ, F1_FREQ, G1_FREQ, A1_FREQ, B1_FREQ,
	C2_FREQ, D2_FREQ, E2_FREQ, F2_FREQ, G2_FREQ, A2_FREQ, B2_FREQ,
	C3_FREQ, D3_FREQ, E3_FREQ, F3_FREQ, G3_FREQ, A3_FREQ, B3_FREQ,
	C4_FREQ, D4_FREQ, E4_FREQ, F4_FREQ, G4_FREQ, A4_FREQ, B4_FREQ,
	C5_FREQ, D5_FREQ, E5_FREQ, F5_FREQ, G5_FREQ, A5_FREQ, B5_FREQ,
	C6_FREQ, D6_FREQ, E6_FREQ, F6_FREQ, G6_FREQ, A6_FREQ, B6_FREQ,
	C7_FREQ, D7_FREQ, E7_FREQ, F7_FREQ, G7_FREQ, A7_FREQ, B7_FREQ,
	C8_FREQ, D8_FREQ, E8_FREQ, F8_FREQ, G8_FREQ, A8_FREQ, B8_FREQ,
	SILENCE_FREQ
};
uint8_t music_sheet_cursor = 0;
Note* music_sheet = 0;
uint8_t music_sheet_length = 0;

void toggleBuzzer()
{
	if (TIM3->CR1 & 1)
	{
		TIM2->CR1 &= ~1;
		TIM3->CR1 &= ~1;
		TIM3->CCER &= ~(1 << 4);
	}
	else
	{
		TIM2->CR1 |= 1;
		TIM3->CR1 |= 1;
		TIM3->CCER |= 1 << 4;
	}
}

void tone(Note note)
{
	NoteName frequency = note.name;
	if (note.name == SILENCE)
		TIM3->ARR = 0;
	else
		TIM3->ARR = (uint32_t)(1/all_frequencies[frequency] * 1000000);
	TIM3->CCR2 = TIM3->ARR / 2;
	
	if (note.duration == custom)
		TIM2->ARR = note.custom_duration - 1;
	else
		TIM2->ARR = note.duration - 1;
}

void setSheetMusic(Note user_music_sheet[], uint8_t user_music_sheet_length)
{
	free(music_sheet);	
	music_sheet_length = user_music_sheet_length * 2;
	music_sheet = malloc(sizeof(Note) * music_sheet_length);
	if (!music_sheet)
		return;
	
	Note silence = {SILENCE, custom, SILENCE_DURATION};
	for (music_sheet_cursor = 0; music_sheet_cursor < music_sheet_length; music_sheet_cursor += 2)
	{
		music_sheet[music_sheet_cursor] = user_music_sheet[music_sheet_cursor/2];
		music_sheet[music_sheet_cursor+1] = silence;
	}
	
	music_sheet_cursor = -1;
}

Buzzer InitBuzzer()
{
	initTIM2();
	initTIM3();
	initPWM();
	initBuzzer();
	enableInterruptTIM2();
	
	Buzzer buzzer = {0, toggleBuzzer, setSheetMusic};
	return buzzer;
}