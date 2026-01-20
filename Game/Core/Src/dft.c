#include "game.h"
#include "main.h"

volatile bool dft_ready = false;
volatile bool left = false;
volatile bool right = false;
volatile bool start = false;

volatile int sample_count = 0;
float INPUT_raw[(int)N];
float INPUT_win[(int)N];
float blackman[(int)N];


void dft_inter(void)
{
	if (dft_ready == false)
	{
		HAL_ADC_Start(&hadc2);
		if (HAL_ADC_PollForConversion(&hadc2, 1) == HAL_OK)
		{
			INPUT_raw[sample_count] = (float)HAL_ADC_GetValue(&hadc2);

			sample_count++;
		}

		if (sample_count >= (int)N)
		{
			dft_ready = true;
			sample_count = 0;
		}
	}
}


void DFT(void)
{
    // eerst window toepassen op kopie
    for (int n = 0; n < (int)N; n++)
    {
        INPUT_win[n] = INPUT_raw[n] * blackman[n];
    }

    for (int k = 30; k < 41; k++) {
        float re = 0.0f;
        float im = 0.0f;
        for (int n = 0; n < (int)N; n++) {
            float angle = 2.0f * M_PI * k * n / N;
            re += INPUT_win[n] * cosf(angle);
            im += INPUT_win[n] * sinf(angle);
        }
        float mag = sqrtf(re * re + im * im);
        switch (k)
        {
        case 30:
        		if (mag > 300)
        		{
        			left = true;
        			HAL_GPIO_TogglePin(GPIOD, LD4_Pin);
        			continue;
        		}
        		break;

        case 31:
        		if (mag > 300)
        		{
        			left = true;
        			HAL_GPIO_TogglePin(GPIOD, LD4_Pin);
        			continue;
        		}
        		break;

        case 35:
        		if (mag > 300)
				{
					right = true;
					HAL_GPIO_TogglePin(GPIOD, LD5_Pin);
					continue;
				}
        		break;

        case 36:
        		if (mag > 300)
        		{
        			right = true;
        			HAL_GPIO_TogglePin(GPIOD, LD5_Pin);
        			continue;
        		}
        		break;

        case 39:
        		if (mag > 300)
        		{
        			start = true;
        			HAL_GPIO_TogglePin(GPIOD, LD6_Pin);
        			continue;
        		}
        		break;

        case 40:
        		if (mag > 300)
        		{
        			start = true;
        			HAL_GPIO_TogglePin(GPIOD, LD6_Pin);
        			continue;
        		}
        		break;
        }
    }
}


void init_blackman(void)
{
    for (int n = 0; n < (int)N; n++)
    {
        blackman[n] = 0.42f - 0.5f * cosf((2.0f * M_PI * n) / (N - 1.0f)) + 0.08f * cosf((4.0f * M_PI * n) / (N - 1.0f));
    }
}
