#include "Source.h"
#include "TFigureMatrix.h"

using namespace glm;

GLEnvironment Env;
Camera Cam(vec3(0, 3, 0));
TFigureMatrix <MyMesh> Mesh;
GLfloat RRL = 0, GRL = 0, BRL = 0;
vec3 LightPos(2), LightAmb(0.5), LightDif(0.5), LightSpc(1);

void callback_framebuffer_size(GLFWwindow* Win, int width, int height) {
	glViewport(0, 0, width, height); 
}
void callback_mouse(GLFWwindow* Win, double xpos, double ypos) {
	Cam.ProcessMouseMovement(Env.MouseX(xpos), Env.MouseY(ypos));
}
void callback_scroll(GLFWwindow* Win, double xoffset, double yoffset) {
	Cam.ProcessMouseScroll(yoffset); 
}
void processInput(GLFWwindow *Win) {
	if (glfwGetKey(Win, GLFW_KEY_ESCAPE) == GLFW_PRESS) exit(0);
	if (glfwGetKey(Win, GLFW_KEY_W) == GLFW_PRESS) Cam.ProcessKeyboard(FORWARD, Env.GetDelta());
	if (glfwGetKey(Win, GLFW_KEY_S) == GLFW_PRESS) Cam.ProcessKeyboard(BACKWARD, Env.GetDelta());
	if (glfwGetKey(Win, GLFW_KEY_A) == GLFW_PRESS) Cam.ProcessKeyboard(LEFT, Env.GetDelta());
	if (glfwGetKey(Win, GLFW_KEY_D) == GLFW_PRESS) Cam.ProcessKeyboard(RIGHT, Env.GetDelta());
	if (glfwGetKey(Win, GLFW_KEY_Q) == GLFW_PRESS) Mesh.ReadTxt();
	if (glfwGetKey(Win, GLFW_KEY_E) == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(Win, GLFW_KEY_R) == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (glfwGetKey(Win, GLFW_KEY_KP_1) == GLFW_PRESS) LightPos += vec3(0.01, 0, 0);
	if (glfwGetKey(Win, GLFW_KEY_KP_4) == GLFW_PRESS) LightPos -= vec3(0.01, 0, 0);
	if (glfwGetKey(Win, GLFW_KEY_KP_7) == GLFW_PRESS) { RRL += 0.01; LightPos += vec3(0, sin(RRL) / 100., cos(RRL) / 100.); }
	if (glfwGetKey(Win, GLFW_KEY_KP_2) == GLFW_PRESS) LightPos += vec3(0, 0.01, 0);
	if (glfwGetKey(Win, GLFW_KEY_KP_5) == GLFW_PRESS) LightPos -= vec3(0, 0.01, 0);
	if (glfwGetKey(Win, GLFW_KEY_KP_8) == GLFW_PRESS) { GRL += 0.01; LightPos += vec3(sin(GRL) / 100., 0, cos(GRL) / 100.); }
	if (glfwGetKey(Win, GLFW_KEY_KP_3) == GLFW_PRESS) LightPos += vec3(0, 0, 0.01);
	if (glfwGetKey(Win, GLFW_KEY_KP_6) == GLFW_PRESS) LightPos -= vec3(0, 0, 0.01);
	if (glfwGetKey(Win, GLFW_KEY_KP_9) == GLFW_PRESS) { BRL += 0.01; LightPos += vec3(sin(BRL) / 100., cos(BRL) / 100., 0); }
	if (glfwGetKey(Win, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) if (LightAmb.x != 0) LightAmb -= 0.01;
	if (glfwGetKey(Win, GLFW_KEY_KP_ADD) == GLFW_PRESS) if (LightAmb.x != 1) LightAmb += 0.01;
	if (glfwGetKey(Win, GLFW_KEY_KP_DIVIDE) == GLFW_PRESS) if (LightDif.x != 0) LightDif -= 0.01;
	if (glfwGetKey(Win, GLFW_KEY_KP_MULTIPLY) == GLFW_PRESS) if (LightDif.x != 1) LightDif += 0.01;
}

void Draw() {
	int DrawMenuChoice = 0, l = 1;
	try {
		while (l) {
			cout
				<< "\n0. Continue"
				<< "\n1. Input"
				<< "\n2. Random"
				<< "\n3. Console"
				<< "\n5. Exit\n";
			cin >> DrawMenuChoice;
			switch (DrawMenuChoice) {
			case 0: l = 0; break;
			case 1: Mesh.ReadTxt(); break;
			case 2: Mesh.GenRandVals(); break;
			case 3: Mesh.Show(); break;
			default: exit(0); break;
			}
		}
	}
	catch (int) {
		cerr << "Choice fail!\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		Draw();
	}
	catch (Fail) { Draw(); }
	catch (...) { cerr << "Unexpected error!\n"; terminate(); }
}
void DrawSquares(uint shader, mat4 view, mat4 projection) {
	GLfloat Vertices[] = { 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f };
	GLuint Indices[] = { 0, 1, 2, 1, 2, 3 };
	//Offset/Yaw
	vector<vector<GLfloat>> Off, Yaw;
	GLuint N = Mesh.GetN();
	Off.resize(N);
	Yaw.resize(N);
	for (int i = 0; i < N; i++) {
			Off[i].resize(3);
			Yaw[i].resize(3);
			for (__int8 k = 0; k < 3; k++) {
				Off[i][k] = Mesh.GetFigArr(i)[k]; 
				Yaw[i][k] = Mesh.GetFigArr(i)[k + 3];
			}
		}
	//Assigning
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STREAM_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//Shader
	Shader::Use(shader);
	Shader::SetMat4(shader, "view", view);
	Shader::SetMat4(shader, "projection", projection);
	Shader::SetVec3(shader, "ViewPos", Cam.Position);
	Shader::SetVec3(shader, "light.position", LightPos);
	Shader::SetVec3(shader, "light.ambient", LightAmb);
	Shader::SetVec3(shader, "light.diffuse", LightDif);
	Shader::SetVec3(shader, "light.specular", LightSpc);
	Shader::SetVec3(shader, "material.ambient", 1.0f, 0.5f, 0.31f);
	Shader::SetVec3(shader, "material.diffuse", 1.0f, 0.5f, 0.31f);
	Shader::SetVec3(shader, "material.specular", 0.5f, 0.5f, 0.5f);
	Shader::SetFloat(shader, "material.shininess", 1024.0f);
	//Drawing
	glBindVertexArray(VAO);
	for (int i = 0; i < N; i++) {
		mat4 model;
		model = rotate(model, radians(Yaw[i][0]), vec3(1.0f, 0.0f, 0.0f));
		model = rotate(model, radians(Yaw[i][1]), vec3(0.0f, 1.0f, 0.0f));
		model = rotate(model, radians(Yaw[i][2]), vec3(0.0f, 0.0f, 1.0f));
		//model = scale(model, vec3(0.5));
		model = translate(model, vec3(Off[i][0], Off[i][1], Off[i][2]));
		Shader::SetMat4(shader, "model", model);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
	//Cleaning
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
};
void DrawAxes(uint shader, mat4 view, mat4 projection) {
	GLfloat	Axis[] = { 
		1.0f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,-1.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,-1.0f 
	};
	//Assigning
	GLuint VAO_a, VBO_a;
	glGenVertexArrays(1, &VAO_a);
	glGenBuffers(1, &VBO_a);
	glBindVertexArray(VAO_a);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_a);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Axis), Axis, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	//Shader
	Shader::Use(shader);
	Shader::SetMat4(shader, "view", view);
	Shader::SetMat4(shader, "projection", projection);
	Shader::SetMat4(shader, "model", mat4());
	//Drawing
	glLineWidth(3.f);
	glBindVertexArray(VAO_a);
	Shader::SetVec3(shader, "_color", 1.0, 0.0, 0.0);
	glDrawArrays(GL_LINES, 0, 2);
	Shader::SetVec3(shader, "_color", 0.0, 1.0, 0.0);
	glDrawArrays(GL_LINES, 2, 2);
	Shader::SetVec3(shader, "_color", 0.0, 0.0, 1.0);
	glDrawArrays(GL_LINES, 4, 2);
	glBindVertexArray(0);
	//Cleaning
	glDeleteVertexArrays(1, &VAO_a);
	glDeleteBuffers(1, &VBO_a);
}
void DrawLamp(uint shader, mat4 view, mat4 projection) {
	float Vertices[] = {
		-0.1f, -0.1f, -0.1f,
		0.1f, -0.1f, -0.1f,
		0.1f,  0.1f, -0.1f,
		0.1f,  0.1f, -0.1f,
		-0.1f,  0.1f, -0.1f,
		-0.1f, -0.1f, -0.1f,

		-0.1f, -0.1f,  0.1f,
		0.1f, -0.1f,  0.1f,
		0.1f,  0.1f,  0.1f,
		0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,
		-0.1f, -0.1f,  0.1f,

		-0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f, -0.1f,
		-0.1f, -0.1f, -0.1f,
		-0.1f, -0.1f, -0.1f,
		-0.1f, -0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,

		0.1f,  0.1f,  0.1f,
		0.1f,  0.1f, -0.1f,
		0.1f, -0.1f, -0.1f,
		0.1f, -0.1f, -0.1f,
		0.1f, -0.1f,  0.1f,
		0.1f,  0.1f,  0.1f,

		-0.1f, -0.1f, -0.1f,
		0.1f, -0.1f, -0.1f,
		0.1f, -0.1f,  0.1f,
		0.1f, -0.1f,  0.1f,
		-0.1f, -0.1f,  0.1f,
		-0.1f, -0.1f, -0.1f,

		-0.1f,  0.1f, -0.1f,
		0.1f,  0.1f, -0.1f,
		0.1f,  0.1f,  0.1f,
		0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f, -0.1f,
	};
	//Assigning
	GLuint VAO_l, VBO_l;
	glGenVertexArrays(1, &VAO_l);
	glGenBuffers(1, &VBO_l);
	glBindVertexArray(VAO_l);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_l);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	//Shader
	Shader::Use(shader);
	Shader::SetMat4(shader, "view", view);
	Shader::SetMat4(shader, "projection", projection);
	mat4 model;
	model = translate(model, LightPos);
	Shader::SetMat4(shader, "model", model);
	//Drawing
	glBindVertexArray(VAO_l);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	//Cleaning
	glDeleteVertexArrays(1, &VAO_l);
	glDeleteBuffers(1, &VBO_l);
}
void DrawHand(uint shader, mat4 view, mat4 projection) {
	//Shader
	Shader::Use(shader);
	Shader::SetMat4(shader, "view", view);
	Shader::SetMat4(shader, "projection", projection);
	mat4 model;
	model = scale(model, vec3(0.05f));
	Shader::SetMat4(shader, "model", model);
	Shader::SetVec3(shader, "ViewPos", Cam.Position);
	Shader::SetVec3(shader, "light.position", LightPos);
	Shader::SetVec3(shader, "light.ambient", LightAmb);
	Shader::SetVec3(shader, "light.diffuse", LightDif);
	Shader::SetVec3(shader, "light.specular", LightSpc);
	Shader::SetVec3(shader, "material.ambient", 1.0f, 0.5f, 0.31f);
	Shader::SetVec3(shader, "material.diffuse", 1.0f, 0.5f, 0.31f);
	Shader::SetVec3(shader, "material.specular", 0.5f, 0.5f, 0.5f);
	Shader::SetFloat(shader, "material.shininess", 10.0f);
}

