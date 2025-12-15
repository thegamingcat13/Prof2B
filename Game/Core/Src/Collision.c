#include "game.h"

bool Collision()
{
	bool collided = false;
	for (int i = 0; i < MAX_ENEMYS; i++)
	{
		if (Player.lane == Enemy[i].lane)
		{
			if (PLAYER_Y_POS - Enemy[i].yPosition <= 0)
				collided = true;
		}
	}
	return collided;
}
