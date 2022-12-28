#include "speler.h"
//Auteur: Simon Knuts en Yara Mijnendonckx

#include <iostream>
#include <limits>
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
    if (m_spelerAanBeurt == Pion::Team::rood)
        return "rood";
    if (m_spelerAanBeurt == Pion::Team::groen)
        return "groen";
    if (m_spelerAanBeurt == Pion::Team::geel)
        return "geel";
    else
        return "Mag niet!";
}

// tijdens Chaturaji kan een speler zijn beurt beëindigen met behulp van deze functie
bool Speler::wiltBeurtStoppen() const {
    int keuzeOmBeurtTeStoppen;
    cout << "Kan je een stuk verzetten, druk dan 1. Moet je je beurt stoppen, druk dan 2." << endl;
    cin >> keuzeOmBeurtTeStoppen;
    while (1) {
        if (keuzeOmBeurtTeStoppen == 1 || keuzeOmBeurtTeStoppen == 2) {
            if (keuzeOmBeurtTeStoppen == 2)
                return true;
            else
                break;
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Gelieve geldige input op te geven!" << endl;
            cin >> keuzeOmBeurtTeStoppen;
        }
    }
    return false;
}
