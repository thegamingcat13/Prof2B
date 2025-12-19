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
	Player.lane = -1;
	Player.isActive = false;
}

// Function: initializeRandomSeed
// Developer: Sander van Beek
// Input: None
// Output: None
// This function start the seed for the randomizer
void initializeRandomSeed()
{
	srand((unsigned int) HAL_GetTick());
}

// Function: init
// Developer: Sander van Beek
// Input: None
// Output; None
// This function will be run once and runs all the other initalization functions
void init()
{
	HAL_TIM_Base_Start_IT(&htim3);
	initStructures();
	initializeRandomSeed();
}

//Function : Clock_change
// Developer: Sander van Beek
// Input: int* clock_speed (in Hz)
// Output: status
// This function changed the speed of tim3 from the base 60Hz value to either 70Hz or 80Hz
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
		// Change timer period for 140Hz frequency
		htim3.Init.Prescaler = 349;
		break;
	case 160:
		// Change timer period for 160Hz frequency
		htim3.Init.Prescaler = 299;
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
