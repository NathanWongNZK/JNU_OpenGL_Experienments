//真实感图形绘制
#include <stdlib.h>
#include <GL/glut.h>
GLfloat vertices[][3] = {{-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, 1.0, -1.0}, {-1.0, 1.0, -1.0}, {-1.0, -1.0, 1.0}, {1.0, -1.0, 1.0}, {1.0, 1.0, 1.0}, {-1.0, 1.0, 1.0}};
static GLfloat theta[] = {0.0, 0.0, 0.0};
static GLint axis = 2;
static GLdouble viewer[] = {0.0, 0.0, 5.0};
GLfloat sgenparams[] = {1.0, 1.0, 1.0, 0.0};
#define TEXTUREWIDTH 64
GLubyte Texture[3 * TEXTUREWIDTH];
void makeTexture(void)
{
    int i;
    for (i = 0; i < TEXTUREWIDTH; i++)
    {
        Texture[3 * i] = 255;
        Texture[3 * i + 1] = 255 - 2 * i;
        Texture[3 * i + 2] = 255;
    }
}
void polygon(int a, int b, int c, int d)
{
    glBegin(GL_POLYGON);
    glVertex3fv(vertices[a]);
    glVertex3fv(vertices[b]);
    glVertex3fv(vertices[c]);
    glVertex3fv(vertices[d]);
    glEnd();
}
void colorcube()
{
    //正前面
    glColor3f(1, 1, 1);
    polygon(4, 5, 6, 7);
    //正背面
    glColor3f(1.0, 0, 0);
    polygon(0, 3, 2, 1);

    glColor3f(0, 1, 0);
    polygon(2, 3, 7, 6);
    glColor3f(0, 0, 1);
    polygon(0, 4, 7, 3);
    glColor3f(1, 1, 0);
    polygon(1, 2, 6, 5);
    glColor3f(0, 1, 1);
    polygon(0, 1, 5, 4);
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    //更新视点位置
    gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0); /* 旋转立方体 */
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    colorcube();
    glutSwapBuffers();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    //增加光照效果和设置相应的参数
    GLfloat light_ambient[] = {0.01, 0.01, 0.01, 1.0};
    GLfloat light_diffuse[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat light_specular[] = {0.5, 0.5, 0.5, 0.5};
    GLfloat light_position[] = {0.0, 0.0, 1.5, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, light_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, light_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialf(GL_FRONT, GL_SHININESS, 1.0);
    //启动光照
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //创建纹理
    makeTexture();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //控制纹理
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage1D(GL_TEXTURE_1D, 0, 3, TEXTUREWIDTH, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, Texture);
    //启用纹理坐标自动产生，生成环境纹理
    //纹理的方向S
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGenfv(GL_S, GL_OBJECT_PLANE, sgenparams);
    //启用纹理
    glEnable(GL_TEXTURE_1D);
    glEnable(GL_TEXTURE_GEN_S);
}
void keys(unsigned char key, int x, int y)
{ /* 用 x, X, y, Y, z, and Z 键 移动视点 */
    if (key == 'x')
        viewer[0] -= 1.0;
    if (key == 'X')
        viewer[0] += 1.0;
    if (key == 'y')
        viewer[1] -= 1.0;
    if (key == 'Y')
        viewer[1] += 1.0;
    if (key == 'z')
        viewer[2] -= 1.0;
    if (key == 'Z')
        viewer[2] += 1.0;
    display();
}
void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //设置窗口，使之与适口的比例一致，图形不变形
    if (w <= h)
        glFrustum(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
                  2.0 * (GLfloat)h / (GLfloat)w, 2.0, 20.0);
    else
        glFrustum(-2.0, 2.0, -2.0 * (GLfloat)w / (GLfloat)h,
                  2.0 * (GLfloat)w / (GLfloat)h, 2.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}
void mouse(int btn, int state, int x, int y) //鼠标控制
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        axis = 0;
    if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
        axis = 1;
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        axis = 2;
    theta[axis] += 2.0;
    if (theta[axis] > 360.0)
        theta[axis] -= 360.0;
    display();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutCreateWindow("chen");
    glutDisplayFunc(display);
    glutReshapeFunc(myReshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keys);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //选择面型显示
    glEnable(GL_CULL_FACE);                    //消隐剔除背向面
    glCullFace(GL_BACK);
    glutMainLoop();
}