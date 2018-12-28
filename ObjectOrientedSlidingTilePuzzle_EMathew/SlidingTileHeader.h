#pragma once
#pragma once
//HEADER FILE

#ifndef __SlidingPuzzle__
#define __SlidingPuzzle__

#include <iostream>				// for general IO
using namespace std;

#ifndef __TRUE_FALSE__
#define __TRUE_FALSE__
#define TRUE 1
#define FALSE 0


// direction codes (part of the slideTile() interface)
#define SLIDE_UP		1		// pass to slideTile() to trigger UP movement
#define SLIDE_DOWN		2		// pass to slideTile() to trigger DOWN movement
#define SLIDE_LEFT		3		// pass to slideTile() to trigger LEFT movement
#define SLIDE_RIGHT		4		// pass to slideTile() to trigger RIGHT movement
#endif

// CLASS RECTANGLE
class SlidingPuzzle {
private:
	int height;//used to work on table rows
	int width;//used for table columns
	int** theBoard;//the board i work off of
	int** solvedBoard;//solved board for comparison
	bool invalid;//invalid boolean for keystrokes
	char key;//key that user inputs


public:
	// CONSTRUCTOR
	SlidingPuzzle();

	//GETTERS
	int** getRoot();//returns theBoard
	int** getSolvedRoot();//returns solvedBoard
	int getRows();//returns height
	int getCols();//returns width

	//SETTERS
	int InitializeBoard(int **root, int rows, int cols);//initalizes the board, arguments are double pointer for theBoard, rows, and cols
	int InitializeSolvedBoard(int **solvedRoot, int rows, int cols);//initalizes the solvedBoard, arguments are double pointer for solvedBoard, rows, and cols
	bool isBoardSolved(int** solvedRoot, int **root, int rows, int cols);		// indicates if the board is in the SOLVED state
	void PrintBoard(int **root, int rows, int cols); //prints theBoard
	bool slideTile(int **root, int rows, int cols, int moves);// slides the tile
	void ScrambleBoard(int** solvedRoot, int **root, int rows, int cols);	//scrambles using pseudo random seed
	void BoardMoves(int** solvedRoot, int **root, int rows, int cols); //moves tiles
	void SlidingPuzzleDestructor(int** solvedRoot, int **root, int rows, int cols);//destructor to free memory
}; // end 
#endif#pragma once