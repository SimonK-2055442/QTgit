//Auteur: Simon Knuts en Yara Mijnendonckx

#include <iostream>
#include <fstream>
#include <vector>
#include <QDir>
#include <QFile>
#include "ChaturajiSpel.h"
#include "qdebug.h"

using namespace std;

ChaturajiSpel::ChaturajiSpel(Bord spelbord) : m_spelbord{ spelbord } {
    Speler speler1{ Pion::Team::blauw };
    Speler speler2{ Pion::Team::groen };
    Speler speler3{ Pion::Team::rood };
    Speler speler4{ Pion::Team::geel };
    m_spelerVector.push_back(speler1);
    m_spelerVector.push_back(speler2);
    m_spelerVector.push_back(speler3);
    m_spelerVector.push_back(speler4);
    Dobbelstenen dobbelstenen;
    m_dobbelstenen = dobbelstenen;
};


void ChaturajiSpel::vindEnMaakZet(Speler* spelerAanBeurt) {
    bool gevonden{ false };
    for (int i = 0; i < m_spelbord.getPionnen().size(); i++) {
        Pion* p = m_spelbord.getPionVanLijst(i);
        if (p->getTeam() == spelerAanBeurt->getSpelerAanBeurt() && p->isVerslaan() == false) {
            Zet zet{ p->getXCoordinaat(), p->getYCoordinaat(), p->getXCoordinaat(), p->getYCoordinaat() };
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    zet.setEindXCoordinaat(x);
                    zet.setEindYCoordinaat(y);
                    if (gevonden == false) {
                        if (checkZet(zet, p, spelerAanBeurt->getSpelerAanBeurt(), 1, true)) {
                            Pion* verslagenPion = zet.welkePionIsErVerslaanChaturaji(m_spelbord, p->getTeam());
                            if (verslagenPion != nullptr){
                                if (verslagenPion->getWaarde() == 5) { //koning
                                    aantalVerslagenKoningen ++;
                                    if (aantalVerslagenKoningen == 3) {
                                        emit spelIsGedaan(m_spelerVector[0].getPunten(), m_spelerVector[1].getPunten(), m_spelerVector[2].getPunten(), m_spelerVector[3].getPunten());
                                    }
                                }
                                spelerAanBeurt->verhoogPuntenMet(verslagenPion->getWaarde());
                                emit puntenVeranderen(spelerAanBeurt->getPunten(), spelerAanBeurt->getSpelerAanBeurtString());
                            }
                            //spelerAanBeurt->verhoogPuntenMet(zet.kijkOfPionnenVerslaanZijnChaturaji(m_spelbord, p->getTeam()));
                            zet.maakZet(m_spelbord);
                            gevonden = true;
                        }
                        else {
                            zet.setEindXCoordinaat(p->getXCoordinaat());
                            zet.setEindYCoordinaat(p->getYCoordinaat());
                        }
                    }
                }
            }
        }
    }
}

bool ChaturajiSpel::checkZet(Zet zet, Pion* p, Pion::Team teamSpeler, int spelKeuze, bool echt) {
    if (!m_spelbord.isZetInHetBord(zet)) {
        if (spelKeuze == 2)
            cout << "Geselecteerde zet valt buiten het bord of je probeert een pion naar zichzelf te verplaatsen." << endl;
        return false;
    }
    else if (!p->mogelijkeZet(m_spelbord, zet, teamSpeler)) {
        if (spelKeuze == 2)
            cout << "Deze zet is niet mogelijk met deze pion." << endl;
        return false;
    }
    else if (!stukMagVerplaatstWorden(p, echt)) {
        if (spelKeuze == 2)
            cout << "Je hebt geen stuk dat op de dobbelstenen staat geselecteerd of je hebt deze dobbelsteen al gebruikt." << endl;
        return false;
    }
    else
        return true;
}

