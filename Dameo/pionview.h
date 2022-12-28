#ifndef PIONVIEW_H
#define PIONVIEW_H

#include <QGraphicsPixmapItem>

class PionView : public QGraphicsPixmapItem
{
public:
    PionView(QString type, QGraphicsItem *parent = nullptr);
};

#endif // PIONVIEW_H
