#ifndef BORD_H
#define BORD_H

#pragma once

#include "windows.h"
#include <vector>
#include <iostream>
#include <string>
#include "zet.h"
//#include "dameopion.h"
//#include "bordview.h"
#include "qgraphicssceneevent.h"
#include "pion.h"

//class BordView;
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

public slots:
    //void linkerMuisKlik(QGraphicsSceneMouseEvent *event);
    //void rechterMuisKlik();

private:
    vector<Pion*> pionnen;
    int grootteBord = 8;
    //BordCelView *lastClicked{nullptr};
};

#endif // BORD_H
