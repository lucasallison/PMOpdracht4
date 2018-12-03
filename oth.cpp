//in deze file komen de functies van oth.h
#include "oth.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//kunnen lengte en breedte verschillen? of lengte == breedte??
//voeg toe dat er gepast kan worden
//fix de while loops
//voeg toe dat je tijdens spelen kan stoppen
//als een speler niet kan heeft hij verloren
//stand tussen door cout
//mensen kunnen een zet terug nemen
//dat mensen kunnen stoppen tijdens spelen


//constructors
bordVakje::bordVakje() {
    kleur = '.';
    int i;
    for (i=0; i<8; i++){
        buren[i] = nullptr;
    }
}//bordVakje

othelloBord::othelloBord() {
    speler1 = true;
    speler2 = false;
    lengte = 0;
    breedte = 0;
    ingang = nullptr;
    beurt = true; //speler 1 als true: hij is zwart

}//othelloBord

//destructor
othelloBord::~othelloBord() {
    verwijderen();
}//~othelloBord


void othelloBord::drukAf() {

    bordVakje *hulpEen, *hulpTwee;
    hulpEen = ingang;
    hulpTwee = ingang;

    cout << "\n";
    while (hulpEen != nullptr) {
        while (hulpEen != nullptr) {

            cout << hulpEen->kleur << " ";
            hulpEen = hulpEen->buren[2];
        }
        cout << "\n";
        hulpEen = hulpTwee->buren[4];
        hulpTwee = hulpEen;
    }

    cout << "\nPunten zwart: " << telPunten(true) << ". Punten wit: " << telPunten(false) << endl;

}//drukAf

void othelloBord::doeZetVolgensbeurt() {

    cout << "\n";

    if (beurt) {
        if (speler1) {
            cout << "Zwart is aan de beurt" << endl;
            mensZet();
            drukAf();
        } else {
            if (!speler1 && !speler2) {
                computerZet();
            } else {
                cout << "De computer (zwart) heeft zijn zet gedaan." << endl;
                computerZet();
                drukAf();


            }
        }
    } else {
        if (speler2) {
            cout << "Wit is aan de beurt" << endl;
            mensZet();
            drukAf();
        } else {
            if (!speler1 && !speler2) {
                computerZet();
            } else {
                cout << "De computer (wit) heeft zijn zet gedaan." << endl;
                computerZet();
                drukAf();

            }
        }

    }

    beurt = !beurt;
}//MAAAAAK DEZE BETER

void othelloBord::klaar() {

    int puntenZwart = telPunten(true);
    int puntenWit = telPunten(false);

    cout << "Het spel is afgelopen!" << endl;

    if (puntenZwart > puntenWit) {
        cout << "Zwart is de winnaar, met een totaal van " << puntenZwart << " punten." << endl;
        cout << "Wit heeft verloren, met een totaal van " << puntenWit << " punten." << endl;
        cout << "Gefelicteerd zwart!" << endl;
    }

    if (puntenZwart < puntenWit) {
        cout << "Wit is de winnaar, met een totaal van " << puntenWit << " punten" << endl;
        cout << "Zwart heeft verloren, met een totaal van " << puntenZwart << " punten" << endl;
        cout << "Gefelicteerd wit!" << endl;
    }

    if (puntenZwart == puntenWit) {
        cout << "Het is geindigd in een gelijk spel. Beide spelers hadden " << puntenZwart << " punten" << endl;
    }

}//klaar

int othelloBord::telPunten(bool zwart ) {
    char kleur;
    int i, j, teller = 0;
    bordVakje *hulp;
    if (zwart) {
        kleur = 'Z';
    } else {
        kleur = 'W';
    }

    for (i=1; i <= lengte; i++) {
        for (j=1; j <= breedte; j++) {
            hulp = gaNaar(i, j);
            if (hulp->kleur == kleur) {
                teller++;
            }
        }
    }
    return teller;
}

void othelloBord::computerZet() {
    int i, j;

    do {
        i = 1+(rand() % lengte);
        j = 1+(rand() % breedte);
    } while (! isGeldigeZet(i, j));


    doeZet(i, j);

}//computerZet

void othelloBord::mensZet() {
    int i, j;
    cout << "Geef 0,0 om te stoppen of geef de plek waar u een zet wilt doen)" << endl;

    do {
        cout << "Lengte: ";
        i = leesGetal(lengte);
        cout << "Breedte: ";
        j = leesGetal(breedte);

        if (! isGeldigeZet(i, j)) {
            drukAf();
            cout << "Dit is geen geldige zet, probeer het opnieuw" << endl;
        }

    } while (! isGeldigeZet(i, j));

    doeZet(i, j);

}//mensZet

bordVakje* othelloBord::gaNaar(int lengte, int breedte) {
    int i, j;
    bordVakje *hulp;
    hulp = ingang;

    for (j= 1; j < breedte; j++) {
        hulp = hulp->buren[2];
    }
    for (i = 1; i < lengte; i++) {
        hulp = hulp->buren[4];
    }

    return hulp;
}//gaNaar

void othelloBord::doeZet(int lengte, int breedte) {

    char kleur;
    int z;

    if (beurt) {
        kleur = 'Z';
    } else {
        kleur = 'W';
    }

    bordVakje *hulpEen, *hulpTwee;
    hulpEen = gaNaar(lengte, breedte);

    hulpEen->kleur = kleur;
    for (z=0; z<8; z++) {
        hulpTwee = hulpEen;
        while (hulpTwee->buren[z] != nullptr && hulpTwee->buren[z]->kleur != kleur) {
                hulpTwee = hulpTwee->buren[z];
        }

        if (hulpTwee->buren[z] != nullptr) {
             if (hulpTwee->buren[z]->kleur != '.') {
                 hulpTwee = hulpEen;
                 while (hulpTwee->buren[z]->kleur != kleur) {
                     hulpTwee = hulpTwee->buren[z];
                     hulpTwee->kleur = kleur;
                 }
             }
         }
    }


}//doeZet

