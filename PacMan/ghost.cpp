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

#include "ghost.h"

Ghost::Ghost()
{
    lastX=0;
    lastY=0;
    analogX=0;
    analogY=0;
    isScared=false;
    scaredTime=0;
}

void Ghost::display(IGame &game)
{
    (void)game;
    if(scared())
        glColor3f(0.8,0.8,0.8);
    else
        glColor3f(0.0,0.0,1.0);
    glRecti(ghostX-12,ghostY-12,ghostX+12,ghostY+12);
}

void Ghost::keyboard(IGame &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void Ghost::keyboardUp(IGame &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void Ghost::idle(IGame &game)
{

    IMap *map=game.getMap();
    int ellap=game.getEllapsed();
    if(isScared) scaredTime-=ellap;
    if(scaredTime<0){scaredTime=0;isScared=false;}

    int lx=(int)(ghostX/map->width());
    int ly=(int)(ghostY/map->height());

    if(true)
    {
        int dx=analogX;
        int dy=analogY;
        int x=((int)(ghostX/map->width()))+dx;
        int y=((int)(ghostY/map->height()))+dy;
        if((!((map->matrix()[x][y])&1))||((map->matrix()[x][y])==IMap::TileGate))
        {
            if(dx) if(((((int)ghostY)-map->height()/2)%map->height()<2))
            {
                lastX=dx;
                lastY=0;
            }
            if(dy) if(((((int)ghostX)-map->width()/2)%map->width()<2))
            {
                lastY=dy;
                lastX=0;
            }
        }
    }

    int x=lx+(int)lastX;
    int y=ly+(int)lastY;
    if((map->matrix()[x][y])&IMap::TileBlock) if((map->matrix()[x][y])!=IMap::TileGate)
    {
        if(lastX)
        {
            double d=(ghostX-(x+0.5)*map->width())/map->width();
            if(-1.0<d&&d<1.0)
            {
                ghostX=((int)(ghostX/map->width()))*map->width()+map->width()/2.0;
                lastX=0;
            }
        }
        if(lastY)
        {
            double d=(ghostY-(y+0.5)*map->height())/map->height();
            if(-1.0<d&&d<1.0)
            {
                ghostY=((int)(ghostY/map->height()))*map->height()+map->height()/2.0;
                lastY=0;
            }
        }
    }

    ghostX+=lastX*ghostSpeed*(ellap/1000.0);
    ghostY+=lastY*ghostSpeed*(ellap/1000.0);

    if(((int)(ghostX/map->width()))!=lx)
    {
        game.stateChanged();
    }
    else if(((int)(ghostY/map->height()))!=ly)
    {
        game.stateChanged();
    }
}

double Ghost::X(double x)
{
    if(x>=0) ghostX=x;
    return ghostX;
}

double Ghost::Y(double y)
{
    if(y>=0) ghostY=y;
    return ghostY;
}

double Ghost::speed(double s)
{
    if(s>=0) ghostSpeed=s;
    return ghostSpeed;
}

void Ghost::setDirection(double x, double y)
{
    analogX=x;
    analogY=y;
}

bool Ghost::scared(int s)
{
    if(s>=0)
    {
        isScared=s;
        if(isScared) scaredTime=8000;
    }
    return isScared;
}

double Ghost::getDirectionX()
{
    return analogX;
}

double Ghost::getDirectionY()
{
    return analogY;
}
