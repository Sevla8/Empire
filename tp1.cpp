/*
	INF3105 -- Structures de données et algorithmes
	UQAM | Département d'informatique
	Automne 2019 | TP1 | tp1.cpp
*/

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <limits>
#include "polygone.h"
#include "tableau.h"
#include "empire.h"

using namespace std;

int main(int argc, const char** argv) {
	if (argc < 3) {
		cout << "./tp1 carte.txt nbRegions [distMax]" << endl;
		return 1;
	}

	const char* fichierCarte = argv[1];
	int nbRegions = atoi(argv[2]);
	double DM = argc >= 4 ? atof(argv[3]) : numeric_limits<double>::infinity();
	assert(DM >= 0);

	ifstream in(fichierCarte);
	if (in.fail()) {
		cout << "Imposible de lire le fichier " << fichierCarte << endl;
		return 2;
	}

	Tableau<Polygone> territoires;
	while (!in.eof()) {
		string nom;
		Polygone polygone;
		in >> polygone >> std::ws;
		territoires.ajouter(polygone);
	}

	switch (nbRegions) {
		case 1:
		{
			assert(territoires.taille() > 0);
			double aireMax = territoires[0].aire();
			string nom = territoires[0].getNom();
			for (int i = 0; i < territoires.taille(); i += 1) {
				double tmp = territoires[i].aire();
				if (tmp > aireMax) {
					aireMax = tmp;
					nom = territoires[i].getNom();
				}
			}
			cout << round(aireMax) << endl;
			cout << nom << endl;
			break;
		}
		case 2:
		{
			assert(territoires.taille() > 0);
			double aireMax = 0;
			string noms;
			for (int i = 0; i < territoires.taille(); i += 1) {
				for (int j = 0; j < territoires.taille(); j += 1) {
					if (i != j && territoires[i].distance(territoires[j]) <= DM) {
						if (territoires[i].aire() + territoires[j].aire() > aireMax) {
							aireMax = territoires[i].aire() + territoires[j].aire();
							noms = territoires[i].getNom();
							noms += "\n";
							noms += territoires[j].getNom();
							noms += "\n";
						}
					}
				}
				if ( territoires[i].aire() >= aireMax )
				{
					aireMax = territoires[i].aire();
					noms = territoires[i].getNom() + "\n";
				}
			}
			cout << round(aireMax) << endl;
			cout << noms << endl;
			break;
		}
		default:
		{
			Empire	empire(nbRegions, DM, territoires);
			// cout << "Ce programme ne supporte pas 3 régions ou plus!" << endl;
			break;
		}
	}

	return 0;
}