void OpenGL() {
	try {
		Env.InitWin(800, 600, "OpenGL");
		Env.CallbackSet(callback_framebuffer_size, nullptr, callback_mouse, callback_scroll);
		Env.InitGLAD();
		Env.ApplyTests();

		Mesh.ImportObjFile();
		uint
			ObjShader = Shader::CreateProgram("Res/vShader.versh", "Res/fShader.fragsh"),
			AxisShader = Shader::CreateProgram("Res/Axis.versh", "Res/Axis.fragsh"),
			LampShader = Shader::CreateProgram("Res/Lamp.versh", "Res/Lamp.fragsh");
		GLuint nbFrames = 0;
		GLfloat LastTime = glfwGetTime();
		//Assigning
		GLuint VAO, VBO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ARRAY_BUFFER, Mesh.Verts.size() * sizeof(vec3), Mesh.Verts.data(), GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Mesh.Indices.size() * sizeof(GLuint), Mesh.Indices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		while (!glfwWindowShouldClose(Env.GetWin())) {
			Env.UpdateFrames();

			processInput(Env.GetWin());

			mat4 view = Cam.GetViewMatrix();
			mat4 projection = perspective(45.0f, (GLfloat)Env.GetWidth() / (GLfloat)Env.GetHeight(), 0.1f, 100.0f);
			glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//Drawing
			DrawHand(ObjShader, view, projection);
			//Drawing
			glBindVertexArray(VAO);
			int loop = Mesh.Indices.size();
			//glDrawArrays(GL_TRIANGLES, 0, loop);
			glDrawElements(GL_TRIANGLES, loop, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			DrawLamp(LampShader, view, projection);
			DrawAxes(AxisShader, view, projection);
			//FPS counter
			nbFrames++;
			if (GLfloat(glfwGetTime()) - LastTime >= 1.0) {
				cout << nbFrames << " fps\n";// printf("%f ms/frame\n", 1000.0/double(nbFrames));
				cout << fixed << setprecision(0) << "["
					<< Cam.Position.x << "]:["
					<< Cam.Position.y << "]:["
					<< Cam.Position.z << "]" << endl;
				nbFrames = 0;
				LastTime += 1.0;
			}
			//Finish
			glfwSwapBuffers(Env.GetWin());
			glfwPollEvents();
		}
		//Cleaning
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);

		glfwTerminate();
	}
	catch (MYERROR* e) {
		cerr << e->what() << endl;
		delete e;
		terminate();
	}
}

int main(int argc, char * argv[]) {
	srand((unsigned int)time(NULL));
	
	OpenGL();

	return 0;
}