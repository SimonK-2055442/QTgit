#ifndef BORDCELVIEW_H
#define BORDCELVIEW_H

#include <QGraphicsRectItem>

class BordCelView : public QGraphicsRectItem
{
public:
    BordCelView(int rij, int kolom);
    BordCelView();
};

#endif // BORDCELVIEW_H