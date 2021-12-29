#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

char field[10];

void clearConsole() {
	system("cls");
}

void resetField() {
	for (int i = 0; i < 10; i++) {
		field[i] = ' ';
	}
}

char keyInput(bool x) {
	while (true) {
		cout << "\n\nInput: ";
		char input = ' ';
		cin >> input;
		int inputNumber = input - '0';
		if (inputNumber > 9 || inputNumber < 1) {
			if (input == 'q') {
				return input;
			}
			else {
				cout << "\nInvalid Input!";
			}
		}
		else if (field[inputNumber] != ' ') {
			cout << "\nThis field is already used";
		}
		else {
			if (x) field[inputNumber] = 'X';
			else field[inputNumber] = 'O';

			return input;
		}
	}
}

bool checkWin(char sign) {
	if (field[1] == sign) {
		if (field[4] == sign && field[7] == sign) return true;
		if (field[2] == sign && field[3] == sign) return true;
		if (field[5] == sign && field[9] == sign) return true;
	} 
	if (field[2] == sign && field[5] == sign && field[8] == sign) return true;
	if (field[4] == sign && field[5] == sign && field[6] == sign) return true;
	if (field[9] == sign && field[7] == sign && field[8] == sign) return true;
	if (field[3] == sign) {
		if (field[6] == sign && field[9] == sign) return true;
		if (field[5] == sign && field[7] == sign) return true;
	} 
	return false;
}

bool checkFull() {
	for (int i = 1; i <= 9; i++) {
		if (field[i] == ' ') return false;
	}
	return true;
}

void AI(int difficulty) {
	if (checkFull()) return;
	srand(time(nullptr));
	
	//EASY
	if (difficulty == 1) {
		int check = rand() % 3;

		//Check if AI can win in 67% of cases
		if (check != 1) {
			for (int i = 1; i < 10; i++) {
				if (field[i] == ' ') {
					field[i] = 'O';

					if (checkWin('O')) return;
					else field[i] = ' ';
				}
			}
		}
		//Check if Player can win and stop it in 67% of cases
		else if (check != 2) {
			for (int i = 1; i < 10; i++) {
				if (field[i] == ' ') {
					field[i] = 'X';

					if (checkWin('X')) {
						field[i] = 'O';
						return;
					}
					else field[i] = ' ';
				}
			}
		}
		//Select random field
		while (true) {
			int i = rand() % 9 + 1;
			if (field[i] == ' ') {
				field[i] = 'O';
				return;
			}
		}
	}


	//MEDIUM
	else if (difficulty == 2) {
		int check = rand() % 5 + 1;

		//Check if AI can win in 80% of cases
		if (check != 3) {
			for (int i = 1; i < 10; i++) {
				if (field[i] == ' ') {
					field[i] = 'O';

					if (checkWin('O')) return;
					else field[i] = ' ';
				}
			}
		}
		//Check if Player can win and stop it in 80% of cases
		else if(check != 2) {
			for (int i = 1; i < 10; i++) {
				if (field[i] == ' ') {
					field[i] = 'X';

					if (checkWin('X')) {
						field[i] = 'O';
						return;
					}
					else field[i] = ' ';
				}
			}
		}
		//Select random field
		while (true) {
			int i = rand() % 9 + 1;
			if (field[i] == ' ') {
				field[i] = '0';
				return;
			}
		}
	}
	//HARD
	else if (difficulty == 3) {
		//Check if AI can win
		for (int i = 1; i < 10; i++) {
			if (field[i] == ' ') {
				field[i] = 'O';
				
				if (checkWin('O')) return;
				else field[i] = ' ';
			}
		}
		//Check if Player can win and stop it
		for (int i = 1; i < 10; i++) {
			if (field[i] == ' ') {
				field[i] = 'X';
				
				if (checkWin('X')) {
					field[i] = 'O';
					return;
				} else field[i] = ' ';
			}
		}
		//Set to field in the middle with a chance when it is still free
		int middle = rand() % 4;
		if (field[5] == ' ' && middle != 1) {
			field[5] = 'O';
			return;
		}
		//Select random field
		while (true) {
			int i = rand() % 9 + 1;
			if (field[i] == ' ') {
				field[i] = '0';
				return;
			}
		}
	}
	else return;
}

void drawField() {
	clearConsole();
	cout << "\n\n\n"
		<< "     " << field[1] << "  | " << field[2] << " | " << field[3] << endl
		<< "     ---|---|---" << endl
		<< "     " << field[4] << "  | " << field[5] << " | " << field[6] << endl
		<< "     ---|---|---" << endl
		<< "     " << field[7] << "  | " << field[8] << " | " << field[9] << endl;
}

void singleplayer() {
	string playername;
	
	cout << "\nPlayer Name: ";
	cin >> playername;

	clearConsole();
	char input = ' ';
	int difficulty = 0;
	cout << "\n\n\nDIFFICULTY\n\n\n1: Easy\n\n2: Medium\n\n3: Hard\n\n";
	cout << "\n\n\nInput: ";
	cin >> input;
	switch (input) {
		case '1': difficulty = 1; break;
		case '2': difficulty = 2; break;
		case '3': difficulty = 3; break;
		case 'q': return; break;
		default: cout << "\nInvalid Input!"; singleplayer(); break;
	}

	while (true) {
		drawField();
		if (checkWin('O')) {
			cout << "\nComputer has won!\n\n";
			system("pause");
			return;
		}
		if (checkFull()) {
			cout << "\nTie!\n\n";
			system("pause");
			return;
		}
		input = keyInput(true);
		drawField();
		if (input == 'q') return;
		if (checkWin('X')) {
			cout << "\n" << playername <<" has won!!!\n\n";
			system("pause");
			return;
		}
		AI(difficulty);
	}
}

void multiplayer() {
	
	string namePlayer1;
	string namePlayer2;
	char input = ' ';
	bool player1Turn = true;
	
	cout << "\n\n\nPlayer1 Name: ";
	cin >> namePlayer1;
	cout << "\n\nPlayer2 Name: ";
	cin >> namePlayer2;

	while (true) {
		drawField();
		if (checkWin('X')) {
			cout << "\n" << namePlayer1 << " has won!\n\n";
			system("pause");
			return;
		}
		else if (checkWin('O')) {
			cout << "\n" << namePlayer2 << " has won!\n\n";
			system("pause");
			return;
		}

		if (checkFull()) {
			cout << "Tie!\n\n";
			system("pause");
			return;
		}
		input = keyInput(player1Turn);
		if (input == 'q') return;
		player1Turn = !player1Turn;
	}
}

void help() {
	clearConsole();
	cout << "\n\n\nHelp\n\nSingleplayer: In Singleplayermode you play against the Computer\n\nMultiplayer:\nIn Multiplayermode you play against your neighbour.\n\n\n";
	system("pause");
	return;
}

void menu() {
	while (true) {
		resetField();
		drawField();
		char inputmenu;
		cout << "\n\n"
			<< "MENU\n\n"
			<< "1: Singleplayer\n"
			<< "2: Multiplayer\n"
			<< "3: Help\n"
			<< "4: Quit\n\n\n"
			<< "Input: ";
		cin >> inputmenu;

		if (inputmenu == '1') singleplayer();
		else if (inputmenu == '2') multiplayer();
		else if (inputmenu == '3') help();
		else if (inputmenu == '4' || inputmenu == 'q') return;
		else {
			clearConsole();
			cout << "Invalid Input!";
		}
	}
}



int main() {
	menu();
	return 0;
}