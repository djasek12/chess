#ifndef _AI_H_INCLUDED
#define _AI_H_INCLUDED

#include <vector>
#include "board.h"
#include "manager.h"
using namespace std;

class AI {

    friend class Manager;

    public:
        AI(Board b, int turnFuture, int primaryPlayer, int look, int turn);
        Move overallAlgorithm(int player); // skeleton
        void findMoves(int player); // find valid moves
        void dispValidMoves();
        Move getOutOfCheck(int player);
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
        int getDevelopmentValue(Move move, int player); //rewards for developing pieces, specifically pawns
        int getPressureValue(Move move, int player); //rewards for removing possible moves away from the king

        // findLosses functions
        double numAttackers(Move move, int player); // pieces that can attack you
        double pieceValueAbandoned(Move move); // value of pieces you are no longer defending

        void updateKingValue(int player);

        //board data member for passing AI board to Manager class
        Board Brd;
        Board temp;
        
        double CAPTUREVALUE_0;
        double ATTACKINGVALUE_0;
        double DEFENDINGVALUE_0;
        double MOVEABLEVALUE_0;
        double DEVELOPMENTVALUE_0;
        double PRESSUREVALUE_0;
        
        double ATTACKERSVALUE_0;
        double ABANDONVALUE_0; 
        
        double CAPTUREVALUE_1;
        double ATTACKINGVALUE_1;
        double DEFENDINGVALUE_1;
        double MOVEABLEVALUE_1;
        double DEVELOPMENTVALUE_1;
        double PRESSUREVALUE_1;
        
        double ATTACKERSVALUE_1;
        double ABANDONVALUE_1; 
        
        int turnsAhead;
        int primaryPlayer;
        int lookAhead;
        int turn;
};

#endif
