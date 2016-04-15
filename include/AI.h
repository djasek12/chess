// Header file for AI class - Danny Jasek and Billy Theisen

#ifndef _AI_H_INCLUDED
#define _AI_H_INCLUDED

#include <vector>
#include "board.h"
#include "manager.h"

using namespace std;

class AI
{

    //friend class Manager;

    public:
        AI(Board b /*,Manager m*/); // constructor

        Move overallAlgorithm(); // skeleton
        void findMoves(int player); // find valid moves
        void dispMoveValues(vector<Move>, int player);
        Move getOutOfCheck();
        int makeObviousMove();
        void assignMoveValues();
        int decideMove(int movesAhead);
        Move playMove(int movesAhead);
        void findNextPiece();
        int currentRow; // row of current piece
        int currentCol; // column of current piece
        int randomMove(); // really simple AI
        void recursiveAlgorithm(int turnsAhead, int i, vector<Move>);
        Move recursiveCaller();

    private:
        vector<Move> moves;
        vector<vector<Piece> > boardOriginal; 
        vector<vector<Piece> > boardCopy; 
        vector<Move> humanMoves;
        vector<Move> firstLevelMoves; // for recursive function
        //Manager mnger;

        double findGains();
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
};

#endif
