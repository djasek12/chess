/*Includes*/
#include "../include/manager.h"

/*Macros*/
#include <ctype.h>
#include <stdlib.h>
#include <algorithm>
#include <fstream>

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
    //cout << "current player" << curPlayer << endl;
    if( checkBounds( sourceRow, sourceColumn, targetRow, targetColumn) == 0){
        return 1; //not in bounds
    }else if( checkPlayer( sourceRow, sourceColumn, targetRow, targetColumn, curPlayer) == 0){
        return 2; //player not valid
    }else if( checkSpecific( sourceRow, sourceColumn, targetRow, targetColumn, curPlayer) == 0){
        return 3;
    } else if(checkSpecific( sourceRow, sourceColumn, targetRow, targetColumn, curPlayer) == 2) {
        return 4;
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
        //cout << "not moving own player!: current player is " << curPlayer << " and your player is " << board.chessBoard[sourceColumn].at(sourceRow).getPlayer() << endl;
        //cout << "character of the piece is: " << board.chessBoard[sourceColumn].at(sourceRow).getChar() << endl;
        //board.display(); 
        return 0;
    }else if( board.chessBoard[sourceColumn].at(sourceRow).getPlayer() == board.chessBoard[targetColumn].at(targetRow).getPlayer()){
        //cout << "attacking own player!" << endl;
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
        case 'c': return checkCastle(sourceRow, sourceColumn, targetRow, targetColumn, curPlayer);
        case 'b': return checkBishop(sourceRow, sourceColumn, targetRow, targetColumn, curPlayer);
        case 'q': return checkQueen( sourceRow, sourceColumn, targetRow, targetColumn, curPlayer);
        case 'k': return checkKing( sourceRow, sourceColumn, targetRow, targetColumn, curPlayer);
        case 'n': return checkKnight( sourceRow, sourceColumn, targetRow, targetColumn, curPlayer);
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
    
    if (isEmpty){ //moving to empty
        //make sure not moving horizontally
        if( sourceColumn - targetColumn != 0){
            return 0; //moving horizontaly
        }
        int originalSpot = 0; //check if in original spot
        if (board.chessBoard[sourceColumn].at(sourceRow).getPlayer() == 1 && sourceRow == 6){
            originalSpot = 1;
        }else if(board.chessBoard[sourceColumn].at(sourceRow).getPlayer() == 0 && sourceRow == 1){
            originalSpot = 1;
        }


        //check if move is proper length
        int moveDiff = abs(sourceRow - targetRow);
        if(originalSpot)
        {
            if(moveDiff >= 3)
            {
                return 0; //move too long
            }
            
            if (moveDiff == 2 && sourceRow == 6 && board.chessBoard[sourceColumn].at(5).getPlayer() == curPlayer) {
                return 0; // prevents jumping piece on first move
            }
            
            if (moveDiff == 2 && sourceRow == 1 && board.chessBoard[sourceColumn].at(2).getPlayer() == curPlayer) {
                return 0; // prevents jumping piece on first move
            }
            
        }
        else
        {
            if(moveDiff >=2)
                return 0;
        }
    }
        
    else{//moving to enemy
        //make sure both vert and hor move are 1
        if( abs(sourceRow - targetRow) != 1 || abs(sourceColumn - targetColumn) != 1){
            return 0;
        }
    }
    //if reached, valid
    return 1;
}

