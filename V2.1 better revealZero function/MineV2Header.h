#ifndef header_h
#define header_h


#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 25
#define MAXHEIGHT 25
#define QTYSQUARENEIGHBORS 8
#define ASCIIDECIMALCHAROFFSET 48

//In order to define the structure in all C files that need it
struct Square {
	char symbol;
	unsigned int is_revealed : 1;
	unsigned int is_flagged : 1;
	unsigned int function_revealNeighbors_was_ran;
	unsigned int has_bomb : 1;
	unsigned int qty_nearby_bombs : 4;
	struct Square* nearby_Squares[QTYSQUARENEIGHBORS];
	/* indices for nearby_Squares:
	0 = up, 1 = down, 2 = left, 3 = right, 4 = up left, 5 = up right, 6 = down left, 7 = down right
	according to Step 2 of initializeBoard */
};


//Prototypes
void getBoardSize(unsigned int *length, unsigned int *height);
void getQtyBombs(unsigned int maximum_bombs, unsigned int* qty_bombs);
void initializeBoard(struct Square Board[MAXHEIGHT][MAXLENGTH], unsigned int* length, unsigned int* height, unsigned int *qty_bombs);
void printBoard(struct Square Board[MAXHEIGHT][MAXLENGTH], unsigned int* length, unsigned int* height);
void placeBombs(struct Square Board[MAXHEIGHT][MAXLENGTH], unsigned int length, unsigned int height, unsigned int qty_bombs);
void getQtyNearbyBombs(struct Square Board[MAXHEIGHT][MAXLENGTH], unsigned int length, unsigned int height);
unsigned int updateGameState(struct Square Board[MAXLENGTH][MAXHEIGHT], unsigned int length, unsigned int height, unsigned int qty_bombs);
void expandZeroSquares(struct Square Board[MAXLENGTH][MAXHEIGHT], unsigned int length, unsigned int height);
void getUserMove(unsigned int* row, unsigned int* col, unsigned int* flag_reveal, unsigned int length, unsigned int height);
unsigned int getPlayAgain(void);

unsigned int revealNeighbors(struct Square* revealMyNeighbors);


#endif