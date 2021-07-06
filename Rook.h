#pragma once
#ifndef ROOK
#define ROOK
#include "Piece.h"
class Rook:public Piece{
	public:
		Rook(Player, Position);
		bool CanMoveTo(Direction) const;
		void PrintLabel(std::ostream&) const;
};
#endif
