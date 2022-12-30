#ifndef CHATURAJISPEL_H
#define CHATURAJISPEL_H


#pragma once

#include <string>
#include "ChaturajiPion.h"
#include "ChaturajiKoning.h"
#include "Dobbelstenen.h"
#include "Speler.h"
#include <QObject>

class ChaturajiSpel: public QObject {
    Q_OBJECT
public:
    ChaturajiSpel(Bord spelbord);
    void vindEnMaakZet(Speler* speler);
    bool isGedaan() const;
    bool checkZet(Zet zet, Pion* p, Pion::Team teamSpeler, int spelKeuze, bool echt);
    bool stukMagVerplaatstWorden(Pion* p, bool echt);
    void saveSpel(int i);
    int loadSpel();
    void eindeSpel();
    void maakNieuwePion(char type, char xCoord, char Ycoord, char team);
    void setSpelbord(Bord bord);
    Bord getSpelbord();
    void vindAlleZettenVoorPion(Pion* p, Speler* spelerAanBeurt);
    std::vector<int> eersteKlik(int rij,int kolom);
    bool tweedeKlik(int rij,int kolom);
    void clearMogelijkeZetten();

public slots:
    void initialiseerRonde();

signals:
    void pionVerslaan(int rij, int kolom);
    void veranderDobbelsteen(string eerste, string tweede);

private:
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
