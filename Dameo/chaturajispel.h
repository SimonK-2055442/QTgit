#ifndef CHATURAJISPEL_H
#define CHATURAJISPEL_H


#pragma once

#include <string>
#include "ChaturajiPion.h"
#include "ChaturajiKoning.h"
#include "Dobbelstenen.h"
#include "Speler.h"
#include <QObject>
#include <QString>

class ChaturajiSpel: public QObject {
    Q_OBJECT
public:
    ChaturajiSpel(Bord spelbord);
    void vindEnMaakZet(Speler* speler);
    bool isGedaan() const;
    bool checkZet(Zet zet, Pion* p, Pion::Team teamSpeler, int spelKeuze, bool echt);
    bool stukMagVerplaatstWorden(Pion* p, bool echt);
    void saveSpel(QString naam);
    int loadSpel(QString naam);
    void eindeSpel();
    void maakNieuwePion(char type, char xCoord, char Ycoord, char team);
    void setSpelbord(Bord bord);
    Bord getSpelbord();
    void vindAlleZettenVoorPion(Pion* p, Speler* spelerAanBeurt);
    std::vector<int> eersteKlik(int rij,int kolom);
    bool tweedeKlik(int rij,int kolom);
    void clearMogelijkeZetten();
    void setTegenAi();
    bool getTegenAi();
    bool aiBeurt();
    void initialiseerRonde();

public slots:
    //void initialiseerRonde();
    void volgendeRonde();

signals:
    void loadGame();
    void pionVerslaan(int rij, int kolom);
    void veranderDobbelsteen(string eerste, string tweede);

private:
    bool m_tegenAi{false};
    ChaturajiPion* m_pionDieNogEenZetMag{nullptr};
    std::vector<int> m_mogelijkeZetten;
    std::tuple<int, int> coordinatenEersteKlik;
    Bord m_spelbord;
    int m_beurt{ -1 };
    Dobbelstenen m_dobbelstenen;
    ChaturajiPion::Team m_speler;
    vector<Speler> m_spelerVector;
};
#endif // CHATURAJISPEL_H
