//Auteur: Simon Knuts en Yara Mijnendonckx

#include <iostream>
#include <fstream>
#include <vector>
#include "ChaturajiSpel.h"

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

void ChaturajiSpel::startSpel(int spelKeuze) {
    m_spelbord.initialiseerBord(Bord::KeuzeSpel::chaturaji);
    for (int i = 0; i < m_spelerVector.size(); i++) {
        if (isGedaan() == false) {
            m_dobbelstenen.rolDobbelstenen();
            /*if (m_spelbord.zoekPionOpCoordinaat(5, 5) != nullptr) {
                i = loadSpel() + 1;
                if (i == 4) {
                    i = 3;
                }
            }*///spel laden wanneer user dit wilt
            for (int j = 0; j < 2; j++) {
                if (spelKeuze == 1 && i > 0) {
                    vindEnMaakZet(&m_spelerVector[i]);
                    vindEnMaakZet(&m_spelerVector[i]);
                    break;
                }
                m_spelbord.laatZien();
                cout << m_spelerVector[i].getSpelerAanBeurtString() << ": je mag " << m_dobbelstenen.getResultaatVanRol().first << " en " << m_dobbelstenen.getResultaatVanRol().second << " verzetten" << endl;
                if (m_spelerVector[i].wiltBeurtStoppen())
                    break;
                Zet zet = vraagZet(&m_spelerVector[i]);
                Pion* p = m_spelbord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), zet.getStartXCoordinaat());
                while (p == nullptr || !checkZet(zet, p, m_spelerVector[i].getSpelerAanBeurt(), spelKeuze, true)) {
                    cout << "Gelieve een geldige zet op te geven!" << endl;
                    zet = vraagZet(&m_spelerVector[i]);
                    p = m_spelbord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), zet.getStartXCoordinaat());
                }
                //saveSpel(i); enkel opslaan nadat een beurt gedaan is best
                m_spelerVector[i].verhoogPuntenMet(zet.kijkOfPionnenVerslaanZijnChaturaji(m_spelbord, p->getTeam()));
                zet.maakZet(m_spelbord, m_spelerVector[i].getSpelerAanBeurt());
            }
            m_dobbelstenen.setEersteDobbelsteenGebruikt(false);
            m_dobbelstenen.setTweedeDobbelsteenGebruikt(false);
            if (i == 3)
                i = -1;
        }
        else {
            eindeSpel();
            return;
        }
    }
}

int ChaturajiSpel::vertaal(string teVertalen) const {
    int vertaaldeString;
    try {
        vertaaldeString = stoi(teVertalen) - 1;
    }
    catch (...) {
        vertaaldeString = (teVertalen[0] - 'A');
    }
    return vertaaldeString;
}

