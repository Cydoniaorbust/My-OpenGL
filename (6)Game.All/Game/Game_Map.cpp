#include "Game_Map.h"

Game_Map::Game_Map() {
	_Map.resize(100);
	for (int i = 0; i < 100; i++) _Map[i].resize(100);
}
Game_Map::~Game_Map() {
	//
}

void Game_Map::Spawn(int id, int x, int y) {
	_Map[x][y] = id;
}
void Game_Map::Despawn(int x, int y) {
	_Map[x][y] = 0;
}
void Game_Map::Move(int x, int y, int a, int b) {
	_Map[x][y] = _Map[a][b];
	Despawn(a, b);
}
