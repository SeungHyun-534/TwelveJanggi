#pragma once
#ifndef KING
#define KING
#include "Piece.h"
class King:public Piece{
	public:
		King(Player, Position);
		bool CanMoveTo(Direction) const;
		void PrintLabel(std::ostream&) const;
};
#endif
