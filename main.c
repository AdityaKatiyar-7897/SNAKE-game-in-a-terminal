#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "game.h"
#include "neural_net.h"
#include "terminal.h"

void draw(GameState *state, int generation, int score) {
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

    printf("Generation: %d | Score: %d\n", generation, score);
}

int main() {
    srand(42);

    NeuralNet net;
    init_network(&net);

    int generation = 1;

    while (1) {
        GameState state;
        init_game(&state);

        int steps = 0;

        while (state.alive && steps < 200) {
            float inputs[INPUT_SIZE];
            get_inputs(&state, inputs);
            forward(&net, inputs);
            int action = get_action(&net);

            if (action == 0) state.snake.direction = UP;
            if (action == 1) state.snake.direction = DOWN;
            if (action == 2) state.snake.direction = LEFT;
            if (action == 3) state.snake.direction = RIGHT;

            update_game(&state);
            draw(&state, generation, state.score);
            usleep(100000);
            steps++;
        }

        generation++;
    }

    return 0;
}
