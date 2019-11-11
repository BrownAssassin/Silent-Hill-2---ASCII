#include <iostream>
#include <Windows.h>
#include "Maps.h"
using namespace std;

void mapPrinter(int map[25][25]) {
	for (int r = 0; r < 25; r++) {
		for (int c = 0; c < 25; c++) {
			if (map[r][c] == 2) cout << "(J)";
			if (map[r][c] == 1) cout << char(219) << char(219) << char(219);
			if (map[r][c] == 0) cout << "   ";
		}
		cout << endl;
	}
}

void charMove(int map[25][25], int row, int col) {
	if (GetAsyncKeyState(!VK_LEFT) & 0x8000) {
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			if (map[row][col - 1] == 0) {
				col = col - 1;
			}
		}
	}
	//if (GetAsyncKeyState(!VK_RIGHT) & 0x8000) {
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			if (map[row][col + 1] == 0) {
				col = col + 1;
			}
		}
	//}
	if (GetAsyncKeyState(!VK_UP) & 0x8000) {
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			if (map[row - 1][col] == 0) {
				row = row - 1;
			}
		}
	}
	if (GetAsyncKeyState(!VK_DOWN) & 0x8000) {
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if (map[row + 1][col] == 0) {
				row = row + 1;
			}
		}
	}
	map[row][col] = 2;
}

void moveCursorTo(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void mainLoop() {
	int currentMap[25][25];
	for (int r = 0; r < 25; r++) {
		for (int c = 0; c < 25; c++) {
			currentMap[r][c] = townLogic[r][c];
		}
	}
	while (true) {
		charMove(currentMap, 1, 1);
		system("cls");
		mapPrinter(currentMap);
	}
}

int main() {
	mainLoop();
	return 0;
}