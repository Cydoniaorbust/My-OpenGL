#include "Study/GLEnvironment.h"
#include "Study/Shader.h"
#include "Study/Camera.h"
#include "Cluster.h"

using namespace glm;

GLEnvironment Env;
Camera Cam(vec3(0, 3, 0));
Cluster Matrixes;
bool keys[1024];

void callback_framebuffer_size(GLFWwindow* Win, int width, int height) { 
	glViewport(0, 0, width, height);
}
void callback_key(GLFWwindow* Win, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)	glfwSetWindowShouldClose(Win, GL_TRUE);
	if (key >= 0 && key < 1024)
		if (action == GLFW_PRESS) keys[key] = true;
		else
			if (action == GLFW_RELEASE) keys[key] = false;
}
void callback_mouse(GLFWwindow* Win, double xpos, double ypos) {
	Cam.ProcessMouseMovement(Env.MouseX(xpos), Env.MouseY(ypos));
}
void callback_scroll(GLFWwindow* Win, double xoffset, double yoffset) { 
	Cam.ProcessMouseScroll(yoffset);
}
void Do_Movement() {
	if (keys[GLFW_KEY_W]) Cam.ProcessKeyboard(FORWARD, Env.delta);
	if (keys[GLFW_KEY_S]) Cam.ProcessKeyboard(BACKWARD, Env.delta);
	if (keys[GLFW_KEY_A]) Cam.ProcessKeyboard(LEFT, Env.delta);
	if (keys[GLFW_KEY_D]) Cam.ProcessKeyboard(RIGHT, Env.delta);
}

