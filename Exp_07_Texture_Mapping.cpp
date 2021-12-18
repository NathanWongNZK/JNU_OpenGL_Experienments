/*----------------------------------------------------------------------------------------------------
题目：3D阴影显示、3D造型、纹理映射和光线跟踪

1.实验目的：要求是做3D阴影显示、3D造型、纹理映射和光线跟踪或 碰撞检测， 
          其中对3D阴影显示、3D造型、纹理映射和光线跟踪的要求是：
(1) 多种形状物体，Ball, box等
(2) 包含多种材质物体：纯镜面反射、透明物体、纯漫反射、半透明物体等
(3) Moving in a 3D world
(4) Environment texture

2.实验内容：根据我提高的代码作为参考来写，当然不限于我提供的代码

----------------------------------------------------------------------------------------------------*/

// This one should be texture mapping.
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

#define BPP 16     // 定义每象素的位数
#define MAXTEXTURE 2

GLfloat angle;              // 控制物体的旋转角度
GLuint texture[MAXTEXTURE]; // 纹理数组，保存纹理名称

void my_Reshape(int width, int height) // 重新设置窗口大小
{
    glViewport(0, 0, (GLsizei)(width), (GLsizei)(height));      // 重置当前视口大小
    glMatrixMode(GL_PROJECTION);                                // 切换到投影矩阵模式
    glLoadIdentity();                                           // 重置投影矩阵
    gluPerspective(45, (float)width / (float)height, 0.1, 100); // 设置透视投影
    glMatrixMode(GL_MODELVIEW);                                 // 切换到模型视图矩阵
    glLoadIdentity();                                           // 重置模型视图矩阵
}

GLuint LoadTexture(const char *filename)
{ 
    GLuint texture;
    int width, height;
    unsigned char *data;

    FILE *file;
    file = fopen(filename, "rb");

    if (file == NULL)
        return 0;
    width = 1024;
    height = 512;
    data = (unsigned char *)malloc(width * height * 3);
    //int size = fseek(file,);
    fread(data, width * height * 3, 1, file);
    fclose(file);

    for (int i = 0; i < width * height; ++i)
    {
        int index = i * 3;
        unsigned char B, R;
        B = data[index];
        R = data[index + 2];

        data[index] = R;
        data[index + 2] = B;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);

    return texture;
}   

void my_Init() // 用户绘制场景相关的函数在此处定义
{
    // 在此处初始化绘制场景
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);              // 清屏为黑色
    glClearDepth(1.0f);                                // 设置深度缓存
    glDepthFunc(GL_LEQUAL);                            // 选择深度测试方式
    glEnable(GL_DEPTH_TEST);                           // 开启深度测试
    glShadeModel(GL_SMOOTH);                           // 阴暗处理采用平滑方式
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // 最精细的透视计算

    texture[0] = LoadTexture("Data/Egypt.bmp");
    texture[1] = LoadTexture("Data/Pyramid.bmp");

    glEnable(GL_TEXTURE_2D); // 开启2D纹理映射

}

void my_Display() // 绘制场景
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除颜色和深度缓存
    glLoadIdentity();                                   // 重置当前矩阵
    // 在此处添加代码进行绘制:

    glTranslatef(-2.0f, 0.0f, -8.0f); // 左移2.0f，并移入屏幕8.0f
    // 绘制四边形并贴图
    glBindTexture(GL_TEXTURE_2D, texture[0]); // 选择并绑定第一张纹理
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.5f, -1.0f, 0.0f); // 纹理和底面四边形的左下顶点（正视）
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.5f, -1.0f, 0.0f); // 纹理和底面四边形的右下顶点
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.5f, 1.0f, 0.0f); // 纹理和底面四边形的右上顶点
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.5f, 1.0f, 0.0f); // 纹理和底面四边形的左上顶点
    glEnd();

    // 绘制旋转的金字塔
    glLoadIdentity();                         // 重置当前矩阵
    glTranslatef(2.0f, 0.0f, -8.0f);          // 右移2.0f，并移入屏幕8.0f
    glRotatef(angle, 0.0f, 1.0f, 0.0f);       // 绕Y轴旋转angle度
    angle += 1.0f;                            // 增加逆时针旋转角度
    glBindTexture(GL_TEXTURE_2D, texture[1]); // 选择并绑定第二张纹理

    glBegin(GL_TRIANGLES); // 开始绘制金字塔各面的三角形
    glTexCoord2f(0.5f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f); // 上顶点（正视）
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f); // 左下顶点
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f); // 右下顶点
    // 右侧面
    glTexCoord2f(0.5f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f); // 上顶点（正视）
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f); // 左下顶点
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f); // 右下顶点
    // 背面
    glTexCoord2f(0.5f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f); // 上顶点（正视）
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f); // 左下顶点
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f); // 右下顶点
    // 左侧面
    glTexCoord2f(0.5f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f); // 上顶点（正视）
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f); // 左下顶点
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f); // 右下顶点
    glEnd();
    // 底面
    glBegin(GL_QUADS); // 绘制底面四边形
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f); // 左下顶点（正视）
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f); // 右下顶点
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f); // 右上顶点
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f); // 左上顶点
    glEnd();
    // 金字塔绘制结束

    glFlush();
    glutSwapBuffers();
}

void my_TimerFunc(int val)
{
    glutPostRedisplay();
    glutTimerFunc(50, my_TimerFunc, 1);
}

void my_Keyboard(unsigned char key, int x, int y) // 在此处更新对消息的动作
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
    glutCreateWindow("It's the Texture Mapping !");

    my_Init();
    glutDisplayFunc(my_Display);
    glutReshapeFunc(my_Reshape);
    glutKeyboardFunc(my_Keyboard);
    //glutTimerFunc(50, my_TimerFunc, 1);
    glutMainLoop();
}

