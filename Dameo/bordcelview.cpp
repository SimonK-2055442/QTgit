//Auteur: Yara Mijnendonckx

#include "bordcelview.h"


BordCelView::BordCelView(int rij, int kolom) : QGraphicsRectItem{0, 0, 95, 95} {
    setBrush(QBrush(Qt::white));
    setPos((95+1) * kolom, (95+1) * rij);
    setFlag(QGraphicsItem::ItemIsSelectable);
}
