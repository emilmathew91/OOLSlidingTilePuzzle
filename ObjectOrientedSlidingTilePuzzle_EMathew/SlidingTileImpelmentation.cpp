#include <SlidingTileHeader.h>
#include <conio.h>				// for getche()
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <string.h>				// for strcpy()



// CONSTRUCTOR
SlidingPuzzle::SlidingPuzzle() {//This method sets theBoard and solvedBoard. They will hold the address of another variable that holds an address. They are initalized to null. This is a double pointer.
	theBoard = NULL;
	solvedBoard = NULL;
}


int SlidingPuzzle::InitializeBoard(int **root, int rows, int cols) { //initialize theBoard
	cout << setw(30) << "WELCOME TO THE SLIDING TILE GAME" << endl;
	cout << "Please enter the number of Rows: ";
	cin >> height;//gets user input for rows
	cout << "Please enter the number of Columns: ";
	cin >> width;//gets user input for columns
	system("CLS");
	cout << "Creating a table of " << " " << height << " rows and " << width << " columns." << endl;
	theBoard = new(int*[height]);// Allocate an array of int* variables and attach to the double pointer.
	for (int i = 0; i < height; i++) {
		theBoard[i] = new(int[width]);// Allocate arrays of int variables and attach each array to one of the  pointers in theBoard's array of pointers.
	}
	int counter = 1;//sets column to 0
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			theBoard[i][j] = counter;//sets theBoard at that width to the counter value. each [] is a dereference so its not printing out the address.
			counter++;
		}
		theBoard[height - 1][width - 1] = 0;
	}
	//sets last row and col as 0 which is then used to swap for *
	return(theBoard[height][width], height, width);
}
int SlidingPuzzle::InitializeSolvedBoard(int **solvedRoot, int rows, int cols) { //initialize solvedboard, same as theBoard above
	solvedBoard = new(int*[height]);
	for (int i = 0; i < height; i++) {
		solvedBoard[i] = new(int[width]);//over here we are now looking at each of the height pointers, and allocating space next to it for the width pointers. 
	}
	int counter = 1;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			solvedBoard[i][j] = counter;
			counter++;
		}
		solvedBoard[height - 1][width - 1] = 0; //sets last row and col as 0 which is then used to swap for *
	}
	return(solvedBoard[height][width], height, width);
}


void SlidingPuzzle::PrintBoard(int **root, int rows, int cols) { //print board
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (theBoard[i][j] == 0) //replaces 0 with * by checking if the arrray holds value 0
			{
				// setting colors 
				//SetConsoleTextAttribute(hConsole, 2);
				cout << setw(3) << "   *";
			}
			else
			{
				// if the number is in the right position
				if (theBoard[i][j] == solvedBoard[i][j]) //matches theBoard with solvedBoard to see if the numbers are in the right place. 
					SetConsoleTextAttribute(hConsole, 2);
				else
					// if the number is not in the right position
					SetConsoleTextAttribute(hConsole, 4);

				cout << "  " << setw(3) << theBoard[i][j];
			}
		}
		cout << endl;
	}
	SetConsoleTextAttribute(hConsole, 12); // set text color
}
bool SlidingPuzzle::isBoardSolved(int** solvedRoot, int **root, int rows, int cols) {
	bool boardSolved = true;
	int row = 0;
	int col = 0;
	while (boardSolved && row < height)
	{
		if (solvedBoard[row][col] == theBoard[row][col])//compares the reference array to the array we have from main while function, compares row and col. 
		{
			col++;  //advances col to check
			if (col >= width) //makes move to row
			{
				row++; //advances row to check
				col = 0;
			}
		}
		else
			boardSolved = false;
	}
	return boardSolved; //returns true. 
	return false;
}
bool SlidingPuzzle::slideTile(int **root, int rows, int cols, int slideDirection) { //takes in board and slide direction, essentially tracks the pointer, by tracking 0.  
	int emptyRow;
	int emptyColumn;
	int emptySpace[2];
	bool legalMoves[4] = { 1,1,1,1 }; //moves max is one. 
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (theBoard[i][j] == 0)
			{
				emptyRow = i;
				emptyColumn = j;     //tracks empty row, aka pointer
			}
		}
	}
	if (emptyRow + 1 > (height - 1))        //checks for valid moves. 
		legalMoves[2] = false;
	else if (emptyRow - 1 < 0)
		legalMoves[3] = false;

	if (emptyColumn - 1 < 0)
		legalMoves[1] = false;
	else if (emptyColumn + 1 > (width - 1))
		legalMoves[0] = false;


	switch (slideDirection) //passes in slide direction
	{
	case 0:
		if (legalMoves[slideDirection]) //checks if moves is legal, no more elements than legalMoves array. 
		{
			theBoard[emptyRow][emptyColumn] = theBoard[emptyRow][emptyColumn + 1]; // moves empty column to the right
			theBoard[emptyRow][emptyColumn + 1] = 0; //makes that element 0
			emptyColumn = emptyColumn + 1; //reassigns empty column
		}
		break;
	case 1:
		if (legalMoves[slideDirection])
		{
			theBoard[emptyRow][emptyColumn] = theBoard[emptyRow][emptyColumn - 1];
			theBoard[emptyRow][emptyColumn - 1] = 0;
			emptyColumn = emptyColumn - 1;
		}
		break;
	case 2:
		if (legalMoves[slideDirection])
		{
			theBoard[emptyRow][emptyColumn] = theBoard[emptyRow + 1][emptyColumn];
			theBoard[emptyRow + 1][emptyColumn] = 0;
			emptyRow = emptyRow + 1;
		}
		break;
	case 3:
		if (legalMoves[slideDirection])
		{
			theBoard[emptyRow][emptyColumn] = theBoard[emptyRow - 1][emptyColumn];
			theBoard[emptyRow - 1][emptyColumn] = 0;
			emptyRow = emptyRow - 1;
		}
		break;
	}


	return false;
}

