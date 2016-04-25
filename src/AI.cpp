// Danny Jasek and Billy Theisen
// CSE20212 Final Project
// AI class implementation

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
    // set data members
    Brd = B;
    turnsAhead = turnFuture;
    lookAhead = look;
    turn = turns;

    // change king value based on turns
    if(pmrPlyr == 0)
        updateKingValue(1);
    else
        updateKingValue(0);

    // constant weights for move calculation functions
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

    // sets primaryPlayer and otherPlayer variables
    primaryPlayer = pmrPlyr;
    if(primaryPlayer==0)
        otherPlayer = 1;
    else
        otherPlayer = 0;
}

// overall algorithm that returns an AI move
Move AI::overallAlgorithm(int player)
{
    // instantiate a manager and pass it the correct board
    Manager mnger;
    mnger.setBoard(Brd);

    // if the king is in check, return a move that gets out of it
    if(mnger.kingInCheck(player))
    {
        cout << "KING IN CHECK" << endl;
        return getOutOfCheck(player);
    }
    else // play a regular move
    {
        return playMove();
    }
}

// gets out of check
Move AI::getOutOfCheck(int player)
{  
    cout << "inside getOutofCheck" << endl;

    vector<Move> escapeMoves;
    Move dummyMove;

    cout << "player: " << player << endl;

    findMoves(player);

    cout << "moves size: " << moves.size() << endl;

    // if the primary player is in check, update the moves array with possible moves
    if(player == primaryPlayer)
    {
        for(int i=0; i<moves.size(); i++)
        {
            Manager mnger;
            mnger.setBoard(Brd);

            // make a move
            mnger.move(moves[i].startRow, moves[i].startCol, moves[i].endRow, moves[i].endCol); 
            if(!mnger.kingInCheck(player)) // if the player is no longer in check, add it to the escape moves vector
            {
                escapeMoves.push_back(moves[i]);
                cout << moves[i].startRow << moves[i].startCol << moves[i].endRow << moves[i].endCol << endl;
            }
        }
    }
    else // otherwise, update the humanMoves array
    {
        for(int i=0; i<humanMoves.size(); i++)
        {
            Manager mnger;
            mnger.setBoard(Brd);

            mnger.move(humanMoves[i].startRow, humanMoves[i].startCol, humanMoves[i].endRow, humanMoves[i].endCol); 
            if(!mnger.kingInCheck(player))
            {
                escapeMoves.push_back(humanMoves[i]);
                cout << humanMoves[i].startRow << humanMoves[i].startCol << humanMoves[i].endRow << humanMoves[i].endCol << endl;
            }
        }

    }

    cout << "escape moves: " << escapeMoves.size() << endl;

    // possibly change this for a checkmate function?
    if(escapeMoves.size() == 0)
    {
        Manager mnger;
        mnger.setBoard(Brd);
        dummyMove.startRow = -1;
        return dummyMove;
    }

    // set escape moves values
    for(int i=0; i<escapeMoves.size(); i++)
    {
        escapeMoves[i].setMoveValue(
        CAPTUREVALUE_0 * getCaptureValue(escapeMoves[i], player) + 
        MOVEABLEVALUE_0 * findMoveableSpaces(escapeMoves[i], player) + 
        ATTACKINGVALUE_0 *  getAttackingValue(escapeMoves[i], player) - 
        ATTACKERSVALUE_0 * numAttackers(escapeMoves[i], player) + 
        DEFENDINGVALUE_0 * getDefendingValue(escapeMoves[i], player));
    }

    // find best escape move
    Move bestMove = escapeMoves[0];
    for(int i=1; i<escapeMoves.size(); i++)
    {
        if(bestMove.getMoveValue() < escapeMoves[i].getMoveValue())
            bestMove = escapeMoves[i];
    }

    // play this move
    return bestMove;
}

