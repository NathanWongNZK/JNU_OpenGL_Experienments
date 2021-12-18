
// This is [3D Shadow].
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

#define MAXTEXTURE	4					 								// 定义最大的纹理数目

GLUquadricObj	*quadric;												// 存放二次曲面的物体
GLfloat shadow_matrix[4][4];											// 存放阴影矩阵
const GLfloat P[4] = {0.0f, 1.0f, 0.0f, 2.0f};							// 阴影平面向量

GLfloat planePos[]  = {0.0f,-1.2f, 0.0f};								// 直升飞机的位置

GLfloat lightPos[] = {0.0f, 4.0f,-3.0f, 0.0f};							// 定义光的位置
GLfloat lightAmb[] = {0.8f, 0.8f, 0.8f, 1.0f};							// 定义环境光的颜色
GLfloat lightDif[] = {1.0f, 0.7f, 0.8f, 1.0f};							// 定义漫反射光的颜色
GLfloat lightSpc[] = {0.8f, 1.0f, 1.0f, 1.0f};							// 定义镜面反射光的颜色

GLfloat matAmb[] = {0.4f, 0.4f, 0.4f, 1.0f};							// 材质的环境光颜色
GLfloat matDif[] = {1.0f, 1.0f, 1.0f, 1.0f};							// 材质的漫反射光颜色
GLfloat matSpc[] = {0.0f, 0.0f, 0.0f, 1.0f};							// 材质的镜面反射光颜色
GLfloat matShn[] = {0.0f};								    			// 材质的镜面指数

GLuint	texture[MAXTEXTURE];											// 纹理数组
bool	pKey_space;														// 判断空格键是否按下
GLfloat	angle_X1;														// 控制物体绕X轴转动
GLfloat	angle_Y1;														// 控制物体绕Y轴转动
GLfloat	angle_X2;														// 控制物体绕X轴转动
GLfloat	angle_Y2;														// 控制物体绕Y轴转动
GLfloat	rot_X;															// 物体绕X轴转动的速度
GLfloat	rot_Y;															// 物体绕Y轴转动的速度
GLfloat	rot;															// 直升飞机螺旋桨的转动速度
GLfloat	z=-8.0f;														// 进入平面的深度
GLint	change;															// 控制当前该绘制何种物体

void my_Reshape(int width, int height)								// 重新设置窗口大小
{
	glViewport(0, 0, (GLsizei)(width), (GLsizei)(height));				// 重置当前视口大小
	glMatrixMode(GL_PROJECTION);										// 切换到投影矩阵模式
	glLoadIdentity();													// 重置投影矩阵
	gluPerspective(45, (float)width/(float)height, 0.1, 100);			// 设置透视投影
	glMatrixMode(GL_MODELVIEW);											// 切换到模型视图矩阵
	glLoadIdentity();													// 重置模型视图矩阵
}

AUX_RGBImageRec *LoadImage(char *Filename)								// 加载一个图片
{
	FILE *File = NULL;													// 文件句柄

	if (!Filename)														// 确保文件名已经提供
	{
		return NULL;													// 如果没有则返回NULL
	}

	File = fopen(Filename,"r");											// 检查文件是否存在

	if (File)															// 文件存在吗？
	{
		fclose(File);													// 关闭File文件句柄
		return auxDIBImageLoad(Filename);								// 载入图片并返回其指针
	}

	return NULL;														// 如果加载错误则返回NULL
}