void ChaturajiSpel::vindAlleZettenVoorPion(Pion* p, Speler* spelerAanBeurt) {
    vector<int> mogelijkeZetten;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (p->getXCoordinaat() != i || p->getYCoordinaat() != j) {
                Zet zet{ p->getXCoordinaat(), p->getYCoordinaat(), i,j };
                if (checkZet(zet, p, spelerAanBeurt->getSpelerAanBeurt(), 1, false) == true) {
                    mogelijkeZetten.push_back(j);
                    mogelijkeZetten.push_back(i);
                }
            }
        }
    }
    m_mogelijkeZetten = mogelijkeZetten;
}

bool ChaturajiSpel::isGedaan() const {
    int aantalKoningenVerslaan{ 0 };
    for (int i = 0; i < 32; i++)
        if (dynamic_cast<ChaturajiKoning*>(m_spelbord.getPionVanLijst(i)) != nullptr && m_spelbord.getPionVanLijst(i)->isVerslaan())
            aantalKoningenVerslaan += 1;
    if (aantalKoningenVerslaan >= 3)
        return true;
    return false;
}

//checkt of het geselecteerde stuk wel gegooid was met de dobbelstenen
bool ChaturajiSpel::stukMagVerplaatstWorden(Pion* p, bool echt) {
    if (!m_dobbelstenen.getEersteDobbelsteenGebruikt() && (p->print() == m_dobbelstenen.getResultaatVanRol().first || (p->print() == "Koning" && m_dobbelstenen.getResultaatVanRol().first == "KoningOfPion") || (p->print() == "Pion" && m_dobbelstenen.getResultaatVanRol().first == "KoningOfPion"))) {
        if (echt == true) {
            m_dobbelstenen.setEersteDobbelsteenGebruikt(true);
        }
        return true;
    }
    else if (!m_dobbelstenen.getTweedeDobbelsteenGebruikt() && (p->print() == m_dobbelstenen.getResultaatVanRol().second || (p->print() == "Koning" && m_dobbelstenen.getResultaatVanRol().second == "KoningOfPion") || (p->print() == "Pion" && m_dobbelstenen.getResultaatVanRol().second == "KoningOfPion"))) {
        if (echt == true) {
            m_dobbelstenen.setTweedeDobbelsteenGebruikt(true);
        }
        return true;
    }
    else
        return false;
}

//geeft klassement weer wanneer spel gedaan is
void ChaturajiSpel::eindeSpel() {
    Speler spelerMetDeMeestePunten{ m_spelerVector[0]};
    for (int i = 1; i < m_spelerVector.size(); i++) {
        if (m_spelerVector[i].getPunten() > spelerMetDeMeestePunten.getPunten())
            spelerMetDeMeestePunten = m_spelerVector[i];
    }
    cout << endl << "Proficiat speler " << spelerMetDeMeestePunten.getSpelerAanBeurtString() << "! U heeft gewonnen met " << spelerMetDeMeestePunten.getPunten() << " punten." << endl;

    for (int i = 0; i < m_spelerVector.size(); i++) {
        if (m_spelerVector[i].getSpelerAanBeurtString() != spelerMetDeMeestePunten.getSpelerAanBeurtString())
            cout << "Speler " << m_spelerVector[i].getSpelerAanBeurtString() << ": " << m_spelerVector[i].getPunten() << " punten" << endl;
    }
    m_spelbord.verwijderPointers();
}

