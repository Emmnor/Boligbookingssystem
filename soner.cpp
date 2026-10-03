/*
 * @file soner.cpp
 * @brief Inneholder alle funksjonsinmat til soner
 */

#include <iostream>
#include <fstream>
#include "soner.h"
#include "const.h"
#include "LesData3.h"


/*
 * Constructor som initialiserer siste nr til 0.
 */
Soner::Soner() {
     sisteNr = 0;
}

/*
 * Destructor som sletter alle pekerne som er allokert og tømmer soner map-en
 */
Soner::~Soner() {
     for (auto & s : soner) {
          delete s.second;
     }
     soner.clear();
}

/*
 * Funksjon for å hente ut sone map
 *
 * @return: returnerer sone map
 */
map <int, Sone*> Soner:: soneMap() {
     return soner;
}

/*
 * Main som håndterer valgene S og O
 *
 * @param valg - valg som er lest inn fra brukeren
 *
 * @see Soner::nySone();
 * @see Soner::skrivAlleSoner();
 * @see Soner::skrivEnSone();
 * @see Soner::nyttOppdrag();
 * @see Soner::skrivAlleOppdrag();
 * @see Soner::skrivEttOppdrag();
 */
void Soner::handling(string valg) {
     if (valg[0] == 'S') { // valg = S
          switch (valg[1]) {
               // Accsi kovertering
               case ('N'): nySone(valg);         break;
               case ('A'): skrivAlleSoner();        break;
               case ('1'): skrivEnSone(valg);    break;

               default: cout << "Ikke gjyldig valg etter S" << endl; break;
          }

     } else { // valg = O
          switch (valg[1]) {
               case ('N'): nyttOppdrag(valg);         break;
               case ('S'): slettOppdrag(valg);        break;
               case ('1'): skrivEttOppdrag(valg);     break;

               default: cout << "Ikke gjyldig valg etter O" << endl; break;
          }

     }
}

/*
 * Fordeller om ett sonenummer finnes i soner-mapen
 *
 * @param sonenr - nummeret på sonen som skal letes etter
 * @return true: at det finnes en sone med sonenummeret medsendt
 * @return false: det finnes IKKE en sone med sonenummeret medsendt
 */
bool Soner::soneLeter(int sonenr) {
     for (auto & s : soner) {
          if (s.second->sonenr() == sonenr) {
               return true;
          }
     }
     return false;
}

/*
 * Leser inn data fra fil
 *
 * @see Sone::lesFraFil(..)
 */
void Soner::lesFraFil() {
     ifstream infil;
     infil.open("SONER.DTA");
     int sonenr;

     if (infil) {
          infil >> sisteNr; infil.ignore();
          while (!infil.eof()){
               Sone* nysone = new Sone();

               infil >> sonenr;
               nysone->lesFraFil(infil, sonenr);
               soner.insert({sonenr, nysone});
          }
          cout << "Data lest inn fra filen \"SONER:DTA\" " << endl;
     } else {
          cout << "Fant ikke filen \"SONER.DTA\" " << endl;
     }
}

/*
 * Skriver data til fil
 *
 * @see Bolig::skrivTilFil(...)
 */
void Soner::skrivTilFil() {
     ofstream utfil;
     utfil.open("SONER.DTA");

     if (utfil) {
          utfil << sisteNr << "\n";

          for (auto & s : soner) {
               s.second->skrivTilFil(utfil);
          }

     } else {
          cout << "Fant ikke \"SONER.DTA\" " << endl;
     }
}
/*
* Skriver sone til fil
*
* @param soneNr: unikt sonenummer
* @param ut: Filen som skal skrives til
*
* @see skrivData()
*/
void Soner::skrivSoneTilFil(int soneNr, ofstream& ut) {

     // sjekk om det er noe boliger som skal skrives til fil
    auto it = soner.find(soneNr);
     
     if (it != soner.end() && it->second) {
         Sone* sone = it->second; // Hent sonepekeren
          ut << "Boliger i sone " << soneNr << ":\n";
          sone->skrivDetaljertData(ut);
     } else {
          ut << "Feil: Sone " << soneNr << " er registrert, men har en nullpeker.\n";
     }
}
/*
 * Lager ett nytt sone objekt
 *
 * @param valg: nummeret som skal regisreres i sonen
 *
 * @see Sone::lesData(...)
 */
