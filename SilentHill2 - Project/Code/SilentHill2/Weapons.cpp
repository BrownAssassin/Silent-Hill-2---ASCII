#include <iostream>
#include "Weapons.h"

using namespace std;

weapon wepArr[7];
int healthPotions = 3;
int health = 100;

void wepSetup() {
	wepArr[0].name = "Rusty Pipe";
	wepArr[0].melee = true;
	wepArr[0].damage = 35;
	wepArr[0].accuracy = 75;
	wepArr[0].delay = 5;
	wepArr[0].unlocked = true;

	wepArr[1].name = "Chainsaw";
	wepArr[1].melee = true;
	wepArr[1].damage = 60;
	wepArr[1].accuracy = 40;
	wepArr[1].delay = 8;

	wepArr[2].name = "Handgun";
	wepArr[2].melee = false;
	wepArr[2].ammo = 15;
	wepArr[2].accuracy = 75;
	wepArr[2].damage = 25;
	wepArr[2].delay = 2;

	wepArr[3].name = "Maria's Revolver";
	wepArr[3].melee = false;
	wepArr[3].ammo = 20;
	wepArr[3].accuracy = 80;
	wepArr[3].damage = 35;
	wepArr[3].delay = 3;

	wepArr[4].name = "Shotgun";
	wepArr[4].melee = false;
	wepArr[4].ammo = 4;
	wepArr[4].accuracy = 90;
	wepArr[4].damage = 60;
	wepArr[4].delay = 6;

	wepArr[5].name = "Rifle";
	wepArr[5].melee = false;
	wepArr[5].ammo = 7;
	wepArr[5].accuracy = 15;
	wepArr[5].damage = 100;
	wepArr[5].delay = 3;

	wepArr[6].name = "Great Knife";
	wepArr[6].melee = true;
	wepArr[6].damage = 120;
	wepArr[6].delay = 10;

}