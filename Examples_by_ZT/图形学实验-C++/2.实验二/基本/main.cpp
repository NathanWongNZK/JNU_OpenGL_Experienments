#include <GL/glut.h>
 #include <iostream>               //需要正确安装GLUT，安装方法如预备知识中所述
using namespace std;
#include <math.h>
int a,N;
void LineDDA(int x0,int y0,int x1,float y1,int color)
{
	int x,dx;
	float m,dy,y;
	dx=x1-x0;
	dy=y1-y0;
	m=dy/dx;
	y=y0;

	switch(color)
	{
		case 1:glColor3f(1.0f, 0.0f, 0.0f);break;
		case 2:glColor3f(0.0f, 1.0f, 0.0f);break;
		case 3:glColor3f(0.0f, 0.0f, 1.0f);break;
		case 4:glColor3f(1.0f, 1.0f, 0.0f);break;
		case 5:glColor3f(0.0f, 1.0f, 1.0f);break;
		case 6:glColor3f(1.0f, 0.0f, 1.0f);break;
		case 7:glColor3f(1.0f, 1.0f, 1.0f);break;
	}

glPointSize(N);
for(x=x0;x<=x1;x++)//x走1步
{
	glBegin(GL_POINTS);
glVertex2i(x,(int)(y+0.5));
glEnd();
y+=m;//y的每次走m步
}
}
void myDisplay(void)

{
glClearColor(0.0, 0.0, 0.0, 0.0);
glClear(GL_COLOR_BUFFER_BIT);

glColor3f (1.0f, 0.0f, 0.0f);

glRectf(25.0f, 25.0f, 75.0f, 75.0f);//画正方形

glPointSize(5);
glBegin(GL_POINTS);
glColor3f (0.0f, 1.0f, 0.0f);
glVertex2f(0.0f,0.0f);
glEnd();//画一个点

LineDDA(0,0,200,300.0,a);//调用DDA函数

glBegin(GL_LINES);//调用画线函数
glColor3f (0.0f, 1.0f, 0.0f);
glVertex2f(100.0f,0.0f);

glVertex2f(180.0f,240.0f);
glEnd ();
glFlush();
}
void Reshape(int w,int h)
{
	glViewport(0,0,(GLsizei) w,(GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble) w,0.0,(GLdouble) h);
}

int main(int argc, char *argv[])
{
	
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Hello World!");
	a=1;N=1;
    glutDisplayFunc(&myDisplay);
	glutReshapeFunc(Reshape);
    glutMainLoop();

    return 0;
}
