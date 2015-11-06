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

#include "game.h"

Game &Game::instance()
{
    static Game ctx;
    return(ctx);
}

void Game::keyboard(unsigned char c, int x, int y)
{
    instance().keyboardImp(c,x,y);
}

void Game::keyboardUp(unsigned char c, int x, int y)
{
    instance().keyboardUpImp(c,x,y);
}

void Game::setup(int cols, int rows, int width, int height)
{
    instance().setupImp(cols,rows, width, height);
}

void Game::idle()
{
    instance().idleImp();
}

void Game::display()
{
    instance().displayImp();
}

Game::Game()
{
    ftime(&last);
    // Controller
    IController* k;
#ifdef USE_QT
    k=new ArduinoController();
#else
    k=new KeyboardController();
#endif
    controller=k;
    gluts.push_back(k);
    // Map
    IMap *m=new Map();
    map=m;
    gluts.push_back(m);
    // PacMan
    IPacMan *p=new PacMan();
    pacman=p;
    gluts.push_back(p);
    // Ghosts
    for(int c=0;c<7;c++)
    {
        IGhost *g=new Ghost();
        ghosts.push_back(g);
        gluts.push_back(g);
    }
    // AI
    IArtificialIntelligence *a=new FakeArtificialIntelligence();
    ai=a;
    gluts.push_back(a);
}

void Game::displayImp()
{
    glClearColor(0.8,0.8,0.8,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    for(unsigned int i=0;i<gluts.size();i++)
    {
        gluts.at(i)->display(*this);
    }
    glutSwapBuffers();
}

void Game::keyboardImp(unsigned char c, int x, int y)
{
    for(unsigned int i=0;i<gluts.size();i++)
    {
        gluts.at(i)->keyboard(*this,c,x,y);
    }
    glutPostRedisplay();
}

void Game::keyboardUpImp(unsigned char c, int x, int y)
{
    for(unsigned int i=0;i<gluts.size();i++)
    {
        gluts.at(i)->keyboardUp(*this,c,x,y);
    }
    glutPostRedisplay();
}

void Game::setupImp(int cols, int rows, int width, int height)
{
    map->setup(*this, cols, rows, width, height);
}

void Game::idleImp()
{
    struct timeb now;
    ftime(&now);
    ellapsed=(now.time-last.time)*1000.0+now.millitm-last.millitm;
    last=now;
    for(unsigned int i=0;i<gluts.size();i++)
    {
        gluts.at(i)->idle(*this);
    }
    glutPostRedisplay();
}
