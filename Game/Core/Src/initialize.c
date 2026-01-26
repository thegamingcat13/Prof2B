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

	// Start tim 5
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);
	HAL_TIM_Base_Start_IT(&htim5);

	// Initialize timer for DFT
	HAL_TIM_Base_Start_IT(&htim2);
}

//Function : Clock_change
// Developer: Sander van Beek
// Input: int* clock_speed (in Hz)
// Output: status
// This function changed the speed of tim5 from the base 120Hz value to either 140Hz or 160Hz
bool Clock_change(int* clock_speed)
{
	// Variable to hold the new counter value
	uint32_t new_arr = 0;

	// Check requested frequency
	switch (*clock_speed)
	    {
	        case 120:
	            new_arr = 699999;
	            break;
	        case 140:
	            new_arr = 599999;
	            break;
	        case 160:
	            new_arr = 524999;
	            break;
	        default:
	            return false; // Ongeldige snelheid
	    }

	// Write new counter value to timer
	__HAL_TIM_SET_AUTORELOAD(&htim5, new_arr);

	// Get the current counter value from the register
	uint32_t current_arr = __HAL_TIM_GET_AUTORELOAD(&htim5);


	// Check counter value based on requested clock speed
	switch (*clock_speed)
	{
	case 120:
		if (current_arr == 699999)
			return true;
		else
			return false;

	case 140:
		if (current_arr == 599999)
			return true;
		else
			return false;

	case 160:
		if (current_arr == 524999)
			return true;
		else
			return false;
	}

	return false;

}