int Manager::checkCastle( int sourceRow, int sourceColumn, int targetRow, int targetColumn, int curPlayer){
    //make sure that move is either entirely vertical or entirely horizontal
    int rowDif = targetRow - sourceRow;
    int colDif = targetColumn - sourceColumn;

    if( rowDif != 0 && colDif != 0){
        return 0; //cannot move both horizontally and vertically
    }
    //check to make sure that no pieces are in between
    if( rowDif == 0){
        int constant = 0;
        if( colDif > 0){
            constant = 1;
        }else{
            constant = -1;
        }
        for(int i = 1; i < abs(colDif); i++){
            if(  board.chessBoard[sourceColumn+constant*i].at(sourceRow).getPlayer() != 2){
                return 0;
            }
        }  
    }else{
        int constant = 0;
        if( rowDif >0 ){
            constant = 1;
        }else{
            constant = -1;
        }
        for( int i = 1; i < abs(rowDif); i++){
            if( board.chessBoard[sourceColumn].at(sourceRow+constant*i).getPlayer() != 2){
                return 0;
            }
        }
    }
    //if prog. reaches this point, then move is valid
    return 1;
}

int Manager::checkBishop( int sourceRow, int sourceColumn, int targetRow, int targetColumn, int curPlayer){
    int rowDif = targetRow - sourceRow;
    int colDif = targetColumn - sourceColumn;

    //check that move is diagonal
    if( abs(rowDif) != abs(colDif )){
        return 0;
    }
    //check that move is in both directions
    if( rowDif == 0 || colDif == 0 ){
        return 0;
    }
    
    //make sure that there is not a piece in the middle of a move
    int rowConst = 0;
    int colConst = 0;
    if(  rowDif > 0 ){
        rowConst = 1;
    }else{
        rowConst = -1;
    }
    if( colDif > 0 ){
        colConst = 1;
    }else{
        colConst = -1;
    }
    
    for( int i = 1; i < abs(rowDif) ; i++){
        if( board.chessBoard[sourceColumn+i*colConst].at(sourceRow+i*rowConst).getPlayer() != 2){
            return 0;
        }
    }

    //if prog. reaches this point, then move is valid
    return 1;
}

int Manager::checkQueen( int sourceRow, int sourceColumn, int targetRow, int targetColumn, int curPlayer){
    return (checkBishop(sourceRow, sourceColumn, targetRow, targetColumn, curPlayer) ||  
            checkCastle( sourceRow, sourceColumn, targetRow, targetColumn, curPlayer));
}

int Manager::checkKing( int sourceRow, int sourceColumn, int targetRow, int targetColumn, int curPlayer){
    if (curPlayer == 1 ) {
        if (abs(targetRow-sourceRow) == 0 && (targetColumn - sourceColumn) == -2) {
            if (board.chessBoard[3].at(7).getChar() != 'K') {
                return 0; }
            if (board.chessBoard[0].at(7).getChar() != 'C') {
                return 0; }
            if (board.chessBoard[1].at(7).getPlayer() != 2 || board.chessBoard[2].at(7).getPlayer() != 2) {
                return 0; }
            return 2; // returns 2 if castling is valid
            
        } else if(abs(targetRow-sourceRow) == 0 && (targetColumn - sourceColumn) == 2) {
            if (board.chessBoard[3].at(7).getChar() != 'K') {
                return 0; }
            if (board.chessBoard[7].at(7).getChar() != 'C') {
                return 0;}
            if (board.chessBoard[4].at(7).getPlayer() != 2 || board.chessBoard[5].at(7).getPlayer() != 2 ||
                board.chessBoard[6].at(7).getPlayer() != 2) {
                return 0;}
            
            return 2; // returns 2 if castling is valid
            
        } else if( abs(targetRow-sourceRow) > 1 || abs(targetColumn - sourceColumn) > 1 ){ //if move is longer than 1 space
            return 0;
        }
    } else if (curPlayer == 0) {
    
        if (abs(targetRow-sourceRow) == 0 && (targetColumn - sourceColumn) == -2) {
            if (board.chessBoard[3].at(0).getChar() != 'k') {
                return 0;}
            if (board.chessBoard[0].at(0).getChar() != 'c') {
                return 0; }
            if (board.chessBoard[1].at(0).getPlayer() != 2 || board.chessBoard[2].at(0).getPlayer() != 2) {
                return 0; }
            return 2; // returns 2 if castling is valid
            
        } else if(abs(targetRow-sourceRow) == 0 && (targetColumn - sourceColumn) == 2) {
            if (board.chessBoard[3].at(0).getChar() != 'k') {
                return 0;}
            if (board.chessBoard[7].at(0).getChar() != 'c') {
                return 0;}
            if (board.chessBoard[4].at(0).getPlayer() != 2 || board.chessBoard[5].at(0).getPlayer() != 2 ||
                board.chessBoard[6].at(0).getPlayer() != 2) {
                return 0;}
            
            return 2; // returns 2 if castling is valid
            
        } else if( abs(targetRow-sourceRow) > 1 || abs(targetColumn - sourceColumn) > 1 ){ //if move is longer than 1 space
            return 0;
        }
    
    }
    
    //if prog. reaches this point, then move is valid
    return 1;
}

