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

int Game::setup(int argc,char *argv[],int cols, int rows, int width, int height)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(64,64);
    glutInitWindowSize(width*cols, height*rows);
    glutCreateWindow("PacMan");

    glutDisplayFunc(Game::display);
    glutKeyboardFunc(Game::keyboard);
    glutKeyboardUpFunc(Game::keyboardUp);
    glutIdleFunc(Game::idle);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,width*cols-1,0,height*rows-1);

    instance().setupImp(cols,rows, width, height);

    glutMainLoop();
    return 0;
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
    state=Game::Running;
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

void Game::displayImp()
{
    glClearColor(0.8,0.8,0.8,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    for(unsigned int i=0;i<gluts.size();i++)
    {
        gluts.at(i)->display(*this);
    }
    if(state==Game::Win)
    {
        displayText(map->width()*map->cols()/2.0-4*14,map->height()*map->rows()/2.0-9,1,1,1," YOU WIN ");
    }
    if(state==Game::GameOver)
    {
        displayText(map->width()*map->cols()/2.0-4*14,map->height()*map->rows()/2.0-9,1,1,1,"GAME OVER");
    }
    glutSwapBuffers();
}

void Game::keyboardImp(unsigned char c, int x, int y)
{
    if(state==Game::Running) for(unsigned int i=0;i<gluts.size();i++)
    {
        gluts.at(i)->keyboard(*this,c,x,y);
    }
    else if(c==' ')
    {
        map->setup(*this,map->cols(),map->rows(),map->width(),map->height());
        state=Game::Running;
    }
    else if(c==27)//esc
    {
        exit(0);
    }
    glutPostRedisplay();
}

void Game::keyboardUpImp(unsigned char c, int x, int y)
{
    if(state==Game::Running) for(unsigned int i=0;i<gluts.size();i++)
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
    if(state==Game::Running)
    {
        for(unsigned int i=0;i<gluts.size();i++)
        {
            gluts.at(i)->idle(*this);
        }
        for(unsigned int i=0;i<ghosts.size();i++)
        {
            IGhost *g=ghosts.at(i);
            int x=(int)(pacman->X()/map->width())-(int)(g->X()/map->width());
            int y=(int)(pacman->Y()/map->height())-(int)(g->Y()/map->height());
            if(!x) if(!y) state=Game::GameOver;
        }
        bool food=false;
        for(int y=0;y<map->rows();y++)
            for(int x=0;x<map->cols();x++)
                if(map->matrix()[x][y]==2) food=true;
        if(food==false) state=Game::Win;
    }
    glutPostRedisplay();
}
