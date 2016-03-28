#include <iostream>
#include "Move.h"
#include "pieces.h"
using namespace std;

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
	cout << "The starting row and column are: " << startRow << "x" << startCol << endl;
	cout << "The ending row and column are: " << endRow << "x" << endCol << endl;
	cout << "The value of the move is: " << value << endl;
}

void Move::setMoveValue(double val)
{
    value = val;
}
