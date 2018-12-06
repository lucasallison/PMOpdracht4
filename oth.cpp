//in deze file komen de functies van oth.h
#include "oth.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//mensen kunnen een zet terug nemen
//mag exit???????
//mag "\n"????
//bedenk nog wat op zijde + 1 (mensZet)


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
    zijde = 0;
    ingang = nullptr;
    ingangKopie = nullptr;
    beurt = true; //speler 1 als true: hij is zwart

}//othelloBord

//destructor
othelloBord::~othelloBord() {
    verwijderen();
}//~othelloBord


void othelloBord::drukAf() {
    int n = 1, j = 0;
    bordVakje *hulpEen, *hulpTwee;
    hulpEen = ingang;
    hulpTwee = ingang;

    cout << "\n  ";
    while (j < zijde){
        if (n == 10) {
            cout << 0 << " ";
            n = 0;
        }  else {
            cout << n << " ";
        }
        n++;
        j++;
    }

    n = 1;
    cout << "\n";
    while (hulpEen != nullptr) {

        if (n == 10) {
            cout << 0 << " ";
            n = 0;
        }  else {
            cout << n << " ";
        }
        n++;

        while (hulpEen != nullptr) {

            cout << hulpEen->kleur << " ";
            hulpEen = hulpEen->buren[2];
        }
        cout << "\n";
        hulpEen = hulpTwee->buren[4];
        hulpTwee = hulpEen;
    }

    cout << "\nPunten zwart: " << telPunten(true) << "  Punten wit: " << telPunten(false) << endl;

}//drukAf

void othelloBord::drukAfKopie() {
    int n = 1, j = 0;
    bordVakje *hulpEen, *hulpTwee;
    hulpEen = ingangKopie;
    hulpTwee = ingangKopie;

    cout << "\n  ";
    while (j < zijde){
        if (n == 10) {
            cout << 0 << " ";
            n = 0;
        }  else {
            cout << n << " ";
        }
        n++;
        j++;
    }

    n = 1;
    cout << "\n";
    while (hulpEen != nullptr) {

        if (n == 10) {
            cout << 0 << " ";
            n = 0;
        }  else {
            cout << n << " ";
        }
        n++;

        while (hulpEen != nullptr) {

            cout << hulpEen->kleur << " ";
            hulpEen = hulpEen->buren[2];
        }
        cout << "\n";
        hulpEen = hulpTwee->buren[4];
        hulpTwee = hulpEen;
    }

    cout << "\nPunten zwart: " << telPunten(true) << "  Punten wit: " << telPunten(false) << endl;

}//drukAfKopie



void othelloBord::kopieerBord() {

    int i, j;
    bordVakje *boven, *onder;
    ingangKopie = maakRij();
    onder = ingangKopie;

    for(i=1; i<zijde; i++){
        boven = onder;
        onder = maakRij();
        ritsen(boven, onder);
    }

    for (i=1; i <= zijde; i++) {
        for (j=1; j <= zijde; j++) {
            gaNaarKopie(i, j)->kleur = gaNaar(i, j)->kleur;

        }
    }

}//kopieerBord

void othelloBord::stapel() {

    bordVakje *hulp;
    hulp = ingangKopie;
    kopieerBord();
    ingangKopie->buren[6] = hulp;

}//stapel

void othelloBord::stappenTerug(int m) {

    bordVakje *hulp;
    int n = 0;

    while ( n < m) {
        if (ingang != nullptr) {
            if (ingangKopie->buren[6] != nullptr) {
                hulp = ingangKopie->buren[6];
                verwijderenKopie();
                ingangKopie = hulp;
            }
        }
        n++;
    }

}//stappenTerug

void othelloBord::zetBordTerug() {
    int i, j;

    for (i=1; i <= zijde; i++) {
        for (j=1; j <= zijde; j++) {
            gaNaar(i, j)->kleur = gaNaarKopie(i, j)->kleur;

        }
    }
}


void othelloBord::doeZetVolgensbeurt() {
    cout << "\n";

    if (beurt) {
        if (speler1) {
            mensZet();
        } else {
            computerZet();
        }
    } else {
        if (speler2) {
            mensZet();
        } else {
            computerZet();
        }
    }


    beurt = !beurt;
}//doeZetVolgensBeurt

