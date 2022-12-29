#ifndef DAMEOSPEL_H
#define DAMEOSPEL_H

//#include "bordview.h"
#pragma once

#include "bord.h"
#include "zet.h"
#include <QObject>

class DameoSpel : public QObject
{
    Q_OBJECT
public:
    DameoSpel(Bord spelbord);
    int vertaal(string teVertalen) const;
    void startSpel(int spelKeuze);
    int isGedaan() const;
    void vindEnMaakZet() const;
    void vindAlleZettenVoorPion(Bord spelbord, DameoPion::Team team, DameoPion* p, bool moetPakken);
    int loadSpel();
    void saveSpel(int i);
    void maakNieuwePion(char type, char xCoord, char Ycoord, char team);
    Bord getBord();
    std::vector<int> eersteKlik(int rij,int kolom);
    bool tweedeKlik(int rij,int kolom);
    QPair<int, int> pionDieVerwijderdMoetWorden();
    void clearMogelijkeZetten();

signals:
    void pionVerslaan(int rij, int kolom);

private:
    //BordView *m_bord;
    std::vector<int> m_mogelijkeZetten;
    std::tuple<int, int> coordinatenEersteKlik;
    Bord m_spelbord;
    int m_beurt{ 1 };
    Pion::Team m_speler;
};
#endif // DAMEOSPEL_H
