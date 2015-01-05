#include "LG_Movement.h"


LG_Movement::LG_Movement(LG_Board_Place *from, LG_Board_Place *to)
{
	this->from = from;
	this->to = to;

	this->fromPiece = from->piece;
	this->toPiece = to->piece;

	this->fromNrPieces = from->nrPieces;
	this->toNrPieces = to->nrPieces;
}

LG_Board_Place * LG_Movement::getFrom(){
	return from;
}
LG_Board_Place * LG_Movement::getTo(){
	return to;
}
int LG_Movement::getFromNrPieces(){
	return fromNrPieces;
}
int LG_Movement::getToNrPieces(){
	return toNrPieces;
}
LG_Board_Piece * LG_Movement::getFromPiece(){
	return fromPiece;
}
LG_Board_Piece * LG_Movement::getToPiece(){
	return toPiece;
}




LG_Movement::~LG_Movement()
{
}
