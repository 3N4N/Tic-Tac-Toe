#include <stdbool.h>
#include <SDL2/SDL.h>

#include "global.h"
#include "sdlrender.h"

extern screen_state;

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
    extern play_mode;
    if (winner == PLAYER_NONE) {
        winner_msg = "It's a tie";
    } else if (winner == PLAYER_X) {
        winner_msg = "X won";
    } else if (winner == PLAYER_O) {
        winner_msg = "O won";
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
