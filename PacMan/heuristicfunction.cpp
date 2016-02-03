#include "heuristicfunction.h"

HeuristicFunction::HeuristicFunction(IMap *map)
{
    map_game = map;
    init();
}

HeuristicFunction::init()
{
    int countnode = 0;

    for (int i = 1; i < map_game->cols() - 1; i++)
    {
        for (int j = 1; j < map_game->rows() - 1; j++)
        {
            if(map_game->matrix()[i][j] == IMap::TilePower
                || map_game->matrix()[i][j] == IMap::TileFood
                || map_game->matrix()[i][j] == IMap::TileNone)
            {
                vector<Position> vector_pos_atual;
                vector_pos_atual.push_back(Position(i, j));
                vector<Position> nextPositions = map_game->legalMov(vector_pos_atual);

                for (int k = 0; k < nextPositions.size(); k++)
                {
                    Position pos = nextPositions.at(k);

                    pair<int,int> p_pos(pos.x, pos.y);
                    if(mapeamento.find(p_pos) == mapeamento.end())//checa se existe, se nao existir adiciona
                    {
                        mapeamento[p_pos] = countnode++;
                    }
                }
            }
        }
    }
}

int HeuristicFunction::findWay(Position& p, Position& g, vector<Position> &all_ghosts)
{
    int dimension = map_game->cols() * map_game->rows();
    int distance;
    priority_queue<pair<int, pair<int, int>>> q; //decrescente order
    int distancia[dimension];
    pair<int,int> padre[dimension];
    bool visto[dimension];
    //vector < vector <bool> > visto2;
    pair<int,int> ghost(p.x,p.y);
    pair<int,int> pacman(g.x, g.y);

    //Initialize arrays
    for (int i = 0; i < dimension/2; i++)
    {
        distancia[i] = 999999;
        padre[i] = pair<int,int>(0,0);
        visto[i] = false;
    }
    //m[3][1] = 3;
    //m[1][0] = 3;
    //m[0][4] = 4;
/*
 * vector< vector< vector < pair<int, int> > > > legalMovPos;
 * legalMovPos.resize(cols,vector< vector< pair<int, int> > >(rows,vector< pair<int, int> >());
 * for()
 * {
 *      pos=map->legalMov(pos);
 *      for()
 *        legalMovPos[x][y].push_back(pair<int,int>(pos[i].x,pos[i].y));
 * if(visto[x][y]=true;
 * }
 *
 *
 */
    int ini = mapeamento[pacman];
    distancia[ini] = 0;
    q.push(pair<int, pair<int, int>>(distancia[ini],pacman));
    bool achou = false;

    while(!q.empty() && !achou)
    {
        //remove from queue
        pair<int, pair<int, int>> value = q.top();
        q.pop();
        pair<int, int> name = value.second;
        int indice = mapeamento[name];
        //mark as seen
        visto[indice] = true;

        vector<Position> vector_pos_atual;
        vector_pos_atual.push_back(Position(name.first, name.second));
        //find next positions accessible
        vector<Position> listneighbors = map_game->legalMov(vector_pos_atual);
        //iterate all neighbors accessible
        for (int k = 0; k < listneighbors.size(); k++)
        {
            Position pos = listneighbors.at(k);

            pair<int,int> nameChild(pos.x, pos.y);
            distance = 1;
            int indiceChild = mapeamento[nameChild];

            if(!visto[indiceChild] && distancia[indiceChild] > (distancia[indice] + distance))
            {
                /*if(m[nameChild.first][nameChild.second] == 3) //ghost
                {
                    distance += 1000;
                }
                if(map_game->matrix()[nameChild.first][nameChild.second] == IMap::TileFood) //food
                {
                    distance -= 10;
                }*/
                distancia[indiceChild] = distancia[indice] + distance;

                //printf("%i %i %i\n",nameChild.first, nameChild.second, distancia[indiceChild]);
                //insert the father's node
                padre[indiceChild] = name;
                //insert in queue new position with distance negative beacause the queue orders in decreasing order
                q.push(pair<int, pair<int, int>>(-distancia[indiceChild],nameChild));

                if(nameChild.first == ghost.first && ghost.second == nameChild.second)
                    achou = true;
            }
        }
    }


    /*int indice = mapeamento[ghost];
    pair<int,int> dad = padre[indice];
    //qDebug() << "(" << ghost.first << "," << ghost.second << ")";
    while(dad != pacman)
    {
        //qDebug() << "(" << dad.first << "," << dad.second << ")";
        indice = mapeamento[dad];
        dad = padre[indice];

    }*/
    //qDebug() << "(" << dad.first << "," << dad.second << ")";

    return distancia[mapeamento[ghost]];
}
