//Auteur: Simon Knuts en Yara Mijnendonckx

#include "ChaturajiBoot.h"

ChaturajiBoot::ChaturajiBoot(int yCoordinaat, int xCoordinaat, Team team, char teken) : Pion{ yCoordinaat, xCoordinaat, teken, team }  {

}

bool ChaturajiBoot::mogelijkeZet(Bord bord, Zet zet, Team team) {
    if ((abs((zet.getEindXCoordinaat() - zet.getStartXCoordinaat())) == 2 && abs((zet.getEindYCoordinaat() - zet.getStartYCoordinaat())) == 2) && team == m_team) {
        if (bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat()) == nullptr)
            return true;
        if (bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat())->print() == "Koning")
            return false;
        else if (bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat())->getTeam() != team)
            return true;
    }
    return false;
}

int ChaturajiBoot::getWaarde() {
    return m_waarde;
}

string ChaturajiBoot::print() {
    return "Boot";
}
