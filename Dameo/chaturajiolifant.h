#ifndef CHATURAJIOLIFANT_H
#define CHATURAJIOLIFANT_H

#pragma once

#include "zet.h"


class ChaturajiOlifant : public Pion {
public:
    ChaturajiOlifant(int yCoordinaat, int xCoordinaat, Team team, char teken);
    bool mogelijkeZet(Bord bord, Zet zet, Team team) override;
    int getWaarde() override;
    string print() override;
    bool mogelijkeZetHorizontaal(Bord bord, Zet zet, Team team) const;
    bool mogelijkeZetVerticaal(Bord bord, Zet zet, Team team) const;

private:
    int m_waarde{ 4 };
};

#endif // CHATURAJIOLIFANT_H
