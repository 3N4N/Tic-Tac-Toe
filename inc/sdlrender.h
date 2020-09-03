#ifndef SDL_RENDER_H
#define SDL_RENDER_H

#include <SDL2/SDL_ttf.h>

void renderStartScreen(SDL_Renderer* renderer, int arr[]);
void renderGameScreen(SDL_Renderer* renderer, int arr[]);
void renderScoreScreen(SDL_Renderer* renderer, int arr[], int winner);
void renderGame(SDL_Renderer* renderer, int arr[], int winner);

#endif      // SDL_RENDER_H
