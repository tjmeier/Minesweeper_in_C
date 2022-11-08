#ifndef HEADER_H
#define HEADER_H


//Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Global Variables
int bRows, bCols, bombsQty;


//Global Constants


//Prototypes


void getGlobalSetupData(void);
void createEmptyBoardArrays(char board[20][20], int boardData[20][20], bool revealed[20][20], bool flagged[20][20]);

void printBoard(char board[20][20]);

void placeBombs(int boardData[20][20]);
void calculateNearbyBombs(int boardData[20][20]);
int checkSurroundings(int boardData[20][20], int i, int j,int condition);


int updateBoardToPrint(char board[20][20], int boardData[20][20], bool revealed[20][20], bool flagged[20][20]);

void expandZeros(int boardData[20][20], bool revealed[20][20], bool flagged[20][20]);



#endif