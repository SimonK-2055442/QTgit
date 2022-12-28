#include "pionview.h"

PionView::PionView(QString kleur, QGraphicsItem *parent) : QGraphicsPixmapItem()
{
    QPointF positie = parent->pos();
    setPos(positie.x() + 17, positie.y() + 5);

    //setFlag(QGraphicsItem::ItemIsSelectable);

    if (kleur == "wit") {
        setPixmap(QPixmap(":/images/pion_wit.png"));
    } else {
        setPixmap(QPixmap(":/images/pion_zwart.png"));
    }
}
