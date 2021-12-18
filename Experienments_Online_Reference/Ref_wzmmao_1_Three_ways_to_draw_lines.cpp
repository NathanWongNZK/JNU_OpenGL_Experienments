// 直线的三种画法
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>

//如果需要记录鼠标点的位置，就定义全局变量来保存
struct Point {int x, y;};
Point pt[2];
int pointNum=0;//标记点号，0表示线段起点，1表示线段中点


//数值微分DDA画线法
void DDALine(Point point1,Point point2)
{
    float x,y,dx,dy;
    int i,step;
    x = point1.x + 0.5;   //保证计算精度      
    y = point1.y + 0.5;
    step = abs(point2.x - point1.x) > abs(point2.y - point1.y) ? abs(point2.x - point1.x) : abs(point2.y - point1.y); //三元运算符
    dx = ((float)(point2.x - point1.x)) / step; //1
    dy = ((float)(point2.y - point1.y)) / step; //m
    glPointSize(2.0f);  //设置线的粗细
    glBegin(GL_POINTS);  //开始作图
    for(i = 0; i<=step; i++)
    {
        x += dx;  
        y += dy;
        glVertex2i(x,y);    //画坐标点
    }
    glEnd();  //作图结束
}

//中点画线法
void MidLine(Point point1,Point point2)
{
    //交换两点的坐标
    if ((point1.x - point2.x) >0 && (point1.y - point2.y) >0 )          
    {
        int c=point1.x;
        point1.x=point2.x;
        point2.x=c;
        c=point1.y;
        point1.y=point2.y;
        point2.y=c;
    }
    if ((point1.x - point2.x) <0 && (point1.y - point2.y) >0 )          
    {
        int c=point1.x;
        point1.x=point2.x;
        point2.x=c;
        c=point1.y;
        point1.y=point2.y;
        point2.y=c;
    }
    
    float a=point1.y-point2.y,b=point2.x-point1.x;
    float m=-(a/b);   //斜率，用于判断直线不同的情况
    glPointSize(2.0f); //设置线的粗细
    glBegin(GL_POINTS); //开始作图
     //当斜率大于0，小于1的情况
    if (0<m && m<=1) 
    {
    float d=2*a+b,deta1=2*a,deta2=2*(a+b),x=point1.x,y=point1.y;
    while(x<point2.x)
    {
        glVertex2f(x,y); //画坐标点
        if(d<0) x++,y++,d+=deta2;
        else x++,d+=deta1;        
    }
    }
    //当斜率大于1的情况
    if ( m>1 )
    {
    int d=a+2*b,deta1=2*b,deta2=2*(a+b),x=point1.x,y=point1.y;
    while(y<point2.y)
    {
        glVertex2f(x,y); //画坐标点
        if(d>0) y++,x++,d+=deta2;
        else y++,d+=deta1;        
    }    
    }
    //当斜率小于-1的情况
    if(m<=-1)
    {
    int d=-a+2*b,deta1=2*b,deta2=2*(b-a),x=point1.x,y=point1.y;
    while(y<point2.y)
    {
        glVertex2f(x,y); //画坐标点
        if(d<0) x--,y++,d+=deta2;
        else y++,d+=deta1;        
    }    
    }
    //当斜率小于0大于-1的情况
    if(m>-1&&m<0)
    {
    int a=point1.y-point2.y,b=point2.x-point1.x;
    int d=-2*a+b,deta1=-2*a,deta2=2*(b-a),x=point1.x,y=point1.y;
    while(x>point2.x)
    {
        glVertex2f(x,y); //画坐标点
        if(d>0) x--,y++,d+=deta2;
        else x--,d+=deta1;        
    }    
    }
    glEnd(); //作图结束    
}


