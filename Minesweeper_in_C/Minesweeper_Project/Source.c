#include "Header.h"




int main(void) {

	char BoardToPrint[20][20];
	int BoardBombsNearby[20][20];
	bool RevealedLocations[20][20];
	bool FlaggedLocations[20][20];
	bool done = false;
	
	
	int win = 0;
	

	int User_Row, User_Col, User_flag_reveal;




	getGlobalSetupData();
	createEmptyBoardArrays(BoardToPrint, BoardBombsNearby, RevealedLocations,FlaggedLocations);

	printBoard(BoardToPrint);

	placeBombs(BoardBombsNearby);
	calculateNearbyBombs(BoardBombsNearby);





	while (!done) {
		//Collects User Move
		printf("\nPress 1 for flag and 2 for reveal: ");
		scanf_s("%d", &User_flag_reveal);
		printf("\nPick a row number: ");
		scanf_s("%d", &User_Row);
		User_Row--;
		printf("\nPick a column number: ");
		scanf_s("%d", &User_Col);
		User_Col--;

		if (User_flag_reveal == 1) { //FLAG
			if (!FlaggedLocations[User_Row][User_Col])
				FlaggedLocations[User_Row][User_Col] = true;
				//places flag at users coordinates
			else
				FlaggedLocations[User_Row][User_Col] = false;
				//if there already was a flag, takes it away
		}
		else if (User_flag_reveal == 2) { //REVEAL
			if (FlaggedLocations[User_Row][User_Col])
				FlaggedLocations[User_Row][User_Col] = false;
			RevealedLocations[User_Row][User_Col] = true;

		}

		expandZeros(BoardBombsNearby, RevealedLocations, FlaggedLocations);

		win = updateBoardToPrint(BoardToPrint, BoardBombsNearby, RevealedLocations, FlaggedLocations);

		printBoard(BoardToPrint);

		if (win == -1) {
			printf("\n\nYou lose!");
			done = true;
		}
		else if (win == 1) {
			printf("You win! You flagged all the bombs correctly!");
			done = true;
		}


	}


	return 0;
}

