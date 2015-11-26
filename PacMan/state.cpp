#include "state.h"

State::State()
{
}

State::State(Position pacman,vector< Position > ghosts)
{
    this->pacman=pacman;
    this->ghosts=ghosts;
}
