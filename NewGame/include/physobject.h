#pragma once

#include "Entity.h"

enum class Movement { FORWARD, BACKWARD, LEFT, RIGHT, SET } ;

class PhysObject : public Entity {
private:
	int hpCurrent;
	GLuint hpMax;

	Hitbox hitbox;
	bool collision = false;
public:
	void SetObject() { SetShader("D:/Google/Resources/Shaders/5/Obj.vert", "D:/Google/Resources/Shaders/5/Obj.frag", nullptr); }

	int GetHP() { return hpCurrent; }
	void AddHP(int _hpAdded) {
		int sum = _hpAdded + hpCurrent;
		if (sum > hpMax) hpCurrent = hpMax;
		else
			if (sum < 0) hpCurrent = 0;
			else hpCurrent += _hpAdded;
	}

	GLuint GetMaxHP() { return hpMax; }
	void SetMaxHP(GLuint _max) { hpMax = _max; }

	Hitbox* GetHitbox() { return &hitbox; }

	bool GetState() { return collision; }
	void Collide() { collision = true; }
	void UnCollide() { collision = false; }

	void Draw(const glm::vec3& _position, const glm::mat4& _view, GLfloat _aspect, bool _draw) {
		Shader::Use(GetShader());

		Shader::SetVec3(GetShader(), "ViewPos", _position);
		Shader::SetVec3(GetShader(), "direction", glm::vec3(-0.2f, -1, -0.3f));

		Shader::SetMat4(GetShader(), "view", _view);
		Shader::SetMat4(GetShader(), "projection", glm::perspective(glm::radians(90.0f), _aspect, 0.1f, 1000.0f));

		Shader::SetMat4(GetShader(), "model", GetPosition());
		GetModel()->Draw(GetShader());

		hitbox.Draw(_view, _aspect, collision, _draw);
	}
	
	void Move(Movement _direction, GLfloat _delta = 0.0f, GLfloat _gamma = 0.0f) {
		switch (_direction) {
		case Movement::FORWARD: {
			MoveZ(_delta);
			GetHitbox()->MoveZ(_delta);
		} break;
		case Movement::BACKWARD: {
			MoveZ(-_delta);
			GetHitbox()->MoveZ(-_delta);
		} break;
		case Movement::LEFT: {
			MoveX(_delta);
			GetHitbox()->MoveX(_delta);
		} break;
		case Movement::RIGHT: {
			MoveX(-_delta);
			GetHitbox()->MoveX(-_delta);
		} break;
		case Movement::SET: {
			SetPos(_delta, _gamma);
			GetHitbox()->SetPos(_delta, _gamma);
		} break;
		default:
			break;
		}
	}

	void NameYourself() { SetName("Object"); }

	PhysObject() : hpCurrent(0), hpMax(100) { NameYourself(); }
	~PhysObject() {}
};

class Bullet : public PhysObject {
	bool active = false;
public:
	bool GetState() { return active; }
	void Activate(GLfloat _x, GLfloat _y) {
		active = true; 
		Move(Movement::SET, _x, _y);
	}
	void Deactivate() { 
		active = false;
		Move(Movement::SET);
	}

	void SetBullet(Model* _model, Model* _model_h, Model* _model_h_c) {
		SetObject();

		SetModel(_model);
		RotateY(90.0f);		
		ScaleAll(0.5);

		GetHitbox()->SetSphere(1, _model_h, _model_h_c);
	}
	
	void NameYourself() { SetName("Bullet"); }

	Bullet() { NameYourself(); }
	~Bullet() {}
};