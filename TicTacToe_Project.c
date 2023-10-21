#include "STD_TYPES.h"
#include <stdio.h>
#include <stdlib.h> // Include the <stdlib.h> header for the exit() function
#include <time.h>
#include <stdbool.h>
#include "TicTacToe_Project.h"//to create module TicTacToe_Project based on TicTacToe_Project.h
 
extern uint8 name1[25],name2[25];
extern sint32 mode;

//******************************general functions********************************************
void delay(sint32 number_of_seconds)
{
    // Converting time into milli_seconds
    sint32 milli_seconds = 1000 * number_of_seconds;
 
    // Storing start time
    clock_t start_time = clock();
 
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}
 
void clearScreen()
{
    #if defined(_WIN32) || defined(_WIN64) // Clear screen for Windows
        system("cls");
    #else // Clear screen for Unix/Linux/Mac
        printf("\033[H\033[J");
    #endif
}
//******************************game functions********************************************
sint32 flipCoin()
{
	srand(time(NULL));
    return rand() % 2; // Returns 0 or 1 randomly
}
 
void playMultiplayer(Game* game)
{
    static sint32 score1 = 0, score2 = 0; // static to keep save score out of stack section

    for (sint32 i = 1; i <= 9; i++)
    {
        game->board[i] = i + '0'; // Initialize the board
    }

    sint32 choice, check;

    do
    {
        printBoard(game); 
        printf("\t\tPlayer %d, enter your choice (1-9, 0 to exit): ", game->currentPlayer);
        scanf("%d", &choice);

        if (choice == 0) // Exit the game
        {
            printf("\tExiting the game.\n");
            return;
        }

        uint8 mark = (game->currentPlayer == 1) ? 'X' : 'O';

        if (!markBoard(game, choice))
        {
            delay(2); // to give applity to the error message to appear
            continue; // Skip the rest of the current iteration and prompt the same player for another choice iteration
        }

        check = checkWinner(game);

        if (check == -1)
        {
            game->currentPlayer = (game->currentPlayer == 1) ? 2 : 1;
        }

    } while (check == -1);

    printBoard(game); // Removed "mode" argument since it's not needed

    if (check == 1)
    {
        printf("\tPlayer %d has won.\n", game->currentPlayer);
        if (game->currentPlayer == 1)
            score1++;
        else
            score2++;
        printf("\tScore:\n\t\t%s :[%d]\t\t%s :[%d]\n", name1, score1, name2, score2);
    }
    else
    {
        printf("\tGame Draw.\n");
        printf("\tScore\n\t\t%s :[%d]\t\t%s :[%d]\n", name1, score1, name2, score2);
    }
}

