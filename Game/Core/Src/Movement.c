#include "game.h"

// Function PlayerMovement
// Developer: Collin Crooy
// Input: De Direction (links, rechts)
// Output: NONE
// Dit is een functie die kijkt of we player naar links moet gaan of naar rechts in elke mogelijke positie.
void PlayerMovement (int direction)
{
	if (direction == LEFT)
	{
		switch (Player.lane)
		{
		case 1: Player.lane = 0; break;
		case 2: Player.lane = 1; break;
		case 3: Player.lane = 2; break;
		default: break;
		}
	}

	if (direction == RIGHT)
	{
		switch (Player.lane)
		{
		case 0: Player.lane = 1; break;
		case 1: Player.lane = 2; break;
		case 2: Player.lane = 3; break;
		default: break;
		}
	}
}
