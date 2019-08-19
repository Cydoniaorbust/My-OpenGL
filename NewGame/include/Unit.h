#pragma once

#include "PhysObject.h"

class Unit : public PhysObject {
public:
	void SetUnit() {
		SetObject();
		AddHP(100);
	}
	bool IsDead() {
		if (GetHP() <= 0) {
			delete this;
			return true;
		}
		else return false;
	}

	void NameYourself() { SetName("Unit"); }

	Unit() { NameYourself(); }
	~Unit() {}
};

class Player : public Unit {
public:
	void SetPlayer(Model* _model, Model* _model_h, Model* _model_h_c) {
		SetUnit();

		SetModel(_model);
		RotateY(90.0f);
		ScaleAll(0.5);

		GetHitbox()->SetSphere(2, _model_h, _model_h_c);
	}
	
	void NameYourself() { SetName("Player"); }

	Player() { NameYourself(); }
	~Player() {}
};
class Enemy : public Unit {
public:
	void SetEnemy(GLfloat size, Model* _model, Model* _model_h, Model* _model_h_c) {
		SetUnit();

		SetModel(_model);
		MoveX(6);
		RotateY(-90.0f);
		ScaleAll(size);

		GetHitbox()->SetBox(size, _model_h, _model_h_c);
	}

	void NameYourself() { SetName("Enemy"); }

	Enemy() { NameYourself(); }
	~Enemy() {}
};