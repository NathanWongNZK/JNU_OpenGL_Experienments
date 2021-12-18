#include <GL/glut.h>
#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<windows.h>
using namespace std;
float   rtri;//金字塔旋转角度
float speed=0.1;

float mouseX, mouseY;
void init(void) 
{
       glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
       glShadeModel(GL_SMOOTH);//设为smooth处理方式，注意看区别
       glEnable(GL_DEPTH_TEST);//激活深度测试
}

 
void display(void)
{
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    //清除颜色缓存和深度缓存
       glLoadIdentity();
       glTranslatef(-1.5f,0.0f,-6.0f);//请尝试修改此函数，掌握其用法与参数含义
       glRotatef(rtri,0.0f,1.0f,0.0f);//请尝试修改此函数，掌握其用法与参数含义
       glBegin(GL_TRIANGLES);
              glColor3f(1.0f,0.0f,0.0f);
              glVertex3f( 0.0f, 1.0f, 0.0f);
              glColor3f(0.0f,1.0f,0.0f);
              glVertex3f(-1.0f,-1.0f, 1.0f);
              glColor3f(0.0f,0.0f,1.0f);
              glVertex3f( 1.0f,-1.0f, 1.0f);

              glColor3f(1.0f,0.0f,0.0f);
              glVertex3f( 0.0f, 1.0f, 0.0f);
              glColor3f(0.0f,0.0f,1.0f);
              glVertex3f( 1.0f,-1.0f, 1.0f);
              glColor3f(0.0f,1.0f,0.0f);
              glVertex3f( 1.0f,-1.0f, -1.0f);

              glColor3f(1.0f,0.0f,0.0f);
              glVertex3f( 0.0f, 1.0f, 0.0f);
              glColor3f(0.0f,1.0f,0.0f);
              glVertex3f( 1.0f,-1.0f, -1.0f);
              glColor3f(0.0f,0.0f,1.0f);
              glVertex3f(-1.0f,-1.0f, -1.0f);

              glColor3f(1.0f,0.0f,0.0f);
              glVertex3f( 0.0f, 1.0f, 0.0f);
              glColor3f(0.0f,0.0f,1.0f);
              glVertex3f(-1.0f,-1.0f,-1.0f);
              glColor3f(0.0f,1.0f,0.0f);
              glVertex3f(-1.0f,-1.0f, 1.0f);
       glEnd();
 
       
       rtri+=speed;;//加一个角度
       glutSwapBuffers();//交换双缓存
}
 
 void mouse(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON)
	{
		 speed=min(1.0,speed+0.1);//加一个角度
	}
	else if(button == GLUT_RIGHT_BUTTON)
	speed=max(0.1,speed-0.1);
} 
void reshape (int width, int height)
{
       glViewport(0, 0, width, height); 
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();
}
 
void keyboard(unsigned char key, int x, int y)
{//考虑添加键盘命令，交互式控制金字塔的旋转
       switch (key)
       {
              case 'x':
                     exit(0);
                     break;
              default:
                     break;
   }
}

int main(int argc, char** argv)
{
       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//使用双缓存模式和深度缓存
       glutInitWindowSize(640, 480); 
       glutInitWindowPosition(100, 100);
       glutCreateWindow("Transform2");
       init();
       glutDisplayFunc(display); 
       glutReshapeFunc(reshape);
       glutKeyboardFunc(keyboard);
       glutIdleFunc(display);//设置空闲时调用的函数
	   glutMouseFunc(mouse);
       //glutMotionFunc(mouseMotionCB);
       glutMainLoop();
       return 0;
}
