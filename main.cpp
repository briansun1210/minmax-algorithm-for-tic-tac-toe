#include <iostream>
#include <string>
using namespace std;

const int SIZE = 3;

void makeMap(char m[][SIZE]); 
void showMap(char m[][SIZE]);
char checkAns(char recordM[],int r);
char checkChar();
char checkNum();
void updateMap(char m[][SIZE], char c, int r);
int checkWin(char m[][SIZE], int r);
bool replay();
void resetRecordMove(char recordM[]);

int main() {
	char map[SIZE][SIZE];
	char recordMove[9];
	char choose, place = '1';
	int round = 0, win = 0;
	bool ans = 1;

	makeMap(map);
	showMap(map);

	while (ans == 1) {
		cout << "enter the position number: ";
		choose = checkAns(recordMove, round); // check char -> check number -> check record
		system("cls"); //clear the screen

		updateMap(map, choose, round);
		showMap(map);
		win = checkWin(map, round);
		round++;

		if (win == 1 || win == 2) {
			ans = replay();
			if (ans == 1) { //reset everything 
				system("cls");
				makeMap(map);
				showMap(map);
				resetRecordMove(recordMove);
				round = 0;
			}
		}
	}
	
	return 0;
}

void makeMap(char m[][SIZE]) {
	char place = '1';

	for (int j = 0; j < SIZE; j++) {
		for (int i = 0; i < SIZE; i++) {
			m[j][i] = place;
			place++;
		}
	}
}

void showMap(char m[][SIZE]) {
	for (int j = 0; j < SIZE; j++) {
		for (int i = 0; i < SIZE; i++) {
			cout << m[j][i];
		}
		cout << endl;
	}
}

char checkAns(char recordM[], int r) {
	char p;

	p = checkNum();
	recordM[r] = p;
	while (true) {
		for (int i = 0; i < r; i++) {
			if (recordM[i] == p) {
				cout << "someone already place here, find another place: ";
				p = checkNum();
				i = 0; // reset check loop
			}
		}
		break;
	}

	return p;
}

char checkChar() {
	char p;
	cin >> p;
	cin.clear();
	cin.ignore(256, '\n');

	while (p >= 'a' && p <= 'z' || p >= 'A' && p <= 'Z') {
		cout << "pls enter a number: ";
		cin >> p;
		cin.clear();
		cin.ignore(256, '\n');
	}

	return p;
}

char checkNum() {
	char p;

	p = checkChar();

	while (p < '1' || p > '9') {
		cout << "pls enter a number between 1 ~ 9, base on the position you wnat on the map ";
		p = checkChar();
	}

	return p;
}

void updateMap(char m[][SIZE], char c, int r) {
	for (int j = 0; j < SIZE; j++) {
		for (int i = 0; i < SIZE; i++) {
			if (m[j][i] == c) {
				if (r % 2 == 0)
					m[j][i] = 'O';
				else
					m[j][i] = 'X';
			}
		}
	}
}

int checkWin(char m[][SIZE], int r) {
	int win = 0;

	if ((m[0][0] == m[0][1] && m[0][1] == m[0][2]) || (m[1][0] == m[1][1] && m[1][0] == m[1][2]) ||
		(m[2][0] == m[2][1] && m[2][1] == m[2][2]) || (m[0][0] == m[1][0] && m[0][0] == m[2][0]) ||
		(m[0][1] == m[1][1] && m[0][1] == m[2][1]) || (m[0][2] == m[1][2] && m[0][2] == m[2][2]) ||
		(m[0][0] == m[1][1] && m[0][0] == m[2][2]) || (m[0][2] == m[1][1] && m[0][2] == m[2][0]))
		win = 1;
	else if (r == 8) {
		win = 2;
	}

	if (win == 1) {
		if (r % 2 == 0)
			cout << "O win" << endl;
		else
			cout << "X win" << endl;
	}
	else if (win == 2)
		cout << "it's a draw" << endl;

	return win;
}

bool replay() {
	char ans;
	bool newGame = 0;

	cout << "do you want to play again? (type y or n) " << endl;
	cin >> ans;

	if (ans == 'Y' || ans == 'y')
		newGame = 1;

	return newGame;
}

void resetRecordMove(char recordM[]) {
	for (int i = 0; i < sizeof(recordM); i++) {
		recordM[i] = 0;
	}
}