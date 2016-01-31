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
    Game3D(int playerAge, std::string playerName);
private:
    void positionObserverZ();
    double phi,theta;
    bool firstPerson;
    double radius;
    double test;
    double lastEyeX;
    double lastEyeY;
    double lastEyeZ;
    double lastTargetX;
    double lastTargetY;
    double lastTargetZ;

    // IGame interface
protected:
    void setup();
    void display();
    void keyboard(unsigned char c,int x,int y);
    void reshape(int w, int h);
    void idle();
    bool isFirstPerson();
    void displayText(float x, float y, float r, float g, float b, const char *string);
};

#endif // BOARD_H
