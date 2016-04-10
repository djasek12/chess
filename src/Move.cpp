/*Includes*/
#include "../include/Move.h"
#include "../include/pieces.h"

/*Macros*/
#include <iostream>

using namespace std;

Move::Move()
{
}

Move::Move(Piece pieceIn, int sRow, int sCol, int eRow, int eCol)
{
	piece = pieceIn;
	startRow = sRow;
	startCol = sCol;
	endRow = eRow;
	endCol = eCol;
	value = 0;
}

void Move::Display()
{
	cout << "starting row and column: " << startRow << "x" << startCol << endl;
	cout << "ending row and column: " << endRow << "x" << endCol << endl;
	//cout << "The value of the move is: " << value << endl;
}

void Move::setMoveValue(double val)
{
    value = val;
}

double Move::getMoveValue()
{
    return value;
}

Piece Move::getPiece()
{
    return piece;
}
