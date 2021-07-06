#pragma once
#ifndef PIECEARRAY
#define PIECEARRAY
#include "Bishop.h"
#include "Pawn.h"
#include "King.h"
#include "Rook.h"
class PieceArray{
	private:
		int length;
		int maxLength;
		Piece** arr;
	public:
		PieceArray(int);
		~PieceArray();
		int GetLength() const;
		Piece* GetPieceAt(int) const;
		void PushPiece(Piece*);
		Piece* PopPieceAt(int);
	    friend std::ostream& operator<<(std::ostream&, const PieceArray&);
};

#endif 
