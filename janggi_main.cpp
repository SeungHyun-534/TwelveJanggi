#include "Board.h"
#include <limits>
#include <cctype>
using namespace std;
int main() {
	Board game;
	while (game.IsGameOver()) {
		start:cout << game;
		game.ShowTurn(cout);
		cout << "What do you want to do?" << endl;
		cout << "1. Move piece" << endl;
		cout << "2. Place piece" << endl;
		cout << "3. Quit" << endl;
		string input[3];
		cin >> input[0];
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (input[0] == "1"){
			while (true) {
				cout << game;
				game.ShowTurn(cout);
				cout << "Please enter the position of the piece and the direction to move\n" << "Direction: [up, down, left, right, upleft, upright, downleft, downright]\n" << "ex) A2 right" << endl;
				Position p; Direction d;
				cin >> input[1] >> input[2];
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if (input[1][0] == 'A') p.x = 0;
				else if (input[1][0] == 'B') p.x = 1;
				else if (input[1][0] == 'C') p.x = 2;
				else if (input[1][0] == 'D') p.x = 3;
				else {
					if (!isdigit(input[1][1]) || !isalpha(input[1][0])) {
						cout << "[Error] Incorrect Position. Please check that the position is only a letter followed by number\n" << endl;
						continue;
					}
					else {
						cout << "[Error] Incorrect column letter. Please check that the column is within A and D\n" << endl;
						continue;
					}
				}
				if (input[1][1] == '1') p.y = 0;
				else if (input[1][1] == '2') p.y = 1;
				else if (input[1][1] == '3') p.y = 2;
				else {
					cout << "[Error] Incorrect row number. Please check that the row number is within 1 and 3\n" << endl;
					continue;
				}
				if (input[2] == "up") d = UP;
				else if (input[2] == "down") d = DOWN;
				else if (input[2] == "left") d = LEFT;
				else if (input[2] == "right") d = RIGHT;
				else if (input[2] == "upleft") d = UPLEFT;
				else if (input[2] == "upright") d = UPRIGHT;
				else if (input[2] == "downleft") d = DOWNLEFT;
				else if (input[2] == "downright") d = DOWNRIGHT;
				else {
					cout << "[Error] Incorrect direction. Please check that the direction is one of the eight\n" << endl;
					continue;
				}
				if (game.MovePiece(p, d)) {
					break;
				};
			}
		}
		else if (input[0] == "2" && game.PlayerHasPiece()){
			while (true) {
				cout << game;
				game.ShowTurn(cout);
				cout << "Please enter the index of the piece and the position to place\n";
				cout << "ex) 3 B3" << endl;
				int in; Position p;
				cin >> in >> input[1];
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if (input[1][0] == 'A') p.x = 0;
				else if (input[1][0] == 'B') p.x = 1;
				else if (input[1][0] == 'C') p.x = 2;
				else if (input[1][0] == 'D') p.x = 3;
				else {
					cout << "[Error] Incorrect column letter. Please check that the column is within A and D\n" << endl;
					continue;
				}
				if (input[1][1] == '1') p.y = 0;
				else if (input[1][1] == '2') p.y = 1;
				else if (input[1][1] == '3') p.y = 2;
				else {
					cout << "[Error] Incorrect row number. Please check that the row number is within 1 and 3\n" << endl;
					continue;
				}
				if (game.PlacePiece(in, p)) {
					break;
				}
			}
		}
		else if (input[0] == "2") {
			goto start;
		}
		else if (input[0] == "3") {
			break;
		}
		else {
			cout << "[EORROR} You should input the number between 1 and 3!\n" << endl;
			goto start;
		}
		system("cls");
	}
}