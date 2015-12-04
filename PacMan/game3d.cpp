#include "game3d.h"

Game3D &Game3D::instance()
{
    static Game3D ctx;
    return(ctx);
}

void Game3D::keyboard(unsigned char c, int x, int y)
{
    instance().keyboardImp(c,x,y);
}

void Game3D::keyboardUp(unsigned char c, int x, int y)
{
    instance().keyboardUpImp(c,x,y);
}

int Game3D::setup(int argc,char *argv[],int cols, int rows, int width, int height)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(64,64);
    glutInitWindowSize(width*cols, height*rows);
    glutCreateWindow("PacMan");

    glutDisplayFunc(Game3D::display);
    glutKeyboardFunc(Game3D::keyboard);
    glutKeyboardUpFunc(Game3D::keyboardUp);
    glutIdleFunc(Game3D::idle);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    instance().setupImp(cols,rows, width, height);

    glutMainLoop();
    return 0;
}

void Game3D::idle()
{
    instance().idleImp();
}

void Game3D::display()
{
    instance().displayImp();
}

Game3D::Game3D()
{
    radius=1.0;
    phi=2.49911;
    theta=0.899557;
    state=Game3D::Running;
    ftime(&last);
    // Controller
    IController* k;
#ifdef USE_QT
    k=new ArduinoController();
#else
    k=new KeyboardController();
#endif
    controller=k;
    gluts.push_back(k);
    // Map
    IMap *m=new Map3D();
    map=m;
    gluts.push_back(m);
    // PacMan
    IPacMan *p=new PacMan3D();
    pacman=p;
    gluts.push_back(p);
    // Ghosts
    for(int c=0;c<3;c++)
    {
        IGhost *g=new Ghost3D();
        ghosts.push_back(g);
        gluts.push_back(g);
    }
    // AI
    IArtificialIntelligence *a=new DistanceArtificialIntelligence();
    ai=a;
    gluts.push_back(a);
}

int Game3D::getEllapsed()
{
    return ellapsed;
}

Game3D::State Game3D::getState()
{
    return state;
}

IController *Game3D::getController()
{
    return controller;
}

IMap *Game3D::getMap()
{
    return map;
}

IPacMan *Game3D::getPacman()
{
    return pacman;
}

vector<IGhost *> Game3D::getGhosts()
{
    return ghosts;
}

IArtificialIntelligence *Game3D::getAi()
{
    return ai;
}

void Game3D::displayText( float x, float y, int r, int g, int b, const char *string )
{
    int j = strlen( string );

    glColor3f( r, g, b );
    glRasterPos2f( x, y );
    for( int i = 0; i < j; i++ )
    {
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, string[i] );
    }
}

void Game3D::positionObserverZ()
{
    double eyeY = 512*cos(phi)*sin(theta);
    double eyeX = 512*sin(phi)*sin(theta);

    double eyeZ = 512*cos(theta);

    gluLookAt(eyeX,eyeY,eyeZ, 0.0,0.0,0.0, 0.0,0.0,1.0);
}

void Game3D::displayImp()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    positionObserverZ();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-width*0.6,width*0.6,-height*0.6,height*0.6,10,2000);
    glMatrixMode(GL_MODELVIEW);
