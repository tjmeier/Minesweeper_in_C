#include "MineV2Header.h"

void getBoardSize(unsigned int* length, unsigned int* height) {

	//Asks user for Board Length
	printf("\nBoard Length: ");
	scanf_s("%d", length);
	
	//Length out of range condition
	while (*length <= 0 || *length > MAXLENGTH) {
		printf("\nTry again. Must be in between 1 and %d", MAXLENGTH);
		printf("\nBoard Length: ");
		scanf_s("%d", length);
	}
	
	

	//Asks user for Board Height
	printf("Board Height: ");
	scanf_s("%d", height);

	//Height out of range condition
	while (*height <= 0 || *height > MAXHEIGHT) {
		printf("\nTry again. Must be in between 1 and %d", MAXHEIGHT);
		printf("\nBoard Height: ");
		scanf_s("%d", height);
	}



}

void getUserMove(unsigned int* row, unsigned int* col, unsigned int* flag_reveal, unsigned int length, unsigned int height) {
	
	//------ Asks user for Reveal / Flag selection ------
	char flag_reveal_input;
	printf("Reveal 'r' or Flag 'f': ");
	scanf_s("%c", &flag_reveal_input, 1);

	//column out of range condition
	while (flag_reveal_input != 'r' && flag_reveal_input != 'f')  {
		printf("\nTry again. Must be exactly the character 'f' or 'r' only");
		printf("\nReveal or Flag: ");
		scanf_s("%c", &flag_reveal_input, 1);
	}

	if (flag_reveal_input == 'f')
		*flag_reveal = 0;
	else if (flag_reveal_input == 'r')
		*flag_reveal = 1;


	
	//------ Asks user for Row Selection ------
	printf("\nRow: ");
	scanf_s("%u", row);

	//row out of range condition
	while (*row <= 0 || *row > height) {
		printf("\nTry again. Must be in between 1 and %d", height);
		printf("\nRow: ");
		scanf_s("%u", row);
	}




	//------ Asks user for Column Selection ------
	printf("Column: ");
	scanf_s("%u", col);

	//column out of range condition
	while (*col <= 0 || *col > length) {
		printf("\nTry again. Must be in between 1 and %d", length);
		printf("\nColumn: ");
		scanf_s("%u", col);
	}





}

void getQtyBombs(unsigned int maximum_bombs, unsigned int* qty_bombs) {
	printf("Quantity of Bombs: ");
	scanf_s("%d", qty_bombs);

	while (*qty_bombs <= 0 || *qty_bombs > maximum_bombs) {
		printf("\nTry again. Must be in between 1 and %d", maximum_bombs);
		printf("\nQuantity of Bombs: ");
		scanf_s("%d", qty_bombs);
	}
}

unsigned int getPlayAgain(void) {
	char play_again;
	printf("\nWould you like to play again? 'y' or 'n'");
	scanf_s("%c", &play_again, 1);

	while (play_again != 'y' && play_again != 'n') {
		printf("\nTry again. Must be exactly the character 'y' or 'n' only");
		printf("\nWould you like to play again?: ");
		scanf_s("%c", &play_again, 1);
	}
	if (play_again == 'y')
		return 1;
	else
		return 0;



}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printBoard(struct Square Board[MAXHEIGHT][MAXLENGTH], unsigned int* length, unsigned int* height) {

	//(adapted from Original Minesweeper in C project printBoard function)

	unsigned int i, j;
	
	printf("   "); //prints a row of column indicators
	for (j = 0; j < *length; j++) {
		printf("%2d  ",j+1);
	}
	printf("\n");


	//--------------------prints main interior-----------
	for (i = 0; i < *height; i++) {

		printf("  ");
		for (j = 0; j < *length; j++) {
			printf("+---");
		} 
		printf("+\n");



		printf("%2d", i+1); //prints a row indicator before printing the row contents
		for (j = 0; j < *length; j++) {
			printf("| %c ",Board[i][j].symbol); //data pulled from symbol of each Square in Board
		}
		printf("|\n");
	}
	//------------------------------------
	
	printf("  "); //prints final bottom boundary
	for (j = 0; j < *length; j++) {
		printf("+---");
	}
	printf("+\n\n");


}


