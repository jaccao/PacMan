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

void FakeArtificialIntelligence::display(IGame &game)
{
    (void)game;
}

void FakeArtificialIntelligence::keyboard(IGame &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void FakeArtificialIntelligence::keyboardUp(IGame &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void FakeArtificialIntelligence::idle(IGame &game)
{
    double px=game.getPacman()->X();
    double py=game.getPacman()->Y();
    for(unsigned int c=0;c<game.getGhosts().size();c++)
    {
        IGhost *g=game.getGhosts().at(c);
        double gx=g->X();
        double gy=g->Y();
        if(py==gy) py-=0.1;
        double r=(px-gx)/(py-gy);
        if(r>1||r<-1)
        {
            if(px<gx)
            {
                g->setDirection(-1,0);
            }
            else
            {
                g->setDirection(1,0);
            }
        }
        else
        {
            if(py<gy)
            {
                g->setDirection(0,-1);
            }
            else
            {
                g->setDirection(0,1);
            }
        }
    }
}
