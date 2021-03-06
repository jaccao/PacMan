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

#ifndef GHOST_H
#define GHOST_H

#include "soil/SOIL.h"

#include "igame.h"

class Ghost: public IGhost
{
protected:
    double ghostX,ghostY;
    double lastX,lastY;
    double analogX,analogY;
    bool isScared;
    int scaredTime;
public:
    Ghost();

    // IGlut interface
public:
    void display(IGame &game);
    void keyboard(IGame &game, unsigned char c, int x, int y);
    void keyboardUp(IGame &game, unsigned char c, int x, int y);
    void idle(IGame &game);

    // IGhost interface
public:
    double X(double x=-1);
    double Y(double y=-1);
    double speed(double s=-1);
    bool scared(int s=-1);
    void setDirection(double x, double y);
    double getDirectionX();
    double getDirectionY();
};

#endif // GHOST_H
