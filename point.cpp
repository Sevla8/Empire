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
	return sqrt(pow(this->x - point.x, 2) + pow(this->y - point.y, 2));
}

double Point::distanceDroite(const Point& point1, const Point& point2) const {
	double a = (point2.y - point1.y) / (point2.x - point1.x);
	double b = point1.y - a * point1.x;
	return abs((a*this->x + (-1)*this->y + b) / (sqrt(pow(a, 2) + pow(-1, 2))));
}

double Point::distanceSegment(const Point& point1, const Point& point2) const {
	bool test = this->x > point1.x && this->x < point2.x || this->x > point2.x && this->x < point1.x ||
				this->y > point1.y && this->y < point2.y || this->y > point2.y && this->y < point1.y;
	return test ? this->distanceDroite(point1, point2) : fmin(this->distancePoint(point1), this->distancePoint(point2));
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
