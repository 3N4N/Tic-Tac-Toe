# Tic Tac Toe

A video game emulating a well-known pen-and-paper game called
Tic-tac-toe. This is implemented in C with SDL2 library.

## Objective

Tic-tac-toe is a two-player game. The players choose one symbols from
X's and O's for themselves. They take turns putting their symbols on
one of the nine squares. Whoever gets to put his or her symbol first
in three continuous squares, either horizontally or vertically or
diagonally is declared the winner.

## How to Play

1. Install the SDL2 library

    ```
    sudo apt install libsdl2-dev libsdl2-{ttf,image}-dev
    ```

2. Build the program

    ```
    make
    ```

3. Run the program

    ```
    ./play
    ```


## Development

* [x] Create the board
* [x] Create mouse click support
* [x] Create single player mode
* [x] Create double player mode
* [ ] Add sound effects
