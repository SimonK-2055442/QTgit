#ifndef ZET_H
#define ZET_H

#pragma once

#include "bord.h"
#include "dameopion.h"
#include <QPair>

class Zet {
public:
    Zet(int startXCoordinaat, int startYCoordinaat, int eindXCoordinaat, int eindYCoordinaat);
    int getStartXCoordinaat() const;
    int getStartYCoordinaat() const;
    int getEindXCoordinaat() const;
    int getEindYCoordinaat() const;
    void setStartXCoordinaat(int startXCoordinaat);
    void setStartYCoordinaat(int startYCoordinaat);
    void setEindXCoordinaat(int eindXCoordinaat);
    void setEindYCoordinaat(int eindYCoordinaat);
    bool eindeVanBordBereiktBijZet(Bord speelbord);
    void maakZet(Bord speelbord) const;
    QPair<int, int> welkePionIsVerslaan(Bord bord, Pion::Team speler, bool alleenChecken);
    Pion* welkePionIsErVerslaanChaturaji(Bord bord, Pion::Team speler) const;

private:
    int m_startXCoordinaat, m_startYCoordinaat;
    int m_eindXCoordinaat, m_eindYCoordinaat;
};

#endif // ZET_H
