#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "global.h"
#include "sdlshape.h"
#include "sdlevent.h"

int screen_state;
int current_player;

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

    /* Check if the game is finished or not
     */
    for (int i = 0; i < 9; ++i) {
        if (arr[i] == BLANK) {
            return UNFINISHED;
        }
    }

    return PLAYER_NONE;
}

void renderStartScreen(SDL_Renderer* renderer, int arr[])
{
    /* Clear the screen with selected color */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    char* playButton = "PLAY";
    char* gameName = "Tic Tac Toe";
    TTF_Font* monaco = TTF_OpenFont("Monaco.ttf", 24);
    if (monaco == NULL) {
        printf("Error opening font: %s\n", SDL_GetError());
        return;
    }
    SDL_Color yellow = {239, 239, 40};
    SDL_Surface* playButtonSurface = TTF_RenderText_Blended(monaco, playButton, yellow);
    SDL_Texture* playButtonTexture = SDL_CreateTextureFromSurface(renderer, playButtonSurface);
    if (!playButtonTexture) {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_FreeSurface(playButtonSurface);
        TTF_CloseFont(monaco);
        return;
    }
    SDL_Surface* gameNameSurface = TTF_RenderText_Blended(monaco, gameName, yellow);
    SDL_Texture* gameNameTexture = SDL_CreateTextureFromSurface(renderer, gameNameSurface);
    if (!gameNameTexture) {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_FreeSurface(gameNameSurface);
        TTF_CloseFont(monaco);
        return;
    }

    SDL_Rect play_button_rect;
    play_button_rect.x = (WINDOW_WIDTH - playButtonSurface->w) / 2;
    play_button_rect.y = (WINDOW_HEIGHT - playButtonSurface->h) / 2 + 100;
    play_button_rect.w = playButtonSurface->w;
    play_button_rect.h = playButtonSurface->h;

    SDL_Rect game_name_rect;
    game_name_rect.x = (WINDOW_WIDTH - gameNameSurface->w) / 2;
    game_name_rect.y = (WINDOW_HEIGHT - gameNameSurface->h) / 2 - 100;
    game_name_rect.w = gameNameSurface->w;
    game_name_rect.h = gameNameSurface->h;

    SDL_RenderCopy(renderer, playButtonTexture, NULL, &play_button_rect);
    SDL_RenderCopy(renderer, gameNameTexture, NULL, &game_name_rect);

    SDL_FreeSurface(playButtonSurface);
    SDL_FreeSurface(gameNameSurface);
    SDL_DestroyTexture(playButtonTexture);
    SDL_DestroyTexture(gameNameTexture);
    TTF_CloseFont(monaco);
}

void renderGameScreen(SDL_Renderer* renderer, int arr[])
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

void renderScoreScreen(SDL_Renderer* renderer, int arr[], int winner)
{
    char* winner_msg;
    if (winner == PLAYER_NONE) {
        winner_msg = "It's a tie";
    } else if (winner == PLAYER_X) {
        winner_msg = "Player 1 won";
    } else if (winner == PLAYER_O) {
        winner_msg = "Player 2 won";
    }

    /* Clear the screen with selected color */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    TTF_Font* monaco = TTF_OpenFont("Monaco.ttf", 24);
    if (monaco == NULL) {
        printf("Error opening font: %s\n", SDL_GetError());
        return;
    }
    SDL_Color yellow = {239, 239, 40};
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(monaco, winner_msg, yellow);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    if (!message) {
        printf("error creating texture: %s\n", SDL_GetError());
        TTF_CloseFont(monaco);
        return;
    }

    SDL_Rect message_rect;
    message_rect.x = (WINDOW_WIDTH - surfaceMessage->w) / 2;
    message_rect.y = (WINDOW_HEIGHT - surfaceMessage->h) / 2;
    message_rect.w = surfaceMessage->w;
    message_rect.h = surfaceMessage->h;

    SDL_RenderCopy(renderer, message, NULL, &message_rect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
    TTF_CloseFont(monaco);
}

void renderGame(SDL_Renderer* renderer, int arr[], int winner)
{
    if (screen_state == STARTSCREEN) {
        renderStartScreen(renderer, arr);
    } else if (screen_state == GAMESCREEN) {
        renderGameScreen(renderer, arr);
    } else if (screen_state == SCORESCREEN) {
        renderScoreScreen(renderer, arr, winner);
    }
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
