//Auteur: Simon Knuts en Yara Mijnendonckx

#include <iostream>
#include <string>
#include "zet.h"

Zet::Zet(int startXCoordinaat, int startYCoordinaat, int eindXCoordinaat, int eindYCoordinaat) : m_startXCoordinaat{ startXCoordinaat }, m_startYCoordinaat{ startYCoordinaat }, m_eindXCoordinaat{ eindXCoordinaat },m_eindYCoordinaat{eindYCoordinaat} {

}

int Zet::getStartXCoordinaat() const {
    return m_startXCoordinaat;
}

int Zet::getStartYCoordinaat() const {
    return m_startYCoordinaat;
}

int Zet::getEindXCoordinaat() const {
    return m_eindXCoordinaat;
}

int Zet::getEindYCoordinaat() const {
    return m_eindYCoordinaat;
}

void Zet::setStartXCoordinaat(int xCoordinaat) {
    m_startXCoordinaat = xCoordinaat;
}

void Zet::setStartYCoordinaat(int yCoordinaat) {
    m_startYCoordinaat = yCoordinaat;
}

void Zet::setEindXCoordinaat(int xCoordinaat) {
    m_eindXCoordinaat = xCoordinaat;
}

void Zet::setEindYCoordinaat(int yCoordinaat) {
    m_eindYCoordinaat = yCoordinaat;
}

void Zet::maakZet(Bord bord, Pion::Team speler) const {
    //elke zet kijken (in het geval van een dameoPion) of er een pion gepromoveerd moet worden
    Pion* teVerzettenPion = bord.zoekPionOpCoordinaat(m_startYCoordinaat, m_startXCoordinaat);
    if (dynamic_cast<DameoPion*>(teVerzettenPion) != nullptr) {
        if (m_eindYCoordinaat == 0 || m_eindYCoordinaat == 7)
            dynamic_cast<DameoPion*>(teVerzettenPion)->maakKoning();
    }
    teVerzettenPion->verzetPion(m_eindYCoordinaat, m_eindXCoordinaat);
}

//functie bekijkt of er in de vakjes waarover er gesprongen is, tijdens de zet, een vijandige pion staat en verwijdert deze
bool Zet::kijkOfPionnenVerslaanZijn(Bord bord, DameoPion::Team speler, bool alleenChecken) const {
    int begin;
    int einde;
    if (m_startXCoordinaat == m_eindXCoordinaat) {
        if (m_startYCoordinaat < m_eindYCoordinaat) {
            begin = m_startYCoordinaat;
            einde = m_eindYCoordinaat;
        } else {
            begin = m_eindYCoordinaat;
            einde = m_startYCoordinaat;
        }
        for (int i = begin; i < einde; i++) {
            if (bord.zoekPionOpCoordinaat(i, m_startXCoordinaat) != nullptr && bord.zoekPionOpCoordinaat(i, m_startXCoordinaat)->getTeam() != speler) {
                if (alleenChecken == false) {
                    bord.zoekPionOpCoordinaat(i, m_startXCoordinaat)->verslaPion();
                }
                return true;
            }
        }
    }
    if (m_startYCoordinaat == m_eindYCoordinaat) {
        if (m_startXCoordinaat < m_eindXCoordinaat) {
            begin = m_startXCoordinaat;
            einde = m_eindXCoordinaat;
        } else {
            begin = m_eindXCoordinaat;
            einde = m_startXCoordinaat;
        }
        for (int i = begin; i < einde; i++) {
            if (bord.zoekPionOpCoordinaat(m_startYCoordinaat, i) != nullptr && bord.zoekPionOpCoordinaat(m_startYCoordinaat, i)->getTeam() != speler) {
                if (alleenChecken == false) {
                    bord.zoekPionOpCoordinaat(m_startYCoordinaat, i)->verslaPion();
                }
                return true;
            }
        }
    }
    return false;
}

// in het geval van Chaturaji wordt een pion verslaan als op de eindpositie een vijandige pion staat, deze pion wordt ook verwijderd
int Zet::kijkOfPionnenVerslaanZijnChaturaji(Bord bord, Pion::Team speler) const {
    Pion* pionOpEindeVanZet = bord.zoekPionOpCoordinaat(m_eindYCoordinaat, m_eindXCoordinaat);
    if (pionOpEindeVanZet != nullptr && pionOpEindeVanZet->getTeam() != speler) {
        int waarde = pionOpEindeVanZet->getWaarde();
        pionOpEindeVanZet->verslaPion();
        return waarde;
    }
    return 0;
}