bool LoadTextureGL(void)												// 加载图片并转换为纹理
{
	bool State = false;													// 状态指示

	AUX_RGBImageRec *TextureImage[MAXTEXTURE];							// 为纹理开辟存储空间

	memset(TextureImage, 0, sizeof(void *)*MAXTEXTURE);					// 清除图像记录，确保其内容为空并使指针指向NULL
	// 加载图片并检查是否出错 ，如果图片不存在则返回
	if ((TextureImage[0] = LoadImage("Data/ground1.bmp"))
		&& (TextureImage[1] = LoadImage("Data/ground2.bmp"))
		&& (TextureImage[2] = LoadImage("Data/wood.bmp"))
		&& (TextureImage[3] = LoadImage("Data/plane.bmp")))
	{   
		State=true;														// 设置状态变量为TRUE
		glGenTextures(MAXTEXTURE, &texture[0]);							// 返回唯一的纹理名字来标识纹理,保存在texture中

		// 用图片数据产生纹理
		for (int loop=0; loop<MAXTEXTURE; loop++)						// 循环处理MAXTEXTURE张纹理
		{
			// 使用来自位图数据生成的典型纹理
			glBindTexture(GL_TEXTURE_2D, texture[loop]);
			// 生成纹理 
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[loop]->sizeX, TextureImage[loop]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[loop]->data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// 线形滤波
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// 线形滤波
		}
	}
	for (int loop=0; loop<MAXTEXTURE; loop++)
	{
		if (TextureImage[loop])											// 纹理是否存在	
		{
			if (TextureImage[loop]->data)								// 纹理图像是否存在
			{
				free(TextureImage[loop]->data);							// 释放纹理存储空间
			}
			free(TextureImage[loop]);									// 释放图像结构
		}
	}
	return State;														// 返回State
}

// 计算阴影矩阵
void generate_shadow_matrix(GLfloat matrix[4][4], const GLfloat ground[4], const GLfloat light[4])
{
	GLfloat dot = 0;
	int i, j;
	for(i = 0; i < 4; i++)
		dot += ground[i] * light[i];
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			if(i == j)
				matrix[i][j] = dot - ground[i] * light[j];
			else
				matrix[i][j] = - ground[i] * light[j];
}

