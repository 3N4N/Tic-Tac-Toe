#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "global.h"
#include "sdlshape.h"
#include "sdlevent.h"
#include "sdlrender.h"

int screen_state;
int current_player;

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

int main(int argc, char *argv[])
{
    /* Initialize the game board */
    int arr[9] = { BLANK, BLANK, BLANK,
                   BLANK, BLANK, BLANK,
                   BLANK, BLANK, BLANK };
    int winner;
    current_player = X;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (TTF_Init() < 0) {
        printf("Error initializing TTF: %s\n", SDL_GetError());
        return EXIT_FAILURE;
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
        return EXIT_FAILURE;
    }

    Uint32 rend_flag = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, rend_flag);
    if (!renderer) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Event event;
    bool quit = false;

    screen_state = STARTSCREEN;
    while (!quit) {

        while (SDL_PollEvent(&event)) {
            quit = handleEvent(&event, arr);
        }

        if ((winner = checkWinner(arr)) != UNFINISHED) {
            screen_state = SCORESCREEN;
        }

        renderGame(renderer, arr, winner);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
