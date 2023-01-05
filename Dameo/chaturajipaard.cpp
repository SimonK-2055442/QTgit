//Auteur: Simon Knuts en Yara Mijnendonckx

#include "chaturajipaard.h"


ChaturajiPaard::ChaturajiPaard(int yCoordinaat, int xCoordinaat, Team team, char teken) : Pion{ yCoordinaat, xCoordinaat, teken, team } {

}

bool ChaturajiPaard::mogelijkeZet(Bord bord, Zet zet, Team team) {
    if (abs((zet.getStartXCoordinaat() - zet.getEindXCoordinaat()) * (zet.getStartYCoordinaat() - zet.getEindYCoordinaat())) == 2 && team == m_team) {
        if (bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat()) == nullptr)
            return true;
        else if (bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat())->getTeam() != team)
            return true;
    }
    return false;
}

int ChaturajiPaard::getWaarde() {
    return m_waarde;
}

string ChaturajiPaard::print() {
    return "Paard";
}
