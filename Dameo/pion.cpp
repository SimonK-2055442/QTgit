//Auteur: Yara Mijnendonckx en Simon Knuts

#include "pion.h"


Pion::Pion(int yCoordinaat, int xCoordinaat, char teken, Team team) :m_xCoordinaat{ xCoordinaat }, m_yCoordinaat{ yCoordinaat }, m_team{ team }, m_teken{ teken } {

}

int Pion::getXCoordinaat() const {
    return m_xCoordinaat;
}

int Pion::getYCoordinaat() const {
    return m_yCoordinaat;
}

void Pion::setXCoordinaat(int xCoordinaat) {
    m_xCoordinaat = xCoordinaat;
}

void Pion::setYCoordinaat(int yCoordinaat) {
    m_yCoordinaat = yCoordinaat;
}

Pion::Team Pion::getTeam() const {
    return m_team;
}

void Pion::verslaPion() {
    m_isVerslaan = true;
}

bool Pion::isVerslaan() const {
    return m_isVerslaan;
}

char Pion::getTeken() const {
    return m_teken;
}

void Pion::verzetPion(int yCoord, int xCoord) {
    m_xCoordinaat = xCoord;
    m_yCoordinaat = yCoord;
}
