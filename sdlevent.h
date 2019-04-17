#ifndef SDL_EVENT_H
#define SDL_EVENT_H

#include <SDL2/SDL.h>
#include "global.h"

bool handleEvent(SDL_Event* event, int arr[])
{
    if (event->type == SDL_QUIT) {
        return true;
    }

    int mouse_x, mouse_y;
    int buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

    if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {

        if (mouse_x < WINDOW_WIDTH / 3) {
            if (mouse_y < WINDOW_HEIGHT / 3) {
                arr[0] = X;
            } else if (mouse_y < 2 * WINDOW_HEIGHT / 3) {
                arr[3] = X;
            } else if (mouse_y < WINDOW_HEIGHT) {
                arr[6] = X;
            }
        } else if (mouse_x < 2 * WINDOW_WIDTH / 3) {
            if (mouse_y < WINDOW_HEIGHT / 3) {
                arr[1] = X;
            } else if (mouse_y < 2 * WINDOW_HEIGHT / 3) {
                arr[4] = X;
            } else if (mouse_y < WINDOW_HEIGHT) {
                arr[7] = X;
            }
        } else if (mouse_x < WINDOW_WIDTH) {
            if (mouse_y < WINDOW_HEIGHT / 3) {
                arr[2] = X;
            } else if (mouse_y < 2 * WINDOW_HEIGHT / 3) {
                arr[5] = X;
            } else if (mouse_y < WINDOW_HEIGHT) {
                arr[8] = X;
            }
        }

    }
    return false;
}

#endif      // SDL_EVENT_H