/*
 * disable: over the pacman light
    // Ambient light
    glEnable(GL_LIGHT0);
    position[0]=0; position[1]=0; position[2]=300; position[3]=0;
    glLightiv(GL_LIGHT0,GL_POSITION,position);
    color[0]=0.01; color[1]=0.01; color[2]=0.01; color[3]=1.0;
    glLightfv(GL_LIGHT0,GL_AMBIENT,color);
*/
    // Pacman light
    GLfloat qaAmbientLight[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat qaDiffuseLight[] = {1, 1, 1, 1.0};
    GLfloat qaSpecularLight[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat qaLightPosition[4];
    GLfloat dirVector0[4];
    glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight);
    qaLightPosition[0]=pacman->X()-width/2.0;
    qaLightPosition[1]=pacman->Y()-height/2.0;
    qaLightPosition[2]=12.0;
    qaLightPosition[3]=1.0;
    glLightfv(GL_LIGHT1, GL_POSITION, qaLightPosition);
    glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight);

    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
    dirVector0[0]=pacman->lastDirectionX();
    dirVector0[1]=pacman->lastDirectionY();
    dirVector0[2]=0.0;
    dirVector0[3]=0.0;
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dirVector0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1);

    glLightf (GL_LIGHT1,GL_CONSTANT_ATTENUATION, 1.0);
    glLightf (GL_LIGHT1,GL_LINEAR_ATTENUATION, 0.0);
    glLightf (GL_LIGHT1,GL_QUADRATIC_ATTENUATION, 0.00002);

    // code
    glScaled(radius,radius,radius);
    glTranslated(-width/2.0,-height/2.0,0.0);

    for(unsigned int i=0;i<gluts.size();i++)
    {
        gluts.at(i)->display(*this);
    }
    if(state==IGame::Win)
    {
        displayText(map->width()*map->cols()/2.0-4*14,map->height()*map->rows()/2.0-9,1,1,1," YOU WIN ");
    }
    if(state==IGame::GameOver)
    {
        displayText(map->width()*map->cols()/2.0-4*14,map->height()*map->rows()/2.0-9,1,1,1,"GAME OVER");
    }
    glutSwapBuffers();
}

void Game3D::keyboardImp(unsigned char c, int x, int y)
{
    double step=0.1;
    switch(c)
    {
    case 'i':
        theta-=step;
        break;
    case 'k':
        theta+=step;
        break;
    case 'j':
        phi+=step;
        break;
    case 'l':
        phi-=step;
        break;
    case 'o':
        radius+=step;
        break;
    case 'u':
        radius-=step;
        break;
    }

    if(theta>(PI/2.0*0.9)) theta=PI/2.0*0.9;
    if(theta<(PI/2.0*0.1)) theta=PI/2.0*0.1;
    if(phi>2*PI) phi=0.0;
    if(phi<0) phi=2*PI;

    if(state==Game3D::Running) for(unsigned int i=0;i<gluts.size();i++)
    {
        gluts.at(i)->keyboard(*this,c,x,y);
    }
    if(c==' ')
    {
        map->setup(*this,map->cols(),map->rows(),map->width(),map->height());
        state=Game3D::Running;
    }
    if(c==27)//esc
    {
        exit(0);
    }
    glutPostRedisplay();
}

void Game3D::keyboardUpImp(unsigned char c, int x, int y)
{
    if(state==Game3D::Running) for(unsigned int i=0;i<gluts.size();i++)
    {
        gluts.at(i)->keyboardUp(*this,c,x,y);
    }
    glutPostRedisplay();
}

void Game3D::setupImp(int cols, int rows, int width, int height)
{
    this->width=cols*width;
    this->height=rows*height;
    map->setup(*this, cols, rows, width, height);
}

void Game3D::idleImp()
{
    struct timeb now;
    ftime(&now);
    ellapsed=(now.time-last.time)*1000.0+now.millitm-last.millitm;
    last=now;
    if(state==Game3D::Running)
    {
        for(unsigned int i=0;i<gluts.size();i++)
        {
            gluts.at(i)->idle(*this);
        }
        for(unsigned int i=0;i<ghosts.size();i++)
        {
            IGhost *g=ghosts.at(i);
            int x=(int)(pacman->X()/map->width())-(int)(g->X()/map->width());
            int y=(int)(pacman->Y()/map->height())-(int)(g->Y()/map->height());
            if(!x) if(!y)
            {
                if(g->scared())
                {
                    g->scared(false);
                    g->setDirection(0,0);
                    g->X((map->cols()/2.0+0.5)*map->width());
                    g->Y((map->rows()/2.0-1+0.5)*map->height());
                }
                else
                {
                    state=Game3D::GameOver;
                }
            }
        }
        bool food=false;
        for(int y=0;y<map->rows();y++)
            for(int x=0;x<map->cols();x++)
                if(map->matrix()[x][y]==2) food=true;
        if(food==false) state=Game3D::Win;
    }
    glutPostRedisplay();
}


void Game3D::stateChanged()
{
}