//Given a player, finds all possible moves for that player, and adds them to a moves vector
void AI::findMoves(int player)
{
    // loop through each space in board vector
    for(int row=0; row<8; row++)
    {
        for(int col=0; col<8; col++)
        {
            if (player == primaryPlayer) // will add to moves
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
                                if(mnger.checkMove(row, col, r, c, player) == 0) // is valid move
                                {
                                    Move testMove(Brd.chessBoard[col][row], row, col, r, c); // make a move and add it to the vector
                                    moves.push_back(testMove);
                                }
                            }
                        }
                    }
                }
            }
            else // add to humanMoves
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


//look at move destination on board and find value of piece there
double AI::getCaptureValue(Move move, int player)
{
    Piece capturedPiece;

    if(player == primaryPlayer)
        capturedPiece = Brd.chessBoard[move.endCol][move.endRow]; // primaryPlayer's chess board
    else
        capturedPiece = temp.chessBoard[move.endCol][move.endRow]; // otherPlayer's chess board

    if(capturedPiece.getChar() != 32) // not null
    {
        return capturedPiece.getValue();
    }
    else
        return 0; 
}

// awards points from moving pieces (especially pawns) out of first 2 rows
int AI::getDevelopmentValue(Move move, int player) //needs to be fixed for human
{
    int develop = 0;

    Manager mnger;  // would like to be able to get rid of this
    if (player == primaryPlayer) // sends apprpriate board to mamanger
        mnger.setBoard(Brd);
    else
        mnger.setBoard(temp);

    if (primaryPlayer == 0) //?
    {
        if(move.startRow < 2 & move.endRow >= 2) // red player
            if (move.piece.getChar() == 'p')
                develop = 1.5;
            else
                develop = 1;
    }
    else
    {
        if (move.startRow > 5 & move.endRow <= 5) // blue player
            if (move.piece.getChar() == 'P')
                develop = 1.5;
            else 
                develop = 1;
    }

    return develop;
}

// awards points for defending one of your own pieces or having pieces defending you
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
            if(mnger.board.chessBoard[c][r].getPlayer() == player & tolower(mnger.board.chessBoard[c][r].getChar()) != 'k') // your own piece, but not the king (no point in defending the king)
            {
                if(r != move.endRow | c != move.endCol) // don't defend yourself
                {
                    if(mnger.checkMove2(move.endRow, move.endCol, r, c, player) == 2) // you can move there
                    {
                        youDefend += mnger.board.chessBoard[c][r].getValue(); 
                    }
                }
            }
        }
    }

    //cout << "you defend: " << youDefend <<endl;

    // gets pieces that can defend you
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

// returns difference in number of moveable spaces and number of moves you have for this turn
int AI::findMoveableSpaces(Move move, int player) //needs to be fixed for human
{
    int moveableSpaces = 0;
    Manager mnger;  // would like to be able to get rid of this
    if (player == primaryPlayer)
    	mnger.setBoard(Brd);
    else
    	mnger.setBoard(temp);

    mnger.move(move.startRow, move.startCol, move.endRow, move.endCol); // need to execute move on board so manager can parse it

    // each space on board
    for(int row=0; row<8; row++)
    {
        for(int col=0; col<8; col++)
        {

            if(mnger.board.chessBoard[col][row].getPlayer() == player) // is your pieces
            {
                // check all other spaces for possible moves
                for(int r=0; r<8; r++)
                {
                    for(int c=0; c<8; c++)
                    {
                        if(mnger.checkMove(row, col, r, c, player) == 0)
                        {
                            moveableSpaces++; // increment counter
                        }

                    }
                }
            }

        }
    }

    return moveableSpaces - moves.size();

}

// sums values of pieces you can attack after a certain move
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
                if(mnger.checkMove(move.endRow, move.endCol, r, c, player) == 0) // valid mvoe
                {
                    int value = mnger.board.chessBoard[c][r].getValue();
                    if(value > 0)
                    {
                        attackValue += value;
                    }
                }
            }
        }
    }

    return attackValue;
}

// sums number of pieces that can attack you after a move multiplied by your piece value/2
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
            if(mnger.board.chessBoard[c][r].getPlayer() == otherPlayer)
            {
                if(mnger.checkMove(r, c, move.endRow, move.endCol, otherPlayer) == 0)
                {
                    numAttackers++;
                }
            }

        }
    }
    return numAttackers * double(move.getPiece().getValue())/2;
}

