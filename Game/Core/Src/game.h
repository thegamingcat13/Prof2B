#include <stdbool.h>
#include <stdint.h> // For uint8_t
#include "usb_host.h"

#define MAX_ENEMYS 4
#define OBSTACLE_SPAWN_Y 0
#define PLAYER_Y_POS 370
#define TICK_SPEED 100

#define RIGHT 1
#define LEFT 2

#define RUN 1
#define HALT 2
#define POINTS_DEATH 3
#define POINTS_LIVE 4

extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim3;

typedef struct {
    int lane;
    int yPosition;
    bool isActive;
} ObstacleCar;

typedef struct {
	int lane;
	bool isActive;
} PlayerCar;

typedef enum {
	RUNNING = 0x08,
	STOP = 0x0C,
	SCORE_DEATH = 0x0E,
} GameState_t;

extern PlayerCar Player;
extern ObstacleCar Enemy[MAX_ENEMYS];
extern GameState_t currentGameState;

extern uint8_t NewEnemyMask;
extern int PixelsMoved;

extern uint8_t tx_byte1;
extern uint8_t tx_byte2;

extern uint8_t current_NewEnemyMask;

extern uint16_t score;

extern bool clock_high;

extern void init(void);
extern void gameState(int);
extern uint8_t EnemyCarGenerator(void);
extern bool addNewEnemy(int);
extern void processNewEnemyMask(uint8_t*);
extern void CreateBytes (uint8_t*, uint8_t*, bool*);
extern void TransmitByte(uint8_t, uint8_t);
extern void gameTick(void);
extern bool Collision(void);
extern bool Clock_change(int*);