void Draw() {
	Shader MyShader("Resources/vShader.versh", "Resources/fShader.fragsh");
	GLuint 
		ColRow[] = {
		Matrixes.MatSqu.GetNColumn(), Matrixes.MatSqu.GetNRow(),
		Matrixes.MatRec.GetNColumn(), Matrixes.MatRec.GetNRow(),
		Matrixes.MatTri.GetNColumn(), Matrixes.MatTri.GetNRow()
	},
		indices[] = { 0, 1, 2, 1, 2, 3 },
		N = 1, l = 0,
		*VAO, *VBO, *EBO,
		*VAOa = new GLuint[3],
		*VBOa = new GLuint[3];
	vector<vector<GLfloat>> Off, Yaw, Axis;
	Axis.resize(3); 
	for (int i = 0; i < 3; i++) Axis[i].resize(6);
	Axis[0] = { 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f }; 
	Axis[1] = { 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f }; 
	Axis[2] = { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f };
	
	if (Matrixes.Once) {
		size_t q = 0, w = 0;
		VAO = new GLuint; 
		VBO = new GLuint; 
		EBO = new GLuint;

		try {
			cin >> q >> w;
			if (q < 0 || w < 0) throw q;
			switch (Matrixes.Tumbler) {
			case 2: if (q >= ColRow[4] || w >= ColRow[5]) throw q;
			case 3: if (q >= ColRow[2] || w >= ColRow[3]) throw q;
			default: if (q >= ColRow[0] || w >= ColRow[1]) throw q;
			}
		}
		catch (...) {
			cerr << "No such element here!\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Draw();
		}

		Off.resize(1); Yaw.resize(1);
		Off[0].resize(3); Yaw[0].resize(3);
		glGenVertexArrays(1, VAO); glGenBuffers(1, VBO);
		glBindVertexArray(*VAO); glBindBuffer(GL_ARRAY_BUFFER, *VBO);
		switch (Matrixes.Tumbler)
		{ 
		case 2: {
			Off[0][0] = Matrixes.MatTri.GetFigArr(q, w)[9]; Off[0][1] = Matrixes.MatTri.GetFigArr(q, w)[10]; Off[0][2] = Matrixes.MatTri.GetFigArr(q, w)[11];
			Yaw[0][0] = Matrixes.MatTri.GetFigArr(q, w)[12]; Yaw[0][1] = Matrixes.MatTri.GetFigArr(q, w)[13]; Yaw[0][2] = Matrixes.MatTri.GetFigArr(q, w)[14];
			glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(GLfloat), Matrixes.MatTri.GetFigArr(q, w), GL_STREAM_DRAW);
		} break;
		case 3: {
			glGenBuffers(1, EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
			Off[0][0] = Matrixes.MatRec.GetFigArr(q, w)[12]; Off[0][1] = Matrixes.MatRec.GetFigArr(q, w)[13]; Off[0][2] = Matrixes.MatRec.GetFigArr(q, w)[14];
			Yaw[0][0] = Matrixes.MatRec.GetFigArr(q, w)[15]; Yaw[0][1] = Matrixes.MatRec.GetFigArr(q, w)[16]; Yaw[0][2] = Matrixes.MatRec.GetFigArr(q, w)[17];
			glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), Matrixes.MatRec.GetFigArr(q, w), GL_STREAM_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);
		} break;
		default: {
			glGenBuffers(1, EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
			Off[0][0] = Matrixes.MatSqu.GetFigArr(q, w)[12]; Off[0][1] = Matrixes.MatSqu.GetFigArr(q, w)[13]; Off[0][2] = Matrixes.MatSqu.GetFigArr(q, w)[14];
			Yaw[0][0] = Matrixes.MatSqu.GetFigArr(q, w)[15]; Yaw[0][1] = Matrixes.MatSqu.GetFigArr(q, w)[16]; Yaw[0][2] = Matrixes.MatSqu.GetFigArr(q, w)[17];
			glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), Matrixes.MatSqu.GetFigArr(q, w), GL_STREAM_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);
		} break;
		}
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(0); glBindBuffer(GL_ARRAY_BUFFER, 0); glBindVertexArray(0);
		glGenVertexArrays(3, VAOa); glGenBuffers(3, VBOa);
		for (int i = 0; i < 3; i++) {
			glBindVertexArray(VAOa[i]);
			glBindBuffer(GL_ARRAY_BUFFER, VBOa[i]);
			glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), &Axis[i][0], GL_STREAM_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
		glLineWidth(3.f);

		while (!glfwWindowShouldClose(Env.Win)) {
			Env.UpdateFrames();
			
			glfwPollEvents();
			Do_Movement();

			//render
			glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			MyShader.Use();
			mat4 view = Cam.GetViewMatrix();
			mat4 projection = perspective(45.0f, (GLfloat)Env.w / (GLfloat)Env.h, 0.1f, 100.0f);
			GLint viewLoc = glGetUniformLocation(MyShader.GetId(), "view");
			GLint projLoc = glGetUniformLocation(MyShader.GetId(), "projection");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projection));

			//drawing
			GLint vertexColorLocation = glGetUniformLocation(MyShader.GetId(), "color");
			glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f);
			mat4 model;
			model = rotate(model, Yaw[0][0], vec3(1.0f, 0.0f, 0.0f));
			model = rotate(model, Yaw[0][1], vec3(0.0f, 1.0f, 0.0f));
			model = rotate(model, Yaw[0][2], vec3(0.0f, 0.0f, 1.0f));
			model = translate(model, vec3(Off[0][0], Off[0][1], Off[0][2]));
			GLint modelLoc = glGetUniformLocation(MyShader.GetId(), "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

			glBindVertexArray(*VAO);
			switch (Matrixes.Tumbler) {
				case 2: glDrawArrays(GL_TRIANGLES, 0, 3); break;
				default: glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); break;
			}
			glBindVertexArray(0);

			mat4 model_a;
			vertexColorLocation = glGetUniformLocation(MyShader.GetId(), "color");
			modelLoc = glGetUniformLocation(MyShader.GetId(), "model");

			for (int i = 0; i < 3; i++) {
				glUniform4f(vertexColorLocation, Axis[i][0], Axis[i][1], Axis[i][2], 1.0f);
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model_a));
				glBindVertexArray(VAOa[i]);
				glDrawArrays(GL_LINES, 0, 2);
				glBindVertexArray(0);
			}

			glfwSwapBuffers(Env.Win);
		}
	}
	else {
		switch (Matrixes.Tumbler)
		{
		case 0: { 
			N = ColRow[0] * ColRow[1] + ColRow[2] * ColRow[3] + ColRow[4] * ColRow[5];
			VAO = new GLuint[N];
			VBO = new GLuint[N];
			EBO = new GLuint[N];
			Off.resize(N);
			Yaw.resize(N);
			glGenVertexArrays(N, VAO);
			glGenBuffers(N, VBO);
			glGenBuffers(N, EBO);

			for (int k = 0; k < 3; k++)
				for (GLuint i = 0; i < ColRow[k * 2]; i++)
					for (GLuint j = 0; j < ColRow[k * 2 + 1]; j++, l++) {
						Off[l].resize(3);
						Yaw[l].resize(3);
						glBindVertexArray(VAO[l]);
						glBindBuffer(GL_ARRAY_BUFFER, VBO[l]);
						
						if (k != 2) glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[l]);
						switch (k) {
						case 0: {
							Off[l][0] = Matrixes.MatSqu.GetFigArr(i, j)[12];
							Off[l][1] = Matrixes.MatSqu.GetFigArr(i, j)[13];
							Off[l][2] = Matrixes.MatSqu.GetFigArr(i, j)[14];
							Yaw[l][0] = Matrixes.MatSqu.GetFigArr(i, j)[15];
							Yaw[l][1] = Matrixes.MatSqu.GetFigArr(i, j)[16];
							Yaw[l][2] = Matrixes.MatSqu.GetFigArr(i, j)[17];
							glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), Matrixes.MatSqu.GetFigArr(i, j), GL_STREAM_DRAW);
							glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);						
						}; break;
						case 1: {
							Off[l][0] = Matrixes.MatRec.GetFigArr(i, j)[12];
							Off[l][1] = Matrixes.MatRec.GetFigArr(i, j)[13];
							Off[l][2] = Matrixes.MatRec.GetFigArr(i, j)[14];
							Yaw[l][0] = Matrixes.MatRec.GetFigArr(i, j)[15];
							Yaw[l][1] = Matrixes.MatRec.GetFigArr(i, j)[16];
							Yaw[l][2] = Matrixes.MatRec.GetFigArr(i, j)[17];
							glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), Matrixes.MatRec.GetFigArr(i, j), GL_STREAM_DRAW);
							glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);
						}; break;
						case 2: {
							Off[l][0] = Matrixes.MatTri.GetFigArr(i, j)[9];
							Off[l][1] = Matrixes.MatTri.GetFigArr(i, j)[10];
							Off[l][2] = Matrixes.MatTri.GetFigArr(i, j)[11];
							Yaw[l][0] = Matrixes.MatTri.GetFigArr(i, j)[12];
							Yaw[l][1] = Matrixes.MatTri.GetFigArr(i, j)[13];
							Yaw[l][2] = Matrixes.MatTri.GetFigArr(i, j)[14];
							glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(GLfloat), Matrixes.MatTri.GetFigArr(i, j), GL_STREAM_DRAW);
						}; break;
						default: break;
						}

						glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
						glEnableVertexAttribArray(0);
						glBindBuffer(GL_ARRAY_BUFFER, 0);
						glBindVertexArray(0);
					}
		} break;
		case 1: {
			N = ColRow[0] * ColRow[1];
			VAO = new GLuint[N];
			VBO = new GLuint[N];
			EBO = new GLuint[N];
			Off.resize(N);
			Yaw.resize(N);
			glGenVertexArrays(N, VAO);
			glGenBuffers(N, VBO);
			glGenBuffers(N, EBO);
			
			for (GLuint i = 0; i < ColRow[0]; i++)
				for (GLuint j = 0; j < ColRow[1]; j++, l++) {
					Off[l].resize(3);
					Yaw[l].resize(3);
					glBindVertexArray(VAO[l]);
					glBindBuffer(GL_ARRAY_BUFFER, VBO[l]);

					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[l]);
					Off[l][0] = Matrixes.MatSqu.GetFigArr(i, j)[12];
					Off[l][1] = Matrixes.MatSqu.GetFigArr(i, j)[13];
					Off[l][2] = Matrixes.MatSqu.GetFigArr(i, j)[14];
					Yaw[l][0] = Matrixes.MatSqu.GetFigArr(i, j)[15];
					Yaw[l][1] = Matrixes.MatSqu.GetFigArr(i, j)[16];
					Yaw[l][2] = Matrixes.MatSqu.GetFigArr(i, j)[17];
					glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), Matrixes.MatSqu.GetFigArr(i, j), GL_STREAM_DRAW);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);
					
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
					glEnableVertexAttribArray(0);
					glBindBuffer(GL_ARRAY_BUFFER, 0);
					glBindVertexArray(0);
				}
		} break;
		case 2: {
			N = ColRow[2] * ColRow[3];
			VAO = new GLuint[N];
			VBO = new GLuint[N];
			EBO = new GLuint[N];
			Off.resize(N);
			Yaw.resize(N);
			glGenVertexArrays(N, VAO);
			glGenBuffers(N, VBO);
			glGenBuffers(N, EBO);

			for (GLuint i = 0; i < ColRow[2]; i++)
				for (GLuint j = 0; j < ColRow[3]; j++, l++) {
					Off[l].resize(3);
					Yaw[l].resize(3);
					glBindVertexArray(VAO[l]);
					glBindBuffer(GL_ARRAY_BUFFER, VBO[l]);

					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[l]);

					Off[l][0] = Matrixes.MatRec.GetFigArr(i, j)[12];
					Off[l][1] = Matrixes.MatRec.GetFigArr(i, j)[13];
					Off[l][2] = Matrixes.MatRec.GetFigArr(i, j)[14];
					Yaw[l][0] = Matrixes.MatRec.GetFigArr(i, j)[15];
					Yaw[l][1] = Matrixes.MatRec.GetFigArr(i, j)[16];
					Yaw[l][2] = Matrixes.MatRec.GetFigArr(i, j)[17];
					glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), Matrixes.MatRec.GetFigArr(i, j), GL_STREAM_DRAW);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);


					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
					glEnableVertexAttribArray(0);
					glBindBuffer(GL_ARRAY_BUFFER, 0);
					glBindVertexArray(0);
				}
		} break;
		default: {
			N = ColRow[4] * ColRow[5];
			VAO = new GLuint[N];
			VBO = new GLuint[N];
			EBO = new GLuint[N];
			Off.resize(N);
			Yaw.resize(N);
			glGenVertexArrays(N, VAO);
			glGenBuffers(N, VBO);
			glGenBuffers(N, EBO);

			for (GLuint i = 0; i < ColRow[4]; i++)
				for (GLuint j = 0; j < ColRow[5]; j++, l++) {
					Off[l].resize(3);
					Yaw[l].resize(3);
					glBindVertexArray(VAO[l]);
					glBindBuffer(GL_ARRAY_BUFFER, VBO[l]);

					Off[l][0] = Matrixes.MatTri.GetFigArr(i, j)[9];
					Off[l][1] = Matrixes.MatTri.GetFigArr(i, j)[10];
					Off[l][2] = Matrixes.MatTri.GetFigArr(i, j)[11];
					Yaw[l][0] = Matrixes.MatTri.GetFigArr(i, j)[12];
					Yaw[l][1] = Matrixes.MatTri.GetFigArr(i, j)[13];
					Yaw[l][2] = Matrixes.MatTri.GetFigArr(i, j)[14];
					glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(GLfloat), Matrixes.MatTri.GetFigArr(i, j), GL_STREAM_DRAW);

					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
					glEnableVertexAttribArray(0);
					glBindBuffer(GL_ARRAY_BUFFER, 0);
					glBindVertexArray(0);
				}
		} break;
		}

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(0); glBindBuffer(GL_ARRAY_BUFFER, 0); glBindVertexArray(0);
		glGenVertexArrays(3, VAOa); glGenBuffers(3, VBOa);
		for (int i = 0; i < 3; i++) {
			glBindVertexArray(VAOa[i]);
			glBindBuffer(GL_ARRAY_BUFFER, VBOa[i]);
			glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), &Axis[i][0], GL_STREAM_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
		glLineWidth(3.f);

		while (!glfwWindowShouldClose(Env.Win)) {
			Env.UpdateFrames();

			glfwPollEvents();
			Do_Movement();

			//render
			glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			MyShader.Use();
			mat4 view = Cam.GetViewMatrix();
			mat4 projection = perspective(45.0f, (GLfloat)Env.w / (GLfloat)Env.h, 0.1f, 100.0f);
			GLint viewLoc = glGetUniformLocation(MyShader.GetId(), "view");
			GLint projLoc = glGetUniformLocation(MyShader.GetId(), "projection");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projection));

			//drawing
			switch (Matrixes.Tumbler)
			{
			case 0: {
				for (GLuint i = 0; i < N - ColRow[4] * ColRow[5]; i++) {
					GLint vertexColorLocation = glGetUniformLocation(MyShader.GetId(), "color");
					glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f);
					mat4 model;
					model = rotate(model, Yaw[i][0], vec3(1.0f, 0.0f, 0.0f));
					model = rotate(model, Yaw[i][1], vec3(0.0f, 1.0f, 0.0f));
					model = rotate(model, Yaw[i][2], vec3(0.0f, 0.0f, 1.0f));
					model = translate(model, vec3(Off[i][0], Off[i][1], Off[i][2]));
					GLint modelLoc = glGetUniformLocation(MyShader.GetId(), "model");
					glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

					glBindVertexArray(VAO[i]);
					glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
					glBindVertexArray(0);
				}
				for (GLuint i = N - ColRow[4] * ColRow[5]; i < N; i++) {
					GLint vertexColorLocation = glGetUniformLocation(MyShader.GetId(), "color");
					glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f);
					mat4 model;
					model = rotate(model, Yaw[i][0], vec3(1.0f, 0.0f, 0.0f));
					model = rotate(model, Yaw[i][1], vec3(0.0f, 1.0f, 0.0f));
					model = rotate(model, Yaw[i][2], vec3(0.0f, 0.0f, 1.0f));
					model = translate(model, vec3(Off[i][0], Off[i][1], Off[i][2]));
					GLint modelLoc = glGetUniformLocation(MyShader.GetId(), "model");
					glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

					glBindVertexArray(VAO[i]);
					glDrawArrays(GL_TRIANGLES, 0, 3);
					glBindVertexArray(0);
				}
			} break;
			case 3: {
				for (GLuint i = 0; i < N; i++) {
					GLint vertexColorLocation = glGetUniformLocation(MyShader.GetId(), "color");
					glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f);
					mat4 model;
					model = rotate(model, Yaw[i][0], vec3(1.0f, 0.0f, 0.0f));
					model = rotate(model, Yaw[i][1], vec3(0.0f, 1.0f, 0.0f));
					model = rotate(model, Yaw[i][2], vec3(0.0f, 0.0f, 1.0f));
					model = translate(model, vec3(Off[i][0], Off[i][1], Off[i][2]));
					GLint modelLoc = glGetUniformLocation(MyShader.GetId(), "model");
					glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

					glBindVertexArray(VAO[i]);
					glDrawArrays(GL_TRIANGLES, 0, 3);
					glBindVertexArray(0);
				}
			} break;
			default: {
				for (GLuint i = 0; i < N; i++) {
					GLint vertexColorLocation = glGetUniformLocation(MyShader.GetId(), "color");
					glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f);
					mat4 model;
					model = rotate(model, Yaw[i][0], vec3(1.0f, 0.0f, 0.0f));
					model = rotate(model, Yaw[i][1], vec3(0.0f, 1.0f, 0.0f));
					model = rotate(model, Yaw[i][2], vec3(0.0f, 0.0f, 1.0f));
					model = translate(model, vec3(Off[i][0], Off[i][1], Off[i][2]));
					GLint modelLoc = glGetUniformLocation(MyShader.GetId(), "model");
					glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

					glBindVertexArray(VAO[i]);
					glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
					glBindVertexArray(0);
				}
			} break;
			}
			
			for (int i = 0; i < 3; i++) {
				GLint vertexColorLocation = glGetUniformLocation(MyShader.GetId(), "color");
				glUniform4f(vertexColorLocation, Axis[i][0], Axis[i][1], Axis[i][2], 1.0f);
				mat4 model;
				GLint modelLoc = glGetUniformLocation(MyShader.GetId(), "model");
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
				glBindVertexArray(VAOa[i]);
				glDrawArrays(GL_LINES, 0, 2);
				glBindVertexArray(0);
			}

			glfwSwapBuffers(Env.Win);
		}
	}
	
	glDeleteVertexArrays(N, VAO);
	glDeleteBuffers(N, VBO);
	glDeleteBuffers(N, EBO);
	delete[] VAO;
	delete[] VBO;
	delete[] EBO;

	glDeleteVertexArrays(1, VAOa);
	glDeleteBuffers(1, VBOa);
	delete[] VAOa;
	delete[] VBOa;
}