void playSinglePlayer(Game* game, int mode)
{
    static sint32 score1 = 0, score2 = 0; // static to keep save score out of stack section

    for (sint32 i = 1; i <= 9; i++)
    {
        game->board[i] = i + '0'; // Initialize the board
    }

    sint32 choice, check;

    do
    {
        printBoard(game);

        if (game->currentPlayer == 1)
        {
            printf("\t\tPlayer 1, enter your choice (1-9, 0 to exit): ");
            scanf("%d", &choice);

            if (choice == 0)
            {
                printf("\tExiting the game.\n");
                return;
            }
        }
        else
        {
            // Computer player's turn
            if (mode == 1) // Simple mode
            {
                sint32 i;
                for (i = 1; i <= 9; i++)
                {
                    if (game->board[i] == i + '0')
                    {
                        uint8 temp = game->board[i]; // Save the current value
                        game->board[i] = 'O'; // Make the move
                        check = checkWinner(game);

                        if (check != -1)
                        {
                            break;
                        }

                        game->board[i] = temp; // Undo the move if it doesn't lead to an immediate win
                    }
                }

                if (i == 10) // No immediate winning move found
                {
                    // Choose a random available spot
                    srand(time(NULL));
                    do
                    {
                        choice = rand() % 9 + 1;
                    } while (game->board[choice] != choice + '0');
                }
            }
            else if (mode == 2) // Hard mode
            {
                // Find the first available winning move
                for (sint32 i = 1; i <= 9; i++)
                {
                    if (game->board[i] == i + '0')
                    {
                        uint8 temp = game->board[i]; // Save the current value
                        game->board[i] = 'O'; // Make the move
                        check = checkWinner(game);

                        if (check == 2)
                        {
                            break; // Found a winning move, break the loop
                        }

                        game->board[i] = temp; // Undo the move
                    }
                }

                if (check != 2)
                {
                    // If no winning move found, play defensively
                    for (sint32 i = 1; i <= 9; i++)
                    {
                        if (game->board[i] == i + '0')
                        {
                            uint8 temp = game->board[i]; // Save the current value
                            game->board[i] = 'X'; // Pretend to make a move for player 1
                            check = checkWinner(game);

                            if (check == 1)
                            {
                                game->board[i] = 'O'; // Found a defensive move, make the move
                                break; // Break the loop
                            }

                            game->board[i] = temp; // Undo the move
                        }
                    }
                }

                if (check == -1)
                {
                    // If no winning or defensive move found, choose a random available spot
                    srand(time(NULL));
                    do
                    {
                        choice = rand() % 9 + 1;
                    } while (game->board[choice] != choice + '0');
                }
            }
        }

        uint8 mark = (game->currentPlayer == 1) ? 'X' : 'O';
        printBoard(game);

        if (!markBoard(game, choice))
        {
            continue; // Skip the rest of the current iteration and prompt the same player for another choice iteration
        }

        check = checkWinner(game);

        if (check == -1)
        {
            game->currentPlayer = (game->currentPlayer == 1) ? 2 : 1;
        }

    } while (check == -1);

    if (check == 1)
    {
        if (game->currentPlayer == 1)
        {
            printf("\tCongratulations Player 1, you have won.\n");
            score1++;
        }
        else
        {
            printf("\tComputer has won.\n");
            score2++;
        }
        printf("\tScore\n\t\tPlayer 1 : [%d]\t\tComputer : [%d]\n", score1, score2);
    }
    else
    {
        printf("\tGame Draw.\n");
        printf("\tScore\n\t\tPlayer 1 : [%d]\t\tComputer : [%d]\n", score1, score2);
    }
}

void printBoard(Game* game)
{
    clearScreen();
    printf("\n\t<======Welcome to Tic Tac Toe!======>\n\n");
    if (mode == 1)
		printf("\t%s (X)  -  %s (O)\n\n", name1, name2);
	else
		printf("\t%s (X)  -  Computer (O)\n\n", name1);
    printf("\t\t     |     |     \n");
    printf("\t\t  %c  |  %c  |  %c \n", game->board[1], game->board[2], game->board[3]);
    printf("\t\t_____|_____|_____\n");

    printf("\t\t     |     |     \n");
    printf("\t\t  %c  |  %c  |  %c \n", game->board[4], game->board[5], game->board[6]);
    printf("\t\t_____|_____|_____\n");

    printf("\t\t     |     |     \n");
    printf("\t\t  %c  |  %c  |  %c \n", game->board[7], game->board[8], game->board[9]);
    printf("\t\t     |     |     \n\n");
}

sint32 markBoard(Game* game, sint32 choice)
{
    uint8 mark = (game->currentPlayer == 1) ? 'X' : 'O';

    if (choice >= 1 && choice <= 9 && game->board[choice] == choice + '0')
    {
        game->board[choice] = mark;
        return 1; // Valid move
    }
    else
    {
        printf("\t\tInvalid move. Please try again.\n");
        return 0; // Invalid move
    }
}

sint32 checkWinner(Game* game)
{
    sint32 i;
    uint8 mark = (game->currentPlayer == 1) ? 'X' : 'O';

    for (i = 1; i <= 9; i += 3)
    {
        if (game->board[i] == mark && game->board[i + 1] == mark && game->board[i + 2] == mark)
        {
            return 1; // Player has won
        }
    }

    for (i = 1; i <= 3; i++)
    {
        if (game->board[i] == mark && game->board[i + 3] == mark && game->board[i + 6] == mark)
        {
            return 1; // Player has won
        }
    }

    if ((game->board[1] == mark && game->board[5] == mark && game->board[9] == mark) ||
        (game->board[3] == mark && game->board[5] == mark && game->board[7] == mark))
    {
        return 1; // Player has won
    }

    for (i = 1; i <= 9; i++)
    {
        if (game->board[i] == i + '0')
        {
            return -1; // Game still in progress
        }
    }

    return 0; // Game is a draw
}



