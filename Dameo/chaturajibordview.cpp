#include "chaturajibordview.h"
#include "pionview.h"

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

    m_spel->initialiseerRonde();
    connect(m_spel, &ChaturajiSpel::pionVerslaan, this, &ChaturajiBordView::verwijderPionVanBord);

    // voeg pionnen toe
    for (int i = 0; i < 32; i++){
        if (spel->getSpelbord().getPionVanLijst(i)->getTeam()==Pion::Team::blauw) {
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'p'){
                PionView *p = new PionView{"ZwartPion", speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'k'){
                PionView *p = new PionView{"ZwartKoning", speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'h'){
                PionView *p = new PionView{"ZwartPaard", speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'b'){
                PionView *p = new PionView{"ZwartBoot", speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'o'){
                PionView *p = new PionView{"ZwartOlifant", speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
        }
        if (spel->getSpelbord().getPionVanLijst(i)->getTeam()==Pion::Team::geel) {
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'p'){
                PionView *p = new PionView{"GeelPion", speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'k'){
                PionView *p = new PionView{"GeelKoning", speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'h'){
                PionView *p = new PionView{"GeelPaard", speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'b'){
                PionView *p = new PionView{"GeelBoot", speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'o'){
                PionView *p = new PionView{"GeelOlifant", speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
        }
        if (spel->getSpelbord().getPionVanLijst(i)->getTeam()==Pion::Team::groen) {
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'p'){
                PionView *p = new PionView{"GroenPion", speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'k'){
                PionView *p = new PionView{"GroenKoning", speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'h'){
                PionView *p = new PionView{"GroenPaard", speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'b'){
                PionView *p = new PionView{"GroenBoot", speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'o'){
                PionView *p = new PionView{"GroenOlifant", speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
        }
        if (spel->getSpelbord().getPionVanLijst(i)->getTeam()==Pion::Team::rood) {
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'p'){
                PionView *p = new PionView{"RoodPion", speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'k'){
                PionView *p = new PionView{"RoodKoning", speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'h'){
                PionView *p = new PionView{"RoodPaard", speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'b'){
                PionView *p = new PionView{"RoodBoot", speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
            if (spel->getSpelbord().getPionVanLijst(i)->getTeken() == 'o'){
                PionView *p = new PionView{"RoodOlifant", speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]};
                p->setParentItem(speelbord[spel->getSpelbord().getPionVanLijst(i)->getYCoordinaat()][spel->getSpelbord().getPionVanLijst(i)->getXCoordinaat()]);
                p->setPos(0,0);
            }
        }
    }
}


void ChaturajiBordView::verwijderPionVanBord(int rij, int kolom) {
    removeItem(speelbord[rij][kolom]->childItems()[0]);
}

//moet nog verbeterd worden met signals of slots maar zie nie hoe met returnvalues want ge hebt 3 mogelijkheden:
//1) op leeg vakje geklikt of pion van tegenstander -> rode kleur bij mogelijkezetten van vorige geklikte pion weg doen
//2) op geldige pion geklikt voor het eerst -> rode vakjes laten zien
//3) op geldige vakje geklikt voor bestemming -> pion verhuizen
//hoe weten welke da ge moet doen zonder logica op return value toe te passen? met signals en slots dan?
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

