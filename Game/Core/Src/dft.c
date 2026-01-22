#include "game.h"
#include "main.h"

volatile int dft_ready = 0;
int left = 0;
int right = 0;
volatile int start = 0;

volatile int sample_count = 0;

float INPUT_raw[(int)N];
float INPUT_win[(int)N];
float blackman[(int)N];
float dft_array[(int)N];


// Function dft_inter
// Developer: Collin Crooy
// Input: De microfoon die op de ADC staat
// Output: Een signaal dat DFT_ready is waardoor de DFT kan gaan berekenen
// Dit is de functie die aangeroepen word door de interupt die dan input in een buffer zet.
void dft_inter(void)
{
	if (dft_ready == 0)
	{
		// start de ADC om een signaal op te vangen
		HAL_ADC_Start(&hadc2);
		if (HAL_ADC_PollForConversion(&hadc2, 1) == HAL_OK)
		{
			// zodra de ADC oke geeft zet de waardens in de array.
			INPUT_raw[sample_count] = (float)HAL_ADC_GetValue(&hadc2);

			sample_count++;
		}

		// stuurd een signaal als de sample count gelijk/groter is dan de bin(N)
		if (sample_count >= (int)N)
		{
			dft_ready = 1;
			sample_count = 0;
		}
	}
}

// Function DFT
// Developer: Collin Crooy
// Input: NONE
// Output: een signaal of de player naar links, rechts en of de game start.
// Dit is de functie die al de berekeningen doet om te weten welke frequentie er is
// en stuurd een signaal welke output die dan moet geven
void DFT(void)
{
    // eerst window toepassen op ADC input
    for (int n = 0; n < (int)N; n++)
    {
        INPUT_win[n] = INPUT_raw[n] * blackman[n];
    }

//    for (int k = 0; k < N; k++)
//    {
//		float re = 0.0f;
//		float im = 0.0f;
//		for (int n = 0; n < (int)N; n++) {
//			float angle = 2.0f * M_PI * k * n / N;
//			re += INPUT_win[n] * cosf(angle);
//			im += INPUT_win[n] * sinf(angle);
//		}
//		float mag = sqrtf(re * re + im * im);
//		dft_array[k] = mag;
//	}

    int k = 21;
	float re = 0.0f;
	float im = 0.0f;
	for (int n = 0; n < (int)N; n++)
	{
		float angle = 2.0f * M_PI * k * n / N;
		re += INPUT_win[n] * cosf(angle);
		im += INPUT_win[n] * sinf(angle);
	}
	float mag = sqrtf(re * re + im * im);

	if (mag >= 13000)
	{
		left = 1;
		HAL_GPIO_TogglePin(GPIOD, LD4_Pin);
//		for (int n = 0; n < (int)N; n++)
//		{
//			INPUT_raw[n] = 0;
//			INPUT_win[n] = 0;
//			mag = 0;
//		}
		return;
    } // bin 45 bin 50 57

	k = 24;
	re = 0.0f;
	im = 0.0f;
	for (int n = 0; n < (int)N; n++)
	{
		float angle = 2.0f * M_PI * k * n / N;
		re += INPUT_win[n] * cosf(angle);
		im += INPUT_win[n] * sinf(angle);
	}
	mag = sqrtf(re * re + im * im);

	if (mag >= 9000)
	{
		right = 1;
		HAL_GPIO_TogglePin(GPIOD, LD5_Pin);
//		for (int n = 0; n < (int)N; n++)
//		{
//			INPUT_raw[n] = 0;
//			INPUT_win[n] = 0;
//			mag = 0;
//		}
		return;
	}

	k = 26;
	re = 0.0f;
	im = 0.0f;
	for (int n = 0; n < (int)N; n++)
	{
		float angle = 2.0f * M_PI * k * n / N;
		re += INPUT_win[n] * cosf(angle);
		im += INPUT_win[n] * sinf(angle);
	}
	mag = sqrtf(re * re + im * im);

	if (mag >= 5000)
	{
		start = 1;
		HAL_GPIO_TogglePin(GPIOD, LD6_Pin);
//		for (int n = 0; n < (int)N; n++)
//		{
//			INPUT_raw[n] = 0;
//			INPUT_win[n] = 0;
//			mag = 0;
//		}
		return;
	}
}

// Function init_blackman
// Developer: Collin Crooy
// Input: NONE
// Output: NONE
// Dit is een funcite die de blackman window 1 keer inialiseerd om dan te gebruiken in de DFT
void init_blackman(void)
{
    for (int n = 0; n < (int)N; n++)
    {
        blackman[n] = 0.42f - 0.5f * cosf((2.0f * M_PI * n) / (N - 1.0f)) + 0.08f * cosf((4.0f * M_PI * n) / (N - 1.0f));
    }
}
