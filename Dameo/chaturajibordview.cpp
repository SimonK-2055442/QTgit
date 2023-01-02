#include "chaturajibordview.h"
#include "pionview.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

ChaturajiBordView::ChaturajiBordView(int grootteBord, ChaturajiSpel *spel, QObject *parent) : QGraphicsScene{parent} {
    m_spel = spel;
    m_grootteBord = grootteBord;
    //setSceneRect(0, 0, 1200, 800);
    setBackgroundBrush(QBrush(Qt::gray));

    // maak het bord
    for (int i = 0; i < m_grootteBord; ++i) {
        for (int j = 0; j < m_grootteBord; ++j) {
            speelbord[i][j] = new BordCelView{i, j};
            addItem(speelbord[i][j]);
        }
    }

    // voeg pionnen toe
    plaatsPionnen();


    // voeg punten toe
    voegPuntentellingToe();


    m_geroldeDobbelsteen1 = new QLabel();
    m_geroldeDobbelsteen2 = new QLabel();
    m_geroldeDobbelsteen1->setGeometry(800, 50, 100, 100);
    m_geroldeDobbelsteen2->setGeometry(920, 50, 100, 100);
    addWidget(m_geroldeDobbelsteen1);
    addWidget(m_geroldeDobbelsteen2);

    QPushButton* volgendeBeurtKnop = new QPushButton("Stop met beurt");
    volgendeBeurtKnop->setGeometry(1100, 200, 250, 50);
    addWidget(volgendeBeurtKnop);

    QLabel *saveText = new QLabel("Opslaan onder welke naam?");
    saveText->setGeometry(1100, 290, 250, 30);
    saveText->setAlignment(Qt::AlignCenter);
    addWidget(saveText);

    m_saveName = new QLineEdit();
    m_saveName->setGeometry(1100, 320, 250, 30);
    addWidget(m_saveName);

    QPushButton* saveKnop = new QPushButton("Sla dit spel op");
    saveKnop->setGeometry(1100, 340, 250, 60);
    addWidget(saveKnop);

    QLabel *loadText = new QLabel("Geef de naam van het spel:");
    loadText->setGeometry(1100, 420, 250, 30);
    loadText->setAlignment(Qt::AlignCenter);
    addWidget(loadText);

    m_loadName = new QLineEdit();
    m_loadName->setGeometry(1100, 450, 250, 30);
    addWidget(m_loadName);

    QPushButton* loadKnop = new QPushButton("Laad een spel");
    loadKnop->setGeometry(1100, 480, 250, 60);
    addWidget(loadKnop);

    m_aiKnop = new QPushButton("Druk om tegen de AI te spelen");
    m_aiKnop->setGeometry(1100, 585, 250, 30);
    addWidget(m_aiKnop);

    m_beginnersModusKnop = new QPushButton("Druk om beginnersmodus aan te zetten");
    m_beginnersModusKnop->setGeometry(1100, 630, 250, 30);
    addWidget(m_beginnersModusKnop);

    connect(volgendeBeurtKnop, &QPushButton::pressed, m_spel, &ChaturajiSpel::volgendeRonde);
    connect(saveKnop, &QPushButton::pressed, this, &ChaturajiBordView::eventSaveKnop);
    connect(loadKnop, &QPushButton::pressed, this, &ChaturajiBordView::eventLoadKnop);
    connect(m_aiKnop, &QPushButton::pressed, this, &ChaturajiBordView::aiKnop);
    connect(m_beginnersModusKnop, &QPushButton::clicked, this, &ChaturajiBordView::beginnersModusKnop);

    connect(m_spel, &ChaturajiSpel::pionVerslaan, this, &ChaturajiBordView::verwijderPionVanBord);
    connect(m_spel, &ChaturajiSpel::puntenVeranderen, this, &ChaturajiBordView::verhoogPunten);
    connect(m_spel, &ChaturajiSpel::veranderDobbelsteen, this, &ChaturajiBordView::veranderDobbelstenen);
    connect(m_spel, &ChaturajiSpel::loadGame, this, &ChaturajiBordView::reloadBord);
    connect(m_spel, &ChaturajiSpel::spelIsGedaan, this, &ChaturajiBordView::bepaalWinnaar);

    m_spel->initialiseerRonde();
}

