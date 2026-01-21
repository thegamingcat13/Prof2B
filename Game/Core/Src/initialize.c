#include "game.h"
#include <stdlib.h> // For rand() and srand()
#include <time.h>   // For time() (used to seed the random number generator)
#include "stdio.h"

// Function initStructures
// Developer: Sander van Beek
// Input: None
// Output: None
// This function initializes all structure field to their start value
void initStructures()
{
	for (int i = 0; i < MAX_ENEMYS; i++) // repeat for all structures in array
	{
		// Initialize enemy structure
		Enemy[i].lane = -1;
		Enemy[i].yPosition = -1;
		Enemy[i].isActive = false;
	}

	// Initialize player structure
	Player.lane = 0;
	Player.isActive = false;
}

// Function: init
// Developer: Sander van Beek
// Input: None
// Output: None
// This function will be run once and runs all the other initalization functions
void init()
{
	// Create blackman window
	init_blackman();

	// Initialize structure
	initStructures();

	// Initialize timer for DFT
	HAL_TIM_Base_Start_IT(&htim2);
}

//Function : Clock_change
// Developer: Sander van Beek
// Input: int* clock_speed (in Hz)
// Output: status
// This function changed the speed of tim3 from the base 120Hz value to either 140Hz or 160Hz
bool Clock_change(int* clock_speed)
{
	// Variable for status check
	HAL_StatusTypeDef status;

	// Stop timer
	HAL_TIM_Base_Stop_IT(&htim3);

	// Check requestion frequency
	switch (*clock_speed)
	{
	case 140:
		// Change timer prescaler for 140Hz frequency
		htim3.Init.Prescaler = 600-1;
		break;
	case 160:
		// Change timer prescaler for 160Hz frequency
		htim3.Init.Prescaler = 525-1;
		break;
	}

	// Initialize timer
	status = HAL_TIM_Base_Init(&htim3);

	// Check status of initialization
	if (status != HAL_OK)
		return false;

	// Start timer in interupt mode
	status = HAL_TIM_Base_Start_IT(&htim3);

	// Check status of started timer
	if (status != HAL_OK)
		return false;

	return true;

}
