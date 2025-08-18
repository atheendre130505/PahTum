#ifndef PLAYMOVE_1_H
#define PLAYMOVE_1_H

#define SIZE 7

// Function declaration for Player 1's moves
// Board is passed by value (copy) to prevent modification
void playMove_1(char board[SIZE][SIZE], char player, int *x, int *y);

#endif // PLAYMOVE_1_H
