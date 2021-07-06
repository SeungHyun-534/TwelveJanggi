#pragma once
#ifndef BISHOP
#define BISHOP
#include "Piece.h"
class Bishop: public Piece{
	public:
		Bishop(Player, Position);
		bool CanMoveTo(Direction) const;
		void PrintLabel(std::ostream&) const;
};
#endif
