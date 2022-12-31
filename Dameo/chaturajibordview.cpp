#include "chaturajibordview.h"
#include "pionview.h"
#include "qpushbutton.h"
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
    zetPionnen();

    QPushButton* saveKnop = new QPushButton("Sla dit spel op");
    m_saveName = new QLineEdit();
    QLabel *saveText = new QLabel("Opslaan onder welke naam?");
    QPushButton* loadKnop = new QPushButton("Laad een spel");
    m_loadName = new QLineEdit();
    QLabel *loadText = new QLabel("Geef de naam van het spel");
    QPushButton* volgendeBeurtKnop = new QPushButton("Stop met beurt");
    m_geroldeDobbelsteen1 = new QLabel();
    m_geroldeDobbelsteen2 = new QLabel();
    saveText->setAlignment(Qt::AlignCenter);
    loadText->setAlignment(Qt::AlignCenter);
    addWidget(saveKnop);
    addWidget(saveText);
    addWidget(m_saveName);
    addWidget(loadKnop);
    addWidget(loadText);
    addWidget(m_loadName);
    addWidget(volgendeBeurtKnop);
    addWidget(m_geroldeDobbelsteen1);
    addWidget(m_geroldeDobbelsteen2);
    loadText->setGeometry(810,470,200,30);
    m_loadName->setGeometry(810,500,200,30);
    loadKnop->setGeometry(810,530,200,60);
    saveText->setGeometry(810,340,200,30);
    m_saveName->setGeometry(810,370,200,30);
    saveKnop->setGeometry(810,390,200,60);
    volgendeBeurtKnop->setGeometry(810,220,200,100);
    m_geroldeDobbelsteen1->setGeometry(800,100,100,100);
    m_geroldeDobbelsteen2->setGeometry(920,100,100,100);
    connect(m_spel, &ChaturajiSpel::pionVerslaan, this, &ChaturajiBordView::verwijderPionVanBord);
    connect(m_spel, &ChaturajiSpel::veranderDobbelsteen, this, &ChaturajiBordView::veranderDobbelstenen);
    connect(volgendeBeurtKnop, &QPushButton::pressed, m_spel, &ChaturajiSpel::initialiseerRonde);
    connect(m_spel, &ChaturajiSpel::loadGame, this, &ChaturajiBordView::reloadBord);
    connect(saveKnop, &QPushButton::pressed, this, &ChaturajiBordView::eventSaveKnop);
    connect(loadKnop, &QPushButton::pressed, this, &ChaturajiBordView::eventLoadKnop);
    m_spel->initialiseerRonde();
}


void ChaturajiBordView::verwijderPionVanBord(int rij, int kolom) {
    removeItem(speelbord[rij][kolom]->childItems()[0]);
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

void ChaturajiBordView::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        int kolom = event->scenePos().x()/96;
        int rij = event->scenePos().y()/96;
        if (lastClicked == nullptr) {
            mogelijkeZetten.clear();
            mogelijkeZetten = m_spel->eersteKlik(rij, kolom);
            for (int i = 0; i < mogelijkeZetten.size(); i += 2) {
                speelbord[mogelijkeZetten.at(i)][mogelijkeZetten.at(i+1)]->setBrush(Qt::red);
            }
            if (mogelijkeZetten.size() > 0) {
                lastClicked = speelbord[rij][kolom];
            }

        } else {
            if (m_spel->tweedeKlik(rij,kolom)){
               lastClicked->childItems()[0]->setParentItem(speelbord[rij][kolom]);
               for (int i = 0; i < mogelijkeZetten.size(); i += 2){
                   speelbord[mogelijkeZetten.at(i)][mogelijkeZetten.at(i+1)]->setBrush(Qt::white);
               }
               m_spel->clearMogelijkeZetten();
               lastClicked = nullptr;
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
    zetPionnen();
}

void ChaturajiBordView::zetPionnen(){
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

