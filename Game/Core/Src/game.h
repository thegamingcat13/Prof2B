#include <stdbool.h>
#include <stdint.h> // For uint8_t
#include "usb_host.h"
#include "math.h"

#define MAX_ENEMYS 4
#define OBSTACLE_SPAWN_Y 320
#define PLAYER_Y_POS 370
#define ENEMY_END 400
#define TICK_SPEED 100

#define RIGHT 1
#define LEFT 2

#define RUN 1
#define HALT 2
#define POINTS_DEATH 3
#define POINTS_LIVE 4

#define INTERVAL 1000

#define N 70.0f // Aantal bins
#define FS 7000.0f // Sample rate

extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim5;
extern RNG_HandleTypeDef hrng;
extern ADC_HandleTypeDef hadc2;

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

extern volatile int dft_ready;
extern int left;
extern int right;
extern volatile int start;

extern volatile int Do_Game_Tick;
extern volatile int cycle_count_enemy;
extern int volatile cycleCountPlayer;
extern volatile int cycle_start_stop;

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
extern void dft_inter(void);
extern void DFT(void);
extern void init_blackman(void);
extern int PlayerMovement(int*, int*);
