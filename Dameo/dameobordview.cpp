//Auteur: Yara Mijnendonckx en Simon Knuts

#include "dameobordview.h"
#include "mainwindow.h"
#include "pionview.h"


DameoBordView::DameoBordView(int grootteBord, DameoSpel *spel, QObject *parent) : QGraphicsScene{parent} {
    m_spel = spel;
    m_grootteBord = grootteBord;
    setBackgroundBrush(QBrush(Qt::gray));

    // maak het bord
    for (int i = 0; i < m_grootteBord; ++i) {
        for (int j = 0; j < m_grootteBord; ++j) {
            m_speelbord[i][j] = new BordCelView{i, j};
            addItem(m_speelbord[i][j]);
        }
    }

    // voeg pionnen toe
    for (int i = 0; i < 36; i++) {
        if (spel->getBord().getPionVanLijst(i)->getTeam() == Pion::Team::blauw) {
            PionView *zwartePion = new PionView{PionView::dameoZwart, m_speelbord[spel->getBord().getPionVanLijst(i)->getYCoordinaat()][spel->getBord().getPionVanLijst(i)->getXCoordinaat()]};
            zwartePion->setParentItem(m_speelbord[spel->getBord().getPionVanLijst(i)->getYCoordinaat()][spel->getBord().getPionVanLijst(i)->getXCoordinaat()]);
            zwartePion->setPos(17, 4);
        } else {
            PionView *wittePion = new PionView{PionView::dameoWit, m_speelbord[spel->getBord().getPionVanLijst(i)->getYCoordinaat()][spel->getBord().getPionVanLijst(i)->getXCoordinaat()]};
            wittePion->setParentItem(m_speelbord[spel->getBord().getPionVanLijst(i)->getYCoordinaat()][spel->getBord().getPionVanLijst(i)->getXCoordinaat()]);
            wittePion->setPos(17, 4);
        }
    }

    QLabel *saveText = new QLabel("Opslaan onder welke naam?");
    saveText->setGeometry(800, 140, 250, 30);
    saveText->setAlignment(Qt::AlignCenter);
    addWidget(saveText);

    m_saveName = new QLineEdit();
    m_saveName->setGeometry(800, 170, 250, 30);
    addWidget(m_saveName);

    QPushButton* saveKnop = new QPushButton("Sla dit spel op");
    saveKnop->setGeometry(800, 200, 250, 60);
    addWidget(saveKnop);

    m_aiKnop = new QPushButton("Druk om tegen de AI te spelen");
    m_aiKnop->setGeometry(800, 300, 250, 30);
    addWidget(m_aiKnop);

    m_beginnersModusKnop = new QPushButton("Druk om beginnersmodus aan te zetten");
    m_beginnersModusKnop->setGeometry(800, 370, 250, 30);
    addWidget(m_beginnersModusKnop);

    QLabel *loadText = new QLabel("Geef de naam van het spel:");
    loadText->setGeometry(800, 440, 250, 30);
    loadText->setAlignment(Qt::AlignCenter);
    addWidget(loadText);

    m_loadName = new QLineEdit();
    m_loadName->setGeometry(800, 470, 250, 30);
    addWidget(m_loadName);

    QPushButton* loadKnop = new QPushButton("Laad een spel");
    loadKnop->setGeometry(800, 500, 250, 60);
    addWidget(loadKnop);

    connect(m_spel, &DameoSpel::pionVerslaan, this, &DameoBordView::verwijderPionVanBord);
    connect(m_spel, &DameoSpel::pionPromoveren, this, &DameoBordView::promoveerPion);
    connect(m_spel, &DameoSpel::spelIsGedaan, this, &DameoBordView::toonWinnaar);
    connect(m_spel, &DameoSpel::loadGame, this, &DameoBordView::reloadBord);

    connect(m_aiKnop, &QPushButton::pressed, this, &DameoBordView::aiKnop);
    connect(m_beginnersModusKnop, &QPushButton::clicked, this, &DameoBordView::beginnersModusKnop);
    connect(saveKnop, &QPushButton::pressed, this, &DameoBordView::eventSaveKnop);
    connect(loadKnop, &QPushButton::pressed, this, &DameoBordView::eventLoadKnop);
}

void DameoBordView::verwijderPionVanBord(int rij, int kolom) {
    QPointF positie(1100 + m_rijVerslagenPionnen*95, m_kolomVerslagenPionnen*95);
    m_speelbord[rij][kolom]->childItems()[0]->setPos(positie);
    m_speelbord[rij][kolom]->childItems()[0]->setParentItem(nullptr);

    m_kolomVerslagenPionnen++;
    if (m_kolomVerslagenPionnen == 8) {
        m_kolomVerslagenPionnen = 0;
        m_rijVerslagenPionnen ++;
    }
}

void DameoBordView::promoveerPion(int rij, int kolom, int parameterSpeler) {
    removeItem(m_speelbord[rij][kolom]->childItems()[0]);
    if (parameterSpeler == -1) {
        PionView *koning = new PionView{PionView::dameoKZwart, m_speelbord[rij][kolom]};
        koning->setParentItem(m_speelbord[rij][kolom]);
    } else {
        PionView *koning = new PionView{PionView::dameoKWit, m_speelbord[rij][kolom]};
        koning->setParentItem(m_speelbord[rij][kolom]);
    }
}