void Soner::nySone(string valg) {
     // gjør om siste del av komando til en int
     int nr = atoi(valg.substr(2, valg.length()).c_str());

     if (1 <= nr && nr <= makssone) {
          if (!soner.count(nr)) {
               Sone *nySone = new Sone();
               nySone->lesData(nr);
               soner[nr] = nySone;
          } else {
               cout << "Det er en sone som har dette nummeret! Prøv igjen!" << endl;
          }
     } else {
          cout << "Ugjyldig sonenummer, range er 1-" << makssone << endl;
     }
}

/*
 * Skriver alt om en sone
 *
 * @param valg: nummeret på sonen som skal skrives ut
 *
 * @see Sone::skrivData();
 */
void Soner::skrivEnSone(string valg) {
     int nr = atoi(valg.substr(2, valg.length()).c_str());

     if (soner.find(nr) != soner.end()) {
          cout << "Info om en sone; " << endl;
          soner[nr]->skrivDetaljertData();
     } else {
          cout << "Det er ingen sone som er registrert med det nummeret" << endl;
     }
}

/*
 * Skriver ut data om alle sonene
 *
 * @see Sone::skrivData();
 */
void Soner::skrivAlleSoner() const {
     if (!soner.empty()) {
          cout << "Skriver ut alle data om sonene" << endl;
          int i = 0;
          for (const auto & s : soner) {
               s.second->skrivData();
               cout << endl;
          }
     } else {
          cout << "Det er ingen registrerte soner" << endl;
     }
}

/*
 * Skriver ut alle oppdrag
 *
 * @param valg: nummeret på oppdraget som skal regisreres
 *
 * @see Sone::boligVector(...)
 * @see Bolig::getOppdragsnummer(...)
 * @see Bolig::slettBolig(...)
 */
void Soner::slettOppdrag(string valg) {
     bool funnetB = false;
     int nr = atoi(valg.substr(2, valg.length()).c_str());
     if (!soner.empty()) {
          for (const auto & s : soner){
               vector<Bolig*> boliger = s.second->boligVector();
               for (auto & b :boliger) {
                    if (b->getOppdragsnummer() == nr) {
                         funnetB = true;
                         const char c = lesChar("Ønsker du å virkelig slette oppdraget? (J/N)");
                         if (toupper(c) == 'J') {
                              s.second->slettBolig(nr);
                              cout << "Bolig slettet" << endl;
                              break;
                         } else {
                              cout << "Sletting avsluttet" << endl;
                         }
                    }
               }

          }
          if (!funnetB) {
               cout << "Ingen oppdrag registrert med nr: " << nr << endl;
          }

     } else {
          cout << "Ingen registrerte soner" << endl;
     }

}

/*
 * Lager nytt oppdrag
 *
 * @param valg: nummeret på oppdraget som skal regisreres
 *
 * @see Sone::leggTilBolig(...)
 */
void Soner::nyttOppdrag(string valg) {
     // leser in sonenummer
     int nr = atoi(valg.substr(2, valg.length()).c_str());

     if (!soner.empty()) {
          if (soner.count(nr)) {
               auto type =static_cast<Boligtype> (lesInt("Ønsker du å registrere Leilighet (0) eller Eneborlig (1)", 0, 1));

               for (auto & s : soner) {
                    if (s.first == nr) {
                         s.second->leggTilBolig(type, ++sisteNr);
                    }
               }
          } else {
               cout << "Sonenummeret du skrev inn er ikke registrert" << endl;
          }
     } else {
          cout << "Det er ingen regostrerte soner enda!" << endl;
     }


}

/*
 * Skriver ut data om en sone
 *
 * @param valg: nummeret på oppdraget som skal skrives ut
 *
 * @see Sone::boligVector(...)
 * @see Bolig::getOppdragsnummer(...)
 * @see Bolig::skrivData(...)
 */
void Soner::skrivEttOppdrag(string valg) {
     int nr = atoi(valg.substr(2, valg.length()).c_str());
     bool oppdrag = false;
     for (const auto & s : soner) {
          vector<Bolig*> boliger = s.second->boligVector();
          for (const auto & b : boliger)
               if (b->getOppdragsnummer() == nr) {
                    oppdrag = true;
                    cout << "Oppdrag nr: " << nr << endl;
                    b->skrivData();
                    break;
               }
     }
     if (!oppdrag) {
          cout << "Det er ingen oppdrag som er registrert med det nummeret" << endl;
     }
}
