/*
	INF3105 -- Structures de données et algorithmes
	UQAM | Département d'informatique
	Automne 2019 | TP1 | polygone.cpp
*/

#include <cmath>
#include <limits>
#include "polygone.h"

double Polygone::distance(const Polygone& poly2) const {
	double distMin = std::numeric_limits<double>::infinity();
	for (int i = 0; i < this->sommets.taille(); i += 1) {
		for (int j = 0; j < poly2.sommets.taille(); j += 1) {
			double distance = this->sommets[i].distanceSegment(poly2.sommets[j], poly2.sommets[(j+1)%poly2.sommets.taille()]);
			if (distance < distMin)
				distMin = distance;
		}
	}
	return distMin;
}

double Polygone::aire() const {
	return 1;
}

std::ostream& operator<<(std::ostream& os, const Polygone& polygone) {
	os << polygone.nom << " : ";
	for (int i = 0; i < polygone.sommets.taille()-1; i += 1)
		os << polygone.sommets[i] << ", ";
	os << polygone.sommets[polygone.sommets.taille()-1] << std::endl;
	return os;
}

std::istream& operator>>(std::istream& in, Polygone& polygone) {
	polygone.sommets.vider();
	in >> polygone.nom >> std::ws;
	char c;
	in >> c >> std::ws;
	assert(c == ':');
	do {
		Point p;
		in >> p >> c >> std::ws;
		polygone.sommets.ajouter(p);
	} while (c == ',');
	assert(c == ';');
	return in;
}
