#ifndef CHATURAJIBORDVIEW_H
#define CHATURAJIBORDVIEW_H

#pragma once

#include <QLabel>
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "bordcelview.h"
#include "chaturajispel.h"


class ChaturajiBordView : public QGraphicsScene {
    Q_OBJECT

public:
    ChaturajiBordView(int grootteBord, ChaturajiSpel *spel, QObject *parent = nullptr);

public slots:
    void veranderDobbelstenen(std::string eerste, std::string tweede);
    void verhoogPunten(int totaal, std::string speler);
    void verwijderPionVanBord(int rij, int kolom);
    void bepaalWinnaar(int ptnZwart, int ptnGroen, int ptnRood, int ptnGeel);
    void eventSaveKnop() const;
    void eventLoadKnop() const;
    void aiKnop() const;
    void beginnersModusKnop() const;
    void reloadBord();

private:
    ChaturajiSpel *m_spel;
    BordCelView *m_speelbord[8][8];
    std::vector<int> m_mogelijkeZetten{};
    BordCelView *m_lastClicked{nullptr};
    int m_grootteBord;
    int m_rijVerslagenPionnen{ 0 };
    int m_kolomVerslagenPionnen{ 0 };
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void voegPionnenToe() const;
    void voegPuntentellingToe();
    QLabel *m_geroldeDobbelsteen1;
    QLabel *m_geroldeDobbelsteen2;
    QLineEdit *m_saveName;
    QLineEdit *m_loadName;
    QPushButton *m_aiKnop;
    QPushButton *m_beginnersModusKnop;
    QLabel *m_puntenZwart;
    QLabel *m_puntenGroen;
    QLabel *m_puntenRood;
    QLabel *m_puntenGeel;
};

#endif // CHATURAJIBORDVIEW_H
