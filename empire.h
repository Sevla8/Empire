/*
	INF3105 -- Structures de données et algorithmes
	UQAM | Département d'informatique
	Automne 2019 | TP1 | empire.h
*/

#ifndef __EMPIRE_H__
#define __EMPIRE_H__

#include <iostream>
#include "tableau.h"
#include "polygone.h"

class Empire {
	public:
		Empire(int n,double dm, Tableau<Polygone>& poly);

		Tableau<Polygone> proche(const Polygone& poly);	// Retourne le sous-nuage de points contenant les points à l'intérieur d'un cercle centré sur le point p et ayant un rayon de r.
	private:
		class Cellule {
			public:
				Cellule(const Polygone&, Cellule*);
				Polygone contenu;
				Cellule* suivante;
		};

		Cellule* racine;

		int nbTerritoires;
		int distanceMinimale;
		Tableau<Polygone> territoires;

		// Tableau<Cellule*> empire;
};

#endif
