#ifndef DAMEOPION_H
#define DAMEOPION_H

#pragma once

#include "zet.h"
#include "pion.h"


class DameoPion : public Pion {
public:
    DameoPion(int yCoordinaat, int xCoordinaat, Team team, char teken);
    void maakKoning();
    bool isKoning() const;
    bool mogelijkeZet(Bord bord, Zet zet, DameoPion::Team speler) override;
    bool mogelijkeBewegingVanPion(Bord bord, Zet zet, int parameterSpeler, DameoPion::Team speler) const;
    bool diagonaleBewegingVanKoning(Bord bord, Zet zet, DameoPion::Team speler) const;
    bool rechteBewegingVanKoning(Bord bord, Zet zet, DameoPion::Team speler) const;
    string print() override;
    int getWaarde() override;

private:
    bool m_isKoning{ false };
};

#endif // DAMEOPION_H
