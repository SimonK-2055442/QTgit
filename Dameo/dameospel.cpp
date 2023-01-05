//Auteur: Simon Knuts en Yara Mijnendonckx

#include <iostream>
#include <fstream>
#include "dameospel.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>


DameoSpel::DameoSpel(Bord spelbord) : m_spelbord{spelbord} {
    m_speler = DameoPion::Team::blauw;
};

// als een speler geen pionnen meer heeft, is het spel gedaan
int DameoSpel::isGedaan() const {
    int verslagenPionnenSpelerZ = 0;
    int verslagenPionnenSpelerW = 0;
    for (int i = 0; i < 36; i++) {
        if (m_spelbord.getPionVanLijst(i)->isVerslaan()) {
            if (m_spelbord.getPionVanLijst(i)->getTeam() == DameoPion::Team::blauw)
                verslagenPionnenSpelerZ++;
            else
                verslagenPionnenSpelerW++;
        }
    }
    if (verslagenPionnenSpelerZ == 18)
        return 2;
    if (verslagenPionnenSpelerW == 18)
        return 1;
    else
        return 0;
}

//gaat over alle pionnen van speler G en probeert elke zet, een simpele AI
void DameoSpel::vindEnMaakZet(){
    bool gevonden{ false };
    for (int i = 0; i < m_spelbord.getPionnen().size(); i++) {
        Pion* p = m_spelbord.getPionVanLijst(i);
        Zet zet{ p->getXCoordinaat(), p->getYCoordinaat(), p->getXCoordinaat(), p->getYCoordinaat() };
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                zet.setEindXCoordinaat(x);
                zet.setEindYCoordinaat(y);
                if (gevonden == false) {
                    if (p->mogelijkeZet(m_spelbord, zet, DameoPion::Team::geel)) {
                        zet.welkePionIsVerslaan(m_spelbord, DameoPion::Team::geel, false);
                        if (zet.getEindYCoordinaat() == 0 || zet.getEindYCoordinaat() == 7) {
                            dynamic_cast<DameoPion*>(p)->maakKoning();
                        }
                        zet.maakZet(m_spelbord);
                        gevonden = true;
                    } else {
                        zet.setEindXCoordinaat(p->getXCoordinaat());
                        zet.setEindYCoordinaat(p->getYCoordinaat());
                    }
                }
            }
        }
    }
}

void DameoSpel::vindAlleZettenVoorPion(Bord spelbord,DameoPion::Team speler, DameoPion* p, bool moetPakken) {
    vector<int> mogelijkeZetten;
    if (p != nullptr) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (p->getXCoordinaat() != i || p->getYCoordinaat() != j) {
                    Zet zet{ p->getXCoordinaat(), p->getYCoordinaat(), i,j };
                    if (p->mogelijkeZet(spelbord, zet, speler) == true) {
                        QPair<int, int> pionVerslaan = zet.welkePionIsVerslaan(spelbord, speler, true);
                        if ((moetPakken == true && pionVerslaan.first != NULL && pionVerslaan.second != NULL) || moetPakken == false) {
                            mogelijkeZetten.push_back(j);
                            mogelijkeZetten.push_back(i);
                        }
                    }
                }
            }
        }
    }
    m_mogelijkeZetten = mogelijkeZetten;
}

void DameoSpel::maakNieuwePion(char teken, char xCoord, char yCoord, char team) {
    Pion::Team teamPion;
    int xCoordPion, yCoordPion;
    xCoordPion = xCoord - '0';
    yCoordPion = yCoord - '0';
    if (team == 'g') {
        teamPion = Pion::Team::groen;
    }
    else if (team == 'r') {
        teamPion = Pion::Team::rood;
    }
    else if (team == 'y') {
        teamPion = Pion::Team::geel;
    }
    else {
        teamPion = Pion::Team::blauw;
    }
    m_spelbord.voegPionToe(true, teken, xCoordPion, yCoordPion, teamPion);
}

Bord DameoSpel::getBord() {
    return m_spelbord;
}

std::vector<int> DameoSpel::eersteKlik(int rij,int kolom) {
    if (m_spelbord.zoekPionOpCoordinaat(rij,kolom) == nullptr || rij < 0 || rij > 7 || kolom < 0 || kolom > 7 || m_spelbord.zoekPionOpCoordinaat(rij,kolom)->getTeam() != m_speler) {
        m_mogelijkeZetten.clear();
        return m_mogelijkeZetten;
    } else {
        coordinatenEersteKlik = make_tuple(rij , kolom);
        DameoPion* pion = dynamic_cast<DameoPion*>(m_spelbord.zoekPionOpCoordinaat(rij, kolom));
        if (m_pionDieNogEenZetMag != nullptr){
            vindAlleZettenVoorPion(m_spelbord,m_spelbord.zoekPionOpCoordinaat(rij, kolom)->getTeam(), pion, true);
        } else {
            vindAlleZettenVoorPion(m_spelbord,m_spelbord.zoekPionOpCoordinaat(rij, kolom)->getTeam(), pion, false);
        }
        return m_mogelijkeZetten;
    }
}