void initializeBoard(struct Square Board[MAXHEIGHT][MAXLENGTH] /*defined in Header file*/, unsigned int* length, unsigned int* height, unsigned int* qty_bombs) {

	//Initialize Pointers
	struct Square* const p_first_Square = Board; //p_firstSquare is a constant pointer to the first square in Board
	struct Square* p_current_Square;
	struct Square* p_null_Square = (struct Square*)0; //creates a null Square pointer extra rigorously
	
	//Initialize Step 1: Get Board Size; recorded to length and height
	getBoardSize(length, height);
	unsigned int qty_squares = (*length) * (*height);
	getQtyBombs(qty_squares, qty_bombs);

	//Initialize Step 2: Zero out data for each Square

	p_current_Square = p_first_Square;

	for (unsigned int index = 0; index < qty_squares; index++){


		p_current_Square++;
	}

	//Initialize Step 2: Zero out data and establish nearby_Squares array for the pointers of the 8 surrounding squares for each Square used in Board (QTYSQUARENEIGHBORS must be 8 for this)



	for (unsigned int row = 0; row < *height; row++) {
		p_current_Square = &Board[row][0]; //resets pointer to the beginning of each new row

		for (unsigned int col = 0; col < *length; col++) {
			p_current_Square->symbol = ' ';
			p_current_Square->is_revealed = 0;
			p_current_Square->is_flagged = 0;
			p_current_Square->has_bomb = 0;
			p_current_Square->qty_nearby_bombs = 0;

			p_current_Square->nearby_Squares[0] = &Board[row - 1][col]; //up
			p_current_Square->nearby_Squares[1] = &Board[row + 1][col]; //down
			p_current_Square->nearby_Squares[2] = &Board[row][col - 1]; //left
			p_current_Square->nearby_Squares[3] = &Board[row][col + 1]; //right

			p_current_Square->nearby_Squares[4] = &Board[row - 1][col - 1]; //up left
			p_current_Square->nearby_Squares[5] = &Board[row - 1][col + 1]; //up right
			p_current_Square->nearby_Squares[6] = &Board[row + 1][col - 1]; //down left
			p_current_Square->nearby_Squares[7] = &Board[row + 1][col + 1]; //down right

			p_current_Square++; //walks pointer through each row
		}
	}

	//In nearby_Squares array nulling out pointers to invalid squares (not in the Board array or not being used)

	for (unsigned int row = 0; row < *height; row++) {
		Board[row][0].nearby_Squares[2] = p_null_Square; //has no left
		Board[row][0].nearby_Squares[4] = p_null_Square; //has no up left
		Board[row][0].nearby_Squares[6] = p_null_Square; //has no down left

		Board[row][*length - 1].nearby_Squares[3] = p_null_Square; //has no right
		Board[row][*length - 1].nearby_Squares[5] = p_null_Square; //has no up right
		Board[row][*length - 1].nearby_Squares[7] = p_null_Square; //has no down right

		/*
		counting through far left and right columns

		X			X
		X			X
		X			X
		X			X
		X			X
		
		*/
	}

	for (unsigned int col = 0; col < *length; col++) {
		Board[0][col].nearby_Squares[0] = 0; //has no up
		Board[0][col].nearby_Squares[4] = 0; //has no up left
		Board[0][col].nearby_Squares[5] = 0; //has no up right

		Board[*height - 1][col].nearby_Squares[1] = 0; //has no down
		Board[*height - 1][col].nearby_Squares[6] = 0; //has no down left
		Board[*height - 1][col].nearby_Squares[7] = 0; //has no down right

		/*
		counting through far left and right columns

		X X X X X X



		X X X X X X

		*/


	}
}

void placeBombs(struct Square Board[MAXHEIGHT][MAXLENGTH], unsigned int length, unsigned int height, unsigned int qty_bombs) {
	unsigned int current_bomb, rand_i, rand_j;

	//Repeats for the quantity of bombs

	//Places a bomb at a random row and column
	for (current_bomb = 0; current_bomb < qty_bombs; current_bomb++) {
		do {
			rand_i = rand() % height; //keeps generating random coordinates until there is NOT a bomb at that Square
			rand_j = rand() % length;
		} while (Board[(rand_i)][(rand_j)].has_bomb);

		Board[(rand_i)][(rand_j)].has_bomb = 1;

	}
}

void getQtyNearbyBombs(struct Square Board[MAXHEIGHT][MAXLENGTH], unsigned int length, unsigned int height) {
	unsigned int i, j, k;

	//cycles through all the squares in Board
	for (i = 0; i < height; i++) {
		for (j = 0; j < length; j++) {
			
			if (Board[i][j].has_bomb) { //if a Square has a bomb, adds 1 to the qty_nearby_bombs for each Square in nearby_Squares
				for (k = 0; k < QTYSQUARENEIGHBORS; k++) {
					if (Board[i][j].nearby_Squares[k]) {
						(Board[i][j].nearby_Squares[k])->qty_nearby_bombs++;
					}
				}
			}
		}
	}
}

