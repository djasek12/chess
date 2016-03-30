#include "manager.h"
#include <ctype.h>
#include <stdlib.h>
#include <algorithm>

Manager::Manager(){

}

void Manager::move( int sourceRow, int sourceColumn, int targetRow, int targetColumn ){ //actually moves pieces
	//determine if piece is being captured
	int captureStatus = 0; //0 signifies not a capturing move, etc...
	
	if( board.chessBoard[targetColumn].at(targetRow).getPlayer() != 2){
	    captureStatus = 1;
	}

	if( captureStatus == 0){
		swap(  board.chessBoard[targetColumn].at(targetRow), board.chessBoard[sourceColumn].at(sourceRow));		
	}

	if( captureStatus == 1){
		swap(  board.chessBoard[targetColumn].at(targetRow), board.chessBoard[sourceColumn].at(sourceRow));	
		//get null piece from null board
		for( int i = 0; i < 8; i++){
			for( int j = 0; j < 8; j++){
				if (board.nullBoard[j].at(i).getPlayer() == 2){
					targetColumn = j;
					targetRow = i;
					break;
				}
			}
		}
			swap(  board.nullBoard[targetColumn].at(targetRow), board.chessBoard[sourceColumn].at(sourceRow));	
	}	
	
}

/*Returns the following:
    0: Valid Move, 1: Move coordinates out of bounds 
    2: Source piece player different from player with turn, attacked same team
    3: Move not valid  
*/
int Manager::checkMove( int sourceRow, int sourceColumn, int targetRow, int targetColumn, int curPlayer){
    if( checkBounds( sourceRow, sourceColumn, targetRow, targetColumn) == 0){
        return 1; //not in bounds
    }else if( checkPlayer( sourceRow, sourceColumn, targetRow, targetColumn, curPlayer) == 0){
        return 2; //player not valid
    }else if( checkSpecific( sourceRow, sourceColumn, targetRow, targetColumn, curPlayer) == 0){
        return 3;
    }
    
       
}

/*Return 1 for inbounds (valid), 0 otherwise */
int Manager::checkBounds( int sourceRow, int sourceColumn, int targetRow, int targetColumn ){
    //check each coordinate individually for validity
    if(  sourceRow < 0 || sourceRow > 7){
        return 0;
    }else if( sourceColumn < 0 || sourceColumn > 7){
        return 0;
    }else if( targetRow < 0 || targetRow > 7){
        return 0;
    }else if( targetColumn < 0 || targetColumn > 7){
        return 0;
    }
    //check to make sure source and target are not the same
    if( sourceRow == targetRow && sourceColumn == targetColumn ){
        return 0; 
    }

    //if prog reaches this point, move is in bounds
    return 1;
}

/*Return 1 for valid, 0 otherwise */
int Manager::checkPlayer( int sourceRow, int sourceColumn, int targetRow, int targetColumn, int curPlayer){
    //check if curPlayer matches source piece 
    if( board.chessBoard[sourceColumn].at(sourceRow).getPlayer() != curPlayer){
        return 0;
    }    
    //if prog reaches this point, move is valid
    return 1;
}

/*Return 1 for valid move, 0 otherwise */
int Manager::checkSpecific( int sourceRow, int sourceColumn, int targetRow, int targetColumn, int curPlayer){
    //determine which piece it is
    char curChar = tolower(board.chessBoard[sourceColumn].at(sourceRow).getChar());

    //call function appropriatte for that piece
    switch (curChar){
        case 'p': return checkPawn(sourceRow, sourceColumn, targetRow, targetColumn, curPlayer);
        default:  return 0;
    }
}

