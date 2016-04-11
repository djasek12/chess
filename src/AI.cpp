/*Header files from include*/ 
#include "../include/AI.h"
#include "../include/Move.h"

/*Macros*/
#include <iostream>
#include "stdlib.h"

using namespace std;

// constructor that takes in a board
AI::AI(Board B/*, Manager gmMnger*/)
{
    boardOriginal = B.chessBoard;
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
        cout << "king in check" << endl;
        return getOutOfCheck();
    }
    else
    {
        //cout << "play move" << endl;
        return playMove();
    }

    /*if(!makeObviousMove())
      {
      int movesAhead = 1;
      decideMove(movesAhead);
      }*/
}

Move AI::getOutOfCheck()
{  
    vector<Move> escapeMoves;

    for(int i=0; i<moves.size(); i++)
    {
        Manager mnger;
        mnger.setBoard(Brd);

        mnger.move(moves[i].startRow, moves[i].startCol, moves[i].endRow, moves[i].endCol); 
        if(mnger.kingInCheck() != 2)
        {
            escapeMoves.push_back(moves[i]);
        }
    }

    for(int i=0; i<escapeMoves.size(); i++)
    {
        escapeMoves[i].setMoveValue(getCaptureValue(moves[i]) + 0.05*findMoveableSpaces(escapeMoves[i]) + 0.2*getAttackingValue(escapeMoves[i]) - 3*numAttackers(escapeMoves[i]) + 0.2*getDefendingValue(escapeMoves[i]));
        cout << "\nstarting row/col: " << escapeMoves[i].startRow << " " << escapeMoves[i].startCol << " ending row/col: " << escapeMoves[i].endRow << " " << escapeMoves[i].endCol << endl;
        cout << "capture value of move: " << getCaptureValue(escapeMoves[i]) << endl;
        cout << "moveable spaces: " << 0.05*findMoveableSpaces(escapeMoves[i]) << endl;
        cout << "attack value: " << 0.2*getAttackingValue(escapeMoves[i]) << endl;
        cout << "numAttackers: " << numAttackers(escapeMoves[i]) << endl;
        cout << "defending value: " << 0.2*getDefendingValue(escapeMoves[i]) << endl;

        cout << "overall value: " << moves[i].getMoveValue() << endl << endl;
    }

    Move bestMove = escapeMoves[0];
    for(int i=1; i<escapeMoves.size(); i++)
    {
        if(bestMove.getMoveValue() < escapeMoves[i].getMoveValue())
            bestMove = escapeMoves[i];
    }

    return bestMove;
}

