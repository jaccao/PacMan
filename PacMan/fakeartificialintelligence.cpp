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

#include "fakeartificialintelligence.h"

FakeArtificialIntelligence::FakeArtificialIntelligence()
{

}

void FakeArtificialIntelligence::display(Game &game)
{
    (void)game;
}

void FakeArtificialIntelligence::keyboard(Game &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void FakeArtificialIntelligence::keyboardUp(Game &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void FakeArtificialIntelligence::idle(Game &game)
{
    vector< vector< int > > visited;
    vector< Position > pg;
    for(unsigned int g=0;g<game.ghosts.size();g++)
    {
        IGhost* gh=game.ghosts[g];
        pg.push_back(Position(gh->X()/game.map->width(),gh->Y()/game.map->height()));
    }
    pg.resize(game.ghosts.size());
    visited.resize(game.map->cols(),vector<int>(game.map->rows(),0));
    Position p(game.pacman->X()/game.map->width(),game.pacman->Y()/game.map->height());
    vector< Position > ps=game.map->legalMov(p,&visited);
    while (ps.size())
    {
        for(unsigned int i=0;i<ps.size();i++)
        {
            for(unsigned int g=0;g<pg.size();g++)
            {
                if(ps[i].x==pg[g].x) if(ps[i].y==pg[g].y)
                {
                    pg[g]=ps[i];
                }
            }
        }
        ps=game.map->legalMov(ps,&visited);
    }
    for(unsigned int c=0;c<pg.size();c++)
    {
        IGhost *g=game.ghosts.at(c);
        Position* pa=&pg.at(c);
        if(pa->p)
        {
            Position* pp=pg[c].p;
            if(pa->x<pp->x)
            {
                g->setDirection(1,0);
            }
            else if(pa->x>pp->x)
            {
                g->setDirection(-1,0);
            }
            else if(pa->y<pp->y)
            {
                g->setDirection(0,1);
            }
            else if(pa->y>pp->y)
            {
                g->setDirection(0,-1);
            }
        }
    }
}
