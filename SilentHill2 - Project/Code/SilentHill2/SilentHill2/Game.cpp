#include <iostream>
#include <Windows.h>
#include <cstdio>
#include <ctime>
#include <math.h>
#include "Maps.h"
#include "Monsters.h"
#include "Battle.h"
#include "Weapons.h"

//ARROW KEYS TO MOVE, E TO SELECT AN OPTION DURING A FIGHT, MUST WAIT FOR COOLDOWN BAR AT BOTTOM OF SCREEN FOR EACH ACTION

using namespace std;

int row = 41;
int col = 2;
double globalTime;
double playerTime = 0;

void mainLoop(clock_t start);

void fullscreen()
{
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

void moveCursorTo(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void mapPrinter(int map[50][50], int r, int c) {
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	int xc, yr;
	for (int y = 0; y < 50; y++) {
		for (int x = 0; x < 50; x++) {
			xc = x - c;
			yr = y - r;
			xc = abs(xc);
			yr = abs(yr);
			if (xc + yr <= pRange) {
				SetConsoleTextAttribute(color, 7);
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
					cout << "*" << char(176) << "*";
					SetConsoleTextAttribute(color, 7);
				}
				if (map[y][x] >= 4 && map[y][x] < 8) cout << "*" << char(176) << "*";
				if (map[y][x] == 2) cout << "(J)";
				if (map[y][x] == 1) cout << char(219) << char(219) << char(219);
				if (map[y][x] == 0) cout << "   ";
			}
			if (xc + yr > pRange) {
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
					cout << "*" << char(176) << "*";
					SetConsoleTextAttribute(color, 7);
				}
				if (map[y][x] >= 4 && map[y][x] < 8) cout << "*" << char(176) << "*";
				if (map[y][x] == 2) cout << "(J)";
				if (map[y][x] == 1) cout << char(219) << char(219) << char(219);
				if (map[y][x] == 0) cout << "   ";
			}
			if (xc + yr == pRange+1) {
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
	if (map[row][col] == 19) {
		pRange = pRange + 1;
		map[row][col] = 0;
	}
	if (map[row][col] == 18) {
		healthPotions = healthPotions + 1;
		map[row][col] = 0;
	}
	if (map[row][col] == 17) {
		wepArr[5].ammo = wepArr[5].ammo + 3;
		map[row][col] = 0;
	}
	if (map[row][col] == 16) {
		wepArr[4].ammo = wepArr[4].ammo + 2;
		map[row][col] = 0;
	}
	if (map[row][col] == 15) {
		wepArr[3].ammo = wepArr[3].ammo + 5;
		map[row][col] = 0;
	}
	if (map[row][col] == 14) {
		wepArr[2].ammo = wepArr[2].ammo + 5;
		map[row][col] = 0;
	}
	if (map[row][col] == 13) {
		wepArr[5].unlocked = true;
		map[row][col] = 0;
	}
	if (map[row][col] == 12) {
		wepArr[4].unlocked = true;
		map[row][col] = 0;
	}
	if (map[row][col] == 11) {
		wepArr[3].unlocked = true;
		map[row][col] = 0;
	}
	if (map[row][col] == 10) {
		wepArr[2].unlocked = true;
		map[row][col] = 0;
	}
	if (map[row][col] == 9) {
		wepArr[1].unlocked = true;
		map[row][col] = 0;
	}
	if (map[row][col] >= 4 && map[row][col] <= 8) return 2;
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
	if (moveAttempt && playerMoveTest(map, testRow, testCol) == 2) {
		for (int m = 0; m < 100; m++) {
			if (monArray[m].row == testRow && monArray[m].col == testCol) {
				int outcome = fight(monArray[m].health, monArray[m].damage, monArray[m].attackSpeed, monArray[m].value);
				Sleep(500);
				if (outcome == 1) {
					int x = 20;
					int y = 20;
					moveCursorTo(x, y);
					cout << "  _____              __  __   ______      ____   __      __  ______   _____  ";
					moveCursorTo(x, y+1);
					cout << " / ____|     /\\     |  \\/  | |  ____|    / __ \\  \\ \\    / / |  ____| |  __ \\ ";
					moveCursorTo(x, y+2);
					cout << "| |  __     /  \\    | \\  / | | |__      | |  | |  \\ \\  / /  | |__    | |__) |";
					moveCursorTo(x, y+3);
					cout << "| | |_ |   / /\\ \\   | |\\/| | |  __|     | |  | |   \\ \\/ /   |  __|   |  _  / ";
					moveCursorTo(x, y+4);
					cout << "| |__| |  / ____ \\  | |  | | | |____    | |__| |    \\  /    | |____  | | \\ \\ ";
					moveCursorTo(x, y+5);
					cout << " \\_____| /_/    \\_\\ |_|  |_| |______|    \\____/      \\/     |______| |_|  \\_\\ ";
					Sleep(1000);
					/*
					health = 100;
					for (int x = 1; x < 6; x++) {
						if (x == 1) {
							wepArr[1].name = "Chainsaw";
							wepArr[1].melee = true;
							wepArr[1].damage = 60;
							wepArr[1].accuracy = 40;
							wepArr[1].delay = 8;
							wepArr[1].unlocked = false;
						}
						if (x == 2) {
							wepArr[2].name = "Handgun";
							wepArr[2].melee = false;
							wepArr[2].ammo = 15;
							wepArr[2].accuracy = 75;
							wepArr[2].damage = 25;
							wepArr[2].delay = 3;
							wepArr[2].unlocked = false;
						}
						if (x == 3) {
							wepArr[3].name = "Maria's Revolver";
							wepArr[3].melee = false;
							wepArr[3].ammo = 20;
							wepArr[3].accuracy = 80;
							wepArr[3].damage = 30;
							wepArr[3].delay = 4;
							wepArr[3].unlocked = false;
						}
						if (x == 4) {
							wepArr[4].name = "Shotgun";
							wepArr[4].melee = false;
							wepArr[4].ammo = 2;
							wepArr[4].accuracy = 90;
							wepArr[4].damage = 60;
							wepArr[4].delay = 6;
							wepArr[4].unlocked = false;
						}
						if (x == 5) {
							wepArr[5].name = "Rifle";
							wepArr[5].melee = false;
							wepArr[5].ammo = 7;
							wepArr[5].accuracy = 15;
							wepArr[5].damage = 100;
							wepArr[5].delay = 3;
							wepArr[5].unlocked = false;
						}
						if (x == 6) {
							wepArr[6].name = "Great Knife";
							wepArr[6].melee = true;
							wepArr[6].damage = 120;
							wepArr[6].delay = 10;
							wepArr[6].unlocked = false;
						}
					}
					row = 42;
					col = 2;
					pRange = 5;
					healthPotions = 3;
					std::clock_t newStart;

					newStart = std::clock();

					globalTime = (std::clock() - newStart) / (double)CLOCKS_PER_SEC;
					mainLoop(newStart);
					*/
				}
				if (outcome == 2) {
					monArray[m].value = 0;
					map[testRow][testCol] = 0;
				}
				if (outcome == 3) monArray[m].delay = monArray[m].delay + 10;
			}
		}
	}
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
	bool hasWon = false;
	while (!hasWon && health > 0) {
		hasWon = true;
		globalTime = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		if (globalTime > playerTime + 0.15) charMove(currentMap);
		for (int m = 0; m < 100; m++) {
			if (monArray[m].value > 0) hasWon = false;
			if (globalTime > monArray[m].time + monArray[m].delay && monArray[m].value >= 4) {
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

	wepSetup();


	mainLoop(start);
	return 0;
}