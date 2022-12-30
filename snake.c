#include <stdlib.h>
#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 600
#define CAST 20

typedef enum direction {
    UP,
    DOWN,
    RIGHT,
    LEFT
} DIRECTION;

typedef enum food_type {
    APPLE,
    BANANA,
} FOOD_TYPE;

typedef struct position {
    int x;
    int y;
} POSITION;

typedef struct snake {
    POSITION position;
    DIRECTION direction;
} SNAKE;

typedef struct food {
    POSITION position;
    //FOOD_TYPE foodType;
} FOOD;

typedef struct game {
    SNAKE telo[100];
    FOOD food;
    int lenght;
    int gameOver;
} GAME;

//TODO: Nemoze sa otacat o 180 stupnov
void updateHead(SNAKE* head) {
    switch (head->direction) {
        case UP:
            head->position.y--;
            break;
        case DOWN:
            head->position.y++;
            break;
        case RIGHT:
            head->position.x++;
            break;
        case LEFT:
            head->position.x--;
            break;
    }
}

void addFruit(GAME* snake) {
    snake->food = (FOOD) {
        .position = (POSITION) {
            .x = rand() % (WIDTH / CAST),
            .y = rand() % (WIDTH / CAST)
        }
    };
}

void checkHeadCollision(SNAKE* head, GAME* snake) {
    //Kontrola kolizie so stenou
    if (head->position.x < 0 || head->position.x >= WIDTH / CAST ||
        head->position.y < 0 || head->position.y >= HEIGHT / CAST) {
        snake->gameOver = 1;
        return;
    }

    //Kontrola kolizie s telom
    for (int i = 1; i < snake->lenght; i++) {
        if (head->position.x == snake->telo[i].position.x && head->position.y == snake->telo[i].position.y) {
            snake->gameOver = 1;
            return;
        }
    }

    //Kontrola kolizie s jedlom
    if (head->position.x == snake->food.position.x && head->position.y == snake->food.position.y) {
        snake->telo[snake->lenght] = (SNAKE) {
            .position = snake->telo[snake->lenght - 1].position,
            .direction = snake->telo[snake->lenght - 1].direction
        };

        snake->lenght++;
        addFruit(snake);
    }
}

void updateSnake(GAME* snake) {
    for (int i = snake->lenght - 1; i > 0; i--) {
        snake->telo[i] = snake->telo[i - 1];
    }

    SNAKE* head = &snake->telo[0];
    updateHead(head);
    checkHeadCollision(head, snake);
}

void drawGame(GAME* snake, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    for (int i = 0; i < snake->lenght; i++) {
        SNAKE telo = snake->telo[i];

        SDL_Rect rect = {
                .x = telo.position.x * CAST,
                .y = telo.position.y * CAST,
                .w = CAST,
                .h = CAST
        };

        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect rect = {
            .x = snake->food.position.x * CAST,
            .y = snake->food.position.y * CAST,
            .w = CAST,
            .h = CAST
    };

    SDL_RenderFillRect(renderer, &rect);
}

int main(int argc, char* argv[]) {
    SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    if (window == NULL) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    GAME game = {
            .gameOver = 0,
            .lenght = 3,
            .food = (FOOD) {
                    .position = (POSITION) {
                            .x = rand() % (WIDTH / CAST),
                            .y = rand() % (WIDTH / CAST)
                    }
            }
    };

    for (int i = 0; i < 3; i++) {
        game.telo[i] = (SNAKE) {
                .direction = UP,
                .position = (POSITION) {
                        .x = WIDTH / 2 / CAST - i,
                        .y = HEIGHT / 2 / CAST
                }
        };
    }

    int gameon = 1;
    Uint32 lastTick = SDL_GetTicks();
    while (gameon == 1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    gameon = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            if (game.telo[0].direction != DOWN) {
                                game.telo[0].direction = UP;
                            }
                            break;
                        case SDLK_DOWN:
                            if (game.telo[0].direction != UP) {
                                game.telo[0].direction = DOWN;
                            }
                            break;

                        case SDLK_LEFT:
                            if (game.telo[0].direction != RIGHT) {
                                game.telo[0].direction = LEFT;
                            }
                            break;

                        case SDLK_RIGHT:
                            if (game.telo[0].direction != LEFT) {
                                game.telo[0].direction = RIGHT;
                            }
                            break;
                    }
                    break;
            }
        }

        Uint32 currentTick = SDL_GetTicks();
        if (currentTick - lastTick >= 250) {
            updateSnake(&game);
            lastTick = currentTick;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        drawGame(&game, renderer);
        SDL_RenderPresent(renderer);

        if (game.gameOver == 1 || event.key.keysym.sym == SDLK_LCTRL) {
            gameon = 0;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}