// Light.h: interface for the Light class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIGHT_H__CCD0A844_279D_4B73_910D_008056236329__INCLUDED_)
#define AFX_LIGHT_H__CCD0A844_279D_4B73_910D_008056236329__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Vector3.h"

class Light{
public:
	void SetAmbient( Vector3& a_ambient){m_ambient=a_ambient;}  //设置环境光
	void SetDiffuse(Vector3& a_diffuse){m_diffuse=a_diffuse;}  //设置漫反射光线
	void SetSpecular(Vector3& a_specular){m_specular=a_specular;}  //设置镜面反射光线
	void SetPosition(Vector3& a_position){m_position=a_position;}   //设置交点处的位置
	Vector3 GetAmbient(){return m_ambient;}    //返回环境光
	Vector3 GetDiffuse(){return m_diffuse;}    //返回漫反射光线
	Vector3 GetSpecular(){return m_specular;}  //返回镜面反射光线
	Vector3 GetPosition(){return m_position;}  //返回交点处的位置
private:
	Vector3 m_ambient;  //环境光线
	Vector3 m_diffuse;  //漫反射光线
	Vector3 m_specular; //镜面反射光线
	Vector3 m_position; //焦点处位置
};


#endif // !defined(AFX_LIGHT_H__CCD0A844_279D_4B73_910D_008056236329__INCLUDED_)
