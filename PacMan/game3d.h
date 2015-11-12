#ifndef GAME3D_H
#define GAME3D_H

#include <sys/timeb.h>
#include <string.h>

#include "igame.h"
#include "imap.h"
#include "ipacman.h"
#include "ighost.h"
#include "iglut.h"
#include "icontroller.h"
#include "iartificialintelligence.h"

#include "arduinocontroller.h"
#include "fakecontroller.h"
#include "keyboardcontroller.h"
#include "map.h"
#include "pacman.h"
#include "ghost.h"
#include "distanceartificialintelligence.h"

class Game3D: public IGame
{
private:
    vector< IGlut* > gluts;
    struct timeb last;
    Game3D();
private:
    IGame::State state;
    int ellapsed;
    IController *controller;
    IMap *map;
    IPacMan *pacman;
    vector< IGhost* > ghosts;
    IArtificialIntelligence *ai;
private:
    static Game3D &instance();
public:
    static int setup(int argc, char *argv[], int cols, int rows, int width, int height);
    static void display();
    static void keyboard(unsigned char c,int x,int y);
    static void keyboardUp(unsigned char c,int x,int y);
    static void idle();
private:
    void setupImp(int cols,int rows,int width,int height);
    void displayImp();
    void keyboardImp(unsigned char c,int x,int y);
    void keyboardUpImp(unsigned char c,int x,int y);
    void idleImp();
    void displayText(float x, float y, int r, int g, int b, const char *string);
    void positionObserver(float alpha, float beta, int radi);
private:
    /*--- Global variables that determine the viewpoint location ---*/
    int anglealpha;
    int anglebeta;
    int width;
    int height;

    // IGame3D interface
public:
    int getEllapsed();
    State getState();
    IController *getController();
    IMap *getMap();
    IPacMan *getPacman();
    vector<IGhost *> getGhosts();
    IArtificialIntelligence *getAi();
};

#endif // GAME3D_H
