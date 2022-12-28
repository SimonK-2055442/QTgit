#ifndef SPELER_H
#define SPELER_H

#pragma once

#include <string>
#include "pion.h"

class Speler {
public:
    Speler(Pion::Team spelerAanBeurt);
    int getPunten() const;
    void verhoogPuntenMet(int aantal);
    Pion::Team getSpelerAanBeurt() const;
    string getSpelerAanBeurtString() const;
    bool wiltBeurtStoppen() const;

private:
    Pion::Team m_spelerAanBeurt;
    int m_punten{ 0 };
};

#endif // SPELER_H
