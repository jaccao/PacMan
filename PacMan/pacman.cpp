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

#include "pacman.h"

PacMan::PacMan()
{

}

void PacMan::display(IGame &game)
{
    (void)game;
    glColor3f(0.8,0.8,0.0);
    glRecti(pacX-12,pacY-12,pacX+12,pacY+12);
}

void PacMan::keyboard(IGame &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void PacMan::keyboardUp(IGame &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void PacMan::idle(IGame &game)
{
//    static int lastX=0,lastY=0;
    IController *controller=game.getController();
    IMap *map=game.getMap();
    int ellap=game.getEllapsed();
    if(controller)
    {
        double ax=controller->analogX()*controller->digitalX();
        double ay=controller->analogY()*controller->digitalY();
        int dx=controller->digitalX();
        int dy=controller->digitalY();
        if(ax>ay)
        {
            dy=0;
        }
        else
        {
            dx=0;
        }
        int x=((int)(pacX/map->width()))+dx;
        int y=((int)(pacY/map->height()))+dy;
        if(!((map->matrix()[x][y])&IMap::TileBlock))
        {
            if(dx) if(((((int)pacY)-map->height()/2)%map->height()<2))
            {
                lastX=dx;
                lastY=0;
            }
            if(dy) if(((((int)pacX)-map->width()/2)%map->width()<2))
            {
                lastY=dy;
                lastX=0;
            }
        }
    }
    int x=((int)(pacX/map->width()))+(int)lastX;
    int y=((int)(pacY/map->height()))+(int)lastY;
    if((map->matrix()[x][y])&IMap::TileBlock)
    {
        if(lastX)
        {
            double d=(pacX-(x+0.5)*map->width())/map->width();
            if(-1.0<d&&d<1.0)
            {
                pacX=((int)(pacX/map->width()))*map->width()+map->width()/2.0;
                lastX=0;
            }
        }
        if(lastY)
        {
            double d=(pacY-(y+0.5)*map->height())/map->height();
            if(-1.0<d&&d<1.0)
            {
                pacY=((int)(pacY/map->height()))*map->height()+map->height()/2.0;
                lastY=0;
            }
        }
    }
    pacX+=lastX*pacSpeed*(ellap/1000.0);
    pacY+=lastY*pacSpeed*(ellap/1000.0);
    x=((int)(pacX/map->width()));
    y=((int)(pacY/map->height()));
    if(map->matrix()[x][y]==IMap::TileFood) map->matrix()[x][y]=IMap::TileNone;
    if(map->matrix()[x][y]==IMap::TilePower)
    {
        map->matrix()[x][y]=IMap::TileNone;
        for(unsigned int c=0;c<game.getGhosts().size();c++) game.getGhosts()[c]->scared(true);
    }
}

double PacMan::X(double x)
{
    if(x>=0) pacX=x;
    return pacX;
}

double PacMan::Y(double y)
{
    if(y>=0) pacY=y;
    return pacY;
}

double PacMan::speed(double s)
{
    if(s>=0) pacSpeed=s;
    return pacSpeed;
}
