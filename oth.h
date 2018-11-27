//hierin komt de class van het orthello bord

class bordVakje {
public:
    char kleur; //PAS DIT AAN!!
    bordVakje* buren[8];
    bordVakje ();
};//bordVakje

class othelloBord {
    private:
    bordVakje *ingang;
    bordVakje *maakRij();
    void ritsen(bordVakje* boven, bordVakje *onder);
    int lengte, breedte;

    bool beurt; //als true, beurt speler 1

    public:
    othelloBord();
    //VOEG EEN DESTRUCTOR TOE
    void drukAf();
    void hoofdMenu(); //MOET DIT IN OTH.H????
    void maakBord();
    char gebruikerInvoer(); //MOET DEZE IN CLASS??
    int leesGetal(int max);
    void beginPositie();
    bool isGeldigeZet(int i, int j);
    bool mogelijkeZetten();
    void verwijderen();
    void doeZet(int i, int j);
    bordVakje *gaNaar(int i, int j);
    void startSpel();

    void gegevens(); //l,b, speler1, speler2,..

    void point();
    void mensZet();
    void computerZet();

    void zetVolgensRegels(); //??


    bool speler1; //true als mens
    bool speler2; //true als mens
    int klaar();

};
