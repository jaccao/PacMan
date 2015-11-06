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

#include "game.h"

#define V_COLUMNS 31
#define V_ROWS 19
#define V_WIDTH 32
#define V_HEIGHT 32

int main(int argc,char *argv[])
{
    Game::setup(V_COLUMNS,V_ROWS,V_WIDTH,V_HEIGHT);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(64,64);
    glutInitWindowSize(V_WIDTH*V_COLUMNS, V_HEIGHT*V_ROWS);
    glutCreateWindow("PacMan");

    glutDisplayFunc(Game::display);
    glutKeyboardFunc(Game::keyboard);
    glutKeyboardUpFunc(Game::keyboardUp);
    glutIdleFunc(Game::idle);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,V_WIDTH*V_COLUMNS-1,0,V_HEIGHT*V_ROWS-1);

    glutMainLoop();
    return 0;
}
