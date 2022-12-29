#ifndef BORDCELVIEW_H
#define BORDCELVIEW_H

#include "pionview.h"
#include <QBrush>
#include <QGraphicsRectItem>

class BordCelView : public QGraphicsRectItem
{
public:
    BordCelView(int rij, int kolom);
    BordCelView();
    void setChild(PionView* child);
    PionView* getChild();
private:
    PionView* m_child;
};


#endif // BORDCELVIEW_H
