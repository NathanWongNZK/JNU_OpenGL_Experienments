#include<gl/glut.h>
#include<math.h>
#include<windows.h>
#include<algorithm>
using namespace std;
const float COLOR[7][3] = { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 1.0, 1.0, 0.0 }, { 1.0, 0.0, 1.0 }, { 0.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0 } };
int color, lineWidth;       //颜色和线宽
//优化后的DDA算法
void LineDDA(int x0, int y0, int x1, int y1)        //DDA算法画直线，指定颜色和宽度
{
    glColor3f(COLOR[color][0], COLOR[color][1], COLOR[color][2]);
    glPointSize(lineWidth);
    if (x1 == x0)
    {
        if (y0 > y1)
            swap(y0, y1);
        glBegin(GL_POINTS);
        for (int y = y0; y <= y1; y++)
            glVertex2f(x0, y);
        glEnd();
        return;
    }

    int dy, dx;
    float m;
    dx = x1 - x0;
    dy = y1 - y0;
    m = (float)dy / dx;
    if (fabs(m) > 1)        //k的绝对值大于等于1时：y为计长方向
    {
        if (y0 > y1)
        {
            swap(x0, x1);
            swap(y0, y1);
        }
        float x = x0;
        for (int y = y0; y <= y1; y++)
        {
            glBegin(GL_POINTS);
            glVertex2i((int)(x + 0.5), y);
            glEnd();
            x += 1.0 / m;
        }
    }
    else    //否则x为计长方向
    {
        if (x0 > x1)
        {
            swap(x0, x1);
            swap(y0, y1);
        }
        float y = y0;
        for (int x = x0; x <= x1; x++)
        {
            glBegin(GL_POINTS);
            glVertex2i(x, (int)(y + 0.5));
            glEnd();
            y += m;
        }
    }   
}
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);       //清除。GL_COLOR_BUFFER_BIT表示清除颜色
    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(25.0, 25.0, 75.0, 75.0);        //画矩形

    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(0.0, 1.0, 0.0);       glVertex2f(100, 300);
    glEnd();

    LineDDA(0, 0, 200, 300);

    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);       glVertex2f(100.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);       glVertex2f(180.0, 240.0);
    glEnd();

    glFlush();
}

void Reshape(int w, int h)      //两个参数：窗口被移动后大小
{
    //调整像素矩形，用于绘制整个窗口
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    //接下来绘制坐标系，使左下角为（0,0）,右上角为（w,h）
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

void initWindow(int &argc, char *argv[], int width, int height, char *title)    //初始化并显示到屏幕中央
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition((GetSystemMetrics(SM_CXSCREEN) - width) >> 1, (GetSystemMetrics(SM_CYSCREEN) - height) >> 1);       //指定窗口位置
    glutInitWindowSize(width, height);       //指定窗口大小
    glutCreateWindow(title);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);      //设置颜色过渡模式，默认为GL_SMOOTH（渐变）
}

int main(int argc, char *argv[])
{
    initWindow(argc, argv, 400, 400, "Hello OpenGL");

    puts("\n划线颜色:");
    puts("1\t2\t3\t4\t5\t6\t7");
    puts("红色\t绿色\t蓝色\t黄色\t紫色\t兰色\t白色");
    puts("\n请输入要划线的颜色：");
    scanf("%d", &color);
    color--;
    puts("\n请输入划线的宽度：");
    scanf("%d", &lineWidth);

    glutDisplayFunc(&myDisplay);
    glutReshapeFunc(Reshape);
    glutMainLoop();
    return 0;
}
