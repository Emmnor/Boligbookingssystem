/**
* @file kunde.cpp
* @brief Implementasjon av Kunde-klassen.
*/

#include "kunde.h"
extern Soner gSonebase;  


/**
* @brief Konstruktør som oppretter en ny kunde.
* @param nr Kundens unike nummer.
*/
Kunde::Kunde(int nr) {
    kundeNr = nr;
    tlfNr = 0;
    interesse = LEILIGHET;
}
/**
* @brief Destruktør for Kunde-klassen.
*/
Kunde::~Kunde() {
}

/** 
* @brief Leser inn en kunde fra fil.
* @param inn Inndatastrøm fra fil.
*/  
Kunde::Kunde(ifstream& inn) {
    int boligTypeInt, antSoner, soneNummer;
    
    inn >> kundeNr;
    inn.ignore(256, '\n'); // ENDRET
    getline(inn, navn);
    getline(inn, gateAdr);
    getline(inn, postAdr);
    getline(inn, mail);
    inn >> tlfNr >> boligTypeInt >> antSoner;
    
    interesse = static_cast<Boligtype>(boligTypeInt);
    
    for (int i = 0; i < antSoner; i++) {
        inn >> soneNummer;
        soner.push_back(soneNummer);
    }
}

/** 
* @brief Skriver kunden til fil.
* @param ut Utstrøm til fil.
*/
void Kunde::skrivTilFil(ofstream& ut) const {
    ut << kundeNr << '\n'
       << navn << '\n'
       << gateAdr << '\n'
       << postAdr << '\n'
       << mail << '\n'
       << tlfNr << '\n'
       << static_cast<int>(interesse) << '\n'
       << soner.size() << '\n';
       
    for (int sone : soner)
        ut << sone << ' ';
    
    ut << '\n';
}

/** 
* @brief Skriver kundens informasjon til skjerm.
*/
void Kunde::skrivData() const {
    cout << "Kundenr: " << kundeNr << "\n"
         << "Navn: " << navn << "\n"
         << "Adresse: " << gateAdr << ", " << postAdr << "\n"
         << "Mail: " << mail << "\n"
         << "Telefon: " << tlfNr << "\n"
         << "Interesse: " << (interesse == LEILIGHET ? "Leilighet" : "Enebolig") 
         << "\n"
         << "Soner: ";
         
    for (int sone : soner)
        cout << sone << ' ';
    
    cout << "\n--------------------------\n";
}

/**
* @brief Leser inn kundedata fra brukeren
*/   
void Kunde::lesData() {
    cout << "Skriv inn navn: ";
    cin.ignore(); 
    getline(cin, navn);

    cout << "Skriv inn gateadresse: ";
    getline(cin, gateAdr);

    cout << "Skriv inn postadresse: ";
    getline(cin, postAdr);

    cout << "Skriv inn e-post: ";
    getline(cin, mail);

    tlfNr = lesInt("Skriv inn telefonnummer uten mellomrom:", MINTLF, MAXTLF);
    
    int boligValg;
    cout << "Interesse (0: Leilighet, 1: Enebolig): ";
    do {                                            // ENDRET, la til hele denne 
        cin >> boligValg;                           // do løkken
        if (boligValg < 0 || boligValg > 1) {
            cout << "Ugyldig valg. Prøv igjen: ";
        }
    } while (boligValg < 0 || boligValg > 1);
    interesse = static_cast<Boligtype>(boligValg);
    cin.ignore();

    // Legge til soner kunden er interessert i
    cout << "Skriv inn sonenumre som du er interessert i (0 for å avslutte):\n";
    int sonenr;
    while (true) {
    sonenr = lesInt("Sonenummer:", 0, makssone);

    if (sonenr == 0) break;  // Avslutter hvis brukeren skriver 0

    if (gSonebase.soneLeter(sonenr)) {  // Sjekker om sonen eksisterer
        if (find(soner.begin(), soner.end(), sonenr) == soner.end()) {
            soner.push_back(sonenr);  // Legg til sone hvis den ikke finnes fra før
            sort(soner.begin(), soner.end());  // Sorter listen etter hver innlegging
            cout << "Sone " << sonenr << " lagt til.\n";
        } else {
            cout << "Sone " << sonenr << " er allerede lagt til.\n";
        }
    } else {
         cout << "Sonenummeret finnes ikke. Prøv igjen.\n";
    }
  }
}