void DameoBordView::toonWinnaar(QString winnaar) {
    MainWindow *nieuwSpel = new MainWindow();
    nieuwSpel->setWindowState(Qt::WindowMaximized);
    nieuwSpel->show();

    QDialog *window = new QDialog();
    window->setWindowTitle("Er is een winnaar!");
    window->setFixedHeight(150);

    QLabel *label = new QLabel("");
    if (winnaar == "wit") {
        label->setText("Speler met de witte pionnen u heeft gewonnen. Proficiat!");
    } else {
        label->setText("Speler met de zwarte pionnen u heeft gewonnen. Proficiat!");
    }
    QFont fontLabel = label->font();
    fontLabel.setPointSize(12);
    label->setFont(fontLabel);
    label->setAlignment(Qt::AlignCenter);

    QPushButton *button = new QPushButton("Sluiten");
    QFont fontButton = button->font();
    fontButton.setPointSize(12);
    button->setFont(fontButton);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(button);
    window->setLayout(layout);

    QObject::connect(button, &QPushButton::clicked, window, &QDialog::close);

    window->show();
    this->deleteLater();
}

void DameoBordView::eventSaveKnop() const {
    qDebug() << m_saveName->text();
    m_spel->saveSpel(m_saveName->text());
}

void DameoBordView::eventLoadKnop() const {
    qDebug() << "Spel inladen";
    m_spel->loadSpel(m_loadName->text());
}

void DameoBordView::aiKnop() const {
    if (m_aiKnop->text() == "Druk om tegen de AI te spelen"){
        m_aiKnop->setText("Druk om 1 vs 1 te spelen");
        m_spel->setTegenAi();
    } else {
        m_aiKnop->setText("Druk om tegen de AI te spelen");
        m_spel->setTegenAi();
    }
}

void DameoBordView::beginnersModusKnop() const {
    if (m_beginnersModusKnop->text() == "Druk om beginnersmodus aan te zetten"){
        m_beginnersModusKnop->setText("Druk om beginnersmodus uit te zetten");
        m_spel->setBeginnersModus();
    } else {
        m_beginnersModusKnop->setText("Druk om beginnersmodus aan te zetten");
        m_spel->setBeginnersModus();
    }
}

//laad het bord opnieuw na een zet van de AI
void DameoBordView::reloadBord() {
    for (int i = 0; i < m_grootteBord; i++){
        for (int j = 0; j < m_grootteBord; j++){
            if (!m_speelbord[i][j]->childItems().empty()){
                removeItem(m_speelbord[i][j]->childItems()[0]);
            }
        }
    }
    for (int i = 0; i < m_grootteBord; i++){
        for (int j = 0; j < m_grootteBord; j++){
            DameoPion* p = dynamic_cast<DameoPion*>(m_spel->getBord().zoekPionOpCoordinaat(i,j));
            if (p != nullptr){
                if (p->getTeam() == Pion::Team::blauw){
                    if (p->isKoning() == true){
                        PionView *koning = new PionView{PionView::dameoKZwart, m_speelbord[i][j]};
                        koning->setParentItem(m_speelbord[i][j]);
                        koning->setPos(2,2);
                    }
                    else{
                        PionView *pion = new PionView{PionView::dameoZwart, m_speelbord[i][j]};
                        pion->setParentItem(m_speelbord[i][j]);
                        pion->setPos(17,4);
                    }
                }
                else{
                    if (p->isKoning() == true){
                        PionView *koning = new PionView{PionView::dameoKWit, m_speelbord[i][j]};
                        koning->setParentItem(m_speelbord[i][j]);
                        koning->setPos(2,2);
                    }
                    else{
                        PionView *pion = new PionView{PionView::dameoWit, m_speelbord[i][j]};
                        pion->setParentItem(m_speelbord[i][j]);
                        pion->setPos(17,4);
                    }
                }
            }
        }
    }
}

void DameoBordView::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        int kolom = event->scenePos().x()/96;
        int rij = event->scenePos().y()/96;
        if (m_lastClicked == nullptr) {
            m_mogelijkeZetten.clear();
            m_mogelijkeZetten = m_spel->eersteKlik(rij, kolom);
            if (m_spel->getBeginnersModus()) {
                for (int i = 0; i < m_mogelijkeZetten.size(); i += 2)
                    m_speelbord[m_mogelijkeZetten.at(i)][m_mogelijkeZetten.at(i+1)]->setBrush(Qt::red);
            }
            if (m_mogelijkeZetten.size() > 0)
                m_lastClicked = m_speelbord[rij][kolom];

        } else {
            if (m_spel->tweedeKlik(rij,kolom)) {
                   m_lastClicked->childItems()[0]->setParentItem(m_speelbord[rij][kolom]);
                   m_lastClicked->childItems().clear();
                for (int i = 0; i < m_mogelijkeZetten.size(); i += 2)
                   m_speelbord[m_mogelijkeZetten.at(i)][m_mogelijkeZetten.at(i+1)]->setBrush(Qt::white);
                m_spel->clearMogelijkeZetten();
                m_lastClicked = nullptr;
                if (m_spel->aiBeurt())
                   reloadBord();
            }
        }
    }

    if(event->button() == Qt::RightButton) {
        for (int i = 0; i < m_mogelijkeZetten.size(); i += 2)
            m_speelbord[m_mogelijkeZetten.at(i)][m_mogelijkeZetten.at(i+1)]->setBrush(Qt::white);
        m_lastClicked = nullptr;
    }
}
