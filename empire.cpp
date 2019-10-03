/*
	INF3105 -- Structures de données et algorithmes
	UQAM | Département d'informatique
	Automne 2019 | TP1 | empire.cpp
*/

#include "empire.h"

//Constructeur de la classe
Empire::Empire(int n, double dm, Tableau<Polygone>& poly) : nbTerritoires(n), distanceMinimale(dm), terrVisit(0) {
	this->territoires = poly;
}

//Empire::~Empire() {}

//Liste dans un tableau les polygones voisins (distance < distanceMinimale) et encore non visité d'un polygone (poly)
Tableau<Polygone> Empire::voisins(const Polygone& poly, const Tableau<Polygone> dejaVu ) {
	//Tableau qu'on retournera
	Tableau<Polygone> result;

	//On vérifie pour l'ensemble des polygones
	/*Tous les empires possibles contenant un terrioire se trouvant avant la position this->terrVisit
	dans le tableau this->territoires ont déjà été testés*/
	for (int i = this->terrVisit ; i < this->territoires.taille(); i += 1) {
		
		/*Si le polygone "i" est suffisamment proche
		Et si encore non visité */
		if (poly.distance(this->territoires[i]) <= this->distanceMinimale && !dejaVu.contient(this->territoires[i]))
		{
			//Alors on le rajoute dans la liste des territoires voisins potentiels
			result.ajouter(this->territoires[i]);
		}
	}	
	return result;
}

double Empire::superficie(Tableau<Polygone> terrains){
	//On initialise l'aire qu'on retournera
	double aire = 0;
	//On parcours tous les polygones du tableau
	for (int i = 0; i < terrains.taille(); i += 1) {
		//On additionne leur aire
		aire += terrains[i].aire();
	}
	//On retourne la somme totale
	return aire;
}

Tableau<Polygone> Empire::conquete(){

	//Création du tableau qu'on retournera en sortie
	Tableau<Polygone> result;

	//On commence par lancer une conquête depuis chaque polygone
	for ( this->terrVisit = 0 ; this->terrVisit < this->territoires.taille() ; this->terrVisit+= 1 ) {

		//Terrains qui deviendra la conquête de l'empire depuis le territoire "this->terrVisit"
		Tableau<Polygone> terrains;
		//On y ajoute le polygone de départ
		terrains.ajouter(this->territoires[this->terrVisit]);

		//On lance la conquête à partir de ce polygone
		//Avec ce 1er territoire, on en a donc déjà visité 1, d'où le "nbTerritoires - 1"
		terrains = this->conquerir(terrains, this->nbTerritoires - 1);

		//Si la nouvelle superficie est plus grande que l'ancienne retenue
		if ( this->superficie(result) < this->superficie(terrains) )
		{
			//On sauvegarde le nouveau tableau
			result = terrains;
		}
	}

	//On retourne le tableau obtenu
	return result;
}

Tableau<Polygone> Empire::conquerir(Tableau<Polygone> terrains, int nbT ){

	//Si on n'a plus de territoire à visiter, on s'arrête là
	if (nbT <= 0)
		return terrains;

	/*Le dernier territoire visité
	-> Soit là où on est est dans notre conquête*/
	int dernier = terrains.taille()-1;
	//On établie une liste de ses voisins potentiels
	Tableau<Polygone> voisins = this->voisins(terrains[dernier], terrains );

	//Tableaux qui définiera les nouvelles terres explorées
	Tableau<Polygone> nvTerres;
	//TAbelaux sauvegardant le plus haut résulat
	Tableau<Polygone> nvTerresResult = terrains;

	//Nombre de terrains à visiter baisse de 1	
	nbT = nbT - 1;

	//On visite tous les terrains que l'on peut conquérir
	for ( int i = 0 ; i < voisins.taille() ; i+= 1) {

		//nvTerres = territoire d'origine + 1 nouveau voisin
		nvTerres = terrains;
		nvTerres.ajouter(voisins[i]);

		//On explore à partir de ce voisin
		nvTerres = this->conquerir(nvTerres,nbT);

		//Si la superfice obtenue est supérieur à la superfice précédente
		if ( this->superficie(nvTerres) > this->superficie(nvTerresResult) )
			//On la sauvegarde
			nvTerresResult = nvTerres;
	}

	//On retourne le tableaux de territoires obtenu
	return nvTerresResult;
}