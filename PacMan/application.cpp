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

#include "application.h"

Application::Application()
{
    game=new Game3D(35);
}

Application &Application::instance()
{
    static Application app;
    return app;
}

int Application::setup(int argc, char *argv[], int cols, int rows, int width, int height)
{
    glutInit(&argc, argv);

    instance().game->setup(cols, rows, width, height);

    glutDisplayFunc(Application::display);
    glutKeyboardFunc(Application::keyboard);
    glutKeyboardUpFunc(Application::keyboardUp);
    glutIdleFunc(Application::idle);
    glutReshapeFunc(Application::reshape);

    glutMainLoop();
    return 0;
}

void Application::display()
{
    instance().game->display();
}

void Application::keyboard(unsigned char c, int x, int y)
{
    instance().game->keyboard(c,x,y);
}

void Application::keyboardUp(unsigned char c, int x, int y)
{
    instance().game->keyboardUp(c,x,y);
}

void Application::idle()
{
    instance().game->idle();
}

void Application::reshape(int w, int h)
{
    instance().game->reshape(w,h);
}
