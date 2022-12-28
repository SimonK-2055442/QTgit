#ifndef CHATURAJIOLIFANT_H
#define CHATURAJIOLIFANT_H


#pragma once

#include "Zet.h"

using namespace std;

class ChaturajiOlifant : public Pion {
public:
    ChaturajiOlifant(int yCoordinaat, int xCoordinaat, Team team, char teken);
    bool mogelijkeZet(Bord bord, Zet zet, Team team) override;
    int getWaarde() override;
    string print() override;
    bool mogelijkeZetHorizontaal(Bord bord, Zet zet, Team team);
    bool mogelijkeZetVerticaal(Bord bord, Zet zet, Team team);
private:
    int m_waarde{ 4 };
};

#endif // CHATURAJIOLIFANT_H
