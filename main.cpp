//dit is de file met main functie

#include <iostream>
#include "oth.h"
#include <ctime>
#include <cstdlib>

using namespace std;


int main () {

    srand(time(0));
    othelloBord oth;
    oth.hoofdMenu();

   return 0;

}//main