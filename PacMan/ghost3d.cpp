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

#include "ghost3d.h"

Ghost3D::Ghost3D()
{
    lastX=0;
    lastY=0;
    analogX=0;
    analogY=0;
    isScared=false;
    scaredTime=0;
}

void Ghost3D::display(IGame &game)
{
    (void)game;
    if(scared())
        glColor3f(0.8,0.8,0.8);
    else
        glColor3f(0.0,0.0,0.8);
    glPushMatrix();

    glTranslated(ghostX,ghostY,16.0);
    glScaled(16.0,16.0,16.0);
    glutSolidTetrahedron();

    glPopMatrix();
}
