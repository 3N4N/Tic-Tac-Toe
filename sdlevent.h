#ifndef SDL_EVENT_H
#define SDL_EVENT_H

#include <SDL2/SDL.h>
#include "global.h"

bool handleStartScreenEvent(SDL_Event* event, int arr[]);
bool handleGameScreenEvent(SDL_Event* event, int arr[]);
bool handleScoreScreenEvent(SDL_Event* event, int arr[]);

bool handleEvent(SDL_Event* event, int arr[])
{
    extern screen_state;

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
    extern screen_state;
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
    if (current_player == O) return X;
}

bool handleGameScreenEvent(SDL_Event* event, int arr[])
{
    extern current_player;

    if (event->type == SDL_QUIT) {
        return true;
    }

    int mouse_x, mouse_y;
    int buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

    if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {

        if (mouse_x < WINDOW_WIDTH / 3) {

            if (mouse_y < WINDOW_HEIGHT / 3) arr[0] = current_player;
            else if (mouse_y < 2 * WINDOW_HEIGHT / 3) arr[3] = current_player;
            else if (mouse_y < WINDOW_HEIGHT) arr[6] = current_player;

        } else if (mouse_x < 2 * WINDOW_WIDTH / 3) {

            if (mouse_y < WINDOW_HEIGHT / 3) arr[1] = current_player;
            else if (mouse_y < 2 * WINDOW_HEIGHT / 3) arr[4] = current_player;
            else if (mouse_y < WINDOW_HEIGHT) arr[7] = current_player;

        } else if (mouse_x < WINDOW_WIDTH) {

            if (mouse_y < WINDOW_HEIGHT / 3) arr[2] = current_player;
            else if (mouse_y < 2 * WINDOW_HEIGHT / 3) arr[5] = current_player;
            else if (mouse_y < WINDOW_HEIGHT) arr[8] = current_player;

        }

        current_player = switchPlayer(current_player);

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

#endif      // SDL_EVENT_H
