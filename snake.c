#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

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
    //na kontrolu ktory had sa ma vykreslit
    SNAKE_TYPE type;
    int length;
    int score;
} SNAKE;

typedef struct food
{
    POSITION position;
} FOOD;

//player pridany aby sa vedelo ktoreho hada otocit
//TODO: Pripomenu, že existuje aj druhy hadik + vyriešiť dokreslenie druheho hadika
void InitMap(char map[WIDTH][HEIGHT], SNAKE * snake,SNAKE * snake2, FOOD food, DIRECTION * direction, int player)
{
    //Vykreslenie mapy
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            map[i][j] = EMPTY;
        }
    }

    //Vykreslenie hlavy
    switch (*direction)
    {
        case UP:
            if (player == 1){
            map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_UP;}
            if (player == 2){
                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_UP;
            }
            if (player == 100){
                map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_UP;
                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_UP;
            }
            break;
        case DOWN:
            if (player == 1){
            map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_DOWN;}
            if (player == 2){
                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_DOWN;
            }
            if (player == 100){
                map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_DOWN;
                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_DOWN;
            }
            break;
        case RIGHT:
            if (player == 1){
            map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_RIGHT;}
            if (player == 2){
                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_RIGHT;
            }
            if (player == 100){
                map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_RIGHT;
                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_RIGHT;
            }
            break;
        case LEFT:
            if (player == 1){
            map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_LEFT;}
            if (player == 2){
                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_LEFT;
            }
            if (player == 100){
                map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_LEFT;
                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_LEFT;
            }
            break;
        default:
            break;
    }

    //Vykreslenie tela
    if (snake->type == SERVER){
        for (int i = 1; i < snake->length; i++) {
            map[snake->position[i].y][snake->position[i].x] = SNAKE_BODY;
        }
    }
     if (snake->type == KLIENT){
        for (int i = 1; i < snake2->length; i++) {
            map[snake->position[i].y][snake->position[i].x] = SNAKE_BODY_2;
        }
    }

    //Vykreslenie jedla
    map[food.position.y][food.position.x] = FOOD_TY;
}

void Movement(SNAKE * snake)
{
    for (int i = snake->length - 1; i > 0; i--) {
        snake->position[i] = snake->position[i - 1];
    }
    if (snake->direction == UP)
    {
        printf("Hore\n");
        snake->position[0].y--;
    }
    else if (snake->direction == DOWN)
    {
        printf("Dole\n");
        snake->position[0].y++;
    }
    else if (snake->direction == LEFT)
    {
        printf("Vlavo\n");
        snake->position[0].x--;
    }
    else if (snake->direction == RIGHT)
    {
        printf("Vpravo\n");
        snake->position[0].x++;
    }
}

void InputKeyboard(SNAKE * snake)
{
    //Vkladanie pohybu z klavesnice + kontrola
    int c = getchar();
    getchar();
    //co ak nezadal nic? - myslim si ze preto to pokracuje s vypisom nespravna klavesa

    if (c == 'w')
    {
        if (snake->direction != DOWN)
        {
            snake->direction = UP;
        }
        else
        {
            printf("Nie je mozne vykonat z pohladu DOLE na pohlad HORE\n");
        }
    }
    else if (c == 'd')
    {
        if (snake->direction != LEFT)
        {
            snake->direction = RIGHT;
        }
        else
        {
            printf("Nie je mozne vykonat z pohladu ZLAVA na pohlad DOPRAVA\n");
        }
    }
    else if (c == 'a')
    {
        if (snake->direction != RIGHT)
        {
            snake->direction = LEFT;
        }
        else
        {
            printf("Nie je mozne vykonat z pohladu ZPRAVA na pohlad DOLAVA\n");
        }
    }
    else if (c == 's')
    {
        if (snake->direction != UP)
        {
            snake->direction = DOWN;
        }
        else
        {
            printf("Nie je mozne vykonat z pohladu ZHORA na pohlad DOLE\n");
        }
    }
    else
    {
        printf("Zadana klavesa nie je spravna\n");
    }
}

