#ifndef PION_H
#define PION_H

#pragma once

#include <string>
class Bord;
class Zet;

using namespace std;

class Pion {
public:
    int getXCoordinaat() const;
    int getYCoordinaat() const;
    void setXCoordinaat(int xCoordinaat);
    void setYCoordinaat(int yCoordinaat);
    enum class Team { blauw, geel, rood, groen};
    Team getTeam() const;
    void verslaPion();
    bool isVerslaan() const;
    char getTeken() const;
    void verzetPion(int yCoord, int xCoord);
    virtual bool mogelijkeZet(Bord bord, Zet zet, Team team) = 0;
    virtual int getWaarde() = 0;
    virtual string print() = 0;

protected:
    Pion(int yCoordinaat, int xCoordinaat, char teken, Team team);
    int m_xCoordinaat;
    int m_yCoordinaat;
    Team m_team;
    bool m_isVerslaan{false};
    char m_teken;
};

#endif // PION_H
