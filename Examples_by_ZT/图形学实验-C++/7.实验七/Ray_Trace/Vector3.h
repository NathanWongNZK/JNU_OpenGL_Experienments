// Point.h: interface for the Point class.
//
//////////////////////////////////////////////////////////////////////
#ifndef POINT_H
#define POINT_H
#include <math.h>
#define EPS 1E-6

typedef class Vector3{
public:
	Vector3() : x( 0.0f ), y( 0.0f ), z( 0.0f ) {};  //构造函数
	Vector3(Vector3& vector3){x=vector3.x;y=vector3.y;z=vector3.z; }//设置向量的3个坐标点
	Vector3( float a_X, float a_Y, float a_Z ) : x( a_X ), y( a_Y ), z( a_Z ) {};//设置向量的3个坐标点
	void Set( float a_X, float a_Y, float a_Z ) { x = a_X; y = a_Y; z = a_Z; }//设置向量的3个坐标点
	float Length() { return (float)sqrt( x * x + y * y + z * z ); }  //返回向量的长度
	Vector3 Normalize() { float l = 1.0f / Length(); x *= l; y *= l; z *= l;return Vector3(x,y,z); }//转化为单位向量
	float Dot( Vector3 a_V ) { return x * a_V.x + y * a_V.y + z * a_V.z; }//向量相乘
	float GetFirst(){return x;}  //返回向量的X坐标
	float GetSecond(){return y;} //返回向量的Y坐标 
	float GetThird(){return z;}  //返回向量的Z坐标
	void operator += ( Vector3& a_V ) { x += a_V.x; y += a_V.y; z += a_V.z; }//向量相加
	void operator = ( Vector3& a_V ) { x = a_V.x; y = a_V.y; z = a_V.z; }//向量相等操作
	void operator += ( Vector3* a_V ) { x += a_V->x; y += a_V->y; z += a_V->z; }//向量相加
	void operator -= ( Vector3& a_V ) { x -= a_V.x; y -= a_V.y; z -= a_V.z; }//向量相减
	void operator -= ( Vector3* a_V ) { x -= a_V->x; y -= a_V->y; z -= a_V->z; }//向量相减
	void operator *= ( float f ) { x *= f; y *= f; z *= f; }//向量与f相乘
	void operator *= ( Vector3& a_V ) { x *= a_V.x; y *= a_V.y; z *= a_V.z; }//向量相乘
	void operator *= ( Vector3* a_V ) { x *= a_V->x; y *= a_V->y; z *= a_V->z; }//向量相乘
	Vector3 operator- () const { return Vector3( -x, -y, -z ); }//反向量
	friend Vector3 operator + ( const Vector3& v1, const Vector3& v2 ) { return Vector3( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z ); }//向量相加
	friend Vector3 operator - ( const Vector3& v1, const Vector3& v2 ) { return Vector3( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z ); }//向量相减
	friend Vector3 operator * ( const Vector3& v1, Vector3& v2 ) { return Vector3( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z ); }//向量相乘
	friend Vector3 operator * ( float f, const Vector3& v ) { return Vector3( v.x * f, v.y * f, v.z * f ); } //向量与f相乘
	friend Vector3 operator * ( const Vector3& v, float f ) { return Vector3( v.x * f, v.y * f, v.z * f ); } //向量与f相乘
	friend Vector3 operator / ( const Vector3& v, float f ) { return Vector3( v.x / f, v.y / f, v.z / f ); } //向量与f相除
	
private:
	float x;  //向量的x坐标
	float y;  //向量的y坐标
	float z;  //向量的z坐标
}Color;
#define BACKGROUND Vector3( 0, 0, 0 )
#endif