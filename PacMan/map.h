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

#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "igame.h"

class Map: public IMap
{
protected:
    int c,r,w,h;
    vector< vector< int > > m;
    int sumArea(int px, int py);

public:
    Map();
    // IGlut interface
public:
    void display(IGame &game);
    void keyboard(IGame &game, unsigned char c, int x, int y);
    void keyboardUp(IGame &game, unsigned char c, int x, int y);
    void idle(IGame &game);

    // IMap interface
public:
    vector<vector<int> > &matrix();
    vector<Position> legalMov(Position &p,vector< vector< int > >* visited=NULL);
    vector<Position> legalMov(vector<Position> &p, vector<vector<int> > *visited);
    void mapgen();
    void setup(IGame &game, int cols, int rows, int width, int height);
    int cols();
    int rows();
    int width();
    int height();
    int random(int nmax);
};

#endif // MAP_H
