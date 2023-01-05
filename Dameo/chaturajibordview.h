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
    BordCelView* speelbord[8][8];

public slots:
    void veranderDobbelstenen(std::string eerste, std::string tweede);
    void verhoogPunten(int totaal, std::string speler);
    void verwijderPionVanBord(int rij, int kolom);
    void bepaalWinnaar(int ptnZwart, int ptnGroen, int ptnRood, int ptnGeel);
    void eventSaveKnop();
    void eventLoadKnop();
    void aiKnop();
    void beginnersModusKnop();
    void reloadBord();

private:
    ChaturajiSpel *m_spel;
    std::vector<int> mogelijkeZetten{};
    BordCelView *lastClicked{nullptr};
    int m_grootteBord;
    int m_rijVerslagenPionnen{ 0 };
    int m_kolomVerslagenPionnen{ 0 };
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void voegPionnenToe();
    void voegPuntentellingToe();
    QLabel *m_geroldeDobbelsteen1;
    QLabel *m_geroldeDobbelsteen2;
    QLineEdit *m_saveName;
    QLineEdit *m_loadName;
    QPushButton* m_aiKnop;
    QPushButton* m_beginnersModusKnop;
    QLabel *aantalPuntenZwart;
    QLabel *aantalPuntenGroen;
    QLabel *aantalPuntenRood;
    QLabel *aantalPuntenGeel;
};

#endif // CHATURAJIBORDVIEW_H
