/*
 * @file sone.cpp
 * @brief Inneholder alle funksjonene til Sone klassen
 */

#include "sone.h"
#include <string>
#include <iostream>
#include "enebolig.h"
using namespace std;


Sone::Sone() {
     nr = 0;
}

void Sone::lesData(int nr) {
     this->nr = nr;
     cout << "Skriv en kort beskrivelse av sonen" << endl;
     getline(cin, beskrivelse);
}


void Sone::lesFraFil(ifstream & inn, int sonenr) {
     int boligantall = 0;
     int boligtype = 0;

     this->nr = sonenr;

     inn >> boligantall;
     //inn.ignore();
     getline(inn, beskrivelse);
     //inn.ignore();

     for (int i = 0; i < boligantall; i++) {
          Bolig *nyBolig;
          inn >> boligtype;
          (boligtype == 1) ? nyBolig = new Enebolig() :  nyBolig = new Bolig();
          nyBolig->lesFraFil(inn);
          boliger.push_back(nyBolig);
     }
}

void Sone::skrivTilFil(ofstream & ut) {
     ut << nr << " " << boliger.size() << " " << beskrivelse << "\n";

     for (auto & b : boliger) {
          // Sjekker om det er enebolig eller ikke
          (dynamic_cast<Enebolig*>(b)) ? ut << 1 : ut << 0;   ut << " ";
          b->skrivTilFil(ut);
     }
}

void Sone::skrivData() {
     cout << "Nr: " << this->nr << endl
          << "Beskrivelse: " << beskrivelse << endl
          << "Antall Boliger i sonen: " << boliger.size() << endl;
}

void Sone::skrivDetaljertData() {
     cout << "Nr: " << this->nr << endl
          << "Beskrivelse: " << beskrivelse << endl;

     if (!boliger.empty()) {
          cout << "Registrerte boliger: " << endl;
          int i = 1;
          for (const auto & b : boliger) {
               if (i++%5 == 0) {
                    do {
                         cout << '\n' << "Trykk enter for å fortsette..." << endl;
                    } while (cin.get() != '\n');
               }
               b->skrivData();
          }
     } else {
          cout << "Det er ingen registrerte boliger" << endl;
     }
}
void Sone::skrivDetaljertData(ofstream & ut) {
     ut   << "Nr: " << this->nr << endl
          << "Beskrivelse: " << beskrivelse << endl
          << "Registrerte boliger: " << endl;

     if (!boliger.empty()) {
          for (const auto & b : boliger) {
               b->skrivTilPDF(ut);
          }
     }
}

vector<Bolig*> Sone::boligVector() {
     return boliger;
}

int Sone::sonenr () const {
     return nr;
}

void Sone::leggTilBolig(enum Boligtype type, int bolignr) {
     Bolig * nyBolig;
     (type == LEILIGHET) ? nyBolig = new Bolig : nyBolig = new Enebolig;
     nyBolig->lesData(bolignr);
     boliger.push_back(nyBolig);
}

void Sone::slettBolig(int nr) {
     swap(boliger[nr-1], boliger[boliger.size()-1]);
     boliger.pop_back();
}


