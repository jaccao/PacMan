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

#ifndef APPLICATION_H
#define APPLICATION_H

#include "game3d.h"

class Application
{
private:
    IGame* game;
    Application();
    static Application &instance();
public:
    static int setup(int argc, char *argv[], int cols, int rows, int width, int height);
    static void display();
    static void keyboard(unsigned char c,int x,int y);
    static void keyboardUp(unsigned char c,int x,int y);
    static void idle();
};

#endif // APPLICATION_H
