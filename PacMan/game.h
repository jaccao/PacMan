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

#ifndef GAME_H
#define GAME_H

#include <sys/timeb.h>

#include "imap.h"
#include "ipacman.h"
#include "ighost.h"
#include "iglut.h"
#include "icontroller.h"
#include "iartificialintelligence.h"

#include "arduinocontroller.h"
#include "fakecontroller.h"
#include "keyboardcontroller.h"
#include "map.h"
#include "pacman.h"
#include "ghost.h"
#include "fakeartificialintelligence.h"

class Game
{
private:
    vector< IGlut* > gluts;
    struct timeb last;
    Game();
public:
    int ellapsed;
    IController *controller;
    IMap *map;
    IPacMan *pacman;
    vector< IGhost* > ghosts;
    IArtificialIntelligence *ai;
private:
    static Game &instance();
public:
    static void setup(int cols,int rows,int width,int height);
    static void display();
    static void keyboard(unsigned char c,int x,int y);
    static void keyboardUp(unsigned char c,int x,int y);
    static void idle();
private:
    void setupImp(int cols,int rows,int width,int height);
    void displayImp();
    void keyboardImp(unsigned char c,int x,int y);
    void keyboardUpImp(unsigned char c,int x,int y);
    void idleImp();
};

#endif // BOARD_H
