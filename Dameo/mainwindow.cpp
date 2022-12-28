#include "mainwindow.h"
#include "dameospel.h"
#include "welcome.h"
#include <QGraphicsView>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QPushButton* p = new QPushButton(this);
    p->setGeometry(300,0,200,50);
    p->setText("Chaturaji");
    QObject::connect(p, SIGNAL (clicked()), this, SLOT (buttonpressed()));
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

void MainWindow::buttonpressed(){
    Bord speelbord;
    speelbord.initialiseerBord(Bord::KeuzeSpel::dameo);
    DameoSpel spel(speelbord);
    BordView* sceneBord = new BordView(8, spel);
    view = new QGraphicsView{sceneBord};
    setCentralWidget(view);
}
