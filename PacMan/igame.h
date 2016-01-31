#ifndef IGAME_H
#define IGAME_H

#include "icontroller.h"
#include "imap.h"
#include "ipacman.h"
#include "iartificialintelligence.h"

class IGame
{
public:
    enum State{NotStarted,Running,Win,GameOver,Reset,Start};
    virtual int getEllapsed()=0;
    virtual State getState()=0;
    virtual IController *getController()=0;
    virtual IMap *getMap()=0;
    virtual IPacMan *getPacman()=0;
    virtual vector< IGhost* > getGhosts()=0;
    virtual IArtificialIntelligence *getAi()=0;
    virtual void stateChanged()=0;
    virtual void setup()=0;
    virtual void display()=0;
    virtual void keyboard(unsigned char c,int x,int y)=0;
    virtual void keyboardUp(unsigned char c,int x,int y)=0;
    virtual void idle()=0;
    virtual void displayText(float x, float y, float r, float g, float b, const char *string)=0;
    virtual void reshape(int w, int h)=0;
    virtual bool isFirstPerson()=0;
    virtual int addScore(int s)=0;
};

#endif // IGAME_H
