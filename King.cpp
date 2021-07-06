#include "King.h"
using namespace std;
King::King(Player player, Position pos) :Piece(player, pos) {
	SetName("King");
}
bool King::CanMoveTo(Direction dir) const{
	return true;
}

void King::PrintLabel(ostream& os) const {
	os << "шн";
}