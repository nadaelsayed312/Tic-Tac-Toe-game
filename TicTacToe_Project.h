#ifndef TICTACTOE_PROJECT_H //using (_) as their is no (.h) in macros
#define TICTACTOE_PROJECT_H //define this macro

#define SizeofBoard 10

typedef struct {
    uint8 board[10]; // Array to store the board state
    sint32 currentPlayer; // Current player (1 or 2)
} Game;

void clearScreen();
void delay(sint32 number_of_seconds);
sint32 flipCoin();
void playMultiplayer(Game* game);
void playSinglePlayer(Game* game, int mode);
void printBoard(Game* game);
sint32 markBoard(Game* game, sint32 choice);
sint32 checkWinner(Game* game);


#endif