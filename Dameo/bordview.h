#ifndef BORDVIEW_H
#define BORDVIEW_H
#pragma once
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
//#include "bord.h"
#include "bordcelview.h"
#include "dameospel.h"
//#include "pionview.h"

class BordView : public QGraphicsScene
{
public:
    BordView(int grootteBord, DameoSpel spel, QObject *parent = nullptr);
    BordCelView* speelbord[8][8];

public slots:
    void verwijderPionVanBord(int rij, int kolom);

private:
    BordCelView *lastClicked{nullptr};
    DameoSpel m_spel;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    std::vector<int> mogelijkeZetten{};
};

#endif // BORDVIEW_H