bool DameoSpel::tweedeKlik(int rij,int kolom) {
    int parameterSpeler;
    if (m_speler == Pion::Team::blauw)
        parameterSpeler = -1;
    else
        parameterSpeler = 1;

    for (int i = 0; i < m_mogelijkeZetten.size(); i+= 2) {
        if (rij == m_mogelijkeZetten.at(i) && kolom == m_mogelijkeZetten.at(i+1)) {

            Zet zet{std::get<1>(coordinatenEersteKlik), std::get<0>(coordinatenEersteKlik), kolom, rij};
            QPair<int, int> pion = zet.welkePionIsVerslaan(m_spelbord, m_speler, false);
            m_pionDieNogEenZetMag = dynamic_cast<DameoPion*>(m_spelbord.zoekPionOpCoordinaat(std::get<0>(coordinatenEersteKlik), std::get<1>(coordinatenEersteKlik)));

            if (pion.first != -1 && pion.second != -1) {
                emit pionVerslaan(pion.first, pion.second);
                zet.maakZet(m_spelbord);
                if (zet.eindeVanBordBereiktBijZet(m_spelbord)){
                    emit pionPromoveren(std::get<0>(coordinatenEersteKlik), std::get<1>(coordinatenEersteKlik), parameterSpeler);
                }
                if (isGedaan() == 1) {
                    emit spelGedaan("zwart");
                }
                if (isGedaan() == 2) {
                    emit spelGedaan("wit");
                }
            }
            else {
                zet.maakZet(m_spelbord);
                if (zet.eindeVanBordBereiktBijZet(m_spelbord)){
                    emit pionPromoveren(std::get<0>(coordinatenEersteKlik), std::get<1>(coordinatenEersteKlik), parameterSpeler);
                }
                m_pionDieNogEenZetMag = nullptr;
            }
            vindAlleZettenVoorPion(m_spelbord,m_spelbord.zoekPionOpCoordinaat(rij, kolom)->getTeam(), m_pionDieNogEenZetMag, true);
            if (m_mogelijkeZetten.size() == 0){
                m_pionDieNogEenZetMag = nullptr;
                veranderBeurt();
            }
            return true;
        }
    }
    return false;
}

void DameoSpel::clearMogelijkeZetten() {
    m_mogelijkeZetten.clear();
}

void DameoSpel::veranderBeurt() {
    if (m_speler == DameoPion::Team::geel) {
        m_speler = DameoPion::Team::blauw;
    } else {
        m_speler = DameoPion::Team::geel;
    }
}

void DameoSpel::saveSpel(QString naam) {
    string naamOpgeslagenSpel;
    int beurt;
    if (m_speler == DameoPion::Team::geel) {
        beurt = 1;
    } else {
        beurt = 2;
    }
    string opgeslagenSpelstatus = to_string(beurt);
    for (int i = 0; i < 36; i++) {
        Pion* p = m_spelbord.getPionVanLijst(i);
        if (!p->isVerslaan()){
            opgeslagenSpelstatus.push_back(p->getTeken());
            opgeslagenSpelstatus.append(to_string(p->getXCoordinaat()));
            opgeslagenSpelstatus.append(to_string(p->getYCoordinaat()));
            if (p->getTeam() == DameoPion::Team::blauw) {
                opgeslagenSpelstatus.push_back('b');
            }
            else if (p->getTeam() == DameoPion::Team::geel) {
                opgeslagenSpelstatus.push_back('y');
            }
        }
    }
    qDebug() << QDir::currentPath();
    QString filename = naam + ".txt";
    QFile file( filename );
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream( &file );
        QString Qsave = QString::fromStdString(opgeslagenSpelstatus);
        stream << Qsave;
    }
    file.close();
}


int DameoSpel::loadSpel(QString naam) {
    QFile file(naam + ".txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;

    QTextStream stream(&file);
    QString contents = stream.readAll();
    std::string saveStatus = contents.toStdString();
    file.close();
    m_spelbord.verwijderPointers();
    for (int i = 1; i < saveStatus.length(); i += 4) {
        maakNieuwePion(saveStatus[i], saveStatus[i + 1], saveStatus[i + 2], saveStatus[i + 3]);
    }
    if (saveStatus[0] - '0' == 1){
        m_speler = DameoPion::Team::geel;
    } else {
        m_speler = DameoPion::Team::blauw;
    }
    emit loadGame();
    return 0;
}

void DameoSpel::setTegenAi() {
    m_tegenAi = !m_tegenAi;
}

bool DameoSpel::getTegenAi() {
    return m_tegenAi;
}

bool DameoSpel::aiBeurt(){
    if (m_speler == DameoPion::Team::geel && m_tegenAi == true){
        vindEnMaakZet();
        veranderBeurt();
        return true;
    } else {
        return false;
    }
}

void DameoSpel::setBeginnersModus() {
    m_beginnersModus = !m_beginnersModus;
}

bool DameoSpel::getBeginnersModus() {
    return m_beginnersModus;
}
