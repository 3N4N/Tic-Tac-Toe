#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL2/SDL.h>

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)

enum {
    BLANK,
    X,
    O
};

enum {
    STARTSCREEN,
    GAMESCREEN,
    SCORESCREEN

};

enum {
    UNFINISHED,
    PLAYER_NONE,
    PLAYER_X,
    PLAYER_O
};

#endif      // GLOBAL_H
