//so the point of a move class was to allow us to easily pass around moves, which made everything a lot easier
#ifndef Move_H
#define Move_H

#include <iostream>
#include "pieces.h"

class Move
{
	public:
		Move(); //This just creates a default move with dummy values
	
		Move(Piece piece, int startRow, int startCol, int endRow, int endCol); //allows us to specify all of the data memebers of a move
        void Display(); //prints out the move
        void setMoveValue(double val); //sets the value of the move
        double getMoveValue(); //returns the value of the move as determined by the AI algorithm
        Piece getPiece(); //returns the piece associated with the move

	    int startRow; //these data memebers are pretty self explanatory, everything that a move consists of we store, they're all public so the AI and manager can access them
		int startCol;
		int endRow;
		int endCol;
		double value;	
		Piece piece;
	
	private: 
	
};

#endif
