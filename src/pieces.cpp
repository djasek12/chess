/*Includes*/
#include "../include/board.h"

// sets piece values, including value, player and character

// default piece
Piece::Piece(){
    repChar= 'x';
    player = 3;
    value = 0;
}

void Piece::setChar( char c){
	repChar = c;
}

void Piece::setPlayer( int num){
	player = num;	
}

void Piece::setValue(double val){
	value = val;
}

char Piece::getChar(){
	return repChar;
}

int Piece::getPlayer(){
	return player;
}

double Piece::getValue(){
	return value;
}

Null::Null(int num){
	setPlayer(num);
	setChar(32);
	setValue(0);
}

Pawn::Pawn(int num){
	setPlayer(num);
	setChar('p' - num * 32);
	setValue( 1);
}

Knight::Knight(int num){
	setPlayer(num);
	setChar('n' - num * 32);
	setValue( 3);
}

Castle::Castle(int num){
	setPlayer(num);
	setChar('c' - num * 32);
	setValue( 5);
}

Bishop::Bishop(int num){
	setPlayer(num);
	setChar('b' - num * 32);
	setValue( 3.5);
}

King::King(int num){
	setPlayer(num);
	setChar('k' - num * 32);
	setValue(3);
}

Queen::Queen(int num){
	setPlayer(num);
	setChar('q' - num * 32);
	setValue( 9);
}


