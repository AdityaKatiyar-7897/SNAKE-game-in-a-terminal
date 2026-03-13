#ifndef GAME_H
#define GAME_H

#include <stdlib.h>

#define GRID_WIDTH 20
#define GRID_HEIGHT 20
#define MAX_SNAKE_LENGTH (GRID_WIDTH * GRID_HEIGHT)

typedef enum {
    EMPTY,
    FOOD,
    SNAKE
} CellType;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point body[MAX_SNAKE_LENGTH];
    int head_idx;
    int tail_idx;
    int length;
    Direction direction;
} Snake;

typedef struct {
    CellType grid[GRID_HEIGHT][GRID_WIDTH];
    Snake snake;
    Point food;
    int score;
    int alive;
} GameState;

void init_game(GameState *state);
void spawn_food(GameState *state);
void update_game(GameState *state);

#endif
