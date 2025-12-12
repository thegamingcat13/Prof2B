#include "game.h"

// Function: CreateBytes
// Developer: Sander van Beek
// Input uint8_t (pointer) Byte1 & Byte2
// Output: None
// This function reads the necessary data and compiles it into the data protocol separated in two bytes
void CreateBytes (uint8_t* byte1, uint8_t* byte2)
{
	//initialize byte1 and byte2 to 0000
	*byte1 = 0;
	*byte2 = 0;

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
	HAL_UART_Transmit(&huart3, &transmit_bytes, 2, HAL_MAX_DELAY);
}
