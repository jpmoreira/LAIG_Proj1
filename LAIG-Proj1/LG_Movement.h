#pragma once

#include "LG_Board_Place.h"

class LG_Movement
{
public:
	LG_Movement(LG_Board_Place *from, LG_Board_Place *to);
	~LG_Movement();

	LG_Board_Place *getFrom();
	LG_Board_Place *getTo();
	int getFromNrPieces();
	int getToNrPieces();
	LG_Board_Piece *getFromPiece();
	LG_Board_Piece *getToPiece();

private:
	LG_Board_Place *from, *to;
	LG_Board_Piece *fromPiece, *toPiece;
	int fromNrPieces, toNrPieces;

};

