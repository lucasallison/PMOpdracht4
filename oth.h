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
    int zijde; //lengte == breedte

    bool beurt; //als true, beurt speler 1

    public:
    othelloBord();
    ~othelloBord();
    void drukAf();
    void maakBord();
    char gebruikerInvoer(); //MOET DEZE IN CLASS??
    int leesGetal(int max);
    void beginPositie();
    bool isGeldigeZet(int i, int j);
    bool mogelijkeZetten();
    void verwijderen();
    void doeZet(int i, int j);
    bordVakje *gaNaar(int i, int j);
    void mensZet();
    void computerZet();
    void gegevens();
    int telPunten(bool zwart);
    bool checkVrijePlekken();
    void klaar();
    void doeZetVolgensbeurt();
    bool speler1; //true als mens
    bool speler2; //true als mens



    void kopieer ();
    void vervolg ();


};
