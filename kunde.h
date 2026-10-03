/**
* @file Kunde.h
* @brief Definerer klassen for en enkelt kunde i eiendomsregisteret.
*/

#ifndef KUNDE_H
#define KUNDE_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "const.h"
#include "enum.h"
#include "LesData3.h"
#include "soner.h"
using namespace std;


/**
* @brief Representerer en kunde i eiendomsregisteret.
*/
class Kunde {
  private:
    int kundeNr, tlfNr;
    string navn, gateAdr, mail, postAdr;
    Boligtype interesse;
    vector<int> soner;

  public:
    Kunde(int nr);
    ~Kunde();
    //Kunde(int nr);
    Kunde(ifstream& inn);  // Leser fra fil
    int getKundeNr() const { return kundeNr; } // Getter-metode for kundeNr
    int getTlfNr() const { return tlfNr; } 
    string getNavn() const { return navn; }
    string getGateAdr() const { return gateAdr; }
    string getPostAdr() const { return postAdr; }
    string getMail() const { return mail; }
    Boligtype getInteresse() const { return interesse; }
    vector<int>& getSoner() { return soner; }
    const vector<int>& getSoner() const { return soner; }

    void skrivData() const;    //Skriver ut data
    void skrivTilFil(ofstream& ut) const;  //Skriver til fil
    void lesData();            //Leser inn fra bruker

};
#endif //KUNDE_H
