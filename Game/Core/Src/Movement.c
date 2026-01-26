#include "game.h"

// Function PlayerMovement
// Developer: Collin Crooy
// Input: De Direction (links, rechts)
// Output: NONE
// Dit is een functie die kijkt of we player naar links moet gaan of naar rechts in elke mogelijke positie.
int PlayerMovement (int *left, int *right)
{
	// Beweeg naar rechts
	if (*right == 1)
	{
		*right = 0;
		switch (Player.lane)
		{
		case 0: Player.lane = 1; return 1;
		case 1: Player.lane = 2; return 1;
		case 2: Player.lane = 3; return 1;
		default: return 1;
		}
	}

	// Beweeg naar links
	if (*left == 1)
	{
		*left = 0;

		switch (Player.lane)
		{
		case 1: Player.lane = 0; return 1;
		case 2: Player.lane = 1; return 1;
		case 3: Player.lane = 2; return 1;
		default: return 1;
		}
	}

	return 0;
}
