#include<GL/glut.h>
#include<cmath>
const int n = 100;
const GLfloat R = 0.6f;
const GLfloat pi = 3.1415926536f;
const GLfloat Pi = 3.1415926536f;
void myDisplay(void){
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear (GL_COLOR_BUFFER_BIT);
	
	glColor3f (1.0f, 1.0f, 1.0f);
	glRectf(-1.0f, -1.0f, 1.0f, 1.0f);

	glBegin (GL_TRIANGLES);
	glColor3f (0.0f, 1.0f, 0.0f); glVertex2f (1.0f, 1.0f);
	glColor3f (0.0f, 0.0f, 1.0f); glVertex2f (-1.0f, 1.0f);
	glColor3f (1.0f, 0.0f, 0.0f); glVertex2f (0.0f, -1.0f);
	glEnd ();
	
	glBegin (GL_TRIANGLES);
	glColor3f (0.0f, 1.0f, 0.0f); glVertex2f (0.8f, -0.7f);
	glColor3f (0.0f, 0.0f, 1.0f); glVertex2f (0.7f, -0.9f);
	glColor3f (1.0f, 0.0f, 0.0f); glVertex2f (0.9f, -0.9f);
	glEnd ();
	
	glBegin (GL_TRIANGLES);
	glColor3f (0.0f, 1.0f, 0.0f); glVertex2f (-0.8f, -0.7f);
	glColor3f (0.0f, 0.0f, 1.0f); glVertex2f (-0.7f, -0.9f);
	glColor3f (1.0f, 0.0f, 0.0f); glVertex2f (-0.9f, -0.9f);
	glEnd ();
	
	glBegin(GL_POLYGON);
	glColor3f (0.8f, 0.0f, 0.8f); 
	for (int i = 0; i < n; i++)
	{
		glVertex2f(R*cos(2*pi/n*i), R*sin(2*pi/n*i));		
	}
	glEnd();
	//画五角星
 	glColor3f (0.0f, 0.0f, 1.0f);
 	//GLfloat a = 1 / (2 - 2 * cos(72 * Pi / 180));
 	GLfloat a = 0.8;
    GLfloat bx = a * cos(18 * Pi / 180);
    GLfloat by = a * sin(18 * Pi / 180);
    //GLfloat cx = a * sin(36 * Pi / 180);
    GLfloat cy = -a * cos(36 * Pi / 180);
    GLfloat
        PointA[2] = { 0, a },
        PointB[2] = { bx, by },
        PointC[2] = { 0.5, cy },
        PointD[2] = { -0.5, cy },
        PointE[2] = { -bx, by };
    //glClear(GL_COLOR_BUFFER_BIT);
    // 按照A->C->E->B->D->A的顺序，可以一笔将五角星画出
    glBegin(GL_LINE_LOOP);
	
        glVertex2fv(PointA);
        glVertex2fv(PointC);
        glVertex2fv(PointE);
        glVertex2fv(PointB);
        glVertex2fv(PointD);
	 glVertex2fv(PointA);
    glEnd();	
	glFlush();
}

int main(int argc, char *argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition (100, 100);
	glutInitWindowSize (400, 400);
	glutCreateWindow ("Hello world!");
	glutDisplayFunc (&myDisplay);
	glutMainLoop ();
	return 0;
}