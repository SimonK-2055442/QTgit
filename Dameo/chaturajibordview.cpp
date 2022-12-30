#include "chaturajibordview.h"
#include "pionview.h"
#include "qpushbutton.h"
#include <QLabel>

ChaturajiBordView::ChaturajiBordView(int grootteBord, ChaturajiSpel *spel, QObject *parent) : QGraphicsScene{parent} {
    m_spel = spel;
    //setSceneRect(0, 0, 1200, 800);
    setBackgroundBrush(QBrush(Qt::gray));

    // maak het bord
    for (int i = 0; i < grootteBord; ++i) {
        for (int j = 0; j < grootteBord; ++j) {
            speelbord[i][j] = new BordCelView{i, j};
            addItem(speelbord[i][j]);
        }
    }

    // voeg pionnen toe
    for (int i = 0; i < 32; i++){
        if (spel->getSpelbord().getPionVanLijst(i)->getTeam()==Pion::Team::blauw) {
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'p'){
                PionView *p = new PionView{PionView::zwartPion, speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'k'){
                PionView *p = new PionView{PionView::zwartKoning, speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'h'){
                PionView *p = new PionView{PionView::zwartPaard, speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'b'){
                PionView *p = new PionView{PionView::zwartBoot, speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'o'){
                PionView *p = new PionView{PionView::zwartOlifant, speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
        }
        if (spel->getSpelbord().getPionVanLijst(i)->getTeam()==Pion::Team::geel) {
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'p'){
                PionView *p = new PionView{PionView::geelPion, speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'k'){
                PionView *p = new PionView{PionView::geelKoning, speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'h'){
                PionView *p = new PionView{PionView::geelPaard, speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'b'){
                PionView *p = new PionView{PionView::geelBoot, speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'o'){
                PionView *p = new PionView{PionView::geelOlifant, speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
        }
        if (spel->getSpelbord().getPionVanLijst(i)->getTeam()==Pion::Team::groen) {
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'p'){
                PionView *p = new PionView{PionView::groenPion, speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'k'){
                PionView *p = new PionView{PionView::groenKoning, speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'h'){
                PionView *p = new PionView{PionView::groenPaard, speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'b'){
                PionView *p = new PionView{PionView::groenBoot, speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'o'){
                PionView *p = new PionView{PionView::groenOlifant, speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
        }
        if (spel->getSpelbord().getPionVanLijst(i)->getTeam()==Pion::Team::rood) {
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'p'){
                PionView *p = new PionView{PionView::roodPion, speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'k'){
                PionView *p = new PionView{PionView::roodKoning, speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'h'){
                PionView *p = new PionView{PionView::roodPaard, speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'b'){
                PionView *p = new PionView{PionView::roodBoot, speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'o'){
                PionView *p = new PionView{PionView::roodOlifant, speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
        }
    }

    QPushButton* volgendeBeurtKnop = new QPushButton("Stop met beurt");
    m_geroldeDobbelsteen1 = new QLabel();
    m_geroldeDobbelsteen2 = new QLabel();
    volgendeBeurtKnop->setGeometry(860,400,100,100);
    m_geroldeDobbelsteen1->setGeometry(800,200,100,100);
    m_geroldeDobbelsteen2->setGeometry(920,200,100,100);
    addWidget(volgendeBeurtKnop);
    addWidget(m_geroldeDobbelsteen1);
    addWidget(m_geroldeDobbelsteen2);
    connect(m_spel, &ChaturajiSpel::pionVerslaan, this, &ChaturajiBordView::verwijderPionVanBord);
    connect(m_spel, &ChaturajiSpel::veranderDobbelsteen, this, &ChaturajiBordView::veranderDobbelstenen);
    connect(volgendeBeurtKnop, &QPushButton::pressed, m_spel, &ChaturajiSpel::initialiseerRonde);
    m_spel->initialiseerRonde();
}


void ChaturajiBordView::verwijderPionVanBord(int rij, int kolom) {
    removeItem(speelbord[rij][kolom]->childItems()[0]);
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

