//dit is de file met main functie

#include <iostream>
#include "oth.h"
#include <ctime>
#include <cstdlib>

using namespace std;


int main () {

    srand(time(0));
    othelloBord oth;
    oth.gegevens();
    oth.maakBord();
    oth.beginPositie();

    while (oth.mogelijkeZetten()) {
        oth.drukAf();
        oth.doeZetVolgensbeurt();
    }

    oth.klaar();



   return 0;

}//main