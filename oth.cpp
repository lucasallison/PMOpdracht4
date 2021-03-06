#include "oth.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//constructors
bordVakje::bordVakje() {
    kleur = '.';
    int i;
    for (i = 0; i < 8; i++) {
        buren[i] = nullptr;
    }
}//bordVakje

othelloBord::othelloBord() {
    speler1 = true;
    speler2 = true;
    zijde = 0;
    ingang = nullptr;
    beurt = true;
}//othelloBord

//destructor
othelloBord::~othelloBord() {
    verwijderen();
}//~othelloBord

//drukt het huidige bord en punten af
void othelloBord::drukAf() {
    int n = 1, j = 0;
    bordVakje *hulpEen, *hulpTwee;
    hulpEen = ingang;
    hulpTwee = ingang;

    cout << endl << "  ";
    while (j < zijde) {
        if (n == 10) {
            cout << 0 << " ";
            n = 0;
        } else {
            cout << n << " ";
        }
        n++;
        j++;
    }
    n = 1;
    cout << endl;
    while (hulpEen != nullptr) {
        if (n == 10) {
            cout << 0 << " ";
            n = 0;
        } else {
            cout << n << " ";
        }
        n++;
        while (hulpEen != nullptr) {
            cout << hulpEen->kleur << " ";
            hulpEen = hulpEen->buren[2];
        }
        cout << endl;
        hulpEen = hulpTwee->buren[4];
        hulpTwee = hulpEen;
    }
    cout << endl << "Punten zwart: " << telPunten(true) << "  Punten wit: " << telPunten(false) << endl;
}//drukAf

//cout het aantal vervolgzetten
void othelloBord::vervolgPartijen() {
    int aantalPartijen = 0, nieuwBord = 1;
    bool bewaarBeurt = beurt;

    berekenenZetten(aantalPartijen, nieuwBord);
    cout << "Aantal vervolg partijen: " << aantalPartijen << endl;
    beurt = bewaarBeurt;
}

//berekent het aantal vervolg zetten
void othelloBord::berekenenZetten(int &tellerPartijen, int &tellerNieuwBord) {
    int i, j, z, w;
    bordVakje *hulpEen = ingang, *hulpTwee = ingang;
    w = tellerNieuwBord;
    tellerNieuwBord = 0;

    while (hulpTwee->buren[7] != nullptr) {
        hulpTwee = hulpTwee->buren[7];
    }
    for (z = 0; z < w; z++) {
        for (i = 1; i <= zijde; i++) {
            for (j = 1; j <= zijde; j++) {
                if (isGeldigeZet(i, j)) {
                    kopieren();
                    doeZet(i, j);
                    hulpTwee->buren[7] = ingang;
                    ingang->buren[6] = hulpTwee;
                    hulpTwee = ingang;
                    ingang = hulpEen;
                    tellerNieuwBord++;
                    tellerPartijen++;
                }
            }
        }
        if (ingang->buren[7] != nullptr) {
            ingang = ingang->buren[7];
            hulpEen = ingang;
        }
    }
    if (w != 0) {
        if (ingang->buren[7] != nullptr) {
            ingang = ingang->buren[6];
            hulpEen = ingang;
        }
    }
    hulpTwee = ingang;
    if (ingang->buren[7] == nullptr) {

        while (hulpEen->buren[6] != nullptr) {
            hulpEen = ingang->buren[6];
            verwijderen();
            ingang = hulpEen;
        }
    } else {
        hulpTwee = hulpTwee->buren[7];
        while (hulpEen->buren[6] != nullptr) {
            hulpEen = ingang->buren[6];
            verwijderen();
            ingang = hulpEen;
        }
        ingang = hulpTwee;
        ingang->buren[6] = hulpEen;
        hulpEen->buren[7] = ingang;
        beurt = !beurt;
        berekenenZetten(tellerPartijen, tellerNieuwBord);
    }
}//vervolgPartijen

//kopieert het huidige bord naar een nieuw bord
void othelloBord::kopieren() {
    int i, j;
    bordVakje *hulpEen, *hulpTwee = ingang;

    maakBord();
    for (i = 1; i <= zijde; i++) {
        hulpEen = hulpTwee;
        hulpTwee = hulpTwee->buren[4];
        for (j = 1; j <= zijde; j++) {
            gaNaar(i, j)->kleur = hulpEen->kleur;
            hulpEen = hulpEen->buren[2];
        }
    }
}//kopieren

