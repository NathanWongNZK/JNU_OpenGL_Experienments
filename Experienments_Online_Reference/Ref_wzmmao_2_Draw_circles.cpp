// 圆和圆弧的绘制
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
// #include <windows.h>
#include <math.h>
#define pi 3.1415926

//如果需要记录鼠标点的位置，就定义全局变量来保存
struct Point
{
    int x, y;
};
Point pt[2];
int pointNum = 0; //标记点号，0表示线段起点，1表示线段中点
int k;            //全局变量，用于选择算法

//中点画圆法
void MidCircle(Point point1, Point point2)
{
    float x, y, r, d;
    r = sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
    x = 0;
    y = r;
    d = 1 - r;
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    while (y >= x)
    {
        glVertex2i(x + point1.x, y + point1.y); //顺时针第一八分圆部分。

        glVertex2i(-x + point1.x, y + point1.y); //根据对称性，画出其余7个八分圆部分
        glVertex2i(-y + point1.x, x + point1.y);
        glVertex2i(-y + point1.x, -x + point1.y);
        glVertex2i(-x + point1.x, -y + point1.y);
        glVertex2i(x + point1.x, -y + point1.y);
        glVertex2i(y + point1.x, -x + point1.y);
        glVertex2i(y + point1.x, x + point1.y);

        x++;
        if (d >= 0)
        {
            d = d + 2 * (x - y) + 5;
            y--;
        }
        else
            d = d + 2 * x + 3;
    }
    glEnd();
}

//Bresenham画圆算法
void Bresenham(Point point1, Point point2)
{
    float x, y, d, d1, d2, r;
    r = sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
    x = 0;
    y = r;
    d = 2 * (1 - r);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    while (y >= 0)
    {
        glVertex2i(x + point1.x, y + point1.y); //顺时针第一四分圆部分

        glVertex2i(-x + point1.x, y + point1.y); //其余的3个四分圆
        glVertex2i(-x + point1.x, -y + point1.y);
        glVertex2i(x + point1.x, -y + point1.y);

        if (d < 0) //从H、D、V三个点中做选择
        {
            d1 = 2 * (d + y) - 1;
            if (d1 <= 0)
            {
                x++;
                d = d + 2 * x + 1;
            }
            else
            {
                x++;
                y--;
                d = d + 2 * (x - y + 1);
            }
        }
        else if (d > 0)
        {
            d2 = 2 * (d - x) - 1;
            if (d2 <= 0)
            {
                x++;
                y--;
                d = d + 2 * (x - y + 1);
            }
            else
            {
                y--;
                d = d - 2 * y + 1;
            }
        }
        else
        {
            y--;
            d = d - 2 * y + 1;
        }
    }
    glEnd();
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT); //图之前先设置画图区的背景色
    glColor3f(1.0f, 0.0f, 0.0f);  //设置前景色（相当于画笔颜色）

    /*
    LARGE_INTEGER Freq;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    QueryPerformanceFrequency(&Freq); // 获取时钟周期
    */

    if (pointNum == 2)
    {
        // QueryPerformanceCounter(&start); // 获取时钟计数

        switch (k) //选择算法
        {
        case 1:
            Bresenham(pt[0], pt[1]);
            break;
        case 2:
            MidCircle(pt[0], pt[1]);
            break;
        }

        // QueryPerformanceCounter(&end);
        // printf("用时%d微秒\n", (end.QuadPart - start.QuadPart) * 1000000 / Freq.QuadPart);
    }
    glFlush(); //强制刷新缓冲，保证绘图命令被立即执行
}

void Init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);       //设置平滑颜色过渡模式（相当于在两种颜色间进行差值，想象一下线段的两个端点颜色不一样，线段中间该是什么颜色）
    printf("这是一个演示程序!\n"); //在窗口中给出提示
}

void Reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);       //设置视口大小与窗口大小完全一致
    glMatrixMode(GL_PROJECTION);                    //指定当前矩阵为投影矩阵
    glLoadIdentity();                               //将投影矩阵初始化为单位矩阵
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h); //定义二维投影矩阵
}

//自定义的键盘消息处理函数，需要在main函数中调用对应的回调函数才能起作用
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'c':
        break;
    case 'r':
        break;
    case 'x':
        exit(0);
        break;
    default:
        break;
    }
}

void mouse(int button, int state, int x, int y) //鼠标处理回调函数
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) //如果鼠标左键按下
    {
        if (pointNum == 2)
            pointNum = 0;         //重新记录线段的端点
        pt[pointNum].x = x;       //保存线段端点的横坐标
        pt[pointNum].y = 600 - y; //保存线段端点的纵坐标 由于屏幕坐标的纵轴向下，而画图时坐标向上，因此需要取反
        pointNum++;
        glutPostRedisplay();
    }
}

int main(int argc, char *argv[])
{

    printf("\n============实验2 圆和圆弧的扫描转换==============\n");
    printf("              算法1.Bresenham画圆法；\n");
    printf("              算法2.中点画圆法。\n\n");
    printf("请输入您需要的算法：");
    scanf("%d", &k); //输入选择算法对应的数值
    if (k > 0 && k < 3)
    {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
        glutInitWindowPosition(100, 100);
        glutInitWindowSize(800, 600);
        glutCreateWindow("Hello World!");
        Init();
        glutDisplayFunc(myDisplay);
        glutReshapeFunc(Reshape);
        glutKeyboardFunc(keyboard); //注册键盘函数
        glutMouseFunc(mouse);       // 注册鼠标处理函数
        glutMainLoop();
    }
    else
    {
        printf("  '对不起，您输入的参数错误，请重新启动程序。'\n");
    }
}