// 绘制直升飞机
void DrawPlane()
{
	// 绘制直升飞机机头
	glPushMatrix();
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -1.5f);
		gluCylinder(quadric, 1.0f, 0.6f, 0.8f, 32, 32);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(1.9f, -2.3f, 0.0f);
		gluSphere(quadric, 0.3f, 32, 32);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-7.0f, -1.5f, 0.0f);
		gluSphere(quadric, 0.2f, 32, 32);
	glPopMatrix();

	glTranslatef(0.0f, -1.5f, 0.0f);
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
	    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.3f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.01f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0.01f, 0.8f, 0.6f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 0.8f, 0.6f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.3f, 0.0f,-1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.01f, 0.0f,-1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0.01f, 0.8f,-0.6f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 0.8f,-0.6f);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.3f, 0.0f,-1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.3f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.0f, 0.8f, 0.6f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 0.8f,-0.6f);
		glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.3f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.3f,-1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f,-1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f, 0.0f, 1.0f);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.3f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.3f,-1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f,-1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f, 0.0f, -1.0f);
	    glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.3f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.3f,-1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.3f,0.0f,   1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.3f,-1.0f,  1.0f);
	glEnd();
    glPushMatrix();
	    glTranslatef(1.0f, -0.8f, 0.0f);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	    gluCylinder(quadric, 1.0f, 0.2f, 1.1f, 32, 32);
    glPopMatrix();
    glPushMatrix();
	    glTranslatef(1.0f, -0.8f, 0.0f); 
	    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		gluCylinder(quadric, 1.0f, 1.0f, 3.0f, 32, 32);
	glPopMatrix();
	glPushMatrix();	
	    glTranslatef(-2.0f, -0.8f, 0.0f);
	    gluSphere(quadric, 1.0f, 32, 32);
	glPopMatrix();
	// 直升机机头绘制完成

	// 绘制直升机机尾
	glPushMatrix();
        glTranslatef(-2.8f, -0.5f, 0.0f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(-7.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadric, 0.3f, 0.2f, 4.3f, 32, 32);
    glPopMatrix();
	// 绘制机尾翘起部分
	glPushMatrix();
		glTranslatef(-2.8f, -0.5f, 0.0f);
     	glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, 1.5f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-4.0f, 0.5f, 0.2f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-3.4f, 0.5f, 0.2f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-4.4f, 1.5f, 0.0f);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, 1.5f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-4.0f, 0.5f,-0.2f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-3.4f, 0.5f,-0.2f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-4.4f, 1.5f, 0.0f);
		glEnd();
        glBegin(GL_TRIANGLES);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-4.0f, 0.5f, 0.2f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, 1.5f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-4.0f, 0.5f,-0.2f);
		glEnd();
    glPopMatrix();
	// 直升机机尾绘制完成

	// 绘制飞机螺旋桨
	// 绘制螺旋桨支柱
	glPushMatrix();
		glTranslatef(-0.5, 0.0f, 0.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadric, 0.2f, 0.2f,1.5f, 32, 32);
	glPopMatrix();
	// 绘制螺旋桨叶片
	glPushMatrix();
		glTranslatef(-0.5f, 0.0f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(angle_X2, 0.0f, 1.0f, 0.0f);//旋转飞机螺旋桨叶片 
		glPushMatrix();
			glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 1.0f, 0.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, 1.5f, 0.3f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f, 1.5f, 0.3f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f, 1.5f,-0.3f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, 1.5f,-0.3f);
			glEnd();
		glPopMatrix();

		glPushMatrix();
			glRotatef(150.0f, 0.0f, 1.0f, 0.0f);
			glBegin(GL_QUADS);
				glNormal3f(0.0f,1.0f, 0.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, 1.5f, 0.3f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f, 1.5f, 0.3f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f, 1.5f,-0.3f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, 1.5f,-0.3f);
			glEnd();
		glPopMatrix();

		glPushMatrix();
			glRotatef(270.0f, 0.0f, 1.0f, 0.0f);
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, 1.5f, 0.3f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f, 1.5f, 0.3f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f, 1.5f,-0.3f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, 1.5f,-0.3f);
			glEnd();
		glPopMatrix();
	glPopMatrix();
	// 直升机螺旋桨绘制完成

	// 绘制直升机底座
	// 绘制底座4个支柱
	glPushMatrix();
		glTranslatef(0.8f, 0.0f, -0.4f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadric, 0.1f, 0.1f, 2.3f, 32, 32);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.8f, 0.0f, 0.4f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadric, 0.1f, 0.1f, 2.3f, 32, 32);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.0f, 0.0f, -0.4f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadric, 0.1f, 0.1f, 2.3f, 32, 32);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.0f, 0.0f, 0.4f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadric, 0.1f, 0.1f, 2.3f, 32, 32);
	glPopMatrix();
	// 绘制底座的底板
	glTranslatef(0.0f, -3.75f, 0.4f);
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 1.5f, 0.15f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 1.5f, 0.15f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.5f,-0.15f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 1.5f,-0.15f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 1.5f,-0.75f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 1.5f,-0.75f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.5f,-0.95f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 1.5f,-0.95f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f, 1.7f, 0.15f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f, 1.5f, 0.15f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.0f, 1.5f,-0.15f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5f, 1.7f,-0.15f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.5f, 1.7f, 0.15f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5f, 1.7f,-0.15f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.5f,-0.15f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.5f, 0.15f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f, 1.7f,-0.75f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f, 1.5f,-0.75f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.0f, 1.5f,-0.95f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5f, 1.7f,-0.95f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.5f,  1.7f,-0.75f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5f,  1.7f,-0.95f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,  1.5f,-0.95f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,  1.5f,-0.75f);
	glEnd();
	// 直升机底座绘制完成
}

