#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

static struct termios orig_termios;

void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void clear_screen() { printf("\033[H\033[J"); }
void hide_cursor()  { printf("\033[?25l");    }
void show_cursor()  { printf("\033[?25h");    }

int get_key() {
    char c;
    if (read(STDIN_FILENO, &c, 1) == 1) return c;
    return 0;
}

#endif
