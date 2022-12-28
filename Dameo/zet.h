#ifndef ZET_H
#define ZET_H

#pragma once

#include "bord.h"
#include "dameopion.h"

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
    void maakZet(Bord speelbord, Pion::Team speler) const;
    bool kijkOfPionnenVerslaanZijn(Bord bord, Pion::Team speler, bool alleenChecken) const;
    int kijkOfPionnenVerslaanZijnChaturaji(Bord bord, Pion::Team speler) const;

private:
    int m_startXCoordinaat, m_startYCoordinaat;
    int m_eindXCoordinaat, m_eindYCoordinaat;
};

#endif // ZET_H