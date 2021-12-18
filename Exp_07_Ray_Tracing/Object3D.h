// Object3D.h: interface for the Object3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECT3D_H__101A6D2D_2C39_4D9D_BE56_E02F73686911__INCLUDED_)
#define AFX_OBJECT3D_H__101A6D2D_2C39_4D9D_BE56_E02F73686911__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Material.h"
#include "Ray.h"
#include "Hit.h"
class Object3D{
public:
	void SetMaterial(Material& a_Material){m_Material = a_Material;} //设置材料
	Material GetMaterial(){return m_Material;}                       //返回材料
	virtual bool intersect(Ray& ray,Hit& hit, float tmin){return false;}
private:
	Material m_Material;
};

#endif // !defined(AFX_OBJECT3D_H__101A6D2D_2C39_4D9D_BE56_E02F73686911__INCLUDED_)
