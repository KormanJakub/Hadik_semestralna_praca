#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#define WIDTH 20
#define HEIGHT 20

#define SNAKE_HEAD_UP		'^'
#define SNAKE_HEAD_DOWN		'V'
#define SNAKE_HEAD_LEFT		'<'
#define SNAKE_HEAD_RIGHT	'>'
#define SNAKE_BODY			'O'
#define FOOD_TY				'*'
#define EMPTY				'.'

#define SNAKE_BODY_2 '§'

typedef struct position
{
    int x;
    int y;
} POSITION;

typedef enum direction
{
    UP, DOWN, RIGHT, LEFT
} DIRECTION;

typedef struct snake
{
    POSITION position[100];
    DIRECTION direction;
    int length;
    int score;
} SNAKE;

typedef struct food
{
    POSITION position;
} FOOD;

void InitMap(char map[WIDTH][HEIGHT], SNAKE * snake, FOOD food, DIRECTION * direction)
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
            map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_UP;
            break;
        case DOWN:
            map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_DOWN;
            break;
        case RIGHT:
            map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_RIGHT;
            break;
        case LEFT:
            map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_LEFT;
            break;
        default:
            break;
    }

    //Vykreslenie tela
    //pravdepodobne treba nastavit pociatocnu hodnotu x a y lebo na pozicii 1 je x -136349896 a y 32767
    for (int i = 1; i < snake->length; i++) {
        map[snake->position[i].y][snake->position[i].x] = SNAKE_BODY;

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
    srand(time(NULL));

    //prerabka na smernik pokus zbavit sa segmentation fault --smernik nebol spravne riesenie
    SNAKE snake;
    snake.length = 3;
    snake.score = 0;
    snake.direction = UP;
    snake.position[0].x = WIDTH / 2;
    snake.position[0].y = HEIGHT / 2;

    //prvotne nastavenie prvych pozicii tela - uz nevyhadzuje segmentation fault
    for (int i = 1; i < snake.length; ++i) {
        snake.position[i].x = snake.position[i-1].x;
        snake.position[i].y = snake.position[i-1].y + 1;
    }

    FOOD food;
    food.position.x = rand() % WIDTH;
    food.position.y = rand() % HEIGHT;

    DIRECTION direction = UP;

    char map[HEIGHT][WIDTH];
    InitMap(map, &snake, food, &snake.direction);
    while (true)
    {


        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                printf("%c", map[i][j]);
            }
            printf("\n");
        }

        InputKeyboard(&snake);
        Movement(&snake);

        if (CheckCollision(snake))
        {
            break;
        }

        if (CheckCollisionWithFood(snake, food))
        {
            food.position.x = rand() % WIDTH;
            food.position.y = rand() % HEIGHT;

            snake.length++;
            snake.score++;
        }
        InitMap(map, &snake, food, &snake.direction);
    }

    return 0;
}