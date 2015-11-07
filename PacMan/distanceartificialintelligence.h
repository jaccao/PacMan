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

#ifndef DISTANCEARTIFICIALINTELLIGENCE_H
#define DISTANCEARTIFICIALINTELLIGENCE_H

#include "game.h"

class DistanceArtificialIntelligence: public IArtificialIntelligence
{
public:
    DistanceArtificialIntelligence();

    // IGlut interface
public:
    void display(Game &game);
    void keyboard(Game &game, unsigned char c, int x, int y);
    void keyboardUp(Game &game, unsigned char c, int x, int y);
    void idle(Game &game);
private:
    vector<State> generateStates(Game &game);
    vector<State> generateStates(Game &game, vector<Position> &ps_pac, vector<vector<Position> > &vps_ghosts, unsigned int ps);
    double evalState(Game &game, State &state);
};

#endif // FAKEARTIFICIALINTELLIGENCE_H