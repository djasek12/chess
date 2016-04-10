#ifndef Move_H
#define Move_H

#include <iostream>
#include "pieces.h"

class Move
{
	public:
		Move();
	
		Move(Piece piece, int startRow, int startCol, int endRow, int endCol);
                void Display();
                void setMoveValue(double val);
                double getMoveValue();
                Piece getPiece();

	        int startRow;
		int startCol;
		int endRow;
		int endCol;
		double value;	
	
	private: 
		Piece piece;
	
};

#endif
