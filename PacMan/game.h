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

#ifndef GAME_H
#define GAME_H

#include <sys/timeb.h>
#include <string.h>

#include "igame.h"
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
#include "distanceartificialintelligence.h"
#include "minimaxartificialintelligence.h"
#include "aleatoryartificialintelligence.h"

class Game: public IGame
{
protected:
    vector< IGlut* > gluts;
    struct timeb last;
    Game();
protected:
    IGame::State state;
    int ellapsed;
    IController *controller;
    IMap *map;
    IPacMan *pacman;
    vector< IGhost* > ghosts;
    IArtificialIntelligence *ai;
protected:
    static Game &instance();
public:
    static int setup(int argc, char *argv[], int cols, int rows, int width, int height);
    static void display();
    static void keyboard(unsigned char c,int x,int y);
    static void keyboardUp(unsigned char c,int x,int y);
    static void idle();
protected:
    void setupImp(int cols,int rows,int width,int height);
    void displayImp();
    void keyboardImp(unsigned char c,int x,int y);
    void keyboardUpImp(unsigned char c,int x,int y);
    void idleImp();
    void displayText(float x, float y, int r, int g, int b, const char *string);

    // IGame interface
public:
    int getEllapsed();
    State getState();
    IController *getController();
    IMap *getMap();
    IPacMan *getPacman();
    vector<IGhost *> getGhosts();
    IArtificialIntelligence *getAi();
};

#endif // BOARD_H
