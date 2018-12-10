#pragma once

#include <map>
#include <string>
#include <exception>
#include <vector>
#include <stdlib.h>

using std::vector;

class Game_Map {
public:
	vector<vector<int>> _Map;

	Game_Map();
	~Game_Map();

	void Spawn(int, int, int);
	void Despawn(int, int);
	void Move(int, int, int, int);
};
