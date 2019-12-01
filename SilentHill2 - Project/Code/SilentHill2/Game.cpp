#include <iostream>
#include <Windows.h>
#include <cstdio>
#include <ctime>
#include <math.h>
#include "Maps.h"
#include "Monsters.h"

using namespace std;

int row = 41;
int col = 2;
double globalTime;
double playerTime = 0;

void fullscreen()
{
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

void mapPrinter(int map[50][50], int r, int c) {
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	int range = 4;
	int xc, yr;
	for (int y = 0; y < 50; y++) {
		for (int x = 0; x < 50; x++) {
			xc = x - c;
			yr = y - r;
			xc = abs(xc);
			yr = abs(yr);
			if (xc + yr <= range) {
				SetConsoleTextAttribute(color, 7);
				if (map[y][x] == 8) cout << "888";
				if (map[y][x] == 7) cout << "777";
				if (map[y][x] == 6) cout << "666";
				if (map[y][x] == 5) cout << "555";
				if (map[y][x] == 4) cout << "444";
				if (map[y][x] == 3) cout << "*" << char(176) << "*";
				if (map[y][x] == 2) cout << "(J)";
				if (map[y][x] == 1) cout << char(219) << char(219) << char(219);
				if (map[y][x] == 0) cout << "   ";
			}
			if (xc + yr > range) {
				SetConsoleTextAttribute(color, 0);
				if (map[y][x] == 1) cout << char(219) << char(219) << char(219);
				else cout << "   ";
			}
		}
		cout << endl;
	}
}



void movePrint(int map[50][50], int r, int c) {
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	int range = 4;
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

			if (xc + yr <= range) {
				SetConsoleTextAttribute(color, 7);
				int col = (x + 1) * 3;
				COORD p = { col, y };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
				cout << "\b\b\b";
				if (map[y][x] == 8) cout << "888";
				if (map[y][x] == 7) cout << "777";
				if (map[y][x] == 6) cout << "666";
				if (map[y][x] == 5) cout << "555";
				if (map[y][x] == 4) cout << "444";
				if (map[y][x] == 3) cout << "*" << char(176) << "*";
				if (map[y][x] == 2) cout << "(J)";
				if (map[y][x] == 1) cout << char(219) << char(219) << char(219);
				if (map[y][x] == 0) cout << "   ";
			}
			if (xc + yr == range+1) {
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

int playerMoveTest(int map[50][50], int row, int col) {
	if (map[row][col] == 2) return 2;
	if (map[row][col] == 0) return 1;
	else return 0;
}

void charMove(int map[50][50]) {
	int testRow, testCol;
	bool moveAttempt = false;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		testRow = row;
		testCol = col - 1;
		moveAttempt = true;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		testRow = row;
		testCol = col + 1;
		moveAttempt = true;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		testRow = row - 1;
		testCol = col;
		moveAttempt = true;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		testRow = row + 1;
		testCol = col;
		moveAttempt = true;
	}
	if (moveAttempt && playerMoveTest(map, testRow, testCol) == 1) {
		map[row][col] = 0;
		movePrint(map, row, col);
		row = testRow;
		col = testCol;
		map[row][col] = 2;
		movePrint(map, row, col);
		playerTime = globalTime;
	}
}

void moveCursorTo(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void mainLoop(clock_t start) {
	int currentMap[50][50];
	for (int r = 0; r < 50; r++) {
		for (int c = 0; c < 50; c++) {
			currentMap[r][c] = townReturn(r, c);
		}
	}
	mapPrinter(currentMap, row, col);
	monsterUpdate(currentMap);
	while (true) {
		globalTime = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		if (globalTime > playerTime + 0.15) charMove(currentMap);
		for (int m = 0; m < 100; m++) {
			if (globalTime > monArray[m].time + monArray[m].delay) {
				monArray[m].monMove(currentMap, row, col, globalTime);
			}
		}
	}
}

int main() {
	fullscreen();
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	std::clock_t start;

	start = std::clock();

	globalTime = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	mainLoop(start);
	return 0;
}