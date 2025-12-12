#include "game.h"
#include <stdlib.h> // For rand() and srand()
#include <time.h>   // For time() (used to seed the random number generator)
#include "stdio.h"

void initStructures()
{
	for (int i = 0; i < MAX_ENEMYS; i++)
	{
		Enemy[i].lane = -1;
		Enemy[i].yPosition = -1;
		Enemy[i].isActive = false;
	}

	Player.lane = -1;
	Player.isActive = false;
}

void initializeRandomSeed()
{
	srand((unsigned int) HAL_GetTick());
}

void init()
{
	initStructures();
	initializeRandomSeed();
}
