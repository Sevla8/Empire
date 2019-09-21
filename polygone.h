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
		double distance(const Polygone&) const;
		double aire() const;
		char getNom() const;
	private:
		char nom;
		Tableau<Point> sommets;
	friend std::ostream& operator<<(std::ostream&, const Polygone&);
	friend std::istream& operator>>(std::istream&, Polygone&);
};

#endif
