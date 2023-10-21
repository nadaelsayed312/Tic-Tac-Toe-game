#include "STD_TYPES.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "TicTacToe_Project.h"

static uint8 a[SizeofBoard]; 

uint8 name1[25], name2[25];
sint32 mode;
int main()
{
    
    do //*********************playAgain*****************************
    {
        printf("\n\t<======Welcome to Tic Tac Toe!======>\n");
        printf("\tPlease enter your name: ");
        scanf("%[^\n]%*c", name1);
        printf("\tHi %s\n", name1);
        clearScreen();
		//******************1st list @ program***********************
        printf("\n\t<======Welcome to Tic Tac Toe!======>\n");
        printf("\n\tHi %s\n\n", name1);
        printf("\t\tSelect a mode:\n");
        printf("\t\t1. Multiplayer mode\n");
        printf("\t\t2. Single player mode\n");
        printf("\t\t3. Exit the program\n");
        printf("\t\tEnter your choice: ");

        // Read the input as a string instead of an integer
        char input[10];
        scanf("%s", input);

        // Convert the input to an integer using the atoi function
        mode = atoi(input);

        Game game; // Create an instance of the Game structure
        game.currentPlayer = 1; // Set the initial player
        int Mode,Who_1st, first, Res;
        switch (mode)
        {
            case 1:
                printf("\t\tPlayer 2, please enter your name: ");
                scanf(" %[^\n]%*c", name2);
                printf("Hi %s\n", name2);
                clearScreen();
				//******************2nd list @ program for mode 1***********************
                printf("\n\t<======Welcome to Tic Tac Toe!======>\n");
                printf("\n\t\t~~~[%s] and [%s] are now playing~~~\n", name1, name2);
                printf("\n\t\tWho wants to play first:\n");
                printf("\t\t1. Flip a coin (for random choice)\n");
                printf("\t\t2. %s choose who begins\n", name1);
                printf("\t\tEnter your choice: ");

                // Read the input as a string instead of an integer
                scanf("%s", input);

                // Convert the input to an integer using the atoi function
                Who_1st = atoi(input);

                switch (Who_1st)
                {
                    case 1:
                        Res = flipCoin();
                        game.currentPlayer = Res + 1;
                        break;
                    case 2:
					//******************sub 2nd list @ program for mode 1***********************
                        printf("\t\t\t\t1. %s\t\t",name1);
                        printf("\t\t2. %s\n",name2);
                        printf("\t\tEnter your choice: ");

                        // Read the input as a string instead of an integer
                        scanf("%s", input);

                        // Convert the input to an integer using the atoi function
                        first = atoi(input);

                        game.currentPlayer = first;
                        break;
                    default:
                        printf("\t\tInvalid input! Please try again.\n");
                        continue; // Go back to the beginning of the loop
                }

                playMultiplayer(&game); // Pass the address of the game structure to the multiplayer function
                break;

            case 2:
                clearScreen();
				//******************2nd list @ program for mode 2***********************
                printf("\n\t<======Welcome to Tic Tac Toe!======>\n");
                printf("\n\t\t~~~you are now playing against the Computer~~~\n", name1, name2);
                printf("\n\t\tWho wants to play first:\n");
                printf("\t\t1. Flip a coin (for random choice)\n");
                printf("\t\t2. %s choose who begins\n", name1);
                printf("\t\tEnter your choice: ");

                // Read the input as a string instead of an integer
                scanf("%s", input);

                // Convert the input to an integer using the atoi function
                Who_1st = atoi(input);

                switch (Who_1st)
                {
                    case 1:
                        Res = flipCoin();
                        game.currentPlayer = Res + 1;
                        break;
                    case 2:
					//******************sub 2nd list @ program for mode 2***********************
                        printf("\t\t\t\t1. %s\t\t",name1);
                        printf("\t\t2. Computer\n");
                        printf("\t\tEnter your choice: ");

                        // Read the input as a string instead of an integer
                        scanf("%s", input);

                        // Convert the input to an integer using the atoi function
                        first = atoi(input);

                        game.currentPlayer = first;
                        break;
                    default:
                        printf("\t\tInvalid input! Please try again.\n");
                        continue; // Go back to the beginning of the loop
                }
                //******************sub 2nd list @ program for mode 2***********************
                clearScreen();
                printf("\n\t<======Welcome to Tic Tac Toe!======>\n");
                printf("\n\t\t~~~you are now playing against the Computer~~~\n", name1, name2);
				printf("\t\tSelect a mode:\n");
				printf("\t\t1. Simple mode\n");
				printf("\t\t2. Hard mode\n");
				printf("\t\t3. Exit the program\n");
				printf("\t\tEnter your choice: ");	
				scanf("%s", input);
                Mode = atoi(input);
				switch (Mode)
				{
					case 1:
						playSinglePlayer(&game,1);
						break;
					case 2:
						playSinglePlayer(&game,2);
						break;
					/*default:
                        printf("\t\tInvalid input! Please try again.\n");
                        continue; // Goack to the beginning of the loop*/
				}
				
				break;

            case 3:
                printf("\n\tExiting the game.\n");
                return 0;

            default:
                printf("\t\tInvalid input! Please try again.\n");
                continue; // Go back to the beginning of the loop
        }

        int playAgain;
        printf("\tDo you want to play again? (1 for Yes, 0 for No): ");
        scanf("%d", &playAgain);
        clearScreen();

        if (playAgain != 1)
            break; // Exit the loop if playAgain is not 1

    } while (1);

    return 0;
}