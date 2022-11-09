#include "Header.h"

//Sets up a blank game
void getGlobalSetupData(void) {
	//Gets user input to setup the game and stores in global vars
	printf("\nBoard Length: ");
	scanf_s("%d", &bCols);
	printf("\nBoard Height: ");
	scanf_s("%d", &bRows);
	printf("\nQuantity of Bombs: ");
	scanf_s("%d", &bombsQty);
	printf("\n\n");
}



void createEmptyBoardArrays(char board[20][20], int boardData[20][20], bool revealed[20][20],bool flagged[20][20]) {
	int i, j;

	for (i = 0; i < bRows; i++) {

		for (j = 0; j < bCols; j++) {
			board[i][j] = ' ';
			boardData[i][j] = 0;
			revealed[i][j] = false;
			flagged[i][j] = false;
		}
	}

}


void printBoard(char board[20][20]) {
	int i, j;

	
	
	printf("   "); //prints a row of column indicators
	for (j = 0; j < bCols; j++) {
		printf("%2d  ",j+1);
	}
	printf("\n");


	//--------------------prints main interior-----------
	for (i = 0; i < bRows; i++) {

		printf("  ");
		for (j = 0; j < bCols; j++) {
			printf("+---");
		} 
		printf("+\n");



		printf("%2d", i+1); //prints a row indicator before printing the row contents
		for (j = 0; j < bCols; j++) {
			printf("| %c ",board[i][j]);
		}
		printf("|\n");
	}
	//------------------------------------
	
	printf("  "); //prints final bottom boundary
	for (j = 0; j < bCols; j++) {
		printf("+---");
	}
	printf("+\n\n");



}
//Adding the bombs
void placeBombs(int boardData[20][20]) {
	int currentBomb, rand_i, rand_j;

	//Repeats for the quantity of bombs

	//Places a bomb at a random row and column
	for (currentBomb = 0; currentBomb < bombsQty; currentBomb++) {
		do {
			rand_i = rand() % bRows; //keeps generating random coordinates until there is not a bomb at them
			rand_j = rand() % bCols;
		} while (boardData[(rand_i)][(rand_j)] == -1);

		boardData[(rand_i)][(rand_j)] = -1;  //A bomb is indicated by -1
		
	}
}

void calculateNearbyBombs(int boardData[20][20]) {
	int i, j;

	for (i = 0; i < bRows; i++) {

		for (j = 0; j < bCols; j++) {
			
			if (boardData[i][j] != -1){
				//check the surroundings if the current location isn't a bomb
				boardData[i][j] = checkSurroundings(boardData,i,j,-1);
			}
		}
	}
}



int checkSurroundings(int boardData[20][20],int i,int j,int condition) {

	int appearanceCounter = 0;

	if (boardData[i][j - 1] == condition)
		appearanceCounter++;
	if (boardData[i][j + 1] == condition)
		appearanceCounter++;
	if (boardData[i + 1][j - 1] == condition)
		appearanceCounter++;
	if (boardData[i + 1][j + 1] == condition)
		appearanceCounter++;
	if (boardData[i + 1][j] == condition)
		appearanceCounter++;
	if (boardData[i - 1][j - 1] == condition)
		appearanceCounter++;
	if (boardData[i - 1][j + 1] == condition)
		appearanceCounter++;
	if (boardData[i - 1][j] == condition)
		appearanceCounter++;

	return appearanceCounter;
}


int updateBoardToPrint(char board[20][20], int boardData[20][20], bool revealed[20][20], bool flagged[20][20]) {
	int i, j;
	int Correct_Bombs = 0;

	for (i = 0; i < bRows; i++) {

		for (j = 0; j < bCols; j++) {

			if (flagged[i][j]) {
				board[i][j] = 'F';
				if (boardData[i][j] == -1)
					Correct_Bombs++;
			}
			else if (revealed[i][j]) {
				if (boardData[i][j] == -1) {
					board[i][j] = 'B'; //Marks a B if the revealed location was a bomb
					return -1;
				}
				else if (boardData[i][j] > 0)
					board[i][j] = '0' + boardData[i][j]; //Marks the number of nearby bombs if there are any nearby
				else
					board[i][j] = (char)177;
			}
			else
				board[i][j] = ' ';

		}
	}



	if (Correct_Bombs == bombsQty)
		return 1;
	else
		return 0;

}