void ChaturajiBordView::aiKnop(){
    if (m_aiKnop->text() == "Druk om tegen de AI te spelen"){
        m_aiKnop->setText("Druk om 1 vs 1 vs 1 vs 1 te spelen");
        m_spel->setTegenAi();
    }
    else{
        m_aiKnop->setText("Druk om tegen de AI te spelen");
        m_spel->setTegenAi();
    }
}

void ChaturajiBordView::beginnersModusKnop() {
    if (m_beginnersModusKnop->text() == "Druk om beginnersmodus aan te zetten"){
        m_beginnersModusKnop->setText("Druk om beginnersmodus uit te zetten");
        m_spel->setBeginnersModus();
    } else {
        m_beginnersModusKnop->setText("Druk om beginnersmodus aan te zetten");
        m_spel->setBeginnersModus();
    }
}

void ChaturajiBordView::verwijderPionVanBord(int rij, int kolom) {
    removeItem(speelbord[rij][kolom]->childItems()[0]);
}

void ChaturajiBordView::verhoogPunten(int totaal, string speler) {
    if (speler == "geel") {
        aantalPuntenGeel->setText(QString::number(totaal));
    } else if (speler == "groen") {
        aantalPuntenGroen->setText(QString::number(totaal));
    } else if (speler == "rood") {
        aantalPuntenRood->setText(QString::number(totaal));
    } else {
        aantalPuntenZwart->setText(QString::number(totaal));
    }
}

void ChaturajiBordView::eventSaveKnop() {
    qDebug() << m_saveName->text();
    m_spel->saveSpel(m_saveName->text());
}

void ChaturajiBordView::eventLoadKnop() {
    qDebug() << "inladen";
    m_spel->loadSpel(m_loadName->text());
}

void ChaturajiBordView::veranderDobbelstenen(string eerste, string tweede){
    if (eerste == "KoningOfPion"){
        m_geroldeDobbelsteen1->setPixmap(QPixmap(":/images/zwartKoning.png").scaled(100,100));
    }
    if (eerste == "Boot"){
        m_geroldeDobbelsteen1->setPixmap(QPixmap(":/images/zwartBoot.png").scaled(100,100));
    }
    if (eerste == "Paard"){
        m_geroldeDobbelsteen1->setPixmap(QPixmap(":/images/zwartPaard.png").scaled(100,100));
    }
    if (eerste == "Olifant"){
        m_geroldeDobbelsteen1->setPixmap(QPixmap(":/images/zwartOlifant.png").scaled(100,100));
    }
    if (tweede == "KoningOfPion"){
        m_geroldeDobbelsteen2->setPixmap(QPixmap(":/images/zwartKoning.png").scaled(100,100));
    }
    if (tweede == "Boot"){
        m_geroldeDobbelsteen2->setPixmap(QPixmap(":/images/zwartBoot.png").scaled(100,100));
    }
    if (tweede == "Paard"){
        m_geroldeDobbelsteen2->setPixmap(QPixmap(":/images/zwartPaard.png").scaled(100,100));
    }
    if (tweede == "Olifant"){
        m_geroldeDobbelsteen2->setPixmap(QPixmap(":/images/zwartOlifant.png").scaled(100,100));
    }
}

