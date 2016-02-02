#ifndef HEURISTICFUNCTION_H
#define HEURISTICFUNCTION_H

#include <map>
#include <queue>
#include <tuple>

#include "imap.h"

using namespace std;

class HeuristicFunction
{
    IMap * map_game;
    //map<pair<int, int>,  vector<Position>> neighbors2;
    map< pair<int, int>, int> mapeamento;

public:
    HeuristicFunction(IMap *map);
    int findWay(Position &p, Position &g, vector<Position> &all_ghosts);

private:
    init();
};

#endif // HEURISTICFUNCTION_H
