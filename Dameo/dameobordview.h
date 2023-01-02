#ifndef DAMEOBORDVIEW_H
#define DAMEOBORDVIEW_H
#include "qlineedit.h"
#pragma once
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPushButton>
#include "bordcelview.h"
#include "dameospel.h"
#include "pionview.h"

class DameoBordView : public QGraphicsScene
{
    Q_OBJECT
public:
    DameoBordView(int grootteBord, DameoSpel *spel, QObject *parent = nullptr);
    BordCelView* speelbord[8][8];

public slots:
    void verwijderPionVanBord(int rij, int kolom);
    void promoveerPion(int rij, int kolom, int parameterSpeler);
    void toonWinnaar(QString winnaar);
    void eventSaveKnop();
    void eventLoadKnop();
    void reloadBord();
    void aiKnop();
    void beginnersModusKnop();

private:
    int m_grootteBord;
    QPushButton *m_aiKnop;
    QPushButton *m_beginnersModusKnop;
    QLineEdit *m_saveName;
    QLineEdit *m_loadName;
    BordCelView *lastClicked{nullptr};
    DameoSpel *m_spel;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    std::vector<int> mogelijkeZetten{};
};

#endif // BORDVIEW_H
