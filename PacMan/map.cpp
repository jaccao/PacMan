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

void Map::setup(IGame &game, int cols, int rows, int width, int height)
{
    this->c=cols;
    this->r=rows;
    this->w=width;
    this->h=height;
    m.resize(cols,vector<int>(rows,0));
    srand(time(NULL));
    mapgen();
    game.getPacman()->X((cols/2+0.5)*width);
    game.getPacman()->Y(1.5*height);
    game.getPacman()->speed(96);
    unsigned int c=0;
    for(int j=-2;j<=0;j++)
        for(int i=-2;i<=2;i++)
            if(c<game.getGhosts().size())
            {
                IGhost *g=game.getGhosts().at(c);
                g->speed(96);
                g->X((cols/2+i+0.5)*width);
                g->Y((rows/2+j+0.5)*height);
                c++;
            }
}

void Map::display(IGame &game)
{
    (void)game;
    int i,j;

    for(i=0;i<c;i++)
        for(j=0;j<r;j++)
        {
            switch (m[i][j]) {
            case IMap::TileBlock:
                glColor3f(0.8,0.8,0.8);
                break;
            default:
                glColor3f(0.0,0.0,0.0);
                break;
            }
            glRecti(i*w,j*h,(i+1)*w,(j+1)*h);
            if(m[i][j]==IMap::TileFood)
            {
                glColor3f(0.8,0.0,0.0);
                glRecti(i*w+14,j*h+14,(i+1)*w-14,(j+1)*h-14);
            }
            if(m[i][j]==IMap::TilePower)
            {
                glColor3f(1,1,1);
                glRecti(i*w+10,j*h+10,(i+1)*w-10,(j+1)*h-10);
            }
        }
}

void Map::keyboard(IGame &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)x;
    (void)y;
    if(c==' ') {
        this->setup(game,this->cols(),this->rows(),this->width(),this->height());
    }
}

void Map::keyboardUp(IGame &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void Map::idle(IGame &game)
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
            else  m[i][j]=IMap::TileNone;
        }
    // DO: adjust the box
    // pandora box
    for(int i=c/2-3;i<=c/2;i++)
        for(int j=r/2-3;j<r/2+2;j++)
        {
            m[i][j]=IMap::TileBlock;
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
            m[px][py]=IMap::TileBlock;
            int tries=2000;
            // random to continue
            while ((rand()%100<97))
            {
                tries--;
                if(!tries)
                {
                    m[px][py]=IMap::TileDebug;
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
                        m[px][py]=IMap::TileBlock;
                    }
                }
            }
        }
    }
    // fill corner
    for(int i=0;i<c;i++)
        for(int j=0;j<r;j++)
        {
            if(j%2==0&&i%2==0) m[i][j]=IMap::TileBlock;
        }
    // food
    for(int i=0;i<=c/2;i++)
        for(int j=0;j<r;j++)
        {
            if(m[i][j]==0) m[i][j]=IMap::TileFood;
        }
    // power
    m[1][1]=IMap::TilePower;
    // open pandora box
    for(int i=c/2-2;i<=c/2;i++)
        for(int j=r/2-2;j<r/2+1;j++)
        {
            m[i][j]=IMap::TileNone;
        }
    m[c/2][r/2-3]=IMap::TileGate;
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

vector<Position> Map::legalMov(Position &p,vector< vector< int > >* visited)
{
    vector< Position > ret;
    if(p.x>0){
        if(!(m[p.x-1][p.y]==IMap::TileBlock)){
            if(visited){
                if(!((*visited)[p.x-1][p.y]==IMap::TileBlock)) ret.push_back(Position(p,p.x-1,p.y));
            }else{
                ret.push_back(Position(p,p.x-1,p.y));
            }
        }
    }
    if(p.y>0){
        if(!(m[p.x][p.y-1]==IMap::TileBlock)){
            if(visited){
                if(!((*visited)[p.x][p.y-1]==IMap::TileBlock)) ret.push_back(Position(p,p.x,p.y-1));
            }else{
                ret.push_back(Position(p,p.x,p.y-1));
            }
        }
    }
    if(p.x<c-1){
        if(!(m[p.x+1][p.y]==IMap::TileBlock)){
            if(visited){
                if(!((*visited)[p.x+1][p.y]==IMap::TileBlock)) ret.push_back(Position(p,p.x+1,p.y));
            }else{
                ret.push_back(Position(p,p.x+1,p.y));
            }
        }
    }
    if(p.y<r-1){
        if(!(m[p.x][p.y+1]==IMap::TileBlock)){
            if(visited){
                if(!((*visited)[p.x][p.y+1]==IMap::TileBlock)) ret.push_back(Position(p,p.x,p.y+1));
            }else{
                ret.push_back(Position(p,p.x,p.y+1));
            }
        }
    }
    if(visited)
        for(unsigned int i=0;i<ret.size();i++)
            (*visited)[ret.at(i).x][ret.at(i).y]=IMap::TileBlock;
    return ret;
}


vector<Position> Map::legalMov(vector<Position> &p, vector<vector<int> > *visited)
{
    vector< Position > ret;
    for(unsigned int i=0;i<p.size();i++)
    {
        vector<Position> n=legalMov(p.at(i),visited);
        ret.insert(ret.end(), n.begin(), n.end());
    }
    return ret;
}

int Map::random(int nmax)
{
    return rand()%nmax;
}
