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
    IController *controller=game.getController();
    IMap *map=game.getMap();
    int ellap=game.getEllapsed();
    int x=((int)(pacX/map->width()));
    int y=((int)(pacY/map->height()));
    if(controller)
    {
        double ax=controller->analogX();
if(Util::isDebugTime(true)) qDebug()<<"start";
if(Util::isDebugTime()) qDebug()<<"ax:"<<ax;
        double ay=controller->analogY();
        // only legal directions
        if((map->matrix()[x+Util::topInt(ax)][y])&IMap::TileBlock) ax=0;
        if((map->matrix()[x][y+Util::topInt(ay)])&IMap::TileBlock) ay=0;
if(Util::isDebugTime()) qDebug()<<"legal ax:"<<ax;
        // only one direction
        if(Util::abs(ax)>Util::abs(ay))
            ay=0;
        else
            ax=0;
if(Util::isDebugTime()) qDebug()<<"only ax:"<<ax;
        // if pacman is in position to change X
        if(ax) if(((((int)pacY)-map->height()/2)%map->height()<2))
        {
if(Util::isDebugTime()) qDebug()<<"iam x:"<<lastX;
            // if change direction
            if(Util::topInt(ax)!=Util::topInt(lastX))
            {
                lastX=ax;
if(Util::isDebugTime()) qDebug()<<"change dir x:"<<lastX;
            }
            // if increase speed
            else if(Util::abs(ax)>Util::abs(lastX))
            {
                lastX=ax;
if(Util::isDebugTime()) qDebug()<<"increase x:"<<lastX;
            }
            lastY=0;
        }
        // if pacman is in position to change Y
        if(ay) if(((((int)pacX)-map->width()/2)%map->width()<2))
        {
            // if change direction
            if(Util::topInt(ay)!=Util::topInt(lastY))
            {
                lastY=ay;
            }
            // if increase speed
            else if(Util::abs(ay)>Util::abs(lastY))
            {
                lastY=ay;
            }
            lastX=0;
        }
    }
    // if is upon to collision
    if((map->matrix()[x+Util::topInt(lastX)][y+Util::topInt(lastY)])&IMap::TileBlock)
    {
        if(lastX)
        {
            double d=(pacX-(x+Util::topInt(lastX)+0.5)*map->width())/map->width();
            // if distance is minor than one block
            if(Util::abs(d)<1.0)
            {
                // stop in center
                pacX=((int)(pacX/map->width()))*map->width()+map->width()/2.0;
                lastX=0;
            }
        }
        if(lastY)
        {
            double d=(pacY-(y+Util::topInt(lastY)+0.5)*map->height())/map->height();
            // if distance is minor than one block
            if(Util::abs(d)<1.0)
            {
                // stop in center
                pacY=((int)(pacY/map->height()))*map->height()+map->height()/2.0;
                lastY=0;
            }
        }
    }
    // walk
    pacX+=lastX*pacSpeed*(ellap/1000.0);
    pacY+=lastY*pacSpeed*(ellap/1000.0);
    // set direction for the light
    if(lastX)
    {
        lastDirX=Util::topInt(lastX);
        lastDirY=0;
    }
    else if(lastY)
    {
        lastDirY=Util::topInt(lastY);
        lastDirX=0;
    }
    // eat the food
    if(map->matrix()[x][y]==IMap::TileFood) map->matrix()[x][y]=IMap::TileNone;
    // eat the power
    if(map->matrix()[x][y]==IMap::TilePower)
    {
        map->matrix()[x][y]=IMap::TileNone;
        // scare all ghost
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

int PacMan::getDirectionX()
{
    return lastX;
}

int PacMan::getDirectionY()
{
    return lastY;
}

int PacMan::lastDirectionX()
{
    return lastDirX;
}

int PacMan::lastDirectionY()
{
    return lastDirY;
}
