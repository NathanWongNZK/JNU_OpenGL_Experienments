/* 2D/3D 变换
 模拟一个太阳系星球的运转系统🌍：地球环绕太阳转，月亮🌛环绕地球转
*/
/*
    Needs texture, lighting, reflection, and movement.
    Also needs Z-Buffer. Use glEnable(GL_DEPTH_TEST).
    Remember it also needs glutInitDisplayMode(GLUT_DEPTH).
*/
#define GL_SILENCE_DEPRECATION
#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

float fElect1 = 2.0f; //
float fElect2 = 24.0f;

// Light for the Sun
GLfloat light1_ambient[] = { 1.0f, 1.0f, 0.0f, 1.0f };  
GLfloat light1_diffuse[] = { 1.0f, 1.0f, 0.0f, 1.0f };  
GLfloat light1_specular[] = { 1.0f, 1.0f, 0.0f, 1.0f };  
GLfloat light1_position[] = { 100.0f, 100.0f, 100.0f, 1.0f };  
 
//定义太阳的光系数  
GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };  
GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.4f, 1.0f };  
GLfloat light_specular[] = { 1.0f, 1.0f, 0.0f, 1.0f };  
GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };  
 
//定义太阳的材质系数  
GLfloat sun_ambient[] = { 0.2f, 0.2f, 0.0f, 1.0f };  
GLfloat sun_diffuse[] = { 0.8f, 0.8f, 0.0f, 1.0f };  
GLfloat sun_specular[] = { 1.0f, 1.0f, 0.0f, 1.0f };  
GLfloat sun_emission[] = { 0.1f, 0.0f, 0.0f, 1.0f};  
 
//定义地球的材质系数  
GLfloat earth_ambient[] = { 0.0f, 0.2f, 0.0f, 1.0f };  
GLfloat earth_diffuse[] = { 0.0f, 0.8f, 0.0f, 1.0f };  
GLfloat earth_specular[] = { 0.0f, 1.0f, 0.0f, 1.0f };  
GLfloat earth_shininess[] = { 80.0f };  
GLfloat earth_emission[] = { 0.0f, 0.1f, 0.0f, 1.0f };  
 
//定义月球的材质系数  
GLfloat moon_ambient[] = { 0.0f, 0.0f, 0.1f, 1.0f };  
GLfloat moon_diffuse[] = { 0.0f, 0.0f, 0.8f, 1.0f };  
GLfloat moon_specular[] = { 0.0f, 0.0f, 0.9f, 1.0f };  
GLfloat moon_shininess[] = { 50.0f };  
GLfloat moon_emission[] = { 0.0f, 0.1f, 0.0f, 1.0f };  
 

void my_Init()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void my_Display()
{
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslated(0.0f, 0.0f, -500.0f);
    
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);  
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);  
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);  
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);  
    glEnable(GL_LIGHT1);

    glMaterialfv(GL_FRONT, GL_AMBIENT, sun_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, sun_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, sun_emission);

    //glColor3f(0.8f, 0.0f, 0.0f);
    glColor3ub(40, 122, 184);
    glutSolidSphere(70.0f, 50, 50); // The SUN!
    glDisable(GL_LIGHT1);

    //画地球  
    glMaterialfv(GL_FRONT, GL_AMBIENT, earth_ambient);  
    glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_diffuse);  
    glMaterialfv(GL_FRONT, GL_SPECULAR, earth_specular);  
    glMaterialfv(GL_FRONT, GL_SHININESS, earth_shininess);  
    glMaterialfv(GL_FRONT, GL_EMISSION, earth_emission);  
 
    glColor3ub(40, 122, 184);  
    glRotatef(23.27,0.0,0.0,1.0); //地球与太阳的黄赤交角  
    glRotatef(fElect1, 0.0f, 1.0f, 0.0f);  
    glTranslatef(300.0f, 0.0f, 0.0f);  
    glutSolidSphere(20.0f, 50, 50);             // The Earth!
 
    //画月球  
    glMaterialfv(GL_FRONT, GL_AMBIENT, moon_ambient);  
    glMaterialfv(GL_FRONT, GL_DIFFUSE, moon_diffuse);  
    glMaterialfv(GL_FRONT, GL_SPECULAR, moon_specular);  
    glMaterialfv(GL_FRONT, GL_SHININESS, moon_shininess);  
    glMaterialfv(GL_FRONT, GL_EMISSION, moon_emission);  
 
    glPopMatrix();
    glPopMatrix();
    glRotatef(6.0f, 1.0f, 1.0f, 1.0f);
    glRotatef(fElect2, 0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.8f);
    glTranslatef(30.0f, 0.0f, 0.0f);
    glutSolidSphere(5.0f, 50, 50);              // The Moon!

    glLoadIdentity();
    fElect1 += 2.0f;
    if( 360.0f < fElect1)
        fElect1 = 2.0f;
    fElect2 += 24.0f;
    if( 360.0f < fElect2)
        fElect2 = 24.0f;

    glFlush();
    glutSwapBuffers();
}

void my_Reshape(int width, int height)
{
    GLfloat fAspect;
    if( height == 0)
        height = 1;
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    fAspect = (float) width / (float) height;
    gluPerspective(45.0f, fAspect, 1.0f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void my_Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
        glutPostRedisplay();
        //exit(0);
        break;

    default:
        break;
    }
}


void my_TimerFunc(int val)
{
    glutPostRedisplay();
    glutTimerFunc(50, my_TimerFunc, 1);
}

// ---------------Main Function Starts Here---------------
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
    glutCreateWindow("It's the SEM Model !");

    my_Init();
    glutDisplayFunc(my_Display);
    glutReshapeFunc(my_Reshape);
    glutKeyboardFunc(my_Keyboard);
    glutTimerFunc(50, my_TimerFunc, 1);
    glutMainLoop();
}
