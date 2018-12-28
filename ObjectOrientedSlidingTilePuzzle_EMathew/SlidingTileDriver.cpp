#include <iostream>				// for general IO
#include <iomanip>				// for setw()
using namespace std;

#include <string.h>				// for strcpy()
#include <conio.h>				// for getche()
#include <stdlib.h>				//for srand() and rand()
#include <time.h>				//for time()
#include <windows.h>			// for COLOR!
#include <SlidingTileHeader.h>

// direction codes (part of the slideTile() interface)
#define SLIDE_UP		1		// pass to slideTile() to trigger UP movement
#define SLIDE_DOWN		2		// pass to slideTile() to trigger DOWN movement
#define SLIDE_LEFT		3		// pass to slideTile() to trigger LEFT movement
#define SLIDE_RIGHT		4		// pass to slideTile() to trigger RIGHT movement


int main() {
	SlidingPuzzle myBoard;
	// Declarations
	int** root = myBoard.getRoot(); //sets root to the address of theBoard[0][0]
	int** solvedRoot = myBoard.getSolvedRoot();//sets solvedRoot to the address of solvedBoard[0][0]
	int rows = 0;
	int cols = 0;
	rows = myBoard.getRows(); //sets rows to user inputted height
	cols = myBoard.getCols(); //sets rows to user inputted width

	// Seed the Pseudo-Random Number Generator (system clock)
	srand((unsigned int)time(NULL));

	myBoard.InitializeBoard(root, rows, cols);				//sends input to method InitializeBoard to fill the array with the values needed.
	myBoard.InitializeSolvedBoard(solvedRoot, rows, cols); //sends input to method InitializeSolvedBoard to fill the array of solvedBoard.
	myBoard.PrintBoard(root, rows, cols); cout << boolalpha; //sends input to method PrintBoard to print the completed array.
	if (myBoard.isBoardSolved(solvedRoot, root, rows, cols)) { //sends input to method isBoardSolved to verify the displayed board is accurate
		cout << "This board is currently solved" << endl;
	}
	cout << "Scrambling the game tiles..." << endl << endl;
	myBoard.ScrambleBoard(solvedRoot, root, rows, cols);	//scrambles the tiles using scrambleBoard function. 
	cout << "Scrambling complete, press enter to begin solving. " << endl << endl;
	cin.get();
	cout << "GOOD LUCK! " << endl;
	cin.get(); //gets user input of enter to start the puzzle
	system("CLS"); // clear the screen to began solving.

	myBoard.PrintBoard(root, rows, cols); //prints new scrambled board. 
	cout << endl << endl;
	cout << "<W -> UP : <A -> LEFT : S -> DOWN : D -> RIGHT]" << endl;
	cout << "INPUT: ";
	myBoard.BoardMoves(solvedRoot, root, rows, cols); //sends input into method boardMoves to move the tiles as per user input
	cout << endl;
	cout << "Congratulations! You solved the board! " << endl;
	system("PAUSE");
	myBoard.SlidingPuzzleDestructor(solvedRoot, root, rows, cols);//sends input into method SlidingPuzzleDestructor to deallocate memory
	// Exit
	return 0;
}