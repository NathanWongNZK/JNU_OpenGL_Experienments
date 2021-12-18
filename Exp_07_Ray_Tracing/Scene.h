// Scene.h: interface for the Scene class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCENE_H__1BB16233_561A_4D63_BA15_8FE397FA36DF__INCLUDED_)
#define AFX_SCENE_H__1BB16233_561A_4D63_BA15_8FE397FA36DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include <vector>
//#include "glut.h"
#include "ray.h"
//#define TRACE_DEPTH 1
//using namespace std;
#include "Sphere.h"
class Scene{
public:

//	bool load_scene(char*);
   void create_scene();  //创建场景
	int m_nObject;       //场景中物体的个数
	Object3D *m_objlist[2];//场景物体的数组
	Material *m_matlist[2];//材料数组
};
void Scene::create_scene(){
		m_nObject=2;     //两个物体
		Color m_c1,m_c2; //两种颜色
		m_c1.Set(0,0,1);  //设置物体1的颜色
		m_c2.Set(1,1,0);  //设置物体2的颜色

		Material m_material1,m_material2;  //两个物体的材料
		m_material1.SetColor(m_c1);  //设置材料1的颜色
		m_material1.SetShininess(100); //设置材料1的镜面指数
		m_material1.SetDiffuse(0.8);   //设置材料1的漫反射系数
		m_material1.SetSpecular(0.5);  //设置材料1的镜面指数
		m_material1.SetReflection(0.3);//设置材料1的影像
		m_matlist[0]=&m_material1;     // 把材料2放到数组中

		m_material2.SetColor(m_c2);//设置材料2的颜色
		m_material2.SetShininess(100);//设置材料2的镜面指数
		m_material2.SetDiffuse(0.8);  //设置材料2的漫反射系数
		m_material2.SetSpecular(0.5); //设置材料2的镜面指数
		m_material2.SetReflection(0.3);//设置材料2的影像
		m_matlist[1]=&m_material2;   // 把材料2放到数组中

		Vector3 m_center1,m_center2;  //创建两个向量
		m_center1.Set(100,200,200);   //对向量赋值
		m_center2.Set(300,260,180);   //对向量赋值

		Sphere *m_pSphere1,*m_pSphere2;  //两个球体
		m_pSphere1=new Sphere();   //创建球体1
		m_pSphere1->SetCenter(m_center1); //设置球体的中心
		m_pSphere1->SetRadius(100);  //设置球体的半径
		m_pSphere1->SetMaterial(*m_matlist[0]);//设置球体的材料
		m_objlist[0]=m_pSphere1;  //把球体1放入场景物体数组


		m_pSphere2=new Sphere();  //创建球体2	
		m_pSphere2->SetCenter(m_center2);  //设置球体的中心
		m_pSphere2->SetRadius(80);        //设置球体的半径
		m_pSphere2->SetMaterial(*m_matlist[1]);//设置球体的材料
		m_objlist[1]=m_pSphere2;  //把球体2放入场景物体数组
	}

#endif