//绘制长方体width，height，depth分别为长方体的长，高和深度
void DrawCube(GLfloat width, GLfloat height, GLfloat depth)
{
	GLfloat x = width/2, y = height/2, z = depth/2;
	glBegin(GL_QUADS);													// 绘制长方体的各面
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-x,-y, z);					// 前面四边形的左下顶点（正视）
		glTexCoord2f(0.0f, 1.0f); glVertex3f( x,-y, z);					// 前面四边形的右下顶点
		glTexCoord2f(1.0f, 1.0f); glVertex3f( x, y, z);					// 前面四边形的右上顶点
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-x, y, z);					// 前面四边形的左上顶点
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( x,-y,-z);					// 后面四边形的左下顶点（正视）
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-x,-y,-z);					// 后面四边形的右下顶点
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-x, y,-z);					// 后面四边形的右上顶点
		glTexCoord2f(1.0f, 0.0f); glVertex3f( x, y,-z);					// 后面四边形的左上顶点
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( x,-y, z);					// 右侧面四边形的左下顶点（正视）
		glTexCoord2f(0.0f, 1.0f); glVertex3f( x,-y,-z);					// 右侧面四边形的右下顶点
		glTexCoord2f(1.0f, 1.0f); glVertex3f( x, y,-z);					// 右侧面四边形的右上顶点
		glTexCoord2f(1.0f, 0.0f); glVertex3f( x, y, z);					// 右侧面四边形的左上顶点
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-x,-y,-z);					// 左侧面四边形的左下顶点（正视）
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-x,-y, z);					// 左侧面四边形的右下顶点
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-x, y, z);					// 左侧面四边形的右上顶点
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-x, y,-z);					// 左侧面四边形的左上顶点
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, y, z);					// 顶面四边形的左下顶点（正视）
		glTexCoord2f(0.0f, 1.0f); glVertex3f( x, y, z);					// 顶面四边形的右下顶点
		glTexCoord2f(1.0f, 1.0f); glVertex3f( x, y,-z);					// 顶面四边形的右上顶点
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-x, y,-z);					// 顶面四边形的左上顶点
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-x,-y,-z);					// 底面四边形的左下顶点（正视）
		glTexCoord2f(0.0f, 1.0f); glVertex3f( x,-y,-z);					// 底面四边形的右下顶点
		glTexCoord2f(1.0f, 1.0f); glVertex3f( x,-y, z);					// 底面四边形的右上顶点
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-x,-y, z);					// 底面四边形的左上顶点
	glEnd();
}

void my_Init()							// 用户绘制场景相关的函数在此处定义	
{
	// 在此处初始化绘制场景
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);								// 清屏为黑色
	glClearDepth(1.0f);													// 设置深度缓存
	glDepthFunc(GL_LEQUAL);												// 选择深度测试方式
	glEnable(GL_DEPTH_TEST);											// 开启深度测试
	glShadeModel(GL_SMOOTH);											// 阴暗处理采用平滑方式
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);					// 最精细的透视计算	
	
	LoadTextureGL();

	glEnable(GL_TEXTURE_2D);											// 开启2D纹理映射
	
	quadric = gluNewQuadric();											// 建立一个曲面对象指针
    gluQuadricTexture(quadric, GLU_TRUE);								// 建立纹理坐标
    gluQuadricDrawStyle(quadric, GLU_FILL);								// 用面填充
	
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);						// 绘制光源1
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);							// 设置光源1的环境光
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDif);							// 设置光源1的漫反射光
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpc);						// 设置光源1的镜面反射光
	glEnable(GL_LIGHT1);												// 启用光源1

	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);							// 设置材质的环境光
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif);							// 设置材质的漫反射光
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpc);						// 设置材质的镜面反射光
	glMaterialfv(GL_FRONT, GL_SHININESS, matShn);						// 设置材质的镜面指数

}