// returns difference in number of kings moves it can make after the move and before the move - helps to end game
int AI::getPressureValue(Move move, int player)
{
    int kingMovesOld = 0;
    int kingMovesNew = 0;
    Manager mnger;

    // set board
    if (player == primaryPlayer)
        mnger.setBoard(Brd);
    else
        mnger.setBoard(temp);


    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((mnger.board.chessBoard[i][j].getChar() == 'K' && player == 0) || (mnger.board.chessBoard[i][j].getChar() == 'k' && player == 1)) // king
            {
                for (int row = 0; row < 8; row++)
                {
                    for (int col = 0; col < 8; col++)
                    {
                        if (player == 0)
                        {
                            if (mnger.checkMove(i, j, row, col, 1) == 0)
                            {
                                kingMovesOld++;
                            }
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

    mnger.move(move.startRow, move.startCol, move.endRow, move.endCol); // make the move

    // find new number of moves
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
                        {
                            if (mnger.checkMove(i, j, row, col, 1) == 0)
                            {
                                kingMovesNew++;
                            }
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

// simple AI that makes a random move
int AI::randomMove()
{
    srand(time(NULL));
    int moveIndex = rand()%moves.size();
    return moveIndex;
}

// returns a move
Move AI::playMove()
{     
    findGains(); // finds moves and their values

    // finds best move
    Move bestMove = moves[0];
    for(int i=1; i<moves.size(); i++)
    {
        if(bestMove.getMoveValue() < moves[i].getMoveValue())
            bestMove = moves[i];
    }

    cout << "best AI move" << endl;
    dispMoveValue(bestMove, primaryPlayer);

    return bestMove;
}

// recursive function that finds and assigns move values
double AI::findGains()
{
    if(turnsAhead == 1)
    {
        cout << "finding initial moves: turns Ahead = 1" << endl;

        // find AI moves and assign values
        findMoves(primaryPlayer);
        for(int i=0; i<moves.size(); i++)
        {
            moves[i].setMoveValue(
                    CAPTUREVALUE_0 * getCaptureValue(moves[i], primaryPlayer) + 
                    MOVEABLEVALUE_0 * findMoveableSpaces(moves[i], primaryPlayer) + 
                    ATTACKINGVALUE_0 * getAttackingValue(moves[i], primaryPlayer) - 
                    ATTACKERSVALUE_0 * numAttackers(moves[i], primaryPlayer) + 
                    DEFENDINGVALUE_0 * getDefendingValue(moves[i], primaryPlayer) + 
                    DEVELOPMENTVALUE_0 * getDevelopmentValue(moves[i], primaryPlayer) +
                    PRESSUREVALUE_0 * getPressureValue(moves[i], primaryPlayer));
        }

        for(int i=0; i<moves.size(); i++) // loop through each AI move
        {
            cout << "in " << i << "th move, turns ahead: " << turnsAhead << endl;

            //cout << "\nAI move" << endl;
            //dispMoveValue(moves[i], primaryPlayer);

            // set board and make the move
            Manager mnger;
            mnger.setBoard(Brd);
            mnger.move(moves[i].startRow, moves[i].startCol, moves[i].endRow, moves[i].endCol); // make the move
            temp = mnger.board;

            // find and assign human move values
            humanMoves.clear();
            findMoves(otherPlayer);
            for(int j=0; j<humanMoves.size(); j++)
            {
                humanMoves[j].setMoveValue(
                        CAPTUREVALUE_1 * getCaptureValue(humanMoves[j], otherPlayer) + 
                        MOVEABLEVALUE_1 * findMoveableSpaces(humanMoves[j], otherPlayer) + 
                        ATTACKINGVALUE_1 * getAttackingValue(humanMoves[j], otherPlayer) - 
                        ATTACKERSVALUE_1 * numAttackers(humanMoves[j], otherPlayer) + 
                        DEFENDINGVALUE_1 * getDefendingValue(humanMoves[j], otherPlayer) + 
                        DEVELOPMENTVALUE_1 * getDevelopmentValue(humanMoves[j], otherPlayer) +
                        PRESSUREVALUE_1 * getPressureValue(humanMoves[j], otherPlayer));
            }   

            // find best human move and make it
            Move maxValue = humanMoves[0];
            for(int j=1; j<humanMoves.size(); j++)
            {
                if(humanMoves[j].getMoveValue() > maxValue.getMoveValue())
                    maxValue = humanMoves[j];
            }
            // makes a new manager, and plays this AI move
            Manager forwardManager;
            Board forwardBoard;
            forwardManager.setBoard(temp);
            forwardManager.move(maxValue.startRow, maxValue.startCol, maxValue.endRow, maxValue.endCol);
            forwardBoard = forwardManager.board;

            //cout << "Max human move" << endl;
            //dispMoveValue(maxValue, otherPlayer);

            // recursive bit
            if (turnsAhead < lookAhead)
            {
                cout << "inside recursive block" << endl;

                // call a new AI on board with both AI and human move made, and get a mvoe back
                AI forwardAI(forwardBoard, turnsAhead+1, primaryPlayer, lookAhead, turn);
                Move forwardMove = forwardAI.overallAlgorithm(primaryPlayer);
                
                // update value of max human move appropriatley
                maxValue.setMoveValue(maxValue.getMoveValue() - double(1/double(turnsAhead))*forwardMove.getMoveValue());
            }

            //cout << "original value: " << moves[i].getMoveValue() << " response: " << maxValue.getMoveValue();
            moves[i].setMoveValue(moves[i].getMoveValue() - maxValue.getMoveValue()); // update AI move value w/new human move value
            cout << "move returned" << endl;
            //cout << " final value: " << moves[i].getMoveValue() << endl; 
        }
    }


    if(turnsAhead > 1) // greater than 1 level deep in recursion
    {
        cout << "inside turnsAhead > 1 block" << endl;

        // find AI moves and assign values
        findMoves(primaryPlayer);
        for(int i=0; i<moves.size(); i++)
        {
            moves[i].setMoveValue(
                    CAPTUREVALUE_0 * getCaptureValue(moves[i], primaryPlayer) + 
                    MOVEABLEVALUE_0 * findMoveableSpaces(moves[i], primaryPlayer) + 
                    ATTACKINGVALUE_0 * getAttackingValue(moves[i], primaryPlayer) - 
                    ATTACKERSVALUE_0 * numAttackers(moves[i], primaryPlayer) + 
                    DEFENDINGVALUE_0 * getDefendingValue(moves[i], primaryPlayer) + 
                    DEVELOPMENTVALUE_0 * getDevelopmentValue(moves[i], primaryPlayer) +
                    PRESSUREVALUE_0 * getPressureValue(moves[i], primaryPlayer));
        }


        cout << "moves size: " << moves.size() << endl;
        // only find the BEST move and make it
        Move maxValueMove = moves[0];

        cout << "set initial max" << endl;
        for(int j=1; j<moves.size(); j++)
        {
            if(moves[j].getMoveValue() > maxValueMove.getMoveValue())
                maxValueMove = moves[j];
        }

        Manager mnger;
        mnger.setBoard(Brd);
        mnger.move(maxValueMove.startRow, maxValueMove.startCol, maxValueMove.endRow, maxValueMove.endCol); // make the move
        temp = mnger.board;

        cout << "made best ai move" << endl;

        // find best human move and make it
        humanMoves.clear();
        findMoves(otherPlayer);
        for(int j=0; j<humanMoves.size(); j++)
        {
            humanMoves[j].setMoveValue(
                    CAPTUREVALUE_1 * getCaptureValue(humanMoves[j], otherPlayer) + 
                    MOVEABLEVALUE_1 * findMoveableSpaces(humanMoves[j], otherPlayer) + 
                    ATTACKINGVALUE_1 * getAttackingValue(humanMoves[j], otherPlayer) - 
                    ATTACKERSVALUE_1 * numAttackers(humanMoves[j], otherPlayer) + 
                    DEFENDINGVALUE_1 * getDefendingValue(humanMoves[j], otherPlayer) + 
                    DEVELOPMENTVALUE_1 * getDevelopmentValue(humanMoves[j], otherPlayer) +
                    PRESSUREVALUE_1 * getPressureValue(humanMoves[j], otherPlayer));
        }   

        // find best human move and make it
        Move maxValue = humanMoves[0];
        for(int j=1; j<humanMoves.size(); j++)
        {
            if(humanMoves[j].getMoveValue() > maxValue.getMoveValue())
                maxValue = humanMoves[j];
        }

        Manager forwardManager;
        Board forwardBoard;
        forwardManager.setBoard(temp);
        forwardManager.move(maxValue.startRow, maxValue.startCol, maxValue.endRow, maxValue.endCol);
        forwardBoard = forwardManager.board;

        //cout << "Max human move" << endl;
        //dispMoveValue(maxValue, otherPlayer);

        // recursive bit
        if (turnsAhead < lookAhead)
        {
            cout << "inside recursive block" << endl;
            
            AI forwardAI(forwardBoard, turnsAhead+1, primaryPlayer, lookAhead, turn); // call another AI
            Move forwardMove = forwardAI.overallAlgorithm(primaryPlayer); // get move from AI

            maxValue.setMoveValue(maxValue.getMoveValue() - double(1/double(turnsAhead))*forwardMove.getMoveValue());
        }

        //cout << "original value: " << moves[i].getMoveValue() << " response: " << maxValue.getMoveValue();
        maxValueMove.setMoveValue(maxValueMove.getMoveValue() - maxValue.getMoveValue());
        cout << "move returned" << endl;
        //cout << " final value: " << moves[i].getMoveValue() << endl; 


    }

}

// increase value of king as game progresses
void AI::updateKingValue(int player)
{
    double val = double(turn) * .5;

    cout << "turn: " << turn << endl;

    // find king and update its value
    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 8; c++)
        {
             if(Brd.chessBoard[c][r].getChar() == 'K' & player == 1 | Brd.chessBoard[c][r].getChar() == 'k' & player == 0 ) 
             {
                 Brd.chessBoard[c][r].setValue(3+val);
                 cout << "king at position: " << r << c << " and has value: " << Brd.chessBoard[c][r].getValue() << endl;
                 break;
             }
        }
    }
}

// displays the value of a given move given a certain player
void AI::dispMoveValue(Move mv, int player)
{
    cout << "starting row/col: " << mv.startRow << " " << mv.startCol << " ending row/col: " << mv.endRow << " " << mv.endCol << endl;
    if(player==0)
    {
        cout << "capture value of move: " << CAPTUREVALUE_0 * getCaptureValue(mv, player) << endl;
        cout << "moveable spaces: " << MOVEABLEVALUE_0 * findMoveableSpaces(mv, player) << endl;
        cout << "attack value: " << ATTACKINGVALUE_0 * getAttackingValue(mv, player) << endl;
        cout << "numAttackers: " << ATTACKERSVALUE_0 * numAttackers(mv, player) << endl;
        cout << "defending value: " << DEFENDINGVALUE_0 * getDefendingValue(mv, player) << endl;
        cout << "pressure value: " << PRESSUREVALUE_0 * getPressureValue(mv, player);
    }
    else
    {
        cout << "capture value of move: " << CAPTUREVALUE_1 * getCaptureValue(mv, player) << endl;
        cout << "moveable spaces: " << MOVEABLEVALUE_1 * findMoveableSpaces(mv, player) << endl;
        cout << "attack value: " << ATTACKINGVALUE_1 * getAttackingValue(mv, player) << endl;
        cout << "numAttackers: " << ATTACKERSVALUE_1 * numAttackers(mv, player) << endl;
        cout << "defending value: " << DEFENDINGVALUE_1 * getDefendingValue(mv, player) << endl;
        cout << "pressure value: " << PRESSUREVALUE_1 * getPressureValue(mv, player);
    }

    cout << "\noverall value: " << mv.getMoveValue() << endl << endl;
}
