#include <unistd.h>
#include <string.h>
#include <error.h>
#include "game_snake.h"

void drawOtherSnakeHead(SNAKE * snake, char map[WIDTH][HEIGHT]){
    switch (snake->direction) {
        case UP:
            pthread_mutex_lock(&mutex);
            map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_UP;
            pthread_mutex_unlock(&mutex);
            break;
        case DOWN:
            pthread_mutex_lock(&mutex);
            map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_DOWN;
            pthread_mutex_unlock(&mutex);
            break;
        case LEFT:
            pthread_mutex_lock(&mutex);
            map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_LEFT;
            pthread_mutex_unlock(&mutex);
            break;
        case RIGHT:
            pthread_mutex_lock(&mutex);
            map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_RIGHT;
            pthread_mutex_unlock(&mutex);
            break;

    }
}

//player pridany aby sa vedelo ktoreho hada otocit
void InitMap(char map[WIDTH][HEIGHT], SNAKE * snake,SNAKE * snake2, FOOD food, DIRECTION * direction, int player)
{
    //Vykreslenie mapy
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            pthread_mutex_lock(&mutex);
            map[i][j] = EMPTY;
            pthread_mutex_unlock(&mutex);
        }
    }

    //Vykreslenie hlavy
    switch (*direction)
    {
        case UP:
            if (player == 1){
                pthread_mutex_lock(&mutex);
                map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_UP;
                pthread_mutex_unlock(&mutex);
                drawOtherSnakeHead(snake2, map);
            }
            if (player == 2){
                pthread_mutex_lock(&mutex);
                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_UP;
                pthread_mutex_unlock(&mutex);
                drawOtherSnakeHead(snake, map);
            }
            if (player == 100){
                pthread_mutex_lock(&mutex);
                map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_UP;
                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_UP;
                pthread_mutex_unlock(&mutex);
            }
            break;
        case DOWN:
            if (player == 1){
                pthread_mutex_lock(&mutex);
                map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_DOWN;
                pthread_mutex_unlock(&mutex);
                drawOtherSnakeHead(snake2, map);
            }
            if (player == 2){
                pthread_mutex_lock(&mutex);
                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_DOWN;
                pthread_mutex_unlock(&mutex);
                drawOtherSnakeHead(snake, map);
            }
            if (player == 100){
                pthread_mutex_lock(&mutex);
                map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_DOWN;
                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_DOWN;
                pthread_mutex_unlock(&mutex);
            }
            break;
        case RIGHT:
            if (player == 1){
                pthread_mutex_lock(&mutex);
                map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_RIGHT;
                pthread_mutex_unlock(&mutex);
                drawOtherSnakeHead(snake2, map);
            }
            if (player == 2){
                pthread_mutex_lock(&mutex);
                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_RIGHT;
                pthread_mutex_unlock(&mutex);
                drawOtherSnakeHead(snake, map);
            }
            if (player == 100){
                pthread_mutex_lock(&mutex);
                map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_RIGHT;
                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_RIGHT;
                pthread_mutex_unlock(&mutex);
            }
            break;
        case LEFT:
            if (player == 1){
                pthread_mutex_lock(&mutex);
                map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_LEFT;
                pthread_mutex_unlock(&mutex);
                drawOtherSnakeHead(snake2, map);
            }
            if (player == 2){
                pthread_mutex_lock(&mutex);
                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_LEFT;
                pthread_mutex_unlock(&mutex);
                drawOtherSnakeHead(snake, map);
            }
            if (player == 100){
                pthread_mutex_lock(&mutex);
                map[snake->position[0].y][snake->position[0].x] = SNAKE_HEAD_LEFT;
                map[snake2->position[0].y][snake2->position[0].x] = SNAKE_HEAD_LEFT;
                pthread_mutex_unlock(&mutex);
            }
            break;
        default:
            break;
    }

    //Vykreslenie tela
    //if (snake->type == SERVER){
    for (int i = 1; i < snake->snakeLength; i++) {
        int posY = snake->position[i].y;
        int posX = snake->position[i].x;
        pthread_mutex_lock(&mutex);
        map[posY][posX] = SNAKE_BODY;
        pthread_mutex_unlock(&mutex);
    }
    //}
    //if (snake->type == KLIENT){

    for (int i = 1; i < snake2->snakeLength; i++) {
        pthread_mutex_lock(&mutex);
        map[snake2->position[i].y][snake2->position[i].x] = SNAKE_BODY_2;
        pthread_mutex_unlock(&mutex);
    }
    //}

    //Vykreslenie jedla
    pthread_mutex_lock(&mutex);
    map[food.position.y][food.position.x] = FOOD_TY;
    pthread_mutex_unlock(&mutex);
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
        if(snake->position[snake->snakeLength-2].y == 0) {
            //rohy su vyriesene vyssie
            if (snake->position[snake->snakeLength-2].y == snake->position[snake->snakeLength-3].y){
                //ak je
                if (snake->position[snake->snakeLength-2].x > snake->position[snake->snakeLength-3].x){
                    snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x + 1;
                    snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y;
                } else {
                    snake->position[snake->snakeLength - 1].x = snake->position[snake->snakeLength - 2].x - 1;
                    snake->position[snake->snakeLength - 1].y = snake->position[snake->snakeLength - 2].y;
                }

            } else {
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
        }
    }
}

int gameplay()
{
    int snake1crash = 0;
    int snake2crash = 0;
    char map_buffer[map_size];
    srand(time(NULL));

    //prerabka na smernik pokus zbavit sa segmentation fault --smernik nebol spravne riesenie
    SNAKE snake, snake2;
    SNAKEP snakep;

    snakep.snakeLength = 2;
    snakep.score = 0;

    snake.snakeLength = 3;
    snake.score = 0;

    snake2.snakeLength = 3;
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

        if(snake1crash == 0)
        {
            printf("Narade je SERVER\n");
            InputKeyboard(&snake);
            Movement(&snake);

            //toto bude treba inak lebo druhy hrac bude este moct predsa hrat
            if (CheckCollision(snake, snake2))
            {
                snake1crash = 1;
            }
            if (CheckCollisionWithFood(snake, food))
            {
                food.position.x = rand() % WIDTH;
                food.position.y = rand() % HEIGHT;
                int snk = snake.snakeLength;
                snk = snk + 1;
                snake.snakeLength = snk;
                placeNewBodyPart(&snake);
                snake.score++;
            }
        }

        //POSLI DATA
        InitMap(map, &snake,&snake2, food, &snake.direction, 1);

        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                printf("%c", map[i][j]);
            }
            printf("\n");
        }

        //PRECITAJ CO NAPISAL KLIENT
        if(snake2crash == 0) {
            printf("Narade je KLIENT\n");
            InputKeyboard(&snake2);
            Movement(&snake2);
            if (CheckCollision(snake2, snake)) {
                snake2crash = 1;
            }

            if (CheckCollisionWithFood(snake2, food))
            {
                food.position.x = rand() % WIDTH;
                food.position.y = rand() % HEIGHT;
                snake2.snakeLength++;
                placeNewBodyPart(&snake2);
                snake2.score++;
            }
        }

        if (snake1crash == 1 && snake2crash == 1) {
            printf("Oba hadiky zomreli\nGAME OVER!!!");
            break;
        }

        InitMap(map, &snake,&snake2, food, &snake2.direction, 2);

        //POSLI DATA
    }

    return 0;
}