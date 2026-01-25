#include "main.h"
#include "stm32f4xx_it.h"
#include "game.h"

int cycleCount = 0;
int volatile cycleCountPlayer = 0;
volatile int cycle_count_enemy = 0;
volatile int cycle_start_stop = 0;
volatile int Do_Game_Tick = 0;


// Function HAL_TIM_PeriodElapsedCallback
// Developer: Sander van Beek, Collin Crooy
// Input: None
// Output: None
// Dit is een functie die checkt welke timer bezig is en dan de bij passelijke dingen moet uitvoeren
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        dft_inter();
    }

    if (htim->Instance == TIM5)
    {
        cycleCount++;
        cycle_count_enemy++;
        cycle_start_stop++;
        cycleCountPlayer++;

        if (cycleCount >= 12) // 12 * 8.33ms = ~100ms
        {
            cycleCount = 0;
            // Zet hier een vlaggetje (flag) dat 100ms voorbij is
            Do_Game_Tick = 1;
        }

        for (int i = 0; i < MAX_ENEMYS; i++)
        {
			if (Enemy[i].isActive)
			{
				Enemy[i].yPosition++;

				if (Enemy[i].yPosition + ENEMY_HEIGHT >= ENEMY_OFF_SCREEN)
					Enemy[i].isActive = false;
			}
		}
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_0)
    {
        collisionEnabled = !collisionEnabled;
    }
}
