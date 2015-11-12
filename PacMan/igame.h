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
    virtual int getEllapsed();
    virtual State getState();
    virtual IController *getController();
    virtual IMap *getMap();
    virtual IPacMan *getPacman();
    virtual vector< IGhost* > getGhosts();
    virtual IArtificialIntelligence *getAi();
};

#endif // IGAME_H
