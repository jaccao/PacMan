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

#ifndef GAME3D_H
#define GAME3D_H

#include "game.h"

#include "map3d.h"
#include "pacman3d.h"
#include "ghost3d.h"
#include "arduino.h"

class Game3D: public Game
{
public:
    Game3D(int playerAge);
protected:
    void setup(int cols,int rows,int width,int height);
    void display();
    void keyboard(unsigned char c,int x,int y);
private:
    void positionObserverZ();
    int width,height;
    double phi,theta,radius;
};

#endif // BOARD_H