// get rid of curPlayer parameter?
int Manager::checkKnight( int sourceRow, int sourceColumn, int targetRow, int targetColumn, int curPlayer){
    int rowDif = abs(targetRow-sourceRow);
    int colDif = abs(targetColumn-sourceColumn);
   
    if( (rowDif !=1 || colDif!= 2 ) && ( rowDif != 2 || colDif != 1)){
        return 0;
    } 
     

    return 1;
    
}

int Manager::kingInCheck(int player) {
    // returns 1 if player's king in check

    int krow, kcol;
    int i, j;
    int kingRow, kingCol;

    //cout << "player: " << player << endl;

    for (krow = 0; krow < 8; krow++) { // find location of player's king
        for (kcol = 0; kcol < 8; kcol++) {
            if (board.chessBoard[kcol].at(krow).getChar() == 'K' & player == 1 | board.chessBoard[kcol].at(krow).getChar() == 'k' & player == 0 ) {
                //cout << "found king at " << krow << kcol << endl;
                kingRow = krow;
                kingCol = kcol;
                break;
            }
        }
    }

    //cout << "krow and col" << kingRow << kingCol << endl;

    for (i = 0; i < 8; i++) { // check if player's king is in check
        for (j = 0; j < 8; j++) {
            if (board.chessBoard[i].at(j).getPlayer() != player) {
                //cout << "i and j" << i << j << endl;
                //cout << "player" << player << endl;

                if(checkMove(i, j, kingRow, kingCol, 1) == 0 & player == 0)
                {
                    //cout << "first if" << endl;
                    return 1;
                }
                    
                if(checkMove(i, j, kingRow, kingCol, 0) == 0 & player == 1)
                {
                    //cout << "second if" << endl;
                    return 1;
                }
            }
        }
    }

   
    return 0;

}