bool othelloBord::mogelijkeZetten() {

    int i, j;

    for (i=1; i <= lengte; i++) {
        for (j=1; j <= breedte; j++) {
            if (isGeldigeZet(i, j)) {
                return true;
            }
        }
    }

    return false;
}//mogelijkeZetten



bool othelloBord::isGeldigeZet(int plekLengte, int plekBreedte) {
    char kleur, kleurCheck;
    int z;
    if (beurt) {
        kleur = 'Z';
        kleurCheck = 'W';
    } else {
        kleur = 'W';
        kleurCheck = 'Z';
    }

    bordVakje *hulpEen, *hulpTwee;
    hulpEen = gaNaar(plekLengte, plekBreedte);

    if (hulpEen->kleur == '.') {
        for (z = 0; z < 8; z++) {
            hulpTwee = hulpEen;
            while (hulpTwee->buren[z] != nullptr && hulpTwee->buren[z]->kleur == kleurCheck) {
                hulpTwee = hulpTwee->buren[z];
            }

            if (hulpTwee->buren[z] != nullptr && hulpTwee != hulpEen) {
                hulpTwee = hulpTwee->buren[z];
                if (hulpTwee->kleur == kleur) {
                    return true;
                }
            }

        }
    }
    return false;
}//isGeldigeZet

void othelloBord::gegevens() {

    int invoerGebruiker;
    bool ongeldigeInvoer = false;

    cout << "Vul eerst een paar gegevens in." << endl;
    do {
        if (ongeldigeInvoer) {
            cout << "Dit is ongeldig, probeer het opnieuw." << endl;
        }
        cout << "Geef de afmetingen van het bord: ";
        invoerGebruiker = leesGetal(100);
        ongeldigeInvoer = true;
    } while (invoerGebruiker >= 4 && invoerGebruiker%2 != 0);
    lengte = invoerGebruiker;
    breedte = invoerGebruiker;

    cout << "Vul nu de rollen van de spelers in. " << endl;
    cout << "[0] Speler 1 is een mens. [1] Speler 1 is een computer" << endl;
    invoerGebruiker = leesGetal(1);
    if (invoerGebruiker == 0) {
        speler1 = true;
    } else {
        speler1 = false;
    }
    cout << "[0] Speler 2 is een mens. [1] Speler  is een computer" << endl;
    invoerGebruiker = leesGetal(1);
    if (invoerGebruiker == 0) {
        speler2 = true;
    } else {
        speler2 = false;
    }


}//gegevens

void othelloBord::beginPositie() {

    bordVakje *hulp;
    hulp = gaNaar(lengte/2, breedte/2);

    hulp->kleur = 'W';
    hulp = hulp->buren[4];
    hulp->kleur = 'Z';
    hulp = hulp->buren[2];
    hulp->kleur = 'W';
    hulp = hulp->buren[0];
    hulp->kleur = 'Z';

}//beginPositie

void othelloBord::maakBord() {
    int i;
    bordVakje *boven, *onder;
    ingang = maakRij();
    onder = ingang;

    for(i=1; i<lengte; i++){
        boven = onder;
        onder = maakRij();
        ritsen(boven, onder);
    }

}//maakBord

void othelloBord::ritsen(bordVakje *boven, bordVakje *onder) {

    while (boven != nullptr) {
        boven->buren[5] = onder->buren[6];
        onder->buren[7] = boven->buren[6];
        boven->buren[3] = onder->buren[2];
        onder->buren[1] = boven->buren[2];
        onder->buren[0] = boven;
        boven->buren[4] = onder;

        boven = boven->buren[2];
        onder = onder->buren[2];
    }

}//ritsen

void  othelloBord::verwijderen() {

    bordVakje *hulp;

    while (ingang != nullptr) {
        hulp = ingang;
        ingang = hulp->buren[4];
        while (hulp->buren[2] != nullptr) {
            hulp = hulp->buren[2];
            delete hulp->buren[6];
        }
        delete hulp;
    }
}//verwijderen

bordVakje* othelloBord::maakRij() {
    int i;

    bordVakje *hulpEen, *hulpTwee;
    hulpEen = new bordVakje;
    hulpTwee = hulpEen;

    for (i=1; i < breedte; i++) {
        hulpEen->buren[6] = new bordVakje;
        hulpTwee = hulpEen->buren[6];
        hulpTwee->buren[2] = hulpEen;
        hulpEen = hulpTwee;
    }

    return hulpEen;
}//maakRij

char othelloBord::gebruikerInvoer() {
    char invoer;

    cin.get(invoer);
    while (invoer == '\n') {
        cin.get(invoer);
    }
    return invoer;
}//gebruikerInvoer

int othelloBord::leesGetal(int max) {
    int getal = 0;
    char invoer;

    cin.get(invoer);
    while (invoer == '\n') {
        cin.get(invoer);
    }
    while (invoer != '\n') {
        if (isdigit(invoer)) {
            getal = getal * 10 + invoer - '0';
        }

        if (getal > max) {
            do {
                getal--; //CHECK DIT EVEN: EEN GETAL GROTER DAN MAX WORDT MAX EN WAT IS MAX??
            } while (getal > max);
        }
        cin.get(invoer);
    }

    return getal;
}//leesGetal




