#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "global.h"
#include "sdlevent.h"

extern int screen_state;
extern int play_mode;
extern int current_player;
extern int screen_state;

int switchPlayer(int current_player)
{
    if (current_player == X) return O;
    return X;
}

int checkWinner(int arr[])
{
    for (int i = 0, j = 0; i < 9, j < 3; i += 3, ++j) {

        /* Check rows */
        if (arr[i] != BLANK && arr[i] == arr[i+1] && arr[i] == arr[i+2]) {
            if (arr[i] == X) return PLAYER_X;
            else return PLAYER_O;
        }
        /* Check columns */
        if (arr[j] != BLANK && arr[j] == arr[j+3] && arr[j] == arr[j+6]) {
            if (arr[j] == X) return PLAYER_X;
            if (arr[j] == O) return PLAYER_O;
        }
    }

    /* Check diagonals */
    if (arr[0] != BLANK && arr[0] == arr[4] && arr[0] == arr[8]) {
        if (arr[0] == X) return PLAYER_X;
        if (arr[0] == O) return PLAYER_O;
    }
    if (arr[2] != BLANK && arr[2] == arr[4] && arr[2] == arr[6]) {
        if (arr[2] == X) return PLAYER_X;
        if (arr[2] == O) return PLAYER_O;
    }

    /* Check if the game is finished or not
     */
    for (int i = 0; i < 9; ++i) {
        if (arr[i] == BLANK) {
            return UNFINISHED;
        }
    }

    return PLAYER_NONE;
}

bool handleEvent(SDL_Event* event, int arr[])
{
    bool return_value = false;
    if (screen_state == STARTSCREEN) {
        return_value = handleStartScreenEvent(event, arr);
    } else if (screen_state == GAMESCREEN) {
        return_value = handleGameScreenEvent(event, arr);
    } else if (screen_state == SCORESCREEN) {
        return_value = handleScoreScreenEvent(event, arr);
    }

    return return_value;
}

bool handleStartScreenEvent(SDL_Event* event, int arr[])
{
    extern int screen_state;
    if (event->type == SDL_QUIT) {
        return true;
    }

    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_1 || event->key.keysym.sym == SDLK_2) {
            for (int i = 0; i < 9; ++i) {
                arr[i] = BLANK;
            }

            screen_state = GAMESCREEN;

            if (event->key.keysym.sym == SDLK_1) {
              play_mode = SINGLEPLAYER;
            }
            else if (event->key.keysym.sym == SDLK_2) {
              play_mode = DOUBLEPLAYER;
            }
        }
    }

    return false;
}

bool handleGameScreenEvent(SDL_Event* event, int arr[])
{
    extern int current_player;

    if (event->type == SDL_QUIT) {
        return true;
    }

    int mouse_x, mouse_y;
    int buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

    if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {

        if (mouse_x < WINDOW_WIDTH / 3) {

            if (mouse_y < WINDOW_HEIGHT / 3) {
                if(arr[0] == BLANK) {
                    arr[0] = current_player;
                    current_player = switchPlayer(current_player);
                }
            } else if (mouse_y < 2 * WINDOW_HEIGHT / 3) {
                if(arr[3] == BLANK) {
                    arr[3] = current_player;
                    current_player = switchPlayer(current_player);
                }
            } else if (mouse_y < WINDOW_HEIGHT) {
                if(arr[6] == BLANK) {
                    arr[6] = current_player;
                    current_player = switchPlayer(current_player);
                }
            }

        } else if (mouse_x < 2 * WINDOW_WIDTH / 3) {

            if (mouse_y < WINDOW_HEIGHT / 3) {
                if(arr[1] == BLANK) {
                    arr[1] = current_player;
                    current_player = switchPlayer(current_player);
                }
            } else if (mouse_y < 2 * WINDOW_HEIGHT / 3) {
                if(arr[4] == BLANK) {
                    arr[4] = current_player;
                    current_player = switchPlayer(current_player);
                }
            } else if (mouse_y < WINDOW_HEIGHT) {
                if(arr[7] == BLANK) {
                    arr[7] = current_player;
                    current_player = switchPlayer(current_player);
                }
            }

        } else if (mouse_x < WINDOW_WIDTH) {

            if (mouse_y < WINDOW_HEIGHT / 3) {
                if(arr[2] == BLANK) {
                    arr[2] = current_player;
                    current_player = switchPlayer(current_player);
                }
            } else if (mouse_y < 2 * WINDOW_HEIGHT / 3) {
                if(arr[5] == BLANK) {
                    arr[5] = current_player;
                    current_player = switchPlayer(current_player);
                }
            } else if (mouse_y < WINDOW_HEIGHT) {
                if(arr[8] == BLANK) {
                    arr[8] = current_player;
                    current_player = switchPlayer(current_player);
                }
            }

        }
    }
    return false;
}

bool handleScoreScreenEvent(SDL_Event* event, int arr[])
{
    if (event->type == SDL_QUIT) {
        return true;
    }

    return false;
}
