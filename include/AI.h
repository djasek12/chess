// Daniel Jasek and Billy Theisen
// CSE20212 Final Project
// Header file for AI class

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
        AI(Board b, int turnFuture, int primaryPlayer, int look, int turn); // AI constructor

        Move overallAlgorithm(int player, int turnsAhead); // parent function
        void findMoves(int player); // find valid moves for AI
        void dispValidMoves();
        Move playMove(int turnsAhead); // returns best AI move
        int randomMove(); // really simple AI - returns random integer index in moves vector

    private:
        vector<Move> moves; // possible AI moves
        vector<Move> humanMoves; // possible human moves in response to move
        //Manager mnger;
        
        Move getOutOfCheck(int player); // gets AI out of check
        void dispMoveValue(Move mv, int player); // displays value of a move

        double findGains(); // calculates value of a move - 0 is AI, 1 is player

        // findGains functions
        double getCaptureValue(Move move, int player);
        double getAttackingValue(Move move, int player); // sum of values of pieces you can attack
        double getDefendingValue(Move move, int player); // sum of values of pieces you can defend
        int findMoveableSpaces(Move move, int player); // sum of spaces you can move
        int getDevelopmentValue(Move move, int player); //rewards for developing pieces, specifically pawns
        int getPressureValue(Move move, int player); //rewards for removing possible moves away from the king
        double numAttackers(Move move, int player); // pieces that can attack you
        double pieceValueAbandoned(Move move); // value of pieces you are no longer defending

        void updateKingValue(int player); // increases kings value throughout the game

        //board data members for passing AI board to Manager class
        Board Brd;
        Board temp;

        // constants that weight the various findGains functions - can be different for AI and human moves
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

        int turnsAhead; // turns ahead the AI is loking
        int primaryPlayer; // player AI is playing as - usually player 0 (red)
        int otherPlayer;
        int lookAhead; // max turnsAhead
        int turn;

        Move maxValueMove;
};

#endif
