// AI algorithms - Danny Jasek and Billy Theisen

// Header files from include
#include "../include/AI.h"
#include "../include/Move.h"

// Macros
#include <iostream>
#include "stdlib.h"

// Move Value constants
#define CAPTURE_VALUE 2.0
#define MOVEABLE_SPACES 0.1
#define ATTACKING_VALUE 0.4
#define NUM_ATTACKERS 1.0
#define DEFENDING_VALUE 0.1
#define DEVELOPMENT_VALUE 1.5

using namespace std;

// Helpful notes - AI is player 0, access chessboard[col][row]

// constructor that takes in a board
AI::AI(Board B/*, Manager gmMnger*/)
{
    Brd = B;
    //gameManager = gmMnger;
}

Move AI::overallAlgorithm()
{
    // instantiate a manager and pass it the correct board
    Manager mnger;
    mnger.setBoard(Brd);

    if(mnger.kingInCheck() == 2)
    {
        cout << "KING IN CHECK" << endl;
        return getOutOfCheck();
    }
    else
    {
        int movesAhead = 1;
        //cout << "play move" << endl;
        return playMove(movesAhead);
    }

    /*if(!makeObviousMove())
      {
      int movesAhead = 1;
      decideMove(movesAhead);
      }*/
}

// what to do if AI is in check
Move AI::getOutOfCheck()
{  
    vector<Move> escapeMoves; // possible escape moves

    for(int i=0; i<moves.size(); i++)
    {
        Manager mnger;
        mnger.setBoard(Brd);

        mnger.move(moves[i].startRow, moves[i].startCol, moves[i].endRow, moves[i].endCol); // try each possible move
        if(mnger.kingInCheck() != 2) // if king is no longer in check, add this move to move possibilities
        {
            escapeMoves.push_back(moves[i]);
        }
    }

    // assign values to these valid moves
    for(int i=0; i<escapeMoves.size(); i++)
    {
        escapeMoves[i].setMoveValue(
            CAPTURE_VALUE * getCaptureValue(moves[i], 0) + 
            MOVEABLE_SPACES * findMoveableSpaces(escapeMoves[i], 0) + 
            ATTACKING_VALUE * getAttackingValue(escapeMoves[i], 0) - 
            NUM_ATTACKERS * numAttackers(escapeMoves[i], 0) + 
            DEFENDING_VALUE * getDefendingValue(escapeMoves[i], 0) + 
            DEVELOPMENT_VALUE * getDevelopmentValue(escapeMoves[i], 0)
        );
    }

    // find best move
    // add recursion to this?
    Move bestMove = escapeMoves[0];
    for(int i=1; i<escapeMoves.size(); i++)
    {
        if(bestMove.getMoveValue() < escapeMoves[i].getMoveValue())
            bestMove = escapeMoves[i];
    }

    return bestMove;
}

// makes most obvious move - is this function necessary?
int AI::makeObviousMove() // returns 1 if move is made
{
  
   int AIQueenRow, AIQueenCol, PlayerQueenRow, PlayerQueenCol; // track position of both queens
   
   // find queen and store the space where it is
   for(int col=0; col<8; col++)
   {
      for(int row=0; row<8; row++)
      {
         Piece P = Brd.chessBoard[col][row];

         if(P.getChar() == 'q')
         {
            if(P.getPlayer() == 0) // this is the AI queen
            {
               AIQueenRow = row;
               AIQueenCol = col;
               cout << "Found AI queen in row " << AIQueenRow+1 << " and column " << AIQueenCol+1 << endl;
            }
            else if(P.getPlayer() == 1) // this is the player Queen
            {
               PlayerQueenRow = row;
               PlayerQueenCol = col;
               cout << "Found Player queen in row " << PlayerQueenRow+1 << " and column " << PlayerQueenCol+1 << endl;
            }
         }

      }
   }

   // check if our queen is threatened or can capture the opposing queen
   for(int c=0; c<8; c++)
   {
      for(int r=0; r<8; r++)
      {

         Piece P = Brd.chessBoard[c][r];
         if(P.getPlayer() == 1)
         {
            //if(isValidMove(P, AIQueenRow, AIQueenCol)) // queen is threatened
            {
               //move queen
               return 1; 
            }
         }
         if(P.getPlayer() == 0)
         {
            //if(isValidMove(P, PlayerQueenRow, PlayerQueenCol)) // can take opposing queen
            {
               //capture queen
               return 1;
            }
         }

      }
   }

   return 0;
}

