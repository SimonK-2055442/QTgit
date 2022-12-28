#ifndef CHATURAJIBOOT_H
#define CHATURAJIBOOT_H


#pragma once

#include "Zet.h"

using namespace std;

class ChaturajiBoot : public Pion {
public:
    ChaturajiBoot(int yCoordinaat, int xCoordinaat, Team team, char teken);
    bool mogelijkeZet(Bord bord, Zet zet, Team team) override;
    int getWaarde() override;
    string print() override;
private:
    int m_waarde{ 2 };
};
#endif // CHATURAJIBOOT_H
