//Auteur: Simon Knuts en Yara Mijnendonckx

#include "ChaturajiKoning.h"

ChaturajiKoning::ChaturajiKoning(int yCoordinaat, int xCoordinaat, Team team, char teken) : Pion{ yCoordinaat, xCoordinaat, teken, team } {

}

bool ChaturajiKoning::mogelijkeZet(Bord bord, Zet zet, Team team) {
    if (abs(zet.getEindXCoordinaat() - zet.getStartXCoordinaat()) <= 1 && abs(zet.getEindYCoordinaat() - zet.getStartYCoordinaat()) <= 1 && team == m_team) {
        if (bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat()) == nullptr)
            return true;
        else if (bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat())->getTeam() != team)
            return true;
    }
    return false;
}

int ChaturajiKoning::getWaarde() {
    return m_waarde;
}

string ChaturajiKoning::print() {
    return "Koning";
}