// finds valid moves for a given player
void AI::findMoves(int player)
{
    // loop through each space in board vector
    for(int row=0; row<8; row++)
    {
        for(int col=0; col<8; col++)
        {

            if (player == 0) // AI
            {
                if(Brd.chessBoard[col][row].getChar() != 32) // piece isn't null 
                {
                    if(Brd.chessBoard[col][row].getPlayer() == player) // is on correct team
                    {

                        for(int r=0; r<8; r++) // loop through all of spaces on board again to check for valid moves
                        {
                            for(int c=0; c<8; c++)
                            {
                                Manager mnger;
                                mnger.setBoard(Brd); // need to pass AI board to Manager
                                if(mnger.checkMove(row, col, r, c, player) == 0)
                                {
                                    Move testMove(Brd.chessBoard[col][row], row, col, r, c);
                                    moves.push_back(testMove); // add new moves to vector
                                }
                            }
                        }
                    }
                }
            }

            else // human player
            {
                if(temp.chessBoard[col][row].getChar() != 32) // uses temporary board for human
                {
                    if (temp.chessBoard[col][row].getPlayer() == player)
                    {

                        for (int r = 0; r < 8; r++)
                        {
                            for (int c = 0; c < 8; c++)
                            {
                                Manager mnger;
                                mnger.setBoard(temp);
                                if (mnger.checkMove(row, col, r, c, player) == 0)
                                {
                                    Move testMove(temp.chessBoard[col][row], row, col, r, c);
                                    humanMoves.push_back(testMove);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// useful for debugging
void AI::dispMoveValues(vector<Move> moves, int player)
{
    cout << "number of moves: " << moves.size() << endl;
    for(int i=0; i<moves.size(); i++)
    { 

        cout << "\nstarting row/col: " << moves[i].startRow << " " << moves[i].startCol << " ending row/col: " << moves[i].endRow << " " << moves[i].endCol << endl;
        cout << "capture value of move: " << CAPTURE_VALUE * getCaptureValue(moves[i], player) << endl;
        cout << "moveable spaces: " << MOVEABLE_SPACES * findMoveableSpaces(moves[i], player) << endl;
        cout << "attack value: " << ATTACKING_VALUE * getAttackingValue(moves[i], player) << endl;
        cout << "numAttackers: " << NUM_ATTACKERS * numAttackers(moves[i], player) << endl;
        cout << "defending value: " << DEFENDING_VALUE * getDefendingValue(moves[i], player) << endl;
        cout << "development value: " << DEVELOPMENT_VALUE * getDevelopmentValue(moves[i], player) << endl;

        cout << "overall value: " << moves[i].getMoveValue() << endl << endl;

    }
}

// might still use this - using findGains for now
void AI::assignMoveValues()
{
    //if(movesAhead > 4)
    //return 0; 
    //
    double moveValue;
    int turnsAhead = 1; // hardcoded for now

    for(int i=0; i<moves.size(); i++)
    {
        
        //moveValue = (1/turnsAhead) * (findGains(0) - findLosses(0)); //+ (findGains(1) - findLosses(1)) 
        //moves[i].setMoveValue(moveValue);
    }

    //cout << "moves ahead: " << movesAhead << endl;

    //makeMove(movesAhead+1);
}

//look at move destination on board and find value of piece there
double AI::getCaptureValue(Move move, int player)
{
    Piece capturedPiece;

    if (player == 0)
        capturedPiece = Brd.chessBoard[move.endCol][move.endRow];
    else
        capturedPiece = temp.chessBoard[move.endCol][move.endRow];

    if(capturedPiece.getChar() != 32) // not null
        return capturedPiece.getValue();
    else
        return 0; 
}

// returns a 1 if move gets a piece from its starting position
int AI::getDevelopmentValue(Move move, int player) //needs to be fixed for human
{
    int develop = 0;

    Manager mnger;  
    if (player == 0)
        mnger.setBoard(Brd);
    else
        mnger.setBoard(temp);

    if (player == 0) // AI
    {
        if(move.startRow < 2 & move.endRow >= 2)
            develop = 1;
    }
    else // human
    {
        if (move.startRow > 6 & move.endRow <= 6)
        {
            develop = 1;
        }
    }

    return develop;
}

// sums values of pieces you are defending and number of pieces defending you
double AI::getDefendingValue(Move move, int player) //needs to be fixed for human
{
    double youDefend = 0; // sum of values of pieces you are defending
    double defendYou = 0; // sum of values of pieces defending you

    // each of these have their own weights and then are summed together

    Manager mnger;  // would like to be able to get rid of this
    if (player == 0)
    	mnger.setBoard(Brd);
    else
    	mnger.setBoard(temp);
    mnger.move(move.startRow, move.startCol, move.endRow, move.endCol); // need to execute move on board so manager can parse it

    // sum values of pieces you are defending
    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 8; c++)
        {
            if(mnger.board.chessBoard[c][r].getPlayer() == player & mnger.board.chessBoard[c][r].getValue() != 1000) // not defending king
            {
                if(r != move.endRow | c != move.endCol) // not the current piece
                {
                    if(mnger.checkMove2(move.endRow, move.endCol, r, c, player) == 2) // move ends on a piece on your team
                    {
                        youDefend += mnger.board.chessBoard[c][r].getValue(); 
                    }
                }
            }
        }
    }

    //cout << "you defend: " << youDefend <<endl;

    // sum number of pieces defending you
    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 8; c++)
        {
            if(mnger.board.chessBoard[c][r].getPlayer() == player)
            {
                if(r != move.endRow | c != move.endCol)
                {
                    if(mnger.checkMove2(r, c, move.endRow, move.endCol, player) == 2)
                    {
                        defendYou++;
                    }
                }
            }
        }
    }

    //cout << "defend you: " << defendYou << endl;

    return youDefend + defendYou; 
}

// find number of moveable spaces after a move relative to what is was before
int AI::findMoveableSpaces(Move move, int player) //needs to be fixed for human
{
    int moveableSpaces = 0;

    Manager mnger;  // would like to be able to get rid of this
    if (player == 0)
    	mnger.setBoard(Brd);
    else
    	mnger.setBoard(temp);

    mnger.move(move.startRow, move.startCol, move.endRow, move.endCol); // need to execute move on board so manager can parse it

    for(int row=0; row<8; row++)
    {
        for(int col=0; col<8; col++)
        {

            if(mnger.board.chessBoard[col][row].getPlayer() == player) // find pieces of player
            {
                for(int r=0; r<8; r++)
                {
                    for(int c=0; c<8; c++)
                    {
                        if(mnger.checkMove(row, col, r, c, player) == 0) // find places they can move
                        {
                            moveableSpaces++;
                        }

                    }
                }
            }

        }
    }

    return moveableSpaces - moves.size();

}

// sum of values of pieces you can attack after a give move
double AI::getAttackingValue(Move move, int player) //needs to be fixed for human
{
    int attackValue = 0;
    Manager mnger;  // would like to be able to get rid of this
    if (player == 0)
    	mnger.setBoard(Brd);
    else
    	mnger.setBoard(temp);
    	
    mnger.move(move.startRow, move.startCol, move.endRow, move.endCol); // need to execute move on board so manager can parse it

    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 8; c++)
        {
            if(move.startRow != r | move.startCol != c) // can't go back and capture itself
            {
                if(mnger.checkMove(move.endRow, move.endCol, r, c, player) == 0)
                {
                    int value = mnger.board.chessBoard[c][r].getValue();
                    if(value > 0 & value != 1000) // this would blow things out of proportion
                    {
                        attackValue += value;
                        //cout << "Possible attacking move: row, column, value: "  << r << c << value << endl;
                    }
                }
            }
        }
    }

    return attackValue;
}

// number of pieces that can attack a given piece after a move multipied by that piece's value over 2
double AI::numAttackers(Move move, int player)
{
    double numAttackers = 0;
    Manager mnger;  // would like to be able to get rid of this
    if (player == 0)
    	mnger.setBoard(Brd);
    else
        mnger.setBoard(temp);

    mnger.move(move.startRow, move.startCol, move.endRow, move.endCol); // need to execute move on board so manager can parse it

    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 8; c++)
        {
            if (player == 0)
            {
                if(mnger.board.chessBoard[c][r].getPlayer() == player)
                {
                    if(mnger.checkMove(r, c, move.endRow, move.endCol, player) == 0)
                    {
                        numAttackers++;
                    }
                }
            }
        }
    }
    return numAttackers * double(move.getPiece().getValue())/2;
}

// develop later?
double AI::pieceValueAbandoned(Move move)
{
}

// picks a random move
int AI::randomMove()
{
    srand(time(NULL));
    int moveIndex = rand()%moves.size();
    //cout << "moveIndex: " << moveIndex << endl;
    return moveIndex;
}

// executes logic needed to weigh and execute a move - taking into account 1 AI and 1 human move
Move AI::playMove(int movesAhead)
{
    findGains(); // find both AI moves and best human moves in response - combines these into a value for each AI move

    Move bestMove = moves[0];
    for(int i=1; i<moves.size(); i++)
    {
        if(bestMove.getMoveValue() < moves[i].getMoveValue())
            bestMove = moves[i];
    }

    return bestMove;
}

// should be called find value - finds values of possible moves for a player
double AI::findGains()
{
    findMoves(0); // find moves for AI

    for(int i=0; i<moves.size(); i++) // assign values for AI
    {
        moves[i].setMoveValue(
                CAPTURE_VALUE * getCaptureValue(moves[i], 0) + 
                MOVEABLE_SPACES * findMoveableSpaces(moves[i], 0) + 
                ATTACKING_VALUE * getAttackingValue(moves[i], 0) - 
                NUM_ATTACKERS * numAttackers(moves[i], 0) + 
                DEFENDING_VALUE * getDefendingValue(moves[i], 0) + 
                DEVELOPMENT_VALUE * getDevelopmentValue(moves[i], 0));
    }   

    for(int i=0; i<moves.size(); i++) // for each AI move
    {
        Manager mnger;
        mnger.setBoard(Brd);
        mnger.move(moves[i].startRow, moves[i].startCol, moves[i].endRow, moves[i].endCol);
        temp = mnger.board;

        humanMoves.clear();
        findMoves(1); // find moves for human

        for(int j=0; j<humanMoves.size(); j++) // assign values and assign to new vector
        {
            humanMoves[j].setMoveValue(
                    CAPTURE_VALUE * getCaptureValue(humanMoves[j], 1) + 
                    MOVEABLE_SPACES * findMoveableSpaces(humanMoves[j], 1) + 
                    ATTACKING_VALUE * getAttackingValue(humanMoves[j], 1) - 
                    NUM_ATTACKERS * numAttackers(humanMoves[j], 1) + 
                    DEFENDING_VALUE * getDefendingValue(humanMoves[j], 1) + 
                    DEVELOPMENT_VALUE * getDevelopmentValue(humanMoves[j], 1));
        }   

        // find best human move for this AI move
        Move maxValue = humanMoves[0];

        for(int j=1; j<humanMoves.size(); j++)
        {
            if(humanMoves[j].getMoveValue() > maxValue.getMoveValue())
                maxValue = humanMoves[j];
            }

            cout << "max human move value: " << maxValue.getMoveValue() << endl;
            cout << "start: " << maxValue.startRow << maxValue.startCol << endl;
            cout << "end: " << maxValue.endRow << maxValue.endCol << endl;

            moves[i].setMoveValue(moves[i].getMoveValue() - maxValue.getMoveValue()); // set overall value equal to the AI value - the best human move value
        }

}

Move AI::recursiveCaller()
{
    findGains();
    firstLevelMoves = moves;
    int turnsAhead = 1;

    //Move bestMove = moves[0];
    //for(int i=1; i<firstLevelMoves.size(); i++)
    //{
        recursiveAlgorithm(turnsAhead, 0,  firstLevelMoves);
        //if(bestMove.getMoveValue() < moves[i].getMoveValue())
            //bestMove = moves[i];
    //}

    //return bestMove;

}

void AI::recursiveAlgorithm(int turnsAhead, int index, vector<Move> moves)
{
    if(turnsAhead > 2)
        return;

    cout << "one run of recursive function" << endl;

    for(int i=0; i<moves.size(); i++)
    {
        Manager mnger;
        mnger.setBoard(Brd);
        mnger.move(moves[i].startRow, moves[i].startCol, moves[i].endRow, moves[i].endCol);
        temp = mnger.board;

    recursiveAlgorithm(++turnsAhead, 0, moves);

    }
}