void ChaturajiBordView::bepaalWinnaar(int ptnZwart, int ptnGroen, int ptnRood, int ptnGeel) {
    QPair<string, int> winnaar("zwarte", ptnZwart);

    if (ptnGroen > winnaar.second) {
        winnaar.first = "groene";
        winnaar.second = ptnGroen;
    }
    if (ptnRood > winnaar.second) {
        winnaar.first = "rode";
        winnaar.second = ptnRood;
    }
    if (ptnGeel > winnaar.second) {
        winnaar.first = "gele";
        winnaar.second = ptnGeel;
    }

    QDialog *window = new QDialog();
    window->setWindowTitle("Er is een winnaar!");

    QLabel *winnaarLabel = new QLabel();
    string tekst = "Speler met de " + winnaar.first + " pionnen u heeft gewonnen met " + to_string(winnaar.second) + " punten. Proficiat!";
    winnaarLabel->setText(QString::fromStdString(tekst));
    winnaarLabel->setAlignment(Qt::AlignLeft);

    QLabel *spelerZwart = new QLabel();
    string tekstZwart = "Zwart: " + to_string(ptnZwart) + " punten";
    spelerZwart->setText(QString::fromStdString(tekstZwart));
    spelerZwart->setAlignment(Qt::AlignLeft);

    QLabel *spelerGroen = new QLabel();
    string tekstGroen = "Groen: " + to_string(ptnGroen) + " punten";
    spelerGroen->setText(QString::fromStdString(tekstGroen));
    spelerGroen->setAlignment(Qt::AlignLeft);

    QLabel *spelerRood = new QLabel();
    string tekstRood = "Rood: " + to_string(ptnRood) + " punten";
    spelerRood->setText(QString::fromStdString(tekstRood));
    spelerRood->setAlignment(Qt::AlignLeft);

    QLabel *spelerGeel = new QLabel();
    string tekstGeel = "Geel: " + to_string(ptnGeel) + " punten";
    spelerGeel->setText(QString::fromStdString(tekstGeel));
    spelerGeel->setAlignment(Qt::AlignLeft);

    QLabel *leeg = new QLabel("");
    QPushButton *button = new QPushButton("Sluiten");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(winnaarLabel);
    layout->addWidget(leeg);
    layout->addWidget(spelerZwart);
    layout->addWidget(spelerGroen);
    layout->addWidget(spelerRood);
    layout->addWidget(spelerGeel);
    layout->addWidget(button);
    window->setLayout(layout);

    QObject::connect(button, &QPushButton::clicked, window, &QDialog::close);

    window->show();
    this->deleteLater();
}

void ChaturajiBordView::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        int kolom = event->scenePos().x()/96;
        int rij = event->scenePos().y()/96;
        if (lastClicked == nullptr) {
            mogelijkeZetten.clear();
            mogelijkeZetten = m_spel->eersteKlik(rij, kolom);
            if (m_spel->getBeginnersModus()) {
                for (int i = 0; i < mogelijkeZetten.size(); i += 2) {
                    speelbord[mogelijkeZetten.at(i)][mogelijkeZetten.at(i+1)]->setBrush(Qt::red);
                }
            }
            if (mogelijkeZetten.size() > 0) {
                lastClicked = speelbord[rij][kolom];
            }

        } else {
            if (m_spel->tweedeKlik(rij, kolom)){
                lastClicked->childItems()[0]->setParentItem(speelbord[rij][kolom]);
                for (int i = 0; i < mogelijkeZetten.size(); i += 2){
                   speelbord[mogelijkeZetten.at(i)][mogelijkeZetten.at(i+1)]->setBrush(Qt::white);
                }
                m_spel->clearMogelijkeZetten();
                lastClicked = nullptr;
                m_spel->aiBeurt();
                //reloadBord();
            }
        }
    }

    if(event->button() == Qt::RightButton) {
        for (int i = 0; i < mogelijkeZetten.size(); i += 2){
            speelbord[mogelijkeZetten.at(i)][mogelijkeZetten.at(i+1)]->setBrush(Qt::white);
        }
        lastClicked = nullptr;
    }
}

