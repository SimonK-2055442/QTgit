//Auteur: Simon Knuts en Yara Mijnendonckx

#include "chaturajiolifant.h"

ChaturajiOlifant::ChaturajiOlifant(int yCoordinaat, int xCoordinaat, Team team, char teken) : Pion{ yCoordinaat, xCoordinaat, teken, team } {

}

bool ChaturajiOlifant::mogelijkeZet(Bord bord, Zet zet, Team team) {
    if ((zet.getEindXCoordinaat() == zet.getStartXCoordinaat() || zet.getEindYCoordinaat() == zet.getStartYCoordinaat()) && team == m_team) {
        if (zet.getEindXCoordinaat() == zet.getStartXCoordinaat()) {
            return mogelijkeZetVerticaal(bord, zet, team);
        }
        else if (zet.getEindYCoordinaat() == zet.getStartYCoordinaat()) {
            return mogelijkeZetHorizontaal(bord, zet, team);
        }
        return false;
    }
    return false;
}

int ChaturajiOlifant::getWaarde() {
    return m_waarde;
}

string ChaturajiOlifant::print() {
    return "Olifant";
}

bool ChaturajiOlifant::mogelijkeZetHorizontaal(Bord bord, Zet zet, Team team) {
    if (zet.getEindXCoordinaat() > zet.getStartXCoordinaat()) {
        for (int i = zet.getStartXCoordinaat() + 1; i <= zet.getEindXCoordinaat() - 1; i++) {
            if (bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), i) != nullptr)
                return false;
        }
    }
    if (zet.getEindXCoordinaat() < zet.getStartXCoordinaat()) {
        for (int i = zet.getStartXCoordinaat() - 1; i >= zet.getEindXCoordinaat() + 1; i--) {
            if (bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), i) != nullptr)
                return false;
        }
    }
    if (zet.getEindXCoordinaat() != zet.getStartXCoordinaat()) {
        if (bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat()) == nullptr)
            return true;
        else if (bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat())->getTeam() != team)
            return true;
        else
            return false;
    }
    return false;
}

bool ChaturajiOlifant::mogelijkeZetVerticaal(Bord bord, Zet zet, Team team) {
    if (zet.getEindYCoordinaat() > zet.getStartYCoordinaat()) {
        for (int i = zet.getStartYCoordinaat() + 1; i <= zet.getEindYCoordinaat() - 1; i++) {
            if (bord.zoekPionOpCoordinaat(i, zet.getStartXCoordinaat()) != nullptr)
                return false;
        }
    }
    if (zet.getEindYCoordinaat() < zet.getStartYCoordinaat()) {
        for (int i = zet.getStartYCoordinaat() - 1; i >= zet.getEindYCoordinaat() + 1; i--) {
            if (bord.zoekPionOpCoordinaat(i, zet.getStartXCoordinaat()) != nullptr)
                return false;
        }
    }
    if (zet.getEindYCoordinaat() != zet.getStartYCoordinaat()) {
        if (bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat()) == nullptr)
            return true;
        else if (bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat())->getTeam() != team)
            return true;
        else
            return false;
    }
    return false;
}
