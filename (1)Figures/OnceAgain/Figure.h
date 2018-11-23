#pragma once

#include <time.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#define RND1 (float)((rand() % 101)/500.)
#define RND2 (float)((rand() % 151-75)/100.)
#define RND3 (float)(rand() % 361)
#define SQR(x) x*x

using namespace std;

class Fail {
public:
	class SizeMatters {};
	class FailFileRead {};
};