int AI::makeObviousMove() // returns 1 if move is made
{
  
   int AIQueenRow, AIQueenCol, PlayerQueenRow, PlayerQueenCol; // track position of both queens
   
   // find queen and store the space where it is
   for(int col=0; col<8; col++)
   {
      for(int row=0; row<8; row++)
      {
         Piece P = boardOriginal[col][row];

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

         Piece P = boardOriginal[c][r];
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

void AI::findMoves(int player)
{
    // loop through each space in board vector
    for(int row=0; row<8; row++)
    {
        for(int col=0; col<8; col++)
        {

            if(boardOriginal[col][row].getChar() != 32) // piece isn't null 
            {
                if(boardOriginal[col][row].getPlayer() == player) // is on correct team
                {
                    for(int r=0; r<8; r++) // loop through all of spaces on board again to check for valid moves
                    {
                        for(int c=0; c<8; c++)
                        {
                            Manager mnger;
                            mnger.setBoard(Brd); // need to pass AI board to Manager
                            if(mnger.checkMove(row, col, r, c, player) == 0)
                            {
                                Move testMove(boardOriginal[col][row], row, col, r, c);
                                if(player == 0)
                                    moves.push_back(testMove);
                                else
                                    humanMoves.push_back(testMove); 
                            }
                        }
                    }
                }
            }
        }
    }
}

void AI::dispValidMoves()
{
    cout << "number of moves: " << moves.size() << endl;
    /*for(int i=0; i<moves.size(); i++)
    {
        moves[i].Display();
        cout << "capture value: " << getCaptureValue(moves[i]) << endl;
        cout << "moveable spaces: " << findMoveableSpaces(moves[i]) << endl;

    }*/


}

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
double AI::getCaptureValue(Move move)
{
    Piece capturedPiece = boardOriginal[move.endCol][move.endRow];
    if(capturedPiece.getChar() != 32) // not null
    {
        return capturedPiece.getValue();
    }
    else
        return 0; 
}

int AI::getDevelopmentValue(Move move)
{
    int develop = 0;

    Manager mnger;  // would like to be able to get rid of this
    mnger.setBoard(Brd);

    if(move.startCol < 3 & move.endCol >= 3)
        develop = 1;

    return develop;
}


double AI::getDefendingValue(Move move)
{
    double youDefend = 0; // sum of values of pieces you are defending
    double defendYou = 0; // sum of values of pieces defending you

    // each of these have their own weights and then are summed together

    Manager mnger;  // would like to be able to get rid of this
    mnger.setBoard(Brd);
    mnger.move(move.startRow, move.startCol, move.endRow, move.endCol); // need to execute move on board so manager can parse it

    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 8; c++)
        {
            if(mnger.board.chessBoard[c][r].getPlayer() == 0 & mnger.board.chessBoard[c][r].getValue() != 1000)
            {
                if(r != move.endRow | c != move.endCol)
                {
                    if(mnger.checkMove2(move.endRow, move.endCol, r, c, 0) == 2)
                    {
                        youDefend += mnger.board.chessBoard[c][r].getValue(); 
                    }
                }
            }
        }
    }

    //cout << "you defend: " << youDefend <<endl;

    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 8; c++)
        {
            if(mnger.board.chessBoard[c][r].getPlayer() == 0)
            {
                if(r != move.endRow | c != move.endCol)
                {
                    if(mnger.checkMove2(r, c, move.endRow, move.endCol, 0) == 2)
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

int AI::findMoveableSpaces(Move move)
{
    int moveableSpaces = 0;
    Manager mnger;  // would like to be able to get rid of this
    mnger.setBoard(Brd);

    mnger.move(move.startRow, move.startCol, move.endRow, move.endCol); // need to execute move on board so manager can parse it


    for(int row=0; row<8; row++)
    {
        for(int col=0; col<8; col++)
        {

            if(mnger.board.chessBoard[col][row].getPlayer() == 0)
            {
                for(int r=0; r<8; r++)
                {
                    for(int c=0; c<8; c++)
                    {
                        if(mnger.checkMove(row, col, r, c, 0) == 0)
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

double AI::getAttackingValue(Move move)
{
    int attackValue = 0;
    Manager mnger;  // would like to be able to get rid of this
    mnger.setBoard(Brd);
    mnger.move(move.startRow, move.startCol, move.endRow, move.endCol); // need to execute move on board so manager can parse it

    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 8; c++)
        {
            if(move.startRow != r | move.startCol != c) // can't go back and capture itself
            {
                if(mnger.checkMove(move.endRow, move.endCol, r, c, 0) == 0)
                {
                    int value = mnger.board.chessBoard[c][r].getValue();
                    if(value > 0 & value != 1000)
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

double AI::numAttackers(Move move)
{
    double numAttackers = 0;
    Manager mnger;  // would like to be able to get rid of this
    mnger.setBoard(Brd);
    mnger.move(move.startRow, move.startCol, move.endRow, move.endCol); // need to execute move on board so manager can parse it
   
    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 8; c++)
        {
            if(mnger.board.chessBoard[c][r].getPlayer() == 1)
            {
                if(mnger.checkMove(r, c, move.endRow, move.endCol, 1) == 0)
                {
                    numAttackers++;
                }
            }
        }
    }
    return numAttackers * double(move.getPiece().getValue())/2;
}

double AI::pieceValueAbandoned(Move move)
{
}

int AI::randomMove()
{
    srand(time(NULL));
    int moveIndex = rand()%moves.size();
    //cout << "moveIndex: " << moveIndex << endl;
    return moveIndex;
}

Move AI::playMove()
{
    //cout << "Inside playMove()" << endl;
    //findMoves();
    //cout << "Calling dispValidMoves()" << endl;
    //dispValidMoves();
    //cout << "calling randomMove()" << endl;
    //return moves[randomMove()];
    findGains(0);
    //cout << "found moves of 0" << endl;
    findGains(1);
    //cout << "found moves of 1" << endl;

    Move bestMove = moves[0];
    for(int i=1; i<moves.size(); i++)
    {
            cout << "\nstarting row/col: " << moves[i].startRow << " " << moves[i].startCol << " ending row/col: " << moves[i].endRow << " " << moves[i].endCol << endl;
            cout << "capture value of move: " << getCaptureValue(moves[i]) << endl;
            cout << "moveable spaces: " << 0.05*findMoveableSpaces(moves[i]) << endl;
            cout << "attack value: " << 0.2*getAttackingValue(moves[i]) << endl;
            cout << "numAttackers: " << numAttackers(moves[i]) << endl;
            cout << "defending value: " << 0.2*getDefendingValue(moves[i]) << endl;
            cout << "development value: " << getDevelopmentValue(moves[i]) << endl;

            cout << "overall value: " << moves[i].getMoveValue() << endl << endl;


        if(bestMove.getMoveValue() < moves[i].getMoveValue())
            bestMove = moves[i];
    }
    //cout << "about to exit function, bestMove value is " << bestMove.getMoveValue() << endl;
    return bestMove;
}

double AI::findGains(int player)
{
    if(player == 0)
    {
        findMoves(0);

        for(int i=0; i<moves.size(); i++)
        {
            moves[i].setMoveValue(getCaptureValue(moves[i]) + 0.2*findMoveableSpaces(moves[i]) + 0.2*getAttackingValue(moves[i]) - 5*numAttackers(moves[i]) + 0.1*getDefendingValue(moves[i]) + 1*getDevelopmentValue(moves[i]));

        }   

    }

    else
    {
        for(int i=0; i<moves.size(); i++)
        {
            Manager mnger;
            mnger.setBoard(Brd);
            mnger.move(moves[i].startRow, moves[i].startCol, moves[i].endRow, moves[i].endCol);
            
            findMoves(1);

            for(int j=0; j<humanMoves.size(); j++)
            {
                humanMoves[j].setMoveValue(getCaptureValue(humanMoves[j]) + 0.2*findMoveableSpaces(humanMoves[j]) + 0.2*getAttackingValue(humanMoves[j]) - 5*numAttackers(humanMoves[j]) + 0.1*getDefendingValue(humanMoves[j]) + 1*getDevelopmentValue(humanMoves[j]));

            }   


            Move maxValue = humanMoves[0];

            for(int j=1; j<humanMoves.size(); j++)
            {
                if(humanMoves[j].getMoveValue() > maxValue.getMoveValue())
                    maxValue = humanMoves[j];
            }

            cout << "max human move value: " << maxValue.getMoveValue() << endl;
            cout << "start: " << maxValue.startRow << maxValue.startCol << endl;
            cout << "end: " << maxValue.endRow << maxValue.endCol << endl;
            moves[i].setMoveValue(moves[i].getMoveValue() - maxValue.getMoveValue());
        }
    }

}