//stapelt het huidige bord
void othelloBord::stapel() {
    int i, j;
    bordVakje *hulpEen, *hulpTwee = ingang;

    maakBord();
    ingang->buren[5] = hulpTwee;
    for (i = 1; i <= zijde; i++) {
        hulpEen = hulpTwee;
        hulpTwee = hulpTwee->buren[4];
        for (j = 1; j <= zijde; j++) {
            gaNaar(i, j)->kleur = hulpEen->kleur;
            hulpEen = hulpEen->buren[2];
        }
    }
}//stapel

//hierdoor kan het bord terug worden gezet naar een oude stand
void othelloBord::stappenTerug(int m) {
    bordVakje *hulp;
    int n;

    for (n = 0; n < m; n++) {
        if (ingang->buren[5] != nullptr) {
            hulp = ingang->buren[5];
            verwijderen();
            ingang = hulp;
        }
    }
}//stappenTerug

//hierdoor kan een gebruiker een zet doen, stap terug doen of stoppen
void othelloBord::mensZet() {
    int i, j;
    char kleur, invoer;
    if (beurt) {
        kleur = 'Z';
    } else {
        kleur = 'W';
    }

    cout << "(" << kleur << ") Geef de plek waar u een zet wilt doen of (0,0) voor extra opties " << endl;
    cout << "Lengte: ";
    i = leesGetal(zijde);
    cout << "Breedte: ";
    j = leesGetal(zijde);

    if (i == 0 && j == 0) {
        do {
            cout << "Vul in: [A]antal vervolg partijen, [S]tap terug gaan, [Q]uit of [Z]et doen " << endl;
            invoer = gebruikerInvoer();

            switch (invoer) {
                case 'A': case 'a':
                    vervolgPartijen();
                    break;
                case 'S': case 's':
                    if (speler1 && speler2) {
                        stappenTerug(2);
                    } else {
                        stappenTerug(1);
                    }
                    cout << endl << "Het bord is terug gezet naar uw vorige beurt" << endl;
                    drukAf();
                    break;
                case 'Q': case 'q':
                    cout << endl << "Dat was het dan!" << endl;
                    exit(0);
                case 'Z': case 'z':
                    drukAf();
                    break;
                default:
                    cout << "Vul een valide letter in" << endl;
            }
        } while (invoer != 'Z' && invoer != 'z');

        cout << "Geef de plek waar u een zet wilt doen " << endl;
        cout << "Lengte: ";
        i = leesGetal(zijde);
        cout << "Breedte: ";
        j = leesGetal(zijde);
    }

    do {
        if (!isGeldigeZet(i, j)) {
            drukAf();
            cout << "(" << kleur << ")" << " Dit is geen geldige zet, probeer het opnieuw" << endl;
            cout << "Lengte: ";
            i = leesGetal(zijde);
            cout << "Breedte: ";
            j = leesGetal(zijde);
        }
    } while (!isGeldigeZet(i, j));
    stapel();
    doeZet(i, j);
}//mensZet

//bepaald welke speler een zet mag doen
void othelloBord::doeZetVolgensbeurt() {
    cout << endl;
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

//zet op het scherm wie de winnaar is
void othelloBord::klaar() {
    int puntenZwart = telPunten(true);
    int puntenWit = telPunten(false);

    cout << endl << "Het spel is afgelopen!" << endl;
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
            cout << "Het is geindigd in een gelijk spel. Beide spelers hadden " << puntenZwart << " punten." << endl;
        }
    }
    if (puntenZwart != puntenWit) {
        cout << "Zwart is geindigd met een totaal van " << puntenZwart << " punten" << endl;
        cout << "Wit is geindigd met een totaal van " << puntenWit << " punten" << endl;
    }
}//klaar

//telt de punten van zwart of wit
int othelloBord::telPunten(bool zwart) {
    char kleur;
    int i, j, teller = 0;
    bordVakje *hulp;
    if (zwart) {
        kleur = 'Z';
    } else {
        kleur = 'W';
    }

    for (i = 1; i <= zijde; i++) {
        for (j = 1; j <= zijde; j++) {
            hulp = gaNaar(i, j);
            if (hulp->kleur == kleur) {
                teller++;
            }
        }
    }
    return teller;
}//telPunten

