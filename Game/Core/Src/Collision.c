#include "game.h"

// Function Collision
// Developer: Sander van Beek
// Input: None
// Output: Bool collided
// This function check for collision between the player and a enemy car.
// The collision check changed a boolean which value is returned at the end of the function.
bool Collision()
{
	// Loop through all enemy's
	for (int i = 0; i < MAX_ENEMYS; i++)
	{
		// Check if enemy lane is the same as the players
		if (Enemy[i].isActive && Player.lane == Enemy[i].lane)
		{
			int enemy_front = Enemy[i].yPosition + ENEMY_HEIGHT;
			int enemy_back	= Enemy[i].yPosition;

			if (enemy_front >= PLAYER_TOP && enemy_back <= PLAYER_BOTTOM)
				return true;
		}
	}
	return false;
}
