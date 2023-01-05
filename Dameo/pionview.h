#ifndef PIONVIEW_H
#define PIONVIEW_H

#include <QGraphicsPixmapItem>

class PionView : public QGraphicsPixmapItem
{
public:
    enum TypePion { dameoWit, dameoZwart, dameoKWit, dameoKZwart,
        groenPion, groenPaard, groenKoning, groenOlifant, groenBoot,
        geelPion, geelPaard, geelKoning, geelOlifant, geelBoot,
        roodPion, roodPaard, roodKoning, roodOlifant, roodBoot,
        zwartPion, zwartPaard, zwartKoning, zwartOlifant, zwartBoot};
    PionView(TypePion type, QGraphicsItem *parent = nullptr);
};

#endif // PIONVIEW_H
