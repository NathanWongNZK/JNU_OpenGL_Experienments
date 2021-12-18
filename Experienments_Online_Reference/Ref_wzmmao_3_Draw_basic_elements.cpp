// OpenGL基本图元绘制
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
// #include <windows.h>


//用不同颜色绘制宽度为1、3、5的三条直线段
void Line()
{
   glLineWidth(1);//设置线宽
   glBegin(GL_LINES);//开始画线
   glColor3f (0.0f, 0.0f, 1.0f);//设置前景色（相当于画笔颜色）
   glVertex2i(400,200);//设置起点
   glVertex2i(700,200);//设置终点
   glEnd();

    glLineWidth(3);
   glBegin(GL_LINES);
    glColor3f (1.0f, 0.0f, 1.0f);//设置前景色（相当于画笔颜色）
      glVertex2i(400,300);//设置起点
   glVertex2i(700,300);//设置终点
   glEnd();

    glLineWidth(5);
glBegin(GL_LINES);
    glColor3f (0.0f, 1.0f, 1.0f);//设置前景色（相当于画笔颜色）
      glVertex2i(400,100);//设置起点
   glVertex2i(700,100);//设置终点
glEnd();
}



//用不同颜色绘制大小从1到5的5个点
void Point()
{    
    glPointSize(1);//设置点大小
    glColor3f (0.0f, 1.0f, 0.0f);//设置画笔颜色
    glBegin(GL_POINTS);
    glVertex2i(100,550);//设置点位置
    glEnd();

    glPointSize(2.0f);//设置点大小
    glColor3f (1.0f, 0.0f, 0.0f);//设置画笔颜色
    glBegin(GL_POINTS);    
    glVertex2i(150,550);//设置点位置
    glEnd();

    glPointSize(3.0f);//设置点大小
    glColor3f (1.0f, 1.0f, 0.0f);//设置画笔颜色
    glBegin(GL_POINTS);
    glVertex2i(200,550);//设置点位置
    glEnd();


    glPointSize(4.0f);//设置点大小
    glColor3f (0.0f, 1.0f, 1.0f);//设置画笔颜色
    glBegin(GL_POINTS);    
    glVertex2i(250,550);//设置点位置
    glEnd();

    glPointSize(5.0f);//设置点大小
    glColor3f (0.0f, 0.0f, 1.0f);//设置相当于画笔颜色
    glBegin(GL_POINTS);    
    glVertex2i(300,550);//设置点位置
    glEnd();
}
//绘制一条包含5个顶点的折线段
void Line2()
{
   glLineWidth(1);
   glBegin(GL_LINE_LOOP);
   glColor3f (0.5f, 0.8f, 0.5f);//设置画笔颜色
   glVertex2f(700.0f,500.0f);//设置起点
   glVertex2f(620.0f,300.0f);
   glVertex2f(380.0f,30.0f);
   glVertex2f(250.0f,100.0f);   
   glVertex2f(140.0f,500.0f);//设置终点
   glEnd();
}


// 绘制三角形
void Triangle()
{
    glBegin(GL_TRIANGLES);    
    glColor3f(1.0f,0.0f,0.0f);        //设置画笔颜色
    glVertex2i( 100,100);            //设置点的位置            
    glColor3f(0.0f,1.0f,0.0f);                        
    glVertex2i(300,100);
    glColor3f(0.0f,0.0f,1.0f);                        
    glVertex2i( 200,500);                
    glEnd();
}
//绘制六边形
void Hex()
{
   glBegin(GL_POLYGON);
   glVertex2i(460,400);
   glVertex2i(600,360);
   glVertex2i(520,490);
   glVertex2i(500,410);
   glVertex2i(660,600);   
   glEnd();
}
//不使用反混淆绘制宽度为5的直线；启用反混淆后在不同位置绘制相同的直线，比较两者异同。 
void Line3()
{    
            glLineWidth(5);
            glBegin(GL_LINES);
            glVertex2i(500,460);
            glVertex2i(600,280);
            glEnd();


            glLineWidth(5);
            glColor3f(1,0,0);

            //OpenGL实现反走样需要满足两个条件，一是启用混合，二是启用针对几何图元的反走样处理。
            glBlendFunc(GL_ONE,GL_ZERO);//设置混合方法：源颜色和目标颜色，进行颜色透明度等的混合
            glEnable(GL_BLEND); //启用混合
            glEnable (GL_LINE_SMOOTH); //启用几何图元反走样
            glHint (GL_LINE_SMOOTH_HINT, GL_NICEST); //定义反走样的方法
            /* void glHint(GLenum target,GLenum hint); 
            hint定义了反走样的方法
            GL_FASTEST 给出最有效的选择 
            GL_NICEST 给出最高质量的选择 
            GL_DONT_CARE 没有选择
            target定义反走样的对象*/

            glBegin(GL_LINES);
            glVertex2i(500,360);
            glVertex2i(600,180);
            
            glDisable (GL_LINE_SMOOTH); //关闭图元反走样  
            glDisable (GL_BLEND); //关闭混合
            glEnd();
}
void myDisplay()
{


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // 清除颜色缓冲区和深度缓冲区
    //glColor3f (1.0f, 0.0f, 0.0f);//设置前景色（相当于画笔颜色）
    //glLoadIdentity();        // 重置当前模型视图矩阵
    //glTranslate2f(-1.5f,0.0f);        // 向左平移50个单位

    //Triangle();
//    Hex();
    //Point();
    //Line();
    //Line2();    
    Line3();

    glFlush();//强制刷新缓冲，保证绘图命令被立即执行
}

void Init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);//设置平滑颜色过渡模式（相当于在两种颜色间进行差值，想象一下线段的两个端点颜色不一样，线段中间该是什么颜色）
    printf("实验三：OpenGL基本图形绘制\n");//在窗口中给出提示
}

void Reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);//设置视口大小与窗口大小完全一致
    glMatrixMode(GL_PROJECTION);//指定当前矩阵为投影矩阵
    glLoadIdentity();//将投影矩阵初始化为单位矩阵
    gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);//定义二维投影矩阵
}



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Hello World!");
    Init();
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(Reshape);
    glutMainLoop();
}