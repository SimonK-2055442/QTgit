#ifndef CHATURAJIKONING_H
#define CHATURAJIKONING_H


#pragma once

#include "Zet.h"

using namespace std;

class ChaturajiKoning : public Pion {
public:
    ChaturajiKoning(int yCoordinaat, int xCoordinaat, Team team, char teken);
    bool mogelijkeZet(Bord bord, Zet zet, Team team) override;
    int getWaarde() override;
    string print() override;
private:
    int m_waarde{ 5 };
};

#endif // CHATURAJIKONING_H
