// This is [3D Modeling].
#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <iostream>

void my_Reshape(int width, int height)								// 重新设置窗口大小
{
	glViewport(0, 0, (GLsizei)(width), (GLsizei)(height));				// 重置当前视口大小
	glMatrixMode(GL_PROJECTION);										// 切换到投影矩阵模式
	glLoadIdentity();													// 重置投影矩阵
	gluPerspective(45, (float)width/(float)height, 0.1, 100);			// 设置透视投影
	glMatrixMode(GL_MODELVIEW);											// 切换到模型视图矩阵
	glLoadIdentity();													// 重置模型视图矩阵
}

// 绘制长方体 width，height，depth分别为长方体的长，高和深度
void DrawCube(GLfloat width, GLfloat height ,GLfloat depth)
{
	GLfloat x = width/2, y = height/2, z = depth/2;
	glBegin(GL_QUADS);													// 绘制长方体的各面
		// 前面(front)
		glColor3f(0.5f, 1.0f, 0.5f);									// 设置当前颜色（各对面颜色相同）
		glVertex3f(-x, -y, z);											// 前面四边形的左下顶点（正视）
		glVertex3f( x, -y, z);											// 前面四边形的右下顶点
		glVertex3f( x,  y, z);											// 前面四边形的右上顶点
		glVertex3f(-x,  y, z);											// 前面四边形的左上顶点
		// 背面(back)
		glVertex3f( x, -y, -z);											// 背面四边形的左下顶点（正视）
		glVertex3f(-x, -y, -z);											// 背面四边形的右下顶点
		glVertex3f(-x,  y, -z);											// 背面四边形的右上顶点
		glVertex3f( x,  y, -z);											// 背面四边形的左上顶点
		
		// 右侧面(right)
		glColor3f(0.2f, 0.4f, 0.1f);
		glVertex3f( x, -y,  z);											// 右侧面四边形的左下顶点（正视）
		glVertex3f( x, -y, -z);											// 右侧面四边形的右下顶点
		glVertex3f( x,  y, -z);											// 右侧面四边形的右上顶点
		glVertex3f( x,  y,  z);											// 右侧面四边形的左上顶点
		// 左侧面(left)
		glVertex3f(-x, -y, -z);											// 左侧面四边形的左下顶点（正视）
		glVertex3f(-x, -y,  z);											// 左侧面四边形的右下顶点
		glVertex3f(-x,  y,  z);											// 左侧面四边形的右上顶点
		glVertex3f(-x,  y, -z);											// 左侧面四边形的左上顶点

		// 顶面(top)
		glColor3f(0.2f, 0.8f, 0.0f);
		glVertex3f(-x,  y,  z);											// 顶面四边形的左下顶点（正视）
		glVertex3f( x,  y,  z);											// 顶面四边形的右下顶点
		glVertex3f( x,  y, -z);											// 顶面四边形的右上顶点
		glVertex3f(-x,  y, -z);											// 顶面四边形的左上顶点
		// 底面(bottom)
		glVertex3f(-x, -y, -z);											// 底面四边形的左下顶点（正视）
		glVertex3f( x, -y, -z);											// 底面四边形的右下顶点
		glVertex3f( x, -y,  z);											// 底面四边形的右上顶点
		glVertex3f(-x, -y,  z);											// 底面四边形的左上顶点
	glEnd();
}

void my_Init()
{
	// 在此处初始化绘制场景
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);								// 清屏为黑色
	glClearDepth(1.0f);													// 设置深度缓存
	glDepthFunc(GL_LEQUAL);												// 选择深度测试方式
	glEnable(GL_DEPTH_TEST);											// 开启深度测试
	glShadeModel(GL_SMOOTH);											// 阴暗处理采用平滑方式
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);					// 最精细的透视计算	
}

