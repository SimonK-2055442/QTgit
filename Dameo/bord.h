#ifndef BORD_H
#define BORD_H

#pragma once

#include "windows.h"
#include <vector>
#include <iostream>
#include <string>
#include "zet.h"
#include "qgraphicssceneevent.h"
#include "pion.h"

class BordCelView;
using namespace std;

class Bord {
public:
    void laatZien() const;
    Pion* zoekPionOpCoordinaat(int yCoord, int xCoord) const;
    Pion* getPionVanLijst(int index) const;
    void verwijderPointers();
    enum class KeuzeSpel { chaturaji, dameo };
    void initialiseerBord(KeuzeSpel spel);
    bool isZetInHetBord(Zet zet) const;
    void vervangElement(Zet zet);
    void voegPionToe(bool dameo, char type, int xCoord, int yCoord, Pion::Team team);

private:
    vector<Pion*> pionnen;
    int grootteBord = 8;
};

#endif // BORD_H
