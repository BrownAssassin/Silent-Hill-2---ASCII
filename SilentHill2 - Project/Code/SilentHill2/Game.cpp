#include <iostream>
#include <Windows.h>
#include <chrono>
#include "Maps.h"
#include <math.h>
using namespace std;

int row = 1;
int col = 1;

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
	int range = 2;
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

void charMove(int map[50][50]) {



	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		if (map[row][col - 1] == 0) {
			map[row][col] = 0;
			movePrint(map, row, col);
			col = col - 1;
			map[row][col] = 2;
			movePrint(map, row, col);
		}
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		if (map[row][col + 1] == 0) {
			map[row][col] = 0;
			movePrint(map, row, col);
			col = col + 1;
			map[row][col] = 2;
			movePrint(map, row, col);
		}
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		if (map[row - 1][col] == 0) {
			map[row][col] = 0;
			movePrint(map, row, col);
			row = row - 1;
			map[row][col] = 2;
			movePrint(map, row, col);
		}
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		if (map[row + 1][col] == 0) {
			map[row][col] = 0;
			movePrint(map, row, col);
			row = row + 1;
			map[row][col] = 2;
			movePrint(map, row, col);
		}
	}
	Sleep(100);
}

void moveCursorTo(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void mainLoop() {
	int currentMap[50][50];
	for (int r = 0; r < 50; r++) {
		for (int c = 0; c < 50; c++) {
			currentMap[r][c] = townLogic[r][c];
		}
	}
	mapPrinter(currentMap, row, col);
	while (true) {
		charMove(currentMap);
	}
}

int main() {
	fullscreen();
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	mainLoop();
	return 0;
}