void expandZeros(int boardData[20][20], bool revealed[20][20], bool flagged[20][20]) {
	int i, j;
	bool repeat_check;

		do {
			repeat_check = false;

			for (i = 0; i < bRows; i++) {

				for (j = 0; j < bCols; j++) {

					if (revealed[i][j] && boardData[i][j] == 0) {

						if (boardData[i][j - 1] == 0 && !revealed[i][j - 1])
							repeat_check = true;
						else if (boardData[i][j + 1] == 0 && !revealed[i][j + 1])
							repeat_check = true;
						else if (boardData[i + 1][j - 1] == 0 && !revealed[i + 1][j - 1])
							repeat_check = true;
						else if (boardData[i + 1][j + 1] == 0 && !revealed[i + 1][j + 1]) 
							repeat_check = true;
						else if (boardData[i + 1][j] == 0 && !revealed[i + 1][j]) 
							repeat_check = true;
						else if (boardData[i - 1][j - 1] == 0 && !revealed[i - 1][j - 1]) 
							repeat_check = true;
						else if (boardData[i - 1][j + 1] == 0 && !revealed[i - 1][j + 1]) 
							repeat_check = true;
						else if (boardData[i - 1][j] == 0 && !revealed[i - 1][j])
							repeat_check = true;
						

						revealed[i][j - 1] = true; //if a location that is revealed is valued 0, all 8 surrounding locations will be shown
						revealed[i][j + 1] = true;
						revealed[i + 1][j - 1] = true;
						revealed[i + 1][j + 1] = true;
						revealed[i + 1][j] = true;
						revealed[i - 1][j - 1] = true;
						revealed[i - 1][j + 1] = true;
						revealed[i - 1][j] = true;



					}
				}
			}
		} while (repeat_check);
}

 








/*
* 
* UNNEEDED CODE, WAS AN ATTEMPT TO STRICTLY AVOID CHECKING INDICES THAT
* DIDN'T EXSIST IN THE board
* 
int checkSurroundings(int boardData[20][20],int i,int j) {
	//Check corners

	int Bomb_Counter = 0;

	if (i == 0 && j == 0) { //in the top left corner
		if (BoardData[1][0] == -1)
			Bomb_Counter++;
		if (BoardData[1][1] == -1)
			Bomb_Counter++;
		if (BoardData[0][1] == -1)
			Bomb_Counter++;
	}

	else if (i == bRows && j == 0) { //in the bottom left corner
		if (BoardData[bRows-1][0] == -1)
			Bomb_Counter++;
		if (BoardData[bRows-1][1] == -1)
			Bomb_Counter++;
		if (BoardData[bRows][1] == -1)
			Bomb_Counter++;
	}

	else if (i == 0 && j == bCols) { //in the top right corner
		if (BoardData[0][bCols-1] == -1)
			Bomb_Counter++;
		if (BoardData[1][bCols-1] == -1)
			Bomb_Counter++;
		if (BoardData[1][bCols] == -1)
			Bomb_Counter++;
	}

	else if (i == bRows && j == bCols) { //in the bottom right corner
		if (BoardData[bRows][bCols - 1] == -1)
			Bomb_Counter++;
		if (BoardData[bRows-1][bCols - 1] == -1)
			Bomb_Counter++;
		if (BoardData[bRows-1][bCols] == -1)
			Bomb_Counter++;
	}

	else {
		if (i == 0); {//in the top row
			if (BoardData[i][j - 1] == -1)
				Bomb_Counter++;
			if (BoardData[i][j + 1] == -1)
				Bomb_Counter++;
			if (BoardData[i + 1][j] == -1)
				Bomb_Counter++;
			if (BoardData[i + 1][j - 1] == -1)
				Bomb_Counter++;
			if (BoardData[i + 1][j + 1] == -1)
				Bomb_Counter++;
		}

		//finish later *****************
	}

	return Bomb_Counter;
}
*/