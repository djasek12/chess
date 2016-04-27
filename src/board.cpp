/*Includes*/
#include "../include/board.h"

/*Macros*/
#include "stdlib.h"
#include <locale>
#include <ctype.h>

Board::Board(){	
	dim = 8;
	initPieces();
}

void Board::initPieces(){
	//initialize pieces
	Pawn aPawn1(0), aPawn2(0), aPawn3(0), aPawn4(0), aPawn5(0), aPawn6(0), aPawn7(0), aPawn8(0);
	Pawn bPawn1(1), bPawn2(1), bPawn3(1), bPawn4(1), bPawn5(1), bPawn6(1), bPawn7(1), bPawn8(1);
	Null Null1(2), Null2(2), Null3(2), Null4(2), Null5(2), Null6(2), Null7(2), Null8(2);
	Null Null9(2), Null10(2), Null11(2), Null12(2), Null13(2), Null14(2), Null15(2), Null16(2);
	Null Null17(2), Null18(2), Null19(2), Null20(2), Null21(2), Null22(2), Null23(2), Null24(2); 
	Null Null25(2), Null26(2), Null27(2), Null28(2), Null29(2), Null30(2), Null31(2), Null32(2);	
	King aKing(0), bKing(1);
	Queen aQueen(0), bQueen(1);
	Bishop aBishop1(0), aBishop2(0), bBishop1(1), bBishop2(1);
	Castle aCastle1(0), aCastle2(0), bCastle1(1), bCastle2(1);
	Knight aKnight1(0), aKnight2(0), bKnight1(1), bKnight2(1);

	vector<Piece> tempVector;
	tempVector.push_back(aCastle1); tempVector.push_back(aPawn1);
	tempVector.push_back(Null1); tempVector.push_back(Null9); 
	tempVector.push_back(Null17); tempVector.push_back(Null25);
	tempVector.push_back(bPawn1); tempVector.push_back(bCastle1);
	chessBoard.push_back( tempVector);
	tempVector.clear();
	
	tempVector.push_back(aKnight1); tempVector.push_back(aPawn2);
	tempVector.push_back(Null2); tempVector.push_back(Null10); 
	tempVector.push_back(Null18); tempVector.push_back(Null26);
	tempVector.push_back(bPawn2); tempVector.push_back(bKnight1);
	chessBoard.push_back( tempVector);
	tempVector.clear();
	
	tempVector.push_back(aBishop1); tempVector.push_back(aPawn3);
	tempVector.push_back(Null3); tempVector.push_back(Null11); 
	tempVector.push_back(Null19); tempVector.push_back(Null27);
	tempVector.push_back(bPawn3); tempVector.push_back(bBishop1);
	chessBoard.push_back( tempVector);
	tempVector.clear();

	tempVector.push_back(aKing); tempVector.push_back(aPawn4);
	tempVector.push_back(Null4); tempVector.push_back(Null12); 
	tempVector.push_back(Null20); tempVector.push_back(Null28);
	tempVector.push_back(bPawn4); tempVector.push_back(bKing);
	chessBoard.push_back( tempVector);
	tempVector.clear();

	tempVector.push_back(aQueen); tempVector.push_back(aPawn5);
	tempVector.push_back(Null5); tempVector.push_back(Null13); 
	tempVector.push_back(Null21); tempVector.push_back(Null29);
	tempVector.push_back(bPawn5); tempVector.push_back(bQueen);
	chessBoard.push_back( tempVector);
	tempVector.clear();

	tempVector.push_back(aBishop2); tempVector.push_back(aPawn6);
	tempVector.push_back(Null6); tempVector.push_back(Null14); 
	tempVector.push_back(Null22); tempVector.push_back(Null30);
	tempVector.push_back(bPawn6); tempVector.push_back(bBishop2);
	chessBoard.push_back( tempVector);
	tempVector.clear();	
	
	tempVector.push_back(aKnight2); tempVector.push_back(aPawn7);
	tempVector.push_back(Null7); tempVector.push_back(Null15); 
	tempVector.push_back(Null23); tempVector.push_back(Null31);
	tempVector.push_back(bPawn7); tempVector.push_back(bKnight2);
	chessBoard.push_back( tempVector);
	tempVector.clear();

	tempVector.push_back(aCastle2); tempVector.push_back(aPawn8);
	tempVector.push_back(Null8); tempVector.push_back(Null16); 
	tempVector.push_back(Null24); tempVector.push_back(Null32);
	tempVector.push_back(bPawn8); tempVector.push_back(bCastle2);
	chessBoard.push_back( tempVector);
	tempVector.clear();
	
	Null Null33(2), Null34(2), Null35(2), Null36(2), Null37(2), Null38(2), Null39(2), Null40(2);
	Null Null41(2), Null42(2), Null43(2), Null44(2), Null45(2), Null46(2), Null47(2), Null48(2);
	Null Null49(2), Null50(2), Null51(2), Null52(2), Null53(2), Null54(2), Null55(2), Null56(2); 
	Null Null57(2), Null58(2), Null59(2), Null60(2), Null61(2), Null62(2), Null63(2), Null64(2);	
	Null Null65(2), Null66(2), Null67(2), Null68(2), Null69(2), Null70(2), Null71(2), Null72(2);
	Null Null73(2), Null74(2), Null75(2), Null76(2), Null77(2), Null78(2), Null79(2), Null80(2);
	Null Null81(2), Null82(2), Null83(2), Null84(2), Null85(2), Null86(2), Null87(2), Null88(2); 
	Null Null89(2), Null90(2), Null91(2), Null92(2), Null93(2), Null94(2), Null95(2), Null96(2);	

	tempVector.push_back(Null33); tempVector.push_back(Null34);
	tempVector.push_back(Null35); tempVector.push_back(Null36); 
	tempVector.push_back(Null37); tempVector.push_back(Null38);
	tempVector.push_back(Null39); tempVector.push_back(Null40);
	nullBoard.push_back( tempVector);
	tempVector.clear();

	tempVector.push_back(Null41); tempVector.push_back(Null42);
	tempVector.push_back(Null43); tempVector.push_back(Null44); 
	tempVector.push_back(Null45); tempVector.push_back(Null46);
	tempVector.push_back(Null47); tempVector.push_back(Null48);
	nullBoard.push_back( tempVector);
	tempVector.clear();

	tempVector.push_back(Null49); tempVector.push_back(Null50);
	tempVector.push_back(Null51); tempVector.push_back(Null52); 
	tempVector.push_back(Null53); tempVector.push_back(Null54);
	tempVector.push_back(Null55); tempVector.push_back(Null56);
	nullBoard.push_back( tempVector);
	tempVector.clear();
	
	tempVector.push_back(Null57); tempVector.push_back(Null58);
	tempVector.push_back(Null59); tempVector.push_back(Null60); 
	tempVector.push_back(Null61); tempVector.push_back(Null62);
	tempVector.push_back(Null63); tempVector.push_back(Null64);
	nullBoard.push_back( tempVector);
	tempVector.clear();

	tempVector.push_back(Null65); tempVector.push_back(Null66);
	tempVector.push_back(Null67); tempVector.push_back(Null68); 
	tempVector.push_back(Null69); tempVector.push_back(Null70);
	tempVector.push_back(Null71); tempVector.push_back(Null72);
	nullBoard.push_back( tempVector);
	tempVector.clear();
	
	tempVector.push_back(Null73); tempVector.push_back(Null74);
	tempVector.push_back(Null75); tempVector.push_back(Null76); 
	tempVector.push_back(Null77); tempVector.push_back(Null78);
	tempVector.push_back(Null79); tempVector.push_back(Null80);
	nullBoard.push_back( tempVector);
	tempVector.clear();

	tempVector.push_back(Null81); tempVector.push_back(Null82);
	tempVector.push_back(Null83); tempVector.push_back(Null84); 
	tempVector.push_back(Null85); tempVector.push_back(Null86);
	tempVector.push_back(Null87); tempVector.push_back(Null88);
	nullBoard.push_back( tempVector);
	tempVector.clear();
	
	tempVector.push_back(Null89); tempVector.push_back(Null90);
	tempVector.push_back(Null91); tempVector.push_back(Null92); 
	tempVector.push_back(Null93); tempVector.push_back(Null94);
	tempVector.push_back(Null95); tempVector.push_back(Null96);
	nullBoard.push_back( tempVector);
	tempVector.clear();

    Queen Queen1(1), Queen2(1), Queen3(1), Queen4(1);
    Queen Queen5(1), Queen6(1), Queen7(1), Queen8(1);

    Queen Queen11(0), Queen12(0) , Queen13(0), Queen14(0);
    Queen Queen15(0), Queen16(0) , Queen17(0), Queen18(0);
    
    tempVector.push_back(Queen1); tempVector.push_back(Queen2);
    tempVector.push_back(Queen3); tempVector.push_back(Queen4);
    tempVector.push_back(Queen5); tempVector.push_back(Queen6);
    tempVector.push_back(Queen7); tempVector.push_back(Queen8);
    queenBoard.push_back(tempVector);
    tempVector.clear();
    
    tempVector.push_back(Queen11); tempVector.push_back(Queen12);
    tempVector.push_back(Queen13); tempVector.push_back(Queen14);
    tempVector.push_back(Queen15); tempVector.push_back(Queen16);
    tempVector.push_back(Queen17); tempVector.push_back(Queen18);
    queenBoard.push_back(tempVector);
    tempVector.clear();

}



void Board::display(){
	cout << "\033[2J\033[1;1H";
	cout << "    a  b  c  d  e  f  g  h" << endl << endl;
	for( int i = 0; i < dim; i++){
		cout << 8 - i << "  ";
		for( int j = 0; j < dim; j++){
			cout << "|";
			if (isupper(chessBoard[j].at(i).getChar()))
				cout << "\033[0;36m" << char(toupper(chessBoard[j].at(i).getChar())) << "\033[0m";
			else if (islower(chessBoard[j].at(i).getChar()))
				cout << "\033[1;31m" << char(toupper(chessBoard[j].at(i).getChar())) << "\033[0m";
			else
				cout << chessBoard[j].at(i).getChar();	
			cout << "|";
		}
		cout << endl;
	}
	cout << endl << endl;
}

