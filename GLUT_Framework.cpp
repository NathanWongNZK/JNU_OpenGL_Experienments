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

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
    glutCreateWindow("It's the GLUT framework!");

    my_Init();
    glutDisplayFunc(my_Display);
    glutReshapeFunc(my_Reshape);
    glutKeyboardFunc(my_Keyboard);
    glutMouseFunc(my_Mouse);
    glutTimerFunc();
    glutMainLoop();
}

void my_Init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void my_Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glPointSize(2);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);

    glEnd();

    glFlush();
}

void my_Reshape(int width, int height)
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)width, 0.0, (GLdouble)height);
}

void my_Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        glutPostRedisplay();
        break;

    default:
        break;
    }
}

void my_Mouse()
{
}

void drive(int data)
{
    glutTimerFunc(1000, drive, -1); // call drvie() again in 1000ms.
    // callback function moves the object.
    glutPostRedisplay(); /* sets a flag to ensure next iter of mainloop, 
                            your display() func is called. It's like a flush()*/
}

/*
    Author:  Dinesh Subedi
    Edited:  ManuelJE
    Website: https://stackoverflow.com/questions/12518111/how-to-load-a-bmp-on-glut-to-use-it-as-a-texture
    *All credits to the author.
    Usage:   // Store texture data in:
             GLuint texture;
             texture = LoadTexture( "Your_image_name.bmp");
             // Now you can bind the texture.
             glBindTexture(GL_TEXTURE_2D, texture);
*/
GLuint LoadTexture(const char *filename)
{ 
    GLuint texture;
    int width, height;
    unsigned char *data;

    FILE *file;
    file = fopen(filename, "rb");

    if (file == NULL)
        return 0;
    width = 1024;
    height = 512;
    data = (unsigned char *)malloc(width * height * 3);
    //int size = fseek(file,);
    fread(data, width * height * 3, 1, file);
    fclose(file);

    for (int i = 0; i < width * height; ++i)
    {
        int index = i * 3;
        unsigned char B, R;
        B = data[index];
        R = data[index + 2];

        data[index] = R;
        data[index + 2] = B;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);

    return texture;
}
