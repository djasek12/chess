/*Includes*/
#include "../include/Move.h"
#include "../include/pieces.h"

/*Macros*/
#include <iostream>

using namespace std;

Move::Move() //we never actually found a need for this so we left it blank
{
}

Move::Move(Piece pieceIn, int sRow, int sCol, int eRow, int eCol)
{
	piece = pieceIn;
	startRow = sRow;
	startCol = sCol;
	endRow = eRow;
	endCol = eCol;
	value = 0; //creates a move with the default value of zero that the AI later fills in
}

void Move::Display() //basic display function
{
	cout << "starting row and column: " << startRow << "x" << startCol << endl;
	cout << "ending row and column: " << endRow << "x" << endCol << endl;
	//cout << "The value of the move is: " << value << endl;
}

void Move::setMoveValue(double val) //allows us to set the move value in the AI
{
    value = val;
}

double Move::getMoveValue() //returns the value of the move
{
    return value;
}

Piece Move::getPiece() //returns the piece of the move
{
    return piece;
}
