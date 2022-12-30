#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QPushButton* dameo = new QPushButton(this);
    QPushButton* chaturaji = new QPushButton(this);
    dameo->setGeometry(300,300,200,50);
    chaturaji->setGeometry(800,300,200,50);
    dameo->setText("Dameo");
    chaturaji->setText("Chaturaji");
    QObject::connect(dameo, SIGNAL (clicked()), this, SLOT (DameoButtonPressed()));
    QObject::connect(chaturaji, SIGNAL (clicked()), this, SLOT (ChaturajiButtonPressed()));
}

void MainWindow::DameoButtonPressed() {
    Bord spelbord;
    spelbord.initialiseerBord(Bord::KeuzeSpel::dameo);
    DameoSpel *spel = new DameoSpel(spelbord);
    dameoBord = new BordView(8, spel);
    view = new QGraphicsView{dameoBord};
    setCentralWidget(view);

    menuToevoegen();
}

void MainWindow::ChaturajiButtonPressed() {
    Bord spelbord;
    spelbord.initialiseerBord(Bord::KeuzeSpel::chaturaji);
    ChaturajiSpel *spel = new ChaturajiSpel(spelbord);
    chaturajiBord = new ChaturajiBordView(8, spel);
    view = new QGraphicsView{chaturajiBord};
    setCentralWidget(view);

    menuToevoegen();
}

void MainWindow::menuToevoegen() {
    QMenuBar *menu = new QMenuBar();
    QMenu *gameMenu = new QMenu("Game");
    QMenu *dameoMenu = new QMenu("Dameo");
    QMenu *chaturajiMenu = new QMenu("Chaturaji");
    menu->addMenu(gameMenu);
    menu->addMenu(dameoMenu);
    menu->addMenu(chaturajiMenu);

    QAction *saveAction = new QAction("Save", this);
    QAction *loadAction = new QAction("Load", this);
    gameMenu->addAction(saveAction);
    gameMenu->addAction(loadAction);

    setMenuBar(menu);
}
