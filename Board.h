#pragma once
#ifndef BOARD
#define BOARD
#include "Square.h"
#include "PieceArray.h"
class Board{
	private:
		Square board[3][4];
		Player player;
		PieceArray left;
		PieceArray right;
		void InitalizePieces();
		void SwitchPlayer();
		void DrawRow(std::ostream&, int) const;
		bool IsWithinBoard(Position) const;
		bool CanPlace(int, Position) const;
	public:
		Board();
		void Draw(std::ostream&) const;
		void ShowTurn(std::ostream&) const;
		bool MovePiece(Position, Direction);
		bool PlayerHasPiece() const;
		bool PlacePiece(int, Position);
		bool IsGameOver() const;
		friend std::ostream& operator <<(std::ostream&, const Board&);
};

#endif 