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


double Point::distance(const Point& point1, const Point& point2) const {
	//Algorithme donné dans le sujet
	double ratio = (this->x - point1.x) * (point2.x - point1.x) + (this->y - point1.y) * (point2.y - point1.y); 
	ratio /= (pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));

	if (ratio > 1)
		ratio = 1;
	else if (ratio < 0)
		ratio = 0;

	double x = ratio * (point2.x - point1.x);
	double y = ratio * (point2.y - point1.y);
	Point v(x, y);

	x = point1.x + v.x;
	y = point1.y + v.y;
	Point p(x, y);

	return sqrt(pow(p.x - this->x, 2) + pow(p.y - this->y, 2));
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
