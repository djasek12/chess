#ifndef _MANAGER_H_INCLUDED_
#define _MANAGER_H_INCLUDED_

#include "board.h"
#include "AI.h"
//#include "Move.h"
//#include "game.h"

class Manager{

        friend class AI;
        
	public:
		Manager();
		void move( int, int, int, int );
        int checkMove( int, int, int, int, int);
		void play();
		void collectValues();	
        //functions for move checks
        int checkBounds(int, int, int, int);
		int checkPlayer( int, int, int, int, int);
        int checkSpecific( int, int, int, int, int);
        int checkPawn( int, int, int, int, int);
        int checkCastle( int, int, int, int, int);
        int checkBishop( int, int, int, int, int);
        int checkQueen( int, int, int, int, int);
        int checkKnight( int, int, int, int, int);
        int checkKing( int, int, int, int, int);
        int kingInCheck();
        //public data members
		Board board;
		Game game;
                //AI AI_1(Board);
	
	private:	
		int player0Val;
		int player1Val;
};

#endif
