/*
 * Alle headinger til Soner klassen
 */
#ifndef SONER_H
#define SONER_H
#include <map>
#include "sone.h"
using namespace std;


/*
 * Sonerklasse som holder styr på Sone klassene.
 */
class Soner {
private:
     int sisteNr = 0;     // holder styr på antall boliger som er til salgs
     //int sisteSone = 0;   // holder styr på antall soner som er registrert
     map <int, Sone*> soner;

     // Funksjoner som ikke skal brukes av main/andre klasser
     void nyttOppdrag(string valg);
     void nySone(string valg);
     void skrivAlleSoner() const;
     void skrivEttOppdrag(string valg);
     void slettOppdrag(string valg);

public:
     Soner();
     ~Soner();
     void handling(string valg);
     bool soneLeter(int sonenr);
     void lesFraFil();
     void skrivEnSone(string valg);
     void skrivTilFil();
     void skrivSoneTilFil(int soneNr, ofstream& ut);
     map <int, Sone*> soneMap();
};

#endif //SONER_H
