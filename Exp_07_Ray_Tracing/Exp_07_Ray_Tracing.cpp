// This is [Ray Tracing]! Horryyyyyyyyyyyy! Finally to the modern times!
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
#include <math.h>

#include "Light.h"
#include "Hit.h"
#include "Material.h"
#include "Object3D.h"
#include "Ray.h"
#include "Scene.h"

float max(float x, float y) //返回最大值
{
    if (x >= y)
        return x;
    else
        return y;
}

float min(float x, float y) //返回最小值
{
    if (x <= y)
        return x;
    else
        return y;
}

Color RayTracing(Scene &, Light &, Ray &, int); //光线跟踪

Color RayShading(Scene &s1, Light &light, Object3D *object, int o, Ray &ray,
                 Hit &hit, Vector3 &point, Vector3 &noraml, int depth)
{
    Color color;                                                     //光线的颜色
    Ray rRay, sRay;                                                  //反射光线，阴影光线
    Color rColor;                                                    //折射光线的颜色
    color = light.GetAmbient() * (object->GetMaterial().GetColor()); //获得环境光的颜色
    sRay.SetOrigin(hit.GetPosition());                               //从交点到光源的光线
    sRay.SetDirection(light.GetPosition() - hit.GetPosition());      //设置光线的方向
    //法线与阴影光线点积大于0则是能被光照到的
    if (sRay.GetDirection().Dot(hit.GetNormal()) > 0)
    {
        Hit h;
        if (s1.m_objlist[1 - o]->intersect(sRay, h, h.GetTmin()))
        {
        }
        else
        {
            color += max(((light.GetPosition() - hit.GetPosition()).Normalize()).Dot(hit.GetNormal().Normalize()), 0) * light.GetDiffuse() * (object->GetMaterial().GetColor());
            color += pow(max((((light.GetPosition() - hit.GetPosition()) + (ray.GetOrigin() - hit.GetPosition())).Normalize()).Dot(hit.GetNormal().Normalize()), 0), object->GetMaterial().GetShininess()) * light.GetSpecular() * (object->GetMaterial().GetSpecular()); //镜面光
        }
    }
    if (depth < 4)
    { //如果深度太深则返回
        if (object->GetMaterial().GetReflection() > 0)
        { //景物是反射体
            rRay.SetOrigin(hit.GetPosition());
            Vector3 r, d;
            d = ray.GetDirection();
            r = d + 2 * fabs(d.Dot(hit.GetNormal().Normalize())) * (hit.GetNormal().Normalize());
            rRay.SetDirection(r);
            rColor = RayTracing(s1, light, rRay, depth + 1);
            color += rColor * (object->GetMaterial().GetReflection());
        }
    }
    color.Set(min(color.GetFirst(), 1.0), min(color.GetSecond(), 1.0), min(color.GetThird(), 1.0));
    return color;
}
//光线跟踪
Color RayTracing(Scene &s1, Light &light, Ray &ray, int depth)
{
    Hit hit;
    bool flag[2];
    flag[0] = s1.m_objlist[0]->intersect(ray, hit, hit.GetTmin());
    float t1 = hit.GetTmin();
    flag[1] = s1.m_objlist[1]->intersect(ray, hit, hit.GetTmin());
    float t2 = hit.GetTmin();
    if (flag[0] || flag[1])
    {
        if (flag[0] && !flag[1])
        {
            return RayShading(s1, light, s1.m_objlist[0], 0, ray, hit, hit.GetPosition(), hit.GetNormal(), depth);
        }
        else if (!flag[0] && flag[1])
        {
            return RayShading(s1, light, s1.m_objlist[1], 1, ray, hit, hit.GetPosition(), hit.GetNormal(), depth);
        }
        else
        {
            if (t1 > t2)
                return RayShading(s1, light, s1.m_objlist[1], 1, ray, hit, hit.GetPosition(), hit.GetNormal(), depth);
            else
                return RayShading(s1, light, s1.m_objlist[0], 0, ray, hit, hit.GetPosition(), hit.GetNormal(), depth);
        }
    }
    else
    {
        if (depth == 1)
        {
            return BACKGROUND;
        }
        else
        {
            return RayShading(s1, light, s1.m_objlist[0], 0, ray, hit, hit.GetPosition(), hit.GetNormal(), depth);
        }
    }
}

void my_Display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    Scene s1;
    s1.create_scene(); // 创建场景

    Light light; //创建光线
    light.SetPosition(Vector3(0, 500, -100));
    light.SetAmbient(Vector3(0.1, 0.1, 0.1));
    light.SetDiffuse(Vector3(1.0, 1.0, 1.0));
    light.SetSpecular(Vector3(1.0, 1.0, 1.0));
    Vector3 e(SCRWIDTH / 2, SCRHEIGHT / 2, -200);
    for (int b = 0; b < SCRHEIGHT; b++)
    {
        for (int a = 0; a < SCRWIDTH; a++)
        {
            Vector3 s(a, b, 0); //s是屏幕上的像素点
            Ray ray(e, (s - e));
            hit[a][b].SetColor(RayTracing(s1, light, ray, 1));
        }
    }
    /*对所有屏幕上的像素点遍历*/
    for (int d = 0; d < SCRHEIGHT; d++)
    {
        for (int c = 0; c < SCRWIDTH; c++)
        {
            glColor3f(hit[c][d].GetColor().GetFirst(), hit[c][d].GetColor().GetSecond(), hit[c][d].GetColor().GetThird());
            glBegin(GL_POINTS);
            glVertex2d(c, d); // 中间是点的坐标
            glEnd();
        }
    }

    glFlush();
}

void my_Init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(SCRWIDTH, SCRHEIGHT);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("It's Ray Tracing ! Modern! ");
    my_Init();
    glutDisplayFunc(my_Display);
    glutMainLoop();
    return 0;
}
