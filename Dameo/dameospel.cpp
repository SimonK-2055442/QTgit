//Auteur: Simon Knuts

#include <iostream>
#include <fstream>
#include "dameospel.h"
#include <QDebug>
//#include "bordview.h"

//using namespace std;

DameoSpel::DameoSpel(Bord spelbord) : m_spelbord{spelbord}{
    m_speler = DameoPion::Team::blauw;
};

int DameoSpel::vertaal(string teVertalen) const {
    int vertaaldeString;
    try {
        vertaaldeString = stoi(teVertalen) - 1;
    }
    catch (...) {
        vertaaldeString = (teVertalen[0] - 'A');
    }
    return vertaaldeString;
}

void DameoSpel::startSpel(int spelkeuze) {
    string teVerzettenStuk, eindPositie;
    bool magNogEenZet{ false };
    char wilNogEenZet{ 'n' };
    m_spelbord.initialiseerBord(Bord::KeuzeSpel::dameo);
    while (isGedaan() == 0) {
        /*if (m_spelbord.zoekPionOpCoordinaat(5, 0) != nullptr) {
            m_beurt = loadSpel();
            //m_spelbord.laatZien();
        }*/
        if (m_beurt % 2 == 0)
            m_speler = DameoPion::Team::geel;
        else
            m_speler = DameoPion::Team::blauw;
        if (m_speler == DameoPion::Team::geel && spelkeuze == 1)
            vindEnMaakZet();
        else {
            m_spelbord.laatZien();
            if (m_speler == DameoPion::Team::blauw)
                cout << "Speler 1 (blauw): welke pion wil je verzetten? " << endl;
            else
                cout << "Speler 2 (geel): welke pion wil je verzetten? " << endl;
            cin >> teVerzettenStuk;
            DameoPion* p = dynamic_cast<DameoPion*>(m_spelbord.zoekPionOpCoordinaat(vertaal(teVerzettenStuk.substr(1, 1)), vertaal(teVerzettenStuk.substr(0, 1))));
            vindAlleZettenVoorPion(m_spelbord, m_speler, p, false);
            cout << "Naar welke positie wil je dit stuk verplaatsen?" << endl;
            cin >> eindPositie;
            Zet zet{ vertaal(teVerzettenStuk.substr(0, 1)),vertaal(teVerzettenStuk.substr(1, 1)),vertaal(eindPositie.substr(0, 1)),vertaal(eindPositie.substr(1, 1)) };
            if (p == nullptr || p->mogelijkeZet(m_spelbord, zet, m_speler) == false) {
                while (p == nullptr || p->mogelijkeZet(m_spelbord, zet, m_speler) == false) {
                    cout << "Gelieve een geldige zet in te geven!" << endl;
                    if (m_speler == DameoPion::Team::blauw)
                        cout << "Speler 1 (blauw): welke pion wil je verzetten?" << endl;
                    else
                        cout << "Speler 2 (geel): welke pion wil je verzetten?" << endl;
                    cin >> teVerzettenStuk;
                    p = dynamic_cast<DameoPion*>(m_spelbord.zoekPionOpCoordinaat(vertaal(teVerzettenStuk.substr(1, 1)), vertaal(teVerzettenStuk.substr(0, 1))));
                    vindAlleZettenVoorPion(m_spelbord, m_speler, p, false);
                    cout << "Naar welke positie wil je dit stuk verplaatsen?" << endl;
                    cin >> eindPositie;
                    zet.setStartXCoordinaat(vertaal(teVerzettenStuk.substr(0, 1)));
                    zet.setStartYCoordinaat(vertaal(teVerzettenStuk.substr(1, 1)));
                    zet.setEindXCoordinaat(vertaal(eindPositie.substr(0, 1)));
                    zet.setEindYCoordinaat(vertaal(eindPositie.substr(1, 1)));
                }
            }
            if (zet.isErEenPionVerslaan(m_spelbord, m_speler, false))
                magNogEenZet = true;
            else
                magNogEenZet = false;
            zet.maakZet(m_spelbord, m_speler);
            while (magNogEenZet == true) {
                m_spelbord.laatZien();
                cout << "Kan je nog een zet doen waarbij je een pion verslaat? Zoja, wil je deze uitvoeren? Druk j voor ja en n voor nee." << endl;
                cin >> wilNogEenZet;
                if (wilNogEenZet == 'j') {
                    vindAlleZettenVoorPion(m_spelbord, m_speler, p, true);
                    cout << "Naar welke positie wil je het stuk verplaatsen?" << endl;
                    cin >> eindPositie;
                    Zet extraZet{ zet.getEindXCoordinaat(), zet.getEindYCoordinaat(), vertaal(eindPositie.substr(0, 1)), vertaal(eindPositie.substr(1, 1)) };
                    if (p->mogelijkeZet(m_spelbord, extraZet, m_speler) && extraZet.isErEenPionVerslaan(m_spelbord, m_speler, false)) {
                        extraZet.maakZet(m_spelbord, m_speler);
                        m_spelbord.laatZien();
                        zet.setEindXCoordinaat(extraZet.getEindXCoordinaat());
                        zet.setEindYCoordinaat(extraZet.getEindYCoordinaat());
                    }
                    else {
                        magNogEenZet = false;
                        cout << "Dat was geen geldige extra zet!" << endl;
                    }
                }
                else
                    magNogEenZet = false;
            }
        }
    m_beurt++;
    saveSpel(m_beurt);
    }
    cout << "Proficiat speler " << isGedaan() << " u heeft het spel gewonnen!";
    m_spelbord.verwijderPointers();
}

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
void DameoSpel::vindEnMaakZet() const {
    bool gevonden{ false };
    for (int i = 18; i < 35; i++) {
        Pion* p = m_spelbord.getPionVanLijst(i);
        Zet zet{ p->getXCoordinaat(), p->getYCoordinaat(), p->getXCoordinaat(), p->getYCoordinaat() };
        for (int x = 1; x < 8; x++) {
            for (int y = 1; y < 8; y++) {
                zet.setEindXCoordinaat(x);
                zet.setEindYCoordinaat(y);
                if (gevonden == false) {
                    if (p->mogelijkeZet(m_spelbord, zet, DameoPion::Team::geel)) {
                        zet.welkePionIsVerslaan(m_spelbord, DameoPion::Team::geel, false);
                        zet.maakZet(m_spelbord, DameoPion::Team::geel);
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

void DameoSpel::vindAlleZettenVoorPion(Bord spelbord,DameoPion::Team speler, DameoPion* p, bool moetPakken) {
    vector<int> mogelijkeZetten;
    if (p != nullptr) {
        string vertalen = "ABCDEFGH";
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (p->getXCoordinaat() != i || p->getYCoordinaat() != j) {
                    Zet zet{ p->getXCoordinaat(), p->getYCoordinaat(), i,j };
                    if (p->mogelijkeZet(spelbord, zet, speler) == true) {
                        if ((moetPakken == true && zet.isErEenPionVerslaan(spelbord, speler, true)) || moetPakken == false) {
                            string mogelijkeZet = vertalen[i] + to_string(j + 1);
                            cout << mogelijkeZet + " ";
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

void DameoSpel::saveSpel(int i) {
    string naamOpgeslagenSpel;
    string opgeslagenSpelstatus = to_string(i);
    for (int i = 0; i < 36; i++) {
        Pion* p = m_spelbord.getPionVanLijst(i);
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
    cout << "onder welke naam wil je dit spel opslaan?" << endl;
    cin >> naamOpgeslagenSpel;
    ofstream file(naamOpgeslagenSpel + ".txt");
    file << opgeslagenSpelstatus << endl;
    file.close();
    ofstream outfile;
    outfile.open("OpgeslagenSpellen.txt", std::ios_base::app);
    outfile << naamOpgeslagenSpel + ".txt,";
    outfile.close();
}

int DameoSpel::loadSpel() {
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
    for (int i = 1; i < saveStatus.length(); i += 4) {
        maakNieuwePion(saveStatus[i], saveStatus[i + 1], saveStatus[i + 2], saveStatus[i + 3]);
    }
    return saveStatus[0] - '0';
}

void DameoSpel::maakNieuwePion(char type, char xCoord, char yCoord, char team) {
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
    else if (team == 'b') {
        teamPion = Pion::Team::blauw;
    }
    m_spelbord.voegPionToe(true, type, xCoordPion, yCoordPion, teamPion);
}

Bord DameoSpel::getBord() {
    return m_spelbord;
}

std::vector<int> DameoSpel::eersteKlik(int rij,int kolom) {
    if(m_spelbord.zoekPionOpCoordinaat(rij,kolom) == nullptr || rij < 0 || rij > 7 || kolom < 0 || kolom > 7 || m_spelbord.zoekPionOpCoordinaat(rij,kolom)->getTeam() != m_speler) {
        m_mogelijkeZetten.clear();
        return m_mogelijkeZetten;
    }
    else {
        coordinatenEersteKlik = make_tuple(rij , kolom);
        DameoPion* pion = dynamic_cast<DameoPion*>(m_spelbord.zoekPionOpCoordinaat(rij, kolom));
        if (m_pionDieNogEenZetMag != nullptr){
            vindAlleZettenVoorPion(m_spelbord,m_spelbord.zoekPionOpCoordinaat(rij, kolom)->getTeam(), pion, true);
        }
        else{
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

            if (zet.isErEenPionVerslaan(m_spelbord, m_speler, true)) {
                QPair<int, int> pion = zet.welkePionIsVerslaan(m_spelbord, m_speler, false);
                m_pionDieNogEenZetMag = dynamic_cast<DameoPion*>(m_spelbord.zoekPionOpCoordinaat(std::get<0>(coordinatenEersteKlik), std::get<1>(coordinatenEersteKlik)));
                emit pionVerslaan(pion.first, pion.second);
                if (zet.maakZet(m_spelbord, m_speler) != nullptr) {
                    emit pionPromoveren(rij, kolom, parameterSpeler);
                }
            } else {
                m_pionDieNogEenZetMag = nullptr;
                if (zet.maakZet(m_spelbord, m_speler) != nullptr) {
                    emit pionPromoveren(rij, kolom, parameterSpeler);
                }
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

void DameoSpel::clearMogelijkeZetten(){
    m_mogelijkeZetten.clear();
}

void DameoSpel::veranderBeurt(){
    if (m_speler == DameoPion::Team::geel) {
        m_speler = DameoPion::Team::blauw;
    } else {
        m_speler = DameoPion::Team::geel;
    }
}
