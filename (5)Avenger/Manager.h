#pragma once

#include "Entity.h"
#include "PhysObject.h"
#include "Unit.h"

#include <map>
#include <iomanip>

class manager {
private:
public:
	Background BImage;

	Player Hero;
	Enemy Foe;

	vector<Bullet> shots;

	static GLfloat Sqr(GLfloat var) { return var * var; }
	static GLfloat CountDistance(const mat4& first, const mat4& second) {
		return sqrt(Sqr(second[3][0] - first[3][0]) + Sqr(second[3][2] - first[3][2]));
	}
	static bool CollisionBetween(Hitbox* first, Hitbox* second) {
		mat4 a = first->GetPosition();
		mat4 b = second->GetPosition();
		GLfloat DistBetween = first->GetRadius() + second->GetRadius();

		if (CountDistance(a, b) < DistBetween) return true;
		else return false;
	}

	manager() {
		shots.reserve(100);
	}
	~manager() {}

	manager(const manager &) = delete;
	manager& operator=(const manager &) = delete;
	manager(manager &&) = delete;
	manager& operator=(manager &&) = delete;
};