void SlidingPuzzle::ScrambleBoard(int** solvedRoot, int **root, int rows, int cols) {
	int slideDirection;
	while (SlidingPuzzle::isBoardSolved(solvedBoard, theBoard, height, width)) //only genearates random numbers while board is true. 
	{
		for (int i = 0; i < ((height * width) + 1); i++)
		{
			slideDirection = rand() % 5; //uses seed and then looks to see if random numer is under 5. 5 because the max number we move is up to 4. rand requires max-min +1. 
			SlidingPuzzle::slideTile(theBoard, height, width, slideDirection); //passes board array and slide direction random number to slideTile
		}
	}
}
void SlidingPuzzle::BoardMoves(int** solvedRoot, int **root, int rows, int cols) {
	invalid = false;
	while (!SlidingPuzzle::isBoardSolved(solvedBoard, theBoard, height, width))			//while isBoardSolved is false, compares puzzleBoard to isBoardSolved
	{
		key = _getch();
		system("CLS");       //clear screen

		// selecting the game controls
		switch (toupper(key))             //toupper makes input caps so we can match it. using switch statements. 
		{

		case '\0':
			invalid = false;
			break;
		case ' ':
			invalid = false;
			break;
		case 'W':								//match case W
			SlidingPuzzle::slideTile(theBoard, height, width, 2);          //sends 2 (aka up to slide tile)   
			invalid = false;
			break;
		case 'A':								//match case A
			SlidingPuzzle::slideTile(theBoard, height, width, 0);          //sends 0 (aka left to slide tile) 
			invalid = false;
			break;
		case 'S':								//match case S
			SlidingPuzzle::slideTile(theBoard, height, width, 3);			//sends 3 (aka down to slide tile) 
			invalid = false;
			break;
		case 'D':								//match case W
			SlidingPuzzle::slideTile(theBoard, height, width, 1);			//sends 1 (aka right to slide tile) 
			invalid = false;
			break;
		default: //default case is invalid input
			invalid = true;
			break;
		}
		SlidingPuzzle::PrintBoard(theBoard, height, width);				//print board
		cout << endl << endl;
		cout << "[W - Up] [S - Down] [A - Left] [D - Right]" << endl;
		if (invalid)//checks for invalid input
		{
			cout << "Invalid Input - [" << key << "].\nPlease enter a valid input of W, A, S or D." << endl;
			cout << "Please press enter." << endl;
			invalid = false;
			cin.get();
		}
		else {
			cout << "Please enter your next input of W, S, A or D.";
		}
	}
}
void SlidingPuzzle::SlidingPuzzleDestructor(int** solvedRoot, int **root, int rows, int cols) {//deallocate the memory
	for (int i = 0; i < height; i++) {
		delete[] solvedBoard[i];
	}
	delete[] solvedBoard;
	for (int i = 0; i < height; i++) {
		delete[] theBoard[i];
	}
	delete[] theBoard;

}

//getters
int** SlidingPuzzle::getRoot() {
	return theBoard;
}
int** SlidingPuzzle::getSolvedRoot() {
	return solvedBoard;
}
int SlidingPuzzle::getRows() {
	return height;
}
int SlidingPuzzle::getCols() {
	return width;
}