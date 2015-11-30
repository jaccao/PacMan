#include "minimaxartificialintelligence.h"
#include "node.h"
#include "imap.h"
MiniMaxArtificialIntelligence::MiniMaxArtificialIntelligence(void)
{

}

void MiniMaxArtificialIntelligence::display(IGame &game)
{
    (void)game;
}

void MiniMaxArtificialIntelligence::keyboard(IGame &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void MiniMaxArtificialIntelligence::keyboardUp(IGame &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void MiniMaxArtificialIntelligence::createTree2(IGame &game)
{
    tree = Node(0);

    vector<Position> all_ghosts;
    Position p_pac(game.getPacman()->X()/game.getMap()->width(),game.getPacman()->Y()/game.getMap()->height());

    for (int var = 0; var < game.getGhosts().size(); var++)
    {
        IGhost* g = game.getGhosts()[var];
        Position p_ghost(g->X()/game.getMap()->width(),g->Y()/game.getMap()->height());
        p_ghost.g=g;
        all_ghosts.push_back(p_ghost);
    }

    State inicial(p_pac, all_ghosts);

    geraStates(game, p_pac, inicial, all_ghosts, 0, all_ghosts.size());
}

void MiniMaxArtificialIntelligence::geraStates(IGame &game, Position pacman, State &move, vector<Position> all_ghosts, int number_of_ghost, int total_of_ghost)
{
    if(number_of_ghost == total_of_ghost)
    {
        Node childGhostValue;
        childGhostValue.atualState = move;
        childGhostValue.data =  -evalState(game,move);
        tree.insert(childGhostValue);
        return ;
    }

    vector< Position > ghostPositions = game.getMap()->legalMov(all_ghosts[number_of_ghost]);// retorna proxima position valida de um fantasma 0

    for (unsigned int j = 0; j < ghostPositions.size(); j++)
    {
        Position ghost = ghostPositions[j];

        State new_state = move;
        new_state.ghosts[number_of_ghost] = ghost;

//        State s = geraStates(game, pacman, new_state, all_ghosts, number_of_ghost+1, total_of_ghost);
        geraStates(game, pacman, new_state, all_ghosts, number_of_ghost+1, total_of_ghost);

        /*Node childGhostValue;
        childGhostValue.atualState = s;
        childGhostValue.data =  evalState(game,s);
        tree.insert(childGhostValue);*/
    }

}

void MiniMaxArtificialIntelligence::createTree(IGame& game)
{
    tree = Node(0);
    vector< vector< int > > visited;
    visited.resize(game.getMap()->cols(),vector<int>(game.getMap()->rows(),0));
    IMap *map = game.getMap();
    vector< Position > pg;
    pg.push_back(getOneGhost(game,0));// adicionando apenas o ghost 0 na lista

    Position p_pac(game.getPacman()->X()/game.getMap()->width(),game.getPacman()->Y()/game.getMap()->height());
    vector< Position > ps=game.getMap()->legalMov(p_pac);
    for(unsigned int i=0;i<ps.size();i++)
    {
        State novoStateAntecipa(ps[i],pg);
        Position possiblePacmanPos = ps[i];
        Node child;
        if(map->matrix()[possiblePacmanPos.x][possiblePacmanPos.y]==IMap::TileFood){
            child.data = 100.0; //se tem comida Movimento + 100 se não pacman -50
        }
        else
            child.data = -50.0;
        child.atualState=novoStateAntecipa;
        //            for(unsigned int g=0;g<pg.size();g++)
        //            {
        vector< Position > ghostPositions=game.getMap()->legalMov(pg[0]);// retorna proxima position valida de um fantasma 0
        for (unsigned int j = 0; j < ghostPositions.size(); j++) {
            vector<Position> tempPositions = pg; // para não perder o valor antigo, que ira ser utilizado no proximo node
            tempPositions.push_back(ghostPositions[j]); // modificando o valor da posição do fantasma 0
            State novoStateGhost(p_pac,tempPositions);
            Node childGhostValue;
            childGhostValue.atualState = novoStateGhost;
            childGhostValue.data =  evalState(game,novoStateGhost);
            child.insert(childGhostValue);

        }
        tree.insert(child);
        // }
    }
}

Position MiniMaxArtificialIntelligence::getOneGhost(IGame& game, int ghostNumber)
{ //Retorna Posicao do Ghost que ira executar o miniMax

    IGhost* g=game.getGhosts()[ghostNumber];
    Position p_ghost(g->X()/game.getMap()->width(),g->Y()/game.getMap()->height());
    p_ghost.g=g;
    return p_ghost;
}

void MiniMaxArtificialIntelligence::idle(IGame &game)
{
    static int ellap=0;
    ellap+=game.getEllapsed();

    if(ellap>200)
    {
        //createTree(game);
        createTree2(game);
        float teste = minimax(tree,4,false);

        for(unsigned int c=0;c<bestState.ghosts.size();c++)
        {
            Position* pa=&bestState.ghosts[c];

            if(pa->g)
            {
                IGhost *g=pa->g;
                g->setDirection(pa->directionX()*-1,pa->directionY()*-1);
            }
        }
        ellap = 0;
    }
}

//minimax(origin, depth, TRUE)
float MiniMaxArtificialIntelligence::minimax(Node &no, int depth, bool maximizingPlayer){
    float bestValue = 0;
    if(depth = 0 || no.children.empty())
    {
        return no.data;
    }
    if(maximizingPlayer)
    {
        bestValue = 9999999; // considerando como -infinito
        for(std::vector<Node>::iterator it=no.children.begin(); it!=no.children.end(); it++) {
            Node child = *it;
            float val = minimax(child,depth-1,false);
            if(val < bestValue){
                bestValue = val;
                no.atualState = child.atualState;
                bestState = no.atualState;
            }
            //  bestValue = std::max(bestValue,val);
        }
        return bestValue;
    }
    else
    {
        bestValue = -9999999; //considerando como valor +infinito
        for(std::vector<Node>::iterator it=no.children.begin(); it!=no.children.end(); it++)
        {
            Node child = *it;
            float val = minimax(child,depth-1,true);
            if(val > bestValue){
                bestValue = val;
                no.atualState = child.atualState;
                bestState = no.atualState;
            }
        }
        // bestValue = std::min(bestValue,val);
        return bestValue;
    }
    return 0;
}

double MiniMaxArtificialIntelligence::evalState(IGame& game,State& state)
{
    vector< vector< int > > visited;
    visited.resize(game.getMap()->cols(),vector<int>(game.getMap()->rows(),0));
    vector< Position > pg=state.ghosts;
    unsigned int visg=0;
    //    vector< Position > ps=game.getMap()->legalMov(state.pacman,&visited);
    vector< Position > ps;
    ps.push_back(state.pacman);
    int steps=0,max_steps=0;
    while(ps.size())
    {
        for(unsigned int i=0;i<ps.size();i++)
        {
            for(unsigned int g=0;g<pg.size();g++)
            {
                if(ps[i].x==pg[g].x) if(ps[i].y==pg[g].y)
                {
                    visg++;
                    if(pg[g].g)
                    {
                        if(pg[g].g->scared())
                        {
                            max_steps-=steps;
                        }
                        else
                        {
                            max_steps+=steps;
                        }
                    }
                    else
                    {
                        max_steps+=steps;
                    }
                }
            }
        }
        if(visg>=pg.size()) break;
        ps=game.getMap()->legalMov(ps,&visited);
        steps++;
    }
    double ret= (double)max_steps/(double)game.getGhosts().size();
    return ret;
}
