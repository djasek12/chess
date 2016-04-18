#ifndef _AI_H_INCLUDED
#define _AI_H_INCLUDED

#include <vector>
#include "board.h"
#include "manager.h"
using namespace std;

class AI {

    friend class Manager;

    public:
        AI(Board b, int turn, int primaryPlayer);
        Move overallAlgorithm(); // skeleton
        void findMoves(int player); // find valid moves
        void dispValidMoves();
        Move getOutOfCheck();
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
        vector<Move> humanMoves;
        //Manager mnger;

        double findGains(int player); // 0 is AI, 1 is player
        double findLosses(int player);

        // findGains functions
        double getCaptureValue(Move move, int player);
        double getAttackingValue(Move move, int player); // sum of values of pieces you can attack
        double getDefendingValue(Move move, int player); // sum of values of pieces you can defend
        int findMoveableSpaces(Move move, int player); // sum of spaces you can move
        int getDevelopmentValue(Move move, int player);

        // findLosses functions
        double numAttackers(Move move, int player); // pieces that can attack you
        double pieceValueAbandoned(Move move); // value of pieces you are no longer defending

        //board data member for passing AI board to Manager class
        Board Brd;
        Board temp;
        
        double CAPTUREVALUE;
        double ATTACKINGVALUE;
        double DEFENDINGVALUE;
        double MOVEABLEVALUE;
        double DEVELOPMENTVALUE;
        
        double ATTACKERSVALUE;
        double ABANDONVALUE; 
        
        int turnsAhead;
        int primaryPlayer;
};

#endif
