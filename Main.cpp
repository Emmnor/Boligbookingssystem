/**
 *   Hovedprogrammet for OOP-prosjektet V25 med kunder, soner og (ene)boliger.
 *
 *   @file     MAIN.CPP
 *   @author   Emma A.S Nordli, Markus G. K. Aarhus, Åne S. Kristoffersen
*/

#include <iostream>
#include "kunder.h"
#include "soner.h"
#include "funksjoner.h"
using namespace std;

 
Kunder gKundebase;         ///<  Globalt container-objekt med ALLE kundene.
Soner gSonebase;           ///<  Globalt container-objekt med ALLE sonene.


/**
 *  Hovedprogram.
*/
int main()  {
     gKundebase.lesFraFil();
     gSonebase.lesFraFil();
 
     skrivMeny();
     // gjør om denne til å lese 3 charer i en string. endre les data
     string valg = lesBedreChar("\nKommando");
 
     while(valg[0] != 'Q')  {
       switch(valg[0])    {
         case 'K':            gKundebase.handling(valg);      break;
         case 'S': case 'O':  gSonebase.handling(valg);   break;
         default:             skrivMeny();                break;
      }
      valg = lesBedreChar("\nKommando");
     }
 
     gKundebase.skrivTilFil();
     gSonebase.skrivTilFil();
 
     cout << "\n\n";
     return 0;
}
