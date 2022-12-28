#include "welcome.h"

Welcome::Welcome(QWidget *parent) : QGraphicsScene{parent} {
    buttonDameo = new QPushButton();
    buttonDameo->setGeometry(0,0,200,50);
    buttonDameo->setText("Dameo");
    addWidget(buttonDameo);

    buttonChaturaji = new QPushButton();
    buttonChaturaji->setGeometry(300,0,200,50);
    buttonChaturaji->setText("Chaturaji");
    addWidget(buttonChaturaji);

    // met een QGridLayout werken is praktischer, maar werkt voorlopig nog niet
    /*setLayout(rooster); //werkt niet,
    rooster->addWidget(buttonDameo, 0, 0);
    rooster->addWidget(buttonChaturaji, 0, 1);*/

    connect(buttonDameo, &QPushButton::clicked, this, &Welcome::slotButtonDameo);
    connect(buttonChaturaji, &QPushButton::clicked, this, &Welcome::slotButtonChaturaji);
}

void Welcome::slotButtonDameo() {
    qDebug() <<"hallo dameo";
}

void Welcome::slotButtonChaturaji() {
    qDebug() <<"hallo chaturaji";
}