void my_Display()												// 绘制场景
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);					// 清除颜色和深度缓存
	glLoadIdentity();													// 重置当前矩阵
	//在此处添加代码进行绘制:
	glTranslatef(0.0f, 0.0f, z);										// 移入屏幕z

	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);						// 光源1的位置
	glEnable(GL_LIGHTING);												// 启用光照
	glEnable(GL_TEXTURE_2D);											// 启用纹理贴图

	if (change == 0)													// 若change等于0选择并绑定第一张纹理
	{
		glBindTexture(GL_TEXTURE_2D, texture[0]);
	}
	else																// 若change等于1选择并绑定第二张纹理
	{
		glBindTexture(GL_TEXTURE_2D, texture[1]);
	}
	glBegin(GL_QUADS);													// 绘制阴影平面	
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 8.0f, -2.0f, -16.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-8.0f, -2.0f, -16.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-8.0f, -2.0f,  16.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 8.0f, -2.0f,  16.0f);
	glEnd();

	// change等于0时绘制十字架
	if (change == 0)
	{
		glPushMatrix();													// 将当前矩阵推入栈中
			glBindTexture(GL_TEXTURE_2D, texture[2]);					// 选择并绑定第三张纹理
			glRotatef(angle_X1, 1.0f, 0.0f, 0.0f);						// 让十字架绕X轴转动
			glRotatef(angle_Y1, 0.0f, 1.0f, 0.0f);						// 让十字架绕Y轴转动
			// 绘制十字架
			DrawCube(2.0f, 0.2f, 0.2f);
			DrawCube(0.2f, 2.0f, 0.2f);
			DrawCube(0.2f, 0.2f, 2.0f);
		glPopMatrix();													// 恢复矩阵

		glPushMatrix();													// 将当前矩阵推入栈中
			glDisable(GL_LIGHTING);										// 关闭光源
			glDisable(GL_TEXTURE_2D);									// 禁用纹理
			glColor3f(0.0f, 0.0f, 0.0f);								// 设置阴影颜色
			glTranslatef(0.0f, 0.01f, 0.0f);
			// 调用generate_shadow_matrix()函数计算阴影矩阵并与当前矩阵相乘，得到绘制阴影的矩阵
			generate_shadow_matrix(shadow_matrix, P, lightPos);
			glMatrixMode(GL_MODELVIEW);	
			glMultMatrixf((GLfloat*) shadow_matrix);
			// 让阴影跟随实际物体一起运动
			glRotatef(angle_X1, 1.0f, 0.0f, 0.0f);
			glRotatef(angle_Y1, 0.0f, 1.0f, 0.0f);
			// 绘制阴影十字架
			DrawCube(2.0f, 0.2f, 0.2f);
			DrawCube(0.2f, 2.0f, 0.2f);
			DrawCube(0.2f, 0.2f, 2.0f);
		glPopMatrix();													// 恢复矩阵

		angle_X1 += rot_X;
		angle_Y1 += rot_Y;
	}
	// change等于1时绘制直升飞机
	if (change == 1)
	{	
		glPushMatrix();													// 将当前矩阵推入栈中
			glBindTexture(GL_TEXTURE_2D, texture[3]);					// 选择并绑定第四张纹理
			glRotatef(angle_Y2, 0.0f, 1.0f, 0.0f);						// 改变直升飞机前进的方向
			glTranslatef(planePos[0], planePos[1], planePos[2]);
			glScalef(0.2f, 0.2f, 0.2f);
			DrawPlane();												// 绘制直升飞机
		glPopMatrix();													// 恢复矩阵

		glPushMatrix();													// 将当前矩阵推入栈中
			glDisable(GL_LIGHTING);										// 关闭光源
			glDisable(GL_TEXTURE_2D);									// 禁用纹理
			glColor3f(0.0f, 0.0f, 0.0f);								// 设置阴影颜色
			glTranslatef(0.0f, 0.01f, 0.0f);
			// 调用generate_shadow_matrix()函数计算阴影矩阵并与当前矩阵相乘，得到绘制阴影的矩阵
			generate_shadow_matrix(shadow_matrix, P, lightPos);
			glMatrixMode(GL_MODELVIEW);
			glMultMatrixf((GLfloat*) shadow_matrix);
			// 让阴影跟随实际物体一起运动
			glRotatef(angle_Y2, 0.0f, 1.0f, 0.0f);
			glTranslatef(planePos[0], planePos[1], planePos[2]);
			glScalef(0.2f, 0.2f, 0.2f);
			DrawPlane();												// 绘制直升飞机
		glPopMatrix();													// 恢复矩阵

		// 若直升飞机已到地面，控制螺旋桨停下;否则加速
		if (planePos[1] <= -1.0 && rot != 0)
		{  
			rot -= 0.5f;
			angle_X2 += rot;
		}
		else
		{
			angle_X2 += rot;
		}
	}

	// 绘制一个模拟光源，表示光射来的方向
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glColor3f(1.0f, 1.0f, 0.0f);
		glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
		gluSphere(quadric, 0.1f, 32, 16);
	glPopMatrix();

	glFlush();															// 刷新GL命令队列
    glutSwapBuffers();
}

