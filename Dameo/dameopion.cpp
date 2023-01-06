//Auteur: Yara Mijnendonckx en Simon Knuts

#include "dameopion.h"


DameoPion::DameoPion(int yCoordinaat, int xCoordinaat, Team team, char teken) : Pion{ yCoordinaat, xCoordinaat, teken, team } {

}

void DameoPion::maakKoning() {
    m_isKoning = true;
    if (m_teken == 'b')
        m_teken = 'B';

    if (m_teken == 'g')
        m_teken = 'G';
}

bool DameoPion::isKoning() const {
    return m_isKoning;
}

bool DameoPion::mogelijkeZet(Bord bord, Zet zet, DameoPion::Team speler) {
    //checken dat coordinaten in het bord liggen
    if (zet.getStartXCoordinaat() > 7 || zet.getStartXCoordinaat() < 0 || zet.getStartYCoordinaat() > 7 || zet.getStartYCoordinaat() < 0)
        return false;

    if (zet.getEindXCoordinaat() > 7 || zet.getEindXCoordinaat() < 0 || zet.getEindYCoordinaat() > 7 || zet.getEindYCoordinaat() < 0)
        return false;

    //start- en eindpositie gelijk
    if ((zet.getStartXCoordinaat() == zet.getEindXCoordinaat()) && (zet.getStartYCoordinaat() == zet.getEindYCoordinaat()))
        return false;

    //geen pion op de startpositie
    if ((bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), zet.getStartXCoordinaat())) == nullptr)
        return false;

    //wel een pion op de eindpositie
    if ((bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat())) != nullptr)
        return false;

    //pion op startpositie is niet van de speler
    if (((bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), zet.getStartXCoordinaat()))->getTeam()) != speler)
        return false;

    int teamParameter;	//blauw = +1, geel = -1
    if ((bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), zet.getStartXCoordinaat()))->getTeam() == DameoPion::Team::blauw)
        teamParameter = +1;
    else
        teamParameter = -1;

    //het stuk dat verplaatst wordt is een pion
    if (dynamic_cast<DameoPion*>(bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), zet.getStartXCoordinaat()))->isKoning() == false)
        return mogelijkeBewegingVanPion(bord, zet, teamParameter, speler);

    //het stuk dat verplaatst wordt is een koning
    else
        //diagonale beweging van de koning
        if (abs(zet.getEindXCoordinaat() - zet.getStartXCoordinaat()) == abs(zet.getEindYCoordinaat() - zet.getStartYCoordinaat()))
            return diagonaleBewegingVanKoning(bord, zet);
        //'rechte' (= horizontaal en verticaal) beweging van de koning of slaan
        else
            return rechteBewegingVanKoning(bord, zet, speler);
}

