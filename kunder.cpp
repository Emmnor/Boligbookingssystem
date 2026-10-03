/**
* @file kunder.cpp
* @brief Håndtering av kunder i systemet, inkludert oppretting, redigering, sletting og skriving til fil.
*/

#include "kunder.h"
#include <sstream>
#include <iomanip>
#include <string>
extern Soner gSonebase;         // Globalt objekt for sonebasen


/**
* @brief Konstruktør for Kunder-klassen.
* Initialiserer siste kundens nummer til 0. 
*/  
Kunder::Kunder() {
    sisteNr = 0;
}
/**
* @brief Destruktør for Kunder-klassen.
*/  
Kunder::~Kunder() {
    // Evt opprydding
}
/**
* @brief Oppretter en ny kunde og legger til i kundelisten.
* @see Kunde::lesData()
*/  
void Kunder::nyKunde(string valg) { 
    int kundeNr = atoi(valg.substr(2, valg.length()).c_str()); 

    sisteNr++;                       // Øker kundens nummer
    Kunde* nyKunde = new Kunde(sisteNr); // Oppretter ny kunde med nyee nummer               
    nyKunde->lesData(); // Kaller lesData(), lar brukeren skrive inn informasjon               
    kundeListe.push_back(nyKunde);   // Legger til den nye kunden i lista
    skrivTilFil();                   // Lagrer den oppdaterte listen til fil  
}
/**
* @brief Leser inn kunder fra filen "KUNDER.DTA".
* @see Kunde::Kunde(std::ifstream&)
*/        
void Kunder::lesFraFil() {              // Leser inn kunder fra fil 
    ifstream inn("KUNDER.DTA");
    if (inn) {                         // Hvis filen åpnes riktig
        int antall;
        inn >> sisteNr >> antall;
        inn.ignore();                // Ignorerer newline etter tallene
            
        for (int i = 0; i < antall; i++){
                Kunde* nyKunde = new Kunde(inn);
                kundeListe.push_back(nyKunde);
        }
        inn.close();
    } else {                           // Hvis filen ikke kunne åpnes
        cout << "Fant ikke/kunne ikke åpne kundefilen\n";
    }
}
/**
* @brief Skriver alle kunder til filen "KUNDER.DTA".
* @see Kunde::skrivTilFil(std::ofstream&)
*/  
void Kunder::skrivTilFil() const {
    ofstream ut("KUNDER.DTA");  // Åpner filen for skriving

    if (!ut) {  // Sjekker om filen kunne åpnes
        cout << "Feil ved åpning av kunde-fil for skriving!\n";
    } else {  // Hvis filen ble åpnet riktig
        ut << sisteNr << '\n' << kundeListe.size() << '\n';  // Lagrer x kunder

        for (const Kunde* k : kundeListe) {
            k->skrivTilFil(ut);  // Kaller Kunde::skrivTilFil() for hver kunde
        }
    }
}
/**
* @brief Skriver ut informasjon om alle kunder.
* @see Kunde::skrivData()
*/  
void Kunder::skrivAlleKunder() const {     // Skriver ut info om alle kunder
    if (!kundeListe.empty()) {
        cout << "----- Alle kunder -----\n";
        for (const Kunde* k : kundeListe)
            k->skrivData();
    } else {
        cout << "Det er ingen regisrerte kunder\n";
    }

}
/**
* @brief Skriver ut informasjon om én kunde.
* @param kundeNr Kundens nummer.
* @see Kunde::skrivData()
*/  
void Kunder::skrivEnKunde(string valg) { // Skriver ut info om én kunde
    int kundeNr = atoi(valg.substr(2, valg.length()).c_str()); 

    if (!kundeListe.empty()) {
        for (Kunde* k : kundeListe) {
            if (k->getKundeNr() == kundeNr) {
                cout << "Info om kunden:" << endl;
                k->skrivData();  // skrivData() fra Kunde
                break;
            }
        }
        cout << "Det finnes ingen kunde med nummer " << kundeNr << "." << endl;
    } else {
        cout << "Det er ingen regisrerte kunder\n";
    }



}
/**
* @brief Endrer en kundes interesserte soner.
* @param kundeNr Kundens nummer.
* @see Kunde::skrivData(), Soner::soneLeter(int)
*/  
void Kunder::endreKunde(string valg){   // Endrer kunde (legge til/fjerne soner)
    int kundeNr = atoi(valg.substr(2, valg.length()).c_str()); 

    // Finn kunden i kundelisten
    Kunde* kunde = nullptr;
    for (Kunde* k : kundeListe) {
        if (k->getKundeNr() == kundeNr) {
            kunde = k;
            break;
        }
    }
        
    // Sjekk om kunden ble funnet
    if (!kunde) {
        cout << "Ingen kunde med nummer " << kundeNr << " funnet.\n";
    } else {
        // Skriv ut kundens nåværende data
        cout << "Kundeinfo:\n";
        kunde->skrivData();
            
        // La brukeren endre sonene
        int valg;
        do {
            cout << "\nVelg handling:\n"
                 << "1. Legg til sone\n"
                 << "2. Fjern sone\n"
                 << "0. Avslutt endring\n"
                 << "Valg: ";
            cin >> valg;
            cin.ignore();
                
            if (valg == 1) {  // Legg til sone
                int soneNr = lesInt("Skriv inn sone du vil legge til: ", 1, makssone);
                if (!gSonebase.soneLeter(soneNr)) {
                    cout << "Sone " << soneNr << " eksisterer ikke.\n";
                } else {
                    // Sjekk om sone allerede er lagt til
                    if (find(kunde->getSoner().begin(), kunde->getSoner().end(), soneNr) != kunde->getSoner().end()) {
                        cout << "Sone " << soneNr << " er allerede lagt til.\n";
                    } else {
                        kunde->getSoner().push_back(soneNr);
                        sort(kunde->getSoner().begin(), kunde->getSoner().end());
                        cout << "Sone " << soneNr << " lagt til.\n";
                    }
                }
            } else if (valg == 2) {  // Fjern sone
                int soneNr = lesInt("Skriv inn sone du vil fjerne: ", 1, makssone);
                auto it = find(kunde->getSoner().begin(), kunde->getSoner().end(), soneNr);
                if (it == kunde->getSoner().end()) {
                    cout << "Sone " << soneNr << " er ikke registrert for kunden.\n";
                } else {
                    kunde->getSoner().erase(it);
                    cout << "Sone " << soneNr << " fjernet.\n";
                }
            } else if (valg != 0) {
                cout << "Ugyldig valg.\n";
            }
        } while (valg != 0);
    }
}
/**
* @brief Sletter en kunde basert på kundenummer.
* 
* Søker etter kunden i kundelisten og sletter den hvis den finnes.
* Ber om bekreftelse før sletting.
* 
* @param kundeNr Kundenummeret til kunden som skal slettes.
*/  
void Kunder::slettKunde(string valg){   // Sletter kunde
    int kundeNr = atoi(valg.substr(2, valg.length()).c_str()); 
   
    //Finner kunden i listen
    auto it = find_if(kundeListe.begin(), kundeListe.end(),
    [kundeNr](const Kunde* k) { return k->getKundeNr() == kundeNr; });
    
    if (it == kundeListe.end()) {  //Hvis kunden ikke finnes
        cout << "Kundenummeret finnes ikke.\n";
    } else {   //funnet kunde
        cout << "Er du sikker på at du vil slette kunden? (J/N): ";
        char svar;
        cin >> svar;
        if (toupper(svar) == 'J') {
            delete *it;              // Sletter objektet fra heapen
            kundeListe.erase(it);    // Fjerner pekeren fra listen
            cout << "Kunden er slettet.\n";
        } else {
            cout << "Sletting avbrutt.\n";
        }
    }
}
/**
* @brief Skriver en kundeoversikt til en fil.
* 
* Oppretter en fil med navnet "Kxxxxx.DTA" hvor "xxxxx" er kundens unike nummer.
* Skriver ut informasjon om alle sonene kunden er interessert i.
* 
* @param kundeNr Kundenummeret til kunden som det skal skrives ut oversikt for.
* @see Soner::skrivSoneTilFil(int, ostream&)
*/  
void Kunder::kundeOversikt(string valg) {  
    int kundeNr = atoi(valg.substr(2, valg.length()).c_str()); 

    Kunde* kunde = nullptr;             //Finner kunden i kundelisten
    for (Kunde* k : kundeListe) {
        if (k->getKundeNr() == kundeNr) {   
            kunde = k;
            break;
        }
    }
    if (!kunde) {     //Hvis kunden ikke finnes
        cout << "Ingen kunde med nummer " << kundeNr << " funnet.\n";
    } else {
        // Sett opp filnavn: Kxxxxx.DTA
        ostringstream oss;
        oss << "K" << setfill('0') << setw(5) << kundeNr << ".DTA";
        string filnavn = oss.str();

        ofstream ut(filnavn);
        if (!ut) {          // Sjekker om filen kan åpnes
            cout << "Kunne ikke åpne fil for skriving: " << filnavn << "\n";
        } else {
            ut << "Kundeoversikt for kunde " << kundeNr << "\n"
               << "Navn: " << kunde->getNavn() << "\n"
               << "Adresse: " << kunde->getGateAdr() << ", " << kunde->getPostAdr() << "\n"
               << "E-post: " << kunde->getMail() << "\n"
               << "Telefon: " << kunde->getTlfNr() << "\n"
               << "Interesse: " << (kunde->getInteresse() == LEILIGHET ? "Leilighet" : "Enebolig") << "\n";
            
                // Hent hele sone-mappen
                map<int, Sone*> soner = gSonebase.soneMap(); 

                // For hver sone kunden er interessert i, skriv ut boligoversikten
                for (int soneNr : kunde->getSoner()) {
                    cout  << "Skriver informasjon for sone " << soneNr << endl;  // Debugging linje

                auto it = soner.find(soneNr); // Finn sonen i mappen
                if (it != soner.end()) {  // Sjekk om sonen finnes
                    Sone* sone = it->second;  // Hent Sone*-objektet

                if (sone) {
                    ut << "\nSone " << soneNr << ":\n";
    
                        // Hent boligene i sonen som en vector<Bolig*>
                        vector<Bolig*> boliger = sone->boligVector();
    
                        if (boliger.empty()) {
                            ut << "Ingen boliger i denne sonen.\n";
                        } else {
                            // Iterer over boliger og skriv til fil
                            for (Bolig* bolig : boliger) {
                                if (bolig) {  // Sjekk at pekeren ikke er null
                                    bolig->skrivTilPDF(ut);  // Skriv boligdata til filen
                                }
                            }
                        } 
                    }   
                } else {
                    ut << "\nSone " << soneNr << " finnes ikke i systemet.\n";
                }
            }  
            ut.close(); // Lukk filen etter skriving
            cout << "Kundeoversikt skrevet til fil: " << filnavn << "\n";
        }
    }
}

/**
* @brief Håndterer brukerens valg i kundemenyen.
* 
* Gir brukeren muligheten til å legge til, endre, slette og vise kunder.
* 
*/
void Kunder::handling(string valg) {
    switch (valg[1]) {
        case ('N'): nyKunde(valg);           break;
        case ('1'): skrivEnKunde(valg);      break;
        case ('A'): skrivAlleKunder();          break;
        case ('E'): endreKunde(valg);        break;
        case ('S'): slettKunde(valg);        break;
        case ('O'): kundeOversikt(valg);     break;
        
        default:
            cout << "Ugyldig input etter K!\n"; break;
    }
}
    