void ChaturajiSpel::saveSpel(QString naam) {
    string naamOpgeslagenSpel;
    int beurt;
    if (m_speler == Pion::Team::blauw) {
        beurt = 1;
    }
    else if (m_speler == Pion::Team::groen) {
        beurt = 2;
    }
    else if (m_speler == Pion::Team::rood) {
        beurt = 3;
    }
    else{
        beurt = 4;
    }


    string opgeslagenSpelstatus = to_string(beurt);
    for (int i = 0; i < 32; i++) {
        Pion* p = m_spelbord.getPionVanLijst(i);
        if (!p->isVerslaan()){
            opgeslagenSpelstatus.push_back(p->getTeken());
            opgeslagenSpelstatus.append(to_string(p->getXCoordinaat()));
            opgeslagenSpelstatus.append(to_string(p->getYCoordinaat()));
            if (p->getTeam() == DameoPion::Team::blauw) {
                opgeslagenSpelstatus.push_back('b');
            }
            else if (p->getTeam() == DameoPion::Team::groen) {
                opgeslagenSpelstatus.push_back('g');
            }
            else if (p->getTeam() == DameoPion::Team::rood) {
                opgeslagenSpelstatus.push_back('r');
            }
            else{
               opgeslagenSpelstatus.push_back('y');
            }
        }
    }
    qDebug() << QDir::currentPath();
    QString filename = naam + ".txt";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        QString Qsave = QString::fromStdString(opgeslagenSpelstatus);
        stream << Qsave;
    }
    file.close();
}


int ChaturajiSpel::loadSpel(QString naam) {
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
    m_beurt = saveStatus[0] - '0';
    emit loadGame();
    return 0;
}

void ChaturajiSpel::maakNieuwePion(char type, char xCoord, char yCoord, char team) {
    Pion::Team teamPion;
    int xCoordPion, yCoordPion;
    xCoordPion = xCoord - '0';
    yCoordPion = yCoord - '0';
    if (team == 'g'){
        teamPion = Pion::Team::groen;
    }
    else if (team == 'r') {
        teamPion = Pion::Team::rood;
    }
    else if (team == 'y') {
        teamPion = Pion::Team::geel;
    }
    else if (team == 'b') {
        teamPion = Pion::Team::blauw;
    }
    m_spelbord.voegPionToe(false, type, xCoordPion, yCoordPion, teamPion);
}

Bord ChaturajiSpel::getSpelbord(){
    return m_spelbord;
}

std::vector<int> ChaturajiSpel::eersteKlik(int rij,int kolom) {
    if(m_spelbord.zoekPionOpCoordinaat(rij,kolom) == nullptr || rij < 0 || rij > 7 || kolom < 0 || kolom > 7 || m_spelbord.zoekPionOpCoordinaat(rij,kolom)->getTeam() != m_spelerVector[m_beurt].getSpelerAanBeurt() || !stukMagVerplaatstWorden(m_spelbord.zoekPionOpCoordinaat(rij,kolom), false)) {
        if(m_spelbord.zoekPionOpCoordinaat(rij,kolom) == nullptr || rij < 0 || rij > 7 || kolom < 0 || kolom > 7 || m_spelbord.zoekPionOpCoordinaat(rij,kolom)->getTeam() != m_spelerVector[m_beurt].getSpelerAanBeurt() || !stukMagVerplaatstWorden(m_spelbord.zoekPionOpCoordinaat(rij,kolom), false)) {
            m_mogelijkeZetten.clear();
            return m_mogelijkeZetten;
        }
        m_mogelijkeZetten.clear();
        return m_mogelijkeZetten;
    }
    else {
        coordinatenEersteKlik = make_tuple(rij , kolom);
        Pion* pion = m_spelbord.zoekPionOpCoordinaat(rij, kolom);
        vindAlleZettenVoorPion(pion, &m_spelerVector[m_beurt]);
        return m_mogelijkeZetten;
    }
}

