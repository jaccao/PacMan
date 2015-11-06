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

#include "ghost.h"

Ghost::Ghost()
{
    lastX=0;
    lastY=0;
    analogX=0;
    analogY=0;
}

void Ghost::display(Game &game)
{
    (void)game;
    glColor3f(0.0,0.0,0.8);
    glRecti(ghostX-12,ghostY-12,ghostX+12,ghostY+12);
}

void Ghost::keyboard(Game &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void Ghost::keyboardUp(Game &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void Ghost::idle(Game &game)
{
    IMap *map=game.map;
    int ellap=game.ellapsed;
    int x=((int)(ghostX/map->width()))+(int)analogX;
    int y=((int)(ghostY/map->height()))+(int)analogY;
    if((!((map->matrix()[x][y])&1))||((map->matrix()[x][y])&2))
    {
        if((((int)ghostY)-map->height()/2)%map->height()<1) if(analogX)
        {
            lastX=analogX;
            lastY=0;
        }
        if(((int)ghostX-map->width()/2)%map->width()<1) if(analogY)
        {
            lastY=analogY;
            lastX=0;
        }
    }
    x=((int)(ghostX/map->width()))+(int)lastX;
    y=((int)(ghostY/map->height()))+(int)lastY;
    if((map->matrix()[x][y])&1)
    {
        if(lastX)
        {
            double d=(pacX-(x+0.5)*map->width())/map->width();
            if(-1.0<d&&d<1.0) lastX=0;
        }
        if(lastY)
        {
            double d=(pacY-(y+0.5)*map->height())/map->height();
            if(-1.0<d&&d<1.0) lastY=0;
        }
    }
    ghostX+=lastX*ghostSpeed*(ellap/1000.0);
    ghostY+=lastY*ghostSpeed*(ellap/1000.0);
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
