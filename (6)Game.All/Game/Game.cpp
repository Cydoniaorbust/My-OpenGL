#include "Game.h"

#include <ctime>
#include <windows.h>

Game::Game() {}
Game::~Game() {}

void Game::Script_Arena(int fights) {
	while (1) {
		int Score[3] = { 0,0,0 };

		for (int i = 0; i < fights; i++) {
			cout << "________________________________\n";

			Unit 
				*First = new Knight, 
				*Second = new Samurai;
			bool WC1, WC2;

			while (1) {
				First->Attack(Second);
				Second->Attack(First);

				WC1 = First->isDead();
				WC2 = Second->isDead();

				if (WC1 && WC2) {
					cout << "Contestants drew!\n";
					Score[0]++;
					break;
				}
				if (WC1) {
					cout << Second->MyNameIs() << " is a winner!\n";
					Score[1]++;
					break;
				}
				if (WC2) {
					cout << First->MyNameIs() << " is a winner!\n";
					Score[2]++;
					break;
				}					
			}
		}

		cout
			<< "________________________________\n"
			<< "Draws: " << Score[0]
			<< "\nFirst wins: " << Score[1]
			<< "\nSecond wins: " << Score[2]
			<< endl;
		Sleep(10000);
	}
}

int main() {
	srand((unsigned int)time(NULL));

	Game Game_1;
	Game_1.Script_Arena(100);

	return 0;
}