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

	// Als de interupt van TIM2 afkomt vullen we de dft buffer
    if (htim->Instance == TIM2)
    {
        dft_inter();
    }

    // Als de interupt van TIM5 afkomt
    if (htim->Instance == TIM5)
    {
    	// Verhoog alle cycle counts met 1
        cycleCount++;
        cycle_count_enemy++;
        cycle_start_stop++;
        cycleCountPlayer++;

        if (cycleCount >= 12) // Na 12 cycles 1 game tick (als de game versnelt versnelt de tick speed dus ook)
        {
            cycleCount = 0;
            Do_Game_Tick = 1;
        }

        // Probeer Y positie van alle tegenstanders te verhogen
        for (int i = 0; i < MAX_ENEMYS; i++)
        {
			if (Enemy[i].isActive)
			{
				Enemy[i].yPosition++;

				// Wanneer de tegenstander van het scherm af is zetten we deze op nonactief
				if (Enemy[i].yPosition + ENEMY_HEIGHT >= ENEMY_OFF_SCREEN)
					Enemy[i].isActive = false;
			}
		}
    }
}

// Function HAL_GPIO_EXTI_Callback
// Developer: Sander van Beek
// Input: None
// Output: None
// Deze functie word opgeroepen als de interupt van EXTI getriggerd wordt
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	// Zet collision aan of uit als er op de knop wordt gedrukt
    if (GPIO_Pin == GPIO_PIN_0)
    {
        collisionEnabled = !collisionEnabled;
    }
}
