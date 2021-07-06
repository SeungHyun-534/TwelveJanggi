#include "Rook.h"
using namespace std;
Rook::Rook(Player player, Position pos):Piece(player, pos) {
	SetName("Rook");
}

bool Rook::CanMoveTo(Direction dir) const {
	if (dir == UP || dir == DOWN || dir == LEFT || dir == RIGHT) {
		return true;
	}
	else return false;
}

void Rook::PrintLabel(ostream& os) const {
	os << "эт";
}