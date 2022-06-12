#include "stm32l1xx_nucleo.h"
#include "../includes/notes.h"

Note playing = C0;
float all_frequencies[63] = {
	C0_FREQ, D0_FREQ, E0_FREQ, F0_FREQ, G0_FREQ, A0_FREQ, B0_FREQ,
	C1_FREQ, D1_FREQ, E1_FREQ, F1_FREQ, G1_FREQ, A1_FREQ, B1_FREQ,
	C2_FREQ, D2_FREQ, E2_FREQ, F2_FREQ, G2_FREQ, A2_FREQ, B2_FREQ,
	C3_FREQ, D3_FREQ, E3_FREQ, F3_FREQ, G3_FREQ, A3_FREQ, B3_FREQ,
	C4_FREQ, D4_FREQ, E4_FREQ, F4_FREQ, G4_FREQ, A4_FREQ, B4_FREQ,
	C5_FREQ, D5_FREQ, E5_FREQ, F5_FREQ, G5_FREQ, A5_FREQ, B5_FREQ,
	C6_FREQ, D6_FREQ, E6_FREQ, F6_FREQ, G6_FREQ, A6_FREQ, B6_FREQ,
	C7_FREQ, D7_FREQ, E7_FREQ, F7_FREQ, G7_FREQ, A7_FREQ, B7_FREQ,
	C8_FREQ, D8_FREQ, E8_FREQ, F8_FREQ, G8_FREQ, A8_FREQ, B8_FREQ
};

Note moonlight[11] = { G4, G4, G4, A5, B5, A5, G4, B5, A5, A5, G4 };

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
	Note frequency = moonlight[note];
	TIM3->ARR = (uint32_t)(1/all_frequencies[frequency] * 1000000);
	TIM3->CCR2 = TIM3->ARR / 2;
}