#ifndef POSITION_H
#define POSITION_H

#include "ighost.h"

class Position
{
public:
    int x,y;
    Position* p;
    IGhost* g;
    Position(int x,int y);
    Position();
    Position(const Position& p,int x,int y);
    Position(const Position& p);
    ~Position();
    Position& operator=(const Position& o);
    int directionX();
    int directionY();
private:
    void assign(const Position& p);
};

#endif // POSITION_H