bool CheckCollision(SNAKE snake)
{
    //Kontrola narazu s hranicami
    if (snake.position[0].x < 0 || snake.position[0].y < 0 || snake.position[0].x >= WIDTH || snake.position[0].y >= HEIGHT)
    {
        return true;
    }

    //Kontrola narazu s telom
    for (int i = 1; i < snake.length; i++)
    {
        if (snake.position[0].x == snake.position[i].x && snake.position[0].y == snake.position[i].y)
        {
            printf("Hadik narazil do svojho tela\n");
            return true;
        }
    }

    return false;
}

bool CheckCollisionWithFood(SNAKE snake, FOOD food)
{
    //Kontrola narazu s jedlom
    if (snake.position[0].x == food.position.x && snake.position[0].y == food.position.y)
    {
        printf("Hadik zjedol jedlo\n");
        return true;
    }
    return false;
}


int main(void)
{
    int snake1crash = 0;
    int snake2crash = 0;
    srand(time(NULL));

    //prerabka na smernik pokus zbavit sa segmentation fault --smernik nebol spravne riesenie
    SNAKE snake, snake2;

    snake.length = 3;
    snake.score = 0;

    snake2.length = 3;
    snake2.score = 0;

    snake.direction = UP;
    snake2.direction = UP;

    snake.type = SERVER;
    snake2.type = KLIENT;

    snake.position[0].x = WIDTH / 2;
    snake.position[0].y = HEIGHT / 2;

    snake2.position[0].x = (WIDTH / 2) + 3;
    snake2.position[0].y = HEIGHT / 2;

    //prvotne nastavenie prvych pozicii tela
    for (int i = 1; i < snake.length; ++i) {
        snake.position[i].x = snake.position[i-1].x;
        snake.position[i].y = snake.position[i-1].y + 1;
    }
    for (int i = 1; i < snake2.length; ++i) {
        snake2.position[i].x = snake2.position[i-1].x;
        snake2.position[i].y = snake2.position[i-1].y + 1;
    }

    FOOD food;
    food.position.x = rand() % WIDTH;
    food.position.y = rand() % HEIGHT;

    char map[HEIGHT][WIDTH];
    //prva inicializacia vykresli oboch rovnako
    InitMap(map, &snake,&snake2, food, &snake.direction, 100);
    while (true)
    {
        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                printf("%c", map[i][j]);
            }
            printf("\n");
        }

        printf("Narade je prvy hrac\n");
        InputKeyboard(&snake);
        Movement(&snake);

        //toto bude treba inak lebo druhy hrac bude este moct predsa hrat
        if (CheckCollision(snake) && snake1crash == 0)
        {
            snake1crash = 1;
        }

        if (CheckCollisionWithFood(snake, food))
        {
            food.position.x = rand() % WIDTH;
            food.position.y = rand() % HEIGHT;

            snake.length++;
            snake.score++;
        }

        InitMap(map, &snake,&snake2, food, &snake.direction, 1);

        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                printf("%c", map[i][j]);
            }
            printf("\n");
        }

        //pohyb bude musiet byt oddelene si myslim
        printf("Narade je druhy hrac\n");
        InputKeyboard(&snake2);
        Movement(&snake2);

        if (CheckCollision(snake2) && snake2crash == 0)
        {
            snake2crash = 1;
        }

        if (CheckCollisionWithFood(snake2, food))
        {
            food.position.x = rand() % WIDTH;
            food.position.y = rand() % HEIGHT;

            snake2.length++;
            snake2.score++;
        }

        if (snake1crash == 1 && snake2crash == 1) {
            printf("Oba hadiky zomreli\nGAME OVER!!!");
            break;
        }

        InitMap(map, &snake,&snake2, food, &snake.direction, 2);
    }

    return 0;
}