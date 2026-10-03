/**
 * @file enebolig.h
 * @brief Deklarasjon av klassen Enebolig (subklasse av Bolig).
*/

#ifndef ENEBOLIG_H
#define ENEBOLIG_H
#include "bolig.h"
using namespace std;


/**
  * Enebolig-klassen inneholder ekstra data for denne spesielle typen bolig.
 */
class Enebolig : public Bolig {
     private:
     int tomtensAreal;                     // Størrelsen på tomta.
     bool selveiet;                        // Om boligen er selveiet eller ikke.
 
     public:
     Enebolig();                           // Standard konstruktør. 
 
     virtual void lesData(int bolignr);    // Leser inn data for eneboligen
                                           // fra bruker.
     virtual void skrivData() const;       // Skriver ut data for eneboligen
                                           // til bruker.
     virtual void lesFraFil(ifstream & inn);// Leser inn data for eneboligen
                                           // fra fil
     virtual void skrivTilPDF(ofstream & ut); // skriver ut leselig format til PDF
     virtual void skrivTilFil(ofstream& ut) const; 
                                           // Skriver ut data for eneboligen
                                           // til fil.
};
 
#endif //ENEBOLIG_H