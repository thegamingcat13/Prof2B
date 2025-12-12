#include "game.h"
#include <stdlib.h> // For rand() and srand()
#include <stdio.h>

// Function: EnemyCarGenerator
// Input: None
// Output: uint8_t with new car location mask
// This function generates a mask that contains the location of the new enemy cars in a byte.
// The location of the new cars is randomized using rand()
uint8_t EnemyCarGenerator()
{
	uint8_t mask; // internal variable for the car mask
	do
	{
		mask = rand() % 16; //Generate random value between 0 and 15 (0000 to 1111)
	} while (mask == 15); //Keep generating the value until it isn't 15
	return mask;
}

// Function: addNewObstacleCar
// Input: int lane
// Output: None
// This function add the information for the new enemy cars to the enemy structure array.
// It read the start lane from the internal lane variable which is externally determined from the newenemycarmask
void addNewEnemy(int lane)
{
    // Find an inactive slot in the array
    for (int i = 0; i < MAX_ENEMYS; i++) {
        if (!Enemy[i].isActive) {
        	Enemy[i].lane = lane;
        	Enemy[i].yPosition = OBSTACLE_SPAWN_Y; // Start at the top
        	Enemy[i].isActive = true;

            // For debugging:
            printf("Spawned new car in lane %d at y=%d\n", lane, Enemy[i].yPosition); //Debug
            return; // Car added, so exit the function
        }
    }
}

// Function: processNewEnemyMask
// Input: uint8_t mask
// Output: None
// This function translates the NewEnemyMask into a interger value that we can use to fill the structure
void processNewEnemyMask(uint8_t mask)
{
	if (mask == 0x00) // if mask is empty or 0 we do nothing
		return;

	for (int lane = 0; lane <4; lane++) //Check for 4 different bits
	{
		if ((mask >> lane) & 0x01)
			addNewEnemy(lane);
	}
}
