/*
# Copyright (C) 2015, 2016
# Luiz Fernando Jaccao <luizfernandojaccao@gmail.com>
# William Malheiros Evangelista <williammalheiros_2@hotmail.com>
# Jose David Oliveira Nunes <david.nunes.co@hotmail.com>
# This file is part of PacMan Project - UdL/FACENS Sem Fronteira.
#
# PacMan is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# PacMan is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
*/

#ifndef IMAP_H
#define IMAP_H

#include <vector>
using std::vector;
#include "iglut.h"

class Game;

class Position
{
public:
    int x,y;
    Position* p;
    Position(int x,int y)
    {
        this->x=x;
        this->y=y;
        this->p=NULL;
    }
    Position():
        Position(0,0)
    {
    }
    Position(const Position& p,int x,int y):
        Position(x,y)
    {
        assign(p);
    }
    Position(const Position& p):
        Position(p.x,p.y)
    {
        if(p.p) assign(*p.p);
    }
    ~Position()
    {
        if(p) delete p;
    }
    Position& operator=(const Position& o)
    {
        if(p) delete p;
        this->x=o.x;
        this->y=o.y;
        this->p=NULL;
        if(o.p) assign(*o.p);
        return *this;
    }
private:
    void assign(const Position& p)
    {
        this->p=new Position(p);
    }
};

class IMap: public IGlut
{
public:
    enum Tile{TileNone=0,TileBlock=1,TileFood=2,TilePower=4,TileGate=9,TileDebug=128};
    virtual void mapgen();
    virtual void setup(Game &game,int cols, int rows, int width, int height);
    virtual vector< vector< int > > &matrix();
    virtual int cols();
    virtual int rows();
    virtual int width();
    virtual int height();
    virtual vector<Position> legalMov(Position &p,vector< vector< int > >* visited=NULL);
    virtual vector<Position> legalMov(vector<Position> &p,vector< vector< int > >* visited=NULL);
};

#endif // IMAP_H
