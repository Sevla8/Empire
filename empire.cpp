/*
	INF3105 -- Structures de données et algorithmes
	UQAM | Département d'informatique
	Automne 2019 | TP1 | empire.cpp
*/

#include "empire.h"
#include <cmath>

//Constructeur de la classe
Empire::Empire(int n, double dm, Tableau<Polygone>& poly) : nbTerritoires(n), distanceMinimale(dm) {
	this->territoires = poly;

	//On lance la conquête
	this->conquete();

	//Trie les territoires en fonction de leur emplacement dans la carte
	this->trierNomCarte();
}

void Empire::conquete(){

	//On commence par lancer une conquête depuis chaque polygone
	for ( int i = 0 ; i < this->territoires.taille() ; i+= 1 ) {

		//Terrains qui deviendra la conquête de l'empire depuis le territoire "i"
		Tableau<Polygone> terrains;
		//On y ajoute le polygone de départ
		terrains.ajouter(this->territoires[i]);

		//On lance la conquête à partir de ce polygone
		//Avec ce 1er territoire, on en a déjà visité 1, d'où le "nbTerritoires - 1"
		terrains = this->conquerir(terrains, this->nbTerritoires - 1);

		//Si la nouvelle superficie est plus grande que l'ancienne retenue
		if ( this->superficie(this->empire) < this->superficie(terrains) )
		{
			//On sauvegarde le nouveau tableau dans 'empire'
			this->empire = terrains;
		}
	}
}

double Empire::superficie(const Tableau<Polygone>& terrains){
	//On initialise l'aire qu'on retournera
	double aire = 0;
	//On parcours tous les polygones du tableau
	for (int i = 0; i < terrains.taille(); i += 1) {
		//On additionne leur aire
		aire += terrains[i].getAire();
	}
	//On retourne la somme totale
	return aire;
}

double Empire::superficie() const {
	//On initialise l'aire qu'on retournera
	double aire = 0;
	//On parcours tous les polygones du tableau
	for (int i = 0; i < this->empire.taille(); i += 1) {
		//On additionne leur aire
		aire += this->empire[i].getAire();
	}
	//On retourne la somme totale
	return aire;
}


/*Liste dans un tableau les polygones voisins (distance < distanceMinimale)
 et encore non visité lors de la conquête de l'empire
 (on s'intéresse qu'aux nouveaux territoires => non conquéris) */
Tableau<Polygone> Empire::voisins(const Polygone& poly, const Tableau<Polygone>& dejaVu ) {
	//Tableau qu'on retournera
	Tableau<Polygone> result;

	//On vérifie pour l'ensemble des polygones de la carte
	for (int i = 0 ; i < this->territoires.taille(); i += 1) {
		
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


Tableau<Polygone> Empire::conquerir(Tableau<Polygone>& terrains, int nbT ){

	//Si on n'a plus de territoire à visiter, on s'arrête là
	if (nbT <= 0)
	{
		return terrains;
	}

	/*Le dernier territoire visité
		-> Soit là où on est est dans notre avancé de conquête*/
	int dernier = terrains.taille()-1;
	//On établie une liste de ses voisins potentiels à partir de notre position 'dernier'
	// ( le paramètre 'terrains' est le tableau des territoires déjà visités )
	Tableau<Polygone> voisins = this->voisins(terrains[dernier], terrains );

	//Tableaux qui définiera les nouvelles terres explorées
	Tableau<Polygone> nvTerres;
	//Tabelaux sauvegardant le plus haut résultat (surface maximum de l'empire)
	Tableau<Polygone> nvTerresResult = terrains;

	//Le nombre de terrains restant à visiter baisse de 1	
	nbT = nbT - 1;

	//On visite tous les terrains que l'on peut conquérir (car proche)
	for ( int i = 0 ; i < voisins.taille() ; i+= 1) {

		nvTerres = terrains;
		//nvTerres = les territoires d'origine + 1 nouveau parmi les voisins
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

void Empire::trierNomCarte(){
	//On recupère la position des terrioitoires de l'empire dans la carte (soit dans 'rritoires')
	Tableau<int> tmp;
	int tmpBis;

	for ( int i = 0 ; i < this->empire.taille() ; i+=1 ) {
		tmp.ajouter(this->territoires.trouver(this->empire[i]));
	}

	//On les ré-organise pour qu'ils apparaîssent dans le même ordre d'apparrition que la carte
	for ( int i = 0 ; i < tmp.taille() ; i+=1 ) {
		for ( int j = i ; j < tmp.taille() ; j+=1 ) {
			if ( tmp[j] < tmp[i] )
			{
				tmpBis = tmp[j];
				tmp[j] = tmp[i];
				tmp[i] = tmpBis;
			}
		}
	}

	//Et on ré-organise donc l'empire initiale
	this->empire.vider();

	for ( int i = 0 ; i < tmp.taille() ; i+=1 ) {
		this->empire.ajouter(this->territoires[tmp[i]]);
	}
}

//Pour écire un empire
std::ostream& operator<<(std::ostream& os, const Empire& emp) {
	//On affiche la superficie
	os << round(emp.superficie()) << std::endl;

	//On affiche le nom des terrioires le composant
	for (int i = 0 ; i < emp.empire.taille() ; i+= 1 ) {
		os << emp.empire[i].getNom() << std::endl ;
	}
	return os;
}