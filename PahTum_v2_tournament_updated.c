#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "playmove_1.h"
#include "playmove_2.h"
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#define SIZE 7
#define GAMES_IN_TOURNAMENT 5
#define MOVE_DELAY_MS 10000

// Structure to hold game scores
typedef struct {
    int player1Score;
    int player2Score;
    int player1Wins;
    int player2Wins;
} TournamentScores;

void printBoard(char board[SIZE][SIZE]);
void scoreBoard(char board[SIZE][SIZE], int countX[SIZE], int countO[SIZE]);
void printScores(char board[SIZE][SIZE]);
TournamentScores playGame(char board[SIZE][SIZE], char player1, char player2, bool player1Starts);
void initializeBoard(char board[SIZE][SIZE]);
void playTournament(char player1, char player2);

// Function to initialize the board
void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

// Function to print the board with ASCII graphics
void printBoard(char board[SIZE][SIZE]) {
    printf("    ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d   ", i);
    }
    printf("\n");
    
    printf("  ");
    for (int i = 0; i <= SIZE * 4; i++) {
        printf("-");
    }
    printf("\n");
    
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < SIZE; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
    }
    printf("  ");
    for (int i = 0; i <= SIZE * 4; i++) {
        printf("-");
    }
    printf("\n");
}







// Function to score the board
void scoreBoard(char board[SIZE][SIZE], int countX[SIZE], int countO[SIZE]) {
    // Initialize counts to zero
    for (int i = 0; i < SIZE; i++) {
        countX[i] = 0;
        countO[i] = 0;
    }
    
    // Check horizontally
    for (int i = 0; i < SIZE; i++) {
        int countXCurrent = 0, countOCurrent = 0;
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 'X') {
                countXCurrent++;
                countOCurrent = 0;
            } else if (board[i][j] == 'O') {
                countOCurrent++;
                countXCurrent = 0;
            } else {
                countXCurrent = 0;
                countOCurrent = 0;
            }
            if (countXCurrent >= 3) {
                countX[countXCurrent - 3]++;
            }
            if (countOCurrent >= 3) {
                countO[countOCurrent - 3]++;
            }
        }
    }

    // Check vertically
    for (int j = 0; j < SIZE; j++) {
        int countXCurrent = 0, countOCurrent = 0;
        for (int i = 0; i < SIZE; i++) {
            if (board[i][j] == 'X') {
                countXCurrent++;
                countOCurrent = 0;
            } else if (board[i][j] == 'O') {
                countOCurrent++;
                countXCurrent = 0;
            } else {
                countXCurrent = 0;
                countOCurrent = 0;
            }
            if (countXCurrent >= 3) {
                countX[countXCurrent - 3]++;
            }
            if (countOCurrent >= 3) {
                countO[countOCurrent - 3]++;
            }
        }
    }
}

// Function to print scores
void printScores(char board[SIZE][SIZE]) {
    int countX[SIZE] = {0}, countO[SIZE] = {0};
    int scoreX = 0, scoreO = 0;
    
    // Get the counts
    scoreBoard(board, countX, countO);
    
    // Calculate scores
    for (int i = 0; i < SIZE; i++) {
        int points = (i == 0) ? 3 : (i == 1) ? 10 : (i == 2) ? 25 : (i == 3) ? 56 : 119;
        scoreX += countX[i] * points;
        scoreO += countO[i] * points;
    }

    printf("Score for Player X: %d\n", scoreX);
    printf("Score for Player O: %d\n", scoreO);
    
    // Print breakdown of scores
    printf("\nBreakdown of Scores:\n");
    printf("Player X: ");
    for (int i = 0; i < 5; i++) {
        printf("%d sequences of %d, ", countX[i], i + 3);
    }
    printf("\n");
    printf("Player O: ");
    for (int i = 0; i < 5; i++) {
        printf("%d sequences of %d, ", countO[i], i + 3);
    }
    printf("\n");
}

// Function to calculate and return scores
TournamentScores calculateScores(char board[SIZE][SIZE], char player1, char player2) {
    int countX[SIZE] = {0}, countO[SIZE] = {0};
    int scoreX = 0, scoreO = 0;
    TournamentScores scores = {0, 0, 0, 0};
    
    scoreBoard(board, countX, countO);
    
    // Calculate scores
    for (int i = 0; i < SIZE; i++) {
        int points = (i == 0) ? 3 : (i == 1) ? 10 : (i == 2) ? 25 : (i == 3) ? 56 : 119;
        scoreX += countX[i] * points;
        scoreO += countO[i] * points;
    }

    // Assign scores to correct players
    if (player1 == 'X') {
        scores.player1Score = scoreX;
        scores.player2Score = scoreO;
    } else {
        scores.player1Score = scoreO;
        scores.player2Score = scoreX;
    }

    return scores;
}

