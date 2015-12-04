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
    texUp=SOIL_load_OGL_texture("../pacmanUp.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texDown=SOIL_load_OGL_texture("../pacmanDown.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texLeft=SOIL_load_OGL_texture("../pacmanLeft.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texRight=SOIL_load_OGL_texture("../pacmanRight.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texLast=texDown;
    quadratic = gluNewQuadric();
    if(!quadratic) exit(2);
    gluQuadricNormals(quadratic, GLU_SMOOTH);
    gluQuadricTexture(quadratic, GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}

void PacMan3D::display(IGame &game)
{
    (void)game;
    glColor3f(1.0,1.0,1.0);

    glDisable(GL_LIGHTING);
    glPushMatrix();

    if(lastX==1)
    {
        texLast=texRight;
    }
    else if(lastY==1)
    {
        texLast=texUp;
    }
    else if(lastX==-1)
    {
        texLast=texLeft;
    }
    else if(lastY==-1)
    {
        texLast=texDown;
    }

    glBindTexture(GL_TEXTURE_2D, texLast);
    glTranslated(pacX,pacY,12.0);

    gluSphere(quadratic, 12.0f, 8, 8);

    glPopMatrix();
    glEnable(GL_LIGHTING);

}
