//in deze file komen de functies van oth.h
#include "oth.h"

//MOET DIT??????
#include <iostream>
using namespace std;

void othelloBord::hoofdMenu() {

    cout << "welkom in het hoofdmenu" << endl;
    maakRij();
    drukAf();

}//hoofdmenu

void othelloBord::drukAf() {

    cout << "lijst van voor naar achter.." << endl;
    bordVakje* hulp = maakRij();

    while (hulp != nullptr) {
        cout << hulp->kleur << endl;
        hulp = hulp->buren[2];
    }
}//drukAf

bordVakje* othelloBord::maakRij() {
    int i;

    bordVakje *hulpEen, *hulpTwee;
    hulpEen = new bordVakje;
    hulpTwee = hulpEen;

    for (i=1; i < breedte; i++) {
        hulpEen->buren[2] = new bordVakje;
        hulpTwee = hulpEen->buren[2];
        hulpTwee->buren[6] = hulpEen;
        hulpEen = hulpTwee;
    }

    return hulpEen;
}//maakRij










//CONSTRUCTORS
bordVakje::bordVakje() {

    int i;
    for (i=0; i<8; i++){
        buren[i] = nullptr;
    }
}//bordVakje

othelloBord::othelloBord() {
    speler1 = true;
    speler2 = true;
    lengte = 8;
    breedte = 8;
    ingang = nullptr;
}//othelloBord