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

#include "map3d.h"

Map3D::Map3D()
{
}

void Map3D::display(IGame &game)
{
    (void)game;
    int i,j;

    for(i=0;i<c;i++)
        for(j=0;j<r;j++)
        {
            glPushMatrix();
            switch (m[i][j]) {
            case IMap::TileBlock:
                glColor3f(0.8,0.8,0.8);
                glTranslated((i+0.5)*w,(j+0.5)*h,8.0);
                glScaled(w,h,16.0);
                break;
            default:
                glColor3f(0.0,0.0,0.0);
                glTranslated((i+0.5)*w,(j+0.5)*h,-0.5);
                glScaled(w,h,1.0);
                break;
            }
            glutSolidCube(1.0);
            glPopMatrix();

            if(m[i][j]==IMap::TileFood)
            {
                glPushMatrix();
                glColor3f(0.8,0.0,0.0);
                glTranslated((i+0.5)*w,(j+0.5)*h,12.0);
                glutSolidCube(4.0);
                glPopMatrix();
            }
            if(m[i][j]==IMap::TilePower)
            {
                glPushMatrix();
                glColor3f(1,1,1);
                glTranslated((i+0.5)*w,(j+0.5)*h,12.0);
                glutSolidCube(8.0);
                glPopMatrix();
            }
        }

}
