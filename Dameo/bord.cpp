//Auteur: Simon Knuts en Yara Mijnendonckx

#include "bord.h"
#include "chaturajipion.h"
#include "chaturajikoning.h"
#include "chaturajiolifant.h"
#include "chaturajipaard.h"
#include "chaturajiboot.h"


void Bord::initialiseerBord(KeuzeSpel spel) {
    if (spel == KeuzeSpel::chaturaji) {
        pionnen.push_back(new ChaturajiPion{ 0,1,Pion::Team::geel,'p',"boot" });
        pionnen.push_back(new ChaturajiPion{ 1,1,Pion::Team::geel,'p',"paard" });
        pionnen.push_back(new ChaturajiPion{ 2,1,Pion::Team::geel,'p',"olifant" });
        pionnen.push_back(new ChaturajiPion{ 3,1,Pion::Team::geel,'p',"koning" });
        pionnen.push_back(new ChaturajiPion{ 1,4,Pion::Team::blauw,'p',"koning" });
        pionnen.push_back(new ChaturajiPion{ 1,5,Pion::Team::blauw,'p',"olifant" });
        pionnen.push_back(new ChaturajiPion{ 1,6,Pion::Team::blauw,'p',"paard" });
        pionnen.push_back(new ChaturajiPion{ 1,7,Pion::Team::blauw,'p',"boot" });
        pionnen.push_back(new ChaturajiPion{ 4,6,Pion::Team::groen,'p',"koning" });
        pionnen.push_back(new ChaturajiPion{ 5,6,Pion::Team::groen,'p',"olifant" });
        pionnen.push_back(new ChaturajiPion{ 6,6,Pion::Team::groen,'p',"paard" });
        pionnen.push_back(new ChaturajiPion{ 7,6,Pion::Team::groen,'p',"boot" });
        pionnen.push_back(new ChaturajiPion{ 6,0,Pion::Team::rood,'p',"boot" });
        pionnen.push_back(new ChaturajiPion{ 6,1,Pion::Team::rood,'p',"paard" });
        pionnen.push_back(new ChaturajiPion{ 6,2,Pion::Team::rood,'p',"olifant" });
        pionnen.push_back(new ChaturajiPion{ 6,3,Pion::Team::rood,'p',"koning" });

        pionnen.push_back(new ChaturajiOlifant{ 2,0,Pion::Team::geel,'o' });
        pionnen.push_back(new ChaturajiOlifant{ 0,5,Pion::Team::blauw,'o' });
        pionnen.push_back(new ChaturajiOlifant{ 5,7,Pion::Team::groen,'o' });
        pionnen.push_back(new ChaturajiOlifant{ 7,2,Pion::Team::rood,'o' });

        pionnen.push_back(new ChaturajiKoning{ 3,0,Pion::Team::geel,'k' });
        pionnen.push_back(new ChaturajiKoning{ 0,4,Pion::Team::blauw,'k' });
        pionnen.push_back(new ChaturajiKoning{ 4,7,Pion::Team::groen,'k' });
        pionnen.push_back(new ChaturajiKoning{ 7,3,Pion::Team::rood,'k' });

        pionnen.push_back(new ChaturajiPaard{ 1,0,Pion::Team::geel,'h' });
        pionnen.push_back(new ChaturajiPaard{ 0,6,Pion::Team::blauw,'h' });
        pionnen.push_back(new ChaturajiPaard{ 6,7,Pion::Team::groen,'h' });
        pionnen.push_back(new ChaturajiPaard{ 7,1,Pion::Team::rood,'h' });

        pionnen.push_back(new ChaturajiBoot{ 0,0,Pion::Team::geel,'b' });
        pionnen.push_back(new ChaturajiBoot{ 0,7,Pion::Team::blauw,'b' });
        pionnen.push_back(new ChaturajiBoot{ 7,7,Pion::Team::groen,'b' });
        pionnen.push_back(new ChaturajiBoot{ 7,0,Pion::Team::rood,'b' });
    }
    else if (spel == KeuzeSpel::dameo) {
        for (int i{ 0 }; i < grootteBord; i++)
            pionnen.push_back(new DameoPion{ 0,i,Pion::Team::blauw,'b' });
        for (int i{ 1 }; i < grootteBord-1; i++)
            pionnen.push_back(new DameoPion{ 1,i,Pion::Team::blauw,'b' });
        for (int i{ 2 }; i < grootteBord-2; i++)
            pionnen.push_back(new DameoPion{ 2,i,Pion::Team::blauw,'b' });

        for (int i{ 0 }; i < grootteBord; i++)
            pionnen.push_back(new DameoPion{ 7,i,Pion::Team::geel,'g' });
        for (int i{ 1 }; i < grootteBord-1; i++)
            pionnen.push_back(new DameoPion{ 6,i,Pion::Team::geel,'g' });
        for (int i{ 2 }; i < grootteBord-2; i++)
            pionnen.push_back(new DameoPion{ 5,i,Pion::Team::geel,'g' });
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
    for (Pion* p : pionnen) {
        if (p->getXCoordinaat() == xCoord && p->getYCoordinaat() == yCoord && !p->isVerslaan())
            return p;
    }
    return nullptr;
}

Pion* Bord::getPionVanLijst(int index) const {
    return pionnen[index];
}

void Bord::voegPionToe(bool dameo, char type, int xCoord, int yCoord, Pion::Team team) {
    if (dameo == false) {
        if (type == 'p') {
            pionnen.push_back(new ChaturajiPion{ yCoord, xCoord, team, type, "koning" });
        }
        else if (type == 'b') {
            pionnen.push_back(new ChaturajiBoot{ yCoord, xCoord, team, type });
        }
        else if (type == 'h') {
            pionnen.push_back(new ChaturajiPaard{ yCoord, xCoord, team, type });
        }
        else if (type == 'k') {
            pionnen.push_back(new ChaturajiKoning{ yCoord, xCoord, team, type });
        }
        else if (type == 'o') {
            pionnen.push_back(new ChaturajiOlifant{ yCoord, xCoord, team, type });
        }
    }
    else {
        DameoPion* p = new DameoPion{ yCoord, xCoord, team, type};
        if (type == 'B' || type == 'G'){
            p->maakKoning();
        }
        pionnen.push_back(p);
    }
}

//wanneer een pion de overkant van het bord bereikt zal deze promoveren en moet deze dus vervangen worden door een ander stuk
void Bord::vervangElement(Zet zet) {
    for (int i = 0; i < pionnen.size(); i++) {
        if (pionnen[i]->getXCoordinaat() == zet.getStartXCoordinaat() && pionnen[i]->getYCoordinaat() == zet.getStartYCoordinaat() && !pionnen[i]->isVerslaan()) {
            if (dynamic_cast<ChaturajiPion*>(pionnen[i])->getPromoverenNaar() == "koning") {
                ChaturajiKoning* nieuwePion = new ChaturajiKoning{ zet.getStartYCoordinaat(),zet.getStartXCoordinaat(),pionnen[i]->getTeam(),'k' };
                pionnen[i] = NULL;
                delete pionnen[i];
                pionnen[i] = nieuwePion;
            }
            else if (dynamic_cast<ChaturajiPion*>(pionnen[i])->getPromoverenNaar() == "olifant") {
                ChaturajiOlifant* nieuwePion = new ChaturajiOlifant{ zet.getStartYCoordinaat(),zet.getStartXCoordinaat(),pionnen[i]->getTeam(),'o' };
                pionnen[i] = NULL;
                delete pionnen[i];
                pionnen[i] = nieuwePion;
            }
            else if (dynamic_cast<ChaturajiPion*>(pionnen[i])->getPromoverenNaar() == "paard") {
                ChaturajiPaard* nieuwePion = new ChaturajiPaard{ zet.getStartYCoordinaat(),zet.getStartXCoordinaat(),pionnen[i]->getTeam(),'h' };
                pionnen[i] = NULL;
                delete pionnen[i];
                pionnen[i] = nieuwePion;
            }
            else if (dynamic_cast<ChaturajiPion*>(pionnen[i])->getPromoverenNaar() == "boot") {
                ChaturajiBoot* nieuwePion = new ChaturajiBoot{ zet.getStartYCoordinaat(),zet.getStartXCoordinaat(),pionnen[i]->getTeam(),'b' };
                pionnen[i] = NULL;
                delete pionnen[i];
                pionnen[i] = nieuwePion;
            }
        }
    }
}

// wanneer een spel is uitgespeeld, kan al het gealloceerde geheugen weer vrijgegeven worden
void Bord::verwijderPointers() {
    for (Pion* p : pionnen) {
        delete p;
        p = NULL;
    }
    pionnen.clear();
}

vector<Pion*> Bord::getPionnen(){
    return pionnen;
}
