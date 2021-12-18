/*
    Notice: glBindTexture can't be put between glBegin() and glEnd().

*/

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <stdio.h>

// -------------------Global Vars-------------------
GLuint *pTexture;
GLsizei size;
// -------------------------------------------------

void Other_stuffs();

void InitGL()
{
    glEnable(GL_TEXTURE_2D); 
    glGenTextures(size, (GLuint*)&pTexture[0]);
    glBindTexture(GL_TEXTURE_2D, pTexture[0]);
    pData = LoadImage( fileName );
    glTexImage2D( GL_TEXTURE_2D,            // Target
                            0,              // Level
                            internalFormat, // TextureInternalFormat
                            width,
                            height,
                            0,             // Texture depth
                            0x80E1,        // GL_BGRA
                            textureType,
                            pData);
}

void RenderGL()
{
    glBindTexture(GL_TEXTURE_2D, pTexture[0]);
    glBegin(primitive);
    glTexCoord(u, v);
    glVertex3f(x, y, z);

    Other_stuffs();

    glEnd();
}
