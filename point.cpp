/*
	INF3105 -- Structures de données et algorithmes
	UQAM | Département d'informatique
	Automne 2019 | TP1 | point.cpp
*/

#include <assert.h>
#include <math.h>
#include "point.h"

Point::Point(const Point& point) : x(point.x), y(point.y) {}

Point::Point(double _x, double _y) : x(_x), y(_y) {}

double Point::distancePoint(const Point& point) const {
	//Pythagore : AC = racine de ( AB² + BC² )
	return sqrt(pow(this->x - point.x, 2) + pow(this->y - point.y, 2));
}

double Point::distanceDroite(const Point& point1, const Point& point2) const {
	/*pour une droite ayant comme equation, d:y=ax+b
	  et pour un point ayant comme coordonnée, P(xp, yp)
	  Le calcul de la distance de ce point par rappport à cette droite est 
	  abs( (a*xp - yp + b) / (sqrt(a² + 1²)) ) 

	  source du calcul : https://lexique.netmath.ca/distance-entre-un-point-et-une-droite/
	*/
	double a = (point2.y - point1.y) / (point2.x - point1.x);
	double b = point1.y - a * point1.x;
	return fabs((a*this->x - this->y + b) / (sqrt(pow(a, 2) + 1 )));
}

double Point::distanceSegment(const Point& point1, const Point& point2) const {
	/* Si l'abscisse du point implicite n'est pas compris entre les abscisses des deux extrémités du segment, formé par param1 et param2
	   ou l'ordonnée du point implicite n'est pas comprise entre les ordonnées des deux extrémités du segment, formé par param1 et param2

	   Alors la distance entre le point implicite et le segment formé par param1 et param2 est le minimum entre :
	   la distance entre le point implicite et param1
	   et
	   la distance entre le point implicite et param2

	   Sinon
		la distance entre le point implicite et le segment formé par param1 et param2 est la distance entre :
		le point implicite et la droite formée par param1 et param2
	*/
	bool test = (this->x > point1.x && this->x < point2.x) || (this->x > point2.x && this->x < point1.x) ||
				(this->y > point1.y && this->y < point2.y) || (this->y > point2.y && this->y < point1.y);
	return test ? this->distanceDroite(point1, point2) : fmin(this->distancePoint(point1), this->distancePoint(point2));
}

double Point::calculAir(const Point& point) const {
	/*retourne le produit de :
		  la somme de l'abscisse du point implicite et de l'abscisse de param1 
		  avec 
		  la différence entre l'ordonnée du point implicite et l'ordonnée de param1

	source : http://www.mathopenref.com/coordpolygonarea2.html */
	return (point.x + this->x) * (point.y - this->y);
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
	os << "(" << point.x << "," << point.y << ")";
	return os;
}

std::istream& operator>>(std::istream& is, Point& point) {
	char po, vir, pf;
	is >> po;
	if (is) {
		is >> point.x >> vir >> point.y >> pf;
		assert(po=='(');
		assert(vir==',');
		assert(pf==')');
	}
	return is;
}
