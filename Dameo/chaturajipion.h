#ifndef CHATURAJIPION_H
#define CHATURAJIPION_H

#pragma once

#include "zet.h"


class ChaturajiPion : public Pion {
public:
    ChaturajiPion(int yCoordinaat, int xCoordinaat, Team team, char teken, string promoverenNaar);
    bool mogelijkeZet(Bord bord, Zet zet, Team team) override;
    int getWaarde() override;
    string print() override;
    void promoveer(Bord bord, Zet zet);
    bool magPromoveren(Bord bord, Zet zet) const;
    bool isGepromoveerd() const;
    string getPromoverenNaar() const;

private:
    int m_waarde{ 1 };
    bool m_isGepromoveerd{ false };
    string m_promoverenNaar;
};

#endif // CHATURAJIPION_H