void ChaturajiBordView::reloadBord() {
    for (int i = 0; i < m_grootteBord; i++){
        for (int j = 0; j < m_grootteBord; j++){
            if (!speelbord[i][j]->childItems().empty()){
                removeItem(speelbord[i][j]->childItems()[0]);
            }
        }
    }
    plaatsPionnen();
}

void ChaturajiBordView::plaatsPionnen(){
    for (int i = 0; i < m_grootteBord; i++){
        for (int j = 0; j < m_grootteBord; j++){
            Pion* p = m_spel->getSpelbord().zoekPionOpCoordinaat(i,j);
            if (p != nullptr){
                if (p->getTeam() == Pion::Team::blauw){
                    if (p->getTeken() == 'k'){
                        PionView *koning = new PionView{PionView::zwartKoning, speelbord[i][j]};
                        koning->setParentItem(speelbord[i][j]);
                    }
                    else if (p->getTeken() == 'h'){
                        PionView *paard = new PionView{PionView::zwartPaard, speelbord[i][j]};
                        paard->setParentItem(speelbord[i][j]);
                    }
                    else if (p->getTeken() == 'b'){
                        PionView *boot = new PionView{PionView::zwartBoot, speelbord[i][j]};
                        boot->setParentItem(speelbord[i][j]);
                    }
                    else if (p->getTeken() == 'o'){
                        PionView *olifant = new PionView{PionView::zwartOlifant, speelbord[i][j]};
                        olifant->setParentItem(speelbord[i][j]);
                    }
                    else if (p->getTeken() == 'p'){
                        PionView *pion = new PionView{PionView::zwartPion, speelbord[i][j]};
                        pion->setParentItem(speelbord[i][j]);
                    }
                }
                if (p->getTeam() == Pion::Team::groen){
                    if (p->getTeken() == 'k'){
                        PionView *koning = new PionView{PionView::groenKoning, speelbord[i][j]};
                        koning->setParentItem(speelbord[i][j]);
                    }
                    else if (p->getTeken() == 'h'){
                        PionView *paard = new PionView{PionView::groenPaard, speelbord[i][j]};
                        paard->setParentItem(speelbord[i][j]);
                    }
                    else if (p->getTeken() == 'b'){
                        PionView *boot = new PionView{PionView::groenBoot, speelbord[i][j]};
                        boot->setParentItem(speelbord[i][j]);
                    }
                    else if (p->getTeken() == 'o'){
                        PionView *olifant = new PionView{PionView::groenOlifant, speelbord[i][j]};
                        olifant->setParentItem(speelbord[i][j]);
                    }
                    else if (p->getTeken() == 'p'){
                        PionView *pion = new PionView{PionView::groenPion, speelbord[i][j]};
                        pion->setParentItem(speelbord[i][j]);
                    }
                }
                if (p->getTeam() == Pion::Team::rood){
                    if (p->getTeken() == 'k'){
                        PionView *koning = new PionView{PionView::roodKoning, speelbord[i][j]};
                        koning->setParentItem(speelbord[i][j]);
                    }
                    else if (p->getTeken() == 'h'){
                        PionView *paard = new PionView{PionView::roodPaard, speelbord[i][j]};
                        paard->setParentItem(speelbord[i][j]);
                    }
                    else if (p->getTeken() == 'b'){
                        PionView *boot = new PionView{PionView::roodBoot, speelbord[i][j]};
                        boot->setParentItem(speelbord[i][j]);
                    }
                    else if (p->getTeken() == 'o'){
                        PionView *olifant = new PionView{PionView::roodOlifant, speelbord[i][j]};
                        olifant->setParentItem(speelbord[i][j]);
                    }
                    else if (p->getTeken() == 'p'){
                        PionView *pion = new PionView{PionView::roodPion, speelbord[i][j]};
                        pion->setParentItem(speelbord[i][j]);
                    }
                }
                if (p->getTeam() == Pion::Team::geel){
                    if (p->getTeken() == 'k'){
                        PionView *koning = new PionView{PionView::geelKoning, speelbord[i][j]};
                        koning->setParentItem(speelbord[i][j]);
                    }
                    else if (p->getTeken() == 'h'){
                        PionView *paard = new PionView{PionView::geelPaard, speelbord[i][j]};
                        paard->setParentItem(speelbord[i][j]);
                    }
                    else if (p->getTeken() == 'b'){
                        PionView *boot = new PionView{PionView::geelBoot, speelbord[i][j]};
                        boot->setParentItem(speelbord[i][j]);
                    }
                    else if (p->getTeken() == 'o'){
                        PionView *olifant = new PionView{PionView::geelOlifant, speelbord[i][j]};
                        olifant->setParentItem(speelbord[i][j]);
                    }
                    else if (p->getTeken() == 'p'){
                        PionView *pion = new PionView{PionView::geelPion, speelbord[i][j]};
                        pion->setParentItem(speelbord[i][j]);
                    }
                }
            }
        }
    }
}

