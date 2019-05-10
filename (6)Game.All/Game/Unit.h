#pragma once

#include <iostream>
#include <string>

/*
#define FLUX			Attack_slash
#define CONDUCTIVITY	Defence_slash
#define FLAW			Attack_pierce
#define CONSISTENCY		Defence_pierce
#define FORCE			Attack_crush
#define CONSTANCY		Defence_crush
#define FERVOR			Attack_scorch
#define CHASTITY		Defence_scorch
*/

using namespace std;
using UINT = unsigned int;

enum UnitTypes { Bio, Mech, Struct, Decor };
enum AttArmTypes { N, L, M, H, U };
const double AtkMod[5][5] = {
	{ 2,	0.75,	0.5,	0.25,	0 },
	{ 2,	1,		0.5,	1.5,	0 },
	{ 2,	1.5,	1,		0.5,	0 },
	{ 2,	0.5,	1.5,	1,		0 },
	{ 10,	10,		10,		10,		1 }
};

struct Attack {
	int Type;
	int Base;
	int Dice;
	int Sides;
	
	UINT Slash;
	UINT Pierce;
	UINT Crush;
	UINT Scorch;
};
struct Defence {
	int Type;
	int	Value;

	UINT Slash;
	UINT Pierce;
	UINT Crush;
	UINT Scorch;
};

class Unit {
private:
	string Name;
public:	
	UINT Id;
	UINT Type;
	UINT HP_max;
	int HP_current;
	UINT MoveSpeed;

	Attack Att;
	Defence Def;

	~Unit();
	void Spawn();	
	bool isDead();
	
	string MyNameIs();
	void NowIam(string);
		
	template <class T> void Attack(T Target) {
		int Damage = Att.Base;

		for (int i = 0; i < Att.Dice; i++) Damage += rand() % (Att.Sides + 1);
		double Reduction_flat = 1 - 0.06*Target->Def.Value / (1 + 0.06*abs(Target->Def.Value));
		double Reduction_type = AtkMod[Target->Type][Att.Type];

		Damage = (int)ceil(Damage * Reduction_type * Reduction_flat);
		Target->HP_current -= Damage;

		cout << Name << " inflicted " << Damage << " dmg to " << Target->Name << endl;
	}
};