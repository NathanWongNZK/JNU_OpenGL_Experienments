#include <GL/glut.h> //需要正确安装GLUT，安装方法如预备知识中所述
void drawSquare(void)
{
glBegin(GL_POLYGON);//红色菱形函数
 	glColor3f(1.0,0.0,0.0);
	glVertex2f (0.0f, 0.0f);
    glVertex2f (0.2f, 0.4f);
    glVertex2f (0.0f, 0.8f);
    glVertex2f (-0.2f, 0.4f);

    glEnd ();
}
void drawgreen(void)//绿色菱形函数
{
	glBegin(GL_POLYGON);
    glColor3f(0.0,1.0,0.0);
	glVertex2f (0.0f, 0.0f);
    glVertex2f (0.4f, 0.2f);
    glVertex2f (0.6f, 0.6f);
    glVertex2f (0.2f, 0.4f);
    glEnd ();
}
void myDisplay(void)

{
	drawSquare();
	for(int i=0;i<3;i++)//循环三次
	{
    glRotatef(90.0,0.0,0.0,1.0);//逆时针方向旋转画四个红色菱形

    drawSquare();
	}

	drawgreen();
	
	for(int j=0;j<3;j++)
	{
    glRotatef(90.0,0.0,0.0,1.0);//逆时针方向旋转画四个绿色菱形
    drawgreen();
	}

glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Hello World!");
    glutDisplayFunc(&myDisplay);
    glutMainLoop();
    return 0;
}
