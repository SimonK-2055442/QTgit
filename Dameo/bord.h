#ifndef BORD_H
#define BORD_H

#pragma once

#include <vector>
#include "zet.h"
#include "pion.h"

class BordCelView;


class Bord {
public:
    enum class KeuzeSpel { chaturaji, dameo };
    void initialiseerBord(KeuzeSpel spel);
    bool isZetInHetBord(Zet zet) const;
    Pion* zoekPionOpCoordinaat(int yCoord, int xCoord) const;
    Pion* getPionVanLijst(int index) const;
    void voegPionToe(bool dameo, char type, int xCoord, int yCoord, Pion::Team team);
    void vervangElement(Zet zet);
    void verwijderPointers();
    vector<Pion*> getPionnen();

private:
    vector<Pion*> pionnen;
    int grootteBord = 8;
};

#endif // BORD_H
