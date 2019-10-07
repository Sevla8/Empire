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
			/*On initialise les variables 'aireMax' et 'nom' qui seront les variables résultats
			 au 1er territoire*/
			double aireMax = territoires[0].getAire();
			string nom = territoires[0].getNom();
			//On compare avec chaque territoire du tableau pour voir si on trouve plus grand
			for (int i = 1; i < territoires.taille(); i += 1) {
				double tmp = territoires[i].getAire();
				//Plus grand ?
				if (tmp > aireMax) {
					/*Si oui, on sauvegarde l'air et le nom de ce nouveau plus grand territoire
					dans les variables 'aireMax' et 'nom' */
					aireMax = tmp;
					nom = territoires[i].getNom();
				}
			}
			//On affiche le plus grand territoire trouvé -> son aire puis son nom
			cout << round(aireMax) << endl;
			cout << nom << endl;
			break;
		}
		case 2:
		{
			assert(territoires.taille() > 0);
			double aireMax = 0;
			string noms;
			//On parcours le tableau de territoires
			for (int i = 0; i < territoires.taille(); i += 1) {
				//On parcours le tableau de territoires une 2e fois pour espérer créer un doublon
				//avec celui en position 'i' (doublons en fonction de la distance DM)
				// On initialise j = i pour éviter de comparer 2 fois la même paire
				// exemple: Si on analyse U + V, inutile d'analyser V + U
				for (int j = i; j < territoires.taille(); j += 1) {
					//Si les territoires numéros 'i'  et 'j' ne sont pas égaux
					//Que la distance qui les sépare soit inférieur à DM
					//Et que la somme de leur aire soit plus grande que la plus grande aire trouvée précédement
					if (i != j && territoires[i].distance(territoires[j]) <= DM) {
						if (territoires[i].getAire() + territoires[j].getAire() > aireMax) {
							//Si oui, on sauvegarde la somme des aires et les 2 noms des 2 territoires
							aireMax = territoires[i].getAire() + territoires[j].getAire();
							noms = territoires[i].getNom();
							noms += "\n";
							noms += territoires[j].getNom();
							noms += "\n";
						}
					}
				}
				//Dans le cas où le territoire i n'aurait pas de voisin mais aurait la plus grande aire recherchée
				if ( territoires[i].getAire() > aireMax )
				{
					aireMax = territoires[i].getAire();
					noms = territoires[i].getNom() + "\n";
				}
			}
			//On affiche le résultat
			cout << round(aireMax) << endl;
			cout << noms ;
			break;
		}
		default:
		{
			assert(territoires.taille() > 0);
			/*Création d'un empire pour gérer l'ensemble des territoires 
			On passe en paramètres le nombre de territoires recherchés, la distance minimum les séparant
			et le tableau contenant tous les territoires*/
					//Empire * empire = new Empire(nbRegions, DM, territoires);
			Empire empire(nbRegions, DM, territoires);
			
			//La méthode conquete() nous retourne la liste des territoires voulus dans un tableau
					//Tableau<Polygone> poly = empire->conquete();
			Tableau<Polygone> poly = empire.conquete();

			//On affiche la superficie totale
					//cout << round(empire->superficie(poly)) << endl;
			cout << round(empire.superficie(poly)) << endl;

			//On affiche les noms de chaques territoires du tableau
			for (int i = 0 ; i < poly.taille() ; i+= 1 ) {
				cout << poly[i].getNom() << endl ;
			}

			//On libère la mémore
			//delete empire;
			break;
		}
	}
 
	return 0;
}
