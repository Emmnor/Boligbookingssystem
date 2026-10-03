/**
* @file Kunder.h
* @brief Håndterer en samling av kunder i eiendomsregisteret.
*/

#ifndef KUNDER_H
#define KUNDER_H
#include "kunde.h"
#include <list>


/**
* @brief Håndterer en samling av kunder i eiendomsregisteret.
*/
class Kunder {
   private:
      int sisteNr; // Holder kontroll på brukte kundenummere
      list<Kunde*> kundeListe; //Sortert kundeliste
       

   public:
      //Konstruktør og destruktør for Kunder
      Kunder();
      ~Kunder();
      vector<int> soner;

      void nyKunde(string valg); //Leser inn fra bruker og legger til ny kunde 
      void skrivEnKunde(string valg);  // Skriver ut info om én kunde
      void skrivAlleKunder() const;  // Skriver ut info om alle kunder
      void endreKunde(string valg);  // Endrer kunde (legge til/fjerne soner)
      void slettKunde(string valg);  // Sletter kunde
      void skrivTilFil()const;  // Skriver alle kunder til fil
      void lesFraFil();  // Leser inn kunder fra fil
      void kundeOversikt(string valg); 
      void handling(string valg);
};

#endif //KUNDER_H
 
 
 
 