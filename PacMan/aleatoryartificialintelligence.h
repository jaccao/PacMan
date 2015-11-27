#ifndef ALEATORYARTIFICIALINTELLIGENCE_H
#define ALEATORYARTIFICIALINTELLIGENCE_H
#include <cstdlib>
#include "igame.h"

class AleatoryArtificialIntelligence: public IArtificialIntelligence
{
public:
    AleatoryArtificialIntelligence();
    // IGlut interface
public:
    void display(IGame &game);
    void keyboard(IGame &game, unsigned char c, int x, int y);
    void keyboardUp(IGame &game, unsigned char c, int x, int y);
    void idle(IGame &game);

private:

};

#endif // ALEATORYARTIFICIALINTELLIGENCE_H
