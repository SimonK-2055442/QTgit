#ifndef DOBBELSTENEN_H
#define DOBBELSTENEN_H

#pragma once

#include <string>


class Dobbelstenen {
public:
    enum class ResultaatDobbelsteen { KoningOfPion, Boot, Paard, Olifant};
    void rolDobbelstenen();
    bool getEersteDobbelsteenGebruikt() const;
    bool getTweedeDobbelsteenGebruikt() const;
    void setEersteDobbelsteenGebruikt(bool status);
    void setTweedeDobbelsteenGebruikt(bool status);
    std::pair<std::string, std::string> getResultaatVanRol() const;

private:
    std::pair<Dobbelstenen::ResultaatDobbelsteen, Dobbelstenen::ResultaatDobbelsteen> getResultaatVanRolEnum() const;
    std::pair<Dobbelstenen::ResultaatDobbelsteen, Dobbelstenen::ResultaatDobbelsteen> m_resultaatVanRol;
    bool m_eersteDobbelsteenGebruikt{ false };
    bool m_tweedeDobbelsteenGebruikt{ false };
};

#endif // DOBBELSTENEN_H