// Function to play a single game
TournamentScores playGame(char board[SIZE][SIZE], char player1, char player2, bool player1Starts) {
    char currentPlayer = player1Starts ? player1 : player2;
    int moves = 0;
    TournamentScores gameScores = {0, 0, 0, 0};

    printf("\n=== Starting New Game ===\n");
    printf("Player %c starts this game\n", currentPlayer);
    
    // Main game loop
    while (moves < SIZE * SIZE) {
        printf("\nCurrent Board:\n");
        printBoard(board);
        
        int row, col;
        if (currentPlayer == player1) {
            playMove_1(board, currentPlayer, &row, &col);
        } else {
            playMove_2(board, currentPlayer, &row, &col);
        }
        // Apply the move to the board since the move functions can't modify it
        board[row][col] = currentPlayer;
        printf("Player %c played at position (%d, %d)\n", currentPlayer, row, col);
        
        // Calculate and show scores after each move
        gameScores = calculateScores(board, player1, player2);
        printf("\nCurrent Scores:\n");
        printf("Player %c: %d\n", player1, gameScores.player1Score);
        printf("Player %c: %d\n", player2, gameScores.player2Score);
        
        // Add delay after each move
        #ifdef _WIN32
            Sleep(MOVE_DELAY_MS);
        #else
            usleep(MOVE_DELAY_MS * 1000);  // Convert ms to microseconds
        #endif
        
        currentPlayer = (currentPlayer == player1) ? player2 : player1;
        moves++;
    }

    printf("\nFinal Board:\n");
    printBoard(board);
    
    // Final scores
    gameScores = calculateScores(board, player1, player2);
    printf("\nFinal Game Scores:\n");
    printf("Player %c: %d\n", player1, gameScores.player1Score);
    printf("Player %c: %d\n", player2, gameScores.player2Score);
    
    // Determine winner
    if (gameScores.player1Score > gameScores.player2Score) {
        gameScores.player1Wins = 1;
        printf("\nPlayer %c wins this game!\n", player1);
    } else if (gameScores.player2Score > gameScores.player1Score) {
        gameScores.player2Wins = 1;
        printf("\nPlayer %c wins this game!\n", player2);
    } else {
        printf("\nThis game is a tie!\n");
    }
    
    return gameScores;
}

// Function to play the tournament
void playTournament(char player1, char player2) {
    TournamentScores tournamentScores = {0, 0, 0, 0};
    int gamesPlayed = 0;
    bool player1Starts = true;  // Player 1 starts the first game
    
    printf("\n=== Starting Tournament: %c vs %c ===\n", player1, player2);
    
    while (gamesPlayed < GAMES_IN_TOURNAMENT) {
        char board[SIZE][SIZE];
        initializeBoard(board);
        
        printf("\nGame %d of %d\n", gamesPlayed + 1, GAMES_IN_TOURNAMENT);
        TournamentScores gameScores = playGame(board, player1, player2, player1Starts);
        
        // Update tournament scores
        tournamentScores.player1Score += gameScores.player1Score;
        tournamentScores.player2Score += gameScores.player2Score;
        tournamentScores.player1Wins += gameScores.player1Wins;
        tournamentScores.player2Wins += gameScores.player2Wins;
        
        gamesPlayed++;
        player1Starts = !player1Starts;  // Alternate starting player
        
        printf("\nTournament Progress:\n");
        printf("Player %c: %d wins, Total Score: %d\n", 
               player1, tournamentScores.player1Wins, tournamentScores.player1Score);
        printf("Player %c: %d wins, Total Score: %d\n", 
               player2, tournamentScores.player2Wins, tournamentScores.player2Score);
    }
    
    printf("\n=== Tournament Complete ===\n");
    printf("Final Results:\n");
    printf("Player %c: %d wins, Total Score: %d\n", 
           player1, tournamentScores.player1Wins, tournamentScores.player1Score);
    printf("Player %c: %d wins, Total Score: %d\n", 
           player2, tournamentScores.player2Wins, tournamentScores.player2Score);
    
    if (tournamentScores.player1Wins > tournamentScores.player2Wins) {
        printf("\nPlayer %c wins the tournament!\n", player1);
    } else if (tournamentScores.player2Wins > tournamentScores.player1Wins) {
        printf("\nPlayer %c wins the tournament!\n", player2);
    } else {
        printf("\nThe tournament is a tie!\n");
    }
}

int main() {
    // Initialize random number generator with current time
    srand(time(NULL));
    
    // Start the tournament
    playTournament('X', 'O');
    
    return 0;
} 