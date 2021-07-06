#include "Bishop.h"
using namespace std;
Bishop::Bishop(Player player, Position pos) :Piece(player, pos) {
	SetName("Bishop");
}

bool Bishop::CanMoveTo(Direction dir) const {
	if (dir == UPLEFT || dir == UPRIGHT || dir == DOWNRIGHT || dir == DOWNLEFT) {
		return true;
	}
	else return false;
}

void Bishop::PrintLabel(ostream& os) const {
	os << "ßÓ";
}