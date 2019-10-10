/*
	INF3105 -- Structures de données et algorithmes
	UQAM | Département d'informatique
	Automne 2019 | TP1 | polygone.cpp
*/

#include <cmath>
#include <limits>
#include "polygone.h"

double Polygone::distance(const Polygone& poly2) const {
	//Initialise la distance minale (distMin) a l'infini.
	double distMin = std::numeric_limits<double>::infinity();

	//Compare la distance de tous les sommets du polygone implicte avec tous les segments de poly2
	//ne retient que la plus petite distance dans distMin
	for (int i = 0; i < this->sommets.taille(); i += 1) {
		for (int j = 0; j < poly2.sommets.taille(); j += 1) {
			double distance;
			//Regarde la distance minimale entre 2 segments appartenant à deux polygones
			//Distance sommet 1 de polygone 1 au segment de polygone 2 
			distance = this->sommets[i].distance(poly2.sommets[j], poly2.sommets[(j+1)%poly2.sommets.taille()]);
			if (distance < distMin)
				distMin = distance;
			//Distance sommet 2 de polygone 1 au segment de polygone 2
			distance = this->sommets[(i+1)%this->sommets.taille()].distance(poly2.sommets[j], poly2.sommets[(j+1)%poly2.sommets.taille()]);
			if (distance < distMin)
				distMin = distance;
			//Distance sommet 1 de polygone 2 au segment de polygone 1
			distance = poly2.sommets[j].distance(this->sommets[i], this->sommets[(i+1)%this->sommets.taille()]);
			if (distance < distMin)
				distMin = distance;
			//Distance sommet 2 de polygone 2 au segment de polygone 1
			distance = poly2.sommets[(j+1)%poly2.sommets.taille()].distance(this->sommets[i], this->sommets[(i+1)%this->sommets.taille()]);
			if (distance < distMin)
				distMin = distance;
		}
	}
	//On retourne la plus petite valeur trouvée
	return distMin;
}

double Polygone::getAire() const{
	return this->aire;
}

std::string Polygone::getNom() const {
	return this->nom;
}

void Polygone::definirAire() {
	//Source du calcul : http://www.mathopenref.com/coordpolygonarea2.html
	double aire = 0;
	for (int i = 0; i < this->sommets.taille(); i += 1)
		aire += this->sommets[(i+1)%this->sommets.taille()].calculAir(this->sommets[i]);

	//Avec calculAir() = (point.x + this->x) * (point.y - this->y);

	//On sauvegarde l'air calculé dans l'attribut 'air' pour ne plus l'avoir à calculer
	this->aire = fabs(aire/2);
}

//Pour écire un polygone
std::ostream& operator<<(std::ostream& os, const Polygone& polygone) {
	os << polygone.nom << " : ";
	for (int i = 0; i < polygone.sommets.taille()-1; i += 1)
		os << polygone.sommets[i] << ", ";
	os << polygone.sommets[polygone.sommets.taille()-1] << " ;"<<  std::endl;
	return os;
}

//Pour lire un polygone
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

	//On calcule l'aire
	polygone.definirAire();

	return in;
}

//Pour comparer deux polygones on compare leur aire
bool operator<(const Polygone& poly1, const Polygone& poly2) {
	return poly1.getAire() < poly2.getAire() ? true : false;
}

//On estime que deux Polygones sont égaux lorsqu'ils ont le même nom
bool operator==(const Polygone& poly1, const Polygone& poly2) {
	return poly1.getNom() == poly2.getNom() ? true : false;
}
