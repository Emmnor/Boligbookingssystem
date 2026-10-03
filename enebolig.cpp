/**
 * @file enebolig.cpp
 * @brief Implementasjon av alle funkjsonene i Enebolig-klassen.
 */

#include "enebolig.h"           // Klassen Enebolig
#include "LesData3.h"           // Verktøykasse for lesing av diverse data
#include <iostream>


/**
 * Standard konstruktør. Setter tomtens areal til 0 og selveiet til false.
 */
Enebolig::Enebolig() : Bolig() {
    tomtensAreal = 0;
    selveiet = false;
}

/**
 * Leser inn data for eneboligen fra brukeren.
 */
void Enebolig::lesData(int bolignr) {
    Bolig::lesData(bolignr);   // Kaller på lesData() i Bolig med bolignr.
                               // Leser inn ekstra data for Enebolig.
    tomtensAreal = lesInt("Tomtens areal (kvm)", 1, 2147483647);
    
    char JaEllerNei;                 
    do {
        JaEllerNei = lesChar("Selveiet? (J/N)");
        JaEllerNei = toupper(JaEllerNei); 
    } while (JaEllerNei != 'J' && JaEllerNei != 'N');

    selveiet = (JaEllerNei == 'J');    
}

void Enebolig::skrivData() const {
    Bolig::skrivData();   // Kaller på skrivData() i Bolig-klassen.
                          // Skriver ut ekstra data for Enebolig.
    cout << "Tomtens areal: " << tomtensAreal << "\n";
    cout << "Selveiet: " << (selveiet ? "Ja" : "Nei") << "\n";
}

/**
 * Leser data om enebolig fra fil.
 * 
 * @param inn - Filen som skal leses fra
 */
void Enebolig::lesFraFil(ifstream & inn) {
    Bolig::lesFraFil(inn);   // Kaller på lesFraFil() i Bolig-klassen.
                             // Leser ekstra data for Enebolig.
    inn >> tomtensAreal >> selveiet;
    inn.ignore();            // Ignorerer linjeskift.
}

/**
 * Skriver data om enebolig til fil.
 * 
 * @param ut - Filen som skal skrives til
 */
void Enebolig::skrivTilFil(ofstream& ut) const {
    Bolig::skrivTilFil(ut);   // Kaller på skrivTilFil() i Bolig-klassen.
                                 // Skriver ekstra data for Enebolig.
    ut << tomtensAreal << " "
       << selveiet << '\n';
}

void Enebolig::skrivTilPDF(ofstream & ut) {
    Bolig::skrivTilPDF(ut);   // Kaller på skrivData() i Bolig-klassen.
    // Skriver ut ekstra data for Enebolig.
    ut << "Tomtens areal: " << tomtensAreal << "\n";
    ut << "Selveiet: " << (selveiet ? "Ja" : "Nei") << "\n";
}