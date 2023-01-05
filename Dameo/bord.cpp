//Auteur: Simon Knuts en Yara Mijnendonckx

#include "bord.h"
#include "chaturajipion.h"
#include "chaturajikoning.h"
#include "chaturajiolifant.h"
#include "chaturajipaard.h"
#include "chaturajiboot.h"


void Bord::initialiseerBord(KeuzeSpel spel) {
    if (spel == KeuzeSpel::chaturaji) {
        m_pionnen.push_back(new ChaturajiPion{ 0,1,Pion::Team::geel,'p',"boot" });
        m_pionnen.push_back(new ChaturajiPion{ 1,1,Pion::Team::geel,'p',"paard" });
        m_pionnen.push_back(new ChaturajiPion{ 2,1,Pion::Team::geel,'p',"olifant" });
        m_pionnen.push_back(new ChaturajiPion{ 3,1,Pion::Team::geel,'p',"koning" });
        m_pionnen.push_back(new ChaturajiPion{ 1,4,Pion::Team::blauw,'p',"koning" });
        m_pionnen.push_back(new ChaturajiPion{ 1,5,Pion::Team::blauw,'p',"olifant" });
        m_pionnen.push_back(new ChaturajiPion{ 1,6,Pion::Team::blauw,'p',"paard" });
        m_pionnen.push_back(new ChaturajiPion{ 1,7,Pion::Team::blauw,'p',"boot" });
        m_pionnen.push_back(new ChaturajiPion{ 4,6,Pion::Team::groen,'p',"koning" });
        m_pionnen.push_back(new ChaturajiPion{ 5,6,Pion::Team::groen,'p',"olifant" });
        m_pionnen.push_back(new ChaturajiPion{ 6,6,Pion::Team::groen,'p',"paard" });
        m_pionnen.push_back(new ChaturajiPion{ 7,6,Pion::Team::groen,'p',"boot" });
        m_pionnen.push_back(new ChaturajiPion{ 6,0,Pion::Team::rood,'p',"boot" });
        m_pionnen.push_back(new ChaturajiPion{ 6,1,Pion::Team::rood,'p',"paard" });
        m_pionnen.push_back(new ChaturajiPion{ 6,2,Pion::Team::rood,'p',"olifant" });
        m_pionnen.push_back(new ChaturajiPion{ 6,3,Pion::Team::rood,'p',"koning" });

        m_pionnen.push_back(new ChaturajiOlifant{ 2,0,Pion::Team::geel,'o' });
        m_pionnen.push_back(new ChaturajiOlifant{ 0,5,Pion::Team::blauw,'o' });
        m_pionnen.push_back(new ChaturajiOlifant{ 5,7,Pion::Team::groen,'o' });
        m_pionnen.push_back(new ChaturajiOlifant{ 7,2,Pion::Team::rood,'o' });

        m_pionnen.push_back(new ChaturajiKoning{ 3,0,Pion::Team::geel,'k' });
        m_pionnen.push_back(new ChaturajiKoning{ 0,4,Pion::Team::blauw,'k' });
        m_pionnen.push_back(new ChaturajiKoning{ 4,7,Pion::Team::groen,'k' });
        m_pionnen.push_back(new ChaturajiKoning{ 7,3,Pion::Team::rood,'k' });

        m_pionnen.push_back(new ChaturajiPaard{ 1,0,Pion::Team::geel,'h' });
        m_pionnen.push_back(new ChaturajiPaard{ 0,6,Pion::Team::blauw,'h' });
        m_pionnen.push_back(new ChaturajiPaard{ 6,7,Pion::Team::groen,'h' });
        m_pionnen.push_back(new ChaturajiPaard{ 7,1,Pion::Team::rood,'h' });

        m_pionnen.push_back(new ChaturajiBoot{ 0,0,Pion::Team::geel,'b' });
        m_pionnen.push_back(new ChaturajiBoot{ 0,7,Pion::Team::blauw,'b' });
        m_pionnen.push_back(new ChaturajiBoot{ 7,7,Pion::Team::groen,'b' });
        m_pionnen.push_back(new ChaturajiBoot{ 7,0,Pion::Team::rood,'b' });
    }
    else if (spel == KeuzeSpel::dameo) {
        for (int i{ 0 }; i < m_grootteBord; i++)
            m_pionnen.push_back(new DameoPion{ 0,i,Pion::Team::blauw,'b' });
        for (int i{ 1 }; i < m_grootteBord-1; i++)
            m_pionnen.push_back(new DameoPion{ 1,i,Pion::Team::blauw,'b' });
        for (int i{ 2 }; i < m_grootteBord-2; i++)
            m_pionnen.push_back(new DameoPion{ 2,i,Pion::Team::blauw,'b' });

        for (int i{ 0 }; i < m_grootteBord; i++)
            m_pionnen.push_back(new DameoPion{ 7,i,Pion::Team::geel,'g' });
        for (int i{ 1 }; i < m_grootteBord-1; i++)
            m_pionnen.push_back(new DameoPion{ 6,i,Pion::Team::geel,'g' });
        for (int i{ 2 }; i < m_grootteBord-2; i++)
            m_pionnen.push_back(new DameoPion{ 5,i,Pion::Team::geel,'g' });
    }
}

