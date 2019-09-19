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
		double distance(const Point&) const;
	private:
    	double x;
    	double y;
	friend std::ostream& operator<<(std::ostream&, const Point&);
	friend std::istream& operator>>(std::istream&, Point&);
};

#endif
