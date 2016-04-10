
/*Header files from include*/ 
#include "../include/AI.h"
#include "../include/Move.h"

/*Macros*/
#include <iostream>
#include "stdlib.h"

using namespace std;

AI::AI(Board B/*, Manager gmMnger*/)
{
   boardOriginal = B.chessBoard;
   Brd = B;
   //gameManager = gmMnger;
   //cout << "board that AI sees" << endl;
   //B.display(); 
}

/*void AI::overallAlgorithm()
{
   //if(kingInCheck)
   //{
      getOutOfCheck();
   //}
   
   if(!makeObviousMove())
   {
      int movesAhead = 1;
      decideMove(movesAhead);
   }
}*/

void AI::getOutOfCheck()
{  
   //if(kingInCheck())
   {

      for(int col=0; col<8; col++)
      {
         for(int row=0; row<8; row++)
         {
            //if(isValidMove(bKing, row, col)
            {
               //move king
            }
         }
      }

   }


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

void AI::findMoves()
{
    //Manager mnger;

    // loop through each space in board vector
    for(int row=0; row<8; row++)
    {
        for(int col=0; col<8; col++)
        {

            if(boardOriginal[col][row].getChar() != 32) // piece isn't null 
            {
                if(boardOriginal[col][row].getPlayer() == 0) // is our piece
                {
                    //cout << "row: " << row << " col: " << col << endl;
                    //cout << "piece character: " << boardOriginal[col][row].getChar() << endl;
                    //cout << "player: " << boardOriginal[col][row].getPlayer() << endl;

                    for(int r=0; r<8; r++) // loop through all of spaces on board again to check for valid moves
                    {
                        for(int c=0; c<8; c++)
                        {
                            Manager mnger;
                            mnger.setBoard(Brd); // need to pass AI board to Manager
                            if(row >= 2 && r == row + 1)
                            {
                                //cout << "row " << r << "col: " << c << endl;
                                //cout << "----------checkMove for piece that has been moved: " << mnger.checkMove(row, col, r, c, 0) << endl;
                            }
                            if(mnger.checkMove(row, col, r, c, 0) == 0)
                            {
                                //cout << "\nstarting row/col: " << row << " " << col << " ending row/col: " << r << " " << c << endl;
                                Move testMove(boardOriginal[col][row], row, col, r, c);
                                //cout << "capture value of move: " << getCaptureValue(testMove) << endl;
                                //cout << "moveable spaces: " << findMoveableSpaces(testMove) << endl;
                                //cout << "attack value: " << getAttackingValue(testMove) << endl;
                                moves.push_back(testMove); 
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
                    if(mnger.checkMove(move.endRow, move.endCol, r, c, 0) == 2)
                    {
                        youDefend += mnger.board.chessBoard[c][r].getValue(); 
                    }
                }
            }
        }
    }

    cout << "you defend: " << youDefend <<endl;

    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 8; c++)
        {
            if(mnger.board.chessBoard[c][r].getPlayer() == 0)
            {
                if(r != move.endRow | c != move.endCol)
                {
                    if(mnger.checkMove(r, c, move.endRow, move.endCol, 0) == 2)
                    {
                        defendYou++;
                    }
                }
            }
        }
    }

    cout << "defend you: " << defendYou << endl;

    return youDefend + defendYou; 
}

int AI::findMoveableSpaces(Move move)
{
    int moveableSpaces = 0;
    Manager mnger;  // would like to be able to get rid of this
    mnger.setBoard(Brd);
    mnger.move(move.startRow, move.startCol, move.endRow, move.endCol); // need to execute move on board so manager can parse it

    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 8; c++)
        {
            if(mnger.checkMove(move.endRow, move.endCol, r, c, 0) == 0)
            {
                moveableSpaces++;
            }
        }
    }

    return moveableSpaces;
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
                    if(value > 0)
                    {
                        cout << "Possible attacking move: row, column, value: "  << r << c << value << endl;
                    }
                    //if(Brd[c][r].getValue() > 0)
                    attackValue += value;
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
    Move bestMove = moves[0];
    for(int i=1; i<moves.size(); i++)
    {
        if(bestMove.getMoveValue() < moves[i].getMoveValue())
            bestMove = moves[i];
    }
    return bestMove;
}

double AI::findGains(int player)
{
    findMoves();

    for(int i=0; i<moves.size(); i++)
    {
        moves[i].setMoveValue(getCaptureValue(moves[i]) + 0.05*findMoveableSpaces(moves[i]) + 0.2*getAttackingValue(moves[i]) - 3*numAttackers(moves[i]) + 0.2*getDefendingValue(moves[i]));
        cout << "\nstarting row/col: " << moves[i].startRow << " " << moves[i].startCol << " ending row/col: " << moves[i].endRow << " " << moves[i].endCol << endl;
        cout << "capture value of move: " << getCaptureValue(moves[i]) << endl;
        cout << "moveable spaces: " << 0.05*findMoveableSpaces(moves[i]) << endl;
        cout << "attack value: " << 0.2*getAttackingValue(moves[i]) << endl;
        cout << "numAttackers: " << numAttackers(moves[i]) << endl;
        cout << "defending value: " << 0.2*getDefendingValue(moves[i]) << endl;

        
        cout << "overall value: " << moves[i].getMoveValue() << endl << endl;

    }   
}
