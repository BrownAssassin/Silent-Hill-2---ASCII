#include <iostream>
#include <Windows.h>
#include "Monsters.h"
#include "Maps.h"
#include "Battle.h"


using namespace std;

monster monArray[100];

int pRange = 5;

void monPrint(int map[50][50], int r, int c) {
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	
	int xc, yr;

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);

	for (int y = 0; y < 50; y++) {
		for (int x = 0; x < 50; x++) {


			xc = x - c;
			yr = y - r;
			xc = abs(xc);
			yr = abs(yr);

			if (xc + yr <= pRange) {
				SetConsoleTextAttribute(color, 7);
				int col = (x + 1) * 3;
				COORD p = { col, y };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
				cout << "\b\b\b";
				if (map[y][x] == 19) {
					SetConsoleTextAttribute(color, 13);
					cout << "[-]";
					SetConsoleTextAttribute(color, 7);
				}
				if (map[y][x] == 18) {
					SetConsoleTextAttribute(color, 13);
					cout << "|+|";
					SetConsoleTextAttribute(color, 7);
				}
				if (map[y][x] >= 14 && map[y][x] <= 17) {
					SetConsoleTextAttribute(color, 14);
					cout << "|x|";
					SetConsoleTextAttribute(color, 7);
				}
				if (map[y][x] >= 9 && map[y][x] <= 13) {
					SetConsoleTextAttribute(color, 14);
					cout << "x--";
					SetConsoleTextAttribute(color, 7);
				}
				if (map[y][x] == 8) {
					SetConsoleTextAttribute(color, 4);
					cout << char(176) << "O" << char(176);
					SetConsoleTextAttribute(color, 7);
				}
				if (map[y][x] >= 4 && map[y][x] < 8) cout << char(176) << "O" << char(176);
				if (map[y][x] == 2) cout << "(J)";
				if (map[y][x] == 1) cout << char(219) << char(219) << char(219);
				if (map[y][x] == 0) cout << "   ";
			}
			if (xc + yr == pRange + 1) {
				SetConsoleTextAttribute(color, 0);
				int col = (x + 1) * 3;
				COORD p = { col, y };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
				cout << "\b\b\b";
				if (map[y][x] == 1) cout << char(219) << char(219) << char(219);
				else cout << "   ";
			}
		}
	}
}

int moveTest(int map[50][50], int row, int col) {
	if (map[row][col] == 2) return 2;
	if (map[row][col] == 0) return 1;
	else return 0;
}

void monster::monMove(int map[50][50], int r, int c, int gTime) {
	int testRow, testCol;
	int distance = sqrt(pow((r - row), 2) + pow((c - col), 2));
	int direction = rand() % 4 + 1;

	if (distance <= range) {
		if (r > row) {
			testRow = row + 1;
		}
		else if (r < row) {
			testRow = row - 1;
		}
		else {
			testRow = row;
		}

		if (c > col) {
			testCol = col + 1;
		}
		else if (c < col) {
			testCol = col - 1;
		}
		else {
			testCol = col;
		}
	}
	else {
		if (direction == 1) {
			testRow = row + 1;
			testCol = col;
		}

		if (direction == 2) {
			testRow = row - 1;
			testCol = col;
		}

		if (direction == 3) {
			testRow = row;
			testCol = col + 1;
		}

		if (direction == 4) {
			testRow = row;
			testCol = col - 1;
		}
	}
	if (moveTest(map, testRow, testCol) == 1) {
		map[row][col] = 0;
		row = testRow;
		col = testCol;
		map[row][col] = value;
		time = gTime;
		monPrint(map, r, c);
	}
	if (moveTest(map, testRow, testCol) == 2) {
		int outcome = fight(health, damage, attackSpeed, value);
		Sleep(500);
		if (outcome == 1) {
			cout << "  _____              __  __   ______      ____   __      __  ______   _____  \n";
			cout << " / ____|     /\\     |  \\/  | |  ____|    / __ \\  \\ \\    / / |  ____| |  __ \\ \n";
			cout << "| |  __     /  \\    | \\  / | | |__      | |  | |  \\ \\  / /  | |__    | |__) |\n";
			cout << "| | |_ |   / /\\ \\   | |\\/| | |  __|     | |  | |   \\ \\/ /   |  __|   |  _  / \n";
			cout << "| |__| |  / ____ \\  | |  | | | |____    | |__| |    \\  /    | |____  | | \\ \\ \n";
			cout << " \\_____| /_/    \\_\\ |_|  |_| |______|    \\____/      \\/     |______| |_|  \\_\\ \n";
			Sleep(1000);
		}
		if (outcome == 2) {
			value = 0;
			map[row][col] = 0;
		}
		if (outcome == 3) delay = gTime + 10;
	}
}

monster dataPass(int x) {
	return monArray[x];
}

string spriteTemp = "hh";
//Monsters are 4-8 for now
void monsterUpdate(int currentMap[50][50]) {
	int numMonsters = 0;
	for (int r = 0; r < 50; r++) {
		for (int c = 0; c < 50; c++) {
			if (currentMap[r][c] >= 4 && currentMap[r][c] <= 8) {
				numMonsters = numMonsters + 1;
				monArray[numMonsters].row = r;
				monArray[numMonsters].col = c;
				monArray[numMonsters].value = currentMap[r][c];

				if (currentMap[r][c] == 4) {
					monArray[numMonsters].health = 60;
					monArray[numMonsters].damage = 10;
					monArray[numMonsters].delay = 1;
					monArray[numMonsters].attackSpeed = 7;
					monArray[numMonsters].range = 7;
					monArray[numMonsters].sprite = spriteTemp;
				}

				if (currentMap[r][c] == 5) {
					monArray[numMonsters].health = 100;
					monArray[numMonsters].damage = 25;
					monArray[numMonsters].delay = 1.2;
					monArray[numMonsters].attackSpeed = 5;
					monArray[numMonsters].range = 12;
					monArray[numMonsters].sprite = spriteTemp;
				}

				if (currentMap[r][c] == 6) {
					monArray[numMonsters].health = 115;
					monArray[numMonsters].damage = 35;
					monArray[numMonsters].delay = 0.8;
					monArray[numMonsters].attackSpeed = 10;
					monArray[numMonsters].range = 7;
					monArray[numMonsters].sprite = spriteTemp;
				}

				if (currentMap[r][c] == 7) {
					monArray[numMonsters].health = 200;
					monArray[numMonsters].damage = 45;
					monArray[numMonsters].delay = 1;
					monArray[numMonsters].attackSpeed = 13;
					monArray[numMonsters].range = 10;
					monArray[numMonsters].sprite = spriteTemp;
				}

				if (currentMap[r][c] == 8) {
					monArray[numMonsters].health = 1000;
					monArray[numMonsters].damage = 80;
					monArray[numMonsters].delay = 2;
					monArray[numMonsters].attackSpeed = 20;
					monArray[numMonsters].range = 80;
					monArray[numMonsters].sprite = spriteTemp;
				}
			}
		}
	}
}