bool DameoPion::mogelijkeBewegingVanPion(Bord bord, Zet zet, int parameterSpeler, DameoPion::Team speler) const {	//teamParameter: zwart = +1, wit = -1
    // simpele beweging met pion
    if ((zet.getStartXCoordinaat() == zet.getEindXCoordinaat()) && (zet.getStartYCoordinaat() + (1 * parameterSpeler) == zet.getEindYCoordinaat()))
        return true;
    if ((zet.getStartXCoordinaat() - 1 == zet.getEindXCoordinaat()) && (zet.getStartYCoordinaat() + (1 * parameterSpeler) == zet.getEindYCoordinaat()))
        return true;
    if ((zet.getStartXCoordinaat() + 1 == zet.getEindXCoordinaat()) && (zet.getStartYCoordinaat() + (1 * parameterSpeler) == zet.getEindYCoordinaat()))
        return true;

    // slaan met pion
    if ((zet.getStartXCoordinaat() == zet.getEindXCoordinaat()) && (zet.getStartYCoordinaat() + (2 * parameterSpeler) == zet.getEindYCoordinaat())) {
        if ((bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat() + (1 * parameterSpeler), zet.getStartXCoordinaat())) != nullptr
            && bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat() + (1 * parameterSpeler), zet.getStartXCoordinaat())->getTeam() != speler)
            return true;
    }
    if ((zet.getStartXCoordinaat() - 2 == zet.getEindXCoordinaat()) && (zet.getStartYCoordinaat() == zet.getEindYCoordinaat())) {
        if ((bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), zet.getStartXCoordinaat() - 1)) != nullptr
            && bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), zet.getStartXCoordinaat() - 1)->getTeam() != speler)
            return true;
    }
    if ((zet.getStartXCoordinaat() + 2 == zet.getEindXCoordinaat()) && (zet.getStartYCoordinaat() == zet.getEindYCoordinaat())) {
        if ((bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), zet.getStartXCoordinaat() + 1)) != nullptr
            && bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), zet.getStartXCoordinaat() + 1)->getTeam() != speler)
            return true;
    }

    // lange beweging met pion
    if ((zet.getStartXCoordinaat() == zet.getEindXCoordinaat()) && ((zet.getStartYCoordinaat() - zet.getEindYCoordinaat()) * parameterSpeler <= -1)) {
        for (int i = 1; i <= abs(zet.getEindYCoordinaat() - zet.getStartYCoordinaat()) - 1; i++) {
            if (bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat() + (i * parameterSpeler), zet.getStartXCoordinaat()) == nullptr)
                return false;
            if ((bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat() + (i * parameterSpeler), zet.getStartXCoordinaat())->getTeam()) != speler)
                return false;
        }
        return true;
    }
    if ((zet.getStartXCoordinaat() - zet.getEindXCoordinaat() > 0) && ((zet.getStartYCoordinaat() - zet.getEindYCoordinaat()) * parameterSpeler <= -1)
        && (abs(zet.getStartXCoordinaat() - zet.getEindXCoordinaat()) == abs(zet.getStartYCoordinaat() - zet.getEindYCoordinaat()))) {
        for (int i = 1; i < abs(zet.getEindYCoordinaat() - zet.getStartYCoordinaat()); i++) {
            if (bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat() + (i * parameterSpeler), zet.getStartXCoordinaat() - i) == nullptr)
                return false;
            if ((bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat() + (i * parameterSpeler), zet.getStartXCoordinaat() - i)->getTeam()) != speler)
                return false;
        }
        return true;
    }
    if ((zet.getStartXCoordinaat() - zet.getEindXCoordinaat() < 0) && ((zet.getStartYCoordinaat() - zet.getEindYCoordinaat()) * parameterSpeler <= -1)
        && (abs(zet.getStartXCoordinaat() - zet.getEindXCoordinaat()) == abs(zet.getStartYCoordinaat() - zet.getEindYCoordinaat()))) {
        for (int i = 1; i < abs(zet.getEindYCoordinaat() - zet.getStartYCoordinaat()); i++) {
            if (bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat() + (i * parameterSpeler), zet.getStartXCoordinaat() + i) == nullptr)
                return false;
            if ((bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat() + (i * parameterSpeler), zet.getStartXCoordinaat() + i)->getTeam()) != speler)
                return false;
        }
        return true;
    }
    return false;
}

bool DameoPion::diagonaleBewegingVanKoning(Bord bord, Zet zet) const {
    if ((zet.getEindXCoordinaat() - zet.getStartXCoordinaat() < 0) && (zet.getEindYCoordinaat() - zet.getStartYCoordinaat() < 0)) {
        for (int i = 1; i < abs(zet.getStartXCoordinaat() - zet.getEindXCoordinaat()); i++) {
            if ((bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat() - i, zet.getStartXCoordinaat() - i)) != nullptr)
                return false;
        }
        return true;
    }
    if ((zet.getEindXCoordinaat() - zet.getStartXCoordinaat() > 0) && (zet.getEindYCoordinaat() - zet.getStartYCoordinaat() < 0)) {
        for (int i = 1; i < abs(zet.getStartXCoordinaat() - zet.getEindXCoordinaat()); i++) {
            if ((bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat() - i, zet.getStartXCoordinaat() + i)) != nullptr)
                return false;
        }
        return true;
    }
    if ((zet.getEindXCoordinaat() - zet.getStartXCoordinaat() > 0) && (zet.getEindYCoordinaat() - zet.getStartYCoordinaat() > 0)) {
        for (int i = 1; i < abs(zet.getStartXCoordinaat() - zet.getEindXCoordinaat()); i++) {
            if ((bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat() + i, zet.getStartXCoordinaat() + i)) != nullptr) {
                return false;
            }
        }
        return true;
    }
    if ((zet.getEindXCoordinaat() - zet.getStartXCoordinaat() < 0) && (zet.getEindYCoordinaat() - zet.getStartYCoordinaat() > 0)) {
        for (int i = 1; i < abs(zet.getStartXCoordinaat() - zet.getEindXCoordinaat()); i++) {
            if ((bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat() + i, zet.getStartXCoordinaat() - 1)) != nullptr)
                return false;
        }
        return true;
    }
    return false;
}

