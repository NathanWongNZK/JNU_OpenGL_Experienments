#include <GL/glut.h> //��Ҫ��ȷ��װGLUT����װ������Ԥ��֪ʶ������
void drawSquare(void)
{
glBegin(GL_POLYGON);//��ɫ���κ���
 	glColor3f(1.0,0.0,0.0);
	glVertex2f (0.0f, 0.0f);
    glVertex2f (0.2f, 0.4f);
    glVertex2f (0.0f, 0.8f);
    glVertex2f (-0.2f, 0.4f);

    glEnd ();
}
void drawgreen(void)//��ɫ���κ���
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
	for(int i=0;i<3;i++)//ѭ������
	{
    glRotatef(90.0,0.0,0.0,1.0);//��ʱ�뷽����ת���ĸ���ɫ����

    drawSquare();
	}

	drawgreen();
	
	for(int j=0;j<3;j++)
	{
    glRotatef(90.0,0.0,0.0,1.0);//��ʱ�뷽����ת���ĸ���ɫ����
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
