/*
	INF3105 -- Structures de données et algorithmes
	UQAM | Département d'informatique
	Automne 2019 | TP1 | point.h
*/

#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>

class Point {
	public:
		//Constructeur
		Point(double x=0, double y=0);
		//Constructeur par copie
		Point(const Point&);

		//Retourne la distance entre le point implicite (*this) et le segment formé par les points ( param1 , param2 )
		double distance(const Point&, const Point&) const;

		//Retourne un calcul permettant de calculer l'air d'un polygone
		double calculAir(const Point&) const;
	private:
		//Coordonnées du point implicite
		double x;
		double y;

	//Surcharge des opérateurs >> et <<
	//Permettent de lire et d'écrire un point sous le format " ( x , y ) "
	friend std::ostream& operator<<(std::ostream&, const Point&);
	friend std::istream& operator>>(std::istream&, Point&);
};

#endif
