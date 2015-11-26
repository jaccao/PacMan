#include "position.h"

Position::Position(int x,int y)
{
    this->x=x;
    this->y=y;
    this->p=NULL;
    this->g=NULL;
}

Position::Position():
    Position(0,0)
{
}

Position::Position(const Position& p,int x,int y):
    Position(x,y)
{
    this->g=p.g;
    assign(p);
}

Position::Position(const Position& p):
    Position(p.x,p.y)
{
    this->g=p.g;
    if(p.p) assign(*p.p);
}

Position::~Position()
{
    if(p) delete p;
}

Position& Position::operator=(const Position& o)
{
    if(p) delete p;
    this->x=o.x;
    this->y=o.y;
    this->p=NULL;
    this->g=o.g;
    if(o.p) assign(*o.p);
    return *this;
}

int Position::directionX()
{
    if(p)
    {
        if(p->x>this->x) return 1;
        else if(p->x<this->x) return -1;
    }
    return 0;
}

int Position::directionY()
{
    if(p)
    {
        if(p->y>this->y) return 1;
        else if(p->y<this->y) return -1;
    }
    return 0;
}

void Position::assign(const Position& p)
{
    this->p=new Position(p);
}