void Manager::play()
{
    string filename;
    int status = startGame();
    int currentPlayer = 0;
    if (status == 0){
        //load game
        cout << "Please enter the name of the file to load from: ";
        cin >> filename;
        int numLines = loadLog( filename);
        if ( numLines % 2 == 1){
            currentPlayer = 1;
        }
    }else if( status == 1){
        //new game
        cout << "Please enter a name of the file to save to: ";
        cin >> filename;
    }else{
        //eror
    }
    
    int turn = 0;
    while(1)
    {
        currentPlayer = 1 - currentPlayer; //flip between 0 and 1
        board.display();
        turn++;
        
        Move AI_move;
        int castling;
        int out_check;
        while(1)
        {
            castling = 0;
            out_check = 0;
            //print which player
            if(currentPlayer == 1 ) cout << "Player: BLUE" << endl;
            if(currentPlayer == 0 ) cout << "Player: red" << endl;
            
            if (end()) {
                return;
            }
            
            if(currentPlayer == 1) {
                if (kingInCheck(currentPlayer) == 1 ){
                    cout << "Your king is in check!" << endl;
                    
                    checkmate(currentPlayer);
                    
                    while(1) {
                        game.getCoordinates();
                        
                        
                        if(checkMove( game.getFromX(), game.getFromY(), game.getToX(), game.getToY(), currentPlayer) == 0){
                            Manager temp1;
                            temp1.setBoard(board);
                            
                            temp1.move(game.getFromX(), game.getFromY(), game.getToX(), game.getToY());
                            if (temp1.kingInCheck(currentPlayer) != 0) {
                                cout << "This move does not get you out of check, move is not valid!" << endl;
                            } else if (temp1.kingInCheck(currentPlayer) == 0) {
                                out_check = 1;
                                break;
                            }
                            
                        }
                        
                        else{
                            cout << "Move is not valid!" << endl;
                        }
                    }
                    
                }
                
                if (out_check) {
                    break;
                }
                
                checkmate(currentPlayer);
                game.getCoordinates();
                
                if(checkMove( game.getFromX(), game.getFromY(), game.getToX(), game.getToY(), currentPlayer) == 0){
                    
                    break;
                } else if (checkMove( game.getFromX(), game.getFromY(), game.getToX(), game.getToY(), currentPlayer) == 4) {
                    castling = 1;
                    break;
                    
                }else{
                    cout << "Move is not valid!" << endl;
                }
            }
            else // AI
            {
                //cout << "AI about to be constructed" << endl;
                
                AI AI_1(board, 1, 0, 3, turn);
                //cout << "AI has been constructed, play move function being called" << endl;
                //AI_1.findMoves(board);
                //AI_1.dispValidMoves();
                AI_move = AI_1.overallAlgorithm(0);
                cout << "move passed to manager correctly" << endl;
                //AI_move = AI_1.playMove();
                
                //cout << "capture value of move: " << AI_1.getCaptureValue(AI_move) << endl;;
                
                break;
            }
        }
        if(currentPlayer == 1)
        {
            if (castling) {
                move( game.getFromX(), game.getFromY(), game.getToX(), game.getToY() );
                if (game.getToY() == 1) {
                    move(7, 0, 7, 2);
                }
                else if (game.getToY() == 5) {
                    move(7, 7, 7, 4);
                }
                string encoded = translateMove( game.getFromX(), game.getFromY(), game.getToX(), game.getToY() );
                saveLog( filename, encoded);
            } else {
                move( game.getFromX(), game.getFromY(), game.getToX(), game.getToY() );
                string encoded = translateMove( game.getFromX(), game.getFromY(), game.getToX(), game.getToY() );
                saveLog( filename, encoded);
            }
        }
        else if(AI_move.startRow != -1) // not in checkmate
        {
            move(AI_move.startRow, AI_move.startCol, AI_move.endRow, AI_move.endCol);
            string encoded = translateMove(AI_move.startRow, AI_move.startCol, AI_move.endRow, AI_move.endCol);
            saveLog( filename, encoded);
        }
        else
        {
            cout << "Checkmate!" << endl;
            break;
        }
        
    }
    
}

