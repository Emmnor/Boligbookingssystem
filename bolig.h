/**
 * @file bolig.h
 * @brief Deklarasjon av klassen Bolig.
 */

 #ifndef BOLIG_H
 #define BOLIG_H
 #include <string>          // string
 #include <fstream>         // ifstream, ofstream
 using namespace std;


/**
 * Bolig-klassen inneholder data for en generell bolig.
 * Subklassen Enebolig arver fra denne klassen.
 */
class Bolig {
private:                  
    int oppdragsnummer;         ///< Unikt nummer for oppdraget.
    int opprettelsesdato;       ///< Datoen oppdraget ble registrert.
    int byggeaar;               ///< Året boligen bel bygget.
    int bruttoareal;            ///< Størrelsen på boligen.
    int antallSoverom;          ///< Antall soverom i boligen.
    int angittPris;             ///< Prisen som er angitt for boligen.
    string saksbehandler;       ///< Navnet på saksbehandleren.
    string eiersNavn;           ///< Navnet på boligens eier.
    string gateadresse;         ///< Gateadressen til boligen (gate+nr).
    string postadresse;         ///< Postadressen til boligen (postnummer+sted).
    string smaalangBeskrivelse; ///< En smaalang beskrivelse av boligen.

public:                 
    Bolig();                                      // Standard konstruktør.

    virtual ~Bolig();                             // Destruktør. 

    virtual void lesData(int bolignr);            // Leser inn data for boligen 
                                                  // fra bruker.
    virtual void skrivData() const;               // Skriver ut data for boligen 
                                                  // til bruker.           
    virtual void lesFraFil(ifstream& inn);        // Leser inn data for boligen 
                                                  // fra fil.
    virtual void skrivTilFil(ofstream& ut) const; // Skriver ut data for boligen 
                                                  // til fil.
     virtual void skrivTilPDF(ofstream& ut);      // skriver til lesbar pdf

    int getOppdragsnummer() const;                // Funksjon som returnerer 
                                                  // oppdragsnummeret.
};                                                
                 

#endif // BOLIG_H
