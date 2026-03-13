#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "game.h"
#include "terminal.h"

void draw(GameState *state) {
    clear_screen();
    
    printf("+");
    for (int j = 0; j < GRID_WIDTH; j++) printf("-");
    printf("+\n");

    for (int i = 0; i < GRID_HEIGHT; i++) {
        printf("|");
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (state->grid[i][j] == SNAKE)     printf("\033[32mO\033[0m");
            else if (state->grid[i][j] == FOOD) printf("\033[31mF\033[0m");
            else printf(" ");
        }
        printf("|\n");
    }

    printf("+");
    for (int j = 0; j < GRID_WIDTH; j++) printf("-");
    printf("+\n");

    printf("Score: %d\n", state->score);
}

int main() {
    srand(42);
    GameState state;
    init_game(&state);

    enable_raw_mode();
    hide_cursor();

    while (state.alive) {
        int key = get_key();

        if (key == 'w' && state.snake.direction != DOWN)  state.snake.direction = UP;
        if (key == 's' && state.snake.direction != UP)    state.snake.direction = DOWN;
        if (key == 'a' && state.snake.direction != RIGHT) state.snake.direction = LEFT;
        if (key == 'd' && state.snake.direction != LEFT)  state.snake.direction = RIGHT;
        if (key == 'q') break;

        update_game(&state);
        draw(&state);

        usleep(150000);
    }

    show_cursor();
    disable_raw_mode();
    clear_screen();
    printf("Game Over! Score: %d\n", state.score);

    return 0;
}