bool ChaturajiSpel::tweedeKlik(int rij,int kolom) {
    for (int i = 0; i < m_mogelijkeZetten.size(); i+= 2) {
        if (rij == m_mogelijkeZetten.at(i) && kolom == m_mogelijkeZetten.at(i+1)) {

            Zet zet{std::get<1>(coordinatenEersteKlik), std::get<0>(coordinatenEersteKlik), kolom, rij};
            Pion* verslagenPion = zet.welkePionIsErVerslaanChaturaji(m_spelbord, m_speler);
            if (verslagenPion != nullptr) {
                m_spelerVector[m_beurt].verhoogPuntenMet(verslagenPion->getWaarde());
                emit puntenVeranderen(m_spelerVector[m_beurt].getPunten(), m_spelerVector[m_beurt].getSpelerAanBeurtString());
                emit pionVerslaan(verslagenPion->getYCoordinaat(), verslagenPion->getXCoordinaat());
                stukMagVerplaatstWorden(m_spelbord.zoekPionOpCoordinaat(std::get<0>(coordinatenEersteKlik), std::get<1>(coordinatenEersteKlik)), true);
                zet.maakZet(m_spelbord);
                if (verslagenPion->getWaarde() == 5) { //koning
                    aantalVerslagenKoningen ++;
                    if (aantalVerslagenKoningen == 3) {
                        emit spelIsGedaan(m_spelerVector[0].getPunten(), m_spelerVector[1].getPunten(), m_spelerVector[2].getPunten(), m_spelerVector[3].getPunten());
                    }
                }
                //if (zet.eindeVanBordBereiktBijZet(m_spelbord)){
                    //emit loadGame();
                //}
            } else {
                stukMagVerplaatstWorden(m_spelbord.zoekPionOpCoordinaat(std::get<0>(coordinatenEersteKlik), std::get<1>(coordinatenEersteKlik)), true);
                zet.maakZet(m_spelbord);
                //if (zet.eindeVanBordBereiktBijZet(m_spelbord)){
                    //emit loadGame();
                //}
            }
            if (m_dobbelstenen.getEersteDobbelsteenGebruikt() && m_dobbelstenen.getTweedeDobbelsteenGebruikt()){
                initialiseerRonde();
            }
            return true;
        }
    }
    return false;
}

void ChaturajiSpel::initialiseerRonde(){
    m_dobbelstenen.setEersteDobbelsteenGebruikt(false);
    m_dobbelstenen.setTweedeDobbelsteenGebruikt(false);
    m_dobbelstenen.rolDobbelstenen();
    if (m_beurt == 3){
        m_beurt = 0;
    } else {
        m_beurt++;
    }
    m_speler = m_spelerVector[m_beurt].getSpelerAanBeurt();
    emit veranderDobbelsteen(m_dobbelstenen.getResultaatVanRol().first, m_dobbelstenen.getResultaatVanRol().second);
}

void ChaturajiSpel::clearMogelijkeZetten(){
    m_mogelijkeZetten.clear();
}

void ChaturajiSpel::setTegenAi() {
    m_tegenAi = !m_tegenAi;
}

bool ChaturajiSpel::getTegenAi() {
    return m_tegenAi;
}

bool ChaturajiSpel::aiBeurt() {
    if (m_speler != DameoPion::Team::blauw && m_tegenAi == true){
        while (m_speler != DameoPion::Team::blauw && m_tegenAi == true){
            vindEnMaakZet(&m_spelerVector[m_beurt]);
            vindEnMaakZet(&m_spelerVector[m_beurt]);
            initialiseerRonde();
        }
        emit loadGame();
        return true;
    } else {
        return false;
    }
}

void ChaturajiSpel::setBeginnersModus() {
    m_beginnersModus = !m_beginnersModus;
}

bool ChaturajiSpel::getBeginnersModus() {
    return m_beginnersModus;
}

void ChaturajiSpel::volgendeRonde(){
    if (m_speler == DameoPion::Team::blauw && m_tegenAi == true){
        m_beurt++;
        m_speler = m_spelerVector[m_beurt].getSpelerAanBeurt();
        m_dobbelstenen.setEersteDobbelsteenGebruikt(false);
        m_dobbelstenen.setTweedeDobbelsteenGebruikt(false);
        m_dobbelstenen.rolDobbelstenen();
        aiBeurt();

    } else {
        initialiseerRonde();
    }
}
