#pragma once

#include "Entity.h"
#include "PhysObject.h"
#include "Unit.h"

#include <map>
#include <iomanip>

class Manager {
private:
	map<string, Model> models;
	//map<string, int> shaders;
	
	int activeShots = 0;
public:
	Background backImage;
	Player hero;
	Enemy foe;
	vector<Bullet> shots;

	Model* GetModel(string _name) { return &models[_name]; }
	void SetModel(string _name, string _path) { models[_name] = Model(_path); }

	int CountShots() {
		activeShots = 0;
		for (int i = 0; i < shots.size(); i++) if (shots[i].GetState()) activeShots++;
		return activeShots;
	}
	
	void SetData() {
		SetModel("box", "D:/Google/Resources/Model/box/box.obj");
		SetModel("box_c", "D:/Google/Resources/Model/box/box_c.obj");
		SetModel("sphere", "D:/Google/Resources/Model/sphere/sphere.obj");
		SetModel("sphere_c", "D:/Google/Resources/Model/sphere/sphere_c.obj");
		SetModel("bullet", "D:/Google/Resources/Model/bullet/bullet.obj");
		SetModel("player", "D:/Google/Resources/Model/Ship/Ship.obj");
		SetModel("enemy", "D:/Google/Resources/Model/corovan/Wagons.obj");

		backImage.SetBack();
		hero.SetPlayer(&models["player"], &models["sphere"], &models["sphere_c"]);
		foe.SetEnemy(0.7, &models["enemy"], &models["box"], &models["box_c"]);
		shots = vector<Bullet>(100);
		for (int i = 0; i < 100; i++) shots[i].SetBullet(&models["bullet"], &models["sphere"], &models["sphere_c"]);
	}

	static GLfloat Sqr(GLfloat _x) { return _x * _x; }
	static GLfloat CountDistance(const mat4& _first, const mat4& _second) {
		return sqrt(Sqr(_second[3][0] - _first[3][0]) + Sqr(_second[3][2] - _first[3][2]));
	}
	static bool CollisionBetween(Hitbox* _first, Hitbox* _second) {
		mat4 x = _first->GetPosition();
		mat4 y = _second->GetPosition();
		GLfloat DistBetween = _first->GetRadius() + _second->GetRadius();

		if (CountDistance(x, y) < DistBetween) return true;
		else return false;
	}
	
	Manager() {}
	~Manager() {}

	Manager(const Manager &) = delete;
	Manager& operator=(const Manager &) = delete;
	Manager(Manager &&) = delete;
	Manager& operator=(Manager &&) = delete;
};