#include "Cluster.h"

void Cluster::Tumble() {
	Tumbler++;
	if (Tumbler == 4) Tumbler = 0;
	cout << "Tumbled to " << Tumbler << endl;
};
void Cluster::OnceTumble() {
	if (Once) Once = false;
	else Once = true;
	cout << "Tumbled to " << Once << endl;
};
void Cluster::Input(bool txt) {
	if (txt) switch (Tumbler)
	{
	case 0: { MatSqu.ReadTxt("Resources/Isqu.txt"); MatRec.ReadTxt("Resources/Irec.txt"); MatTri.ReadTxt("Resources/Itri.txt");  } break;
	case 1: MatSqu.ReadTxt("Resources/Isqu.txt"); break;
	case 2: MatRec.ReadTxt("Resources/Irec.txt"); break;
	case 3: MatTri.ReadTxt("Resources/Itri.txt"); break;
	default: break;
	}
	else
		if (Once) {
			int i, j;
			try {
				cout << "i/j: \n";
				cin >> i >> j;
				if (i < 0 || j < 0) throw i;
				switch (Tumbler) {
				case 2: if (i >= MatRec.GetNColumn() || j >= MatRec.GetNRow()) throw i;
				case 3: if (i >= MatTri.GetNColumn() || j >= MatTri.GetNRow()) throw i;
				default: if (i >= MatSqu.GetNColumn() || j >= MatSqu.GetNRow()) throw i;
				}
			}
			catch (...) {
				cerr << "No such element here!\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				Input(false);
			}
			switch (Tumbler)
			{
			case 0: { Tumble(); MatSqu.ReadConOnce(i, j); } break;
			case 1: MatSqu.ReadConOnce(i, j); break;
			case 2: MatRec.ReadConOnce(i, j); break;
			case 3: MatTri.ReadConOnce(i, j); break;
			default: break;
			}
		}
		else switch (Tumbler)
		{
		case 0: { MatSqu.ReadCon(); MatRec.ReadCon(); MatTri.ReadCon(); } break;
		case 1: MatSqu.ReadCon(); break;
		case 2: MatRec.ReadCon(); break;
		case 3: MatTri.ReadCon(); break;
		default: break;
		}
};
void Cluster::Output(bool txt) {
	if (txt) switch (Tumbler)
	{
	case 0: { MatSqu.Write("Resources/Osqu.txt"); MatRec.Write("Resources/Orec.txt"); MatTri.Write("Resources/Otri.txt"); } break;
	case 1: MatSqu.Write("Resources/Osqu.txt"); break;
	case 2: MatRec.Write("Resources/Orec.txt"); break;
	case 3: MatTri.Write("Resources/Otri.txt"); break;
	default: break;
	}
	else switch (Tumbler)
	{
	case 0: { MatSqu.Show(); MatRec.Show(); MatTri.Show(); } break;
	case 1: MatSqu.Show(); break;
	case 2: MatRec.Show(); break;
	case 3: MatTri.Show(); break;
	default: break;
	}
};
void Cluster::Random() {
	if (Once) {
		int i, j;
		try {
			cout << "i/j: \n";
			cin >> i >> j;
			if (i < 0 || j < 0) throw i;
			switch (Tumbler)
			{
			case 2: if (i >= MatRec.GetNColumn() || j >= MatRec.GetNRow()) throw i;
			case 3: if (i >= MatTri.GetNColumn() || j >= MatTri.GetNRow()) throw i;
			default: if (i >= MatSqu.GetNColumn() || j >= MatSqu.GetNRow()) throw i;
			}
		}
		catch (...) {
			cerr << "No such element here!\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Random();
		}
		switch (Tumbler)
		{
		case 0: { Tumble(); MatSqu.SetRandVal(i, j); } break;
		case 1: MatSqu.SetRandVal(i, j); break;
		case 2: MatRec.SetRandVal(i, j); break;
		case 3: MatTri.SetRandVal(i, j); break;
		default: break;
		}
	}
	else switch (Tumbler)
	{
	case 0: { MatSqu.GenRandVals(); MatRec.GenRandVals(); MatTri.GenRandVals(); } break;
	case 1: MatSqu.GenRandVals(); break;
	case 2: MatRec.GenRandVals(); break;
	case 3: MatTri.GenRandVals(); break;
	default: break;
	}
};
void Cluster::Shell() {
	switch (Tumbler)
	{
	case 0: { MatSqu.Shell(); MatRec.Shell(); MatTri.Shell(); } break;
	case 1: MatSqu.Shell(); break;
	case 2: MatRec.Shell(); break;
	case 3: MatTri.Shell(); break;
	default: break;
	}
};
void Cluster::Search(int OE = 0) {
	try {
		cout << "1. Odd\n2. Even\n";
		cin >> OE;
		if (OE != 1 && OE != 2) throw OE;
	}
	catch (...) {
		cerr << "Choice fail!\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		Search(0);
	}
	switch (Tumbler)
	{
	case 0: { MatSqu.Search(OE); MatRec.Search(OE); MatTri.Search(OE); } break;
	case 1: MatSqu.Search(OE); break;
	case 2: MatRec.Search(OE); break;
	case 3: MatTri.Search(OE); break;
	default: break;
	}
};
void Cluster::Distant() {
	switch (Tumbler)
	{
	case 0: { MatSqu.FiveMostDistant(); MatRec.FiveMostDistant(); MatTri.FiveMostDistant(); } break;
	case 1: MatSqu.FiveMostDistant(); break;
	case 2: MatRec.FiveMostDistant(); break;
	case 3: MatTri.FiveMostDistant(); break;
	default: break;
	}
};