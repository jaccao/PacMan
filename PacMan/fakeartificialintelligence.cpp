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
    double px=game.pacman->X();
    double py=game.pacman->Y();
    for(unsigned int c=0;c<game.ghosts.size();c++)
    {
        IGhost *g=game.ghosts.at(c);
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
