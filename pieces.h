#ifndef _PIECES_H_INCLUDED
#define _PIECES_H_INCLUDED

class Piece{ //base class for chess pieces
	public:
		Piece();
		void setChar( char);
		void setPlayer( int);
		void setValue( int);
		char getChar();
		int getPlayer();
		int getValue();
	protected:
		int player; //0 is caps, 1 is lower-case	
		char repChar; //p for pawn, etc...
		int value;
};

class Null: public Piece{
	public:
		Null(int); //should always be 2
	private:

};

class Pawn: public Piece{
	public:
		Pawn( int );
	private:
        

};

class Bishop: public Piece{
	public:
		Bishop(int);
	private:
};

class Knight: public Piece{
	public:
		Knight(int);
	private:
};

class Castle: public Piece{
	public:
		Castle(int);
	private:
};

class Queen: public Piece{
	public:
		Queen(int);
	private:
};

class King: public Piece{
	public:
		King(int);
	private:

};

#endif

