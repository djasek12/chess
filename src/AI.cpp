/*Header files from include*/ 
#include "../include/AI.h"
#include "../include/Move.h"

/*Macros*/
#include <iostream>
#include "stdlib.h"

using namespace std;

// constructor that takes in a board
AI::AI(Board B, int turnFuture, int pmrPlyr, int look, int turns)
{
    boardOriginal = B.chessBoard;
    Brd = B;

    /*if(pmrPlyr == 0)
        updateKingValue(1);
    else
        updateKingValue(0);*/
    
    turnsAhead = turnFuture;
    lookAhead = look;
    
    turn = turns;
    
    CAPTUREVALUE_0 = 2.6;
    ATTACKINGVALUE_0 = .5;
    DEFENDINGVALUE_0 = 0.1;
    MOVEABLEVALUE_0 = 0.1;
    DEVELOPMENTVALUE_0 = 1.2;
    PRESSUREVALUE_0 = (0.07 * turn);
    
    ATTACKERSVALUE_0 = 2;
    ABANDONVALUE_0 = 0.0;
	
	////////////////////////
	
	CAPTUREVALUE_1 = 3.5;
    ATTACKINGVALUE_1 = .5;
    DEFENDINGVALUE_1 = 0.1;
    MOVEABLEVALUE_1 = 0.1;
    DEVELOPMENTVALUE_1 = 1;
    PRESSUREVALUE_1 = 0.1;
    
    ATTACKERSVALUE_1 = 1.2;
    ABANDONVALUE_1 = 0.0;

    
    primaryPlayer = pmrPlyr;
}

Move AI::overallAlgorithm(int player)
{

    cout << "player " << player << endl;
    // instantiate a manager and pass it the correct board
    Manager mnger;
    mnger.setBoard(Brd);

    if(mnger.kingInCheck(player))
    {
        cout << "king in check" << endl;
        return getOutOfCheck(player);
    }
    else
    {
        cout << "play move" << endl;
        return playMove();
    }

    /*if(!makeObviousMove())
      {
      int movesAhead = 1;
      decideMove(movesAhead);
      }*/
}

