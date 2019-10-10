/*
	INF3105 -- Structures de données et algorithmes
	UQAM | Département d'informatique
	Automne 2019 | TP1 | polygone.h
*/

#ifndef __POLYGONE_H__
#define __POLYGONE_H__

#include <iostream>
#include "point.h"
#include "tableau.h"

class Polygone {
	public:
		//Retourne la distance minimale entre le polygone implicite et le polygone param1
		double distance(const Polygone&) const;
		//Retourne l'aire du polygone implicite
		double getAire() const;
		//Retourne le nom du polygone implicite
		std::string getNom() const;

	private:
		//calcul l'aire
		void definirAire();
		//Nom du polygone
		std::string nom;
		//Tableau dynamique listant les sommets du polygone implicite
		Tableau<Point> sommets;
		//Aire du polygone
		double aire;

	//Surcharge des opérateurs >> et <<
	//Permettent de lire et d'écrire un point sous le format " nom : ( x , y ), etc... ; "
	friend std::ostream& operator<<(std::ostream&, const Polygone&);
	friend std::istream& operator>>(std::istream&, Polygone&);

	//retourne true si l'air de param1 est inférieure à l'air de param2
	friend bool operator<(const Polygone&, const Polygone&); 
	friend bool operator==(const Polygone&, const Polygone&); 

};

#endif
 