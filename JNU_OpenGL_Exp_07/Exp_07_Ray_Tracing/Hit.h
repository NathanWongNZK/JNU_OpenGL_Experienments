// Hit.h: interface for the Hit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HIT_H__70A8DBB6_BC95_4345_A75E_8F7ACE8BE314__INCLUDED_)
#define AFX_HIT_H__70A8DBB6_BC95_4345_A75E_8F7ACE8BE314__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define SCRWIDTH 500
#define SCRHEIGHT 500
#include "Vector3.h"
#include "Material.h"
class Hit
{
public:
	Hit()
	{
		m_t = 10000000;
		m_color = BACKGROUND;
	}																	//构造函数
	void SetTmin(float a_t) { m_t = a_t; }								//设置交点处的Z值
	float GetTmin() { return m_t; }										//得到交点处的Z值
	void SetColor(Color &a_color) { m_color = a_color; }				// 设置颜色
	Color GetColor() { return m_color; }								//得到颜色
	void SetPosition(Vector3 a_position) { m_position = a_position; }	//设置交点处的位置
	void SetMaterial(Material &a_material) { m_material = a_material; } //设置交点处的材料
	Material GetMaterial() { return m_material; }						//返回材料
	void SetNormal(Vector3 &a_normal) { m_normal = a_normal; }			//设置交点处的法向量
	Vector3 GetNormal() { return m_normal; }							//返回交点处的法向量
	Vector3 GetPosition() { return m_position; }						//返回交点处的位置
private:
	float m_t;			 //交点处的Z值
	Color m_color;		 //屏幕的颜色
	Material m_material; //交点处的材料
	Vector3 m_normal;	 //交点处的法向量
	Vector3 m_position;	 //交点处的位置
};

Hit hit[SCRWIDTH][SCRHEIGHT];

#endif // !defined(AFX_HIT_H__70A8DBB6_BC95_4345_A75E_8F7ACE8BE314__INCLUDED_)
