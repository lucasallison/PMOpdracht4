//hierin komt de class van het orthello bord

class bordVakje {
public:
    char kleur;
    bordVakje* buren[8];
    bordVakje ();
};//bordVakje

class othelloBord {
    private:
    bordVakje *ingang;
    bordVakje *ingangKopie;
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
    int leesGetal(int max); //MOET DEZE IN CLASS??
    void beginPositie();
    bool isGeldigeZet(int i, int j);
    bool mogelijkeZetten();
    void verwijderen();
    void doeZet(int i, int j);
    void mensZet();
    void computerZet();
    void gegevens();
    int telPunten(bool zwart);
    void klaar();
    void doeZetVolgensbeurt();
    bordVakje *gaNaar(int lengte, int breedte);
    bool speler1; //true als mens
    bool speler2; //true als mens


    bordVakje *gaNaarKopie(int lengte, int breedte);
    void stappenTerug(int n);
    void verwijderenKopie();
    void zetBordTerug();
    void kopieerBord();
    void stapel();

    void drukAfKopie ();

    //void vervolg ();


};