// Bresenham画线法
void BresenhamLine(Point point1,Point point2)
{
    //交换坐标
    if ((point1.x - point2.x) >0 && (point1.y - point2.y) >0 )          
    {
        int c=point1.x;
        point1.x=point2.x;
        point2.x=c;
        c=point1.y;
        point1.y=point2.y;
        point2.y=c;
    }
    if ((point1.x - point2.x) <0 && (point1.y - point2.y) >0 )          
    {
        int c=point1.x;
        point1.x=point2.x;
        point2.x=c;
        c=point1.y;
        point1.y=point2.y;
        point2.y=c;
    }
    float a=point1.y-point2.y,b=point2.x-point1.x;
    float m=-(a/b); //斜率
    float dx=point2.x-point1.x, dy=point2.y-point1.y, x=point1.x, y=point1.y;

    glPointSize(2.0f); //设置线的粗细
    glBegin(GL_POINTS); //开始作图
     //当斜率大于0，小于1的情况
    if (0<m&&m<=1)  
    {
        float e=2*dy-dx;
        while(x<point2.x)
        {
        glVertex2f(x,y); //画坐标点
        if(e<0) x++,e+=2*dy;
        else x++,y++,e+=2*dy-2*dx;
        }            
    }
    //当斜率大于1的情况
    if (m>1)  
    {
        float e=dx-2*dy;
        while(y<point2.y)
        {
        glVertex2f(x,y); //画坐标点
        if(e<0) y++,e+=2*dx;
        else x++,y++,e+=2*dx-2*dy;
        }            
    }
    //当斜率小于0大于-1的情况    
    if (m>-1 && m<0)  
    {
        dy=-dy;
        float e=2*dy-dx;
        while(x>point2.x)
        {
        glVertex2f(x,y); //画坐标点
        if(e<0) x--,e=e+2*dy;
        else x--,y++,e=e+2*dy-2*dx;
        }
    }
    //当斜率小于-1的情况
    if(m<-1)
    {
        dy=-dy;
        float e=dx+2*dy;
        while(y<point2.y)
        {
        glVertex2f(x,y); //画坐标点
        if(e<0) y++,e+=2*dx;
        else x--,y++,e+=2*dx+2*dy;
        }
    }
    glEnd(); //作图结束    
}


void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);//画图之前先设置画图区的背景色
    glColor3f (1.0f, 0.0f, 0.0f);//设置前景色（相当于画笔颜色）

    /*
     $LARGE_INTEGER Freq;
     $LARGE_INTEGER start;
     $LARGE_INTEGER end;
     $QueryPerformanceFrequency(&Freq); // 获取时钟周期
    */   

    if(pointNum == 2)    
    {
        // $QueryPerformanceCounter(&start); // 获取时钟计数 
        //DDALine(pt[0],pt[1]);
        //MidLine(pt[0],pt[1]);
        BresenhamLine(pt[0],pt[1]);
        // $QueryPerformanceCounter(&end);
        // $printf("用时%d微秒\n",(end.QuadPart-start.QuadPart)*1000000/Freq.QuadPart);
    }
    glFlush();//强制刷新缓冲，保证绘图命令被立即执行
}

void Init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);//设置平滑颜色过渡模式（相当于在两种颜色间进行差值，想象一下线段的两个端点颜色不一样，线段中间该是什么颜色）
    printf("这是一个演示程序!\n");//在窗口中给出提示
}

void Reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);//设置视口大小与窗口大小完全一致
    glMatrixMode(GL_PROJECTION);//指定当前矩阵为投影矩阵
    glLoadIdentity();//将投影矩阵初始化为单位矩阵
    gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);//定义二维投影矩阵
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
    if (button == GLUT_LEFT_BUTTON  && state == GLUT_DOWN) //如果鼠标左键按下
    {
        if(pointNum == 2) pointNum=0; //重新记录线段的端点
        pt[pointNum].x=x;//保存线段端点的横坐标
        pt[pointNum].y=600-y;//保存线段端点的纵坐标 由于屏幕坐标的纵轴向下，而画图时坐标向上，因此需要取反
        pointNum++;
        glutPostRedisplay();    
    }
    
}

void main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Hello World!");
    Init();
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(keyboard);//注册键盘函数
    glutMouseFunc(mouse); // 注册鼠标处理函数
    glutMainLoop();
}