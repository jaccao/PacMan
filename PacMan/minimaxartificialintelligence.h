#ifndef MINIMAXARTIFICIALINTELLIGENCE_H
#define MINIMAXARTIFICIALINTELLIGENCE_H

#include "igame.h"
#include "node.h"
#include "imap.h"
class MiniMaxArtificialIntelligence: public IArtificialIntelligence
{
public:
    MiniMaxArtificialIntelligence(void);

    // IGlut interface
public:
    void display(IGame &game);
    void keyboard(IGame &game, unsigned char c, int x, int y);
    void keyboardUp(IGame &game, unsigned char c, int x, int y);
    void idle(IGame &game);
    State bestState;
private:
    Node tree;
    void createTree(IGame &game);
    Position getOneGhost(IGame& game, int ghostNumber);
    float minimax(Node &no,int depth,bool maximizingPlayer);
    double evalState(IGame& game,State& state);
};

#endif // MINIMAXARTIFICIALINTELLIGENCE_H
