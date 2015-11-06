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

#include "keyboardcontroller.h"

KeyboardController::KeyboardController()
{
    dAnalogX=0;
    dAnalogY=0;
}

void KeyboardController::display(Game &game)
{
    (void)game;
}

void KeyboardController::keyboard(Game &game, unsigned char c, int x, int y)
{
    (void)x;
    (void)y;
    (void)game;
    switch (c)
    {
    case 'a':
        dAnalogX = -1;
        break;
    case 'd':
        dAnalogX = 1;
        break;
    case 's':
        dAnalogY = -1;
        break;
    case 'w':
        dAnalogY = 1;
        break;
    }
}

void KeyboardController::idle(Game &game)
{
    (void)game;
}

double KeyboardController::analogX()
{
    return dAnalogX;
}

double KeyboardController::analogY()
{
    return dAnalogY;
}


void KeyboardController::keyboardUp(Game &game, unsigned char c, int x, int y)
{
    (void)x;
    (void)y;
    (void)game;
    switch (c)
    {
    case 'a':
        dAnalogX = 0;
        break;
    case 'd':
        dAnalogX = 0;
        break;
    case 's':
        dAnalogY = 0;
        break;
    case 'w':
        dAnalogY = 0;
        break;
    }
}


int KeyboardController::digitalX()
{
    return((int)analogX());
}

int KeyboardController::digitalY()
{
    return((int)analogY());
}