void Manager::AIplay()
{ 
    string filename;
    int status = startGame();
    int currentPlayer = 0;
    if (status == 0){
        //load game
        cout << "Please enter the name of the file to load from: ";
        cin >> filename;
        int numLines = loadLog( filename);
        if ( numLines % 2 == 1){
            currentPlayer = 1;
        }
    }else if( status == 1){
        //new game
        cout << "Please enter a name of the file to save to: ";
        cin >> filename;
    }else{
        //eror 
    }
    
	int turn = 0;
    while(1)
    {
        currentPlayer = 1 - currentPlayer; //flip between 0 and 1
        board.display();
        turn++;
        
        int kings = 0;
		
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board.chessBoard[i][j].getChar() == 'k' || board.chessBoard[i][j].getChar() == 'K')
					kings++;
			}
		}
		
		if (kings != 2)
		{
			cout << "we have a winner!" << endl;
			break;
		}
		
        //int blah;
        //cin >> blah;

        Move AI_move;

        while(1)
        {
            //print which player
            if(currentPlayer == 1 ) cout << "Player: BLUE" << endl;
            if(currentPlayer == 0 ) cout << "Player: red" << endl; 

            if(currentPlayer == 1)
            {
                //cout << "AI about to be constructed" << endl;

                AI AI_1(board, 1, 1, 3, turn);
                //cout << "AI has been constructed, play move function being called" << endl;
                //AI_1.findMoves(board);
                //AI_1.dispValidMoves();
                AI_move = AI_1.overallAlgorithm(1);
                cout << "move passed to manager correctly" << endl;
                //AI_move = AI_1.playMove();

                //cout << "capture value of move: " << AI_1.getCaptureValue(AI_move) << endl;;

                break;

            }
            else // AI
            {
                //cout << "AI about to be constructed" << endl;

                AI AI_1(board, 1, 0, 1, turn);
                //cout << "AI has been constructed, play move function being called" << endl;
                //AI_1.findMoves(board);
                //AI_1.dispValidMoves();
                AI_move = AI_1.overallAlgorithm(0);
                cout << "move passed to manager correctly" << endl;
                //AI_move = AI_1.playMove();

                //cout << "capture value of move: " << AI_1.getCaptureValue(AI_move) << endl;;

                break;
            }
        }
            move(AI_move.startRow, AI_move.startCol, AI_move.endRow, AI_move.endCol);
            string encoded = translateMove(AI_move.startRow, AI_move.startCol, AI_move.endRow, AI_move.endCol);
            saveLog( filename, encoded); 
    }

}


string Manager::translateMove( int fromX, int fromY, int toX, int toY ){
    fromX += '0';
    fromY += '0';
    toX += '0';
    toY += '0';
    string translate = "";
    translate += fromX;
    translate += fromY;
    translate += toX;
    translate += toY;
    cout << translate << endl;
    return translate; 
}

/*Return 0 for load game, 1 for new game, 2 for failed */
int Manager::startGame(){
    //determine if new game or load game
    string type;
    cout << "Load: Load from file --- New: New Game: ";
    cin >> type; 

    if(  type[0] == 'L' || type[0] == 'l' ){
        return 0;
    }else if( type[0] == 'N' || type[0] == 'n' ){
        return 1; 
    }else{
        return 2;
    }
}

void Manager::saveLog(string filename, string move){
    ofstream savefile;
    filename.insert(0, "logs/");
    savefile.open(filename.c_str(), ios_base::app);    
    savefile << move << endl;
    savefile.close();

}

int Manager::loadLog(string filename){
    ifstream loadfile;
    string line;
    filename.insert(0, "logs/");
    loadfile.open(filename.c_str(), ios_base::in);
    int count = 0;
    while( getline( loadfile, line )){
        int fromX = int(line[0]) - '0';
        int fromY = int(line[1]) - '0';
        int toX = int(line[2]) - '0';
        int toY = int(line[3]) - '0';
        move(fromX, fromY, toX, toY);
        count++;
    }  
    return count;
}

void Manager::setBoard(Board B)
{
    board = B;
}

// function Danny and Billy made to switch the order checkMove was checking conditions
int Manager::checkMove2( int sourceRow, int sourceColumn, int targetRow, int targetColumn, int curPlayer){
    //cout << "current player" << curPlayer << endl;
    if( checkBounds( sourceRow, sourceColumn, targetRow, targetColumn) == 0)
    {
        return 1; //not in bounds
    }
    else if( checkSpecific( sourceRow, sourceColumn, targetRow, targetColumn, curPlayer) == 0)
    {
        return 3;
    }
    else if( checkPlayer( sourceRow, sourceColumn, targetRow, targetColumn, curPlayer) == 0)
    {
        return 2; //player not valid
    }
}

