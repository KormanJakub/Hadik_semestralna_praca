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

void InitMap(char map[WIDTH][HEIGHT], SNAKE snake, FOOD food, DIRECTION direction)
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
    switch (direction)
    {
        case UP:
            map[snake.position[0].y][snake.position[0].x] = SNAKE_HEAD_UP;
            break;
        case DOWN:
            map[snake.position[0].y][snake.position[0].x] = SNAKE_HEAD_DOWN;
            break;
        case RIGHT:
            map[snake.position[0].y][snake.position[0].x] = SNAKE_HEAD_RIGHT;
            break;
        case LEFT:
            map[snake.position[0].y][snake.position[0].x] = SNAKE_HEAD_LEFT;
            break;
    }

    //Vykreslenie tela
    //pravdepodobne treba nastavit pociatocnu hodnotu x a y lebo na pozicii 1 je x -136349896 a y 32767
    for (int i = 1; i < snake.length; i++) {
        map[snake.position[i].y][snake.position[i].x] = SNAKE_BODY;
    }


    //Vykreslenie jedla
    map[food.position.y][food.position.x] = FOOD_TY;
}

void Movement(SNAKE snake)
{
    for (int i = snake.length - 1; i > 0; i--) {
        snake.position[i] = snake.position[i - 1];
    }

    if (snake.direction == UP)
    {
        snake.position[0].y--;
    }
    else if (snake.direction == DOWN)
    {
        snake.position[0].y++;
    }
    else if (snake.direction == LEFT)
    {
        snake.position[0].x--;
    }
    else if (snake.direction == RIGHT)
    {
        snake.position[0].x++;
    }
}

void InputKeyboard(SNAKE snake)
{
    //Vkladanie pohybu z klavesnice + kontrola
    int c = getchar();
    switch (c) {
        case 'w':
            if (snake.direction != DOWN)
            {
                snake.direction = UP;
            }
            else
            {
                printf("Nie je mozne vykonat z pohladu DOLE na pohlad HORE\n");
            }
            break;
        case 'd':
            if (snake.direction != LEFT)
            {
                snake.direction = RIGHT;
            }
            else
            {
                printf("Nie je mozne vykonat z pohladu ZLAVA na pohlad DOPRAVA\n");
            }
            break;
        case 'a':
            if (snake.direction != RIGHT)
            {
                snake.direction = LEFT;
            }
            else
            {
                printf("Nie je mozne vykonat z pohladu ZPRAVA na pohlad DOLAVA\n");
            }
            break;
        case 's':
            if (snake.direction != UP)
            {
                snake.direction = DOWN;
            }
            else
            {
                printf("Nie je mozne vykonat z pohladu ZHORA na pohlad DOLE\n");
            }
            break;
        default:
            printf("Zadana klavesa nie je spravna\n");
            break;

    }
    /*if (c == 'w')
    {
        if (snake.direction != DOWN)
        {
            snake.direction = UP;
        }
        else
        {
            printf("Nie je mozne vykonat z pohladu DOLE na pohlad HORE\n");
        }
    }
    else if (c == 'd')
    {
        if (snake.direction != LEFT)
        {
            snake.direction = RIGHT;
        }
        else
        {
            printf("Nie je mozne vykonat z pohladu ZLAVA na pohlad DOPRAVA\n");
        }
    }
    else if (c == 'a')
    {
        if (snake.direction != RIGHT)
        {
            snake.direction = LEFT;
        }
        else
        {
            printf("Nie je mozne vykonat z pohladu ZPRAVA na pohlad DOLAVA\n");
        }
    }
    else if (c == 's')
    {
        if (snake.direction != UP)
        {
            snake.direction = DOWN;
        }
        else
        {
            printf("Nie je mozne vykonat z pohladu ZHORA na pohlad DOLE\n");
        }
    }
    else
    {
        printf("Zadana klavesa nie je spravna\n");
    }*/
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

    SNAKE snake;
    snake.length = 3;
    snake.score = 0;
    snake.direction = RIGHT;
    snake.position[0].x = WIDTH / 2;
    snake.position[0].y = HEIGHT / 2;

    FOOD food;
    food.position.x = rand() % WIDTH;
    food.position.y = rand() % HEIGHT;

    DIRECTION direction = UP;

    char map[HEIGHT][WIDTH];

    while (true)
    {
        InitMap(map, snake, food, direction);

        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                printf("%c", map[i][j]);
            }
            printf("\n");
        }

        InputKeyboard(snake);
        Movement(snake);

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
    }

    return 0;
}