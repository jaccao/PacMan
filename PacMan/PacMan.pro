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
CONFIG += console

CONFIG += c++11
#CONFIG -= qt

#Comment the two follow lines to skip Arduino dependence
DEFINES += NO_USE_QT
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
    fakeartificialintelligence.cpp \
    game3d.cpp \
    map3d.cpp \
    pacman3d.cpp \
    ghost3d.cpp \
    position.cpp \
    state.cpp \
    node.cpp \
    minimaxartificialintelligence.cpp \
    aleatoryartificialintelligence.cpp \
    soil/SOIL.c \
    soil/image_helper.c \
    soil/stb_image_aug.c \
    soil/image_DXT.c \
    arduino.cpp \
    util.cpp \
    application.cpp \
    glWindowPos.cpp \
    level.cpp \
    sqlite3.c \
    sql.cpp \
    heuristicfunction.cpp

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
    fakeartificialintelligence.h \
    igame.h \
    game3d.h \
    map3d.h \
    pacman3d.h \
    ghost3d.h \
    position.h \
    state.h \
    node.h \
    minimaxartificialintelligence.h \
    aleatoryartificialintelligence.h \
    soil/SOIL.h \
    soil/image_helper.h \
    soil/stb_image_aug.h \
    soil/image_DXT.h \
    soil/stbi_DDS_aug.h \
    soil/stbi_DDS_aug_c.h \
    arduino.h \
    util.h \
    application.h \
    glWindowPos.h \
    level.h \
    sqlite3.h \
    sqlite3ext.h \
    sql.h \
    heuristicfunction.h

DISTFILES += \
    ../arduino.ini
