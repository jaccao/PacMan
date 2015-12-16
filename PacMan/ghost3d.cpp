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
    tex = SOIL_load_OGL_texture("../ghost.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    if(!tex) exit(1);
    quadratic = gluNewQuadric();
    if(!quadratic) exit(2);
    gluQuadricNormals(quadratic, GLU_SMOOTH);
    gluQuadricTexture(quadratic, GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}

void Ghost3D::display(IGame &game)
{
    (void)game;
    GLfloat colorGray[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat colorWhite[] = {1.0, 1.0, 1.0, 1.0};
    if(scared())
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,colorGray);
    else
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,colorWhite);

    glPushMatrix();

    glTranslated(ghostX,ghostY,12.0);

    glBindTexture(GL_TEXTURE_2D, tex);
    glScaled(12.0,12.0,20.0);
    gluSphere(quadratic, 1.0, 8, 8);

    glPopMatrix();

}
