#ifndef IGAME_H
#define IGAME_H

#include "icontroller.h"
#include "imap.h"
#include "ipacman.h"
#include "iartificialintelligence.h"

class IGame
{
public:
    enum State{NotStarted,Running,Win,GameOver};
    virtual int getEllapsed()=0;
    virtual State getState()=0;
    virtual IController *getController()=0;
    virtual IMap *getMap()=0;
    virtual IPacMan *getPacman()=0;
    virtual vector< IGhost* > getGhosts()=0;
    virtual IArtificialIntelligence *getAi()=0;
    virtual void stateChanged()=0;
    virtual void setup(int cols,int rows,int width,int height)=0;
    virtual void display()=0;
    virtual void keyboard(unsigned char c,int x,int y)=0;
    virtual void keyboardUp(unsigned char c,int x,int y)=0;
    virtual void idle()=0;
    virtual void displayText(float x, float y, int r, int g, int b, const char *string)=0;
    virtual void reshape(int w, int h);
    virtual bool isFirstPerson();
};

#endif // IGAME_H
