#ifndef HADIK_SEMESTRALNA_PRACA_GAME_SNAKE_H
#define HADIK_SEMESTRALNA_PRACA_GAME_SNAKE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define WIDTH 20
#define HEIGHT 20

#define SNAKE_HEAD_UP		'^'
#define SNAKE_HEAD_DOWN		'V'
#define SNAKE_HEAD_LEFT		'<'
#define SNAKE_HEAD_RIGHT	'>'
#define SNAKE_BODY			'O'
#define FOOD_TY				'*'
#define EMPTY				'.'

#define SNAKE_BODY_2        '8'

typedef struct position
{
    int x;
    int y;
} POSITION;

typedef enum direction
{
    UP, DOWN, RIGHT, LEFT
} DIRECTION;

typedef enum snake_type{
    SERVER, KLIENT
}SNAKE_TYPE;

typedef struct snake
{
    POSITION position[100];
    DIRECTION direction;
    SNAKE_TYPE type;
    int score;
    int snakeLength;
} SNAKE;

typedef struct snakeP
{
    int score;
    int snakeLength;
} SNAKEP;

typedef struct food
{
    POSITION position;
} FOOD;

typedef struct food_spawner
{
    pthread_cond_t* signal;
    pthread_mutex_t* mutex;
    FOOD* food;
    bool is_spawned;
} SPAWN_DATA;

void drawOtherSnakeHead(SNAKE * snake, char map[HEIGHT][WIDTH]);
void InitMap(char map[HEIGHT][WIDTH], SNAKE * snake,SNAKE * snake2, FOOD food, DIRECTION * direction, int player);
void Movement(SNAKE * snake);
void InputKeyboard(SNAKE * snake, int sock, bool recieving);
bool CheckCollision(SNAKE snake, SNAKE snake2);
bool CheckCollisionWithFood(SNAKE snake, FOOD food);
void placeNewBodyPart(SNAKE * snake);
int gameplay(int sock, bool is_server);
void* food_spawn_thread(void* data);

#endif //HADIK_SEMESTRALNA_PRACA_GAME_SNAKE_H
