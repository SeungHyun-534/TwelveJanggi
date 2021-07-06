#include "Square.h"
using namespace std;
Square::Square():piece(0){
}
Square::~Square() {
	if (piece) {
		delete piece;
	}
}
Piece* Square::GetPiece() const {
	return piece;
}

void Square::SetPiece(Piece* piece) {
	this->piece = piece;
}

void Square::Clear() {
	piece = 0;
}