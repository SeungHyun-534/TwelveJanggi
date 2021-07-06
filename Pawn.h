#pragma once
#ifndef PAWN
#define PAWN
#include "Piece.h"
class Pawn: public Piece{
	private:
		bool isPromoted;
	public:
		Pawn(Player, Position);
		void Init(Player, Position);
		void SetPosition(Position);
		bool CanMoveTo(Direction) const;
		void PrintLabel(std::ostream&) const;
		

};
#endif
