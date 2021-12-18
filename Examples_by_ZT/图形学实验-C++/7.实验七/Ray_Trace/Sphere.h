// Shere.h: interface for the Shere class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHERE_H__3BF7AF2F_DE7F_44AF_9F10_9908EB3A101A__INCLUDED_)
#define AFX_SHERE_H__3BF7AF2F_DE7F_44AF_9F10_9908EB3A101A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Object3D.h"
class Sphere:public Object3D{
public:
   	bool intersect(Ray& ray,Hit& hit, float tmin);
	void SetCenter(Vector3& a_center){ m_center=a_center;}
	Vector3 GetCenter(){return m_center;}
	void SetRadius(float a_radius){m_radius=a_radius;}
private:
	Vector3 m_center;//圆心坐标
	float m_radius;
};
bool Sphere:: intersect(Ray& ray,Hit& hit, float tmin){
/*		Vector3 e(SCRWIDTH/2,SCRHEIGHT/2,-200);
		for(int j=0;j<SCRHEIGHT;j++){
			for(int i=0;i<SCRWIDTH;i++){
				Vector3 d,t;//d=s-e
				Vector3 s(i,j,0);//s是屏幕上的像素点
				d=s-e;
				t=e-m_center;
				float test=4*(d.Dot(t))*(d.Dot(t))-4*(d.Dot(d))*(t.Dot(t)-m_radius*m_radius);
				if(test<0){
					glColor3f (0.0, 0.0, 0.0);
					glBegin(GL_POINTS);
					glVertex2d(i,j);// 中间是点的坐标 
					glEnd();
				}j
				else{
					glColor3f (1.0, 1.0, 1.0);
					glBegin(GL_POINTS);
					glVertex2d(i,j);// 中间是点的坐标 
					glEnd();
				}
			}
		}
		return true;*/
		Vector3 d,k;
		d=ray.GetDirection();
		k=ray.GetOrigin()-m_center;
		float test=(d.Dot(k))*(d.Dot(k))-(d.Dot(d))*(k.Dot(k)-m_radius*m_radius);
	if(test>=0){
			float t1 = (-d.Dot(k)-sqrt(test))/(d.Dot(d));
			float t2 = (-d.Dot(k)+sqrt(test))/(d.Dot(d));
			if(t1>0 || t2>0){
				Vector3 p1 = ray.GetOrigin()+t1*(d);
				Vector3 p2 = ray.GetOrigin()+t2*(d);
				if(t1<=t2){
					if(t1>0 && t1<tmin){
						hit.SetNormal((p1-m_center)/m_radius);
						hit.SetTmin(t1);
						hit.SetPosition(p1);
					}
				}
				else{
					if(t2>0 && t2<tmin){
						hit.SetNormal((p2-m_center)/m_radius);
						hit.SetTmin(t2);
						hit.SetPosition(p2);
					}
				}
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
#endif // !defined(AFX_SHERE_H__3BF7AF2F_DE7F_44AF_9F10_9908EB3A101A__INCLUDED_)
