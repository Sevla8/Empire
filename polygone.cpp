/*
  INF3105 -- Structures de données et algorithmes
  UQAM | Département d'informatique
  Automne 2019 | TP1 | polygone.cpp
*/

#include <cmath>
#include <limits>
#include "polygone.h"

double Polygone::distance(const Polygone& poly2) const
{
    return 0;
}

double Polygone::aire() const{
    return 1;
}

std::ostream& operator << (std::ostream& os, const Polygone& polygone){
    // À compléter.
    os << "A : (0,0), (0,1), (1,1) ;";
    return os;
}

std::istream& operator >> (std::istream& in, Polygone& polygone){
    // À compléter­.
    char c;
    do{
        Point p;
        in >> p >> c >> std::ws;
    }while(c==',');
    assert(c==';');
    return in;
}