void my_Keyboard(unsigned char key, int x, int y)														// 在此处更新对消息的动作
{
    switch (key)
    {
    case 'd':
    	lightPos[0] += 0.05f;
        break;
    case 'a':
    	lightPos[0] -= 0.05f;
        break;
    case 'w':
        lightPos[1] += 0.05f;
        break;
    case 's':
    	lightPos[1] -= 0.05f;
        break;

    case 'q':
        lightPos[2] += 0.05f;
        break; 

    case 'e':
        lightPos[2] -= 0.05f;
        break;   
    case 91:    // '['
        z += 0.5f;
        break;
    case 93:    // ']'
        z -= 0.5f;
        break;
    /* case GLUT_KEY_DOWN:
        planePos[1] -= 0.05f;
        break;
    case GLUT_KEY_UP:
    	planePos[1] += 0.05f;
        break;
    case GLUT_KEY_RIGHT:
        planePos[0] += 0.05f;
        break;
    case GLUT_KEY_LEFT:
        planePos[0] -= 0.05f;
        break; */
    default:
        break;
    }
    glutPostRedisplay();  
    /*
	// 改变飞机的位置
	
	// 控制螺旋桨的速度
	if (OGL_keys->keyDown[VK_UP] == TRUE)								// UP键是否按下
	{
		rot += 0.5f;
	}
	// 若planePos[1]>=-1.0f则可以改变直升飞机前进的方向
	if (OGL_keys->keyDown[VK_NUMPAD4] == TRUE && planePos[1]>=-1.0f)	// 数字键4是否按下
	{
		angle_Y2 -= 0.5;
	}
	if (OGL_keys->keyDown[VK_NUMPAD6] == TRUE && planePos[1]>=-1.0f)	// 数字键6是否按下
	{
		angle_Y2 += 0.5;
	}

	// 控制十字架的旋转
	if (OGL_keys->keyDown[VK_UP] == TRUE)								// UP键是否按下
	{
		rot_X -= 0.5;
	}
	if (OGL_keys->keyDown[VK_DOWN] == TRUE)								// DOWN键是否按下
	{
		rot_X += 0.5;
	}
	if (OGL_keys->keyDown[VK_LEFT] == TRUE)								// LEFT键是否按下
	{
		rot_Y -= 0.5;
	}
	if (OGL_keys->keyDown[VK_RIGHT] == TRUE)							// RIGHT键是否按下
	{
		rot_Y += 0.5;
	}

	if (OGL_keys->keyDown[VK_SPACE] == TRUE && !pKey_space)				// 空格键是否按下
	{
		// 若空格键按下，则改变change的值并初始化下列各值
		pKey_space = TRUE;
		z = -8.0f;
		change += 1;
		change = change % 2;
		angle_X1 = 0;
		angle_Y1 = 0;
		angle_X2 = 0;
		angle_Y2 = 0;
		rot = 0;
		rot_X = 0;
		rot_Y = 0;
		planePos[0] = 0.0f;
		planePos[1] = -1.2f;
		planePos[2] = 0.0f;
	}
	if (OGL_keys->keyDown[VK_SPACE] == FALSE)							// 空格键是否放开
	{
		pKey_space = FALSE;
	}
    */
}

void my_TimerFunc(int val)
{
    glutPostRedisplay();
    glutTimerFunc(100, my_TimerFunc, 1);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(800, 600);
    glutCreateWindow("It's the 3D Shadow !");

    my_Init();
    glutDisplayFunc(my_Display);
    glutReshapeFunc(my_Reshape);
    glutKeyboardFunc(my_Keyboard);
    glutTimerFunc(100, my_TimerFunc, 1);
    glutMainLoop();
}
