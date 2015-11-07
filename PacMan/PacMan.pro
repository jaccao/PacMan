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

TEMPLATE = app

CONFIG += c++11

QT += serialport

SOURCES += \
    main.cpp \
    arduinocontroller.cpp \
    fakecontroller.cpp \
    game.cpp \
    keyboardcontroller.cpp \
    map.cpp \
    pacman.cpp \
    ghost.cpp \
    distanceartificialintelligence.cpp \
    fakeartificialintelligence.cpp

LIBS += -lglutk32
LIBS += -lopengl32
LIBS += -lglu32

HEADERS += \
    icontroller.h \
    arduinocontroller.h \
    fakecontroller.h \
    iglut.h \
    game.h \
    keyboardcontroller.h \
    map.h \
    imap.h \
    ipacman.h \
    pacman.h \
    ighost.h \
    ghost.h \
    iartificialintelligence.h \
    distanceartificialintelligence.h \
    fakeartificialintelligence.h

DEFINES += NO_USE_QT
