#ifndef NOTES_H_INCLUDED
#define NOTES_H_INCLUDED

#include "stm32l1xx_nucleo.h"

#define A0_FREQ 27.5
#define A1_FREQ 55.0
#define A2_FREQ 110.0
#define A3_FREQ 220.0
#define A4_FREQ 440.0
#define A5_FREQ 880.0
#define A6_FREQ 1760.0
#define A7_FREQ 3520.0
#define A8_FREQ 7040.0

#define B0_FREQ 30.87
#define B1_FREQ 61.74
#define B2_FREQ 123.47
#define B3_FREQ 246.94
#define B4_FREQ 493.88
#define B5_FREQ 987.77
#define B6_FREQ 1975.53
#define B7_FREQ 3951.07
#define B8_FREQ 7902.13

#define C0_FREQ 16.35
#define C1_FREQ 32.7
#define C2_FREQ 65.41
#define C3_FREQ 130.81
#define C4_FREQ 261.63
#define C5_FREQ 523.25
#define C6_FREQ 1046.5
#define C7_FREQ 2093.0
#define C8_FREQ 4186.01

#define D0_FREQ 18.35
#define D1_FREQ 36.71
#define D2_FREQ 73.42
#define D3_FREQ 146.83
#define D4_FREQ 293.66
#define D5_FREQ 587.33
#define D6_FREQ 1174.66
#define D7_FREQ 2349.32
#define D8_FREQ 4698.64

#define E0_FREQ 20.6
#define E1_FREQ 41.2
#define E2_FREQ 82.41
#define E3_FREQ 164.81
#define E4_FREQ 329.63
#define E5_FREQ 659.26
#define E6_FREQ 1318.51
#define E7_FREQ 2637.02
#define E8_FREQ 5274.04

#define F0_FREQ 21.83
#define F1_FREQ 43.65
#define F2_FREQ 87.31
#define F3_FREQ 174.61
#define F4_FREQ 349.23
#define F5_FREQ 698.46
#define F6_FREQ 1396.91
#define F7_FREQ 2793.83
#define F8_FREQ 5587.65

#define G0_FREQ 24.5
#define G1_FREQ 49.0
#define G2_FREQ 98.0
#define G3_FREQ 196.0
#define G4_FREQ 392.0
#define G5_FREQ 783.99
#define G6_FREQ 1567.98
#define G7_FREQ 3135.96
#define G8_FREQ 6271.93

#define SILENCE_FREQ 0

typedef enum NoteName
{
	C0 = 0, D0 = 1, E0 = 2, F0 = 3, G0 = 4, A0 = 5, B0 = 6,
	C1 = 7, D1 = 8, E1 = 9, F1 = 10, G1 = 11, A1 = 12, B1 = 13,
	C2 = 14, D2 = 15, E2 = 16, F2 = 17, G2 = 18, A2 = 19, B2 = 20,
	C3 = 21, D3 = 22, E3 = 23, F3 = 24, G3 = 25, A3 = 26, B3 = 27,
	C4 = 28, D4 = 29, E4 = 30, F4 = 31, G4 = 32, A4 = 33, B4 = 34,
	C5 = 35, D5 = 36, E5 = 37, F5 = 38, G5 = 39, A5 = 40, B5 = 41,
	C6 = 42, D6 = 43, E6 = 44, F6 = 45, G6 = 46, A6 = 47, B6 = 48,
	C7 = 49, D7 = 50, E7 = 51, F7 = 52, G7 = 53, A7 = 54, B7 = 55,
	C8 = 56, D8 = 57, E8 = 58, F8 = 59, G8 = 60, A8 = 61, B8 = 62,
	SILENCE = 63
} NoteName;

typedef enum NoteDuration
{
	semibreve = 2000,
	minim = 1000,
	crotchet = 500,
	quaver = 250,
	custom = 0
} NoteDuration;

typedef struct Note
{
	NoteName name;
	NoteDuration duration;
	uint16_t custom_duration;
} Note;

#endif