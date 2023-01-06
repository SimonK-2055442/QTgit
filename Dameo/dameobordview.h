#ifndef DAMEOBORDVIEW_H
#define DAMEOBORDVIEW_H

#pragma once

#include <QLabel>
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "bordcelview.h"
#include "dameospel.h"


class DameoBordView : public QGraphicsScene {
    Q_OBJECT

public:
    DameoBordView(int grootteBord, DameoSpel *spel, QObject *parent = nullptr);

public slots:
    void verwijderPionVanBord(int rij, int kolom);
    void promoveerPion(int rij, int kolom, int parameterSpeler);
    void toonWinnaar(QString winnaar);
    void eventSaveKnop() const;
    void eventLoadKnop() const;
    void aiKnop() const;
    void beginnersModusKnop() const;
    void reloadBord();

private:
    DameoSpel *m_spel;
    BordCelView *m_speelbord[8][8];
    std::vector<int> m_mogelijkeZetten{};
    BordCelView *m_lastClicked{nullptr};
    int m_grootteBord;
    int m_rijVerslagenPionnen{ 0 };
    int m_kolomVerslagenPionnen{ 0 };
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QLineEdit *m_saveName;
    QLineEdit *m_loadName;
    QPushButton *m_aiKnop;
    QPushButton *m_beginnersModusKnop;
};

#endif // BORDVIEW_H