void othelloBord::klaar() {

    int puntenZwart = telPunten(true);
    int puntenWit = telPunten(false);

    cout << "\nHet spel is afgelopen!" << endl;

    if (zijde * zijde != puntenZwart + puntenWit) {
        if (beurt) {
            cout << "Wit is de winnaar, omdat zwart moest passen. Gefeliciteerd wit!" << endl;
        } else {
            cout << "Zwart is de winnnar, omdat wit moest passen. Gefeliciteerd zwart!" << endl;
        }

    } else {

        if (puntenZwart > puntenWit) {
            cout << "Zwart is de winnaar door de meerderheid van de punten. Gefliciteerd zwart!" << endl;
        }

        if (puntenZwart < puntenWit) {
            cout << "Wit is de winnaar door de meerheid van de punten. Gefelicteerd wit!" << endl;
        }

        if (puntenZwart == puntenWit) {
            cout << "Het is geindigd in een gelijk spel."  << endl;
        }
    }

    cout << "Zwart is geindigd met een totaal van " << puntenZwart << " punten" << endl;
    cout << "Wit is geindigd met een totaal van " << puntenWit << " punten" << endl;

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

    for (i=1; i <= zijde; i++) {
        for (j=1; j <= zijde; j++) {
            hulp = gaNaar(i, j);
            if (hulp->kleur == kleur) {
                teller++;
            }
        }
    }
    return teller;
}//telPunten

void othelloBord::computerZet() {
    int i, j;

    if (speler1 && !speler2) {
        cout << "(W) De computer heeft zijn zet gedaan" << endl;
    }
    if (!speler1 && speler2) {
        cout << "(Z) De computer heeft zijn zet gedaan" << endl;
    }

    do {
        i = 1+(rand() % zijde);
        j = 1+(rand() % zijde);
    } while (! isGeldigeZet(i, j));


    doeZet(i, j);

}//computerZet

void othelloBord::mensZet() {
    int i, j;
    char kleur;
    if (beurt) {
        kleur = 'Z';
    } else {
        kleur = 'W';
    }

    cout << "(" << kleur << ") " << "Vul in: (0,0) om te stoppen, (0,1) om terug te gaan of geef de plek waar u een zet wilt doen" << endl;

        do {
            cout << "Lengte: ";
            i = leesGetal(zijde);
            cout << "Breedte: ";
            j = leesGetal(zijde);

            if (i == 0 && j == 0) {
                cout << "\nDat was het dan!" << endl;
                exit (0);
            }

            if (i == 0 && j == 1) {
                stappenTerug(2);
                zetBordTerug();
                stappenTerug(1);
                cout << "\nHet bord is terug gezet naar uw vorige beurt" << endl;
                beurt = !beurt;
            } else if (!isGeldigeZet(i, j)) {
                drukAf();
                cout << "(" << kleur << ")" << " Dit is geen geldige zet, probeer het opnieuw" << endl;
            }

        } while (!isGeldigeZet(i, j) && i != 0 && j != 1);


        if (i != 0 && j != 1) {
            doeZet(i, j);
        }

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


bordVakje* othelloBord::gaNaarKopie(int lengte, int breedte) {

    int i, j;
    bordVakje *hulp;
    hulp = ingangKopie;

    for (j= 1; j < breedte; j++) {
        hulp = hulp->buren[2];
    }
    for (i = 1; i < lengte; i++) {
        hulp = hulp->buren[4];
    }

    return hulp;

}//VOEG DEZE SAMEN????

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

    for (i=1; i <= zijde; i++) {
        for (j=1; j <= zijde; j++) {
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
    zijde = invoerGebruiker;

    cout << "Vul nu de rollen van de spelers in. " << endl;
    cout << "[0] Speler één is een mens. [1] Speler één is een computer" << endl;
    invoerGebruiker = leesGetal(1);
    if (invoerGebruiker == 0) {
        speler1 = true;
    } else {
        speler1 = false;
    }
    cout << "[0] Speler twee is een mens. [1] Speler twee is een computer" << endl;
    invoerGebruiker = leesGetal(1);
    if (invoerGebruiker == 0) {
        speler2 = true;
    } else {
        speler2 = false;
    }


}//gegevens

void othelloBord::beginPositie() {

    bordVakje *hulp;
    hulp = gaNaar(zijde/2, zijde/2);

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

    for(i=1; i<zijde; i++){
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

void othelloBord::verwijderen() {

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

void othelloBord::verwijderenKopie() {

        bordVakje *hulp;

        while (ingangKopie != nullptr) {
            hulp = ingangKopie;
            ingangKopie = hulp->buren[4];
            while (hulp->buren[2] != nullptr) {
                hulp = hulp->buren[2];
                delete hulp->buren[6];
            }
            delete hulp;
        }


}//VOEG NOG SAMEN??

bordVakje* othelloBord::maakRij() {
    int i;

    bordVakje *hulpEen, *hulpTwee;
    hulpEen = new bordVakje;
    hulpTwee = hulpEen;

    for (i=1; i < zijde; i++) {
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
            getal = max;
        }
        cin.get(invoer);
    }

    return getal;
}//leesGetal




