#ifndef CHATURAJIBORDVIEW_H
#define CHATURAJIBORDVIEW_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPushButton>
#include "bordcelview.h"
#include "chaturajispel.h"
#include "qlabel.h"
#include "qlineedit.h"

class ChaturajiBordView : public QGraphicsScene
{
    Q_OBJECT
public:
    ChaturajiBordView(int grootteBord, ChaturajiSpel *spel, QObject *parent = nullptr);
    BordCelView* speelbord[8][8];
    void plaatsPionnen();
    //virtual ~ChaturajiBordView() {};

public slots:
    void verwijderPionVanBord(int rij, int kolom);
    void verhoogPunten(int totaal, string speler);
    void veranderDobbelstenen(string eerste, string tweede);
    void eventSaveKnop();
    void eventLoadKnop();
    void reloadBord();
    void aiKnop();
    void beginnersModusKnop();
    void bepaalWinnaar(int ptnZwart, int ptnGroen, int ptnRood, int ptnGeel);

private:
    QPushButton* m_aiKnop;
    QPushButton* m_beginnersModusKnop;
    int m_grootteBord;
    QLineEdit *m_saveName;
    QLineEdit *m_loadName;
    QLabel *m_geroldeDobbelsteen1;
    QLabel *m_geroldeDobbelsteen2;
    QLabel *aantalPuntenZwart;
    QLabel *aantalPuntenGroen;
    QLabel *aantalPuntenRood;
    QLabel *aantalPuntenGeel;
    BordCelView *lastClicked{nullptr};
    ChaturajiSpel *m_spel;
    void voegPuntentellingToe();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    std::vector<int> mogelijkeZetten{};
};


#endif // CHATURAJIBORDVIEW_H
