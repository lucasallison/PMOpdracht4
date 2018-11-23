//in deze file komen de functies van oth.h
#include "oth.h"

//MOET DIT??????
#include <iostream>
using namespace std;


void othelloBord::drukAf() {

    maakBord();
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

    cout << "welkom in het hoofdmenu" << endl;
    drukAf();

}//hoofdmenu

void othelloBord::maakBord() {
    int i;
    bordVakje *boven, *onder;
    ingang = maakRij();
    boven = ingang;
    onder = maakRij();
    ritsen(boven, onder);

    for(i=2; i<lengte; i++){
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
    lengte = 2;
    breedte = 2;
    ingang = nullptr;
}//othelloBord