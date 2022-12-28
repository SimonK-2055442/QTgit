#ifndef PIONVIEW_H
#define PIONVIEW_H

#include <QGraphicsPixmapItem>

class PionView : public QGraphicsPixmapItem
{
public:
    PionView(QString kleur, QGraphicsItem *parent = nullptr);
};

#endif // PIONVIEW_H
