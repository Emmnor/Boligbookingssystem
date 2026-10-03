/*
 * @file funksjoner.cpp
 * @brief Inmat til funksjonene
 */

#include <iostream>
#include <string>
#include "funksjoner.h"


void skrivMeny(){
  cout << "Menyvalg:\n";
  cout << " - - - - - - - - - - - - - - - - - \n";
  cout << "\tK N         -  Ny Kunde\n";
  cout << "\tK 1 <knr>   -  Skriv alt om en kunde\n";
  cout << "\tK A         -  Alle kunder skrives\n";
  cout << "\tK E <knr>   -  Endrer spesifik kunde\n";
  cout << "\tK S <knr>   -  Sletter en spesifik kunde\n";
  cout << "\tK O <knr>   -  Oversikt over alle kunder i en fil\n";
  cout << "\tS N <snr>   -  Ny sone\n";
  cout << "\tS 1 <snr>    - Skriv alt om en sone\n";
  cout << "\tS A          - Skriver it alle soner\n";
  cout << "\tO N <snr>    - Nytt oppdrag som blir registrert sonen\n";
  cout << "\tO 1 <onr>    - Skriv alt om ett oppdrag\n";
  cout << "\tO S <onr>    - Slett ett oppdrag\n";
}

string lesBedreChar(string t) {
  bool gjyldig = false;
  string tegn;
  string c;

  do {
    gjyldig = true;


    cout << t << " ";
    tegn = "";
    getline(cin, c);

    for( int i = 0; i < c.length(); i++){
      if ( c[i] != ' ') {
        tegn.push_back(toupper(c[i]));
      }
    }

    if (0 < tegn.length() && tegn.length() < 5) {
      if (tegn.length() > 2) {
        for (int i = 2; i < tegn.length(); i++) {
          if (!isdigit(tegn[i])) {
            gjyldig = false;
            cout << "Ugjyldig inputt, "<< i << " er ikke tall" << endl;
          }
        }
      }
    } else {
      cout << "Inputt kan bare være mellom 1 og 4 tegn" << endl;
      gjyldig = false;
    }

  } while ( ! gjyldig );


  return tegn;
}