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
		Point(){}
		Point(double x, double y);
		Point(const Point&);
		double distanceSegment(const Point&, const Point&) const;
		double calcul(const Point&) const;
	private:
		double x;
		double y;
		double distancePoint(const Point&) const;
		double distanceDroite(const Point&, const Point&) const;
	friend std::ostream& operator<<(std::ostream&, const Point&);
	friend std::istream& operator>>(std::istream&, Point&);
};

#endif
