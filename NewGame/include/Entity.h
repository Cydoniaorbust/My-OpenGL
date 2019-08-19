#pragma once

class Entity {
private:
	std::string name = "defName";
	GLuint shader = 0;
	Model* model;

	glm::mat4 position;

	float stepMove = 1.0f;
	float stepRotate = 1.0f;
public:
	std::string GetName() { return name; }
	void SetName(const char* _name) { name = _name; }
	
	GLuint GetShader() { return shader; }
	void SetShader(const char* _V, const char* _F, const char* _G = nullptr) { shader = Shader::CreateProgram(_V, _F, _G); }
	
	Model* GetModel() { return model; }
	void SetModel(Model* _model) { model = _model; }

	glm::mat4 GetPosition() { return position; }
	#pragma region Movements	
	void MoveX(GLfloat _delta) { position = translate(position, glm::vec3(_delta * stepMove, 0, 0)); }
	void MoveY(GLfloat _delta) { position = translate(position, glm::vec3(0, _delta * stepMove, 0)); }
	void MoveZ(GLfloat _delta) { position = translate(position, glm::vec3(0, 0, _delta * stepMove)); }
	void SetPos(GLfloat _x, GLfloat _y) { position[3][0] = _x; position[3][2] = _y; }

	void ScaleAll(GLfloat _delta) {
		position = glm::scale(position, glm::vec3(_delta));
		stepMove = 5 / _delta;
		stepRotate = 100;
	}

	void RotateX(GLfloat _degrees) { position = glm::rotate(position, glm::radians(_degrees * stepRotate), glm::vec3(1, 0, 0)); }
	void RotateY(GLfloat _degrees) { position = glm::rotate(position, glm::radians(_degrees * stepRotate), glm::vec3(0, 1, 0)); }
	void RotateZ(GLfloat _degrees) { position = glm::rotate(position, glm::radians(_degrees * stepRotate), glm::vec3(0, 0, 1)); }
	#pragma endregion

	virtual void NameYourself() = 0;

	Entity() {}
	virtual ~Entity() { glDeleteProgram(GetShader()); }
};

class Background : public Entity {
private:
	GLuint vao = 1;
	Texture tex = Texture();
public:
	void SetVAO(const GLfloat* _vertices, int _vertSize, const GLuint* _indices, int _indSize) {
		glGenVertexArrays(1, &vao);
		GLuint vbo, ebo;
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);
		
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ARRAY_BUFFER, _vertSize * sizeof(_vertices), _vertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indSize * sizeof(_indices), _indices, GL_STATIC_DRAW);

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
		GLfloat background[] = {
			10, 0, 10, 1, 1,
			10, 0,-10, 1, 0,
			-10, 0,-10, 0, 0,
			-10, 0, 10, 0, 1
		};
		GLuint indices[] = { 0, 1, 3, 1, 2, 3 };

		SetVAO(background, 20, indices, 6);
		SetShader("D:/Google/Resources/Shaders/5/Back.vert", "D:/Google/Resources/Shaders/5/Back.frag", nullptr);
		tex.LoadFromFile("D:/Google/Resources/Tex/Back.jpg");
	}
	void Draw(const glm::mat4& _view, float _aspect) {
		Shader::Use(GetShader());
		Shader::SetMat4(GetShader(), "view", _view);
		Shader::SetMat4(GetShader(), "projection", glm::perspective(glm::radians(90.0f), _aspect, 0.1f, 1000.0f));
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
	~Background() { glDeleteVertexArrays(1, &vao); }
};
class Hitbox : public Entity {
private:
	GLfloat radius = 0;
	
	Model* collisionModel; //model, representing the "collisioned" state (red one)
public:
	GLfloat GetRadius() { return radius; }	

	void SetBox(GLfloat _radius, Model* _model, Model* _model_c) {
		SetShader("D:/Google/Resources/Shaders/5/Hit.vert", "D:/Google/Resources/Shaders/5/Hit.frag", nullptr);
		
		SetModel(_model);
		collisionModel = _model_c;
		
		MoveX(6);
		RotateY(90.0f);
		ScaleAll(_radius);
		
		radius = _radius;
	}
	void SetSphere(GLfloat _radius, Model* _model, Model* _model_c) {
		SetShader("D:/Google/Resources/Shaders/5/Hit.vert", "D:/Google/Resources/Shaders/5/Hit.frag", nullptr);

		SetModel(_model);
		collisionModel = _model_c;
		
		RotateY(90.0f);
		ScaleAll(_radius);

		radius = _radius;
	}
	void Draw(const glm::mat4& _view, float _aspect, bool _collision, bool _draw) {
		if (_draw) {
			Shader::Use(GetShader());

			Shader::SetMat4(GetShader(), "view", _view);
			Shader::SetMat4(GetShader(), "projection", glm::perspective(glm::radians(90.0f), _aspect, 0.1f, 1000.0f));
			Shader::SetMat4(GetShader(), "model", GetPosition());

			if (_collision) collisionModel->DrawOther(GetShader());
			else GetModel()->DrawOther(GetShader());
		}
	}

	bool OutOfBounds() {
		bool x = GetPosition()[3][0] < 10 && GetPosition()[3][0] > -10;
		bool y = GetPosition()[3][2] < 10 && GetPosition()[3][2] > -10;
		if (x && y) return false;
		else return true;
	}

	void NameYourself() { SetName("Hitbox"); }

	Hitbox() { NameYourself(); }
	~Hitbox() {}
};