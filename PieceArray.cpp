#include "PieceArray.h"
using namespace std;
PieceArray::PieceArray(int max): maxLength(max),length(0){
	arr = new Piece* [maxLength];
	for (int i = 0; i < maxLength; i++) {
		arr[i] = 0;
	}
}
PieceArray::~PieceArray() {
	// arr에 남아 있는 Piece를 해제
	for (int i = 0; i < maxLength; i++) {
		if (arr[i]) {
			delete arr[i];
		}
	}
	// arr 해제
	delete[] arr;
}
int PieceArray::GetLength() const {
	return length;
}

Piece* PieceArray::GetPieceAt(int index) const {
	return arr[index];
}

void PieceArray::PushPiece(Piece* piece) {
	for (int i = 0; i < maxLength; i++) {
		if (arr[i] == 0) {
			arr[i] = piece;
			break;
		}
	}
	++length;
}

Piece* PieceArray::PopPieceAt(int index) {
	Piece* tempt = arr[index];
	for (int i = index; arr[i]; i++) {
		arr[i] = arr[i + 1];
	}
	--length;
	return tempt;
}

 ostream& operator <<(ostream& os, const PieceArray& pa) {
	os << "Player's Pieces]: ";
	for (int i = 0; pa.arr[i]; i++) {
		os << *pa.arr[i];
		os << " ";
	}
	os << endl;
	return os;

}