//hierdoor doet de computer een random zet
void othelloBord::computerZet() {
    int i, j;

    if (speler1 && !speler2) {
        cout << "(W) De computer heeft zijn zet gedaan" << endl;
    }
    if (!speler1 && speler2) {
        cout << "(Z) De computer heeft zijn zet gedaan" << endl;
    }
    do {
        i = 1 + (rand() % zijde);
        j = 1 + (rand() % zijde);
    } while (!isGeldigeZet(i, j));
    doeZet(i, j);
}//computerZet

//gaat naar het opgegeven vakje
bordVakje *othelloBord::gaNaar(int lengte, int breedte) {
    int i, j;
    bordVakje *hulp = ingang;

    for (j = 1; j < breedte; j++) {
        hulp = hulp->buren[2];
    }
    for (i = 1; i < lengte; i++) {
        hulp = hulp->buren[4];
    }
    return hulp;
}//gaNaar

//hierdoor wordt er een 'Z' of 'W' op het bord geplaatst
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
    for (z = 0; z < 8; z++) {
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

//kijkt of er nog zetten gedaan kunnen worden
bool othelloBord::mogelijkeZetten() {
    int i, j;

    for (i = 1; i <= zijde; i++) {
        for (j = 1; j <= zijde; j++) {
            if (isGeldigeZet(i, j)) {
                return true;
            }
        }
    }
    return false;
}//mogelijkeZetten

//kijkt of het betreffende vakje een geldige zet is
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

//hier kan de gebruiker de gegevens van het spel invullen
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
    } while (invoerGebruiker >= 4 && invoerGebruiker % 2 != 0);
    zijde = invoerGebruiker;
    if (zijde < 4) {
        zijde = 4;
    }

    cout << "Vul nu de rollen van de spelers in. " << endl;
    cout << "[0] Speler één is een mens. [1] Speler één is een computer" << endl;
    invoerGebruiker = leesGetal(1);
    if (invoerGebruiker != 0) {
        speler1 = !speler1;
    }
    cout << "[0] Speler twee is een mens. [1] Speler twee is een computer" << endl;
    invoerGebruiker = leesGetal(1);
    if (invoerGebruiker != 0) {
        speler2 = !speler2;
    }
}//gegevens

//zet de start waardes op het bord
void othelloBord::beginPositie() {
    gaNaar(zijde / 2, zijde / 2)->kleur = 'W';
    gaNaar(zijde / 2, zijde / 2)->buren[4]->kleur = 'Z';
    gaNaar(zijde / 2, zijde / 2)->buren[2]->kleur = 'Z';
    gaNaar(zijde / 2, zijde / 2)->buren[3]->kleur = 'W';
}//beginPositie

//functie die een bord maakt
void othelloBord::maakBord() {
    int i;
    bordVakje *boven, *onder;
    ingang = maakRij();
    onder = ingang;

    for (i = 1; i < zijde; i++) {
        boven = onder;
        onder = maakRij();
        ritsen(boven, onder);
    }
    beginPositie();
}//maakBord

//zorgt dat twee rijen met elkaar verbonden zijn
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

//verwijderd een bord
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

//deze functie maakt een rij van het bord
bordVakje *othelloBord::maakRij() {
    int i;
    bordVakje *hulpEen, *hulpTwee;

    hulpEen = new bordVakje;
    hulpTwee = hulpEen;
    for (i = 1; i < zijde; i++) {
        hulpEen->buren[6] = new bordVakje;
        hulpTwee = hulpEen->buren[6];
        hulpTwee->buren[2] = hulpEen;
        hulpEen = hulpTwee;
    }
    return hulpEen;
}//maakRij

//pakt de invoer van een gebruiker
char othelloBord::gebruikerInvoer() {
    char invoer;
    cin.get(invoer);
    while (invoer == '\n') {
        cin.get(invoer);
    }
    return invoer;
}//gebruikerInvoer

//haalt een klopend getal (< max) uit een gebruiker invoer
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