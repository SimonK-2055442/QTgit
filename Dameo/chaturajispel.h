#ifndef CHATURAJISPEL_H
#define CHATURAJISPEL_H


#pragma once

#include <string>
#include "ChaturajiPion.h"
#include "ChaturajiKoning.h"
#include "Dobbelstenen.h"
#include "Speler.h"

class ChaturajiSpel {
public:
    ChaturajiSpel(Bord spelbord);
    void startSpel(int spelKeuze);
    int vertaal(string teVertalen) const;
    void vindEnMaakZet(Speler* speler);
    bool isGedaan() const;
    Zet vraagZet(Speler* spelerAanBeurt);
    bool stukMagVerplaatstWorden(Pion* p, bool echt);
    bool checkZet(Zet zet, Pion* p, Pion::Team teamSpeler, int spelKeuze, bool echt);
    void saveSpel(int i);
    int loadSpel();
    void eindeSpel();
    void maakNieuwePion(char type, char xCoord, char Ycoord, char team);
    void setSpelbord(Bord bord);
    Bord getSpelbord();
    vector<string> vindAlleZettenVoorPion(Pion* p, Speler* spelerAanBeurt);
private:
    Bord m_spelbord;
    int m_beurt{ 1 };
    Dobbelstenen m_dobbelstenen;
    ChaturajiPion::Team m_speler;
    vector<Speler> m_spelerVector;
};
#endif // CHATURAJISPEL_H
