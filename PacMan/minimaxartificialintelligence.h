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
    float minimaxAlfaBeta(Node &no,int depth, float alpha, float beta, bool maximizingPlayer);
    double evalState(IGame& game,State& state);
    void geraStates(IGame &game, Position pacman, State &move, vector<Position> all_ghosts, int number_of_ghost, int total_of_ghost);
};

#endif // MINIMAXARTIFICIALINTELLIGENCE_H
