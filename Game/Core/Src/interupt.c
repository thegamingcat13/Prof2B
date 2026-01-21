#include "main.h"
#include "stm32f4xx_it.h"
#include "game.h"


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

    if (htim->Instance == TIM3)
    {
        // Game logica en FPGA clock
        HAL_GPIO_WritePin(Clock_FPGA_GPIO_Port, Clock_FPGA_Pin, SET);
        HAL_GPIO_WritePin(Clock_FPGA_GPIO_Port, Clock_FPGA_Pin, SET);
        HAL_GPIO_WritePin(Clock_FPGA_GPIO_Port, Clock_FPGA_Pin, RESET);

        for (int i = 0; i < MAX_ENEMYS; i++) {
            if (Enemy[i].isActive) Enemy[i].yPosition++;
        }
    }
}
