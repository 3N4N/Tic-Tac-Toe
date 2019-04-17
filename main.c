#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "global.h"
#include "sdlshape.h"
#include "sdlevent.h"

void drawBoard(SDL_Renderer* renderer, int arr[][3])
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
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (arr[i][j] == X) {
                /* Green X's */
                SDL_SetRenderDrawColor(renderer, 152, 195, 121, 255);
                drawCross(renderer,
                          j * WINDOW_WIDTH / 3 + WINDOW_WIDTH / 12,
                          i * WINDOW_HEIGHT / 3 + WINDOW_HEIGHT / 12,
                          j * WINDOW_WIDTH / 3 + WINDOW_WIDTH / 4,
                          i * WINDOW_HEIGHT / 3 + WINDOW_HEIGHT / 4,
                          10);
            } else if (arr[i][j] == O) {
                /* Blue O's */
                SDL_SetRenderDrawColor(renderer, 97, 175, 239, 255);
                for (int k = 0; k < 5; ++k) {
                    drawCircle(renderer,
                               j * WINDOW_WIDTH / 3 + WINDOW_WIDTH / 6,
                               i * WINDOW_HEIGHT / 3 + WINDOW_HEIGHT / 6,
                               50 + k);
                }
            }
        }
    }

    return;
}

int main(int argc, int *argv[])
{
    int arr[3][3] = { { 2, 0, 1 },
                      { 1, 0, 2 },
                      { 0, 2, 0 } };

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

        drawBoard(renderer, arr);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
