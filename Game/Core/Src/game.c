#include "game.h"

PlayerCar Player;
ObstacleCar Enemy[MAX_ENEMYS];
GameState_t currentGameState;

uint8_t NewEnemyMask = 0x00;

uint8_t tx_byte1;
uint8_t tx_byte2;

uint8_t current_NewEnemyMask;

// Function gameTick
// Developer: Sander van Beek
// Input: None
// Output: None
// This function runs one gameTick, and makes sure that everything that needs to run for a tick runs.
void gameTick ()
{
	// Generate new enemies
	current_NewEnemyMask = EnemyCarGenerator();
	processNewEnemyMask(current_NewEnemyMask);
	NewEnemyMask = current_NewEnemyMask;

	// Create the 2 bytes necessary for FPGA communication
	CreateBytes (&tx_byte1, &tx_byte2);

	// Sent bytes to FPGA
	TransmitByte(tx_byte1);
	TransmitByte(tx_byte2);

	NewEnemyMask = 0x00;
}

// Function gameState
// Developer: Sander van Beek
// Input: int state
// Output : None
// This function can be used to change the gameState between STOP, RUNNING and SCORE
void gameState (int state)
{
	switch (state)
	{
	case 1: currentGameState = STOP;
	case 2: currentGameState = RUNNING;
	case 3: currentGameState = SCORE;
	default : currentGameState = STOP;
	}
}
