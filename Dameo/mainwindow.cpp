#include "mainwindow.h"
#include "dameospel.h"
#include "welcome.h"
#include <QGraphicsView>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QPushButton* dameo = new QPushButton(this);
    QPushButton* chaturaji = new QPushButton(this);
    dameo->setGeometry(300,300,200,50);
    chaturaji->setGeometry(800,300,200,50);
    dameo->setText("Dameo");
    chaturaji->setText("Chaturaji");
    QObject::connect(dameo, SIGNAL (clicked()), this, SLOT (DameoButtonPressed()));
    QObject::connect(chaturaji, SIGNAL (clicked()), this, SLOT (ChaturajiButtonPressed()));
    // om het spel te testen:
    // dit uit commentaar halen en regel 22 en 23 in commentaar zetten
    /*Bord speelbord;
    speelbord.initialiseerBord(Bord::KeuzeSpel::dameo);
    DameoSpel spel(speelbord);
    BordView* sceneBord = new BordView(8, spel);
    view = new QGraphicsView{sceneBord};*/

    //MainWindow::connect(spel, spel.clearMogelijkeZetten(),sceneBord, sceneBord->style())
    //sceneBord = new BordView(8,speelbord);
    //view->show();

    // om het opstartscherm te testen:
    // dit uit commentaar halen en regel 10 tem 14 in commentaar zetten
    //Welcome* opstartScherm = new Welcome();
    //view = new QGraphicsView{opstartScherm};
    //test voor github nummer 2
    //setCentralWidget(view);
}

void MainWindow::DameoButtonPressed(){
    Bord speelbord;
    speelbord.initialiseerBord(Bord::KeuzeSpel::dameo);
    DameoSpel spel(speelbord);
    BordView* sceneBord = new BordView(8, spel);
    view = new QGraphicsView{sceneBord};
    setCentralWidget(view);
}

void MainWindow::ChaturajiButtonPressed(){
    //Bord speelbord;
    //speelbord.initialiseerBord(Bord::KeuzeSpel::chaturaji);
    //ChaturajiSpel(speelbord);
    ///BordView* sceneBord = new BordView(8, spel);
    //view = new QGraphicsView{sceneBord};
    //setCentralWidget(view);
}