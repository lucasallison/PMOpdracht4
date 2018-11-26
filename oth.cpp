//in deze file komen de functies van oth.h
#include "oth.h"

//MOET DIT??????
#include <iostream>
using namespace std;


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
    beurt = true;
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
    cout << "Maak een keuze: [S]tart spel, [G]egevens wijzigen, ...." << endl;

    keuzeGebruiker = gebruikerInvoer();
    switch(keuzeGebruiker) {
        case 'G': case 'g':
            gegevens();
            break;
        case 'S': case 's':
            maakBord();
            beginPositie();
            drukAf();
            break;
        default:
            cout << "vul een valide letter in." << endl;

    }
}//hoofdmenu

void othelloBord::gegevens() {
    int invoerGebruiker;

    do {
        cout << "lengte: " << endl;
        invoerGebruiker = leesGetal(21);
    } while (invoerGebruiker >= 4 && invoerGebruiker%2 != 0);
    lengte = invoerGebruiker;
    breedte = invoerGebruiker;
    
}//gegevens

void othelloBord::beginPositie() {
    int i, j;
    bordVakje *hulp = ingang;
    for (i=1; i < breedte/2; i++) {
        hulp = hulp->buren[2];
    }
    for (j=1; j < lengte/2; j++) {
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
                getal = getal / 10;
            } while (getal > max);
        }
        cin.get(invoer);
    }

    return getal;
}//leesGetal




