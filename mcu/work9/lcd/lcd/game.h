#ifndef GAME_CPP
#define GAME_CPP
#include <stdlib.h>

namespace game {
const int MAP_WIDTH = 8;
const int MAP_LINES = 2;

typedef int State;

const State menu = 0;
const State running = 1;
const State gameover = 2;
State state = menu;

int player_x = 0;
int player_y = 1;
int player_air = 0;
char player_symbol = ':';

char screen[MAP_LINES][MAP_WIDTH] = {
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
};
char map_buf[MAP_LINES][MAP_WIDTH] = {
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
};

void shift_and_generate() {
    for (size_t i = 1; i < MAP_WIDTH; i++) {
        map_buf[0][i - 1] = map_buf[0][i];
        map_buf[1][i - 1] = map_buf[1][i];
    }
    map_buf[0][MAP_WIDTH - 1] = ' ';
    map_buf[1][MAP_WIDTH - 1] = ' ';
    int rup = rand() % 100;
    int rdown = rand() % 100;
    if (rup > 80) {
        map_buf[0][MAP_WIDTH - 1] = 'V';
    } else if (rdown > 80) {
        map_buf[1][MAP_WIDTH - 1] = 'A';
    }
}

bool check_collisions() {
    if (map_buf[player_y][player_x] == 'V' ||
        map_buf[player_y][player_x] == 'A') {
        return true;
    }
    return false;
}

void copy_game_buf() {
    for (size_t i = 0; i < MAP_LINES; i++) {
        for (size_t j = 0; j < MAP_WIDTH; j++) {
            screen[i][j] = map_buf[i][j];
        }
    }
}

void update() {
    if (state == running) {
        screen[player_y][player_x] = player_symbol;
    }
}

void clear_map_buf() {
    for (size_t i = 0; i < MAP_LINES; i++) {
        for (size_t j = 0; j < MAP_WIDTH; j++) {
            map_buf[i][j] = ' ';
        }
    }
}

void clear_screen() {
    for (int i = 0; i < MAP_LINES; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            screen[i][j] = ' ';
        }
    }
}

void update_state(State new_state) { state = new_state; }

void player_dash() {
    shift_and_generate();
    if (check_collisions()) {
        update_state(gameover);
    }
    shift_and_generate();
    if (check_collisions()) {
        update_state(gameover);
    }
}

void player_jump() {
    if (player_y == 1 && player_air == 0) {
        player_y = 0;
        player_air = 3;
    }
}

void tick() {
    if (state == running) {
        shift_and_generate();
        if (check_collisions()) {
            update_state(gameover);
        }
        if (player_air > 0) {
            player_air--;
            player_symbol = ';';
        } else {
            player_y = 1;
            player_symbol = ':';
        }
    }
}

void refresh() {
    clear_screen();
    switch (state) {
        case menu:
            screen[0][0] = 'P';
            screen[0][1] = 'R';
            screen[0][2] = 'E';
            screen[0][3] = 'S';
            screen[0][4] = 'S';
            screen[1][0] = 'A';
            screen[1][1] = 'N';
            screen[1][2] = 'Y';
            screen[1][3] = ' ';
            screen[1][4] = 'K';
            screen[1][5] = 'E';
            screen[1][6] = 'Y';
            clear_map_buf();
            player_y = 1;
            break;
        case running:
            tick();
            copy_game_buf();
            screen[player_y][player_x] = player_symbol;
            break;
        case gameover:
            screen[0][0] = 'G';
            screen[0][1] = 'A';
            screen[0][2] = 'M';
            screen[0][3] = 'E';
            screen[1][0] = 'O';
            screen[1][1] = 'V';
            screen[1][2] = 'E';
            screen[1][3] = 'R';
            break;
    }
}
}  // namespace game
#endif