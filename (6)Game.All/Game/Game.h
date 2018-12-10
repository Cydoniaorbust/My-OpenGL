#pragma once

#include "Unit.h"
#include "Game_map.h"

class Samurai : public Unit {
public:
	Samurai() {
		NowIam("Samurai " + to_string(N));

		Type = UnitTypes::Bio;
		HP_max = 80;
		MoveSpeed = 250;

		Att.Type = AttArmTypes::M;
		Att.Base = 12;
		Att.Dice = 3;
		Att.Sides = 3;

		Def.Type = AttArmTypes::L;
		Def.Value = 2;

		Spawn();
	}
};
class Knight : public Unit {
public:
	Knight() {
		NowIam("Knight " + to_string(N));

		Type = UnitTypes::Bio;
		HP_max = 100;
		MoveSpeed = 250;

		Att.Type = AttArmTypes::M;
		Att.Base = 10;
		Att.Dice = 2;
		Att.Sides = 2;

		Def.Type = AttArmTypes::H;
		Def.Value = 5;

		Spawn();
	}
};

class Game {
private:
	vector<int> Id;
	Game_Map Field;
public:
	Game();
	~Game();

	void Script_Arena(int);
};
