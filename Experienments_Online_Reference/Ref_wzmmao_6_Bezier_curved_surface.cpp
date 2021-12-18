// Bezier 曲面绘制

#include <GL/glut.h>

GLsizei winWidth = 600, winHeight = 600;
GLfloat ctrlPts[4][4][3] = { //设置十六个控制点的坐标
    {{-2, -1.5, 4.0}, {-1, -1.5, 2.0}, {-0.5, -3, -1.0}, {1.5, -1.5, 2.0}},
    {{-2, -0.5, 1.0}, {-1, -0.5, 3.0}, {0.5, -0.5, 0.0}, {1.5, -0.5, -1.0}},
    {{-3, 0.5, 4.0}, {-1, 0.5, 0.0}, {0.5, 0.5, 3.0}, {1.5, 0.5, 4.0}},
    {{-3, 1.5, -2.0}, {-1, 1.5, -2.0}, {0.5, 1.5, 0.0}, {1.5, 1.5, -1.0}}};
void myinit(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); //设置背景颜色
    glEnable(GL_DEPTH_TEST);
    glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, // 指定Bezier曲面参数
            0.0, 1.0, 12, 4, &ctrlPts[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3); //激活Bezier曲面显示
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //初始化画面
    glPushMatrix();
    glRotatef(60.0, 1.0, 1.0, 1.0); //旋转一定的角度
    GLint k, j;

    glColor3f(1.0, 1.0, 0.0);

    for (k = 0; k <= 8; k++)
    {
        glBegin(GL_LINE_STRIP);
        for (j = 0; j <= 40; j++)
            glEvalCoord2f(GLfloat(j) / 40.0, GLfloat(k) / 8.0); //绘制Bezier曲面
        glEnd();
        glBegin(GL_LINE_STRIP);
        for (j = 0; j <= 40; j++)
            glEvalCoord2f(GLfloat(k) / 8.0, GLfloat(j) / 40.0);
        glEnd();
    }

    glColor3f(1.0, 0.0, 0.0); //绘制控制点的坐标
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (k = 0; k < 4; k++)
        for (j = 0; j < 4; j++)
            glVertex3fv(&ctrlPts[k][j][0]);
    glEnd();

    glPopMatrix();
    glFlush();
}
void myReshape(GLsizei w, GLsizei h) //设置窗口
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-4.0, 4.0, -4.0 * (GLfloat)h / (GLfloat)w, 4.0 * (GLfloat)h / (GLfloat)w, -4.0, 4.0);
    else
        glOrtho(-4.0 * (GLfloat)w / (GLfloat)h, 4.0 * (GLfloat)w / (GLfloat)h, -4.0, 4.0, -4.0, 4.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Bezier 曲面");
    myinit();
    glutDisplayFunc(display);
    glutReshapeFunc(myReshape);
    glutMainLoop();
}