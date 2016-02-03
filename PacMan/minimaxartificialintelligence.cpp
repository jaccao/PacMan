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

void MiniMaxArtificialIntelligence::createTree(IGame &game)
{
    tree = Node(0);

    //vector all ghosts positions
    vector<Position> all_ghosts;
    //object Pacman
    Position p_pac(game.getPacman()->X()/game.getMap()->width(),game.getPacman()->Y()/game.getMap()->height());

    //insert all ghosts in vector positions of ghosts
    for (unsigned int var = 0; var < game.getGhosts().size(); var++)
    {
        IGhost* g = game.getGhosts()[var];
        Position p_ghost(g->X()/game.getMap()->width(),g->Y()/game.getMap()->height());
        p_ghost.g=g;
        all_ghosts.push_back(p_ghost);
    }
    //initialize the inicial state with atual position of pacman and atual position of all ghosts
    State inicial(p_pac, all_ghosts);
    //start recursive function to create tree
    geraStates(game, p_pac, inicial, all_ghosts, 0, all_ghosts.size());
}

void MiniMaxArtificialIntelligence::geraStates(IGame &game, Position pacman, State &move, vector<Position> all_ghosts, int number_of_ghost, int total_of_ghost)
{
    if(number_of_ghost == total_of_ghost)
    {
        Node childGhostValue;
        childGhostValue.atualState = move;
        //childGhostValue.data =  -evalState(game,move);
        childGhostValue.data =  -evalState2(game,move);
        tree.insert(childGhostValue);
        return ;
    }

    vector< Position > ghostPositions = game.getMap()->legalMov(all_ghosts[number_of_ghost]);// retorna proxima position valida de um fantasma 0

    for (unsigned int j = 0; j < ghostPositions.size(); j++)
    {
        Position ghost = ghostPositions[j];

        State new_state = move;
        new_state.ghosts[number_of_ghost] = ghost;

        geraStates(game, pacman, new_state, all_ghosts, number_of_ghost+1, total_of_ghost);

        /*Node childGhostValue;
        childGhostValue.atualState = s;
        childGhostValue.data =  evalState(game,s);
        tree.insert(childGhostValue);*/
    }
}

void MiniMaxArtificialIntelligence::idle(IGame &game)
{
    static int ellap=0;
    ellap+=game.getEllapsed();

    if(ellap>200)
    {
        createTree(game);
        minimaxAlfaBeta(tree, 4, -999999, 999999, true);

        for(unsigned int c=0;c<bestState.ghosts.size();c++)
        {
            Position* pa=&bestState.ghosts[c];

            if(pa->g)
            {
                IGhost *g=pa->g;
                //if(g->scared())
                    //g->setDirection(pa->directionX(),pa->directionY());
                //else
                    g->setDirection(pa->directionX()*-1,pa->directionY()*-1);
            }
        }
        ellap = 0;
    }
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

float MiniMaxArtificialIntelligence::minimaxAlfaBeta(Node &no,int depth, float alpha, float beta, bool maximizingPlayer)
{
    float maxbestValue = -9999999, minbestValue = 9999999;
    State maxbestState, minbestState;
    if(depth == 0 || no.children.empty())
    {
        return no.data;
    }

    for(std::vector<Node>::iterator it=no.children.begin(); it!=no.children.end(); it++)
    {
        Node child = *it;
        float val = minimaxAlfaBeta(child, depth-1, alpha, beta, maximizingPlayer ? false : true);
        if(val > maxbestValue)
        {
            maxbestValue = val;
            no.atualState = child.atualState;
            maxbestState = no.atualState;
        }
        if(val < minbestValue)
        {
            minbestValue = val;
            no.atualState = child.atualState;
            minbestState = no.atualState;
        }

        if(maximizingPlayer)
        {
            alpha = std::max(maxbestValue, alpha);
        }
        else
        {
            beta = std::min(minbestValue, beta);
        }

        //when max beta cut-off, when min alpha cut-off
        if(beta <= alpha)
            break;
    }

    bestState = maximizingPlayer ? maxbestState : minbestState;
    return maximizingPlayer ? maxbestValue : minbestValue;
}

double MiniMaxArtificialIntelligence::evalState2(IGame& game, State& state)
{
    vector< Position > pg = state.ghosts;
    vector< Position > ps;
    ps.push_back(state.pacman);

    int menor_distance1 = game.getHeuristica()->findWay(state.pacman,pg[0], pg);
    int menor_distance2 = game.getHeuristica()->findWay(state.pacman,pg[1], pg);
    int menor_distance3 = game.getHeuristica()->findWay(state.pacman,pg[2], pg);

    double ret =(menor_distance1 + menor_distance2 + menor_distance3)/3;
    return ret;
}
