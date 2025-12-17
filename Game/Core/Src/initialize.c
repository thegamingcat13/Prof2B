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
