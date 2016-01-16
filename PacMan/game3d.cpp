#include "game3d.h"

void Game3D::setup(int cols, int rows, int width, int height)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(64,64);
//    glutInitWindowSize(width*cols, height*rows);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("PacMan");

    //glutFullScreen();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    radius=1.0;
    phi=2.49911;
    theta=0.899557;
    state=IGame::Running;
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

    this->width=cols*width;
    this->height=rows*height;
    map->setup(*this, cols, rows, width, height);
}

Game3D::Game3D(int playerAge):
    Game(playerAge)
{
}

void Game3D::positionObserverZ()
{
    double eyeY = 512*cos(phi)*sin(theta);
    double eyeX = 512*sin(phi)*sin(theta);

    double eyeZ = 512*cos(theta);

    gluLookAt(eyeX,eyeY,eyeZ, 0.0,0.0,0.0, 0.0,0.0,1.0);
}

void Game3D::display()
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

    // Ambient light
    glEnable(GL_LIGHT0);
    GLint pAmbientLight[] = {0, 0, 300, 0};
    glLightiv(GL_LIGHT0,GL_POSITION,pAmbientLight);
    GLfloat cAmbientLight[] = {0.0, 0.0, 0.0, 1.0};
    cAmbientLight[0]=0.2*getTemperaturePercent();
    cAmbientLight[2]=0.2*(1-getTemperaturePercent());
    glLightfv(GL_LIGHT0,GL_AMBIENT,cAmbientLight);

    // code
    // TODO: distance change to first person, not the zoom
    static double lastDistancePercent=1.0;
    lastDistancePercent=(lastDistancePercent*3.0+getDistancePercent())/4.0;
    radius=1.0-lastDistancePercent*0.2;
    glScaled(radius,radius,radius);
    glTranslated(-width/2.0,-height/2.0,0.0);

    // Pacman light
    GLfloat qaAmbientLight[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat qaDiffuseLight[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat qaSpecularLight[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat qaLightPosition[4];
    GLfloat dirVector0[4];
    glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight);
    qaLightPosition[0]=pacman->X();
    qaLightPosition[1]=pacman->Y();
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
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);

    glLightf (GL_LIGHT1,GL_CONSTANT_ATTENUATION, 0.0);
    glLightf (GL_LIGHT1,GL_LINEAR_ATTENUATION, -2.0/radius);
    glLightf (GL_LIGHT1,GL_QUADRATIC_ATTENUATION, 0.0001/radius);

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

void Game3D::keyboard(unsigned char c, int x, int y)
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

    Game::keyboard(c,x,y);
}
