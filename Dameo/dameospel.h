#ifndef DAMEOSPEL_H
#define DAMEOSPEL_H

#pragma once

#include <QObject>
#include "bord.h"


class DameoSpel : public QObject
{
    Q_OBJECT
public:
    DameoSpel(Bord spelbord);
    void vindEnMaakZet();
    void vindAlleZettenVoorPion(Bord spelbord, DameoPion::Team team, DameoPion* p, bool moetPakken);
    int isGedaan() const;
    void saveSpel(QString naam);
    int loadSpel(QString naam);
    void maakNieuwePion(char teken, char xCoord, char Ycoord, char team);
    Bord getBord();
    std::vector<int> eersteKlik(int rij,int kolom);
    bool tweedeKlik(int rij,int kolom);
    void clearMogelijkeZetten();
    void veranderBeurt();
    bool aiBeurt();
    void setTegenAi();
    bool getTegenAi();
    void setBeginnersModus();
    bool getBeginnersModus();

signals:
    void pionPromoveren(int rij, int kolom, int parameterSpeler);
    void pionVerslaan(int rij, int kolom);
    void spelIsGedaan(QString winnaar);
    void loadGame();

private:
    Bord m_spelbord;
    Pion::Team m_speler;
    DameoPion* m_pionDieNogEenZetMag{ nullptr };
    std::vector<int> m_mogelijkeZetten;
    std::tuple<int, int> m_coordinatenEersteKlik;
    int m_beurt{ 1 };
    bool m_tegenAi{ false };
    bool m_beginnersModus{ false };
};

#endif // DAMEOSPEL_H
