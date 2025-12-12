#include "game.h"

PlayerCar Player;
ObstacleCar Enemy[MAX_ENEMYS];
GameState_t currentGameState;

uint8_t NewEnemyMask = 0x00;

uint8_t tx_byte1;
uint8_t tx_byte2;

uint8_t current_NewEnemyMask;

void gameTick ()
{
	current_NewEnemyMask = EnemyCarGenerator();
	processNewEnemyMask(current_NewEnemyMask);
	NewEnemyMask = current_NewEnemyMask;

	CreateBytes (&tx_byte1, &tx_byte2);

	TransmitByte(tx_byte1);
	TransmitByte(tx_byte2);

	NewEnemyMask = 0x00;
}

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
