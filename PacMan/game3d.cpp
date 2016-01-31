#include "game3d.h"
#include "glWindowPos.h"

void Game3D::setup()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(64,64);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("PacMan");

    glutFullScreen();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    // Map
    map=new Map3D();
    gluts.push_back(map);
    // PacMan
    pacman=new PacMan3D();
    gluts.push_back(pacman);
    // Ghosts
    for(int c=0;c<3;c++)
    {
        IGhost *g=new Ghost3D();
        ghosts.push_back(g);
        gluts.push_back(g);
    }

    state=IGame::Reset;
}

Game3D::Game3D(int playerAge,std::string playerName):
    Game(playerAge,playerName)
{
    lastEyeX=0;
    lastEyeY=0;
    lastEyeZ=0;
    lastTargetX=0;
    lastTargetY=0;
    lastTargetZ=0;
    firstPerson=false;
    radius=1.0;
    phi=2.49911;
    test=1.0;
    theta=0.899557;
}

void Game3D::positionObserverZ()
{
    double eyeX=0;
    double eyeY=0;
    double eyeZ=0;
    double targetX=0;
    double targetY=0;
    double targetZ=0;

    if(firstPerson)
    {
        eyeX = getPacman()->X()-(getPacman()->lastDirectionX()*32.0);
        eyeY = getPacman()->Y()-(getPacman()->lastDirectionY()*32.0);
        eyeZ = 32.0;

        targetX=getPacman()->X();
        targetY=getPacman()->Y();
        targetZ=16.0;
    }
    else
    {
        eyeX = width()*0.5+width()*radius*sin(phi)*sin(theta);
        eyeY = height()*0.5+width()*radius*cos(phi)*sin(theta);
        eyeZ = width()*radius*cos(theta);

        targetX=width()*0.5;
        targetY=height()*0.5;
        targetZ=0.0;
    }
    lastEyeX=(lastEyeX*63.0+eyeX)/64.0;
    lastEyeY=(lastEyeY*63.0+eyeY)/64.0;
    lastEyeZ=(lastEyeZ*63.0+eyeZ)/64.0;

    lastTargetX=(lastTargetX*63.0+targetX)/64.0;
    lastTargetY=(lastTargetY*63.0+targetY)/64.0;
    lastTargetZ=(lastTargetZ*63.0+targetZ)/64.0;

    gluLookAt(lastEyeX,lastEyeY,lastEyeZ, lastTargetX,lastTargetY,lastTargetZ, 0.0,0.0,1.0);
}

void Game3D::display()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    positionObserverZ();

    // Ambient light
    glEnable(GL_LIGHT0);
    GLint pAmbientLight[] = {0, 0, 300, 0};
    glLightiv(GL_LIGHT0,GL_POSITION,pAmbientLight);
    GLfloat cAmbientLight[] = {0.0, 0.0, 0.0, 1.0};
    cAmbientLight[0]=0.2*getTemperaturePercent();
    cAmbientLight[2]=0.2*(1-getTemperaturePercent());
    glLightfv(GL_LIGHT0,GL_AMBIENT,cAmbientLight);

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
    glLightf (GL_LIGHT1,GL_LINEAR_ATTENUATION, -2.0);
    glLightf (GL_LIGHT1,GL_QUADRATIC_ATTENUATION, 0.0001);

    for(unsigned int i=0;i<gluts.size();i++)
    {
        gluts.at(i)->display(*this);
    }
    if(state==IGame::Win)
    {
        displayText(1024.0/2.0-4*14,768.0/2.0-9,1,1,1," YOU WIN ");
    }
    else if(state==IGame::GameOver)
    {
        displayText(1024.0/2.0-4*14,768.0/2.0-9,1,1,1,"GAME OVER");
    }
    char buf[256];
    char tmp[256];
    // Lives
    itoa(lives,tmp,10);
    strcpy(buf,"LIVES: ");
    strcat(buf,tmp);
    displayText(16,64,1,1,1,buf);
    // Score
    itoa(score,tmp,10);
    strcpy(buf,"SCORE: ");
    strcat(buf,tmp);
    displayText(16,32,1,1,1,buf);
    // swap
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
    case 'p':
        firstPerson=!firstPerson;
        break;
    }
    if(theta>(PI/2.0*0.9)) theta=PI/2.0*0.9;
    if(theta<(PI/2.0*0.1)) theta=PI/2.0*0.1;
    if(phi>2*PI) phi=0.0;
    if(phi<0) phi=2*PI;

    Game::keyboard(c,x,y);
}

void Game3D::reshape(int w, int h)
{
    if(w) glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, (width()>height()?width():height())*2.0);
    glMatrixMode(GL_MODELVIEW);
}

void Game3D::idle()
{
    if(Arduino::getDoubleValue("distance")>0.0)
    {
        if(Arduino::getDoubleValue("distance")>18.0)
        {
            firstPerson=false;
        }
        else
        {
            firstPerson=true;
        }
    }

    if(false) if(getState()==IGame::Running) if(getController()->button())
    {
        phi=getController()->analogX()*PI*-0.5+PI;
        theta=getController()->analogY()*PI*-0.2+PI*0.25;
    }
    Game::idle();
}


bool Game3D::isFirstPerson()
{
    return firstPerson;
}

void Game3D::displayText( float x, float y, float r, float g, float b, const char *string )
{
    int j = strlen( string );

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor3f( r, g, b );
    glWindowPos2i(x,y);
    for( int i = 0; i < j; i++ )
    {
        glutBitmapCharacter( GLUT_BITMAP_9_BY_15, string[i] );
    }
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}
