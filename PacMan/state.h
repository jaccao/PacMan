#ifndef STATE_H
#define STATE_H

#include <vector>
using std::vector;

#include "position.h"

class State
{
public:
    Position pacman;
    vector< Position > ghosts;
    State();
    State(Position pacman,vector< Position > ghosts);
};

#endif // STATE_H
