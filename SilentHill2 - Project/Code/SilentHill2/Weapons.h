#include <iostream>

using namespace std;

class weapon {
public:
	string name = "";
	int damage = 0;
	int delay = 0;
	bool melee = true;
	int ammo = 0;
	int accuracy = 100;
	bool unlocked = false;
};

extern weapon wepArr[7];

extern int healthPotions;

extern int health;
void wepSetup();
