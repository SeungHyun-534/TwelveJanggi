#include "Pawn.h"
using namespace std;
Pawn::Pawn(Player player, Position pos): Piece(player,pos),isPromoted(false){
	SetName("Pawn");
}

void Pawn::Init(Player player, Position pos) {
	isPromoted = false;
	SetName("Pawn");
	Piece::Init(player, pos);
}

void Pawn::SetPosition(Position pos){
	if (GetPlayer() == PLAYER_LEFT && pos.x == 3 || GetPlayer() == PLAYER_RIGHT && pos.x == 0){
		isPromoted = true; 
		SetName("Pro");
	}
	Piece::SetPosition(pos);
}

bool Pawn::CanMoveTo(Direction dir) const {
	if (GetPlayer() == PLAYER_LEFT){
		if (isPromoted) {
			if (dir == UPLEFT || dir == DOWNLEFT) {
				return false;
			}
			else {
				return true;
			}
		}
		else {
			if (dir != RIGHT) {
				return false;
			}
			else {
				return true;
			}
		}
	}
	else{
		if (isPromoted) {
			if (dir == UPRIGHT|| dir == DOWNRIGHT) {
				return false;
			}
			else {
				return true;
			}
		}
		else {
			if (dir != LEFT) {
				return false;
			}
			else {
				return true;
			}
		}
	}
}

void Pawn::PrintLabel(ostream& os) const{
	os << "í­";
}




