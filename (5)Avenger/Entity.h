#pragma once

#include "Model.h"

using std::string;

class Entity {
private:
	string Name = "defName";
	GLuint shader = 0;
	Model model;
public:
	string GetName() { return Name; }
	void SetName(const char* name) { Name = name; }
	
	GLuint GetShader() { return shader; }
	void SetShader(const char* V, const char* F, const char* G = nullptr) { shader = Shader::CreateProgram(V, F, G); }
	
	Model* GetModel() { return &model; }
	void SetModel(const char* path) { model = Model(path); }

	virtual void NameYourself() = 0;

	Entity() {}
	virtual ~Entity() { glDeleteProgram(GetShader()); }
};

class Background : private Entity {
private:
	GLuint vao = 1;
	Texture tex = Texture();
public:
	void SetVAO(const GLfloat* vertices, int vert_size, const GLuint* indices, int ind_size) {
		glGenVertexArrays(1, &vao);
		GLuint vbo, ebo;
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);
		
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ARRAY_BUFFER, vert_size * sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_size * sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); //-V566
		glEnableVertexAttribArray(1);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);
	}
	void SetBack() {
		GLfloat Background[] = {
			10, 0, 10, 1, 1,
			10, 0,-10, 1, 0,
			-10, 0,-10, 0, 0,
			-10, 0, 10, 0, 1
		};
		GLuint Indices[] = { 0, 1, 3, 1, 2, 3 };

		SetVAO(Background, 20, Indices, 6);
		SetShader("D:/Google/Resources/Shaders/5/Back.vert", "D:/Google/Resources/Shaders/5/Back.frag", nullptr);
		tex.LoadFromFile("D:/Google/Resources/Tex/Back.jpg");
	}
	void Draw(const mat4& View, float Aspect) {
		Shader::Use(GetShader());
		Shader::SetMat4(GetShader(), "view", View);
		Shader::SetMat4(GetShader(), "projection", glm::perspective(radians(90.0f), Aspect, 0.1f, 1000.0f));
		Shader::SetFloat(GetShader(), "time", glfwGetTime() * 0.1f);
		glActiveTexture(GL_TEXTURE0 + 1);
		Shader::SetInt(GetShader(), "Texture", 1);
		
		tex.Bind();
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void NameYourself() { SetName("Background image"); }
	
	Background() { NameYourself(); }
	~Background() {
		glDeleteTextures(1, &tex.Id);		
		glDeleteVertexArrays(1, &vao);
	}
};
class Hitbox : private Entity {
private:
	GLfloat Radius = 0;
	
	Model CollisionModel;
public:
	GLfloat GetRadius() { return Radius; }
	mat4 GetPosition() { return GetModel()->GetPosition(); }

	void SetBox(GLfloat radius) {
		SetShader("D:/Google/Resources/Shaders/5/Hit.vert", "D:/Google/Resources/Shaders/5/Hit.frag", nullptr);

		SetModel("D:/Google/Resources/Model/box/box.obj");
		GetModel()->MoveX(6);
		GetModel()->RotateY(-90.0f);
		GetModel()->ScaleAll(radius);

		CollisionModel = Model("D:/Google/Resources/Model/box/box_c.obj");
		CollisionModel.MoveX(6);
		CollisionModel.RotateY(-90.0f);
		CollisionModel.ScaleAll(radius);

		Radius = radius;
	}
	void SetSphere(GLfloat radius) {
		SetShader("D:/Google/Resources/Shaders/5/Hit.vert", "D:/Google/Resources/Shaders/5/Hit.frag", nullptr);

		SetModel("D:/Google/Resources/Model/sphere/sphere.obj");
		GetModel()->RotateY(90.0f);
		GetModel()->ScaleAll(radius);

		CollisionModel = Model("D:/Google/Resources/Model/sphere/sphere_c.obj");
		CollisionModel.RotateY(90.0f);
		CollisionModel.ScaleAll(radius);

		Radius = radius;
	}
	void Draw(const mat4& View, float Aspect, bool collision) {
		Shader::Use(GetShader());

		Shader::SetMat4(GetShader(), "view", View);
		Shader::SetMat4(GetShader(), "projection", glm::perspective(radians(90.0f), Aspect, 0.1f, 1000.0f));

		if (collision) {
			Shader::SetMat4(GetShader(), "model", CollisionModel.GetPosition());
			CollisionModel.DrawOther(GetShader());
		}
		else {
			Shader::SetMat4(GetShader(), "model", GetPosition());
			GetModel()->DrawOther(GetShader());
		}
	}

	void MoveForward(GLfloat delta) {
		GetModel()->MoveZ(delta);
		CollisionModel.MoveZ(delta);
	}
	void MoveBackward(GLfloat delta) {
		GetModel()->MoveZ(-delta);
		CollisionModel.MoveZ(-delta);
	}
	void MoveRight(GLfloat delta) {
		GetModel()->MoveX(-delta);
		CollisionModel.MoveX(-delta);
	}
	void MoveLeft(GLfloat delta) {
		GetModel()->MoveX(delta);
		CollisionModel.MoveX(delta);
	}

	void NameYourself() { SetName("Hitbox"); }

	Hitbox() { NameYourself(); }
	~Hitbox() {}
};