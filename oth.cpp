//in deze file komen de functies van oth.h
#include "oth.h"
#include <iostream>
using namespace std;

//kunnen lengte en breedte verschillen? of lengte == breedte??
//Er kan nu gezet worden op een al in beslag genomen vakje, maak dit nog


//CONSTRUCTORS
bordVakje::bordVakje() {
    kleur = '.';
    int i;
    for (i=0; i<8; i++){
        buren[i] = nullptr;
    }
}//bordVakje

othelloBord::othelloBord() {
    speler1 = true;
    speler2 = true;
    lengte = 0;
    breedte = 0;
    ingang = nullptr;
    beurt = true; //speler 1 als true: hij is wit

}//othelloBord


void othelloBord::drukAf() {

    bordVakje *hulpEen, *hulpTwee;
    hulpEen = ingang;
    hulpTwee = ingang;

    while (hulpEen != nullptr) {
        while (hulpEen != nullptr) {

            cout << hulpEen->kleur << " ";
            hulpEen = hulpEen->buren[2];
        }
        cout << "\n";
        hulpEen = hulpTwee->buren[4];
        hulpTwee = hulpEen;
    }

}//drukAf

void othelloBord::hoofdMenu() {

    char keuzeGebruiker = '?';

    cout << "voer eerst een paar gegevens in" << endl;
    gegevens();

    while (keuzeGebruiker != 'q' || keuzeGebruiker != 'Q') {
        cout << "Maak een keuze: [S]tart spel, [G]egevens wijzigen, [Q]uit, ...." << endl;
        keuzeGebruiker = gebruikerInvoer();
        switch (keuzeGebruiker) {
            case 'G': case 'g':
                gegevens(); //DIT MOET NOG AANGEPAST WORDEN

                break;
            case 'S': case 's':
                maakBord();
                startSpel();
                break;
            case 'q': case 'Q':
                cout << "einde programma." << endl;
                break;
            default:
                cout << "vul een valide letter in." << endl;
        }
    }
}//hoofdmenu

void othelloBord::startSpel() {
    beginPositie();
    drukAf();


    while (mogelijkeZetten()) {
        if (beurt) {
            cout << "speler 1 is aan de beurt" << endl;
            if (speler1) {
                mensZet();
                drukAf();
            }

        } else {
            cout << "speler 2 is aan de beurt" << endl;


        }

    }
    
}//startSpel

void othelloBord::mensZet() {
    int i, j;
    cout << "Geeft de plek (lengte, breedte) waar u een zet wilt doen: " << endl;

    do {
        cout << "Lengte: ";
        i = leesGetal(lengte);
        cout << "Breedte: ";
        j = leesGetal(breedte);

        if (! isGeldigeZet(i, j)) {
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
   bordVakje *hulp;
   hulp = gaNaar(lengte, breedte);

    if (beurt) {
        hulp->kleur = 'Z';
    } else {
        hulp->kleur = 'W';
    }

}//doeZet

bool othelloBord::mogelijkeZetten() {
    bordVakje *hulpEen, *hulpTwee;
    int i, j;
    hulpEen = ingang;
    hulpTwee = ingang;
    for (i=1; i < lengte; i++) {
        hulpTwee = hulpEen;
        for (j=1; j < breedte; j++) {
            if (isGeldigeZet(i, j)) {
                return true;
            }
            hulpEen = hulpEen->buren[2];
        }
        hulpEen = hulpTwee->buren[4];
    }

    return false;
}//mogelijkeZetten



bool othelloBord::isGeldigeZet(int plekLengte, int plekBreedte) {
    char kleur;
    int z = 0;
    if (beurt) {
        kleur = 'Z';
    } else {
        kleur = 'W';
    }

    bordVakje *hulpEen, *hulpTwee;
    hulpEen = gaNaar(plekLengte, plekBreedte);

    while (z < 8) {
        if (hulpEen->buren[z] != nullptr) {
            hulpTwee = hulpEen->buren[z];
            if (kleur != hulpTwee->kleur && hulpTwee->kleur != '.' && hulpTwee->buren[z] != nullptr && hulpTwee->buren[z]->kleur == kleur &&  hulpEen->kleur == '.') {
                return true;
            }
        }
        z++;
    }
    return false;
}//isGeldigeZet


void othelloBord::gegevens() {
    int invoerGebruiker;

    do {
        cout << "afmetingen: ";
        invoerGebruiker = leesGetal(21);
    } while (invoerGebruiker >= 4 && invoerGebruiker%2 != 0);
    lengte = invoerGebruiker;
    breedte = invoerGebruiker;

}//gegevens

void othelloBord::beginPositie() {
    int i, j;
    bordVakje *hulp = ingang;
    for (j=1; j < breedte/2; j++) {
        hulp = hulp->buren[2];
    }
    for (i=1; i < lengte/2; i++) {
        hulp = hulp->buren[4];
    }

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

//LAAT DIT EVEN CHECKEN!!!!
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

        if (getal >= max) {
            do {
                getal--; //CHECK DIT EVEN: EEN GETAL GROTER DAN MAX WORDT MAX EN WAT IS MAX??
            } while (getal > max);
        }
        cin.get(invoer);
    }

    return getal;
}//leesGetal




