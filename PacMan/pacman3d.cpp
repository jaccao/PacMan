/*
# Copyright (C) 2015, 2016
# Luiz Fernando Jaccao <luizfernandojaccao@gmail.com>
# William Malheiros Evangelista <williammalheiros_2@hotmail.com>
# Jose David Oliveira Nunes <david.nunes.co@hotmail.com>
# This file is part of PacMan3D Project - UdL/FACENS Sem Fronteira.
#
# PacMan3D is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# PacMan3D is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
*/

#include "pacman3d.h"

PacMan3D::PacMan3D()
{

}

void PacMan3D::display(IGame &game)
{
    (void)game;
    glColor3f(0.8,0.8,0.0);

    glPushMatrix();

    glTranslated(pacX,pacY,12.0);
    glutSolidSphere(12,32,32);

    glPopMatrix();

}
