#ifndef CHATURAJISPEL_H
#define CHATURAJISPEL_H

#pragma once

#include <QObject>
#include "chaturajipion.h"
#include "dobbelstenen.h"
#include "speler.h"


class ChaturajiSpel: public QObject {
    Q_OBJECT

public:
    ChaturajiSpel(Bord spelbord);
    void vindEnMaakZet(Speler* speler);
    bool checkZet(Zet zet, Pion* p, Pion::Team teamSpeler, bool echt);
    void vindAlleZettenVoorPion(Pion* p, Speler* spelerAanBeurt);
    bool isGedaan() const;
    bool stukMagVerplaatstWorden(Pion* p, bool echt);
    void saveSpel(QString naam);
    bool loadSpel(QString naam);
    void maakNieuwePion(char type, char xCoord, char yCoord, char team);
    Bord getSpelbord() const;
    std::vector<int> eersteKlik(int rij,int kolom);
    bool tweedeKlik(int rij,int kolom);
    void initialiseerRonde();
    void clearMogelijkeZetten();
    bool aiBeurt();
    void setTegenAi();
    bool getTegenAi() const;
    void setBeginnersModus();
    bool getBeginnersModus() const;

public slots:
    void volgendeRonde();

signals:
    void veranderDobbelsteen(std::string eerste, std::string tweede);
    void pionVerslaan(int rij, int kolom);
    void puntenVeranderen(int totaal, std::string speler);
    void spelIsGedaan(int ptnZwart, int ptnGroen, int ptnRood, int ptnGeel);
    void loadGame();

private:
    Bord m_spelbord;
    Dobbelstenen m_dobbelstenen;
    ChaturajiPion::Team m_speler;
    vector<Speler> m_spelerVector;
    ChaturajiPion* m_pionDieNogEenZetMag{ nullptr };
    std::vector<int> m_mogelijkeZetten;
    std::tuple<int, int> m_coordinatenEersteKlik;
    int m_beurt{ -1 };
    int m_aantalVerslagenKoningen{ 0 };
    bool m_tegenAi{ false };
    bool m_beginnersModus{ false };
};

#endif // CHATURAJISPEL_H
