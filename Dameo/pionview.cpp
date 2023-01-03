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
        QPixmap pixmap(":/images/groenPion.png"); //[1]
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::groenPaard) {
        QPixmap pixmap(":/images/groenPaard.png"); //[1]
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::groenKoning) {
        QPixmap pixmap(":/images/groenKoning.png"); //[1]
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::groenOlifant) {
        QPixmap pixmap(":/images/groenOlifant.png"); //[1]
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::groenBoot) {
        QPixmap pixmap(":/images/groenBoot.png"); //[1]
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::geelPion) {
        QPixmap pixmap(":/images/geelPion.png"); //[1]
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::geelPaard) {
        QPixmap pixmap(":/images/geelPaard.png"); //[1]
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::geelKoning) {
        QPixmap pixmap(":/images/geelKoning.png"); //[1]
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::geelOlifant) {
        QPixmap pixmap(":/images/geelOlifant.png"); //[1]
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::geelBoot) {
        QPixmap pixmap(":/images/geelBoot.png"); //[1]
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::roodPion) {
        QPixmap pixmap(":/images/roodPion.png"); //[1]
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::roodPaard) {
        QPixmap pixmap(":/images/roodPaard.png"); //[1]
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::roodKoning) {
        QPixmap pixmap(":/images/roodKoning.png"); //[1]
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::roodOlifant) {
        QPixmap pixmap(":/images/roodOlifant.png"); //[1]
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::roodBoot) {
        QPixmap pixmap(":/images/roodBoot.png"); //[1]
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::zwartPion) {
        QPixmap pixmap(":/images/zwartPion.png"); //[1]
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::zwartPaard) {
        QPixmap pixmap(":/images/zwartPaard.png"); //[1]
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::zwartKoning) {
        QPixmap pixmap(":/images/zwartKoning.png"); //[1]
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::zwartOlifant) {
        QPixmap pixmap(":/images/zwartOlifant.png"); //[1]
        setPixmap(pixmap.scaled(95,95));
    }
    else if (type == TypePion::zwartBoot) {
        QPixmap pixmap(":/images/zwartBoot.png"); //[1]
        setPixmap(pixmap.scaled(95,95));
    }
}

/* Bronvermelding afbeeldingen:
 *
 * [1] Wikipedia contributors. (2022, 24 september).
 * Chaturaji. Wikipedia. https://en.wikipedia.org/wiki/Chaturaji
 */
