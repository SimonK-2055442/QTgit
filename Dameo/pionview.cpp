#include "pionview.h"

PionView::PionView(TypePion type, QGraphicsItem *parent) : QGraphicsPixmapItem()
{
    //QPointF positie = parent->pos();
    //setPos(positie.x() + 17, positie.y() + 5);

    //setFlag(QGraphicsItem::ItemIsSelectable);

    if (type == TypePion::dameoWit) {
        setPixmap(QPixmap(":/images/pion_wit.png"));
    }
    else if (type == TypePion::dameoZwart) {
        setPixmap(QPixmap(":/images/pion_zwart.png"));
    }
    else if (type == TypePion::dameoKWit) {
        QPixmap pixmap(":/images/DameoKWit.png");
        setPixmap(pixmap.scaled(90,90));
    }
    else if (type == TypePion::dameoKZwart) {
        QPixmap pixmap(":/images/DameoKZwart.png");
        setPixmap(pixmap.scaled(90,90));
    }
    else if (type == TypePion::groenPion) {
        QPixmap pixmap(":/images/groenPion.png");
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::groenPaard) {
        QPixmap pixmap(":/images/groenPaard.png");
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::groenKoning) {
        QPixmap pixmap(":/images/groenKoning.png");
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::groenOlifant) {
        QPixmap pixmap(":/images/groenOlifant.png");
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::groenBoot) {
        QPixmap pixmap(":/images/groenBoot.png");
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::geelPion) {
        QPixmap pixmap(":/images/geelPion.png");
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::geelPaard) {
        QPixmap pixmap(":/images/geelPaard.png");
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::geelKoning) {
        QPixmap pixmap(":/images/geelKoning.png");
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::geelOlifant) {
        QPixmap pixmap(":/images/geelOlifant.png");
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::geelBoot) {
        QPixmap pixmap(":/images/geelBoot.png");
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::roodPion) {
        QPixmap pixmap(":/images/roodPion.png");
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::roodPaard) {
        QPixmap pixmap(":/images/roodPaard.png");
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::roodKoning) {
        QPixmap pixmap(":/images/roodKoning.png");
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::roodOlifant) {
        QPixmap pixmap(":/images/roodOlifant.png");
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::roodBoot) {
        QPixmap pixmap(":/images/roodBoot.png");
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::zwartPion) {
        QPixmap pixmap(":/images/zwartPion.png");
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::zwartPaard) {
        QPixmap pixmap(":/images/zwartPaard.png");
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::zwartKoning) {
        QPixmap pixmap(":/images/zwartKoning.png");
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::zwartOlifant) {
        QPixmap pixmap(":/images/zwartOlifant.png");
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::zwartBoot) {
        QPixmap pixmap(":/images/zwartBoot.png");
        setPixmap(pixmap.scaled(95,95));
    }
}
