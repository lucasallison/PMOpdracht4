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
    speler2 = false;
    lengte = 0;
    breedte = 0;
    ingang = nullptr;
    beurt = true; //speler 1 als true: hij is zwart

}//othelloBord


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

    cout << "\n";

}//drukAf

void othelloBord::hoofdMenu() {

    char keuzeGebruiker = '?';


    cout << "Voer eerst een paar gegevens in" << endl;
    afmetingenWijzigen();
    spelerKeuze();

    while (keuzeGebruiker != 'q' || keuzeGebruiker != 'Q') {
        cout << "Maak een keuze: [S]tart spel, [G]egevens wijzigen, [Q]uit, ....";
        keuzeGebruiker = gebruikerInvoer();
        switch (keuzeGebruiker) {
            case 'G': case 'g':
                gegevens();
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

        if (beurt) {
            beurt = false;
        } else {
            beurt = true;
        }

    }

    if (! speler1 && ! speler2) {
        cout << "De computers hebben hard gestreden..." << endl;
        drukAf();
    }

    klaar();

}//startSpel

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

    cout << "\n";

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
    cout << "Geeft de plek waar u een zet wilt doen: " << endl;

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

    bordVakje *hulp;
    hulp = gaNaar(lengte, breedte);

    hulp->kleur = kleur;
    for (z=0; z<8; z++){
        if (hulp->buren[z] != nullptr && hulp->buren[z]->buren[z] != nullptr) {
            if (hulp->buren[z]->buren[z]->kleur == hulp->kleur && hulp->buren[z]->kleur != '.') {
                hulp->buren[z]->kleur = kleur;
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
    char kleur;
    int z;
    if (beurt) {
        kleur = 'Z';
    } else {
        kleur = 'W';
    }

    bordVakje *hulpEen, *hulpTwee;
    hulpEen = gaNaar(plekLengte, plekBreedte);

    for (z=0; z < 8; z++) {
        if (hulpEen->buren[z] != nullptr) {
            hulpTwee = hulpEen->buren[z];
            if (kleur != hulpTwee->kleur && hulpTwee->kleur != '.' && hulpTwee->buren[z] != nullptr && hulpTwee->buren[z]->kleur == kleur &&  hulpEen->kleur == '.') {
                return true;
            }
        }
    }
    return false;
}//isGeldigeZet


void othelloBord::gegevens() {
    int keuzeGebruiker;

    cout << "\nWelkom bij gegevens wijzigen." << endl;

   do {
       cout << "Maak een keuze: [A]fmetingen wijzigen, [S]pelers rollen toekennen of [T]erug" << endl;
       keuzeGebruiker = gebruikerInvoer();
       switch (keuzeGebruiker) {
           case 'A': case 'a':
               afmetingenWijzigen();
               break;
           case 'S': case 's':
               spelerKeuze();
               break;
           case 'T': case 't':
               break;
           default:
               cout << "vul een valide letter in" << endl;

       }

   }  while (keuzeGebruiker != 'T' || keuzeGebruiker != 't');

}//gegevens

void othelloBord::spelerKeuze() {

    char keuzeGebruiker;
    int beginnen;
    cout << "Maak een keuze: [A] Player vs Player, [B] Player vs Computer of "
         << "[C] Computer vs Computer" << endl;
    keuzeGebruiker = gebruikerInvoer();
    switch (keuzeGebruiker) {
        case 'A': case 'a':
            speler1 = true;
            speler2 = true;
            break;
        case 'B': case 'b':
                cout << "Wilt u dat [0] de gebruiker begint of [1] de computer begint? ";
                beginnen = leesGetal(1);
                if (beginnen == 0) {
                    speler1 = true;
                    speler2 = false;
                } else {
                    speler1 = false;
                    speler2 = true;
                }
            break;
        case 'C': case 'c':
            speler1 = false;
            speler2 = false;
            break;
        default:
            cout << "Vul een valide letter in:" << endl;
    }
}//spelerKeuze

void othelloBord::afmetingenWijzigen() {
    int invoerGebruiker;
    bool ongeldigeInvoer = false;

    do {
        if (ongeldigeInvoer) {
            cout << "Dit is ongeldig, probeer het opnieuw." << endl;
        }
        cout << "Geef de afmetingen van het bord: ";
        invoerGebruiker = leesGetal(20);
        ongeldigeInvoer = true;
    } while (invoerGebruiker >= 4 && invoerGebruiker%2 != 0);
    lengte = invoerGebruiker;
    breedte = invoerGebruiker;

}//afmetingenWijz

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

        if (getal > max) {
            do {
                getal--; //CHECK DIT EVEN: EEN GETAL GROTER DAN MAX WORDT MAX EN WAT IS MAX??
            } while (getal > max);
        }
        cin.get(invoer);
    }

    return getal;
}//leesGetal




