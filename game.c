#include "game.h"

void init_game(GameState *state) {
    // Clear grid
    for (int i = 0; i < GRID_HEIGHT; i++)
        for (int j = 0; j < GRID_WIDTH; j++)
            state->grid[i][j] = EMPTY;

    // Snake starts in center moving right
    state->snake.head_idx = 0;
    state->snake.tail_idx = 2;
    state->snake.length = 3;
    state->snake.direction = RIGHT;

    // Snake body - 3 blocks in center
    state->snake.body[0] = (Point){GRID_WIDTH/2 - 2, GRID_HEIGHT/2};
    state->snake.body[1] = (Point){GRID_WIDTH/2 - 1, GRID_HEIGHT/2};
    state->snake.body[2] = (Point){GRID_WIDTH/2,     GRID_HEIGHT/2};

    // Mark snake on grid
    for (int i = 0; i <= state->snake.tail_idx; i++)
        state->grid[state->snake.body[i].y][state->snake.body[i].x] = SNAKE;

    // Score and alive
    state->score = 0;
    state->alive = 1;

    // Spawn food
    spawn_food(state);
}

void spawn_food(GameState *state) {
    int x, y;
    do {
        x = rand() % GRID_WIDTH;
        y = rand() % GRID_HEIGHT;
    } while (state->grid[y][x] != EMPTY);

    state->food = (Point){x, y};
    state->grid[y][x] = FOOD;
}

void update_game(GameState *state) {
    // Figure out where head is moving next
    Point head = state->snake.body[state->snake.tail_idx];
    Point next = head;

    if (state->snake.direction == UP)    next.y--;
    if (state->snake.direction == DOWN)  next.y++;
    if (state->snake.direction == LEFT)  next.x--;
    if (state->snake.direction == RIGHT) next.x++;

    // Check wall collision
    if (next.x < 0 || next.x >= GRID_WIDTH ||
        next.y < 0 || next.y >= GRID_HEIGHT) {
        state->alive = 0;
        return;
    }

    // Check self collision
    if (state->grid[next.y][next.x] == SNAKE) {
        state->alive = 0;
        return;
    }

    // Check if food eaten
    int ate_food = (state->grid[next.y][next.x] == FOOD);

    // Move tail forward if no food eaten
    if (!ate_food) {
        Point tail = state->snake.body[state->snake.head_idx];
        state->grid[tail.y][tail.x] = EMPTY;
        state->snake.head_idx++;
        if (state->snake.head_idx >= MAX_SNAKE_LENGTH)
            state->snake.head_idx = 0;
    } else {
        state->score++;
        state->snake.length++;
        spawn_food(state);
    }

    // Add new head
    state->snake.tail_idx++;
    if (state->snake.tail_idx >= MAX_SNAKE_LENGTH)
        state->snake.tail_idx = 0;
    state->snake.body[state->snake.tail_idx] = next;
    state->grid[next.y][next.x] = SNAKE;
}
