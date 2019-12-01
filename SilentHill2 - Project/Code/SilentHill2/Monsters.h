#include <iostream>

using namespace std;

void monsterUpdate(int map[50][50]);

class monster {
public:
	string sprite = "";
	int value = -1;
	int health = 0;
	int damage = 0;
	int row = 0;
	int col = 0;
	int delay = 0;
	int range = 0;
	int time = 0;
	void monMove(int map[50][50], int r, int c, int gTime);
};

monster dataPass(int x);

extern monster monArray[100];
