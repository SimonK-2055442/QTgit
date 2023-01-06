//Auteur: Simon Knuts

#define stringify( name ) #name
#include <time.h>
#include "dobbelstenen.h"

using namespace std;


// de twee dobbelstenen krijgen dankzij deze functie telkens 2 random gegenereerde waarden mee
void Dobbelstenen::rolDobbelstenen() {
    int eersteInt, tweedeInt;
    srand((unsigned)time(NULL));
    eersteInt = rand() % 6 + 1;
    tweedeInt = rand() % 6 + 1;

    if (eersteInt == 1 || eersteInt == 5)
        m_resultaatVanRol.first = ResultaatDobbelsteen::KoningOfPion;
    else if (eersteInt == 2)
        m_resultaatVanRol.first = ResultaatDobbelsteen::Boot;
    else if (eersteInt == 3)
        m_resultaatVanRol.first = ResultaatDobbelsteen::Paard;
    else if (eersteInt == 4 || eersteInt == 6)
        m_resultaatVanRol.first = ResultaatDobbelsteen::Olifant;

    if (tweedeInt == 1 || tweedeInt == 5)
        m_resultaatVanRol.second = ResultaatDobbelsteen::KoningOfPion;
    else if (tweedeInt == 2)
        m_resultaatVanRol.second = ResultaatDobbelsteen::Boot;
    else if (tweedeInt == 3)
        m_resultaatVanRol.second = ResultaatDobbelsteen::Paard;
    else if (tweedeInt == 4 || tweedeInt == 6)
        m_resultaatVanRol.second = ResultaatDobbelsteen::Olifant;
}

bool Dobbelstenen::getEersteDobbelsteenGebruikt() const {
    return m_eersteDobbelsteenGebruikt;
}

bool Dobbelstenen::getTweedeDobbelsteenGebruikt() const {
    return m_tweedeDobbelsteenGebruikt;
}

void Dobbelstenen::setEersteDobbelsteenGebruikt(bool status) {
    m_eersteDobbelsteenGebruikt = status;
}

void Dobbelstenen::setTweedeDobbelsteenGebruikt(bool status) {
    m_tweedeDobbelsteenGebruikt = status;
}

pair<string, string> Dobbelstenen::getResultaatVanRol() const {
    pair<Dobbelstenen::ResultaatDobbelsteen, Dobbelstenen::ResultaatDobbelsteen> resultaatRol = getResultaatVanRolEnum();
    pair<string, string> resultaatVanRolString;

    if (resultaatRol.first == ResultaatDobbelsteen::KoningOfPion)
        resultaatVanRolString.first = "KoningOfPion";
    else if (resultaatRol.first == ResultaatDobbelsteen::Boot)
        resultaatVanRolString.first = "Boot";
    else if (resultaatRol.first == ResultaatDobbelsteen::Paard)
        resultaatVanRolString.first = "Paard";
    else if (resultaatRol.first == ResultaatDobbelsteen::Olifant)
        resultaatVanRolString.first = "Olifant";

    if (resultaatRol.second == ResultaatDobbelsteen::KoningOfPion)
        resultaatVanRolString.second = "KoningOfPion";
    else if (resultaatRol.second == ResultaatDobbelsteen::Boot)
        resultaatVanRolString.second = "Boot";
    else if (resultaatRol.second == ResultaatDobbelsteen::Paard)
        resultaatVanRolString.second = "Paard";
    else if (resultaatRol.second == ResultaatDobbelsteen::Olifant)
        resultaatVanRolString.second = "Olifant";

    return resultaatVanRolString;
}

pair<Dobbelstenen::ResultaatDobbelsteen, Dobbelstenen::ResultaatDobbelsteen> Dobbelstenen::getResultaatVanRolEnum() const {
    return m_resultaatVanRol;
}
