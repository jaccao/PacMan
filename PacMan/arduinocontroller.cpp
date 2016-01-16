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

#include "arduinocontroller.h"

ArduinoController::ArduinoController()
{
}

double ArduinoController::analog(const char *value)
{
    double o=Arduino::getDoubleValue(value)/512.0;
    double m=0.05;
    if(Util::abs(o)<m){return(0.0);}
    if(Util::abs(o)>(1.0-m)){return(Util::topInt(o));}
    return((Util::abs(o)-m)/(1.0-2.0*m)*Util::topInt(o));
}

double ArduinoController::analogX()
{
    return analog("analogX");
}

double ArduinoController::analogY()
{
    return analog("analogY");
}

void ArduinoController::display(IGame &game)
{
    (void)game;
}

void ArduinoController::keyboard(IGame &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void ArduinoController::keyboardUp(IGame &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void ArduinoController::idle(IGame &game)
{
    (void)game;
}

int ArduinoController::digitalX()
{
    return((int)(analogX()*1.9));
}

int ArduinoController::digitalY()
{
    return((int)(analogY()*1.9));
}

int ArduinoController::button()
{
    return((int)Arduino::getDoubleValue("button"));
}
