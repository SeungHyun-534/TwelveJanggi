#pragma once
#ifndef PIECE
#define PIECE
#include <iostream>
#include <string>

enum Player {PLAYER_LEFT, PLAYER_RIGHT};

enum Direction {UP,DOWN,LEFT,RIGHT,UPLEFT,UPRIGHT,DOWNLEFT,DOWNRIGHT};

struct Position {
	int x;
	int y;
};

class Piece{
	private:
		Player player;
		Position pos;
		std::string name;
	public:
		Piece(Player, Position);
		virtual void Init(Player, Position);
		Player GetPlayer() const;
		void SetPlayer(Player);
		Position GetPosition() const;
		virtual void SetPosition(Position);
		virtual bool CanMoveTo(Direction) const=0;
		virtual void PrintLabel(std::ostream&) const =0;
		void SetName(std::string);
		std::string GetName() const;
		
};

std::ostream& operator <<(std::ostream&, const Piece&);
#endif