void ChaturajiBordView::voegPuntentellingToe() {
    QLabel *puntenZwart = new QLabel("Punten zwart:");
    puntenZwart->setGeometry(810, 290, 200, 25);
    puntenZwart->setAlignment(Qt::AlignCenter);
    QLabel *ptnZwart = new QLabel(" punten");
    ptnZwart->setGeometry(895, 315, 115, 25);
    ptnZwart->setAlignment(Qt::AlignLeft);
    addWidget(ptnZwart);
    addWidget(puntenZwart);
    aantalPuntenZwart = new QLabel("0");
    aantalPuntenZwart->setGeometry(810, 315, 85, 25);
    aantalPuntenZwart->setAlignment(Qt::AlignRight);
    addWidget(aantalPuntenZwart);

    QLabel *puntenGroen = new QLabel("Punten groen:");
    puntenGroen->setGeometry(810, 370, 200, 25);
    puntenGroen->setAlignment(Qt::AlignCenter);
    addWidget(puntenGroen);
    QLabel *ptnGroen = new QLabel(" punten");
    ptnGroen->setGeometry(895, 395, 115, 25);
    ptnGroen->setAlignment(Qt::AlignLeft);
    addWidget(ptnGroen);
    aantalPuntenGroen = new QLabel("0");
    aantalPuntenGroen->setGeometry(810, 395, 85, 25);
    aantalPuntenGroen->setAlignment(Qt::AlignRight);
    addWidget(aantalPuntenGroen);

    QLabel *puntenRood = new QLabel("Punten rood:");
    puntenRood->setGeometry(810, 450, 200, 25);
    puntenRood->setAlignment(Qt::AlignCenter);
    addWidget(puntenRood);
    QLabel *ptnRood = new QLabel(" punten");
    ptnRood->setGeometry(895, 475, 115, 25);
    ptnRood->setAlignment(Qt::AlignLeft);
    addWidget(ptnRood);
    aantalPuntenRood = new QLabel("0");
    aantalPuntenRood->setGeometry(810, 475, 85, 25);
    aantalPuntenRood->setAlignment(Qt::AlignRight);
    addWidget(aantalPuntenRood);

    QLabel *puntenGeel = new QLabel("Punten geel:");
    puntenGeel->setGeometry(810, 530, 200, 25);
    puntenGeel->setAlignment(Qt::AlignCenter);
    addWidget(puntenGeel);
    QLabel *ptnGeel = new QLabel(" punten");
    ptnGeel->setGeometry(895, 555, 115, 25);
    ptnGeel->setAlignment(Qt::AlignLeft);
    addWidget(ptnGeel);
    aantalPuntenGeel = new QLabel("0");
    aantalPuntenGeel->setGeometry(810, 555, 85, 25);
    aantalPuntenGeel->setAlignment(Qt::AlignRight);
    addWidget(aantalPuntenGeel);
}
