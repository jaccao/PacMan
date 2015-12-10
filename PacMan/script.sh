#!/bin/sh
g++ -c -pipe -O2 -std=c++0x -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o main.o ../PacMan/main.cpp
g++ -c -pipe -O2 -std=c++0x -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o arduinocontroller.o ../PacMan/arduinocontroller.cpp
g++ -c -pipe -O2 -std=c++0x -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o fakecontroller.o ../PacMan/fakecontroller.cpp
g++ -c -pipe -O2 -std=c++0x -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o game.o ../PacMan/game.cpp
g++ -c -pipe -O2 -std=c++0x -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o keyboardcontroller.o ../PacMan/keyboardcontroller.cpp
g++ -c -pipe -O2 -std=c++0x -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o map.o ../PacMan/map.cpp
g++ -c -pipe -O2 -std=c++0x -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o pacman.o ../PacMan/pacman.cpp
g++ -c -pipe -O2 -std=c++0x -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o ghost.o ../PacMan/ghost.cpp
g++ -c -pipe -O2 -std=c++0x -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o distanceartificialintelligence.o ../PacMan/distanceartificialintelligence.cpp
g++ -c -pipe -O2 -std=c++0x -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o fakeartificialintelligence.o ../PacMan/fakeartificialintelligence.cpp
g++ -c -pipe -O2 -std=c++0x -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o game3d.o ../PacMan/game3d.cpp
g++ -c -pipe -O2 -std=c++0x -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o map3d.o ../PacMan/map3d.cpp
g++ -c -pipe -O2 -std=c++0x -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o pacman3d.o ../PacMan/pacman3d.cpp
g++ -c -pipe -O2 -std=c++0x -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o ghost3d.o ../PacMan/ghost3d.cpp
g++ -c -pipe -O2 -std=c++0x -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o position.o ../PacMan/position.cpp
g++ -c -pipe -O2 -std=c++0x -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o state.o ../PacMan/state.cpp
g++ -c -pipe -O2 -std=c++0x -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o node.o ../PacMan/node.cpp
g++ -c -pipe -O2 -std=c++0x -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o minimaxartificialintelligence.o ../PacMan/minimaxartificialintelligence.cpp
g++ -c -pipe -O2 -std=c++0x -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o aleatoryartificialintelligence.o ../PacMan/aleatoryartificialintelligence.cpp
gcc -c -pipe -O2 -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o SOIL.o ../PacMan/soil/SOIL.c
gcc -c -pipe -O2 -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o image_helper.o ../PacMan/soil/image_helper.c
gcc -c -pipe -O2 -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o stb_image_aug.o ../PacMan/soil/stb_image_aug.c
gcc -c -pipe -O2 -Wall -W -fPIC -DNO_USE_QT -I../PacMan -I. -o image_DXT.o ../PacMan/soil/image_DXT.c
g++ -Wl,-O1 -o PacMan main.o arduinocontroller.o fakecontroller.o game.o keyboardcontroller.o map.o pacman.o ghost.o distanceartificialintelligence.o fakeartificialintelligence.o game3d.o map3d.o pacman3d.o ghost3d.o position.o state.o node.o minimaxartificialintelligence.o aleatoryartificialintelligence.o SOIL.o image_helper.o stb_image_aug.o image_DXT.o   -lglut -lGL -lGLU 
