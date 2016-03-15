#ifndef _PIECES_H_INCLUDED
#define _PIECES_H_INCLUDED

class Piece{ //abstract base class for chess pieces
	public:
		Piece();
		virtual void validMove() const;
		void setChar( char);
		void setPlayer( int);
		void setValue( int);
		char getChar();
		int getPlayer();
		int getValue();
	private:
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
		void validMove();
	private:

};

class Bishop: public Piece{
	public:
		Bishop(int);
		void validMove();
	private:
};

class Knight: public Piece{
	public:
		Knight(int);
		void validMove();
	private:
};

class Castle: public Piece{
	public:
		Castle(int);
		void validMove();
	private:
};

class Queen: public Piece{
	public:
		Queen(int);
		void validMove();
	private:
};

class King: public Piece{
	public:
		King(int);
		void validMove();
	private:

};
#endif

