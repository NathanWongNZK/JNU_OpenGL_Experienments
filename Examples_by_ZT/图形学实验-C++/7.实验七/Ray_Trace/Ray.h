// Ray.h: interface for the Ray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RAY_H__1E702CD5_E748_4FBF_972F_F6856A823522__INCLUDED_)
#define AFX_RAY_H__1E702CD5_E748_4FBF_972F_F6856A823522__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Vector3.h"
class Ray 
{
public:
	Ray() : m_Origin( Vector3( 0, 0, 0 ) ), m_Direction( Vector3( 0, 0, 0 ) ) {};//构造函数，初始化视点和视线的方向
	Ray( Vector3& a_Origin, Vector3& a_Dir ):	m_Origin( a_Origin ), 	m_Direction( a_Dir )	{}//设置视点和视线的方向
	void SetOrigin( Vector3& a_Origin ) { m_Origin = a_Origin; }//设置视点的位置
	void SetDirection( Vector3& a_Direction ) { m_Direction = a_Direction; }//设置视线的方向
	Vector3& GetOrigin() { return m_Origin; }//返回视点的位置
	Vector3& GetDirection() { return m_Direction; }//返回视线的方向
private:
	Vector3 m_Origin;//视点
	Vector3 m_Direction;//视线的方向
};

#endif // !defined(AFX_RAY_H__1E702CD5_E748_4FBF_972F_F6856A823522__INCLUDED_)
