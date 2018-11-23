#pragma once

#include "TFigureMatrix.h"

class Cluster {
public:
	TFigureMatrix <Square> MatSqu;
	TFigureMatrix <Rectangular> MatRec;
	TFigureMatrix <Triangle> MatTri;
	int Tumbler = 0;
	bool Once = false;

	void Tumble();
	void OnceTumble();
	void Input(bool);
	void Output(bool);
	void Random();
	void Shell();
	void Search(size_t);
	void Distant();
};