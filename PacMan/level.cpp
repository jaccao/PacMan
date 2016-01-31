#include "level.h"

Level::Level(int cols, int rows, int ghosts, IArtificialIntelligence *ai)
{
    this->cols=cols;
    this->rows=rows;
    this->ai=ai;
    this->ghosts=ghosts;
    this->height=32;
    this->width=32;
}

