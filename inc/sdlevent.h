#ifndef SDL_EVENT_H
#define SDL_EVENT_H

bool handleEvent(SDL_Event* event, int arr[]);
bool handleStartScreenEvent(SDL_Event* event, int arr[]);
bool handleGameScreenEvent(SDL_Event* event, int arr[]);
bool handleScoreScreenEvent(SDL_Event* event, int arr[]);
int computerTurn(int arr[]);
int computerTurnRandom(int arr[]);
int computerTurnMiniMax(int arr[]);
int availableMoves(int arr[]);
int checkWinner(int arr[]);

#endif      // SDL_EVENT_H
