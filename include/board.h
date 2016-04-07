#ifndef _BOARD_H_INCLUDED_
#define _BOARD_H_INCLUDED_

//macros
#include <iostream> //needed for cout, cin, endl
#include <vector> //needed for stl::vector
#include <string>
#include <fstream>
//headers
#include "pieces.h"
#include "game.h"
#include "Move.h"
//#include "AI.h"

using namespace std;

class Board{

        //friend class AI;
	public:
		Board(); //default constructor for board
		void initPieces();
		void display();
		void writeToFile();
		vector< vector < Piece> > nullBoard;	
		vector< vector < Piece> > chessBoard;
	
	private:
		int dim;
};

#endif

