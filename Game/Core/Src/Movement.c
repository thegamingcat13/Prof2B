#include "game.h"

// Function PlayerMovement
// Developer: Collin Crooy
// Input: De microfoon die op de ADC staat
// Output: Een signaal dat DFT_ready is waardoor de DFT kan gaan berekenen
// Dit is de functie die aangeroepen word door de interupt die dan input in een buffer zet.
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
