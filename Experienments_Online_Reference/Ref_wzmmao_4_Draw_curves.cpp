// 曲线的绘制

#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
using namespace std;
int q;
GLsizei winWidth = 800, winHeight = 800;
/*class wcPt3D {
   public:
      GLfloat x, y, z;
}; */
GLfloat ctrlPts[4][3] = {{-200.0, 50.0, 0.0}, {-100.0, 300.0, 0.0}, {150.0, -170.0, 0.0}, {140.0, 40.0, 0.0}}; //设置四个控制点的坐标
float bezier1(float t)                                                                                         //计算型值点的x坐标
{
    float y;
    y = pow(1 - t, 3) * ctrlPts[0][0] + 3 * t * pow(1 - t, 2) * ctrlPts[1][0] + 3 * pow(t, 2) * (1 - t) * ctrlPts[2][0] + pow(t, 3) * ctrlPts[3][0];
    return y;
}
float bezier2(float t) //计算型值点的y坐标
{
    float y2;
    y2 = pow(1 - t, 3) * ctrlPts[0][1] + 3 * t * pow(1 - t, 2) * ctrlPts[1][1] + 3 * pow(t, 2) * (1 - t) * ctrlPts[2][1] + pow(t, 3) * ctrlPts[3][1];
    return y2;
}
float bezier3(float t) //计算型值点的z坐标
{
    float y3;
    y3 = pow(1 - t, 3) * ctrlPts[0][2] + 3 * t * pow(1 - t, 2) * ctrlPts[1][2] + 3 * pow(t, 2) * (1 - t) * ctrlPts[2][2] + pow(t, 3) * ctrlPts[3][2];
    return y3;
}
float *juzheng(float t)
{

    int i, j, k;
    float a[3][4] = {{-200, -100, 100, 140}, {50, 300, -170, 40}, {0, 0, 0, 0}}; //四个控制点的坐标，即G矩阵
    float b[4][4] = {{1, -3, 3, -1},
                     {0, 3, -6, 3},
                     {0, 0, 3, -3},
                     {0, 0, 0, 1}};               //M矩阵
    float c[4][1] = {1, t, pow(t, 2), pow(t, 3)}; //T矩阵
    float z[3][4];
    memset(z, 0, sizeof(z)); //初始化矩阵
    //下面是矩阵的计算
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 4; j++)
        {
            for (k = 0; k < 4; k++)
            {
                z[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    float z1[3][1];
    memset(z1, 0, sizeof(z1));
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 1; j++)
        {
            for (k = 0; k < 4; k++)
            {
                z1[i][j] = z1[i][j] + z[i][k] * c[k][j];
            }
        }
    }
    float z2[3] = {0, 0, 0};
    z2[0] = z1[0][0];
    z2[1] = z1[1][0];
    z2[2] = z1[2][0];
    return z2;
}
void displayFcn(void)
{
    //glMap1f (GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, *ctrlPts);
    //glEnable (GL_MAP1_VERTEX_3);
    GLint k;
    switch (q)
    {
    case 1:
        glColor3f(1.0, 0.0, 1.0);
        glBegin(GL_LINE_STRIP); //通过bezier函数绘制曲线
        for (k = 0; k <= 50; k++)
            glVertex3f(bezier1(GLfloat(k) / 50.0), bezier2(GLfloat(k) / 50.0), bezier3(GLfloat(k) / 50.0));
        glEnd();
        break;
    case 2:
        glColor3f(0.0, 1.0, 1.0);
        glBegin(GL_LINE_STRIP); //使用矩阵计算绘制曲线
        for (k = 0; k <= 50; k++)
            glVertex3f(juzheng(GLfloat(k) / 50.0)[0], juzheng(GLfloat(k) / 50.0)[1], 0);
        glEnd();
        break;
    }

    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS); //绘制控制点
    for (k = 0; k < 4; k++)
        glVertex3fv(ctrlPts[k]);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP); //绘制控制多边形线条
    for (k = 0; k < 4; k++)
        glVertex3fv(&ctrlPts[k][0]);
    glEnd();

    glFlush();
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
    printf("================请选择====================\n");
    printf("       1.通过bezier函数绘制曲线。\n");
    printf("       2.使用矩阵计算绘制曲线。\n");
    glutInit(&argc, argv);
    scanf("%d", &q);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("使用自己编写的函数绘制bezier曲线");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();
}