void my_Display(void)													// 绘制场景
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);					// 清除场景和深度缓存
	glLoadIdentity();													// 重置当前矩阵
	// 在此处添加代码进行绘制:
	glTranslatef(-2.0f, 0.0f,-8.0f);									// 左移2.0f，并移入屏幕8.0f

	// 绘制金字塔
	glBegin(GL_TRIANGLES);												// 开始绘制金字塔各面的三角形
		// 正面
		glColor3ub(217,167,22);											// 设置当前颜色（土黄色）
		glVertex3f( 0.0f, 1.0f, 0.0f);									// 前面三角形的顶点（正视）
		glVertex3f(-1.0f,-1.0f, 1.0f);									// 前面三角形的左下顶点
		glVertex3f( 1.0f,-1.0f, 1.0f);									// 前面三角形的右下顶点
		// 背面
		glVertex3f( 0.0f, 1.0f, 0.0f);									// 后面三角形的顶点（正视）
		glVertex3f( 1.0f,-1.0f,-1.0f);									// 后面三角形的左下顶点
		glVertex3f(-1.0f,-1.0f,-1.0f);									// 后面三角形的右下顶点
		// 右侧面
		glColor3ub(217,122,0);											// 设置当前颜色		 
		glVertex3f( 0.0f, 1.0f, 0.0f);									// 右边三角形的顶点（正视）
		glVertex3f( 1.0f,-1.0f, 1.0f);									// 右边三角形的左下顶点
		glVertex3f( 1.0f,-1.0f,-1.0f);									// 右边三角形的右下顶点
		// 左侧面
		glVertex3f( 0.0f, 1.0f, 0.0f);									// 左边三角形的顶点（正视）
		glVertex3f(-1.0f,-1.0f,-1.0f);									// 左边三角形的左下顶点
		glVertex3f(-1.0f,-1.0f, 1.0f);									// 左边三角形的右下顶点
	glEnd();															// 金字塔各侧面绘制结束
	// 底面为四边形
	glBegin(GL_QUADS);													// 绘制底面四边形（不改变颜色）
		glVertex3f(-1.0f,-1.0f,-1.0f);									// 底面四边形的左下顶点（正视）
		glVertex3f( 1.0f,-1.0f,-1.0f);									// 底面四边形的右下顶点
		glVertex3f( 1.0f,-1.0f, 1.0f);									// 底面四边形的右上顶点
		glVertex3f(-1.0f,-1.0f, 1.0f);									// 底面四边形的左上顶点
	glEnd();															// 底面绘制结束
	// 金字塔绘制结束

	// 绘制十字架
	glTranslatef(4.0f, 0.0f, 0.0f);										// 往右移4.0f
	glRotatef(10.0f, 0.0f, 1.0f, 0.0f);									// 绕Y轴逆时针旋转10度
	DrawCube(2.0f, 0.2f, 0.2f);											// 绘制一个长方体
	DrawCube(0.2f, 2.0f, 0.2f);											// 绘制另一个长方体
	
	// 用aux库绘制十字架	
	//glTranslatef(4.0f, 0.0f, 0.0f);									// 往右移4.0f
	//glRotatef(10.0f, 0.0f, 1.0f, 0.0f);								// 绕Y轴逆时针旋转10度
	//glColor3f(0.0f, 1.0f, 0.0f);										// 设置颜色为绿色
	//auxSolidBox(2.0f, 0.2f, 0.2f);									// 绘制一个长方体
	//auxSolidBox(0.2f, 2.0f, 0.2f);									// 绘制另一个长方体

	// 绘制结束
	glFlush ();															// 刷新GL命令队列
    glutSwapBuffers();
}

void my_TimerFunc(int val)
{
    glutPostRedisplay();
    glutTimerFunc(100, my_TimerFunc, 1);
}

void my_Keyboard(unsigned char key, int x, int y)               // 在此处更新对消息的动作
{
    switch (key)
    {
    case 'q':
        exit(0);
        glutPostRedisplay();
        break;

    default:
        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(800, 600);
    glutCreateWindow("It's the 3D Modeling !");

    my_Init();
    glutDisplayFunc(my_Display);
    glutReshapeFunc(my_Reshape);
    glutKeyboardFunc(my_Keyboard);
    glutTimerFunc(100, my_TimerFunc, 1);
    glutMainLoop();
}
