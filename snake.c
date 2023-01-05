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

void drawOtherSnakeHead(SNAKE * snake, char map[WIDTH][HEIGHT]){
    printf("?????????? INSIDE DRAW OTHER 56 ????????????????????\n");
    switch (snake->direction) {
        case UP:
            map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_UP;
            break;
        case DOWN:
            map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_DOWN;
            break;
        case LEFT:
            map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_LEFT;
            break;
        case RIGHT:
            map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_RIGHT;
            break;

    }
    printf("?????????? AFTER DRAW OTHER 56 ????????????????????\n");

}

//player pridany aby sa vedelo ktoreho hada otocit
//TODO: Pripomenu, že existuje aj druhy hadik + vyriešiť dokreslenie druheho hadika
void InitMap(char map[WIDTH][HEIGHT], SNAKE * snake,SNAKE * snake2, FOOD food, DIRECTION * direction, int player)
{

    //Vykreslenie mapy
    for (int i = 0; i < WIDTH; i++)
    {
        printf("??????????actual I:%d ????????????????????\n",i);
        for (int j = 0; j < HEIGHT; j++)
        {
            printf("??????????actual J:%d ????????????????????\n",i);
            map[i][j] = EMPTY;
            printf("??????????actual J:%d ????????????????????\n",j);
        }
    }

    //Vykreslenie hlavy
    switch (*direction)
    {
        case UP:
            if (player == 1){

                map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_UP;
                drawOtherSnakeHead(snake2, map);
            }
            if (player == 2){

                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_UP;
                drawOtherSnakeHead(snake, map);
            }
            if (player == 100){
                map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_UP;
                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_UP;
            }
            break;
        case DOWN:
            if (player == 1){

                map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_DOWN;
                drawOtherSnakeHead(snake2, map);
               }
            if (player == 2){

                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_DOWN;
                drawOtherSnakeHead(snake, map);
            }
            if (player == 100){
                map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_DOWN;
                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_DOWN;
            }
            break;
        case RIGHT:
            if (player == 1){

                map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_RIGHT;
                drawOtherSnakeHead(snake2, map);
            }
            if (player == 2){

                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_RIGHT;
                drawOtherSnakeHead(snake, map);
            }
            if (player == 100){
                map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_RIGHT;
                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_RIGHT;
            }
            break;
        case LEFT:
            if (player == 1){

                map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_LEFT;
                drawOtherSnakeHead(snake2, map);
            }
            if (player == 2){

                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_LEFT;
                drawOtherSnakeHead(snake, map);
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
    //if (snake->type == SERVER){
    printf("?????????? PAINT MY BODY ????????????????????\n");
    for (int i = 1; i < snake->snakeLength; i++) {
        printf("?????????? PAINT MY BODY SNAKE 1 BEGIN : %d ????????????????????\n", i);

            int posY = snake->position[i].y;
        int posX = snake->position[i].x;
        printf("?????????? PAINT MY BODY SNAKE 1 posY : %d ????????????????????\n", posY);
        printf("?????????? PAINT MY BODY SNAKE 1 posX : %d ????????????????????\n", posX);
            map[posY][posX] = SNAKE_BODY;
        printf("?????????? PAINT MY BODY SNAKE 1 END : %d ????????????????????\n", i);

    }
    //}
     //if (snake->type == KLIENT){
    //printf("?????????? PAINT MY BODY SNAKE 2 BEGIN  ????????????????????\n");

    for (int i = 1; i < snake2->snakeLength; i++) {
            printf("?????????? PAINT MY BODY BODY SNAKE 2 : %d ????????????????????\n", i);
            map[snake2->position[i].y][snake2->position[i].x] = SNAKE_BODY_2;
        }
    //}
    printf("?????????? FULL PAINT FOOD BEGIN ????????????????????\n");

    //Vykreslenie jedla
    map[food.position.y][food.position.x] = FOOD_TY;
    printf("?????????? FULL PAINT FOOD END ????????????????????\n");

}

void Movement(SNAKE * snake)
{
    for (int i = snake->snakeLength - 1; i > 0; i--) {
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

bool CheckCollision(SNAKE snake, SNAKE snake2)
{
    //Kontrola narazu s hranicami
    if (snake.position[0].x < 0 || snake.position[0].y < 0 || snake.position[0].x >= WIDTH || snake.position[0].y >= HEIGHT)
    {
        return true;
    }

    //Kontrola narazu s telom
    for (int i = 1; i < snake.snakeLength; i++)
    {
        if (snake.position[0].x == snake.position[i].x && snake.position[0].y == snake.position[i].y)
        {
            printf("Hadik narazil do svojho tela\n");
            return true;
        }
    }
//TODO: skontrollovat ci umru pri narazoch hlavy
    for (int i = 0; i < snake2.snakeLength; i++)
    {
        if (snake.position[0].x == snake2.position[i].x && snake.position[0].y == snake2.position[i].y)
        {
            printf("Hadik narazil do druheho hada\n");
            return true;
        }
    }

    return false;
}

bool CheckCollisionWithFood(SNAKE snake, FOOD food)
{
    printf("Had %u sa snazi zjest jedlo\n", snake.type);
    //Kontrola narazu s jedlom
    if (snake.position[0].x == food.position.x && snake.position[0].y == food.position.y)
    {
        printf("Hadik zjedol jedlo\n");
        return true;
    }
    return false;
}

void placeNewBodyPart(SNAKE * snake){
    //ak si na hranici x tak x bude rovnake ale y ine

    if (snake->position[snake->snakeLength-2].x == WIDTH - 1){
        //ak je v pravom hornom rohu
        if  ( snake->position[snake->snakeLength-2].y == 0 ) {
            //ak je aj zvysok tela v pravom stlpci
            if (snake->position[snake->snakeLength - 3].x == WIDTH - 1) {
                snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x - 1;
                snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y;
            } else {
                //ak je zvysok v hornom riadku
                snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x;
                snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y+1;
            }

        } else if(snake->position[snake->snakeLength-2].y == HEIGHT - 1){
            if (snake->position[snake->snakeLength - 3].x == WIDTH - 1) {
                snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x - 1;
                snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y;
            } else {
                //ak je zvysok v hornom riadku
                snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x;
                snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y-1;
            }
            //ak su v rovnako stlpci
        } else if(snake->position[snake->snakeLength - 2].x  ==  snake->position[snake->snakeLength - 3].x ){
            //ak je predposledna cast nizsie teda had smeruje dole
            if (snake->position[snake->snakeLength - 2].y  >  snake->position[snake->snakeLength - 3].y){
                snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x;
                snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y-1;
            }else {
                //ak smeruje had hore
                snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x;
                snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y+1;
            }
        }
        //ak je y ne dolnej hranici tak sa to musi vykreslit bokom
    }else if(snake->position[snake->snakeLength-2].x == 0){
        //ak je v lavom hornom rohu
        if  ( snake->position[snake->snakeLength-2].y == 0 ) {
            //ak je aj zvysok tela v pravom stlpci
            if (snake->position[snake->snakeLength - 3].x == 0) {
                snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x + 1;
                snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y;
            } else {
                //ak je zvysok v hornom riadku
                snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x;
                snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y+1;
            }
            //ak je v lavom dolnom rohu
        } else if(snake->position[snake->snakeLength-2].y == HEIGHT - 1){
            if (snake->position[snake->snakeLength - 3].x == 0) {
                snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x + 1;
                snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y;
            } else {
                //ak je zvysok v dolnom riadku
                snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x;
                snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y-1;
            }
            //ak su v rovnako stlpci
        } else if(snake->position[snake->snakeLength - 2].x  ==  snake->position[snake->snakeLength - 3].x ){
            //ak je predposledna cast nizsie teda had smeruje dole
            if (snake->position[snake->snakeLength - 2].y  >  snake->position[snake->snakeLength - 3].y){
                snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x;
                snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y-1;
            }else {
                //ak smeruje had hore
                snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x;
                snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y+1;
            }
        }else{
            snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x;
            snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y+1;
        }
    } else{
        if(snake->position[snake->snakeLength-2].y == 0){
            //rohy su vyriesene vyssie
            if (snake->position[snake->snakeLength-2].y == snake->position[snake->snakeLength-3].y){
                //ak je
                if (snake->position[snake->snakeLength-2].x > snake->position[snake->snakeLength-3].x){
                    snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x + 1;
                    snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y;
                } else{
                    snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x - 1;
                    snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y;
                }

            } else{
                snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x - 1;
                snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y;
            }
        }else if(snake->position[snake->snakeLength-2].y == HEIGHT - 1){
            //rohy su vyriesene vyssie
            if (snake->position[snake->snakeLength-2].y == snake->position[snake->snakeLength-3].y){
                //ak je//TODO:skontrolovať
                if (snake->position[snake->snakeLength-2].x > snake->position[snake->snakeLength-3].x){
                    snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x + 1;
                    snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y;
                } else{
                    //TODO:skontrolovať
                    snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x - 1;
                    snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y;
                }

            } else {
                snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x - 1;
                snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y;
            }
            //ak sa nerovnaju ani riadky ani stlpce
        } else {
            //ak su v rovnakom riadku
            if ( snake->position[snake->snakeLength - 2].y == snake->position[snake->snakeLength - 3].y){
                //ide had do prava
                if(snake->position[snake->snakeLength - 2].x < snake->position[snake->snakeLength - 3].x){
                    snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x - 1;
                    snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y;
                } else{
                    //had ide do lava
                    snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x + 1;
                    snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y;
                }
                //ak su v jednom stlpci
            } else if (snake->position[snake->snakeLength - 2].x == snake->position[snake->snakeLength - 3].x){
                if(snake->position[snake->snakeLength - 2].y < snake->position[snake->snakeLength - 3].y){
                    snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x;
                    snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y-1;
                } else{
                    //had ide do lava
                    snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x;
                    snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y+1;
                }
            }
            printf("Dostal som suradnice!!!!");
            /*printf("Dostal som sa k switchu!!!!!");
            switch (snake->direction) {
                case UP:
                    snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x;
                    snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y+1;
                    break;
                case DOWN:
                    snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x;
                    snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y-1;
                    break;
                case LEFT:
                    snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x+1;
                    snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y;
                    break;
                case RIGHT:
                    snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x-1;
                    snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y;
                    break;
            }*/
        }
    }
}

int main(void)
{
    int snake1crash = 0;
    int snake2crash = 0;
    srand(time(NULL));

    //prerabka na smernik pokus zbavit sa segmentation fault --smernik nebol spravne riesenie
    SNAKE snake, snake2;
    SNAKEP snakep;

    snakep.snakeLength = 2;
    snakep.score = 0;

    snake.snakeLength = 3;
//    ++snake.snakeLength;
//    ++snake.snakeLength;
//    ++snake.snakeLength;
//    ++snake.snakeLength;
//    ++snake.snakeLength;
//    ++snake.snakeLength;
    snake.score = 0;

    snake2.snakeLength = 3;
//    snake2.snakeLength++;
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
    for (int i = 1; i < snake.snakeLength; ++i) {
        snake.position[i].x = snake.position[i-1].x;
        snake.position[i].y = snake.position[i-1].y + 1;
    }
    for (int i = 1; i < snake2.snakeLength; ++i) {
        snake2.position[i].x = snake2.position[i-1].x;
        snake2.position[i].y = snake2.position[i-1].y + 1;
    }

    FOOD food;
    food.position.x = rand() % WIDTH;
    food.position.y = rand() % HEIGHT;

    char map[HEIGHT][WIDTH];
    //prva inicializacia vykresli oboch rovnako
    InitMap(map, &snake,&snake2, food, &snake.direction, 100);
//    snake.snakeLength++;

    printf("CHCEM INFO AKY JE HAD\n");
    for (int i = 0; i < snake.snakeLength; ++i) {
        printf("HAD 1 poradove cislo: %d posX: %d\n", i, snake.position[i].x);
        printf("HAD 1 poradove cislo: %d posY: %d\n", i, snake.position[i].y);
    }
    for (int i = 0; i < snake2.snakeLength; ++i) {
        printf("HAD 2 poradove cislo: %d posX: %d\n", i, snake2.position[i].x);
        printf("HAD 2 poradove cislo: %d posY: %d\n", i, snake2.position[i].y);
    }


    while (true)
    {
        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                printf("%c", map[i][j]);
            }
            printf("\n");
        }

//        snake.snakeLength = snake.snakeLength + 1;

      if(snake1crash == 0)
      {
            printf("Narade je prvy hrac\n");
            InputKeyboard(&snake);
            Movement(&snake);

            //toto bude treba inak lebo druhy hrac bude este moct predsa hrat
            if (CheckCollision(snake, snake2))
            {
                snake1crash = 1;
            }

//            if (CheckCollisionWithFood(snake, food))
            if (true)
            {
//                snake.snakeLength++;

                printf("HAD1: dostal som sa do jedenia");
                food.position.x = rand() % WIDTH;
                food.position.y = rand() % HEIGHT;

               printf("\n%d\n", snake.snakeLength);
                int snk = snake.snakeLength;
                snk = snk + 1;
                snake.snakeLength = snk;
                printf("??????????%d????????????????????\n",snake.snakeLength );
//TODO:TU TO TREBA TAKTO NAINICIALIZOVAŤ!!!! takto všetko

               //TODO TU VOLAT TU METODU
                placeNewBodyPart(&snake);
                if (snake.position[snake.snakeLength-2].x == 0){

                }
             /*   if (snake.position[snake.snakeLength-2].x == WIDTH - 1){
                    //ak je v pravom hornom rohu
                    if  ( snake.position[snake.snakeLength-2].y == 0 ) {
                        //ak je aj zvysok tela v pravom stlpci
                        if (snake.position[snake.snakeLength - 3].x == WIDTH - 1) {
                            snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x - 1;
                            snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y;
                        } else {
                            //ak je zvysok v hornom riadku
                            snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x;
                            snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y+1;
                        }

                    } else if(snake.position[snake.snakeLength-2].y == HEIGHT - 1){
                        if (snake.position[snake.snakeLength - 3].x == WIDTH - 1) {
                            snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x - 1;
                            snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y;
                        } else {
                            //ak je zvysok v hornom riadku
                            snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x;
                            snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y-1;
                        }
                        //ak su v rovnako stlpci
                    } else if(snake.position[snake.snakeLength - 2].x  ==  snake.position[snake.snakeLength - 3].x ){
                        //ak je predposledna cast nizsie teda had smeruje dole
                        if (snake.position[snake.snakeLength - 2].y  >  snake.position[snake.snakeLength - 3].y){
                            snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x;
                            snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y-1;
                        }else {
                            //ak smeruje had hore
                            snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x;
                            snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y+1;
                        }
                    }
                    //ak je y ne dolnej hranici tak sa to musi vykreslit bokom
                }else if(snake.position[snake.snakeLength-2].x == 0){
                    //ak je v lavom hornom rohu
                    if  ( snake.position[snake.snakeLength-2].y == 0 ) {
                        //ak je aj zvysok tela v pravom stlpci
                        if (snake.position[snake.snakeLength - 3].x == 0) {
                            snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x + 1;
                            snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y;
                        } else {
                            //ak je zvysok v hornom riadku
                            snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x;
                            snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y+1;
                        }
                        //ak je v lavom dolnom rohu
                    } else if(snake.position[snake.snakeLength-2].y == HEIGHT - 1){
                        if (snake.position[snake.snakeLength - 3].x == 0) {
                            snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x + 1;
                            snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y;
                        } else {
                            //ak je zvysok v dolnom riadku
                            snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x;
                            snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y-1;
                        }
                        //ak su v rovnako stlpci
                    } else if(snake.position[snake.snakeLength - 2].x  ==  snake.position[snake.snakeLength - 3].x ){
                        //ak je predposledna cast nizsie teda had smeruje dole
                        if (snake.position[snake.snakeLength - 2].y  >  snake.position[snake.snakeLength - 3].y){
                            snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x;
                            snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y-1;
                        }else {
                            //ak smeruje had hore
                            snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x;
                            snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y+1;
                        }
                    }else{
                        snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x;
                        snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y+1;
                    }
                } else{
                    if(snake.position[snake.snakeLength-2].y == 0){
                        //rohy su vyriesene vyssie
                        if (snake.position[snake.snakeLength-2].y == snake.position[snake.snakeLength-3].y){
                            //ak je
                            if (snake.position[snake.snakeLength-2].x > snake.position[snake.snakeLength-3].x){
                                snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x + 1;
                                snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y;
                            } else{
                                snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x - 1;
                                snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y;
                            }

                        } else{
                            snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x - 1;
                            snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y;
                        }
                    }else if(snake.position[snake.snakeLength-2].y == HEIGHT - 1){
                        //rohy su vyriesene vyssie
                        if (snake.position[snake.snakeLength-2].y == snake.position[snake.snakeLength-3].y){
                            //ak je//TODO:skontrolovať
                            if (snake.position[snake.snakeLength-2].x > snake.position[snake.snakeLength-3].x){
                                snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x + 1;
                                snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y;
                            } else{
                                //TODO:skontrolovať
                                snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x - 1;
                                snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y;
                            }

                        } else {
                            snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x - 1;
                            snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y;
                        }
                        //ak sa nerovnaju ani riadky ani stlpce
                    } else {
                        printf("Dostal som sa k switchu!!!!!");
                        switch (snake.direction) {
                            case UP:
                                snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x;
                                snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y+1;
                                break;
                            case DOWN:
                                snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x;
                                snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y-1;
                                break;
                            case LEFT:
                                snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x+1;
                                snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y;
                                break;
                            case RIGHT:
                                snake.position[snake.snakeLength - 1].x = snake.position[snake.snakeLength - 2].x-1;
                                snake.position[snake.snakeLength - 1].y = snake.position[snake.snakeLength - 2].y;
                                break;
                        }
                    }
                }*/
                //snake.position[snake.snakeLength-1].x = snake.position[snake.snakeLength-2].x; //zlozitejsia logika treba vyriesit ak je na krajoch hracieho pola
                //snake.position[snake.snakeLength-1].y = snake.position[snake.snakeLength-2].y+1;//zlozitejsia logika treba vyriesit ak je na krajoch hracieho pola
//                ++snake.snakeLength;
            //    snake.score = snake.score + 1;
            } else
            {
                printf("HAD1: nezjedol som nic");
            }

      }

        printf("??????????INIT MAP????????????????????\n");
        InitMap(map, &snake,&snake2, food, &snake.direction, 1);
        //TODO: tento for by sa dal dat do funkcie
        printf("??????????AFTER INIT MAP????????????????????\n");
        for (int i = 0; i < WIDTH; i++) {
            //printf("??????????FOR 1 %d????????????????????\n");
            for (int j = 0; j < HEIGHT; j++) {
                printf("%c", map[i][j]);
            }
            printf("\n");
        }
        printf("??????????FOR 414 ????????????????????\n");
        //pohyb bude musiet byt oddelene si myslim
        if(snake2crash == 0) {
            printf("??????????FOR 417 %d????????????????????\n");
                printf("Narade je druhy hrac\n");
                InputKeyboard(&snake2);
            printf("??????????FOR 420 ????????????????????\n");
                Movement(&snake2);
            printf("??????????FOR 422 %d????????????????????\n");
                if (CheckCollision(snake2, snake)) {
                    snake2crash = 1;
                    printf("??????????FOR 425 %d????????????????????\n");
                }

                //if (CheckCollisionWithFood(snake2, food))
                if(true)
                {
                    printf("HAD2: dostal som sa do jedenia");
                    food.position.x = rand() % WIDTH;
                    food.position.y = rand() % HEIGHT;
                    printf("??????????FOR 432 %d????????????????????\n");

                    snake2.snakeLength++;
                    placeNewBodyPart(&snake2);
                    printf("??????????FOR 434 %d????????????????????\n");
                    snake2.score++;
                } else
                {
                    printf("HAD2: nezjedol som nic");
                }

        }

        if (snake1crash == 1 && snake2crash == 1) {
            printf("Oba hadiky zomreli\nGAME OVER!!!");
            break;
        }
        InitMap(map, &snake,&snake2, food, &snake2.direction, 2);

        printf("CHCEM INFO AKY JE HAD\n");

        for (int i = 0; i < snake.snakeLength; ++i) {
            printf("HAD 1 poradove cislo: %d posX: %d\n", i, snake.position[i].x);
            printf("HAD 1 poradove cislo: %d posY: %d\n", i, snake.position[i].y);
        }
        for (int i = 0; i < snake2.snakeLength; ++i) {
            printf("HAD 2 poradove cislo: %d posX: %d\n", i, snake2.position[i].x);
            printf("HAD 2 poradove cislo: %d posY: %d\n", i, snake2.position[i].y);
        }
    }

    return 0;
}