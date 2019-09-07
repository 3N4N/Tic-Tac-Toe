#include <stdbool.h>
#include <SDL2/SDL.h>

#include "global.h"
#include "sdlevent.h"

bool handleEvent(SDL_Event* event, int arr[])
{
    extern int screen_state;

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
        if (event->key.keysym.sym == SDLK_RETURN) {
            for (int i = 0; i < 9; ++i) {
                arr[i] = BLANK;
            }
            screen_state = GAMESCREEN;
        }
    }

    return false;
}

int switchPlayer(int current_player)
{
    if (current_player == X) return O;
    return X;
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
