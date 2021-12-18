// 图形变换
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

void Reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -30, 30); //正交投影
    glMatrixMode(GL_MODELVIEW);         //定义模型观察变换矩阵
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
}

void display(void)
{
    GLfloat params[4][4] = {1};
    glColor3f(1, 0, 0); //线的颜色
    glLoadIdentity();
    gluLookAt(0.0, -2.0, 8.0, 0.0, 0.0, 0.0, 0, 1.0, 0.0); //gluLookAt()共有九个参数，分别是眼睛的位置，眼睛朝向的位置，以及相片朝上的方向。
    glScalef(3, 2, 1);                                     //放缩函数：设置长宽高的比例为3：2：1
    glRotatef(45, 0.0, 0, 1.0);                            //旋转函数，设置倾斜45度
    glTranslatef(0, 0, 0);                                 //平移函数，设置绘图位置
    glutWireCube(2.0);                                     //绘制立方体的函数
    glFlush();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); //窗口背景色
    glShadeModel(GL_FLAT);
}

int main(int argc, char **argv)
{
    //初始化窗口
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(300, 300);
    glutCreateWindow("text05");
    init();
    glutDisplayFunc(display); //回调
    glutReshapeFunc(Reshape);
    glutMainLoop();
    return 0;
}