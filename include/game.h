#ifndef _GAME_H_INCLUDED
#define _GAME_H_INCLUDED
#include <string>

class Game{
	public:
		Game();
		void getCoordinates();
		void moveFrom();
		void moveTo();
		int parseCoordinatesFrom( std::string ); //0 is success, 1 is failur
		int parseCoordinatesTo( std::string );
		int repairCoordinatesX( int ); //convert board representation to vector representation
		int repairCoordinatesY( int );
		void setFromX( int); 
		void setFromY( int);
		void setToX( int);
		void setToY( int);
		int getFromX();
		int getFromY();
		int getToX();
		int getToY();
		void play();
		void makeMove( int, int, int, int);
	private:
		int moveFromX, moveFromY;
		int moveToX, moveToY;
};

#endif