Move AI::getOutOfCheck(int player)
{  
    cout << "inside getOutofCheck" << endl;
    vector<Move> escapeMoves;
    Move dummyMove;
    cout << "player: " << player << endl;
    findMoves(player);
    cout << "moves size: " << moves.size() << endl;

    if(player == primaryPlayer)
    {

        for(int i=0; i<moves.size(); i++)
        {
            //cout << "inside for" << endl;
            Manager mnger;
            mnger.setBoard(Brd);

            //cout << "just set board" << endl;

            mnger.move(moves[i].startRow, moves[i].startCol, moves[i].endRow, moves[i].endCol); 
            //cout << "before if" << endl;
            if(!mnger.kingInCheck(player))
            {
                escapeMoves.push_back(moves[i]);
                cout << moves[i].startRow << moves[i].startCol << moves[i].endRow << moves[i].endCol << endl;
            }
            //cout << "after if" << endl;
        }
    }
    else
    {
        for(int i=0; i<humanMoves.size(); i++)
        {
            //cout << "inside for" << endl;
            Manager mnger;
            mnger.setBoard(Brd);

            //cout << "just set board" << endl;

            mnger.move(humanMoves[i].startRow, humanMoves[i].startCol, humanMoves[i].endRow, humanMoves[i].endCol); 
            //cout << "before if" << endl;
            if(!mnger.kingInCheck(player))
            {
                escapeMoves.push_back(humanMoves[i]);
                cout << humanMoves[i].startRow << humanMoves[i].startCol << humanMoves[i].endRow << humanMoves[i].endCol << endl;
            }
            //cout << "after if" << endl;
        }

    }

    cout << "escape moves: " << escapeMoves.size() << endl;

    //if(escapeMoves.size() == 0)
        //return

    for(int i=0; i<escapeMoves.size(); i++)
    {
        escapeMoves[i].setMoveValue(
        CAPTUREVALUE_0 * getCaptureValue(escapeMoves[i], player) + 
        MOVEABLEVALUE_0 * findMoveableSpaces(escapeMoves[i], player) + 
        ATTACKINGVALUE_0 *  getAttackingValue(escapeMoves[i], player) - 
        ATTACKERSVALUE_0 * numAttackers(escapeMoves[i], player) + 
        DEFENDINGVALUE_0 * getDefendingValue(escapeMoves[i], player));

        cout << "\nstarting row/col: " << escapeMoves[i].startRow << " " << escapeMoves[i].startCol << " ending row/col: " << escapeMoves[i].endRow << " " << escapeMoves[i].endCol << endl;
        cout << "capture value of move: " << getCaptureValue(escapeMoves[i], player) << endl;
        cout << "moveable spaces: " << findMoveableSpaces(escapeMoves[i], player) << endl;
        cout << "attack value: " << getAttackingValue(escapeMoves[i], player) << endl;
        cout << "numAttackers: " << numAttackers(escapeMoves[i], player) << endl;
        cout << "defending value: " << getDefendingValue(escapeMoves[i], player) << endl;

        cout << "overall value: " << escapeMoves[i].getMoveValue() << endl << endl;
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
        	if (player == primaryPlayer)
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
                                   		moves.push_back(testMove);
                            	}
                        	}
                    	}
                	}
           		}
           	}
           	else
           	{
           		if(temp.chessBoard[col][row].getChar() != 32)
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
double AI::getCaptureValue(Move move, int player)
{
	Piece capturedPiece;
	
    if(player == primaryPlayer)
    	capturedPiece = Brd.chessBoard[move.endCol][move.endRow];
    else
    	capturedPiece = temp.chessBoard[move.endCol][move.endRow];
    	
    if(capturedPiece.getChar() != 32) // not null
    {
        return capturedPiece.getValue();
    }
    else
        return 0; 
}

int AI::getDevelopmentValue(Move move, int player) //needs to be fixed for human
{
    int develop = 0;

    Manager mnger;  // would like to be able to get rid of this
    if (player == primaryPlayer)
    	mnger.setBoard(Brd);
    else
    	mnger.setBoard(temp);
	
	if (primaryPlayer == 0) //?
	{
    	if(move.startRow < 2 & move.endRow >= 2)
    		if (move.piece.getChar() == 'p')
        		develop = 1.5;
        	else
        		develop = 1;
    }
    else
    {
    	if (move.startRow > 5 & move.endRow <= 5)
    		if (move.piece.getChar() == 'P')
    			develop = 1.5;
    		else 
    			develop = 1;
    }

    return develop;
}


double AI::getDefendingValue(Move move, int player) //needs to be fixed for human
{
    double youDefend = 0; // sum of values of pieces you are defending
    double defendYou = 0; // sum of values of pieces defending you

    // each of these have their own weights and then are summed together

    Manager mnger;  // would like to be able to get rid of this
    if (player == primaryPlayer)
    	mnger.setBoard(Brd);
    else
    	mnger.setBoard(temp);
    mnger.move(move.startRow, move.startCol, move.endRow, move.endCol); // need to execute move on board so manager can parse it

    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 8; c++)
        {
            if(mnger.board.chessBoard[c][r].getPlayer() == player & mnger.board.chessBoard[c][r].getValue() != 1000)
            {
                if(r != move.endRow | c != move.endCol)
                {
                    if(mnger.checkMove2(move.endRow, move.endCol, r, c, player) == 2)
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

int AI::findMoveableSpaces(Move move, int player) //needs to be fixed for human
{
    int moveableSpaces = 0;
    Manager mnger;  // would like to be able to get rid of this
    if (player == primaryPlayer)
    	mnger.setBoard(Brd);
    else
    	mnger.setBoard(temp);

    mnger.move(move.startRow, move.startCol, move.endRow, move.endCol); // need to execute move on board so manager can parse it


    for(int row=0; row<8; row++)
    {
        for(int col=0; col<8; col++)
        {

            if(mnger.board.chessBoard[col][row].getPlayer() == player)
            {
                for(int r=0; r<8; r++)
                {
                    for(int c=0; c<8; c++)
                    {
                        if(mnger.checkMove(row, col, r, c, player) == 0)
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

double AI::getAttackingValue(Move move, int player) //needs to be fixed for human
{
    int attackValue = 0;
    Manager mnger;  // would like to be able to get rid of this
    if (player == primaryPlayer)
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
                    if(value > 0)
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

double AI::numAttackers(Move move, int player)
{
    double numAttackers = 0;
    Manager mnger;  // would like to be able to get rid of this
    if (player == primaryPlayer)
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
            	if(mnger.board.chessBoard[c][r].getPlayer() == 1)
            	{
                	if(mnger.checkMove(r, c, move.endRow, move.endCol, 1) == 0)
                	{
                    	numAttackers++;
                	}
            	}
            }
            else
            {
            	if (mnger.board.chessBoard[c][r].getPlayer() == 0)
            	{
            		if (mnger.checkMove(r, c, move.endRow, move.endCol, 0) == 0)
            		{
            			numAttackers++;
            		}
            	}
            }
        }
    }
    return numAttackers * double(move.getPiece().getValue())/2;
}

double AI::pieceValueAbandoned(Move move)
{
}

int AI::getPressureValue(Move move, int player)
{
	int kingMovesOld = 0;
	int kingMovesNew = 0;
	Manager mnger;
	
	if (player == primaryPlayer)
    	mnger.setBoard(Brd);
    else
    	mnger.setBoard(temp);
    
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((mnger.board.chessBoard[i][j].getChar() == 'K' && player == 0) || (mnger.board.chessBoard[i][j].getChar() == 'k' && player == 1))
			{
				for (int row = 0; row < 8; row++)
				{
					for (int col = 0; col < 8; col++)
					{
						if (player == 0)
							if (mnger.checkMove(i, j, row, col, 1) == 0)
							{
								kingMovesOld++;
							}
						else
							if (mnger.checkMove(i, j, row, col, 0) == 0)
							{
								kingMovesOld++;
							}
					}
				}
			}
		}
	}
	
	mnger.move(move.startRow, move.startCol, move.endRow, move.endCol);
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((mnger.board.chessBoard[i][j].getChar() == 'K' && player == 0) || (mnger.board.chessBoard[i][j].getChar() == 'k' && player == 1))
			{
				for (int row = 0; row < 8; row++)
				{
					for (int col = 0; col < 8; col++)
					{
						if (player == 0)
							if (mnger.checkMove(i, j, row, col, 1) == 0)
							{
								kingMovesNew++;
							}
						else
							if (mnger.checkMove(i, j, row, col, 0) == 0)
							{
								kingMovesNew++;
							}
					}
				}
			}
		}
	}
	
	return (kingMovesOld - kingMovesNew);
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
    if(primaryPlayer == 0)
    {
        findGains(0);
    //cout << "found moves of 0" << endl;
        findGains(1);
    }
    else
    {
        findGains(1);
        findGains(0);
    }
    //cout << "found moves of 1" << endl;

    Move bestMove = moves[0];
    for(int i=1; i<moves.size(); i++)
    {
        if(bestMove.getMoveValue() < moves[i].getMoveValue())
            bestMove = moves[i];
    }
    //cout << "about to exit function, bestMove value is " << bestMove.getMoveValue() << endl;
    //

    cout << "best AI move" << endl;
    cout << "\nstarting row/col: " << bestMove.startRow << " " << bestMove.startCol << " ending row/col: " << bestMove.endRow << " " << bestMove.endCol << endl;
    cout << "capture value of move: " << CAPTUREVALUE_0 * getCaptureValue(bestMove, primaryPlayer) << endl;
    cout << "moveable spaces: " << MOVEABLEVALUE_0 * findMoveableSpaces(bestMove, primaryPlayer) << endl;
    cout << "attack value: " << ATTACKINGVALUE_0*  getAttackingValue(bestMove, primaryPlayer) << endl;
    cout << "numAttackers: " << ATTACKERSVALUE_0 * numAttackers(bestMove, primaryPlayer) << endl;
    cout << "defending value: " << DEFENDINGVALUE_0 * getDefendingValue(bestMove, primaryPlayer) << endl;
    cout << "development value: " << DEVELOPMENTVALUE_0 * getDevelopmentValue(bestMove, primaryPlayer) << endl;

    cout << "overall value: " << bestMove.getMoveValue() << endl << endl;

    // for testing purposes - here on down till the return statement
    Manager mnger;
    mnger.setBoard(Brd);
    mnger.move(bestMove.startRow, bestMove.startCol, bestMove.endRow, bestMove.endCol); // make the move
    temp = mnger.board;

    // find and assign human move values
    humanMoves.clear();
    if(primaryPlayer == 0)
        findMoves(1);
    else
        findMoves(0);

    for(int j=0; j<humanMoves.size(); j++)
    {
        humanMoves[j].setMoveValue(
                CAPTUREVALUE_1 * getCaptureValue(humanMoves[j], 1) + 
                MOVEABLEVALUE_1 * findMoveableSpaces(humanMoves[j], 1) + 
                ATTACKINGVALUE_1 * getAttackingValue(humanMoves[j], 1) - 
                ATTACKERSVALUE_1 * numAttackers(humanMoves[j], 1) + 
                DEFENDINGVALUE_1 * getDefendingValue(humanMoves[j], 1) + 
                DEVELOPMENTVALUE_1 * getDevelopmentValue(humanMoves[j], 1) +
                PRESSUREVALUE_1 * getPressureValue(humanMoves[j], 1));

                 /*cout << "\nstarting row/col: " << humanMoves[j].startRow << " " << humanMoves[j].startCol << " ending row/col: " << humanMoves[j].endRow << " " << humanMoves[j].endCol << endl;
                cout << "capture value of move: " << CAPTUREVALUE_0 * getCaptureValue(humanMoves[j], 1) << endl;
                cout << "moveable spaces: " << MOVEABLEVALUE_0 * findMoveableSpaces(humanMoves[j], 1) << endl;
                cout << "attack value: " << ATTACKINGVALUE_0*  getAttackingValue(humanMoves[j], 1) << endl;
                cout << "numAttackers: " << ATTACKERSVALUE_0 * numAttackers(humanMoves[j], 1) << endl;
                cout << "defending value: " << DEFENDINGVALUE_0 * getDefendingValue(humanMoves[j], 1) << endl;
                cout << "development value: " << DEVELOPMENTVALUE_0 * getDevelopmentValue(humanMoves[j], 1) << endl;

                cout << "overall value: " << humanMoves[j].getMoveValue() << endl << endl;*/


        //cout << "calculating human move #" << j << endl;
    }   

    Board forwardBoard;

    Move maxValue = humanMoves[0];
    for(int j=1; j<humanMoves.size(); j++)
    {
        if(humanMoves[j].getMoveValue() > maxValue.getMoveValue())
            maxValue = humanMoves[j];
    }

    /*cout << "Best Human Move in response" << endl;

     cout << "\nstarting row/col: " << maxValue.startRow << " " << maxValue.startCol << " ending row/col: " << maxValue.endRow << " " << maxValue.endCol << endl;
    cout << "capture value of move: " << CAPTUREVALUE_0 * getCaptureValue(maxValue, 1) << endl;
    cout << "moveable spaces: " << MOVEABLEVALUE_0 * findMoveableSpaces(maxValue, 1) << endl;
    cout << "attack value: " << ATTACKINGVALUE_0*  getAttackingValue(maxValue, 1) << endl;
    cout << "numAttackers: " << ATTACKERSVALUE_0 * numAttackers(maxValue, 1) << endl;
    cout << "defending value: " << DEFENDINGVALUE_0 * getDefendingValue(maxValue, 1) << endl;
    cout << "development value: " << DEVELOPMENTVALUE_0 * getDevelopmentValue(maxValue, 1) << endl;

    cout << "overall value: " << maxValue.getMoveValue() << endl << endl;*/



    return bestMove;
}

double AI::findGains(int player)
{
    //cout << "before first if" << endl;
    if(player == primaryPlayer)
    {
        //cout << "inside first if" << endl;
        findMoves(primaryPlayer);
        //cout << "after find moves" << endl;

        for(int i=0; i<moves.size(); i++)
        {
            moves[i].setMoveValue(
            CAPTUREVALUE_0 * getCaptureValue(moves[i], player) + 
            MOVEABLEVALUE_0 * findMoveableSpaces(moves[i], player) + 
            ATTACKINGVALUE_0 * getAttackingValue(moves[i], player) - 
            ATTACKERSVALUE_0 * numAttackers(moves[i], player) + 
            DEFENDINGVALUE_0 * getDefendingValue(moves[i], player) + 
            DEVELOPMENTVALUE_0 * getDevelopmentValue(moves[i], player) +
            PRESSUREVALUE_0 * getPressureValue(moves[i], player));

            if(turnsAhead == 1)
                cout << "AI move value: " << moves[i].value << endl; 
            
            //cout << "calculating AI move #" << i << endl;
        }   

    }

    else
    {
        //cout << "inside else" << endl;
        for(int i=0; i<moves.size(); i++) // each AI move
        {
            cout << "AI move" << endl;
            cout << "\nstarting row/col: " << moves[i].startRow << " " << moves[i].startCol << " ending row/col: " << moves[i].endRow << " " << moves[i].endCol << endl;
            cout << "capture value of move: " << CAPTUREVALUE_0 * getCaptureValue(moves[i], 1) << endl;
            cout << "moveable spaces: " << MOVEABLEVALUE_0 * findMoveableSpaces(moves[i], 1) << endl;
            cout << "attack value: " << ATTACKINGVALUE_0*  getAttackingValue(moves[i], 1) << endl;
            cout << "numAttackers: " << ATTACKERSVALUE_0 * numAttackers(moves[i], 1) << endl;
            cout << "defending value: " << DEFENDINGVALUE_0 * getDefendingValue(moves[i], 1) << endl;
            cout << "development value: " << DEVELOPMENTVALUE_0 * getDevelopmentValue(moves[i], 1) << endl;

            cout << "overall value: " << moves[i].getMoveValue() << endl << endl;




            Manager mnger;
            mnger.setBoard(Brd);
            mnger.move(moves[i].startRow, moves[i].startCol, moves[i].endRow, moves[i].endCol); // make the move
            temp = mnger.board;
            

            // find and assign human move values
            humanMoves.clear();
            if(primaryPlayer == 0)
                findMoves(1);
            else
                findMoves(0);

            for(int j=0; j<humanMoves.size(); j++)
            {
                //cout << getCaptureValue(humanMoves[j], player) << endl;
                humanMoves[j].setMoveValue(
                CAPTUREVALUE_1 * getCaptureValue(humanMoves[j], player) + 
                MOVEABLEVALUE_1 * findMoveableSpaces(humanMoves[j], player) + 
                ATTACKINGVALUE_1 * getAttackingValue(humanMoves[j], player) - 
                ATTACKERSVALUE_1 * numAttackers(humanMoves[j], player) + 
                DEFENDINGVALUE_1 * getDefendingValue(humanMoves[j], player) + 
                DEVELOPMENTVALUE_1 * getDevelopmentValue(humanMoves[j], player) +
                PRESSUREVALUE_1 * getPressureValue(humanMoves[j], player));
             
            }   

            Board forwardBoard;

            Move maxValue = humanMoves[0];
            for(int j=1; j<humanMoves.size(); j++)
            {
                if(humanMoves[j].getMoveValue() > maxValue.getMoveValue())
                    maxValue = humanMoves[j];
            }

            cout << "Max human move" << endl;
            cout << "\nstarting row/col: " << maxValue.startRow << " " << maxValue.startCol << " ending row/col: " << maxValue.endRow << " " << maxValue.endCol << endl;
            cout << "capture value of move: " << CAPTUREVALUE_0 * getCaptureValue(maxValue, 1) << endl;
            cout << "moveable spaces: " << MOVEABLEVALUE_0 * findMoveableSpaces(maxValue, 1) << endl;
            cout << "attack value: " << ATTACKINGVALUE_0*  getAttackingValue(maxValue, 1) << endl;
            cout << "numAttackers: " << ATTACKERSVALUE_0 * numAttackers(maxValue, 1) << endl;
            cout << "defending value: " << DEFENDINGVALUE_0 * getDefendingValue(maxValue, 1) << endl;
            cout << "development value: " << DEVELOPMENTVALUE_0 * getDevelopmentValue(maxValue, 1) << endl;

            cout << "overall value: " << maxValue.getMoveValue() << endl << endl;




            if (turnsAhead < lookAhead)
            {
                cout << "inside recursive block" << endl;
            	//for (int j = 0; j < humanMoves.size(); j++) // for each human move, make the move
            	//{
            		Manager forwardManager;
            		forwardManager.setBoard(temp);
            		forwardManager.move(maxValue.startRow, maxValue.startCol, maxValue.endRow, maxValue.endCol);
            		forwardBoard = forwardManager.board;
            		
            		AI forwardAI(forwardBoard, ++turnsAhead, primaryPlayer, lookAhead, turn); // call another AI
            		
            		//cout << "looking " << turnsAhead << " ahead" << endl;
            		//cout << "currently at AI move #" << i << endl;
            		//cout << "currently at human move #" << j << endl;
            		
            		Move forwardMove;
            		forwardMove = forwardAI.overallAlgorithm(player); // get move from AI
            		
            		humanMoves[i].setMoveValue(humanMoves[i].getMoveValue() - double(1/double(turnsAhead))*forwardMove.getMoveValue());

            	//}
            }

            cout << "original value: " << moves[i].getMoveValue() << " response: " << maxValue.getMoveValue();
            //cout << "max human move value: " << maxValue.getMoveValue() << endl;
            //cout << "start: " << maxValue.startRow << maxValue.startCol << endl;
            //cout << "end: " << maxValue.endRow << maxValue.endCol << endl;
            moves[i].setMoveValue(moves[i].getMoveValue() - maxValue.getMoveValue());
             cout << " final value: " << moves[i].getMoveValue() << endl; 
        }
    }

}

void AI::updateKingValue(int player)
{
    double val = turn * .07;

    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 8; c++)
        {
             if(Brd.chessBoard[c][r].getChar() == 'K' & player == 1 | Brd.chessBoard[c][r].getChar() == 'k' & player == 0 ) 
             {
                 Brd.chessBoard[c][r].setValue(int(val));
                 cout << "king at position: " << r << c << " and has value: " << Brd.chessBoard[c][r].getValue() << endl;
                 break;
             }
        }
    }
}

