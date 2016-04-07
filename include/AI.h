#ifndef _AI_H_INCLUDED
#define _AI_H_INCLUDED

#include <vector>
#include "board.h"
#include "manager.h"
using namespace std;

class AI {

    friend class Manager;

    public:
        AI(Board b /*,Manager m*/);
        void overallAlgorithm(); // skeleton
        void findMoves(); // find valid moves
        void dispValidMoves();
        void getOutOfCheck();
        int makeObviousMove();
        void assignMoveValues();
        int decideMove(int movesAhead);
        Move playMove();
        void findNextPiece();
        int currentRow; // row of current piece
        int currentCol; // column of current piece

        int randomMove(); // really simple AI

    private:
        vector<Move> moves;
        vector<vector<Piece> > boardOriginal; 
        vector<vector<Piece> > boardCopy;  
        //Manager mnger;

        double findGains(int player); // 0 is AI, 1 is player
        double findLosses(int player);

        // findGains functions
        double getCaptureValue(Move move);
        double getAttackingValue(Move move); // sum of values of pieces you can attack
        double getDefendingValue(Move move);
        int findMoveableSpaces(Move move); // sum of spaces you can move

        // findLosses functions
        int numAttackers(); // pieces that can attack you
        double pieceValueAbandoned(); // value of pieces you are no longer defending
};

#endif
