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

#include "game.h"

void Game::setup(int cols, int rows, int width, int height)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(64,64);
    glutInitWindowSize(width*cols, height*rows);
    glutCreateWindow("PacMan");

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,width*cols-1,0,height*rows-1);

    state=IGame::Running;
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
    for(int c = 0 ; c < 3 ; c++)
    {
        IGhost *g = new Ghost();
        ghosts.push_back(g);
        gluts.push_back(g);
    }
    // AI
    //IArtificialIntelligence *a=new DistanceArtificialIntelligence();
    IArtificialIntelligence *a=new MiniMaxArtificialIntelligence();
    //IArtificialIntelligence *a=new AleatoryArtificialIntelligence();
    ai=a;
    gluts.push_back(a);

    map->setup(*this, cols, rows, width, height);
}

Game::Game(int playerAge)
{
    state=IGame::NotStarted;
    this->playerAge=playerAge;
}

int Game::getEllapsed()
{
    return ellapsed;
}

Game::State Game::getState()
{
    return state;
}

IController *Game::getController()
{
    return controller;
}

IMap *Game::getMap()
{
    return map;
}

IPacMan *Game::getPacman()
{
    return pacman;
}

vector<IGhost *> Game::getGhosts()
{
    return ghosts;
}

IArtificialIntelligence *Game::getAi()
{
    return ai;
}

void Game::displayText( float x, float y, int r, int g, int b, const char *string )
{
    int j = strlen( string );

    glColor3f( r, g, b );
    glRasterPos2f( x, y );
    for( int i = 0; i < j; i++ )
    {
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, string[i] );
    }
}

void Game::display()
{
    glClearColor(0.8,0.8,0.8,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    for(unsigned int i=0;i<gluts.size();i++)
    {
        gluts.at(i)->display(*this);
    }
    if(state==IGame::Win)
    {
        displayText(map->width()*map->cols()/2.0-4*14,map->height()*map->rows()/2.0-9,1,1,1," YOU WIN ");
    }
    if(state==IGame::GameOver)
    {
        displayText(map->width()*map->cols()/2.0-4*14,map->height()*map->rows()/2.0-9,1,1,1,"GAME OVER");
    }
    glutSwapBuffers();
}

void Game::keyboard(unsigned char c, int x, int y)
{
    if(state==IGame::Running) for(unsigned int i=0;i<gluts.size();i++)
    {
        gluts.at(i)->keyboard(*this,c,x,y);
    }
    if(c==' ')
    {
        map->setup(*this,map->cols(),map->rows(),map->width(),map->height());
        state=IGame::Running;
    }
    if(c==27)//esc
    {
        exit(0);
    }
    glutPostRedisplay();
}

void Game::keyboardUp(unsigned char c, int x, int y)
{
    if(state==IGame::Running) for(unsigned int i=0;i<gluts.size();i++)
    {
        gluts.at(i)->keyboardUp(*this,c,x,y);
    }
    glutPostRedisplay();
}

void Game::idle()
{
    struct timeb now;
    ftime(&now);
    ellapsed=(now.time-last.time)*1000.0+now.millitm-last.millitm;
    last=now;
    if(state==IGame::Running)
    {
        for(unsigned int i=0;i<gluts.size();i++)
        {
            gluts.at(i)->idle(*this);
        }
        for(unsigned int i=0;i<ghosts.size();i++)
        {
            IGhost *g=ghosts.at(i);
            if(!i){g->speed(getStressPercent()*getPacman()->speed()*1.5);}
            int x=(int)(pacman->X()/map->width())-(int)(g->X()/map->width());
            int y=(int)(pacman->Y()/map->height())-(int)(g->Y()/map->height());
            if(!x) if(!y)
            {
                if(g->scared())
                {
                    g->scared(false);
                    g->setDirection(0,0);
                    g->X((map->cols()/2.0+0.5)*map->width());
                    g->Y((map->rows()/2.0-1+0.5)*map->height());
                }
                else
                {
                    state=IGame::GameOver;
                }
            }
        }
        bool food=false;
        for(int y=0;y<map->rows();y++)
            for(int x=0;x<map->cols();x++)
                if(map->matrix()[x][y]==2) food=true;
        if(food==false) state=Game::Win;
    }
    glutPostRedisplay();
}

void Game::stateChanged()
{
}

double Game::getTemperaturePercent()
{
    static double lastColorPercent=0.0;
    static int lastTemperature=0;
    // 4 degrees change the color: 0.25 by degree
    int temperature=Arduino::getDoubleValue("temperature");
    if(temperature)
    {
        if(!lastTemperature) lastTemperature=temperature;
        lastColorPercent-=(lastTemperature-temperature)*0.25;
        lastTemperature=temperature;
    }
    if(lastColorPercent<0.0) lastColorPercent=0.0;
    if(lastColorPercent>1.0) lastColorPercent=1.0;
    return lastColorPercent;
}

double Game::getStressPercent()
{
    static int minResistence=999999;
    static int maxResistence=-1;
    double maxHR=220.0-playerAge;
    int pulse=Arduino::getDoubleValue("pulse");
    double heartPercent=0.5;
    if(pulse)
    {
        double p=pulse/maxHR;
        if(p>0.5) if(p<1.0) heartPercent=p;
    }
    double skinPercent=0.0;
    double skin=Arduino::getDoubleValue("skinResistence");
    if(skin)
    {
        if(skin<minResistence) minResistence=skin-3;
        if(skin>maxResistence) maxResistence=skin+3;
        skinPercent=1.0-(skin-minResistence)/(maxResistence-minResistence);
    }
    double r=((heartPercent>skinPercent)?heartPercent:skinPercent);
    return r;
}

double Game::getDistancePercent()
{
    static int maxRange=30;
    static int minRange=10;
    double distance=Arduino::getDoubleValue("distance");
    double distancePercent=1.0;
    if(distance)
    {
        if(distance<minRange) distance=minRange;
        if(distance>maxRange) distance=maxRange;
        distancePercent=(distance-minRange)/(maxRange-minRange);
    }
    return distancePercent;
}
