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

#ifndef IGLUT_H
#define IGLUT_H

#include "util.h"

#include <GL/glut.h>

class IGame;

class IGlut
{
public:
    virtual void display(IGame &game)=0;
    virtual void keyboard(IGame &game,unsigned char c,int x,int y)=0;
    virtual void keyboardUp(IGame &game,unsigned char c,int x,int y)=0;
    virtual void idle(IGame &game)=0;
};

#endif // IGLUT_H
