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

    char* singleButton = "Press 1 for singleplayer";
    char* doubleButton = "Press 2 for doubleplayer";
    char* gameName = "Tic Tac Toe";
    TTF_Font* monaco = TTF_OpenFont("Monaco.ttf", 24);
    if (monaco == NULL) {
        printf("Error opening font: %s\n", SDL_GetError());
        return;
    }
    SDL_Color yellow = {239, 239, 40};
    SDL_Surface* singleButtonSurface = TTF_RenderText_Blended(monaco, singleButton, yellow);
    SDL_Texture* singleButtonTexture = SDL_CreateTextureFromSurface(renderer, singleButtonSurface);
    if (!singleButtonTexture) {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_FreeSurface(singleButtonSurface);
        TTF_CloseFont(monaco);
        return;
    }

    SDL_Surface* doubleButtonSurface = TTF_RenderText_Blended(monaco, doubleButton, yellow);
    SDL_Texture* doubleButtonTexture = SDL_CreateTextureFromSurface(renderer, doubleButtonSurface);
    if (!doubleButtonTexture) {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_FreeSurface(doubleButtonSurface);
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

    SDL_Rect single_button_rect;
    single_button_rect.x = (WINDOW_WIDTH - singleButtonSurface->w) / 2;
    single_button_rect.y = (WINDOW_HEIGHT - singleButtonSurface->h) / 2 + 50;
    single_button_rect.w = singleButtonSurface->w;
    single_button_rect.h = singleButtonSurface->h;

    SDL_Rect double_button_rect;
    double_button_rect.x = (WINDOW_WIDTH - doubleButtonSurface->w) / 2;
    double_button_rect.y = (WINDOW_HEIGHT - doubleButtonSurface->h) / 2 + 100;
    double_button_rect.w = doubleButtonSurface->w;
    double_button_rect.h = doubleButtonSurface->h;

    SDL_Rect game_name_rect;
    game_name_rect.x = (WINDOW_WIDTH - gameNameSurface->w) / 2;
    game_name_rect.y = (WINDOW_HEIGHT - gameNameSurface->h) / 2 - 100;
    game_name_rect.w = gameNameSurface->w;
    game_name_rect.h = gameNameSurface->h;

    SDL_RenderCopy(renderer, singleButtonTexture, NULL, &single_button_rect);
    SDL_RenderCopy(renderer, doubleButtonTexture, NULL, &double_button_rect);
    SDL_RenderCopy(renderer, gameNameTexture, NULL, &game_name_rect);

    SDL_FreeSurface(singleButtonSurface);
    SDL_FreeSurface(doubleButtonSurface);
    SDL_FreeSurface(gameNameSurface);
    SDL_DestroyTexture(singleButtonTexture);
    SDL_DestroyTexture(doubleButtonTexture);
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
        if (play_mode == SINGLEPLAYER) winner_msg = "You won";
        else winner_msg = "X won";
    } else if (winner == PLAYER_O) {
        if (play_mode == SINGLEPLAYER) winner_msg = "You lost";
        else winner_msg = "O won";
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
