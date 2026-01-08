#include "game.h"
#include <stdlib.h> // For rand() and srand()
#include <stdio.h>

// Function: EnemyCarGenerator
// Developer: Sander van Beek
// Input: None
// Output: uint8_t with new car location mask
// This function generates a mask that contains the location of the new enemy cars in a byte.
// The location of the new cars is randomized using rand()
uint8_t EnemyCarGenerator()
{
	uint32_t mask; // internal variable for the car mask

	if (HAL_RNG_GenerateRandomNumber(&hrng, &mask) == HAL_OK)
	{
		return (uint8_t)(mask % 15);
	}
	return (uint8_t)(HAL_GetTick() % 15);
}

// Function: addNewObstacleCar
// Developer: Sander van Beek
// Input: int lane
// Output: Bool
// This function add the information for the new enemy cars to the enemy structure array.
// It read the start lane from the internal lane variable which is externally determined from the newenemycarmask
// The function returns whether or not the creation of the enemy succeeded
bool addNewEnemy(int lane)
{
    // Check if there already is a car in the requested lane
    for (int i = 0; i < MAX_ENEMYS; i++) {
        if (Enemy[i].isActive && Enemy[i].lane == lane) {
            return false; // Failed: Lane occupied
        }
    }

    // Find an inactive slot in the array
    for (int i = 0; i < MAX_ENEMYS; i++) {
        if (!Enemy[i].isActive) {
            Enemy[i].lane = lane;
            Enemy[i].yPosition = OBSTACLE_SPAWN_Y;
            Enemy[i].isActive = true;

            printf("Spawned new car in lane %d\n", lane);
            return true; // Success
        }
    }
    return false; // Failed: No empty slots in MAX_ENEMYS
}

// Function: processNewEnemyMask
// Developer: Sander van Beek
// Input: uint8_t mask
// Output: None
// This function translates the NewEnemyMask into a interger value that we can use to fill the structure
// We also check if we succesfully added the new enemy to the structure if now we modify the mask
// This way we don't sent wrong information to the fpga
void processNewEnemyMask(uint8_t *mask)
{
    if (*mask == 0x00)
        return;

    for (int lane = 0; lane < 4; lane++) {
        // Check if the bit for this lane is set
        if ((*mask >> lane) & 0x01) {
            // Try to add the enemy
            if (!addNewEnemy(lane)) {
                // If it failed, clear the bit in the mask
                *mask &= ~(1 << lane);
            }
        }
    }
}
