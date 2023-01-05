#ifndef DAMEOSPEL_H
#define DAMEOSPEL_H

#pragma once

#include <QObject>
#include "bord.h"
#include "zet.h"


class DameoSpel : public QObject
{
    Q_OBJECT
public:
    DameoSpel(Bord spelbord);
    int isGedaan() const;
    void vindEnMaakZet();
    void vindAlleZettenVoorPion(Bord spelbord, DameoPion::Team team, DameoPion* p, bool moetPakken);
    int loadSpel(QString naam);
    void saveSpel(QString naam);
    void maakNieuwePion(char teken, char xCoord, char Ycoord, char team);
    Bord getBord();
    std::vector<int> eersteKlik(int rij,int kolom);
    bool tweedeKlik(int rij,int kolom);
    QPair<int, int> pionDieVerwijderdMoetWorden();
    void clearMogelijkeZetten();
    void veranderBeurt();
    void setTegenAi();
    bool getTegenAi();
    bool aiBeurt();
    void setBeginnersModus();
    bool getBeginnersModus();

signals:
    void pionVerslaan(int rij, int kolom);
    void pionPromoveren(int rij, int kolom, int parameterSpeler);
    void spelGedaan(QString winnaar);
    void loadGame();

private:
    bool m_tegenAi{false};
    bool m_beginnersModus{false};
    DameoPion* m_pionDieNogEenZetMag{nullptr};
    std::vector<int> m_mogelijkeZetten;
    std::tuple<int, int> coordinatenEersteKlik;
    Bord m_spelbord;
    int m_beurt{ 1 };
    Pion::Team m_speler;
};
#endif // DAMEOSPEL_H