void ChaturajiSpel::vindEnMaakZet(Speler* spelerAanBeurt) {
    bool gevonden{ false };
    for (int i = 0; i < 32; i++) {
        Pion* p = m_spelbord.getPionVanLijst(i);
        if (p->getTeam() == spelerAanBeurt->getSpelerAanBeurt() && p->isVerslaan() == false) {
            Zet zet{ p->getXCoordinaat(), p->getYCoordinaat(), p->getXCoordinaat(), p->getYCoordinaat() };
            for (int x = 1; x < 8; x++) {
                for (int y = 1; y < 8; y++) {
                    zet.setEindXCoordinaat(x);
                    zet.setEindYCoordinaat(y);
                    if (gevonden == false) {
                        if (checkZet(zet, p, spelerAanBeurt->getSpelerAanBeurt(), 1, true)) {
                            spelerAanBeurt->verhoogPuntenMet(zet.kijkOfPionnenVerslaanZijnChaturaji(m_spelbord, p->getTeam()));
                            zet.maakZet(m_spelbord, spelerAanBeurt->getSpelerAanBeurt());
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

void ChaturajiSpel::vindAlleZettenVoorPion(Pion* p, Speler* spelerAanBeurt){
    vector<int> mogelijkeZetten;
    string vertalen = "ABCDEFGH";
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (p->getXCoordinaat() != i || p->getYCoordinaat() != j) {
                Zet zet{ p->getXCoordinaat(), p->getYCoordinaat(), i,j };
                if (checkZet(zet, p, spelerAanBeurt->getSpelerAanBeurt(), 1, false) == true) {
                    string mogelijkeZet = vertalen[i] + to_string(j+1);
                    cout << mogelijkeZet + " ";
                    //mogelijkeZetten.push_back(mogelijkeZet);
                    mogelijkeZetten.push_back(j);
                    mogelijkeZetten.push_back(i);
                }
                //m_dobbelstenen.setEersteDobbelsteenGebruikt(false);
                //m_dobbelstenen.setTweedeDobbelsteenGebruikt(false);
            }
        }
    }
    cout << endl;
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

Zet ChaturajiSpel::vraagZet(Speler* spelerAanBeurt) {
    string teVerzettenStuk, eindPositie;
    string kleurAanBeurt = spelerAanBeurt->getSpelerAanBeurtString();
    cout << kleurAanBeurt << ": welk stuk wil je verzetten? " << endl;
    cin >> teVerzettenStuk;
    Pion* p = m_spelbord.zoekPionOpCoordinaat(vertaal(teVerzettenStuk.substr(1, 1)), vertaal(teVerzettenStuk.substr(0, 1)));
    if (p != nullptr) {
        vindAlleZettenVoorPion(p, spelerAanBeurt);
    }
    cout << kleurAanBeurt << ": naar welke positie wil je dit stuk verplaatsen?" << endl;
    cin >> eindPositie;
    Zet zet{ vertaal(teVerzettenStuk.substr(0, 1)), vertaal(teVerzettenStuk.substr(1, 1))  , vertaal(eindPositie.substr(0, 1)), vertaal(eindPositie.substr(1, 1)) };
    return zet;
}

//checkt of het geselecteerde stuk wel gegooid was met de dobbelstenen
bool ChaturajiSpel::stukMagVerplaatstWorden(Pion* p, bool echt) {
    if (!m_dobbelstenen.getEersteDobbelsteenGebruikt() && (p->print() == m_dobbelstenen.getResultaatVanRol().first || p->print() == "Koning" && m_dobbelstenen.getResultaatVanRol().first == "KoningOfPion" || p->print() == "Pion" && m_dobbelstenen.getResultaatVanRol().first == "KoningOfPion")) {
        if (echt == true) {
            m_dobbelstenen.setEersteDobbelsteenGebruikt(true);
        }
        return true;
    }
    else if (!m_dobbelstenen.getTweedeDobbelsteenGebruikt() && (p->print() == m_dobbelstenen.getResultaatVanRol().second || p->print() == "Koning" && m_dobbelstenen.getResultaatVanRol().second == "KoningOfPion" || p->print() == "Pion" && m_dobbelstenen.getResultaatVanRol().second == "KoningOfPion")) {
        if (echt == true) {
            m_dobbelstenen.setTweedeDobbelsteenGebruikt(true);
        }
        return true;
    }
    else
        return false;
}

//checkt of het een correcte zet is
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

void ChaturajiSpel::saveSpel(int i) {
    string naamOpgeslagenSpel;
    string opgeslagenSpelstatus = to_string(i);
    for (int i = 0; i < 32; i++) {
        Pion* p = m_spelbord.getPionVanLijst(i);
        opgeslagenSpelstatus.push_back(p->getTeken());
        opgeslagenSpelstatus.append(to_string(p->getXCoordinaat()));
        opgeslagenSpelstatus.append(to_string(p->getYCoordinaat()));
        if (p->getTeam() == Pion::Team::blauw) {
            opgeslagenSpelstatus.push_back('b');
        }
        else if (p->getTeam() == Pion::Team::groen) {
            opgeslagenSpelstatus.push_back('g');
        }
        else if (p->getTeam() == Pion::Team::rood) {
            opgeslagenSpelstatus.push_back('r');
        }
        else if (p->getTeam() == Pion::Team::geel) {
            opgeslagenSpelstatus.push_back('y');
        }
    }
    cout << "onder welke naam wil je dit spel opslaan?" << endl;
    cin >> naamOpgeslagenSpel;
    ofstream file(naamOpgeslagenSpel+".txt");
    file << opgeslagenSpelstatus << endl;
    file.close();
    ofstream outfile;
    outfile.open("OpgeslagenSpellen.txt", std::ios_base::app);
    outfile << naamOpgeslagenSpel + ".txt,";
    outfile.close();
}

int ChaturajiSpel::loadSpel() {
    string spellen;
    string keuze;
    ifstream savedGames("OpgeslagenSpellen.txt");
    if (savedGames.is_open()) {
        savedGames >> spellen;
    }
    cout << "dit zijn je opgeslagen spellen " + spellen << endl;
    cout << "welk spel wil je openen ?" << endl;
    cin >> keuze;
    ifstream file(keuze);
    while (!file) {
        cout << "dit is geen opgeslagen spel" << endl;
        cout << "welk spel wil je openen ?" << endl;
        cin >> keuze;
        file.open(keuze);
    }
    string saveStatus;
    if (file.is_open()) {
        file >> saveStatus;
    }
    m_spelbord.verwijderPointers();
    for (int i = 1; i < saveStatus.length(); i+=4) {
        maakNieuwePion(saveStatus[i], saveStatus[i + 1], saveStatus[i + 2], saveStatus[i+3]);
    }
    return saveStatus[0] - '0';
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
            stukMagVerplaatstWorden(m_spelbord.zoekPionOpCoordinaat(std::get<0>(coordinatenEersteKlik), std::get<1>(coordinatenEersteKlik)), true);
            if (zet.kijkOfPionnenVerslaanZijnChaturaji(m_spelbord, m_speler)) {
                //QPair<int, int> pion = zet.welkePionIsVerslaan(m_spelbord, m_speler, false);
                //emit pionVerslaan(pion.first, pion.second);
                zet.maakZet(m_spelbord, m_speler);
            }
            else{
                zet.maakZet(m_spelbord, m_speler);
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
    cout << m_dobbelstenen.getResultaatVanRol().first + " , " + m_dobbelstenen.getResultaatVanRol().second << endl;
    if (m_beurt == 3){
        m_beurt = 0;
    }
    else{
        m_beurt++;
    }
}

void ChaturajiSpel::clearMogelijkeZetten(){
    m_mogelijkeZetten.clear();
}
