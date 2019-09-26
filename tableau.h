/*
	INF3105 -- Structures de données et algorithmes
	UQAM | Département d'informatique
	Automne 2019 | TP1 | tableau.h
*/

// Ces deux lignes permettent d'éviter d'inclure 2 fois ce .h à la compilation.
#ifndef __TABLEAU_H__
#define __TABLEAU_H__

template <class T>
class Tableau {
	public:
						Tableau(int capacite_initiale = 8);
						Tableau(const Tableau&);
						~Tableau();
		void			ajouter(const T& element);					// Ajouter un element à la fin
		bool			vide() const;								// Indiquer si le tableau est vide
		void			vider();									// Vider le tableau
		int				taille() const;								// Retourne le nombre d'éléments dans le tableau
		void			inserer(const T& element, int index = 0);	// Insère element à position index. Les éléments à partir de index sont décalés d'une position.
		void			enlever(int index = 0);						// Enlève l'element à position index. Les éléments après index sont décalés d'une position.
		void			enlever_dernier();							// Enlève le dernier élément
		int				trouver(const T& element) const;			// Cherche et retourne la position de l'élément. Si non trouvé, retourne -1.
		bool			contient(const T& element) const;			// Indique si le tableau contient l'élément
		T&				operator[](int index);						//return l'élément à la position index
		const T&		operator[](int index) const;				//idem, mais en lecture seule
		Tableau<T>&		operator=(const Tableau<T>& autre);			//surcharge de l'opérateur =
		bool			operator==(const Tableau<T>& autre) const;	//surcharge de l'opérateur ==
	private:
		T*				elements;
		int				capacite;
		int				nbElements;
	//friend void trier<T>(Tableau<T>& tab);
};

/*
 Puisque Tableau<T> est une classe générique, toutes ses définitions doivent être
 inclues après les déclarations. On peut quand même séparer les déclarations et
 les définitions en deux fichiers (tableau.h et tableau.hcc), à condition d'inclure le
 deuxième (tableau.hcc) à la fin du premier (tableau.h). Ainsi, un fichier source
 (.cc, .cpp, c++) qui inclut tableau.h inclura indirectement aussi tableau.hcc.

*/

//#include "tableau.hcc"
/**** Début des définitions pouvant être mises dans tableau.hcc. ****/

#include <assert.h>

template <class T>
Tableau<T>::Tableau(int capacite_initiale) : capacite(capacite_initiale), nbElements(0) {
	this->elements = new T[this->capacite];
}

template <class T>
Tableau<T>::Tableau(const Tableau& autre) : capacite(autre.capacite), nbElements(autre.nbElements) {
	this->elements = new T[this->capacite];
	for (int i = 0; i < this->nbElements; i += 1)
		this->elements[i] = autre.elements[i];
}

template <class T>
Tableau<T>::~Tableau() {
	delete[] elements;
}

template <class T>
void Tableau<T>::ajouter(const T& item) {
	if (this->nbElements >= this->capacite) {
		if (this->capacite == 0)
			this->capacite = 2;
		this->capacite *= 2;
		T* temp = new T[this->capacite];
		for (int i = 0; i < this->nbElements; i += 1)
			temp[i] = this->elements[i];
		delete [] this->elements;
		this->elements = temp;
	}
	this->elements[this->nbElements++] = item;
}

template <class T>
bool Tableau<T>::vide() const {
	return this->nbElements == 0;
}

template <class T>
void Tableau<T>::vider() {
	this->nbElements = 0;
}

template <class T>
int Tableau<T>::taille() const {
	return this->nbElements;
}

template <class T>
void Tableau<T>::inserer(const T& element, int index) {
	assert(index <= this->nbElements);
	if (this->nbElements >= this->capacite) {
		if (this->capacite == 0)
			this->capacite = 2;
		this->capacite *= 2;
		T* temp = new T[this->capacite];
		for (int i = 0; i < index; i += 1)
			temp[i] = this->elements[i];
		temp[index] = element;
		for (int i = index; i < this->nbElements; i += 1)
			temp[i+1] = this->elements[i];
		delete [] this->elements;
		this->nbElements += 1;
		this->elements = temp;
	}
	else {
		for (int i = this->nbElements; i > index; i -= 1)
			this->elements[i] = this->elements[i-1];
		this->elements[index] = element;
		this->nbElements += 1;
	}
}

template <class T>
void Tableau<T>::enlever(int index){
	assert(this->nbElements > 0);
	this->nbElements -= 1;
	for (int i = index; i < this->nbElements; i += 1)
		this->elements[i] = this->elements[i+1];
}

template <class T>
void Tableau<T>::enlever_dernier() {
	assert(this->nbElements > 0);
	this->nbElements -= 1;
}

template <class T>
int Tableau<T>::trouver(const T& element) const {
	for (int i = 0; i < this->nbElements; i += 1)
		if (this->elements[i] == element)
			return i;
	return -1;
}

template <class T>
bool Tableau<T>::contient(const T& element) const {
	return this->trouver(element) != -1;
}

template <class T>
T& Tableau<T>::operator[](int index) {
	assert(index < this->nbElements && index >= 0);
	return this->elements[index];
}

template <class T>
const T& Tableau<T>::operator[](int index) const {
	assert(index < this->nbElements && index >= 0);
	return this->elements[index];
}

template <class T>
Tableau<T>& Tableau<T>::operator=(const Tableau<T>& autre) {
	if (this == &autre)
		return *this;
	this->nbElements = autre.nbElements;
	if (this->capacite < autre.nbElements || autre.nbElements*2 < this->capacite) {
		delete[] this->elements;
		this->capacite = autre.capacite;
		this->elements = new T[capacite];
	}
	for (int i = 0; i < this->nbElements; i += 1)
		this->elements[i] = autre.elements[i];
	return *this;
}

template <class T>
bool Tableau<T>::operator==(const Tableau<T>& autre) const {
	if (this == &autre)
		return true;
	if (this->nbElements != autre.nbElements)
		return false;
	for (int i = 0; i < this->nbElements; i += 1)
		if (elements[i] != autre.elements[i])
			return false;
	return true;
}

/*
#include <algorithm>
template <class T>
void trier<T>(Tableau<T>& tab){
	std::sort(tab.elements, tab.elements+tab.nbElements);
}
*/

#endif
