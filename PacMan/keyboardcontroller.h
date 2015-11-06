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

#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include "game.h"

class KeyboardController: public IController
{
private:
    double dAnalogX;
    double dAnalogY;
public:
    KeyboardController();

    // IGlut interface
public:
    void display(Game &game);
    void keyboard(Game &game, unsigned char c, int x, int y);
    void keyboardUp(Game &game, unsigned char c, int x, int y);
    void idle(Game &game);

    // IController interface
public:
    double analogX();
    double analogY();
    int digitalX();
    int digitalY();
};

#endif // KEYBOARDCONTROLLER_H
