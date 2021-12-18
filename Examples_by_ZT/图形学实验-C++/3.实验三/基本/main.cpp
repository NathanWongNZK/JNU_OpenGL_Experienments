#include <GL/glut.h>
#include <stdlib.h>
GLfloat   rtri;//金字塔旋转角度

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
       glTranslatef(-1.5f,0.0f,-6.0f);
       glRotatef(rtri,0.0f,1.0f,0.0f);
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
 
       
       rtri+=0.1f;//加一个角度
       glutSwapBuffers();//交换双缓存
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
       glutIdleFunc(display);//设置空闲时调用的函数
       glutMainLoop();
       return 0;
}