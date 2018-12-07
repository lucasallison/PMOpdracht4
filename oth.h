class bordVakje {

public:
    char kleur;
    bordVakje *buren[8];
    bordVakje();

};//bordVakje

class othelloBord {

private:
    bordVakje *ingang;
    bordVakje *maakRij();
    void ritsen(bordVakje *boven, bordVakje *onder);
    int zijde; //lengte == breedte
    bool beurt; //als true, beurt speler 1

public:
    othelloBord();
    ~othelloBord();
    void drukAf();
    void maakBord();
    void beginPositie();
    void klaar();
    void doeZetVolgensbeurt();
    void verwijderen();
    void doeZet(int i, int j);
    void mensZet();
    void computerZet();
    void gegevens();
    void stappenTerug(int m);
    void stapel();
    char gebruikerInvoer();
    int telPunten(bool zwart);
    int leesGetal(int max);
    bool isGeldigeZet(int i, int j);
    bool mogelijkeZetten();
    bool speler1; //true als mens
    bool speler2; //true als mens
    bordVakje *gaNaar(int lengte, int breedte);

};//othelloBord
