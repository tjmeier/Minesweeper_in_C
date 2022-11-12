#include "MineV2Header.h"


int main(void) {

	
	struct Square GameBoard[MAXHEIGHT][MAXLENGTH]; /*defined in Header file*/
	unsigned int board_length, board_height, qty_bombs, user_row, user_col, user_flag_reveal, done, win = 0, restart = 1;


	

	while (restart) {
		initializeBoard(GameBoard, &board_length, &board_height, &qty_bombs);

		/* Post Initialization Tests

		printf("---------Post Initialization Tests----------");
		if (&GameBoard[0][0] == (&GameBoard[0][0])->nearby_Squares[1]->nearby_Squares[3]->nearby_Squares[0]->nearby_Squares[2])
			printf("Nice man.");


		for (int i = 0; i < board_height; i++) {
			for (int j = 0; j < board_length; j++) {
				printf("(%d, %d): ", i, j);
				for (int k = 0; k < 8; k++) {
					printf("\n%x", (&GameBoard[i][j])->nearby_Squares[k]);
				}
				printf("\n\n");
			}
		}

		*/

		placeBombs(GameBoard, board_length, board_height, qty_bombs);
		getQtyNearbyBombs(GameBoard, board_length, board_height);

		/* Post Bomb Placement Tests

		printf("---------Post Bomb Placement Tests----------");
		for (int i = 0; i < board_height; i++) {
			for (int j = 0; j < board_length; j++) {
				if (GameBoard[i][j].has_bomb)
					GameBoard[i][j].symbol = 'B';
				else if (GameBoard[i][j].qty_nearby_bombs > 0)
					GameBoard[i][j].symbol = (char)(GameBoard[i][j].qty_nearby_bombs + ASCIIDECIMALCHAROFFSET);
			}
		}

		printBoard(GameBoard, &board_height, &board_height);
		*/
		done = 0;




		/*Main Game Loop*/
		while (!done) {
			printBoard(GameBoard, &board_length, &board_height);

			getUserMove(&user_row, &user_col, &user_flag_reveal, board_length, board_height);

			user_row--, user_col--; //to make the user choices compatible with array indexing

			if (user_flag_reveal) { //Reveal
				if (GameBoard[user_row][user_col].is_flagged)
					GameBoard[user_row][user_col].is_flagged = 0; //If there was a flag on the Square you try to reveal, it gets removed
				GameBoard[user_row][user_col].is_revealed = 1;
			}

			else { //Flag
				//Toggles the flag state 0 <-> 1
				if (GameBoard[user_row][user_col].is_flagged)
					GameBoard[user_row][user_col].is_flagged = 0;
				else
					GameBoard[user_row][user_col].is_flagged = 1;
			}
			
			expandZeroSquares(GameBoard, board_length, board_height);
			win = updateGameState(GameBoard, board_length, board_height, qty_bombs);

			if (win == 2) { //If the user hit a bomb
				printf("Boom! You lose.");
				revealAllBombs(GameBoard, board_length, board_height); //reveals all the bomb locations and shows the user the final board

				updateGameState(GameBoard, board_length, board_height, qty_bombs);
				printBoard(GameBoard, &board_length, &board_height);
				done = 1;
			}
			else if (win == 1) { //If the user correctly flagged every bomb
				printf("You correctly flagged all %u bombs!", qty_bombs);

				updateGameState(GameBoard, board_length, board_height, qty_bombs);
				printBoard(GameBoard, &board_length, &board_height); //shows the user the final board
				done = 1;
			}

		}

		restart = getPlayAgain();

	}



	}

