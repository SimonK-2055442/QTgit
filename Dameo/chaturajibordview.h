#ifndef CHATURAJIBORDVIEW_H
#define CHATURAJIBORDVIEW_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "bordcelview.h"
#include "chaturajispel.h"

class ChaturajiBordView : public QGraphicsScene
{
public:
    ChaturajiBordView(int grootteBord, ChaturajiSpel spel, QObject *parent = nullptr);
    BordCelView* speelbord[8][8];
    //virtual ~ChaturajiBordView() {};

//public slots:
    //void verwijderPionVanBord(int rij, int kolom);

private:
    BordCelView *lastClicked{nullptr};
    ChaturajiSpel m_spel;
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
    std::vector<int> mogelijkeZetten{};
};


#endif // CHATURAJIBORDVIEW_H