bool DameoPion::rechteBewegingVanKoning(Bord bord, Zet zet, DameoPion::Team speler) const {
    if ((zet.getStartXCoordinaat() == zet.getEindXCoordinaat()) && (zet.getStartYCoordinaat() - 1 == zet.getEindYCoordinaat()))
        return true;
    if ((zet.getStartXCoordinaat() == zet.getEindXCoordinaat()) && (zet.getStartYCoordinaat() + 1 == zet.getEindYCoordinaat()))
        return true;
    if ((zet.getStartXCoordinaat() - 1 == zet.getEindXCoordinaat()) && (zet.getStartYCoordinaat() == zet.getEindYCoordinaat()))
        return true;
    if ((zet.getStartXCoordinaat() + 1 == zet.getEindXCoordinaat()) && (zet.getStartYCoordinaat() == zet.getEindYCoordinaat()))
        return true;

    if ((zet.getStartXCoordinaat() == zet.getEindXCoordinaat()) && (zet.getStartYCoordinaat() > zet.getEindYCoordinaat())) {
        if ((bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat() + 1, zet.getEindXCoordinaat())) != nullptr) {
            if ((bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat() + 1, zet.getEindXCoordinaat()))->getTeam() == speler)
                return false;
        }
        for (int i = 1; i < (abs(zet.getStartYCoordinaat() - zet.getEindYCoordinaat()) - 1); i++) {
            if ((bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat() - i, zet.getStartXCoordinaat())) != nullptr)
                return false;
        }
        return true;
    }
    if ((zet.getStartXCoordinaat() == zet.getEindXCoordinaat()) && (zet.getStartYCoordinaat() < zet.getEindYCoordinaat())) {
        if ((bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat() - 1, zet.getEindXCoordinaat())) != nullptr) {
            if ((bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat() - 1, zet.getEindXCoordinaat()))->getTeam() == speler)
                return false;
        }
        for (int i = 1; i < (abs(zet.getStartYCoordinaat() - zet.getEindYCoordinaat()) - 1); i++) {
            if ((bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat() + i, zet.getStartXCoordinaat())) != nullptr)
                return false;
        }
        return true;
    }
    if ((zet.getStartXCoordinaat() < zet.getEindXCoordinaat()) && (zet.getStartYCoordinaat() == zet.getEindYCoordinaat())) {
        if ((bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat() - 1)) != nullptr) {
            if ((bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat() - 1))->getTeam() == speler)
                return false;
        }
        for (int i = 1; i < (abs(zet.getStartXCoordinaat() - zet.getEindXCoordinaat()) - 1); i++) {
            if ((bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), zet.getStartXCoordinaat() + i)) != nullptr)
                return false;
        }
        return true;
    }
    if ((zet.getStartXCoordinaat() > zet.getEindXCoordinaat()) && (zet.getStartYCoordinaat() == zet.getEindYCoordinaat())) {
        if ((bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat() + 1)) != nullptr) {
            if ((bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat() + 1))->getTeam() == speler)
                return false;
        }
        for (int i = 1; i < (abs(zet.getStartXCoordinaat() - zet.getEindXCoordinaat()) - 1); i++) {
            if ((bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), zet.getStartXCoordinaat() - i)) != nullptr)
                return false;
        }
        return true;
    }
    return false;
}

string DameoPion::print() {
    return "dameoPion";
}

//overbodig voor Dameo, wel nodig om het concept polymorfisme bij Chaturaji toe te passen
int DameoPion::getWaarde() {
    return -1;
}