/*Return 1 for valid move, 0 otherwise */
int Manager::checkPawn( int sourceRow, int sourceColumn, int targetRow, int targetColumn, int curPlayer){
    bool isEmpty = 1;
    //determine if moving to empty or enemy
    if ( board.chessBoard[targetColumn].at(targetRow).getPlayer() != 2){
        isEmpty = 0;
    }
    //determine if vertical direction of move is correct
    if (curPlayer){ //must be moving up
        if(sourceRow - targetRow < 0){
            return 0; //moving in wrong direction
        }
    }else{ //must be moving down
        if(sourceRow - targetRow > 0){
            return 0; //moving in wrong direction
        }
    }
    
    //THIS IS A HACK, NEEDS FIXED
    swap(sourceRow, sourceColumn);
    swap(targetRow, targetColumn); 

    if (isEmpty){ //moving to empty
        //make sure not moving horizontally
        if( sourceRow - targetRow != 0){
            return 0; //moving horizontaly
        }
        int originalSpot = 0; //check if in original spot
        if (board.chessBoard[sourceColumn].at(sourceRow).getPlayer() == 1 && sourceColumn == 6){
            originalSpot = 1;
        }else if(board.chessBoard[sourceColumn].at(sourceRow).getPlayer() == 0 && sourceColumn == 1){
            originalSpot = 1;
        }

        //check if move is proper length
        if( originalSpot){
            int moveDiff = abs(sourceColumn - targetColumn);
            if( moveDiff >= 3) {
                return 0; //move too long
            }
        }
    }else{ //moving to enemy
        cout << "Reached" << endl;
        //make sure both vert and hor move are 1
        if( abs(sourceRow - targetRow) != 1 || abs(sourceColumn - targetColumn) != 1){
            return 0;
        }
    }
    //if reached, valid
    return 1;
}

void Manager::play(){
	//loadBoard();
    int currentPlayer = 0;
	while( 1){
        currentPlayer = 1 - currentPlayer; //flip between 0 and 1
		board.display();
        while( 1){
            game.getCoordinates();
            if( checkMove( game.getFromX(), game.getFromY(), game.getToX(), game.getToY(), currentPlayer) == 0){
                break;
            }else{
                cout << "Move is not valid!" << endl;
            }
        }
		move( game.getFromX(), game.getFromY(), game.getToX(), game.getToY() );
		saveBoard();
	}

        //AI AI_1(board);
       //AI_1.findMoves(board);
       // AI_1.dispValidMoves();
}

void Manager::saveBoard(){
	ofstream gamestate; 
	gamestate.open("gamestate");
	for( int i = 0; i < 8; i++){
		for( int j = 0; j < 8; j++){
			gamestate << board.chessBoard[j].at(i).getChar();	
		}
		gamestate << "\n";
	}
	gamestate.close();
}

void Manager::loadBoard(){
	ifstream gamefile; 
	string filename;
	cout << "Please enter the name of file to load from: ";
	cin >> filename;
	gamefile.open(filename.c_str());
	//read char from file into 2d array
	char boardArr[8][8];
	string currentString;
	string fileContents;
	while (getline( gamefile, currentString)){
		fileContents += currentString;
	}
	int count = 0;
	for( int i = 0; i < 8; i++){
		for( int j = 0; j < 8; j++){
			boardArr[i][j] = fileContents[count];
			count++;	
		}
	}
	//boardArr now holds the chars from file
	//now transform board to match boardArr
	for( int i = 0; i < 8; i++){
		for( int j = 0; j < 8; j++){
			char targetChar = boardArr[i][j]; 
			//find an appropriatte piece from the board
			int found = 0;
			for( int a = 0; a < 8; a++){
				for( int b = 0; b < 8; b++){
					if (board.chessBoard[b].at(a).getChar() == targetChar){
						move(  i, j, a, b);
						found = 1;
						break;		
					}
					if (found)
						break;
				}
			}
		}
	}	
}

void Manager::collectValues(){
	player0Val = 0;
	player1Val = 0;	
	
	for( int i = 0; i < 8; i++){
		for( int j = 0; j < 8; j++){
			if( board.chessBoard[j].at(i).getPlayer() == 0){
				player0Val += board.chessBoard[j].at(i).getValue();		
			}else if( board.chessBoard[j].at(i).getPlayer() == 1 ){
				player1Val += board.chessBoard[j].at(i).getValue();
			}
		}
	}	
}


