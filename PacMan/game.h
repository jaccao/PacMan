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
#include <algorithm>
#include <iostream>

#include "igame.h"
#include "imap.h"
#include "ipacman.h"
#include "ighost.h"
#include "iglut.h"
#include "icontroller.h"
#include "iartificialintelligence.h"

#include "arduinocontroller.h"
#include "fakecontroller.h"
#include "fakeartificialintelligence.h"
#include "keyboardcontroller.h"
#include "map.h"
#include "pacman.h"
#include "ghost.h"
#include "distanceartificialintelligence.h"
#include "minimaxartificialintelligence.h"
#include "aleatoryartificialintelligence.h"
#include "level.h"

class Game: public IGame
{
protected:
    vector< IGlut* > gluts;
    vector< Level* > levels;
    struct timeb last;
    IGame::State state;
    int ellapsed;
    IController *controller;
    IMap *map;
    IPacMan *pacman;
    vector< IGhost* > ghosts;
    IArtificialIntelligence *ai;
    int playerAge;
    std::string playerName;
    double getTemperaturePercent();
    double getStressPercent();
    double getDistancePercent();
    int width();
    int height();
    int lives;
    int score;
public:
    Game(int playerAge,std::string playerName);
    int getEllapsed();
    State getState();
    IController *getController();
    IMap *getMap();
    IPacMan *getPacman();
    vector<IGhost *> getGhosts();
    IArtificialIntelligence *getAi();
    // IGame interface
    virtual void stateChanged();
    virtual void setup();
    virtual void display();
    virtual void keyboard(unsigned char c,int x,int y);
    virtual void keyboardUp(unsigned char c,int x,int y);
    virtual void idle();
    virtual void displayText(float x, float y, float r, float g, float b, const char *string);
    virtual void reshape(int w, int h);

    // IGame interface
public:
    bool isFirstPerson();

    // IGame interface
public:
    int addScore(int s = -1);
};

#endif // BOARD_H
