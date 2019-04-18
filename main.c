#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "global.h"
#include "sdlshape.h"
#include "sdlevent.h"

int checkWinner(int arr[])
{
    for (int i = 0, j = 0; i < 9, j < 3; i += 3, ++j) {

        /* Check rows */
        if (arr[i] != BLANK && arr[i] == arr[i+1] && arr[i] == arr[i+2]) {
            if (arr[i] == X) return PLAYER_X;
            if (arr[i] == O) return PLAYER_O;
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

    for (int i = 0; i < 9; ++i) {
        if (arr[i] == BLANK) {
            return UNFINISHED;
        }
    }

    return PLAYER_NONE;
}


void drawBoard(SDL_Renderer* renderer, int arr[])
{

    /* Clear the screen with selected color */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    /* Draw the separators with selected color */
    SDL_SetRenderDrawColor(renderer, 224, 108, 117, 255);
    SDL_RenderDrawLine(renderer,
                       WINDOW_WIDTH / 3, 0,
                       WINDOW_WIDTH / 3, WINDOW_HEIGHT);
    SDL_RenderDrawLine(renderer,
                       WINDOW_WIDTH * 2 / 3, 0,
                       WINDOW_WIDTH * 2 / 3, WINDOW_HEIGHT);
    SDL_RenderDrawLine(renderer,
                       0, WINDOW_HEIGHT / 3,
                       WINDOW_WIDTH, WINDOW_HEIGHT / 3);
    SDL_RenderDrawLine(renderer,
                       0, WINDOW_HEIGHT *2 / 3,
                       WINDOW_WIDTH, WINDOW_HEIGHT * 2 / 3);

    /* Draw the X's and O's */
    for (int i = 0; i < 9; ++i) {
        if (arr[i] == X) {
            /* Green X's */
            SDL_SetRenderDrawColor(renderer, 152, 195, 121, 255);
            drawCross(renderer,
                      (i % 3) * WINDOW_WIDTH  / 3 + WINDOW_WIDTH  / 12,
                      (i / 3) * WINDOW_HEIGHT / 3 + WINDOW_HEIGHT / 12,
                      (i % 3) * WINDOW_WIDTH  / 3 + WINDOW_WIDTH  / 4,
                      (i / 3) * WINDOW_HEIGHT / 3 + WINDOW_HEIGHT / 4,
                      10);
        } else if (arr[i] == O) {
            /* Blue O's */
            SDL_SetRenderDrawColor(renderer, 97, 175, 239, 255);
            for (int k = 0; k < 5; ++k) {
                drawCircle(renderer,
                           (i % 3) * WINDOW_WIDTH  / 3 + WINDOW_WIDTH  / 6,
                           (i / 3) * WINDOW_HEIGHT / 3 + WINDOW_HEIGHT / 6,
                           50 + k);
            }
        }
    }

    return;
}

int main(int argc, int *argv[])
{
    int arr[9] = { BLANK, BLANK, BLANK,
                   BLANK, BLANK, BLANK,
                   BLANK, BLANK, BLANK };
    int winner;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow("Tic Tac Toe",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          0);

    if (!window) {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        EXIT_FAILURE;
    }

    Uint32 rend_flag = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, rend_flag);
    if (!renderer) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        EXIT_FAILURE;
    }

    SDL_Event event;
    bool quit = false;

    while (!quit) {

        while (SDL_PollEvent(&event)) {
            quit = handleEvent(&event, arr);
        }

        if ((winner = checkWinner(arr)) != BLANK) {
            quit = true;
        }

        drawBoard(renderer, arr);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