unsigned int updateGameState(struct Square Board[MAXHEIGHT][MAXLENGTH], unsigned int length, unsigned int height, unsigned int qty_bombs) {
	unsigned int i, j, correct_flags = 0, incorrect_flags = 0;
	struct Square* p_current_Square;

	for (i = 0; i < height; i++) {
		for (j = 0; j < length; j++) {

			if (Board[i][j].is_flagged) {
				printf("updateGameState 1: There was a flag at (%u, %u), so we drew an F there.\n", i, j);
				Board[i][j].symbol = 'F'; //Flagged squares show an F

				if (Board[i][j].has_bomb) //if the flagged square also had a bomb, it was a correct flag
					correct_flags++;
				else
					incorrect_flags++;
			}



			else if (Board[i][j].is_revealed) {
				printf("updateGameState 5: We see that the square at (%u, %u) is supposed to be revealed.\n", i, j);
				if (Board[i][j].has_bomb) {
					printf("updateGameState 2: There was a bomb at (%u, %u), so we drew an F there.\n", i, j);
					Board[i][j].symbol = 'B'; //Revealed squares with a bomb show a B
					return 2; //Lose Condition
				}
				else if (Board[i][j].qty_nearby_bombs > 0) {
					printf("updateGameState 3: There was a %u nearby bombs at (%u, %u), so we drew a number there.\n", Board[i][j].qty_nearby_bombs, i, j);
					Board[i][j].symbol = (char)(Board[i][j].qty_nearby_bombs + ASCIIDECIMALCHAROFFSET); //Revealed squares with a number will be that number
				}
				else {
					printf("updateGameState 4: There was a 0 at (%u, %u), so we drew a %c there.\n", i, j, 219);
					Board[i][j].symbol = 219; //Revealed squares with nothing in them will be a filled box ASCII characte
				}
			}
		}


	}


	if (correct_flags == qty_bombs && incorrect_flags == 0)
		return 1; //Win Condition
	else
		return 0; //Continue Condition
}

void expandZeroSquares(struct Square Board[MAXHEIGHT][MAXLENGTH], unsigned int length, unsigned int height){
	unsigned int i, j, k, repeat_check, run_counter = 0;
	struct Square* p_current_Square;


	do {
		repeat_check = 0;
		run_counter++;

		for (i = 0; i < height; i++) {
			p_current_Square = &Board[i][0];
			for (j = 0; j < length; j++) {

				if (p_current_Square->is_revealed && p_current_Square->qty_nearby_bombs == 0) { //checks if the current Square is revealed and has no nearby bombs i.e. is a 0 Square
					printf("\n\nexpandZeroSquares 1: Run Count %u: We see at (%u, %u) there is a revealed square with a zero value for nearby bombs.\n",run_counter, i, j);

					//In Minesweeper, revealed 0 Squares will automatically reveal the 8 surrounding Squares
					for (k = 0; k < QTYSQUARENEIGHBORS; k++) {
						if (p_current_Square->nearby_Squares[k]) { //checks if it's a valid pointer
							printf("expandZeroSquares 1: Run Count %u; The nearby_Squares[%u] of (%u, %u) is valid and will be revealed.\n", run_counter, k, i, j);
							if (!((p_current_Square->nearby_Squares[k])->is_revealed) && (p_current_Square->nearby_Squares[k])->qty_nearby_bombs == 0) {
								printf("expandZeroSquares 1: Run Count %u; The nearby_Squares[%u] of (%u, %u) is an unrevealed 0 square. Repeat check will be 1.\n", run_counter, k, i, j);
								repeat_check = 1; //if any of the Squares surrounding the 0 Square is an unrevealed 0 Square, then the loop will continue the expansion
							}
							(p_current_Square->nearby_Squares[k])->is_revealed = 1;
						}
					}
				}

				p_current_Square++;
			}
		}

	} while (repeat_check);







	//Test for the Revealed:
	printf("->is_revealed");
	for (i = 0; i < height; i++) {
		p_current_Square = &Board[i][0];
		printf("\n");
		for (j = 0; j < length; j++) {
			printf("%d ", p_current_Square->is_revealed);
			p_current_Square++;

		}
	}

	printf("\n\n");

	printf("->is_flagged");
	for (i = 0; i < height; i++) {
		p_current_Square = &Board[i][0];
		printf("\n");
		for (j = 0; j < length; j++) {
			printf("%d ", p_current_Square->is_flagged);
			p_current_Square++;

		}
	}

	printf("\n\n");

	printf("->has_bomb");
	for (i = 0; i < height; i++) {
		p_current_Square = &Board[i][0];
		printf("\n");
		for (j = 0; j < length; j++) {
			printf("%d ", p_current_Square->has_bomb);
			p_current_Square++;

		}
	}

	printf("\n\n");

	printf("->qty_nearby_bombs");
	for (i = 0; i < height; i++) {
		p_current_Square = &Board[i][0];
		printf("\n");
		for (j = 0; j < length; j++) {
			printf("%d ", p_current_Square->qty_nearby_bombs);
			p_current_Square++;

		}
	}

	printf("\n\n");






}

