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

#ifndef IGHOST_H
#define IGHOST_H

#include "iglut.h"

class IGhost: public IGlut
{
public:
    virtual double X(double x=-1)=0;
    virtual double Y(double y=-1)=0;
    virtual bool scared(int s=-1)=0;
    virtual double speed(double s=-1)=0;
    virtual void setDirection(double x,double y)=0;
    virtual double getDirectionX()=0;
    virtual double getDirectionY()=0;
};

#endif // IGHOST_H
