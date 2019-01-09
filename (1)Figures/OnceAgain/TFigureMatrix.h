#pragma once 

#include "Square.h"
#include "Triangle.h"
#include "Rectangular.h"

#define MIN_val 0.005

template <class figure>
class TFigureMatrix {
	int NColumn = 8, NRow = 8;
	vector<vector<figure>> array;
	ifstream fin;
	ofstream fout;
public:
	TFigureMatrix() {
		array.resize(NColumn);
		for (int i = 0; i < NColumn; i++)
			array[i].resize(NRow);
	};

	int GetNRow() { return NRow; };
	int GetNColumn() { return NColumn; };
	float* GetFigArr(int i, int j) { return array[i][j].GetFig(); };

	void Num() {
		class SizeMatters {};
		try {
			cin >> NColumn >> NRow;
			if (NColumn > NRow) throw SizeMatters();
			array.resize(NColumn);
			for (int i = 0; i < NColumn; i++)
				array[i].resize(NRow);
		}
		catch (SizeMatters) {
			cerr << "Columns must not be greater than Rows!\n";
			Num();
		}
		catch (...) {
			cerr << "Used non-digit symbols!\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Num();
		}
	};

	void ReadConOnce(int i, int j) {
		try {
			cin >> array[i][j];
			if (array[i][j].S() < MIN_val) throw i;
		}
		catch (int) {
			cerr << "Figure is too small!\n";
			ReadConOnce(i, j);
		}
		catch (...) {
			cerr << "Used non-digit symbols!\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			ReadConOnce(i, j);
		}
	};
	void SetRandVal(int i, int j) {
		try {
			array[i][j].Rnd();
			if (array[i][j].S() < MIN_val) throw i, j;
		}
		catch (...) { SetRandVal(i, j); }
	};
	void ReadCon() {
		Num();
		array.resize(NColumn);
		for (int i = 0; i < NColumn; i++) {
			array[i].resize(NRow);
			for (int j = 0; j < NRow; j++)
				ReadConOnce(i, j);
		}
	};
	void ReadTxt(const char input[]) {
		fin.open(input);
		char delim;
		try {
			fin >> delim;
			if (delim != 'd') throw Fail::FailFileRead();
			fin >> NColumn >> NRow;
			if (NColumn > NRow) throw Fail::SizeMatters();
			array.resize(NColumn);
			for (int i = 0; i < NColumn; i++) {
				array[i].resize(NRow);
				for (int j = 0; j < NRow; j++)
					fin >> array[i][j];
			}
		}
		catch (Fail::SizeMatters) {
			cerr << "Columns must not be greater than Rows!\n";
			NColumn = 3;
			NRow = 3;
			fin.clear();
			fin.ignore(numeric_limits<streamsize>::max(), '\n');
			fin.close();
			throw Fail();
		}
		catch (...) {
			cerr << "Failed to read from file!\n";
			fin.clear();
			fin.ignore(numeric_limits<streamsize>::max(), '\n');
			fin.close();
			throw Fail();
		}
		fin.close();
	};
	void Show() {
		for (int i = 0; i < NColumn; i++) {
			for (int j = 0; j < NRow; j++)
				cout << array[i][j];
			cout << endl;
		}
		cout << endl;
	};
	void Write(const char output[]) {
		fout.open(output);
		fout << "d " << NColumn << " " << NRow;
		for (int i = 0; i < NColumn; i++)
			for (int j = 0; j < NRow; j++)
				fout << array[i][j];
		fout.close();
	};
	void GenRandVals() {
		Num();
		for (int i = 0; i < NColumn; i++)
			for (int j = 0; j < NRow; j++)
				SetRandVal(i, j);
	};

	double AverageP(int i) {
		double AP = 0.0;
		for (int j = 0; j < NRow; j++)
			AP += array[i][j].P();
		return AP / NRow;
	};
	double AverageS(int i) {
		double AS = 0.0;
		for (int j = 0; j < NRow; j++)
			AS += array[i][j].S();
		return AS / NRow;
	};
	void Shell() {
		int i, j, d = NColumn;
		d = d / 2;
		while (d > 0) {
			for (i = 0; i < NColumn - d; i++) {
				j = i;
				while (j >= 0 && AverageS(j) > AverageS(j + d)) {
					swap(array[j], array[j + d]);
					j--;
				}
			}
			d = d / 2;
		}
	};
	void Search(int k) {
		double l = 0.0;
		int h = 0;
		for (int i = 0; i < NColumn; i++)
			if ((i + k) % 2 == 0) {
				l += AverageP(i);
				h++;
			}
		l = l / h;
		cout << l << "\n";
		for (int i = 0; i < NColumn; i++)
			for (int j = 0; j < NRow; j++)
				if (array[i][j].P() > l)
					cout << "[" << i << ";" << j << "] : " << array[i][j] << endl << array[i][j].P() << endl;
	};
	void FiveMostDistant() {
		cout << "P:\n";
		float P;
		try {
			cin >> P;
			if (P < 0) throw P;
		}
		catch (int) {
			cerr << "Cannot be less than zero!\n";
			FiveMostDistant();
		}
		catch (...) {
			cerr << "Used non-digit symbols!\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			FiveMostDistant();
		}
		int N = NColumn * NRow;
		vector<vector<float>> arr;
		arr.resize(N);
		for (int i = 0, l = 0; i < NColumn; i++)
			for (int j = 0; j < NRow; j++, l++) {
				arr[l].resize(4);
				arr[l][0] = array[i][j].D();
				arr[l][1] = array[i][j].P();
				arr[l][2] = (float)i;
				arr[l][3] = (float)j;
			}
		
		for (int gap = N / 2; gap > 0; gap /= 2)
			for (int i = gap; i < N; i++)
				for (int j = i - gap; j >= 0 && arr[j][0] > arr[j + gap][0]; j -= gap) swap(arr[j], arr[j + gap]);
		
		for (int i = 0, l = 0; i < NColumn; i++) 
			for (int j = 0; j < NRow; j++, l++)
				cout << fixed << setprecision(4)
				<< arr[l][0] << " "
				<< arr[l][1] << " " << setprecision(0)
				<< arr[l][2] << " "
				<< arr[l][3] << " " << endl;
		cout << endl;
		
		int NN = 0;
		for (int i = N-1; i > 0; i--)
			if (arr[i][1] > P) {
				NN++;
				cout << fixed << setprecision(4)
					<< arr[i][0] << " "
					<< arr[i][1] << " " << setprecision(0)
					<< arr[i][2] << " "
					<< arr[i][3] << " " << endl;
				if (NN == 5) break;
			}
	};
};