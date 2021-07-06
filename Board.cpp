#include "Board.h"
using namespace std;

Board::Board():left(7),right(7),player(PLAYER_LEFT){
	InitalizePieces();
}
void Board::Draw(ostream& os) const {
	os << "          Ａ          Ｂ          Ｃ          Ｄ\n";
	os << "    ┌───────────┬───────────┬───────────┬───────────┐\n";
	DrawRow(os, 0);
	DrawRow(os, 1);
	DrawRow(os, 2);
	os << "          Ａ          Ｂ          Ｃ          Ｄ" << endl;
}
void Board::ShowTurn(ostream& os) const {
	if (player == PLAYER_LEFT) {
		os << "Left player's turn!\n" << endl;
	}
	else {
		os << "Right player's turn!\n" << endl;
	}
}

bool Board::MovePiece(Position pos, Direction dir){
	//처음 고른 위치가 판 안의 영역인지 체크
	if (!IsWithinBoard(pos)) {
		cout << "[ERROR] The destination of this move is out of the board!" << endl;
		return false;
	}
	// 처음 고른 위치에 말이 있는지 체크
	if (board[pos.y][pos.x].GetPiece() == 0) {
		cout << "[ERROR] There is no piece in that position!" << endl;
		return false;
	}
	// 고른 말이 자신(player)의 말인지 체크
	if (board[pos.y][pos.x].GetPiece()->GetPlayer() != player){
		cout << "[ERROR] The piece is not yours!" << endl;
		return false;
	}
	// 고른 말이 입력한 방향대로 움직일 수 있는 말인지 체크
	if (!(board[pos.y][pos.x].GetPiece()->CanMoveTo(dir))) {
		cout << "[Error] ";
		board[pos.y][pos.x].GetPiece()->PrintLabel(cout);
		cout << " cannot move to that direction!" << endl;
		return false;
	}
	// dir 따른 pos 업데이트
	int a=0, b=0;
	switch (dir)
	{
	case UP: --b;
		break;
	case DOWN: ++b;
		break;
	case LEFT: --a;
		break;
	case RIGHT: ++a;
		break;
	case UPLEFT: --a; --b;
		break;
	case UPRIGHT: ++a; --b;
		break;
	case DOWNLEFT: --a; ++b;
		break;
	case DOWNRIGHT: ++a; ++b;
		break;
	}

	//pos를 이동하려는 좌표로 변환한다.
	pos.x += a; pos.y += b;

	if (IsWithinBoard(pos)) {
		if (board[pos.y][pos.x].GetPiece() == 0) {
			//빈 공간으로 이동할 경우
			board[pos.y][pos.x].SetPiece(board[pos.y - b][pos.x - a].GetPiece());
			board[pos.y][pos.x].GetPiece()->SetPosition(pos);
			board[pos.y - b][pos.x - a].Clear();
			SwitchPlayer();
			return true;
		}
		else if(board[pos.y][pos.x].GetPiece()->GetPlayer() == player){
			//자신의 말이 있는 곳으로 이동할 경우
			cout << "[ERROR] There is already another your piece!" << endl;
			return false;
		}
		else {
			//상대방의 말이 있는 곳으로 이동할 경우
			if (player == PLAYER_LEFT) {
				left.PushPiece(board[pos.y][pos.x].GetPiece());
				board[pos.y][pos.x].SetPiece(board[pos.y - b][pos.x - a].GetPiece());
				board[pos.y][pos.x].GetPiece()->SetPosition(pos);
				board[pos.y - b][pos.x - a].Clear();
				SwitchPlayer();
				return true;
			}
			else {
				right.PushPiece(board[pos.y][pos.x].GetPiece());
				board[pos.y][pos.x].SetPiece(board[pos.y - b][pos.x - a].GetPiece());
				board[pos.y][pos.x].GetPiece()->SetPosition(pos);
				board[pos.y - b][pos.x - a].Clear();
				SwitchPlayer();
				return true;
			}
		}
	}
	else{
		cout << "[ERROR] The destination of this move is out of the board!" << endl;
		return false;
	}
}

bool Board::PlayerHasPiece() const {
	if (player == PLAYER_LEFT) {
		if (left.GetLength() == 0) {
			cout << "[Error] There is no piece to place" << endl;
			return false;
		}
	}
	else {
		if (right.GetLength() == 0) {
			cout << "[Error] There is no piece to place" << endl;
			return false;
		}
	}
	return true;
}

