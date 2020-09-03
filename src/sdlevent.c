#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "global.h"
#include "sdlevent.h"

extern int screen_state;
extern int play_mode;
extern int current_player;
extern int screen_state;

int switchPlayer(int current_player)
{
    if (current_player == X) return O;
    return X;
}

int checkWinner(int arr[])
{
    for (int i = 0; i < 9; i += 3) {
        /* Check rows */
        if (arr[i] != BLANK && arr[i] == arr[i+1] && arr[i] == arr[i+2]) {
            if (arr[i] == X) return PLAYER_X;
            else return PLAYER_O;
        }
    }

    for (int j = 0; j < 3; j += 1) {
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

bool handleEvent(SDL_Event* event, int arr[])
{
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
    if (event->type == SDL_QUIT) {
        return true;
    }

    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_1 || event->key.keysym.sym == SDLK_2) {
            for (int i = 0; i < 9; ++i) {
                arr[i] = BLANK;
            }

            screen_state = GAMESCREEN;

            if (event->key.keysym.sym == SDLK_1) {
              play_mode = SINGLEPLAYER;
            }
            else if (event->key.keysym.sym == SDLK_2) {
              play_mode = DOUBLEPLAYER;
            }
        }
    }

    return false;
}

bool handleGameScreenEvent(SDL_Event* event, int arr[])
{
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
                    if (play_mode == DOUBLEPLAYER)
                        current_player = switchPlayer(current_player);
                    else
                        arr[computerTurn(arr)] = O;
                }
            } else if (mouse_y < 2 * WINDOW_HEIGHT / 3) {
                if(arr[3] == BLANK) {
                    arr[3] = current_player;
                    if (play_mode == DOUBLEPLAYER)
                        current_player = switchPlayer(current_player);
                    else
                        arr[computerTurn(arr)] = O;
                }
            } else if (mouse_y < WINDOW_HEIGHT) {
                if(arr[6] == BLANK) {
                    arr[6] = current_player;
                    if (play_mode == DOUBLEPLAYER)
                        current_player = switchPlayer(current_player);
                    else
                        arr[computerTurn(arr)] = O;
                }
            }
        } else if (mouse_x < 2 * WINDOW_WIDTH / 3) {
            if (mouse_y < WINDOW_HEIGHT / 3) {
                if(arr[1] == BLANK) {
                    arr[1] = current_player;
                    if (play_mode == DOUBLEPLAYER)
                        current_player = switchPlayer(current_player);
                    else
                        arr[computerTurn(arr)] = O;
                }
            } else if (mouse_y < 2 * WINDOW_HEIGHT / 3) {
                if(arr[4] == BLANK) {
                    arr[4] = current_player;
                    if (play_mode == DOUBLEPLAYER)
                        current_player = switchPlayer(current_player);
                    else
                        arr[computerTurn(arr)] = O;
                }
            } else if (mouse_y < WINDOW_HEIGHT) {
                if(arr[7] == BLANK) {
                    arr[7] = current_player;
                    if (play_mode == DOUBLEPLAYER)
                        current_player = switchPlayer(current_player);
                    else
                        arr[computerTurn(arr)] = O;
                }
            }
        } else if (mouse_x < WINDOW_WIDTH) {
            if (mouse_y < WINDOW_HEIGHT / 3) {
                if(arr[2] == BLANK) {
                    arr[2] = current_player;
                    if (play_mode == DOUBLEPLAYER)
                        current_player = switchPlayer(current_player);
                    else
                        arr[computerTurn(arr)] = O;
                }
            } else if (mouse_y < 2 * WINDOW_HEIGHT / 3) {
                if(arr[5] == BLANK) {
                    arr[5] = current_player;
                    if (play_mode == DOUBLEPLAYER)
                        current_player = switchPlayer(current_player);
                    else
                        arr[computerTurn(arr)] = O;
                }
            } else if (mouse_y < WINDOW_HEIGHT) {
                if(arr[8] == BLANK) {
                    arr[8] = current_player;
                    if (play_mode == DOUBLEPLAYER)
                        current_player = switchPlayer(current_player);
                    else
                        arr[computerTurn(arr)] = O;
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

int computerTurn(int arr[])
{
    int r;
    if (availableMoves(arr) == 9) {
        r = computerTurnRandom(arr);
    }
    else {
        r = computerTurnMiniMax(arr);
    }

    return r;
}

int minimax(int arr[], int alpha, int beta, bool isMaximizing)
{
    int score = 0;
    int bestScore = 0;
    int winner = checkWinner(arr);
    int emptyTiles = availableMoves(arr);

    if (winner != UNFINISHED) {
        if (winner == PLAYER_X) {
            return -1 * (emptyTiles + 1);
        } else if (winner == PLAYER_O) {
            return 1 * (emptyTiles + 1);
        }

        return 0;
    }

    if (isMaximizing) {
        bestScore = -1 * INFINITY;
        for (int i = 0; i < 9; ++i) {
            if (arr[i] == BLANK) {
                arr[i] = O;
                score = minimax(arr, alpha, beta, false);
                arr[i] = BLANK;
                if (score > bestScore) bestScore = score;
                if (score > alpha) alpha = score;
                if (beta <= alpha) break;
            }
        }
    } else {
        bestScore = INFINITY;
        for (int i = 0; i < 9; ++i) {
            if (arr[i] == BLANK) {
                arr[i] = X;
                score = minimax(arr, alpha, beta, true);
                arr[i] = BLANK;
                if (score < bestScore) bestScore = score;
                if (score < beta) beta = score;
                if (beta <= alpha) break;
            }
        }
    }

    return bestScore;
}

int computerTurnMiniMax(int arr[])
{
    int score = 0;
    int bestScore = -1 * INFINITY;
    int bestMove = -1;

    for (int i = 0; i < 9; ++i) {
        if (arr[i] == BLANK) {
            arr[i] = O;
            score = minimax(arr, -1 * INFINITY, 1 * INFINITY, false);
            arr[i] = BLANK;
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }

    return bestMove;
}

int computerTurnRandom(int arr[])
{
    srand(time(NULL));
    int r;
    do {
        r = rand() % 9;
    } while (arr[r] != BLANK);

    return r;
}

int availableMoves(int arr[])
{
    int c = 0;

    for (int i = 0; i < 9; ++i) {
        if (arr[i] == BLANK) c++;
    }

    return c;
}
