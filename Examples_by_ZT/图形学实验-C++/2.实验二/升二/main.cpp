#include<gl/glut.h>
#include<math.h>
#include<windows.h>
#include<algorithm>
using namespace std;
const double PI = acos(-1.0);
#define getColor(a) (a/255.0)
int cnt;        //顶点数
void drawCircle(float x, float y, float r)      //画圆
{
    int n = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++)
    {
        glVertex2f(r*cos(i * 2 * PI / n)+x, r*sin(i * 2 * PI / n)+y);
    }
    glEnd();
}
void graphy1()      //国民党党徽
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(getColor(14), getColor(0), getColor(140));        //外围大蓝圆
    drawCircle(0, 0, 0.7);

    glColor3f(1, 1, 1);     //白色多边形
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0);
    for (int i = 0; i <= 24; i++)
    {
        if (i & 1)
            glVertex2f(0.4*sin(i * 2 * PI / 24), 0.4*cos(i * 2 * PI / 24));
        else
            glVertex2f(0.68*sin(i * 2 * PI / 24), 0.68*cos(i * 2 * PI / 24));
    }
    glEnd();

    glColor3f(getColor(14), getColor(0), getColor(140));        //蓝色圆
    drawCircle(0, 0, 0.36);

    glColor3f(1, 1, 1);     //白色圆
    drawCircle(0, 0, 0.32);

    glFlush();
}

void graphy2()      //共青团团徽
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 1, 0);     //外围黄色圆
    drawCircle(0, 0, 0.7);

    glColor3f(1, 0, 0);     //红色圆
    drawCircle(0, 0, 0.65);

    glColor3f(1, 1, 0);     //五角星（填充）
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0);
	int i;
    for (i = 0; i <= 10; i++)
    {
        if (i&1)
            glVertex2f(0.25*sin(i * 2 * PI / 10), 0.25*cos(i * 2 * PI / 10));
        else
            glVertex2f(0.65*sin(i * 2 * PI / 10), 0.65*cos(i * 2 * PI / 10));
    }
    glEnd();

    glColor3f(0, 0, 0);     //五角星轮廓
    for (i = 0; i <= 10; i++)
    {
        float p1_x, p1_y, p2_x, p2_y;
        if (i & 1)
        {
            p1_x = 0.25*sin(i * 2 * PI / 10);
            p1_y = 0.25*cos(i * 2 * PI / 10);
            p2_x = 0.65*sin((i + 1) * 2 * PI / 10);
            p2_y = 0.65*cos((i + 1) * 2 * PI / 10);
        }
        else
        {
            p1_x = 0.65*sin(i * 2 * PI / 10);
            p1_y = 0.65*cos(i * 2 * PI / 10);
            p2_x = 0.25*sin((i+1) * 2 * PI / 10);
            p2_y = 0.25*cos((i+1) * 2 * PI / 10);
        }

        glBegin(GL_LINES);
        glVertex2f(0, 0); glVertex2f(p1_x, p1_y);
        glVertex2f(0, 0); glVertex2f(p2_x, p2_y);
        glVertex2f(p1_x, p1_y); glVertex2f(p2_x, p2_y);
        glEnd();
    }

    glFlush();
}

void graphy3()      //多边形
{
    glClear(GL_COLOR_BUFFER_BIT);

    const float r = 0.7;
    const float hr = r / 2.0;
    for (int i = 0; i < cnt; i++)
    {
        float p1_x, p1_y, p2_x, p2_y, p3_x, p3_y;
        p1_x = r*sin(i * 2 * PI / cnt);
        p1_y = r*cos(i * 2 * PI / cnt);
        p2_x = r*sin((i+1) * 2 * PI / cnt);
        p2_y = r*cos((i+1) * 2 * PI / cnt);
        p3_x = hr*sin((i<<1|1) * PI / cnt);
        p3_y = hr*cos((i<<1|1) * PI / cnt);

        glBegin(GL_TRIANGLES);      //填充
        glColor3f(1, 0, 1);
        glVertex2f(p1_x, p1_y);
        glVertex2f(p2_x, p2_y);
        glVertex2f(p3_x, p3_y);
        glEnd();
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1, 1, 1);
        glVertex2f(0, 0);
        glVertex2f(p1_x, p1_y);
        glVertex2f(p3_x, p3_y);
        glVertex2f(p2_x, p2_y);
        glEnd();

        glBegin(GL_LINES);      //边界线条
        glColor3f(1, 0, 0);
        glVertex2f(0, 0); glVertex2f(p1_x, p1_y);
        glVertex2f(0, 0); glVertex2f(p2_x, p2_y);
        glColor3f(0, 0, 0);
        glVertex2f(0, 0); glVertex2f(p3_x, p3_y);
        glVertex2f(p2_x, p2_y); glVertex2f(p1_x, p1_y);
        glVertex2f(p3_x, p3_y); glVertex2f(p1_x, p1_y);
        glVertex2f(p3_x, p3_y); glVertex2f(p2_x, p2_y);
        glEnd();
    }

    glFlush();
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
void welcome()
{
    puts("\n\t说明：\t图案形式选择1：绘制国民党党徽；");
    puts("\t\t图案形式不为1，顶点数输入5；绘制共青团团徽！");
    puts("\t\t其余绘制花型图案！");
    printf("\n请输入图案形式(1：国民党党徽，其余不为1)：");
}
int main(int argc, char *argv[])
{
    initWindow(argc, argv, 400, 400, "Test2");
    welcome();
    int op;
    scanf("%d", &op);
    if (op == 1)
        glutDisplayFunc(&graphy1); 
    else
    {
        printf("请输入多边形的顶点数（1<n<100）: ");
        while (~scanf("%d", &cnt))
        {
            if (cnt == 5)
                glutDisplayFunc(&graphy2);
            else if (cnt > 1 && cnt < 100)
                glutDisplayFunc(&graphy3);
            else
            {
                printf("您的输入有误，请重新输入：");
                continue;
            }
            break;
        }
    }
    glutMainLoop();
    return 0;
}

