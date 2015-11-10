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

#include "distanceartificialintelligence.h"

DistanceArtificialIntelligence::DistanceArtificialIntelligence()
{

}

void DistanceArtificialIntelligence::display(Game &game)
{
    (void)game;
}

void DistanceArtificialIntelligence::keyboard(Game &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void DistanceArtificialIntelligence::keyboardUp(Game &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

vector< State > DistanceArtificialIntelligence::generateStates(Game& game, vector< Position >& ps_pac,vector< vector< Position > >& vps_ghosts,unsigned int ps)
{
    vector< State > ret;
    vector< Position > gps=vps_ghosts[ps];
    if(ps<vps_ghosts.size()-1)
    {
        vector< State > tmp=generateStates(game,ps_pac,vps_ghosts,ps+1);
        for(unsigned int cs=0;cs<tmp.size();cs++)
        {
            State s1=tmp[cs];
            for(unsigned int c=0;c<gps.size();c++)
            {
                State s2;
                s2.pacman=s1.pacman;
                s2.ghosts=s1.ghosts;
                s2.ghosts.push_back(gps[c]);
                ret.push_back(s2);
            }
        }
    }
    else
    {
        for(unsigned int c=0;c<gps.size();c++)
        {
            for(unsigned int cp=0;cp<ps_pac.size();cp++)
            {
                State s;
                s.pacman=ps_pac[cp];
                s.ghosts.push_back(gps[c]);
                ret.push_back(s);
            }
        }
    }
    return(ret);
}

vector< State > DistanceArtificialIntelligence::generateStates(Game& game)
{
    Position p_pac(game.pacman->X()/game.map->width(),game.pacman->Y()/game.map->height());
    vector< Position > ps_pac=game.map->legalMov(p_pac);
    vector< vector< Position > > vps_ghosts;
    for(unsigned int c=0;c<game.ghosts.size();c++)
    {
        IGhost* g=game.ghosts[c];
        Position p_ghost(g->X()/game.map->width(),g->Y()/game.map->height());
        p_ghost.g=g;
        vps_ghosts.push_back(game.map->legalMov(p_ghost));
    }
    vector< State > ret=generateStates(game,ps_pac,vps_ghosts,0);
    return ret;
}

double DistanceArtificialIntelligence::evalState(Game& game,State& state)
{
    vector< vector< int > > visited;
    visited.resize(game.map->cols(),vector<int>(game.map->rows(),0));
    vector< Position > pg=state.ghosts;
    unsigned int visg=0;
    vector< Position > ps=game.map->legalMov(state.pacman,&visited);
    int steps=0,max_steps=0;
    while(ps.size())
    {
        steps++;
        for(unsigned int i=0;i<ps.size();i++)
        {
            for(unsigned int g=0;g<pg.size();g++)
            {
                if(ps[i].x==pg[g].x) if(ps[i].y==pg[g].y)
                {
                    visg++;
                    if(pg[g].g)
                    {
                        if(pg[g].g->scared())
                        {
                            max_steps-=steps;
                        }
                        else
                        {
                            max_steps+=steps;
                        }
                    }
                    else
                    {
                        max_steps+=steps;
                    }
                }
            }
        }
        if(visg>=pg.size()) break;
        ps=game.map->legalMov(ps,&visited);
    }
    return (double)max_steps/(double)game.ghosts.size();
}

void DistanceArtificialIntelligence::idle(Game &game)
{
    static int ellap=0;
    ellap+=game.ellapsed;
    if(ellap>200)
    {
        ellap=0;
        vector< State > states=generateStates(game);
        double min_eval=99999;
        State state;
        for(unsigned int cs=0;cs<states.size();cs++)
        {
            State s=states[cs];
            double eval=evalState(game,s);
            if(eval<min_eval)
            {
                min_eval=eval;
                state=s;
            }
        }
        for(unsigned int c=0;c<state.ghosts.size();c++)
        {
            Position* pa=&state.ghosts[c];
            if(pa->g)
            {
                IGhost *g=pa->g;
                g->setDirection(pa->directionX()*-1,pa->directionY()*-1);
            }
        }
    }
}
