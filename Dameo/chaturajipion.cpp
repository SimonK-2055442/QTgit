//Auteur: Simon Knuts en Yara Mijnendonckx

#include "ChaturajiPion.h"
#include "ChaturajiKoning.h"
#include "ChaturajiOlifant.h"
#include "ChaturajiPaard.h"
#include "ChaturajiBoot.h"

ChaturajiPion::ChaturajiPion(int yCoordinaat, int xCoordinaat, Team team, char teken, string promoverenNaar) : Pion{ yCoordinaat, xCoordinaat, teken,team }, m_promoverenNaar{promoverenNaar} {

}

bool ChaturajiPion::mogelijkeZet(Bord bord, Zet zet, Team team) {
    pair<int, int> teamParameter;
    if (m_team == Team::geel) {
        teamParameter.first = 1;
        teamParameter.second = 0;
    }
    else if (m_team == Team::blauw) {
        teamParameter.first = 0;
        teamParameter.second = 1;
    }
    else if (m_team == Team::groen) {
        teamParameter.first = -1;
        teamParameter.second = 0;
    }
    else if (m_team == Team::rood) {
        teamParameter.first = 0;
        teamParameter.second = -1;
    }

    if (team != m_team)
        return false;

    if (zet.getEindXCoordinaat() == zet.getStartXCoordinaat() + teamParameter.first && zet.getEindYCoordinaat() == zet.getStartYCoordinaat() + teamParameter.second && bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat()) == nullptr) {
        if (magPromoveren(bord, zet))
            dynamic_cast<ChaturajiPion*>(bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), zet.getStartXCoordinaat()))->promoveer(bord, zet);
        return true;
    }
    if (m_team == Team::geel || m_team == Team::groen) {
        if (zet.getEindXCoordinaat() == zet.getStartXCoordinaat() + teamParameter.first && zet.getEindYCoordinaat() == zet.getStartYCoordinaat() + 1 || zet.getEindXCoordinaat() == zet.getStartXCoordinaat() + teamParameter.first && zet.getEindYCoordinaat() == zet.getStartYCoordinaat() - 1) {
            if (bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat()) != nullptr && bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat())->getTeam() != m_team) {
                if (magPromoveren(bord, zet))
                    dynamic_cast<ChaturajiPion*>(bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), zet.getStartXCoordinaat()))->promoveer(bord, zet);
                return true;
            }
            else
                return false;
        }
        return false;

    }
    else {
        if (zet.getEindXCoordinaat() == zet.getStartXCoordinaat() + 1 && zet.getEindYCoordinaat() == zet.getStartYCoordinaat() + teamParameter.second || zet.getEindXCoordinaat() == zet.getStartXCoordinaat() - 1 && zet.getEindYCoordinaat() == zet.getStartYCoordinaat() + teamParameter.second) {
            if (bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat()) != nullptr && bord.zoekPionOpCoordinaat(zet.getEindYCoordinaat(), zet.getEindXCoordinaat())->getTeam() != m_team) {
                if (magPromoveren(bord, zet))
                    dynamic_cast<ChaturajiPion*>(bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), zet.getStartXCoordinaat()))->promoveer(bord, zet);
                return true;
            }
            else
                return false;
        }
    }
    return false;
}

int ChaturajiPion::getWaarde() {
    return m_waarde;
}

string ChaturajiPion::print() {
    return "Pion";
}

void ChaturajiPion::promoveer(Bord bord, Zet zet) {
    m_isGepromoveerd = true;
    bord.vervangElement(zet);
}

bool ChaturajiPion::magPromoveren(Bord bord, Zet zet) {
    if (bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), zet.getStartXCoordinaat())->getTeam() == Team::geel
        && zet.getEindXCoordinaat() == 7)
        return true;
    if (bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), zet.getStartXCoordinaat())->getTeam() == Team::blauw
        && zet.getEindYCoordinaat() == 7)
        return true;
    if (bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), zet.getStartXCoordinaat())->getTeam() == Team::groen
        && zet.getEindXCoordinaat() == 0)
        return true;
    if (bord.zoekPionOpCoordinaat(zet.getStartYCoordinaat(), zet.getStartXCoordinaat())->getTeam() == Team::rood
        && zet.getEindYCoordinaat() == 0)
        return true;

    return false;
}

bool ChaturajiPion::isGepromoveerd() const {
    return m_isGepromoveerd;
}

string ChaturajiPion::getPromoverenNaar() const {
    return m_promoverenNaar;
}
