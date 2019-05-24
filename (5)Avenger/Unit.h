#pragma once

#include "PhysObject.h"

enum Movement { FORWARD, BACKWARD, LEFT, RIGHT };

class Unit : public PhysObject {
private:
	//GLuint Id;
	//GLuint Type;
	//GLuint MoveSpeed;
	
	//int Att;
	//int Def;
public:
	void SetUnit() { SetShader("D:/Google/Resources/Shaders/5/Obj.vert", "D:/Google/Resources/Shaders/5/Obj.frag", nullptr); }
	bool isDead() {
		if (GetHP() <= 0) {
			delete this;
			return true;
		}
		else return false;
	}

	void Move(Movement direction, GLfloat delta) {
		switch (direction) {
		case FORWARD: {
			GetModel()->MoveZ(delta);
			GetHitbox()->MoveForward(delta);
		} break;
		case BACKWARD: {
			GetModel()->MoveZ(-delta);
			GetHitbox()->MoveBackward(delta);
		} break;
		case LEFT: {
			GetModel()->MoveX(delta);
			GetHitbox()->MoveLeft(delta);
		} break;
		case RIGHT: {
			GetModel()->MoveX(-delta);
			GetHitbox()->MoveRight(delta);
		} break;
		default: 
			break;
		}
	}
	/*
	template <class T> void Attack(T Target) {
		int Damage = (int)ceil(Att * (1 - 0.06*Target->Def / (1 + 0.06*abs(Target->Def))));
		
		Target->AddHP(-Damage);

		cout << GetName() << " inflicted " << Damage << " dmg to " << Target->GetName() << endl;
	}
	*/
	
	void NameYourself() { SetName("Unit"); }

	Unit() {
		AddHP(100);
		
		NameYourself();
		if (Logging) logger.write(GetName() + " has been spawned into this world with " + to_string(GetHP()) + " hitpoints.");
	}
	~Unit() {
		if (Logging) logger.write("Unit has been despawned.\n");
	}
};

class Player : public Unit {
public:
	void SetPlayer() {
		SetUnit();

		SetModel("D:/Google/Resources/Model/Ship/Ship.obj");
		GetModel()->RotateY(90.0f);
		GetModel()->ScaleAll(0.5);

		GetHitbox()->SetSphere(2);		
	}
	
	void NameYourself() { SetName("Player"); }

	Player() {
		NameYourself();	
		if (Logging) logger.write("My name is " + GetName() + ".\n");
	}
	~Player() {
		if (Logging) logger.write("Player is dead.");
	}
};
class Enemy : public Unit {
public:
	void SetEnemy(GLfloat size) {
		SetUnit();

		SetModel("D:/Google/Resources/Model/corovan/Wagons.obj");
		GetModel()->MoveX(6);
		GetModel()->RotateY(-90.0f);
		GetModel()->ScaleAll(size);

		GetHitbox()->SetBox(size);
	}

	void NameYourself() { SetName("Enemy"); }

	Enemy() {
		NameYourself();
		if (Logging) logger.write("My name is " + GetName() + ".\n");
	}
	~Enemy() {
		if (Logging) logger.write("Enemy is eliminated.");
	}
};