bool Bord::isZetInHetBord(Zet zet) const {
    //checken dat coordinaten in het bord liggen
    if (zet.getStartXCoordinaat() > 7 || zet.getStartXCoordinaat() < 0 || zet.getStartYCoordinaat() > 7 || zet.getStartYCoordinaat() < 0)
        return false;

    if (zet.getEindXCoordinaat() > 7 || zet.getEindXCoordinaat() < 0 || zet.getEindYCoordinaat() > 7 || zet.getEindYCoordinaat() < 0)
        return false;

    //start- en eindpositie moeten ook verschillend zijn
    if ((zet.getStartXCoordinaat() == zet.getEindXCoordinaat()) && (zet.getStartYCoordinaat() == zet.getEindYCoordinaat()))
        return false;
    else
        return true;
}

//loopt over alle pionen totdat het een pion vindt met de gegeven coordinaten en geeft deze dan terug
Pion* Bord::zoekPionOpCoordinaat(int yCoord, int xCoord) const {
    for (Pion* p : m_pionnen) {
        if (p->getXCoordinaat() == xCoord && p->getYCoordinaat() == yCoord && !p->isVerslaan())
            return p;
    }
    return nullptr;
}

Pion* Bord::getPionVanLijst(int index) const {
    return m_pionnen[index];
}

void Bord::voegPionToe(bool dameo, char type, int xCoord, int yCoord, Pion::Team team) {
    if (dameo == false) {
        if (type == 'p') {
            m_pionnen.push_back(new ChaturajiPion{ yCoord, xCoord, team, type, "koning" });
        }
        else if (type == 'b') {
            m_pionnen.push_back(new ChaturajiBoot{ yCoord, xCoord, team, type });
        }
        else if (type == 'h') {
            m_pionnen.push_back(new ChaturajiPaard{ yCoord, xCoord, team, type });
        }
        else if (type == 'k') {
            m_pionnen.push_back(new ChaturajiKoning{ yCoord, xCoord, team, type });
        }
        else if (type == 'o') {
            m_pionnen.push_back(new ChaturajiOlifant{ yCoord, xCoord, team, type });
        }
    } else {
        DameoPion* p = new DameoPion{ yCoord, xCoord, team, type};
        if (type == 'B' || type == 'G'){
            p->maakKoning();
        }
        m_pionnen.push_back(p);
    }
}

//wanneer een pion de overkant van het bord bereikt zal deze promoveren en moet deze dus vervangen worden door een ander stuk
void Bord::vervangElement(Zet zet) {
    for (int i = 0; i < m_pionnen.size(); i++) {
        if (m_pionnen[i]->getXCoordinaat() == zet.getStartXCoordinaat() && m_pionnen[i]->getYCoordinaat() == zet.getStartYCoordinaat() && !m_pionnen[i]->isVerslaan()) {
            if (dynamic_cast<ChaturajiPion*>(m_pionnen[i])->getPromoverenNaar() == "koning") {
                ChaturajiKoning* nieuwePion = new ChaturajiKoning{ zet.getStartYCoordinaat(),zet.getStartXCoordinaat(),m_pionnen[i]->getTeam(),'k' };
                m_pionnen[i] = NULL;
                delete m_pionnen[i];
                m_pionnen[i] = nieuwePion;
            }
            else if (dynamic_cast<ChaturajiPion*>(m_pionnen[i])->getPromoverenNaar() == "olifant") {
                ChaturajiOlifant* nieuwePion = new ChaturajiOlifant{ zet.getStartYCoordinaat(),zet.getStartXCoordinaat(),m_pionnen[i]->getTeam(),'o' };
                m_pionnen[i] = NULL;
                delete m_pionnen[i];
                m_pionnen[i] = nieuwePion;
            }
            else if (dynamic_cast<ChaturajiPion*>(m_pionnen[i])->getPromoverenNaar() == "paard") {
                ChaturajiPaard* nieuwePion = new ChaturajiPaard{ zet.getStartYCoordinaat(),zet.getStartXCoordinaat(),m_pionnen[i]->getTeam(),'h' };
                m_pionnen[i] = NULL;
                delete m_pionnen[i];
                m_pionnen[i] = nieuwePion;
            }
            else if (dynamic_cast<ChaturajiPion*>(m_pionnen[i])->getPromoverenNaar() == "boot") {
                ChaturajiBoot* nieuwePion = new ChaturajiBoot{ zet.getStartYCoordinaat(),zet.getStartXCoordinaat(),m_pionnen[i]->getTeam(),'b' };
                m_pionnen[i] = NULL;
                delete m_pionnen[i];
                m_pionnen[i] = nieuwePion;
            }
        }
    }
}

// wanneer een spel is uitgespeeld, kan al het gealloceerde geheugen weer vrijgegeven worden
void Bord::verwijderPointers() {
    for (Pion* p : m_pionnen) {
        delete p;
        p = NULL;
    }
    m_pionnen.clear();
}

vector<Pion*> Bord::getPionnen(){
    return m_pionnen;
}
