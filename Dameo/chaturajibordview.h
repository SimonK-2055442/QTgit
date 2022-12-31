#ifndef CHATURAJIBORDVIEW_H
#define CHATURAJIBORDVIEW_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
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
    void zetPionnen();
    //virtual ~ChaturajiBordView() {};



public slots:
    void verwijderPionVanBord(int rij, int kolom);
    void veranderDobbelstenen(string eerste, string tweede);
    void eventSaveKnop();
    void eventLoadKnop();
    void reloadBord();

private:
    int m_grootteBord;
    QLineEdit *m_saveName;
    QLineEdit *m_loadName;
    QLabel* m_geroldeDobbelsteen1;
    QLabel* m_geroldeDobbelsteen2;
    BordCelView *lastClicked{nullptr};
    ChaturajiSpel *m_spel;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    std::vector<int> mogelijkeZetten{};
};


#endif // CHATURAJIBORDVIEW_H
