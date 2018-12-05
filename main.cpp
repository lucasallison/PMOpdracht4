//dit is de file met main functie

#include <iostream>
#include "oth.h"
#include <ctime>
#include <cstdlib>

using namespace std;

void startSpel() {

    othelloBord oth;
    oth.gegevens();
    oth.maakBord();
    oth.beginPositie();
    oth.drukAf();
    oth.stapel();

    while (oth.mogelijkeZetten()) {
        oth.doeZetVolgensbeurt();
        oth.stapel();
        oth.drukAf();
    }

    oth.klaar();

}//startSpel


int main () {

    srand(time(0));
    startSpel();

    return 0;

}//main