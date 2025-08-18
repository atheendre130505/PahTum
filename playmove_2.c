#include "playmove_2.h"
#include <stdlib.h>
#include <stdbool.h>

// Function to check if a move is valid (needed by playMove2)
bool isValidMove(char board[SIZE][SIZE], int row, int col) {
    return (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ');
}

// Function for Player 2's moves
// Board is passed by value (copy) - cannot modify original board
void playMove_2(char board[SIZE][SIZE], char player, int *x, int *y) {
    bool validMove = false;
    
    do {
        // Try a random position
        *x = rand() % SIZE;
        *y = rand() % SIZE;
        
        // Check if move is valid on the copied board
        if (isValidMove(board, *x, *y)) {
            validMove = true;
            // Note: We cannot modify the original board since it's a copy
            // The calling function will need to apply the move
        }
    } while (!validMove);
}
