#ifndef DOBBELSTENEN_H
#define DOBBELSTENEN_H


#pragma once

#include <string>
#include <utility>

using namespace std;

class Dobbelstenen {
public:
    void rolDobbelstenen();
    bool getEersteDobbelsteenGebruikt() const;
    bool getTweedeDobbelsteenGebruikt() const;
    void setEersteDobbelsteenGebruikt(bool status);
    void setTweedeDobbelsteenGebruikt(bool status);
    enum class ResultaatDobbelsteen { KoningOfPion, Boot, Paard, Olifant};
    pair<string, string> getResultaatVanRol() const;
private:
    pair<Dobbelstenen::ResultaatDobbelsteen, Dobbelstenen::ResultaatDobbelsteen> getResultaatVanRolEnum() const;
    pair<Dobbelstenen::ResultaatDobbelsteen, Dobbelstenen::ResultaatDobbelsteen> m_resultaatVanRol;
    bool m_eersteDobbelsteenGebruikt{ false };
    bool m_tweedeDobbelsteenGebruikt{ false };
};

#endif // DOBBELSTENEN_H
