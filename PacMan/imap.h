/*
# Copyright (C) 2015, 2016 Luiz Fernando Jaccao <luizfernandojaccao@gmail.com>
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

class IMap: public IGlut
{
public:
    virtual void mapgen();
    virtual void setup(Game &game,int cols, int rows, int width, int height);
    virtual vector< vector< int > > &matrix();
    virtual int cols();
    virtual int rows();
    virtual int width();
    virtual int height();
};

#endif // IMAP_H
