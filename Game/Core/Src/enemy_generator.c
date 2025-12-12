#include "game.h"
#include <stdlib.h> // For rand() and srand()
#include <stdio.h>

uint8_t EnemyCarGenerator()
{
	uint8_t mask;
	do
	{
		mask = rand() % 16;
	} while (mask == 15);
	return mask;
}

void addNewObstacleCar(int lane)
{
    // Find an inactive slot in the array
    for (int i = 0; i < MAX_ENEMYS; i++) {
        if (!Enemy[i].isActive) {
        	Enemy[i].lane = lane;
        	Enemy[i].yPosition = OBSTACLE_SPAWN_Y; // Start at the top
        	Enemy[i].isActive = true;

            // For debugging:
            printf("Spawned new car in lane %d at y=%d\n", lane, Enemy[i].yPosition);
            return; // Car added, so exit the function
        }
    }
}

void processNewEnemyMask(uint8_t mask)
{
	if (mask == 0x00)
		return;

	for (int lane = 0; lane <4; lane++)
	{
		if ((mask >> lane) & 0x01)
			addNewObstacleCar(lane);
	}
}
