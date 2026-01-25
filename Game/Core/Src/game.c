#include "game.h"

PlayerCar Player;
ObstacleCar Enemy[MAX_ENEMYS];
GameState_t currentGameState;

uint8_t NewEnemyMask = 0x00;

uint8_t tx_byte1;
uint8_t tx_byte2;

uint8_t current_NewEnemyMask = 0x00;

uint16_t score = 0;

int Speed_140 = 140;
int Speed_160 = 160;

volatile bool collisionEnabled = false;

bool coll_detect = false;

// Function gameTick
// Developer: Sander van Beek
// Input: None
// Output: None
// This function runs one gameTick, and makes sure that everything that needs to run for a tick runs.
void gameTick ()
{
	if (dft_ready == 1)
	{
		DFT();

//		PlayerMovement(&left, &right);

		if (cycleCountPlayer >= 30)
		{
			if (PlayerMovement(&left, &right) == 1)
				cycleCountPlayer = 0;
		}

		if (start == 1)
		{
			gameState(RUN);
		}

		dft_ready = 0;
	}

	// Make sure we didn't already die
	if (!(currentGameState == SCORE_DEATH))
	{
		// Check for collision
		coll_detect = (collisionEnabled) ? Collision() : false;
	}

	if (start == 1)
	{

		// Make choice based on collision
		switch (coll_detect)
		{
		// Not collided
		case false:
			// Increase score and make sure it doesn't exceed the max
			score++;
			score &= 0x0FFF;

			if (score == 500)
			{
				// Change clock speed to 140hz
				bool Clock_valid = Clock_change(&Speed_140);
				// Check if clock change succeeded
				switch (Clock_valid)
				{
				// if clock change failed end game
				case false:
					gameState(POINTS_DEATH);
					bool dummy_collision = true;
					CreateBytes (&tx_byte2, &tx_byte2, &dummy_collision);
					TransmitByte(tx_byte1, tx_byte2);
					break;
				// if clock change succeeded continue
				case true: break;
				}

			}

			if (score == 1000)
			{
				// Change clock speed to 160hz
				bool Clock_valid = Clock_change(&Speed_160);
				// Check if clock change succeeded
				switch (Clock_valid)
				{
				// if clock change failed end game
				case false:
					gameState(POINTS_DEATH);
					bool dummy_collision = true;
					CreateBytes (&tx_byte2, &tx_byte2, &dummy_collision);
					TransmitByte(tx_byte1, tx_byte2);
					break;
					// if clock change succeeded continue
				case true: break;
				}
			}

			if (cycle_count_enemy >= 120)
			{
				cycle_count_enemy = 0;

				// Generate new enemies
				current_NewEnemyMask = EnemyCarGenerator();
				processNewEnemyMask(&current_NewEnemyMask);
				NewEnemyMask = current_NewEnemyMask;
			}

			// Create the 2 bytes necessary for FPGA communication
			CreateBytes (&tx_byte1, &tx_byte2, &coll_detect);

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
	case 1: currentGameState = RUNNING; break;
	case 2: currentGameState = STOP; break;
	case 3: currentGameState = SCORE_DEATH; break;
	default : currentGameState = STOP; break;
	}
}
