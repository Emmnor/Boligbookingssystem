/*
 * @file sone.h
 * @brief Inneholder alle sone headingene
 */

#ifndef SONE_H
#define SONE_H
#include "bolig.h"
#include "enum.h"
#include <string>
#include <vector>
using namespace std;


class Sone {
private:
     int nr;
     string beskrivelse;
     vector<Bolig*> boliger;
public:
     Sone();
     void leggTilBolig(enum Boligtype type, int bolignr);
     void lesData(int nr);
     void lesFraFil(ifstream & inn, int sonenr);
     void skrivData();
     void skrivDetaljertData();
     void skrivDetaljertData(ofstream & ut);
     void skrivTilFil(ofstream & ut);
     void slettBolig(int nr);
     int sonenr() const;
     vector<Bolig*> boligVector();
};

#endif
