#ifndef LEVEL_H
#define LEVEL_H

#include "iartificialintelligence.h"

class Level
{
public:
    Level(int cols,int rows,int ghosts,IArtificialIntelligence* ai);
    int cols;
    int rows;
    int ghosts;
    int width;
    int height;
    IArtificialIntelligence* ai;
};

#endif // LEVEL_H
