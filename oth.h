//hierin komt de class van het orthello bord

class bordVakje {
public:
    char kleur = 'w'; //PAS DIT AAN!!
    bordVakje* buren[8];
    bordVakje ();
};//bordVakje

class othelloBord {
    private:
    bordVakje *ingang;
    bordVakje *maakRij();
    void ritsen(bordVakje* boven, bordVakje *onder);
    bool beurt;
    int lengte, breedte;

    public:
    othelloBord();
    //VOEG EEN DESTRUCTOR TOE
    void drukAf();
    void hoofdMenu(); //MOET DIT IN OTH.H????
    void maakBord();
    void gegevens(); //l,b..
    void point ();
    void beginPositie();
    void verwijderen();
    void mensZet();
    bool isGeldigeZet(int i, int j);
    void doeZet(int i, int j);
    bordVakje *gaNaar(int i, int j);
    void zetVolgensRegels();
    bool speler1; //true als mens
    bool speler2; //true als mens
    int klaar();

};
