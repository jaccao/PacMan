#include "aleatoryartificialintelligence.h"

AleatoryArtificialIntelligence::AleatoryArtificialIntelligence()
{

}

void AleatoryArtificialIntelligence::display(IGame &game)
{
    (void)game;
}

void AleatoryArtificialIntelligence::keyboard(IGame &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void AleatoryArtificialIntelligence::keyboardUp(IGame &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void AleatoryArtificialIntelligence::idle(IGame &game)
{
    static int ellap=0;
    ellap+=game.getEllapsed();
    if(ellap>200)
    {
        ellap=0;
        for (unsigned int i = 0; i < game.getGhosts().size(); i++)
        {
            IGhost* g = game.getGhosts()[i];
            Position p_ghost(g->X()/game.getMap()->width(),g->Y()/game.getMap()->height());
            p_ghost.g = g;
            vector<Position> psg = game.getMap()->legalMov(p_ghost);

            bool colision_wall = true;

            for (unsigned int var = 0; var < psg.size(); var++)
            {
                if(psg[var].directionX())if(psg[var].directionX() == g->getDirectionX()*-1) colision_wall = false;
                if(psg[var].directionY())if(psg[var].directionY() == g->getDirectionY()*-1) colision_wall = false;
            }
            if(colision_wall || rand()%10 >= 7)
            {
                Position p_new = psg[ rand()% psg.size() ];
                //Position p_new = psg[ rand%psg.size()];
                g->setDirection(p_new.directionX()*-1,p_new.directionY()*-1);
            }
        }
    }
}

