#include "game.h"

PlayerCar Player;
ObstacleCar Enemy[MAX_ENEMYS];
GameState_t currentGameState;

uint8_t NewEnemyMask = 0x00;

uint8_t tx_byte1;
uint8_t tx_byte2;

uint8_t current_NewEnemyMask = 0x00;

uint16_t score = 0;

int PixelsMoved = 0;

bool coll_detect = false;

// Function gameTick
// Developer: Sander van Beek
// Input: None
// Output: None
// This function runs one gameTick, and makes sure that everything that needs to run for a tick runs.
void gameTick (bool* gameinfo)
{
	switch (*gameinfo)
	{
	case true:
		// Set gameState to running
		gameState(RUN);

		// Check for collision
		coll_detect = Collision();

		// Make choice based on collision
		switch (coll_detect)
		{
		// Not collided
		case false:
			// Increase score and make sure it doesn't exceed the max
			score++;
			score &= 0x0FFF;

			// Generate new enemies
			current_NewEnemyMask = EnemyCarGenerator();
			processNewEnemyMask(current_NewEnemyMask);
			NewEnemyMask = current_NewEnemyMask;

			// Create the 2 bytes necessary for FPGA communication
			CreateBytes (&tx_byte1, &tx_byte2, gameinfo);

			// Sent bytes to FPGA
			TransmitByte(tx_byte1, tx_byte2);

			NewEnemyMask = 0x00;
			break;
			// Collided
			case true:
				// Set gameState to score with death
				gameState(POINTS_DEATH);

				// Create the 2 bytes necessary for FPGA communication
				CreateBytes (&tx_byte1, &tx_byte2, &coll_detect);

				// Sent bytes to FPGA
				TransmitByte(tx_byte1, tx_byte2);
				break;
			}
			break;
	case false:
		// Dummy collision variable necesary for sending score data
		bool dummy_collision = true;

		// Set gameState to score without death
		gameState(POINTS_LIVE);

		// Create the 2 bytes necessary for FPGA communication
		CreateBytes (&tx_byte1, &tx_byte2, &dummy_collision);

		// Sent bytes to FPGA
		TransmitByte(tx_byte1, tx_byte2);
	}
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
	case 1: currentGameState = RUNNING;
	case 2: currentGameState = STOP;
	case 3: currentGameState = SCORE_DEATH;
	case 4: currentGameState = LIVE_SCORE;
	default : currentGameState = STOP;
	}
}