int Manager:: checkmate(int curPlayer) { // to see if player 1 checkmate, put in 1. 0 for 0
    
    int enemy = 1 - curPlayer;
    
    
    if (kingInCheck(curPlayer)) {
        
        int krow, kcol;
        int i, j, l, k;
        
        for (i = 0; i < 8; i++) { // find location of king
            for (j = 0; j < 8; j++) {
                if (board.chessBoard[j].at(i).getChar() == 'k' - curPlayer * 32) { // similiar to node instantiation
                    krow = i;
                    kcol = j;
                    i = 8;
                    break;
                }
            }
        }
        for (i = -1; i < 2; i++) { // checks columns left, same, and right of king location
            for (j = 0; j < 2; j++) { // flips between krow - 1 and krow + 1
                Manager temp; // temporary board to move king and see if once hes moved he becomes out of check
                temp.setBoard(board);
                
                if (temp.checkMove( krow, kcol, krow - 1 + j*2, kcol +
                                   i, curPlayer) == 0) { // checks if king can move there
                    temp.move(krow, kcol, krow - 1 + j*2, kcol + i); // if so, moves him on temporary board
                    if (temp.kingInCheck(curPlayer) == 0) // checks if he's still in check
                        return 0;
                }
            }
        }
        
        Manager temp1;
        temp1.setBoard(board);
        
        for (i = 0; i < 2; i++) { // this for loop checks the spots directly left and right of king, in same row
            if (temp1.checkMove( krow, kcol, krow, kcol - 1 + 2*i,
                                curPlayer) == 0) {
                temp1.move(krow, kcol, krow, kcol - 1 + 2*i);
                if (temp1.kingInCheck(curPlayer) == 0)
                    return 0;
            }
        }
        
        // this for loop checks for same team pieces, and sees if it can make any move and get king out of check
        for (i = 0; i < 8; i++) { // finds same team pieces
            for (j = 0; j < 8; j++) {
                if (board.chessBoard[j].at(i).getPlayer() == curPlayer) {
                    for (l = 0; l < 8; l++) { // sees if pieces can block check
                        for (k = 0; k < 8; k++) {
                            if (checkMove( i, j, l, k, curPlayer) == 0) {
                                Manager temp1;
                                temp1.setBoard(board);
                                temp1.move(i, j, l, k);
                                if (temp1.kingInCheck(curPlayer) == 0)
                                    return 0;
                            }
                        }
                    }
                }
            }
        
        // if function reaches this, king in checkmate
        cout <<
        "CHECKMATE\nCHECKMATE\nCHECKMATE\nCHECKMATE\nCHECKMATE\nCHECKMATE\nCHECKMATE\n";
        return 1;
    }
}}

void Manager::checkSwap() {
    for( int column = 0; column < 8; column++){
        if (board.chessBoard[column].at(0).getChar() == 'P'){
            for( int i = 0; i < 8; i++){
                if (board.queenBoard[0].at(i).getChar() == 'Q' ){
                    swap( board.chessBoard[column].at(0), board.queenBoard[0].at(i) );
                    return;
                }
            }
        }else if( board.chessBoard[column].at(7).getChar() == 'p'){
            for( int i = 0; i < 8; i++){
                if (board.queenBoard[1].at(i).getChar() == 'q' ){
                    swap( board.chessBoard[column].at(7), board.queenBoard[1].at(i) );
                    return;
                }
            }
        }
    }
}


int Manager:: end() {
    int red = 0, blue = 0;
    int i, j;
    for (i = 0; i < 8; i++) { // find location of king
        for (j = 0; j < 8; j++) {
            if (board.chessBoard[j].at(i).getChar() == 'K') {
               blue = 1;
                i = 8;
                break;
            }
        }
    }
    
    if (blue == 0) {
        cout << "Red team wins!" << endl;
        return 1;
    }
    for (i = 0; i < 8; i++) { // find location of king
        for (j = 0; j < 8; j++) {
            if (board.chessBoard[j].at(i).getChar() == 'k') { 
                red = 1;
                i = 8;
                break;
            }
        }
    }
    
    if (red == 0) {
        cout << "Blue team wins!" << endl;
        return 2;
    }
    
    return 0;
}
