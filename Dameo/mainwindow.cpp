//Auteur: Yara Mijnendonckx en Simon Knuts

#include "mainwindow.h"
#include "dameospel.h"
#include "chaturajispel.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QLabel *tekst = new QLabel(this);
    tekst->setText("Maak uw keuze uit de onderstaande spellen:");
    tekst->setGeometry(300, 100, 1000, 100);
    QFont font("Helvetica", 30, QFont::Bold);
    tekst->setFont(font);

    QPushButton *dameo = new QPushButton(this);
    dameo->setText("Dameo");
    dameo->setGeometry(400, 300, 200, 50);
    QFont fontButton = dameo->font();
    fontButton.setPointSize(11);
    dameo->setFont(fontButton);

    QPushButton *chaturaji = new QPushButton(this);
    chaturaji->setText("Chaturaji");
    chaturaji->setGeometry(800, 300, 200, 50);
    chaturaji->setFont(fontButton);

    QObject::connect(dameo, &QPushButton::clicked, this, &MainWindow::DameoButtonPressed);
    QObject::connect(chaturaji, &QPushButton::clicked, this, &MainWindow::ChaturajiButtonPressed);
}

void MainWindow::DameoButtonPressed() {
    Bord spelbord;
    spelbord.initialiseerBord(Bord::KeuzeSpel::dameo);
    DameoSpel *spel = new DameoSpel(spelbord);
    dameoBord = new DameoBordView(8, spel);
    m_view = new QGraphicsView{dameoBord};
    setCentralWidget(m_view);
}

void MainWindow::ChaturajiButtonPressed() {
    Bord spelbord;
    spelbord.initialiseerBord(Bord::KeuzeSpel::chaturaji);
    ChaturajiSpel *spel = new ChaturajiSpel(spelbord);
    chaturajiBord = new ChaturajiBordView(8, spel);
    m_view = new QGraphicsView{chaturajiBord};
    setCentralWidget(m_view);
}
