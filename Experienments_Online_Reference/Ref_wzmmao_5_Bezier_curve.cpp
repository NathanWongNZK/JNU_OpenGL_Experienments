// OpenGL绘制Bezier曲线

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

GLsizei winWidth = 800, winHeight = 800;

GLfloat ctrlPts[4][3] = {{-200.0, 200.0, 0.0}, {-100.0, 300.0, 0.0}, {200.0, -70.0, 0.0}, {180.0, 140.0, 0.0}}; //设置四个控制点的坐标
void displayFcn(void)
{
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, *ctrlPts); //指定Bezier曲线参数
    glEnable(GL_MAP1_VERTEX_3);                          //激活Bezier曲线显示
    GLint k;
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_STRIP);
    for (k = 0; k <= 50; k++)             //系统自带的函数画Bezier曲线
        glEvalCoord1f(GLfloat(k) / 50.0); //计算型值点，其取值范围为0~1
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5.0); //绘制控制点
    glBegin(GL_POINTS);
    for (k = 0; k < 4; k++)
        glVertex3fv(ctrlPts[k]);
    glEnd();
    //绘制控制多边形
    glColor3f(0.0, 1.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    for (k = 0; k < 4; k++)
        glVertex3fv(&ctrlPts[k][0]);
    glEnd();
    glFlush(); //在显示器显示
}
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
    glViewport(0, 0, newHeight, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-newWidth / 2, newWidth / 2, -newHeight / 2, newHeight / 2);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("系统自带的函数画Bezier曲线");

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();
}