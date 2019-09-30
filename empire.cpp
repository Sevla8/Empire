/*
	INF3105 -- Structures de données et algorithmes
	UQAM | Département d'informatique
	Automne 2019 | TP1 | empire.cpp
*/

#include "empire.h"

Empire::Empire(int n, double dm, Tableau<Polygone>& poly) : nbTerritoires(n), distanceMinimale(dm) {
	this->territoires = poly;
}

Tableau<Polygone> Empire::proche(const Polygone& poly) {
	Tableau<Polygone> result;
	for (int i = 0; i < this->territoires.taille(); i += 1) {
		if (poly.distance(this->territoires[i]) < this->distanceMinimale)
			result.ajouter(this->territoires[i]);
	}
	return result;
}
