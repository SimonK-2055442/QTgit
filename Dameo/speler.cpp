//Auteur: Simon Knuts en Yara Mijnendonckx

#include <iostream>
#include "speler.h"


Speler::Speler(Pion::Team spelerAanBeurt) : m_spelerAanBeurt{ spelerAanBeurt } {

}

// functie om punten bij te houden voor Chaturaji
int Speler::getPunten() const {
    return m_punten;
}

void Speler::verhoogPuntenMet(int aantal) {
    m_punten += aantal;
}

Pion::Team Speler::getSpelerAanBeurt() const {
    return m_spelerAanBeurt;
}

string Speler::getSpelerAanBeurtString() const {
    if (m_spelerAanBeurt == Pion::Team::blauw)
        return "blauw";
    else if (m_spelerAanBeurt == Pion::Team::rood)
        return "rood";
    else if (m_spelerAanBeurt == Pion::Team::groen)
        return "groen";
    else
        return "geel";
}
