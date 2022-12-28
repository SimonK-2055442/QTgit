#ifndef CHATURAJIPAARD_H
#define CHATURAJIPAARD_H


#pragma once

#include "Zet.h"

using namespace std;

class ChaturajiPaard : public Pion {
public:
    ChaturajiPaard(int yCoordinaat, int xCoordinaat, Team team, char teken);
    bool mogelijkeZet(Bord bord, Zet zet, Team team) override;
    int getWaarde() override;
    string print() override;
private:
    int m_waarde{ 3 };
};

#endif // CHATURAJIPAARD_H
