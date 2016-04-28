/*Includes*/
#include "../include/board.h"
#include <string>

// implementation for moving pieces around the 2-d board vector and related items

Game::Game(){
	//default constructor
}

void Game::getCoordinates(){
	moveFrom();
	moveTo();	
	moveFromX = repairCoordinatesX( moveFromX );
	moveToX = repairCoordinatesX( moveToX );
	moveFromY = repairCoordinatesY( moveFromY );
	moveToY = repairCoordinatesY( moveToY);	
}

void Game::moveFrom(){
	while(1){
		string coordinates;	
		cout << "Please enter the location of the piece to move: ";
		cin >> coordinates;
		if( parseCoordinatesFrom( coordinates ) == 0){
			break;
		}
	}
}

void Game::moveTo(){
	while(1){
		string coordinates;
		cout << "Please enter the location to move to: ";
		cin >> coordinates;
		if( parseCoordinatesTo( coordinates ) == 0){
			break;
		}
	}
}

int Game::parseCoordinatesFrom( string coordinates ){
	if( coordinates.length()!= 2){
		cout << "Input not the correct length (Example input: 'a1')" << endl;
		return 1;
	}
	int y = coordinates.at(0) - 96;
	int x = coordinates.at(1) - 48;
	
	if( x < 1 || x > 8 || y < 1 || y > 8 ){
		cout << "Coordinates out of bounds!" << endl;
		return 1;
	}
	moveFromX = x;
	moveFromY= y;
	return 0;
}

int Game::parseCoordinatesTo( string coordinates ){
	if( coordinates.length()!= 2){
		cout << "Input not the correct length (Example input: 'a1')" << endl;
		return 1;
	}
	int y = coordinates.at(0) - 96;
	int x = coordinates.at(1) - 48;
	
	if( x < 1 || x > 8 || y < 1 || y > 8 ){
		cout << "Coordinates out of bounds!" << endl;
		return 1;
	}
	moveToX = x;
	moveToY= y;
	return 0;

}

int Game::repairCoordinatesX( int x ){
	switch( x ){
		case 1: return 7;
		case 2: return 6;
		case 3: return 5;
		case 4: return 4;
		case 5: return 3;
		case 6: return 2;
		case 7: return 1;
		case 8: return 0;
	}	
}

int Game::repairCoordinatesY( int y ){
	return (y - 1);
}

void Game::setFromX( int num){
	moveFromX = num;
}

void Game::setFromY( int num){
	moveFromY = num;
}

void Game::setToX( int num){
	moveToX = num;
}

void Game::setToY( int num){
	moveToY = num;
}

int Game::getFromX(){
	return moveFromX;
}

int Game::getFromY(){
	return moveFromY;
}

int Game::getToX(){
	return moveToX;
}

int Game::getToY(){
	return moveToY;
}



void Game::makeMove( int fromX, int fromY, int toX, int toY){
	//if( chessBoard[fromY].at(fromX).getPlayer() == 2) {
		//cout << "No piece there!" << endl;
	//}
}
