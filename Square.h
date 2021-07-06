#pragma once
#ifndef SQUARE
#define SQUARE
#include "Bishop.h"
#include "Pawn.h"
#include "King.h"
#include "Rook.h"
class Square{
	private:
		Piece* piece;
	public:
		Square();
		~Square();
		Piece* GetPiece() const;
		void SetPiece(Piece*);
		void Clear();

};
#endif

