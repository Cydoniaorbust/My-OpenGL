#pragma once

#include "Entity.h"

class PhysObject : public Entity {
private:
	int HP_current;
	GLuint HP_max;

	Hitbox hitbox;
	bool Collision = false;
public:
	int GetHP() { return HP_current; }
	void AddHP(int HP_added) {
		int sum = HP_added + HP_current;
		if (sum > HP_max) HP_current = HP_max;
		else
			if (sum < 0) HP_current = 0;
			else HP_current += HP_added;
	}

	GLuint GetMaxHP() { return HP_max; }
	void SetMaxHP(GLuint max) { HP_max = max; }

	Hitbox* GetHitbox() { return &hitbox; }
	void Collide() { Collision = true; }
	void UnCollide() { Collision = false; }

	void Draw(const vec3& Position, const mat4& View, float Aspect) {
		Shader::Use(GetShader());

		Shader::SetVec3(GetShader(), "ViewPos", Position);
		Shader::SetVec3(GetShader(), "direction", vec3(-0.2f, -1, -0.3f));

		Shader::SetMat4(GetShader(), "view", View);
		Shader::SetMat4(GetShader(), "projection", glm::perspective(radians(90.0f), Aspect, 0.1f, 1000.0f));

		Shader::SetMat4(GetShader(), "model", GetModel()->GetPosition());
		GetModel()->Draw(GetShader());

		hitbox.Draw(View, Aspect, Collision);
	}

	void NameYourself() { SetName("Object"); }

	PhysObject() : HP_current(0), HP_max(100) {
		NameYourself();
	}
	~PhysObject() {}
};

class Bullet : public PhysObject {
public:
	void NameYourself() { SetName("Bullet"); }

	Bullet() {}
	~Bullet() {}
};