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

#include "map.h"

int Map::sumArea(int px,int py)
{
    int sum=0;
    for(int x=px-1;x<px+2;x++)
        for(int y=py-1;y<py+2;y++)
        {
            if(x>=0) if(x<c) if(y>=0) if(y<r)
            {
                sum+=m[x][y];
            }
        }
    return sum;
}

Map::Map()
{
}

void Map::setup(Game &game, int cols, int rows, int width, int height)
{
    this->c=cols;
    this->r=rows;
    this->w=width;
    this->h=height;
    m.resize(cols,vector<int>(rows,0));
    srand(time(NULL));
    mapgen();
    game.pacman->X((cols/2+0.5)*width);
    game.pacman->Y(1.5*height);
//    game.pacman->Y((rows/2-4+0.5)*height);
    game.pacman->speed(128);
    unsigned int c=0;
    for(int j=-2;j<=0;j++)
        for(int i=-2;i<=2;i++)
            if(c<game.ghosts.size())
            {
                IGhost *g=game.ghosts.at(c);
                g->speed((96-32)+rand()%32);
                g->X((cols/2+i+0.5)*width);
                g->Y((rows/2+j+0.5)*height);
                c++;
            }
}

void Map::display(Game &game)
{
    (void)game;
    int i,j;

    for(i=0;i<c;i++)
        for(j=0;j<r;j++)
        {
            switch (m[i][j]) {
            case 1:
                glColor3f(0.8,0.8,0.8);
                break;
            default:
                glColor3f(0.0,0.0,0.0);
                break;
            }
            glRecti(i*w,j*h,(i+1)*w,(j+1)*h);
            if(m[i][j]==2)
            {
                glColor3f(0.8,0.0,0.0);
                glRecti(i*w+14,j*h+14,(i+1)*w-14,(j+1)*h-14);
            }
        }
}

void Map::keyboard(Game &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)x;
    (void)y;
    if(c==' ') mapgen();
}

void Map::keyboardUp(Game &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void Map::idle(Game &game)
{
    (void)game;
}

void Map::mapgen()
{
    // clear
    for(int i=0;i<c;i++)
        for(int j=0;j<r;j++)
        {
            if(i==0||j==0||i==c-1||j==r-1) m[i][j]=1;
            else  m[i][j]=0;
        }
    // DO: adjust the box
    // pandora box
    for(int i=c/2-3;i<=c/2;i++)
        for(int j=r/2-3;j<r/2+2;j++)
        {
            m[i][j]=1;
        }
    // random wall
    for(int t=0;t<1000;t++)
    {
        // get a random position
        int px=(rand()%(c/4))*2;
        int py=(rand()%(r/2))*2;
        // check if its ok to start
        if(sumArea(px,py)==0)
        {
            // set first pixel
            m[px][py]=1;
            int tries=2000;
            // random to continue
            while ((rand()%100<97))
            {
                tries--;
                if(!tries)
                {
                    m[px][py]=2;
                    return;
                }
                int tx=px;
                int ty=py;
                // go to a new position
                switch(rand()%4)
                {
                case 0:
                    ty-=1;
                    break;
                case 1:
                    tx+=1;
                    break;
                case 2:
                    ty+=1;
                    break;
                default:
                    tx-=1;
                }
                // if not in outside continue
                if(tx>=0) if(tx<=c/2) if(ty>=0) if(ty<r)
                {
                    int tmax=1;
                    if(px%2==0) if(py%2==0) tmax=2;
                    // check new position
                    if(sumArea(tx,ty)<=tmax)
                    {
                        // set pixel
                        px=tx;
                        py=ty;
                        m[px][py]=1;
                    }
                }
            }
        }
    }
    // fill corner
    for(int i=0;i<c;i++)
        for(int j=0;j<r;j++)
        {
            if(j%2==0&&i%2==0) m[i][j]=1;
        }
    // food
    for(int i=0;i<=c/2;i++)
        for(int j=0;j<r;j++)
        {
            if(m[i][j]==0) m[i][j]=2;
        }
    // open pandora box
    for(int i=c/2-2;i<=c/2;i++)
        for(int j=r/2-2;j<r/2+1;j++)
        {
            m[i][j]=0;
        }
    m[c/2][r/2-3]=5;
    // mirror matrix
    for(int i=0;i<=c/2;i++)
        for(int j=0;j<r;j++)
        {
            m[c-i-1][j]=m[i][j];
        }
}

vector<vector<int> > &Map::matrix()
{
    return(m);
}

int Map::cols()
{
    return c;
}

int Map::rows()
{
    return r;
}

int Map::width()
{
    return w;
}

int Map::height()
{
    return h;
}
