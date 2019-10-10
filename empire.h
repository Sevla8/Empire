/*
	INF3105 -- Structures de données et algorithmes
	UQAM | Département d'informatique
	Automne 2019 | TP1 | empire.h
*/

#ifndef __EMPIRE_H__
#define __EMPIRE_H__

#include <iostream>
#include "tableau.h"
#include "polygone.h"

class Empire {
	public:
		/*Crée un Empire en fonction du nombre de territoire cherchés -> n
		De la distance minimale les séparants -> dm
		Le tableau contenant tous les territoires -> poly*/
		Empire(int n,double dm, Tableau<Polygone>& poly);
		
		private:

		/*Retourne la superficie d'un tableau de Polygones résultant
		de la somme des aires des polygones le composant*/
		double superficie(const Tableau<Polygone>& terrains);
		//Renvoie la superficie de l'instance grâce à son attribut 'empire' sans le mofidifer
		double superficie() const;
		
		/* Retourne un tableau de polygones étant à une distance suffisamment proches (en fonction de 'distanceMinimale')
		et n'ayant toujours pas été visité par la méthode conquerir() qui parcours les territoires proches*/
		//dejaVu -> ensemble des polygones déjà visité dans un tableau
		Tableau<Polygone> voisins(const Polygone& poly, const Tableau<Polygone>& dejaVu );

		/*Parcours le maximum de territoires possibles en commençant par chaque territoire
		Pour déterminer le plus grand Empire possible en fonction des attributs de l'objet*/
		//nbT => nombre Territoire -> désigne le nombre de territoires restant à visiter
		Tableau<Polygone> conquerir(Tableau<Polygone>& terrains, int nbT );

		//Lance la conquête de l'empire
			/*Trouve le tableau de Polygone à la plus grande superficie en fonction 
			des attributs de l'objet*/
		//Place de résultat dans l'attribut 'empire'
		void conquete();

		//Trie les territoires obtenue en fonction de leur place dans la carte
		//Pour être en accord avec le résultat demandé par le correcteur
			//Exemple: Si résultat demandé -> N,M,R et résultat obtenue -> R,N,M => indique un échec
		void trierNomCarte();

		//Nombre de territoires à visiter
		int nbTerritoires;
		//Distance minimale séparant 2 Polygones / Territoires
		double distanceMinimale;
		//Tableaux composés de tous les polygones de la carte en totalité
		Tableau<Polygone> territoires;
		//Tableau résulat (l'empire demandé en correction)
		Tableau<Polygone> empire;

		//Surcharge de ' opérateurs <<
		friend std::ostream& operator<<(std::ostream&, const Empire&);
};

#endif
