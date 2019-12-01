#include <iostream>
#include <Windows.h>

using namespace std;

void battlePrint() {

}

int optionsArray[2][2] = {
	{ 1, 0 },
	{ 0, 0 }
};

int oRow = 0, oCol = 0;

int playerChoice() {
	int choice = 0;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		optionsArray[oRow][oCol] = 0;
		oRow = oRow;
		oCol = oCol - 1;
		optionsArray[oRow][oCol] = 1;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		optionsArray[oRow][oCol] = 0;
		oRow = oRow;
		oCol = oCol + 1;
		optionsArray[oRow][oCol] = 1;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		optionsArray[oRow][oCol] = 0;
		oRow = oRow - 1;
		oCol = oCol;
		optionsArray[oRow][oCol] = 1;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		optionsArray[oRow][oCol] = 0;
		oRow = oRow + 1;
		oCol = oCol;
		optionsArray[oRow][oCol] = 1;
	}

	if (GetAsyncKeyState('e') & 0x8000) {
		if (oRow == 0 && oCol == 0) {

		}
		if (oRow == 0 && oCol == 1) {

		}
		if (oRow == 1 && oCol == 0) {

		}
		if (oRow == 1 && oCol == 1) {

		}
	}
	return choice;
}

int fight(int pHealth, int pWeapons, int mHealth, int mDamage) {
	int turn = 1;
	if (turn == 1) {
		while (playerChoice == 0) {};
	}
	return pHealth;
}