bool Board::PlacePiece(int pieceIndex, Position pos) {

	if (!CanPlace(pieceIndex, pos)) return false;
	if (player == PLAYER_LEFT) {
		Piece* p = left.PopPieceAt(pieceIndex - 1);
		p->Init(PLAYER_LEFT, pos);
		board[pos.y][pos.x].SetPiece(p);
	}
	else {
		Piece* p = right.PopPieceAt(pieceIndex - 1);
		p->Init(PLAYER_RIGHT, pos);
		board[pos.y][pos.x].SetPiece(p);
	}
	SwitchPlayer();
	return true;
}
//임시 메소드
bool Board::IsGameOver() const {
	static int left_count = 0;
	static int right_count = 0;
	if (player == PLAYER_LEFT) {
		//자신의 왕이 포로로 잡혔는지 확인
		if (right.GetLength() != 0) {
			if (right.GetPieceAt(right.GetLength() - 1)->GetName() == "King") {
				system("cls");
				cout << *this;
				cout << "Left player's king is taken!" << endl;
				cout << "Right player WIN!" << endl;
				return false;
			}
		}
	}
	else {
		if (left.GetLength() != 0) {
			if (left.GetPieceAt(left.GetLength() - 1)->GetName() == "King") {
				system("cls");
				cout << *this;
				cout << "Right player's king is taken!" << endl;
				cout << "Left player WIN!" << endl;
				return false;
			}
		}
		
	}
	for (int i = 0; i < 3; i++) {
		if (board[i][0].GetPiece() != 0) {
			if (board[i][0].GetPiece()->GetName() == "King" && board[i][0].GetPiece()->GetPlayer() == PLAYER_RIGHT) {
				++right_count;
				break;
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		if (board[i][3].GetPiece() != 0) {
			if (board[i][3].GetPiece()->GetName() == "King" && board[i][3].GetPiece()->GetPlayer() == PLAYER_LEFT) {
				++left_count;
				break;
			}
		}
	}
	if (right_count == 2) {
		system("cls");
		cout << *this;
		cout << "Right player's King is in the enemy's region more than one turn!" << endl;
		cout << "Right player WIN!" << endl;
		return false;
	}
	else if (left_count == 2) {
		system("cls");
		cout << *this;
		cout << "Left player's King is in the enemy's region more than one turn!" << endl;
		cout << "Left player WIN!" << endl;
		return false;
	}
	else {
		return true;
	}
}
void Board::InitalizePieces() {
	Position x = { 1,1 };
	board[1][1].SetPiece(new Pawn(PLAYER_LEFT, x));
	x = { 0,0 };
	board[0][0].SetPiece(new Bishop(PLAYER_LEFT, x));
	x = { 0,1 };
	board[1][0].SetPiece(new King(PLAYER_LEFT, x));
	x = { 0,2 };
	board[2][0].SetPiece(new Rook(PLAYER_LEFT, x));
	x = { 2,1 };
	board[1][2].SetPiece(new Pawn(PLAYER_RIGHT, x));
	x = { 3,0 };
	board[0][3].SetPiece(new Rook(PLAYER_RIGHT, x));
	x = { 3,1 }; 
	board[1][3].SetPiece(new King(PLAYER_RIGHT, x));
	x = { 3,2 };
	board[2][3].SetPiece(new Bishop(PLAYER_RIGHT, x));
}

void Board::SwitchPlayer(){
	if (player == PLAYER_LEFT) player = PLAYER_RIGHT;
	else player = PLAYER_LEFT;
}
void Board::DrawRow(ostream& os, int index) const {
	Piece* p[4];
	for (int i = 0; i < 4; i++) {
		p[i] = board[index][i].GetPiece();
	}
	os << "    │";
	for (int i = 0; i < 4; i++) {
		if (p[i] == 0) {
			os << " 　　　　　";
		}
		else if (p[i]->GetName() == "Pawn") {
			os << " 　　　　　";
		}
		else if (p[i]->GetName() == "Pro") {
			if (p[i]->GetPlayer() == PLAYER_LEFT) {
				os << "  　 ↑　↗";
			}
			else {
				os << " ↖　↑　  ";
			}
		}
		else if (p[i]->GetName() == "Bishop") {
			os << " ↖　　　↗";
		}
		else if (p[i]->GetName() == "King") {
			os << " ↖　↑　↗";
		}
		else {
			os << " 　　↑　　";
		}
		os << "│";
	}
	os << "\n";
	os << "    │";
	for (int i = 0; i < 4; i++) {
		if (p[i] == 0) {
			os << " 　　　　　";
		}
		else if (p[i]->GetPlayer() == PLAYER_LEFT) {
			os << " 　■■■　";
		}
		else {
			os << " 　□□□　";
		}
		os << "│";
	}
	os << "\n";
	switch (index)
	{
	case 0: os << "  1 │";
		break;
	case 1: os << "  2 │";
		break;
	case 2: os << "  3 │";
		break;
	}
	for (int i = 0; i < 4; i++) {
		if (p[i] == 0) {
			os << " 　　　　　";
		}
		else if (p[i]->GetName() == "Pawn") {
			if (p[i]->GetPlayer() == PLAYER_LEFT) {
				os << " 　■子■→";
			}
			else {
				os << " ←□子□　";
			}
		}
		else if (p[i]->GetName() == "Pro") {
			if (p[i]->GetPlayer() == PLAYER_LEFT) {
				os << " ←■侯■→";
			}
			else {
				os << " ←□侯□→";
			}
		}
		else if (p[i]->GetName() == "Bishop") {
			if (p[i]->GetPlayer() == PLAYER_LEFT) {
				os << " 　■相■　";
			}
			else {
				os << " 　□相□　";
			}
		}
		else if (p[i]->GetName() == "King") {
			if (p[i]->GetPlayer() == PLAYER_LEFT) {
				os << " ←■王■→";
			}
			else {
				os << " ←□王□→";
			}
		}
		else {
			if (p[i]->GetPlayer() == PLAYER_LEFT) {
				os << " ←■將■→";
			}
			else {
				os << " ←□將□→";
			}
		}
		os << "│";
		
	}
	switch (index)
	{
	case 0: os << "  1 ";
		break;
	case 1: os << "  2 ";
		break;
	case 2: os << "  3 ";
		break;
	}
	os << "\n";
	os << "    │";
	for (int i = 0; i < 4; i++) {
		if (p[i] == 0) {
			os << " 　　　　　";
		}
		else if (p[i]->GetPlayer() == PLAYER_LEFT) {
			os << " 　■■■　";
		}
		else {
			os << " 　□□□　";
		}
		os << "│";
	}
	os << "\n";
	os << "    │";
	for (int i = 0; i < 4; i++) {
		if (p[i] == 0) {
			os << " 　　　　　";
		}
		else if (p[i]->GetName() == "Pawn") {
			os << " 　　　　　";
		}
		else if (p[i]->GetName() == "Pro") {
			if (p[i]->GetPlayer() == PLAYER_LEFT) {
				os << " 　  ↓　↘";
			}
			else {
				os << " ↙　↓　  ";
			}
		}
		else if (p[i]->GetName() == "Bishop") {
			os << " ↙　　　↘";
		}
		else if (p[i]->GetName() == "King") {
			os << " ↙　↓　↘";
		}
		else {
			os << " 　　↓　　";
		}
		os << "│";
	}
	os << "\n";
	if (index == 2) {
		os << "    └───────────┴───────────┴───────────┴───────────┘";
	}
	else {
		os << "    ├───────────┼───────────┼───────────┼───────────┤";
	}
	os << "\n";
}
bool Board::IsWithinBoard(Position pos) const {
	if (pos.x > 3 || pos.x < 0) {
		return false;
	}
	if (pos.y > 2 || pos.y < 0) {
		return false;
	}
	
	return true;

}
// 말을 배치할 때, 다음 사항을 체크하여 예외처리한다.
//1. index가 벗어나 있는지
//2. 그 위치에 이미 말이 있는지
//3. 상대 진영이 아닌지 
bool Board::CanPlace(int index, Position pos) const {
	if (player == PLAYER_LEFT) {
		if (left.GetLength() < index) {
			cout << "[ERROR] Index for piece is out of bound!" << endl;
			return false;
		}
		if (board[pos.y][pos.x].GetPiece() == 0 && pos.x !=3) {
			return true;
		}
		else if (board[pos.y][pos.x].GetPiece() != 0) {
			cout << "[ERROR] There is already a piece in that position!" << endl;
			return false;
		}
		else {
			cout << "[ERROR] You cannot place a piece in the enemy's region" << endl;
			return false;
		}
	}
	else {
		if (right.GetLength() < index) {
			cout << "[ERROR] Index for piece is out of bound!" << endl;
			return false;
		}
		if (board[pos.y][pos.x].GetPiece() == 0 && pos.x != 0) {
			return true;
		}
		else if (board[pos.y][pos.x].GetPiece() != 0) {
			cout << "[ERROR] There is already a piece in that position!" << endl;
			return false;
		}
		else {
			cout << "[ERROR] You cannot place a piece in the enemy's region" << endl;
			return false;
		}
	}
}

ostream& operator << (ostream& os, const Board& board) {

	board.Draw(os);
	os << endl;
	os << "[Left ";
	os << board.left;
	os << "[Right ";
	os << board.right << endl;
	return os;

}



