#include "game.h"

// Function Collision
// Developer: Sander van Beek
// Input: None
// Output: Bool collided
// This function check for collision between the player and a enemy car.
// The collision check changed a boolean which value is returned at the end of the function.
bool Collision()
{
	bool collided = false;
	// Loop through all enemy's
	for (int i = 0; i < MAX_ENEMYS; i++)
	{
		// Check
		if (Player.lane == Enemy[i].lane)
		{
			if (PLAYER_Y_POS - Enemy[i].yPosition <= 0)
			{
				collided = true;
				break;
				;
			}
		}
	}
	return collided;
}
