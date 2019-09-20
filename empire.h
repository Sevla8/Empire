/*
	INF3105 -- Structures de données et algorithmes
	UQAM | Département d'informatique
	Automne 2019 | TP1 | empire.h
*/

#ifndef __EMPIRE_H__
#define __EMPIRE_H__

#include <iostream>
#include "polygone.h"
#include "tableau.h"

class Empire {
	public:

	private:
		Tableau<Polygone> zones;
};

#endif
