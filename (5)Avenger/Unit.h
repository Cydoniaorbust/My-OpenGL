#pragma once

#include "PhysObject.h"

class unit : public physobject {
private:
	UINT Id;
	UINT Type;
	UINT MoveSpeed;

	int Att;
	int Def;
public:
	void NameYourself() {
		MyNewName("Unit");
	}
	void SetUnit() {
		SetShader("D:/Google/Resources/Shaders/5/Obj.vert", "D:/Google/Resources/Shaders/5/Obj.frag", nullptr);
	}
	bool isDead() {
		if (MyHP() <= 0) {
			delete this;
			return true;
		}
		else return false;
	}

	template <class T> void Attack(T Target) {
		int Damage = (int)ceil(Att * (1 - 0.06*Target->Def / (1 + 0.06*abs(Target->Def))));
		
		Target->AddHP(-Damage);

		cout << MyName() << " inflicted " << Damage << " dmg to " << Target->MyName() << endl;
	}

	unit() {
		cout << "The physical object appears to be a unit." << endl;
		NameYourself();
		AddHP(100);
		cout << MyName() << " has been spawned into this world with " << MyHP() << " hitpoints." << endl;
	}
	~unit() {
		cout << "Unit has been despawned." << endl;
	}
};

class player : public unit {
public:
	void SetPlayer() {
		SetUnit();

		Model = model("D:/Google/Resources/Model/Ship/Ship.obj");
		Model.RotateY(90.0f);
		Model.ScaleAll(0.5);
	}
		
	void NameYourself() {
		MyNewName("Player");
		cout << "My name is " << MyName() << "." << endl;
	}

	player() {
		NameYourself();		
	}
	~player() {}
};
class enemy : public unit {
public:
	void SetEnemy() {
		SetUnit();

		Model = model("D:/Google/Resources/Model/corovan/Wagons.obj");
		Model.MoveX(6);
		Model.RotateY(180.0f);
		Model.ScaleAll(0.7);
	}

	void NameYourself() {
		MyNewName("Enemy");
		cout << "My name is " << MyName() << "." << endl;
	}

	enemy() {
		NameYourself();		
	}
	~enemy() {}
};