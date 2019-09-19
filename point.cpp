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

double Point::distance(const Point& point) const {
	return sqrt(pow(this->x - point.x, 2) + pow(this->y - point.y, 2));
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