void OpenGL() {
	try {
		Env.Init_GLFW(4, 0);
		Env.Init_Win("OpenGL");
		Env.Callback_Set(callback_framebuffer_size, callback_key, callback_mouse, callback_scroll);
		Env.Init_GLAD();
		Env.ApplyTests();

		Draw();
		glfwTerminate();
	}
	catch (MYERROR* e) { 
		cerr << e->what() << endl; 
		delete e;
		terminate(); 
	}
};

void MainMenu() {
	size_t MainMenuChoice = 0;
	try {
		for (;;) {
			cout
				<< "\n1. Input from console"
				<< "\n2. Input from txt"
				<< "\n3. Output to console"
				<< "\n4. Output to txt"
				<< "\n5. Random"
				<< "\n6. Change Matrix"
				<< "\n7. Input&Rand one/all"
				<< "\n8. Shell sort"
				<< "\n9. Search"
				<< "\n10. Exit"
				<< "\n11. OpenGL"
				<< "\n12. Five most distant\n\n";
			cin >> MainMenuChoice;
			switch (MainMenuChoice) {
			case 1: Matrixes.Input(false); break;
			case 2: Matrixes.Input(true); break;
			case 3: Matrixes.Output(false); break;
			case 4: Matrixes.Output(true); break;
			case 5: Matrixes.Random(); break;
			case 6: Matrixes.Tumble(); break;
			case 7: Matrixes.OnceTumble(); break;
			case 8: Matrixes.Shell(); break;
			case 9: Matrixes.Search(0); break;
			case 10: exit(0);
			case 11: OpenGL(); break;
			case 12: Matrixes.Distant(); break;
			default: throw "";
			}
		}
	}
	catch (size_t) {
		cerr << "Choice fail!\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		MainMenu();
	}
	catch (Fail) { MainMenu(); }
	catch (...) { cerr << "Unexpected error!\n"; terminate(); }
}
int main(int argc, char * argv[]) {
	srand((unsigned int)time(NULL));

	MainMenu();

	return 0;
}