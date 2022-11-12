#include "MineV2Header.h"

//User Input Functions
void getBoardSize(unsigned int* length, unsigned int* height) {

	//Asks user for Board Length
	printf("\nBoard Length: ");
	scanf("%d", length);
	
	//Length out of range condition
	while (*length <= 0 || *length > MAXLENGTH) {
		printf("\nTry again. Must be in between 1 and %d", MAXLENGTH);
		printf("\nBoard Length: ");
		scanf("%d", length);
	}
	
	

	//Asks user for Board Height
	printf("Board Height: ");
	scanf("%d", height);

	//Height out of range condition
	while (*height <= 0 || *height > MAXHEIGHT) {
		printf("\nTry again. Must be in between 1 and %d", MAXHEIGHT);
		printf("\nBoard Height: ");
		scanf("%d", height);
	}



}

void getUserMove(unsigned int* row, unsigned int* col, unsigned int* flag_reveal, unsigned int length, unsigned int height) {
	
	//------ Asks user for Reveal / Flag selection ------
	char flag_reveal_input;
	printf("For reveal enter 'r' and for flag enter 'f' ");
	scanf("%c", &flag_reveal_input);

	//column out of range condition
	while (flag_reveal_input != 'r' && flag_reveal_input != 'f')  {
		printf("\nReveal or Flag: ");
		scanf("%c", &flag_reveal_input);
	}

	if (flag_reveal_input == 'f')
		*flag_reveal = 0;
	else if (flag_reveal_input == 'r')
		*flag_reveal = 1;


	
	//------ Asks user for Row Selection ------
	printf("\nRow: ");
	scanf("%u", row);

	//row out of range condition
	while (*row <= 0 || *row > height) {
		printf("\nTry again. Must be in between 1 and %d", height);
		printf("\nRow: ");
		scanf("%u", row);
	}




	//------ Asks user for Column Selection ------
	printf("Column: ");
	scanf("%u", col);

	//column out of range condition
	while (*col <= 0 || *col > length) {
		printf("\nTry again. Must be in between 1 and %d", length);
		printf("\nColumn: ");
		scanf("%u", col);
	}





}

void getQtyBombs(unsigned int maximum_bombs, unsigned int* qty_bombs) {
	printf("Quantity of Bombs: ");
	scanf("%d", qty_bombs);

	while (*qty_bombs <= 0 || *qty_bombs > maximum_bombs) {
		printf("\nTry again. Must be in between 1 and %d", maximum_bombs);
		printf("\nQuantity of Bombs: ");
		scanf("%d", qty_bombs);
	}
}

unsigned int getPlayAgain(void) {
	char play_again;
	printf("\nWould you like to play again? Enter 'y' for yes or 'n' for no");
	scanf("%c", &play_again, 1);

	while (play_again != 'y' && play_again != 'n') {
		printf("\nWould you like to play again?: ");
		scanf("%c", &play_again, 1);
	}
	if (play_again == 'y')
		return 1;
	else
		return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Minesweeper Logic Functions

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
			p_current_Square->function_revealNeighbors_was_ran = 0;

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
	time_t t;
	unsigned int current_bomb, rand_i, rand_j;

	srand((unsigned int)time(&t)); //seeds rand() function with the time

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
	unsigned int i, j, correct_flags = 0, incorrect_flags = 0, return_value = 0;
	struct Square* p_current_Square;

	for (i = 0; i < height; i++) {
		for (j = 0; j < length; j++) {

			if (Board[i][j].is_flagged) {
				Board[i][j].symbol = 'F'; //Flagged squares show an F

				if (Board[i][j].has_bomb) //if the flagged square also had a bomb, it was a correct flag
					correct_flags++;
				else
					incorrect_flags++;
			}



			else if (Board[i][j].is_revealed) {
				if (Board[i][j].has_bomb) {
					Board[i][j].symbol = 'B'; //Revealed squares with a bomb show a B
					return_value = 2; //Lose Condition
				}
				else if (Board[i][j].qty_nearby_bombs > 0)
					Board[i][j].symbol = (char)(Board[i][j].qty_nearby_bombs + ASCIIDECIMALCHAROFFSET); //Revealed squares with a number will be that number

				else
					Board[i][j].symbol = '#'; //Revealed squares with nothing in them will be a filled box ASCII character
			}

			else
				Board[i][j].symbol = ' ';
		}
	}


	if (correct_flags == qty_bombs && incorrect_flags == 0)
		return_value = 1; //Win Condition

	return return_value;
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

				if ((p_current_Square->is_revealed) && (p_current_Square->qty_nearby_bombs == 0) && !(p_current_Square->function_revealNeighbors_was_ran)) { //checks if the current Square is revealed and has no nearby bombs i.e. is a 0 Square

					//In Minesweeper, revealed 0 Squares will automatically reveal the 8 surrounding Squares
					//returns a 1 if any of the surrounding squares was also an unrevealed zero

					repeat_check += revealNeighbors(p_current_Square);
				}

				p_current_Square++;

			}
		}

				
	} while (repeat_check);





/*

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




*/

}


unsigned int revealNeighbors(struct Square* reveal_my_neighbors) {
	unsigned int is_any_neighbor_an_unrevealed_0 = 0;

	reveal_my_neighbors->function_revealNeighbors_was_ran = 1;

	for (int k = 0; k < QTYSQUARENEIGHBORS; k++) { //cycles through all neighbors with index k
		if (reveal_my_neighbors->nearby_Squares[k]) { //checks if it's a valid pointer
			if (!((reveal_my_neighbors->nearby_Squares[k])->is_revealed) && (reveal_my_neighbors->nearby_Squares[k])->qty_nearby_bombs == 0) {
				is_any_neighbor_an_unrevealed_0 = 1; //if any of the Squares surrounding the 0 Square is an unrevealed 0 Square, the return value will be 1
			}
			(reveal_my_neighbors->nearby_Squares[k])->is_revealed = 1; //reveals the neighbor
		}
	}

	return is_any_neighbor_an_unrevealed_0;
}

void revealAllBombs(struct Square Board[MAXHEIGHT][MAXLENGTH], unsigned int length, unsigned int height) {
	unsigned int i, j;
	struct Square* p_current_Square;

	for (i = 0; i < height; i++) {
		p_current_Square = &Board[i][0];
		for (j = 0; j < length; j++) {
			if (p_current_Square->has_bomb == 1) //checks every Square in the Board, any Square with a bomb will be revealed
				p_current_Square->is_revealed = 1;

			p_current_Square++;
		}
	}

}