// Material.h: interface for the Material class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATERIAL_H__50634E23_83FA_442F_B629_FACF60489D2E__INCLUDED_)
#define AFX_MATERIAL_H__50634E23_83FA_442F_B629_FACF60489D2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Vector3.h"
class Material
{
public:
	Material()	{}  //构造函数
	void SetColor( Color& a_Color ) { m_Color = a_Color; } //设置物体的颜色
	Color GetColor() { return m_Color; }                   //返回物体的颜色
	void SetDiffuse( float a_Diff ) { m_Diff = a_Diff; }   //设置漫反射系数
	void SetSpecular( float a_Spec ) { m_Spec = a_Spec; }  //设置镜面反射系数
	void SetReflection( float a_Refl ) { m_Refl = a_Refl; }//设置材料的影像
	void SetRefraction( float a_Refr ) { m_Refr = a_Refr; }//设置材料的折射系数
	float GetSpecular() { return m_Spec; }                 //返回镜面系数
	float GetDiffuse() { return m_Diff; }                  //返回散射系数
	float GetReflection() { return m_Refl; }               //返回材料的影像
	float GetRefraction() { return m_Refr; }               //返回折射系数  
	void SetRefrIndex( float a_Refr ) { m_RIndex = a_Refr; }//设置环境、散射和镜面颜色索引
	float GetRefrIndex() { return m_RIndex; }               //返回环境、散射和镜面颜色索引
	void SetShininess(int a_Shin){ m_Shin = a_Shin;}        //设置镜面指数
	int GetShininess(){return m_Shin;}                      //返回镜面指数
	void operator = ( Material& a_V )                       //把材料的各种系数赋值给各个参数
	{  m_Color= a_V.m_Color; m_Refl = a_V.m_Refl; m_Refr = a_V.m_Refr;m_Diff=a_V.m_Diff;m_Spec=a_V.m_Spec;m_RIndex=a_V.m_RIndex;m_Shin=a_V.m_Shin; }
private:
	Color m_Color;//物体本生的颜色
	float m_Refl, m_Refr;//材料的影像和折射系数
	float m_Diff, m_Spec;//材料的散射系数和镜面系数
	int m_Shin;//镜面指数
	float m_RIndex;//环境、散射和镜面颜色索引
};

#endif // !defined(AFX_MATERIAL_H__50634E23_83FA_442F_B629_FACF60489D2E__INCLUDED_)
