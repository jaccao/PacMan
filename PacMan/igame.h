#ifndef IGAME_H
#define IGAME_H

#include "icontroller.h"
#include "imap.h"
#include "ipacman.h"
#include "iartificialintelligence.h"

class IGame
{
public:
    enum State{Running,Win,GameOver};
    virtual int getEllapsed()=0;
    virtual State getState()=0;
    virtual IController *getController()=0;
    virtual IMap *getMap()=0;
    virtual IPacMan *getPacman()=0;
    virtual vector< IGhost* > getGhosts()=0;
    virtual IArtificialIntelligence *getAi()=0;
    virtual void stateChanged()=0;
};

#endif // IGAME_H
