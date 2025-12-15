#include "game.h"

// Function: CreateBytes
// Developer: Sander van Beek
// Input uint8_t (pointer) Byte1 & (pointer) Byte2 & bool collision
// Output: None
// This function reads the necessary data and compiles it into the data protocol separated in two bytes
// The output of the function differs whether or not we want to transmit a score or not
void CreateBytes (uint8_t* byte1, uint8_t* byte2, bool* collision)
{
	//initialize byte1 and byte2 to 0000
	*byte1 = 0x00;
	*byte2 = 0x00;

	switch (*collision)
	{
	case false:
		// Place the gameState and new enemy locations into the first byte
		*byte1 |= ((currentGameState & 0x0F) << 4);
		*byte1 |= (NewEnemyMask & 0x0F);

		//Place the player location into the second byte
		switch (Player.lane)
		{
		case 0: *byte2 |= ((0x08 & 0x0F) << 4); break;
		case 1: *byte2 |= ((0x04 & 0x0F) << 4); break;
		case 2: *byte2 |= ((0x02 & 0x0F) << 4); break;
		case 3: *byte2 |= ((0x01 & 0x0F) << 4); break;
		default: break;
		}
		break;
	case true:
		uint8_t score1 = 0x00;
		uint8_t score2 = 0x00;

		score1 = (uint8_t)score >> 8;
		score1 = score1 & 0x0F;
		score2 = (uint8_t)score & 0xFF;

		*byte1 |= ((currentGameState & 0x0F) << 4);
		*byte1 |= (score1 & 0x0F);

		*byte2 |= score2;
		// Hier komt Score logic
	}
}

// Function: TransmitByte
// Developer: Sander van Beek
// Input uint8_t byte
// Output: None
// This function sends the bytes from the CreateBytes() function to the FPGA over UART
void TransmitByte(uint8_t byte1, uint8_t byte2)
{
	uint8_t transmit_bytes[2];

	transmit_bytes[0] = byte1;
	transmit_bytes[1] = byte2;
	HAL_UART_Transmit_DMA(&huart3, transmit_bytes, 2);
}
