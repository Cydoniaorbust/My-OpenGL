#pragma once

#include "Entity.h"

class physobject : public entity {
private:
	int HP_current;
	UINT HP_max;
public:
	model Model;

	int MyHP() {
		return HP_current;
	}
	UINT MyMaxHP() {
		return HP_max;
	}
	void AddHP(int HP_added) {
		int sum = HP_added + HP_current;
		if (sum > HP_max) HP_current = HP_max;
		else
			if (sum < 0) HP_current = 0;
			else HP_current += HP_added;
	}
	
	void Draw(glm::vec3 Position, glm::mat4 View, float Aspect) {
		Shader::Use(GetShader());

		Shader::SetVec3(GetShader(), "ViewPos", Position);
		Shader::SetVec3(GetShader(), "direction", vec3(-0.2f, -1, -0.3f));

		Shader::SetMat4(GetShader(), "view", View);
		Shader::SetMat4(GetShader(), "projection", glm::perspective(radians(90.0f), Aspect, 0.1f, 1000.0f));

		Shader::SetMat4(GetShader(), "model", Model.position);
		Model.Draw(GetShader());
	}

	void NameYourself() {
		MyNewName("Object");
	}

	physobject() : HP_current(0), HP_max(100), Model() {
		cout << "The entity took shape of a physical object." << endl;
		NameYourself();
	}
	~physobject() {
		cout << "Physical object has been destructed." << endl;
	}
};

class hitbox : public physobject {
public:
	void SetHit() {
		SetShader("D:/Google/Resources/Shaders/5/Hit.vert", "D:/Google/Resources/Shaders/5/Hit.frag", nullptr);

		Model = model("D:/Google/Resources/Model/sphere/sphere.obj");
		Model.RotateY(90.0f);
		Model.ScaleAll(2);
	}
	void Draw(glm::mat4 View, float Aspect) {
		Shader::Use(GetShader());

		Shader::SetMat4(GetShader(), "view", View);
		Shader::SetMat4(GetShader(), "projection", glm::perspective(radians(90.0f), Aspect, 0.1f, 1000.0f));

		Shader::SetMat4(GetShader(), "model", Model.position);
		Model.DrawOther(GetShader());
	}

	void NameYourself() {
		MyNewName("Hitbox");
		cout << "My name is " << MyName() << "." << endl;
	}

	hitbox() {
		NameYourself();	
	}
	~hitbox() {}
};
class bullet : public physobject {
public:
	void NameYourself() {
		MyNewName("Bullet"); 
		cout << "My name is " << MyName() << "." << endl;
	}

	bullet() {
		NameYourself();	
	}
	~bullet() {}
};