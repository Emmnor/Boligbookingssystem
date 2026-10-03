/**
 * @file bolig.cpp
 * @brief Implementasjon av klasse Bolig.
 */

#include "bolig.h"              // Klassen Bolig
#include "LesData3.h"           // Verktøykasse for lesing av diverse data
#include <iostream>             // cout, cin


/**
 * Standard konstruktør. Setter alle verdier til null eller strenger til tom.
 */
Bolig::Bolig() {
    oppdragsnummer = opprettelsesdato = byggeaar = bruttoareal = antallSoverom 
    = angittPris = 0;
    saksbehandler = eiersNavn = gateadresse = postadresse = smaalangBeskrivelse
    = "";   
}

/**
 * Destruktør. Arv med pekere brukes, så må destruere dem.
 */
Bolig::~Bolig() {}

/**
 * Leser inn data for boligen fra brukeren.
 */
void Bolig::lesData(int bolignr) {
    oppdragsnummer = bolignr; // Setter oppdragsnummeret basert på parameter.
    opprettelsesdato = lesInt("Opprettelsesdato (YYYYMMDD)",
                              19000101, 21000101);
    byggeaar = lesInt("Byggeaar", 0, 2100);
    bruttoareal = lesInt("Bruttoareal (kvm)", 1, 100000);
    antallSoverom = lesInt("Antall soverom", 0, 1000);
    angittPris = lesInt("Oppgi angitt pris", 1, 2147483647);

    cout << "Saksbehandler: ";
    getline(cin, saksbehandler);

    cout << "Eiers navn: ";
    getline(cin, eiersNavn);

    cout << "Gateadresse (gate+nr): ";
    getline(cin, gateadresse);

    cout << "Postadresse (nr+sted): ";
    getline(cin, postadresse);

    cout << "Smaalang beskrivelse av boligen: ";
    getline(cin, smaalangBeskrivelse);

}

/**
 * Skriver ut boligen til brukeren. 
 */
void Bolig::skrivData() const {
    cout << "--------------------------------------------------\n";
    cout << "Oppdragsnummer: " << oppdragsnummer << "\n";
    cout << "Opprettelsesdato: " << opprettelsesdato << "\n";
    cout << "Byggeaar: " << byggeaar << "\n";
    cout << "Bruttoareal: " << bruttoareal << "\n";
    cout << "Antall soverom: " << antallSoverom << "\n";
    cout << "Angitt pris: " << angittPris << "\n";
    cout << "Saksbehandler: " << saksbehandler << "\n";
    cout << "Eiers navn: " << eiersNavn << "\n";
    cout << "Gateadresse: " << gateadresse << "\n";
    cout << "Postadresse: " << postadresse << "\n";
    cout << "Smaalang beskrivelse: " << smaalangBeskrivelse << "\n";
    cout << "--------------------------------------------------\n";
}
/**
 * Skriver ut informajson til fil
 */
void Bolig::skrivTilPDF(ofstream& ut) {
    ut << "--------------------------------------------------\n";
    ut << "Oppdragsnummer: " << oppdragsnummer << "\n";
    ut << "Opprettelsesdato: " << opprettelsesdato << "\n";
    ut << "Byggeaar: " << byggeaar << "\n";
    ut << "Bruttoareal: " << bruttoareal << "\n";
    ut << "Antall soverom: " << antallSoverom << "\n";
    ut << "Angitt pris: " << angittPris << "\n";
    ut << "Saksbehandler: " << saksbehandler << "\n";
    ut << "Eiers navn: " << eiersNavn << "\n";
    ut << "Gateadresse: " << gateadresse << "\n";
    ut << "Postadresse: " << postadresse << "\n";
    ut << "Smaalang beskrivelse: " << smaalangBeskrivelse << "\n";
    ut << "--------------------------------------------------\n";
}


/**
 * Leser data om bolig fra fil.
 * 
 * @param inn - Filen som skal leses fra.
 */
void Bolig::lesFraFil(ifstream & inn) {
    inn >> oppdragsnummer >> opprettelsesdato >> byggeaar >> bruttoareal
        >> antallSoverom >> angittPris;
    inn.ignore();

    getline(inn, saksbehandler);
    getline(inn, eiersNavn);
    getline(inn, gateadresse);
    getline(inn, postadresse);
    getline(inn, smaalangBeskrivelse);
}

/**
 * Skriver data om bolig til fil.
 * 
 * @param ut - Filen som skal skrives til.
 */
void Bolig::skrivTilFil(ofstream& ut) const {
    ut << oppdragsnummer << " "
       << opprettelsesdato << " "
       << byggeaar << " "
       << bruttoareal << " "
       << antallSoverom << " "
       << angittPris << "\n"
       << saksbehandler << "\n"
       << eiersNavn << "\n"
       << gateadresse << "\n"
       << postadresse << "\n"
       << smaalangBeskrivelse << "\n";
}

int Bolig::getOppdragsnummer() const {
    return oppdragsnummer;
}