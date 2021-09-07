#include <iostream>
#include <Windows.h>
#include <cstdio>
#include <ctime>
#include "Battle.h"
#include "Weapons.h"

using namespace std;

double fightTime, playerF, playerT, monsterT;
bool isFighting;
int mHealth, mDamage, mDelay;
int currentDelay;
bool firstMove;

void moveCursor(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void battlePrint(int value) {
	system("cls");
	moveCursor(0, 6);
	if (value == 4) {
		cout << "                               &&&&&&&&&&%%%%%     " << endl;
		cout << "                            #&&&&&&&&&&&&&&%%%%%    " << endl;
		cout << "                            #&#&&&&&&&&&&&&&&((      " << endl;
		cout << "                            #&#&&&&&&&&&&&&&&&%%%     " << endl;
		cout << "                            (%%##&&&&&&&&**%&&&&&&&    " << endl;
		cout << "                          %%&&#&&&&&&&&***,,**%&&       " << endl;
		cout << "                          %%(//..,,,&&(**..,,,//%&&      " << endl;
		cout << "                          &&(////###&&(//..,,,**          " << endl;
		cout << "                          &&(//##%%%&&(//..,,,**           " << endl;
		cout << "                       ,**%%&&#%%%%%&&&&&(**&&             " << endl;
		cout << "                       (%%*****&&&&&&&&&&&&%%%&&*,,         " << endl;
		cout << "                       .,,&&(****#%%&&%%%*****&##**         " << endl;
		cout << "                     ,,*//%%#####(//((///**(##**///          " << endl;
		cout << "                     **///%%%%%%%/*********#%%,,///           " << endl;
		cout << "                     &##,,#%%&&%%%%%%%%&&(//**#&&              " << endl;
		cout << "                     &&&&&**(##,,///,,(##,,(##&&&&&             " << endl;
		cout << "                     &&&&&&&(//**(##**///**#&&&&&&&              " << endl;
		cout << "                     &&&&&&&&%%##%%%##%%%##(//((%&&               " << endl;
		cout << "                     &&&&&&&&&&&&&&&&&&&&&&/****%&&                " << endl;
		cout << "                     ##&&#%%%*****&&&&&&&(**&&                      " << endl;
		cout << "                  /##&##&&(****#%%&&&&&&&&&&&&                       " << endl;
		cout << "                  #&&%%&&&     **#%%&&   &&(**&&                      " << endl;
		cout << "                  #&&%%&&&     %%%%%&&   ((/**&&                       " << endl;
		cout << "                  #&&%%&&&     &&%%%&&   *****&&                       " << endl;
		cout << "                  #&&&&          #&&&&   &&&&&&&&&&                    " << endl;
		cout << "                  (%%&&          #&&%%     #&&&&&&&                    " << endl;
		cout << "                &&%%%&&          (%%%%     #&&&&&&&                    " << endl;
		cout << "                &&(//&&          *//&&     #&&&&&&#                    " << endl;
		cout << "                &&(**&&          ,**&&     #&&&&&&&&&                  " << endl;
		cout << "             #&&&&&&&            ,**&&        %%&&&&&                  " << endl;
		cout << "             #&&&&&&&            ,**&&        %%%%%&&                  " << endl;
		cout << "           &&%%%&&&&&          &&/****          (%%##&&&               " << endl;
		cout << "           &&(//&&             &&%%%**          /##&&%##               " << endl;
		cout << "           &&(**&&             &&&&&**          /##&##                 " << endl;
		cout << "           **%&&&&             ##%&#             ##%&&&&               " << endl;
		cout << "        ,****%&&&&             ##%&#             &&(**%%&&&            " << endl;
		cout << "      &&(**&&&&&&&             &&&&&&&             &&&&&*****&&        " << endl;
		cout << " #####&&%%%&&&&&            /##&&&&&&##            #&####%%###         " << endl;
		cout << " &&&&&&&&&&&&&&&            #&&&&&&&&&&&&            #&&%%%%%%%&&&     " << endl;
	}
	if (value == 5) {
		cout << "         @@   @@@@@@@@@@@@#                                                    " << endl;
		cout << "    %@@@@@@@@@@&&&&&&&@@@@@                                                    " << endl;
		cout << "  %%@@@&&&&&&&&&&&&%//&&&@@##(                                                 " << endl;
		cout << "  @@@@@&&&&&&&&&&&&%**&&&@@@@#                                                 " << endl;
		cout << "  @@%%%%%#((&&&&&**/&&&&&&&@@#                                  %@@@@@@@%%     " << endl;
		cout << "  @@/****(((%%&&&&&&&&&&&&&%%%%%                              @@@@@&&&&&%%%%%  " << endl;
		cout << "  @@/**%%%%%&&&&&&&&&&&&&@@@@@@@@@@@@@@                    %@@@@&&&&&&&&%%%%%  " << endl;
		cout << "  @@%##&&&&&&&&&&&&&&&@@@@@&&&&&//(&&@@%####          (##%%@@@&&&&&&&&&&%%     " << endl;
		cout << "  @@&%%&&&&&&&&&&&&&&&@@@@@&&&&&**/&&@@@@@@@          #@@@@@@@&&&&&&&&&&%%     " << endl;
		cout << "  @@&&&&&&&&&&&&&&&&&&@@@&&&&%**&&&((&&&&&&&&&&     %%&@@&&&&&&&&&&&&&&&%%     " << endl;
		cout << "  @@&&&&&&&&&&&&&&&&&&@@@&&&&&&&**/((&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&%%     " << endl;
		cout << "  @@&&&&&&&&&&&((&&&&&@@@&&*****&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&%%     " << endl;
		cout << "  @@&&&&&&&&%%%##&&&&&@@@&&***//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&%%     " << endl;
		cout << "  &&&&&&&&&&**/&&&&&&&@@@&&**/&&&&&&&&&&&&((&&&&&&&&&&&&&&&&%%%%#((&&&&&%%     " << endl;
		cout << "    #&&&&&&&**/&&&&&@@@@&((&&&&&&&&&&&&&&&**%&&&&&&&&&&&&%%%%%**(((&&&%%       " << endl;
		cout << "  &&&&&&&/**&&&&&&&&&&&&&&&&&&&&*****&&&&&%%/**&&&&&&&&&&((/****%&&&&&%%       " << endl;
		cout << "    #&&&((&&&&&&&&&&&&&&&&&%**((/****%&&%%/**((%%%%%&&&&&/**%%&&&&&&%%       " << endl;
		cout << "    #&&&##%%%%%&&&&&&&&&&&&%**///****%&&&&(//##%%%&&&&&&&(//%%&&&&&%%%       " << endl;
		cout << "    #&&&&%%%*****%%%&&&&&&&&&%*****((**%&&&&&&&%%%%%&&&&&&&%%%&&&&&%%%%%      " << endl;
		cout << "    #&&&&&%%**/%%&&&&&&&&&&&&%*********%&&&&&&&%%&&&&&&&&&&&&&&&&&&%%          " << endl;
		cout << "    #&&&&&&&%%&&&&&&&&&&&&&&&%//*****&&&&&&&&%%%%&&&&&&&&&&&&&&&&%%%%          " << endl;
		cout << "    #&&%%%%%&&&&&&&&&&&&&&&&&%////(&&&&&&&&&&%%&&&&&&&&&&&&&&&%%%%%            " << endl;
		cout << "    &&&%%%%%&&&&&&&&&&&&&&&&&%//((#&&&&&&&&&%%%&&&&&&&&&&&&&&&%%%%%            " << endl;
		cout << "         (%%%%%%%%%%%%&&&&&&&%//&&&&&&&&&&%%%%%&&&&&&&&&&&&%%%%%               " << endl;
		cout << "                    %%&&&&&&&&&&//(&&%%%%%%%&&&&&&&&&&&&&%%                    " << endl;
		cout << "                      %%&&&&&%//&&&%%%%&&&&((&&%%%((&&&%%                    " << endl;
		cout << "                      %%%%%&&&&&&&&%%&&&&&&&&&&((/****#%%%%                   " << endl;
		cout << "               .......%%%%%&&&&&&&&%%&&&&&&&&&#(////#%%%%                    " << endl;
		cout << "               ##########%%%%%&&%%%%%&&&&&&&&&&&&&%%%%%%%%%                   " << endl;
		cout << "            #####          %%%%%%%%%%%%&&&&&&&&&&/**&&&&&%%                    " << endl;
		cout << "           ##/  ##########          %%%%%%%&&&&&&&&**%&#                    " << endl;
		cout << "            #######/       #####       (%%%%%%%&&&&&%%%%%#####               " << endl;
		cout << "         ...########       #####...    %%%%%%%%&&&&&%%%%%#####                " << endl;
		cout << "         /##%%%%%               ##/       %%%%%%%%%%%%%%%%%###                 " << endl;
		cout << "       ##      %%%%%&&&&&%%%%%%%            /##%%%%%%%%%%%%#####               " << endl;
		cout << "         /##   ##############/                 ###%%%%%%%#######               " << endl;
		cout << "            ##/               ##                 /#########                    " << endl;
		cout << "         ...###.....,,.......,##                 ##########                    " << endl;
		cout << "         /##   %%%%%&&%%%%%%%(                           " << endl;
	}
	if (value == 6) {
		cout << "         ,**                                                                   " << endl;
		cout << "          /##,,                                                ,,,,,,,,,,,,     " << endl;
		cout << "          (%%**                                                ************     " << endl;
		cout << "   %%        %%                                             ,****/((**********  " << endl;
		cout << "   %%%%%  (%%     %%                                        ,**((*************  " << endl;
		cout << "   %%%%%  (%%  (%%%%                                      *****((***************" << endl;
		cout << "     *//,,(%%((#%%                      /##((###          **********************" << endl;
		cout << "     ,****#%%%%%%%                      #&&%%&&&          **********************" << endl;
		cout << "        %%/**%%                       &&&&&//%&&&&        **/((*****************" << endl;
		cout << "          ,**%%%%%                 #&&&&&&&&&&&&//%&&     **********************" << endl;
		cout << "          (%%%%                  (((((,,,,,,,,,,,,%&&&&     ,*****************  " << endl;
		cout << "        ((#%%%%               *//((/**,,,,,((*,,%%&&&%%        ************     " << endl;
		cout << "        %%%%%%%               /((((*,,,,,,,((*,,&&&&#        ************     " << endl;
		cout << "          (%%                 /((%%&&&&&/,,,,,,,&&&&####       *///////       " << endl;
		cout << "     (%%%%%%%               &((((#%%&&&&&&&&&&&&&&&&&&&&          //          " << endl;
		cout << "     (%%%%                  **%&&((%&&&&&&&&&&&&&&&&&((/****        /////      " << endl;
		cout << "   ,,(%%                    **(((%%&&&&&&&######(((//***((        /////       " << endl;
		cout << "   **#%%                    **///&&&&&&&&&######/////***##        /////       " << endl;
		cout << " ****                    *(((((##//%&&&#####%%#####&&&&&&&     *///////       " << endl;
		cout << " **%%                    *((&&&&&&&&&&&&&&&%%&&&&&&&&(((((&&     *///////      " << endl;
		cout << " %%%%%%%               %%&&&&&&&&&&&&&&&@@@@@&&&&((((%&&&&     *////          " << endl;
		cout << "   %%%%%  *((          %%&&&&((&&&&&,,&@@@@/,,&((((%&&          //*****     " << endl;
		cout << "   %%%%%  (%%          %%&&&&&(((&&&&&  %@@@@,  &&(((((%&&          ///////  " << endl;
		cout << "     ,****#%%%%/****#%%%%&&&((%&&&&,              #&&((%&&&&          *////   " << endl;
		cout << "     (%%%%/****#%%**#%%%%   &&&&&@@@@@          @@@@@&&&&&&&   /////////////// " << endl;
		cout << "          (%%%%%%%          &&&&&&&,              ,**&&&&&((///////////////     " << endl;
		cout << "                            #####&##  (%%%%.  ,,#%%&&&&&((   /////            " << endl;
		cout << "                            (((((&&&&&  %@@@@,  **%&&&&&&&((   /////           " << endl;
		cout << "                           &&&&&(((((&&@@@@@(****%&&&&&&&((////////            " << endl;
		cout << "                            &&&&&((%&&&&&&&&&&&&**%&&&&&&&//////////            " << endl;
		cout << "                            %%%%%&&&&&&&(//&&/****%&&&&&&&/////                 " << endl;
		cout << "                            &&%%%%%%%%&&%%%&&/**%%&&####                      " << endl;
		cout << "                            &&%%%%%%%%&&&&&&&/**&&&&&(((((                     " << endl;
		cout << "                            //######%%&&   ##&&&&((((%&&                      " << endl;
		cout << "                            //%&&&&&&#     /####(((&&&&&                      " << endl;
		cout << "                              /####&&&          &&&&&&&                        " << endl;
	}
	if (value == 7) {
		cout << "            ((((((((((((                                               " << endl;
		cout << "         /((%%%%%%%%%%((                                                " << endl;
		cout << "    /((((#%%%%%%%%%%%%((                                                 " << endl;
		cout << "  //###//#%%%%%%%%%%%%((                                                  " << endl;
		cout << "  ((#%%**#%%%%%%%%%%%%((                                                   " << endl;
		cout << "((%%/**,,***%%%%%%%%%%((                                                    " << endl;
		cout << "((%%/**  ,,,**#%%%%%%%((                                                     " << endl;
		cout << "((%%%%%,,***%%%%%%%#(((((((                                                   " << endl;
		cout << "((%%%%%**(##%%%%%########((//                                                  " << endl;
		cout << "((%%%%%**#%%%%%%%((#%%%%#((((                                                  " << endl;
		cout << "((%%%%%**#%%%%#((((#%%%%%%%(((((                                               " << endl;
		cout << "((%%%%%%%%%%%%%%%%%%%%%%%%%%%#((((                                             " << endl;
		cout << "((%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#((((                                        " << endl;
		cout << "((%%%%%%%%%%%%(////&@@@@(//%%%%%%%###((///                                     " << endl;
		cout << "((%%%%%%%%%%%%/****&@@@@(**%%%%%%%%%%(((((                                     " << endl;
		cout << "((%%%%%%%%%%%%/**@@@@@@@(**@@%%%%%%%%%%%%%((                                   " << endl;
		cout << "  ((#%%%%%%%%%@@@@@,    %@@@@%%%%%%%%%%#((       /((((((((((((((               " << endl;
		cout << "  ((#%%%%%%%%%@@@@@,    %@@*****%%%%%%%#((  /((((#%%%%%%%%%#((                 " << endl;
		cout << "    /##%%%%%%%%%%((#%%%%(((&&/**%%%%%##(((//######%%%%%%%##(((                 " << endl;
		cout << "    /((%%%%%%%%%%**&@@@@(**@@(**%%%%%(((((((#%%%%%%%%%%%%(((((                 " << endl;
		cout << "       ((#%%%%%%%%%%%%@@@@@*****%%#((%%%%%%%%%%%%%%%%%%%%((                    " << endl;
		cout << "       (((((%%%%%%%%%%%%%%%**#%%%%%%%%%%%%%%%%%*****%%%%%((                    " << endl;
		cout << "        /((((#%%%%%%%%%%%%**#%%%%%%%%%%%%%%/**,,(%%%%#((((                    " << endl;
		cout << "              /##%%%%%%%%%%##///%%%%%%%%%%%%/**  ***%%#((                      " << endl;
		cout << "              /((%%%%%%%%%%%%/**%%%%%%%%%%%%*,,  ,,,%%#((                      " << endl;
		cout << "              /((((#%%%%%%%**#%%%%%%%%%%%%%%%%%,,***((                         " << endl;
		cout << "                  /((%%%%%%%%%%%%%%%%%%%%%%%%%**(((                           " << endl;
		cout << "                      (((((%%%%%%%%%%%%%%%%%%%%(((((                           " << endl;
		cout << "                           #####%%%%%%%%%%%%###((                              " << endl;
		cout << "                           (((((%%%%%%%%%%%%#((((                              " << endl;
		cout << "                             /((((#%%%%#((((                                   " << endl;
		cout << "                                (((((((                                        " << endl;
	}
	if (value == 8) {
		cout << "                                  .,,                                         " << endl;
		cout << "                                  .,,                                          " << endl;
		cout << "                                ..,,,..                                        " << endl;
		cout << "                                ,,,,,,,                                        " << endl;
		cout << "                                ,,,,,,,,,,                                     " << endl;
		cout << "                             .,,,,,,,,,,,,                                     " << endl;
		cout << "                           ,,,,,,,,,,,,,,,,,                                   " << endl;
		cout << "                        ...,,,,,,,,,,,,,,,,,                                   " << endl;
		cout << "                        .,,,,,,,,,,,,,,,,,,,                                   " << endl;
		cout << "                        .,,,,,,,,,,,,,,,,,,,,,,                                " << endl;
		cout << "                           ,,,,,,,,,,,,,,,,,,,,,,                              " << endl;
		cout << "                           ##*,,,,,,,,,,,,,,,,,,,                              " << endl;
		cout << "                        *//##(((,,,,,,,,,,,,,,,,,,..                           " << endl;
		cout << "                        /#######,,,,,,,,,,,,,,,,,,,,                           " << endl;
		cout << "                        /############,,,,,,,,,,,,,,,                           " << endl;
		cout << "                      ####################  .,,,,,,,,,                         " << endl;
		cout << "                      ######################     .,,,,                         " << endl;
		cout << "                   *//#####  /##############                                   " << endl;
		cout << "                   /#######  /##############                                   " << endl;
		cout << "                   /####     /#################                                " << endl;
		cout << "                   /####     (%%#################                              " << endl;
		cout << "                   /####     (%%%%%%%%%%%%%%########                           " << endl;
		cout << "                   /####     (%%%%%%%%%%%%%%   #####//                         " << endl;
		cout << "                   /####     (%%%%%%%%%%%%%%   #######                         " << endl;
		cout << "                   /####*,,,,(%%%%%%%%%%%%%%%%%  /####                         " << endl;
		cout << "                      ##*,,,,,,,,,(%%%%%%%%%%%%                                " << endl;
		cout << "                      ,,,,,,,,,,,,,,,%%%%%%%%%%                                " << endl;
		cout << "                           ,,,,,,,,,,**#%%%%%%%((                              " << endl;
		cout << "                           ,,,,,,,,,,,,(%%%%%%%%%                              " << endl;
		cout << "                           ##*,,,,,,,,,,,,%%%%%%%                              " << endl;
		cout << "                           #####  .,,,,,,,,,(%%%%                              " << endl;
		cout << "                           ##        ,,,,,,,,,,%%                              " << endl;
		cout << "                        *//##          ,,,,,,,,**                              " << endl;
		cout << "                        /####          .,,,,,,,,,                              " << endl;
		cout << "                        /####             ##*,,,,,,,,,                         " << endl;
		cout << "                        /####             #####,,,,,,,,,,                      " << endl;
		cout << "                      #######             #####  .,,,,,,,,,                    " << endl;
		cout << "                                                    ,,,,,,,,..                 " << endl;
		cout << "                                                         ,,,,,,      " << endl;
	}

	int x = 120;
	int y = 1;

	moveCursor(x, y+5);
	cout << "	 ______   _____    _____   _    _   _______ ";
	moveCursor(x, y+6);
	cout << "	| ____|  |_   _|  / ____| | |  | | |__   __|";
	moveCursor(x, y+7);
	cout << "	| |__      | |   | |  __  | |__| |    | |   ";
	moveCursor(x, y+8);
	cout << "	|  __|     | |   | | |_ | |  __  |    | |   ";
	moveCursor(x, y+9);
	cout << "	| |       _| |_  | |__| | | |  | |    | |   ";
	moveCursor(x, y+10);
	cout << "	|_|      |_____|  \\_____| |_|  |_|    |_|  ";
	moveCursor(x, y + 15);
	cout << "	__          __  ______              _____     ____    _   _ ";
	moveCursor(x, y + 16);
	cout << "	\\ \\        / / |  ____|     /\\     |  __ \\   / __ \\  | \\ | |";
	moveCursor(x, y + 17);
	cout << "	 \\ \\  /\\  / /  | |__       /  \\    | |__) | | |  | | |  \\| |";
	moveCursor(x, y + 18);
	cout << "	  \\ \\/  \\/ /   |  __|     / /\\ \\   |  ___/  | |  | | | . ` |";
	moveCursor(x, y + 19);
	cout << "	   \\  /\\  /    | |____   / ____ \\  | |      | |__| | | |\\  |";
	moveCursor(x, y + 20);
	cout << "	    \\/  \\/     |______| /_/    \\_\\ |_|       \\____/  |_| \\_|";
	moveCursor(x, y + 25);
	cout << "	 _    _   ______              _        ";
	moveCursor(x, y+26);
	cout << "	| |  | | |  ____|     /\\     | |      ";
	moveCursor(x, y+27);
	cout << "	| |__| | | |__       /  \\    | |      ";
	moveCursor(x, y+28);
	cout << "	|  __  | |  __|     / /\\ \\   | |     ";
	moveCursor(x, y+29);
	cout << "	| |  | | | |____   / ____ \\  | |____  ";
	moveCursor(x, y+30);
	cout << "	|_|  |_| |______| /_/    \\_\\ |______|";
	moveCursor(x, y + 35);
	cout << "	 _____    _    _   _   _     ";
	moveCursor(x, y + 36);
	cout << "	|  __ \\  | |  | | | \\ | |  ";
	moveCursor(x, y + 37);
	cout << "	| |__) | | |  | | |  \\| |   ";
	moveCursor(x, y + 38);
	cout << "	|  _  /  | |  | | | . ` |    ";
	moveCursor(x, y + 39);
	cout << "	| | \\ \\  | |__| | | |\\  | ";
	moveCursor(x, y + 40);
	cout << "	|_|  \\_\\  \\____/  |_| \\_|";
                          
         
}

int optionsArray[6] = { 2, 1, 0, 0, 0, 2};

int oRow = 1;
int weaponCycle = 0;
int storeRow = -1;

void choicePrinter() {
	int x = 190;
	int y = 6;
	if (storeRow == 0) y = 6;
	if (storeRow == 1) y = 16;
	if (storeRow == 2) y = 26;
	if (storeRow == 3) y = 36;
	if (storeRow >= 0) {
		moveCursor(x + 6, y);
		cout << "\b\b\b\b\b\b      ";
		moveCursor(x + 6, y + 1);
		cout << "\b\b\b\b\b\b      ";
		moveCursor(x + 6, y + 2);
		cout << "\b\b\b\b\b\b      ";
		moveCursor(x + 6, y + 3);
		cout << "\b\b\b\b\b\b      ";
		moveCursor(x + 6, y + 4);
		cout << "\b\b\b\b\b\b      ";
		moveCursor(x + 6, y + 5);
		cout << "\b\b\b\b\b\b      ";
	}

	if (oRow - 1 == 0) y = 6;
	if (oRow - 1 == 1) y = 16;
	if (oRow - 1 == 2) y = 26;
	if (oRow - 1 == 3) y = 36;
	moveCursor(x, y);
	cout << "   __ ";
	moveCursor(x, y+1);
	cout << "  / / ";
	moveCursor(x, y+2);
	cout << " / /  ";
	moveCursor(x, y+3);
	cout << " < <  ";
	moveCursor(x, y+4);
	cout << " \\ \\  ";
	moveCursor(x, y+5);
	cout << "  \\_\\ ";
	storeRow = oRow - 1;
}

void playerChoice() {
	if (firstMove) {
		choicePrinter();
		firstMove = false;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		if (optionsArray[oRow - 1] != 2) {
			optionsArray[oRow] = 0;
			oRow = oRow - 1;
			optionsArray[oRow] = 1;
			choicePrinter();
			playerT = fightTime + 0.15;
		}
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		if (optionsArray[oRow + 1] != 2) {
			optionsArray[oRow] = 0;
			oRow = oRow + 1;
			optionsArray[oRow] = 1;
			choicePrinter();
			playerT = fightTime + 0.15;
		}
	}

	if (fightTime > playerF && GetAsyncKeyState('E') & 0x8000) {
		if (oRow == 1) {
			currentDelay = wepArr[weaponCycle].delay;
			int missChance = rand() % 100 + 1;
			if (missChance <= wepArr[weaponCycle].accuracy && wepArr[weaponCycle].melee == false && wepArr[weaponCycle].ammo > 0) {
				moveCursor(20, 48);
				cout << "                                                                                 ";
				moveCursor(20, 48);
				cout << "THE BULLET STRIKES YOUR TARGET";
				wepArr[weaponCycle].ammo = wepArr[weaponCycle].ammo - 1;
				mHealth = mHealth - wepArr[weaponCycle].damage;
				moveCursor(133, 47);
				cout << "                                                                                 ";
				moveCursor(133, 47);
				cout << "Weapon: " << wepArr[weaponCycle].name;
				if (wepArr[weaponCycle].melee == false) cout << " Ammo: " << wepArr[weaponCycle].ammo;
			}
			else if (missChance <= wepArr[weaponCycle].accuracy && wepArr[weaponCycle].melee == true) {
				moveCursor(20, 48);
				cout << "                                                                                 ";
				moveCursor(20, 48);
				cout << "THE WEAPON STRIKES YOUR TARGET";
				mHealth = mHealth - wepArr[weaponCycle].damage;
			}
			else if (missChance > wepArr[weaponCycle].accuracy && wepArr[weaponCycle].melee == false && wepArr[weaponCycle].ammo > 0) {
				moveCursor(20, 48);
				cout << "                                                                                 ";
				moveCursor(20, 48);
				cout << "THE BULLET MISSES YOUR TARGET";
				moveCursor(133, 47);
				cout << "                                                                                 ";
				moveCursor(133, 47);
				wepArr[weaponCycle].ammo = wepArr[weaponCycle].ammo - 1;
				cout << "Weapon: " << wepArr[weaponCycle].name;
				if (wepArr[weaponCycle].melee == false) cout << " Ammo: " << wepArr[weaponCycle].ammo;
			}
			else if (missChance > wepArr[weaponCycle].accuracy && wepArr[weaponCycle].melee == true) {
				moveCursor(20, 48);
				cout << "                                                                                 ";
				moveCursor(20, 48);
				cout << "THE WEAPON STRIKES YOUR TARGET BUT YOU ARE HIT IN THE PROCESS";
				mHealth = mHealth - wepArr[weaponCycle].damage;
				health = health - 10;
				if (health < 0) health = 0;
				moveCursor(135, 45);
				cout << "                                                                                 ";
				moveCursor(135, 45);
				cout << "Health: " << health << " Remaining Health Drink: " << healthPotions;
			}
			else if (wepArr[weaponCycle].melee == false && wepArr[weaponCycle].ammo <= 0) {
				moveCursor(20, 48);
				cout << "                                                                                 ";
				moveCursor(20, 48);
				cout << "NO AMMO";
			}
			playerF = fightTime + currentDelay;
			moveCursor(0, 45);
			for (int x = 0; x <= currentDelay; x++) {
				cout << char(219);
			}
		}
		if (oRow == 2) {
			currentDelay = 1;
			bool selected = false;
			while (!selected) {
				weaponCycle = weaponCycle + 1;
				if (wepArr[weaponCycle].unlocked) selected = true;
			}
			if (weaponCycle > 6) weaponCycle = 0;
			playerF = fightTime + currentDelay;
			moveCursor(133, 47);
			cout << "                                                                                 ";
			moveCursor(133, 47);
			cout << "Weapon: " << wepArr[weaponCycle].name;
			if (wepArr[weaponCycle].melee == false) cout << " Ammo: " << wepArr[weaponCycle].ammo;
			moveCursor(0, 45);
			for (int x = 0; x <= currentDelay; x++) {
				cout << char(219);
			}
		}
		if (oRow == 3) {
			if (healthPotions > 0) {
				if (healthPotions > 0 && health < 100) {
					currentDelay = 5;

					health = health + 20;
					healthPotions = healthPotions - 1;
					if (health > 100) health = 100;
					moveCursor(20, 48);
					cout << "                                                                                 ";
					moveCursor(20, 48);
					cout << "YOU CONSUME A HEALTH DRINK";
					moveCursor(135, 45);
					cout << "                                                                                 ";
					moveCursor(135, 45);
					cout << "Health: " << health << " Remaining Health Drink: " << healthPotions;
					playerF = fightTime + currentDelay;
					moveCursor(0, 45);
					for (int x = 0; x <= currentDelay; x++) {
						cout << char(219);
					}
				}
				else if (healthPotions < 1) {
					moveCursor(20, 48);
					cout << "                                                                                 ";
					moveCursor(20, 48);
					cout << "YOU ARE OUT OF HEALTH DRINKS";
				}
				else if (health > 99) {
					moveCursor(20, 48);
					cout << "                                                                                 ";
					moveCursor(20, 48);
					cout << "YOU ARE ALREADY FULL HEALTH";
				}
			}
		}
		if (oRow == 4) {
			currentDelay = 10;
			playerF = fightTime + currentDelay;
			int escapeChance = rand() % 2;
			if (escapeChance == 1) {
				moveCursor(20, 48);
				cout << "                                                                                 ";
				moveCursor(20, 48);
				cout << "YOU ESCAPE SUCCESSFULLY";
				isFighting = false;
			}
			if (escapeChance == 2) {
				moveCursor(20, 48);
				cout << "                                                                                 ";
				moveCursor(20, 48);
				cout << "YOU FAIL TO ESCAPE";
			}
			
		}
		playerT = fightTime;
	}
}

int fight(int mHP, int mDa, int mDe, int value) {

	currentDelay = 0;

	firstMove = true;

	fightTime = 0;
	playerF = 0;
	playerT = 0;
	monsterT = 0;

	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 7);

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);

	battlePrint(value);
	
	mHealth = mHP;
	mDamage = mDa;
	mDelay = mDe;

	isFighting = true;
	std::clock_t s;

	s = std::clock();

	fightTime = (std::clock() - s) / (double)CLOCKS_PER_SEC;

	moveCursor(135, 45);
	cout << "Health: " << health << " Remaining Health Drink: " << healthPotions;

	moveCursor(133, 47);
	cout << "Weapon: " << wepArr[weaponCycle].name;
	if (wepArr[weaponCycle].melee == false) cout << " Ammo: " << wepArr[weaponCycle].ammo;

	monsterT = fightTime + 20;
	moveCursor(0, 5);
	for (int x = 0; x <= 20; x++) {
		cout << char(219);
	}
	moveCursor((monsterT - fightTime) + 1, 5);
	cout << "\b ";

	while (health > 0 && mHealth > 0 && isFighting) {
		fightTime = (std::clock() - s) / (double)CLOCKS_PER_SEC;
		if (fightTime > playerT) playerChoice();
		if (fightTime > monsterT) {
			health = health - mDamage;
			monsterT = fightTime + 20;
			moveCursor(0, 5);
			if (health < 0) health = 0;
			for (int x = 0; x <= 20; x++) {
				cout << char(219);
			}
			moveCursor(20, 48);
			cout << "                                                                                 ";
			moveCursor(20, 48);
			cout << "THE CREATURE STRIKES YOU";
			moveCursor(135, 45);
			cout << "                                                                                 ";
			moveCursor(135, 45);
			cout << "Health: " << health << " Remaining Health Drink: " << healthPotions;
		}
		moveCursor((monsterT - fightTime) + 1, 5);
		cout << "\b ";
		moveCursor((playerF - fightTime) + 2, 45);
		cout << "\b ";
	}
	Sleep(500);
	system("cls");
	if (health <= 0) return 1;
	if (mHealth <= 0) return 2;
	if (!isFighting) return 3;
}