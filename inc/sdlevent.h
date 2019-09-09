#ifndef SDL_EVENT_H
#define SDL_EVENT_H

int switchPlayer(int current_player);
bool handleEvent(SDL_Event* event, int arr[]);
bool handleStartScreenEvent(SDL_Event* event, int arr[]);
bool handleGameScreenEvent(SDL_Event* event, int arr[]);
bool handleScoreScreenEvent(SDL_Event* event, int arr[]);

#endif      // SDL_EVENT_H
