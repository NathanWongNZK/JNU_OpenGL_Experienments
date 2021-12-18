#include<gl/glut.h>
#include<math.h>
#include<windows.h>
#include<algorithm>
using namespace std;
const float COLOR[7][3] = { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 1.0, 1.0, 0.0 }, { 1.0, 0.0, 1.0 }, { 0.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0 } };
int color, lineWidth;       //��ɫ���߿�
//�Ż����DDA�㷨
void LineDDA(int x0, int y0, int x1, int y1)        //DDA�㷨��ֱ�ߣ�ָ����ɫ�Ϳ��
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
    if (fabs(m) > 1)        //k�ľ���ֵ���ڵ���1ʱ��yΪ�Ƴ�����
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
    else    //����xΪ�Ƴ�����
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
    glClear(GL_COLOR_BUFFER_BIT);       //�����GL_COLOR_BUFFER_BIT��ʾ�����ɫ
    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(25.0, 25.0, 75.0, 75.0);        //������

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

void Reshape(int w, int h)      //�������������ڱ��ƶ����С
{
    //�������ؾ��Σ����ڻ�����������
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    //��������������ϵ��ʹ���½�Ϊ��0,0��,���Ͻ�Ϊ��w,h��
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

void initWindow(int &argc, char *argv[], int width, int height, char *title)    //��ʼ������ʾ����Ļ����
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition((GetSystemMetrics(SM_CXSCREEN) - width) >> 1, (GetSystemMetrics(SM_CYSCREEN) - height) >> 1);       //ָ������λ��
    glutInitWindowSize(width, height);       //ָ�����ڴ�С
    glutCreateWindow(title);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);      //������ɫ����ģʽ��Ĭ��ΪGL_SMOOTH�����䣩
}

int main(int argc, char *argv[])
{
    initWindow(argc, argv, 400, 400, "Hello OpenGL");

    puts("\n������ɫ:");
    puts("1\t2\t3\t4\t5\t6\t7");
    puts("��ɫ\t��ɫ\t��ɫ\t��ɫ\t��ɫ\t��ɫ\t��ɫ");
    puts("\n������Ҫ���ߵ���ɫ��");
    scanf("%d", &color);
    color--;
    puts("\n�����뻮�ߵĿ�ȣ�");
    scanf("%d", &lineWidth);

    glutDisplayFunc(&myDisplay);
    glutReshapeFunc(Reshape);
    glutMainLoop();
    return 0;
}
