#include "bordview.h"
#include "pion.h"
#include "qpushbutton.h"
#include "QLineEdit"
#include "QLabel"

BordView::BordView(int grootteBord, DameoSpel *spel, QObject *parent) : QGraphicsScene{parent} {
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
    for (int i = 0; i < 36; i++) {
        if (spel->getBord().getPionVanLijst(i)->getTeam() == Pion::Team::blauw) {
            PionView *zwartePion = new PionView{"DameoZwart", speelbord[spel->getBord().getPionVanLijst(i)->getYCoordinaat()][spel->getBord().getPionVanLijst(i)->getXCoordinaat()]};
            zwartePion->setParentItem(speelbord[spel->getBord().getPionVanLijst(i)->getYCoordinaat()][spel->getBord().getPionVanLijst(i)->getXCoordinaat()]);
            //speelbord[spel->getBord().getPionVanLijst(i)->getYCoordinaat()][spel->getBord().getPionVanLijst(i)->getXCoordinaat()]->setChild(zwartePion);
            zwartePion->setPos(17,4);
        } else {
            PionView *wittePion = new PionView{"DameoWit", speelbord[spel->getBord().getPionVanLijst(i)->getYCoordinaat()][spel->getBord().getPionVanLijst(i)->getXCoordinaat()]};
            wittePion->setParentItem(speelbord[spel->getBord().getPionVanLijst(i)->getYCoordinaat()][spel->getBord().getPionVanLijst(i)->getXCoordinaat()]);
            //speelbord[spel->getBord().getPionVanLijst(i)->getYCoordinaat()][spel->getBord().getPionVanLijst(i)->getXCoordinaat()]->setChild(wittePion);
            wittePion->setPos(17,4);
        }
    }

    QPushButton* saveKnop = new QPushButton("save spel");
    m_saveName = new QLineEdit();
    QLabel *saveText = new QLabel("opslaan onder welke naam?");
    QPushButton* loadKnop = new QPushButton("load spel");
    m_loadName = new QLineEdit();
    QLabel *loadText = new QLabel("naam van het spel dat je wilt laden?");
    saveText->setAlignment(Qt::AlignCenter);
    loadText->setAlignment(Qt::AlignCenter);
    addWidget(saveKnop);
    addWidget(saveText);
    addWidget(m_saveName);
    addWidget(loadKnop);
    addWidget(loadText);
    addWidget(m_loadName);
    loadText->setGeometry(800,440,200,30);
    m_loadName->setGeometry(800,470,200,30);
    loadKnop->setGeometry(800,500,200,60);
    saveText->setGeometry(800,140,200,30);
    m_saveName->setGeometry(800,170,200,30);
    saveKnop->setGeometry(800,200,200,60);


    connect(m_spel, &DameoSpel::pionVerslaan, this, &BordView::verwijderPionVanBord);
    connect(m_spel, &DameoSpel::pionPromoveren, this, &BordView::promoveerPion);
    connect(m_spel, &DameoSpel::spelGedaan, this, &BordView::toonWinnaar);
    connect(saveKnop, &QPushButton::pressed, this, &BordView::eventSaveKnop);
    connect(loadKnop, &QPushButton::pressed, this, &BordView::eventLoadKnop);
}

void BordView::verwijderPionVanBord(int rij, int kolom) {
    removeItem(speelbord[rij][kolom]->childItems()[0]);
    //verwijderen werkt nog niet altijd
    //delete speelbord[rij][kolom]->childItems()[0];
    //speelbord[rij][kolom]->childItems()[0]->setParentItem(nullptr);   // moet nog naar de view naast het spelbord
}

void BordView::promoveerPion(int rij, int kolom, int parameterSpeler) {
    //verwijderen werkt nog niet altijd
    delete speelbord[rij+parameterSpeler][kolom]->childItems()[0];
    if (parameterSpeler == -1) {
        PionView *koning = new PionView{"DameoKZwart", speelbord[rij+parameterSpeler][kolom]};
        koning->setParentItem(speelbord[rij+parameterSpeler][kolom]);
    } else {
        PionView *koning = new PionView{"DameoKWit", speelbord[rij+parameterSpeler][kolom]};
        koning->setParentItem(speelbord[rij+parameterSpeler][kolom]);
    }
}

void BordView::toonWinnaar(QString winnaar) {
    qDebug() << "spel is gedaan met als winnaar" << winnaar;
}

void BordView::eventSaveKnop() {
    qDebug() << m_saveName->text();
    m_spel->saveSpel(m_saveName->text());
}

void BordView::eventLoadKnop() {
    qDebug() << "spel is gedaan met als winnaar";
}



//moet nog verbeterd worden met signals of slots maar zie nie hoe met returnvalues want ge hebt 3 mogelijkheden:
//1) op leeg vakje geklikt of pion van tegenstander -> rode kleur bij mogelijkezetten van vorige geklikte pion weg doen
//2) op geldige pion geklikt voor het eerst -> rode vakjes laten zien
//3) op geldige vakje geklikt voor bestemming -> pion verhuizen
//hoe weten welke da ge moet doen zonder logica op return value toe te passen? met signals en slots dan?
void BordView::mousePressEvent(QGraphicsSceneMouseEvent *event) {
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
               //if (rij != 7 && rij != 0){
                   lastClicked->childItems()[0]->setParentItem(speelbord[rij][kolom]);
                   lastClicked->childItems().clear();
               //}
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
