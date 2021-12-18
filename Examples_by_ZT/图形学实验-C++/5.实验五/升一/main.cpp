#include<gl/glut.h>
#include<math.h>
#include<windows.h>
#include<vector>
#include<algorithm>
using namespace std;
struct Point
{
    int x, y;
    Point(){};
    Point(int tx, int ty)
    {
        x = tx;
        y = ty;
    }
};
vector<Point> p;
double getRatio(double t,double a,double b,double c,double d)
{
    return a * pow(t, 3) + b * pow(t, 2) + c * t + d;
}
void Bezier()
{
    int n = 500;
    double derta = 1.0 / n;
    glPointSize(2);
    glColor3d(0, 0, 0);
    glBegin(GL_POINTS);
    for (int i = 1; i < n; i++)
    {
        double t = derta * i;
        double ratio[4];
        ratio[0] = getRatio(t, -1, 3, -3, 1);
        ratio[1] = getRatio(t, 3, -6, 3, 0);
        ratio[2] = getRatio(t, -3, 3, 0, 0);
        ratio[3] = getRatio(t, 1, 0, 0, 0);
        double x=0, y=0;
        for (int j = 0; j < 4; j++)
        {
            x += ratio[j] * p[j].x;
            y += ratio[j] * p[j].y;
        }
        glVertex2d(x, y);
    }
    glEnd();
}
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);    //�����ɫ�������Ȼ���

    //����
    glPointSize(5);
    glColor3d(1, 0, 0);
    glBegin(GL_POINTS);
	int i;
    for (i = 0; i < p.size(); i++)
        glVertex2d(p[i].x, p[i].y);
    glEnd();

    //����
    glLineWidth(2);
    glColor3d(0, 1, 0);
    glBegin(GL_LINE_STRIP);
    for (i = 0; i < p.size(); i++)
        glVertex2d(p[i].x, p[i].y);
    glEnd();

    if (p.size() == 4)
        Bezier();

    glFlush();
}
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && p.size() < 4)
    {
        Point t(x, y);
        p.push_back(t);
        glutPostRedisplay();
    }
}

void Reshape(int w, int h)      //�������������ڱ��ƶ����С
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void initWindow(int &argc, char *argv[], int width, int height, char *title)    //��ʼ������ʾ����Ļ����
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition((GetSystemMetrics(SM_CXSCREEN) - width) >> 1, (GetSystemMetrics(SM_CYSCREEN) - height) >> 1);       //ָ������λ��
    glutInitWindowSize(width, height);       //ָ�����ڴ�С
    glutCreateWindow(title);

    glClearColor(1, 1, 1, 0);
    glShadeModel(GL_FLAT);
}

int main(int argc, char *argv[])
{
    initWindow(argc, argv, 600, 600, "�ĵ㻭Bezier����");

    puts("\n\t����ڴ��ڵ���Ĵκ��Զ����Ƴ�Bezier����");

    glutDisplayFunc(myDisplay);
    glutReshapeFunc(Reshape);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
