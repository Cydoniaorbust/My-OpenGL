#include "Game.h"

Game::Game() : State(GAME_ACTIVE), Keys(), Width(0), Height(0), Manager() {}
Game::Game(GLuint width, GLuint height) : Game() {
	Width = width;
	Height = height;
}
Game::~Game() {}

void Game::Init(SpriteRenderer &renderer) {
	Manager.LoadShader("Res/sprite.vs", "Res/sprite.fg", "sprite");

	glm::mat4 projection = glm::ortho(
		0.0f, 
		static_cast<GLfloat>(Width), 
		static_cast<GLfloat>(Height), 
		0.0f, -1.0f, 1.0f
	);
	Manager.GetShader("sprite").Use();
	Manager.GetShader("sprite").SetInt("image", 0);
	Manager.GetShader("sprite").SetMat4("projection", projection);

	renderer = SpriteRenderer(Manager.GetShader("sprite"));

	Manager.LoadTexture("Res/awesome.png", GL_TRUE, "face");
}
void Game::Update(GLfloat dt) {}
void Game::ProcessInput(GLfloat dt) {}
void Game::Render(SpriteRenderer renderer) {
	renderer.DrawSprite(Manager.GetTexture("face"), glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}