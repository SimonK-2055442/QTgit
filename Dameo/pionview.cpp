#include "pionview.h"

PionView::PionView(QString type, QGraphicsItem *parent) : QGraphicsPixmapItem()
{
    QPointF positie = parent->pos();
    //setPos(positie.x() + 17, positie.y() + 5);

    //setFlag(QGraphicsItem::ItemIsSelectable);

    if (type == "DameoWit") {
        setPixmap(QPixmap(":/images/pion_wit.png"));
    }
    else if (type == "DameoZwart"){
        setPixmap(QPixmap(":/images/pion_zwart.png"));
    }
    else if (type == "DameoKWit"){
        QPixmap pixmap(":/images/DameoKWit.png");
        setPixmap(pixmap.scaled(90,90));
    }
    else if (type == "DameoKZwart"){
        QPixmap pixmap(":/images/DameoKZwart.png");
        setPixmap(pixmap.scaled(90,90));
    }
    else if (type == "GroenPion"){
        QPixmap pixmap2(":/images/groenPion.png");
        setPixmap(pixmap2.scaled(95,95));
    }
    else if (type == "GroenPaard"){
        QPixmap pixmap2(":/images/groenPaard.png");
        setPixmap(pixmap2.scaled(95,95));
    }
    else if (type == "GroenKoning"){
        QPixmap pixmap2(":/images/groenKoning.png");
        setPixmap(pixmap2.scaled(95,95));    }
    else if (type == "GroenOlifant"){
        QPixmap pixmap2(":/images/groenOlifant.png");
        setPixmap(pixmap2.scaled(95,95));    }
    else if (type == "GroenBoot"){
        QPixmap pixmap2(":/images/groenBoot.png");
        setPixmap(pixmap2.scaled(95,95));    }
    else if (type == "GeelPion"){
        QPixmap pixmap2(":/images/geelPion.png");
        setPixmap(pixmap2.scaled(95,95));    }
    else if (type == "GeelPaard"){
        QPixmap pixmap2(":/images/geelPaard.png");
        setPixmap(pixmap2.scaled(95,95));    }
    else if (type == "GeelKoning"){
        QPixmap pixmap2(":/images/geelKoning.png");
        setPixmap(pixmap2.scaled(95,95));    }
    else if (type == "GeelOlifant"){
        QPixmap pixmap2(":/images/geelOlifant.png");
        setPixmap(pixmap2.scaled(95,95));    }
    else if (type == "GeelBoot"){
        QPixmap pixmap2(":/images/geelBoot.png");
        setPixmap(pixmap2.scaled(95,95));    }
    else if (type == "RoodPion"){
        QPixmap pixmap2(":/images/roodPion.png");
        setPixmap(pixmap2.scaled(95,95));    }
    else if (type == "RoodPaard"){
        QPixmap pixmap2(":/images/roodPaard.png");
        setPixmap(pixmap2.scaled(95,95));    }
    else if (type == "RoodKoning"){
        QPixmap pixmap2(":/images/roodKoning.png");
        setPixmap(pixmap2.scaled(95,95));    }
    else if (type == "RoodOlifant"){
        QPixmap pixmap2(":/images/roodOlifant.png");
        setPixmap(pixmap2.scaled(95,95));    }
    else if (type == "RoodBoot"){
        QPixmap pixmap2(":/images/roodBoot.png");
        setPixmap(pixmap2.scaled(95,95));    }
    else if (type == "ZwartPion"){
        QPixmap pixmap2(":/images/zwartPion.png");
        setPixmap(pixmap2.scaled(95,95));    }
    else if (type == "ZwartPaard"){
        QPixmap pixmap2(":/images/zwartPaard.png");
        setPixmap(pixmap2.scaled(95,95));    }
    else if (type == "ZwartKoning"){
        QPixmap pixmap2(":/images/zwartKoning.png");
        setPixmap(pixmap2.scaled(95,95));    }
    else if (type == "ZwartOlifant"){
        QPixmap pixmap2(":/images/zwartOlifant.png");
        setPixmap(pixmap2.scaled(95,95));    }
    else if (type == "ZwartBoot"){
        QPixmap pixmap2(":/images/zwartBoot.png");
        setPixmap(pixmap2.scaled(95,95));    }
}
