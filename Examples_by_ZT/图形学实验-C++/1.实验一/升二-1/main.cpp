#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.1415926
#define RAND_MAX 0x7fff
void InitDisplay(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,1.0f,1.0f);
	glRectf(-1.0f,-1.0f,1.0f,1.0f);
}

void DispalyTriangles(float points[], float color[])
{
	glBegin(GL_TRIANGLES);
	int i=0;
	for(;i<6;i+=2){
		glColor3f(color[0],color[1],color[2]);glVertex2f(points[i],points[i+1]);
	}
	glEnd();
	
}

float BH_X(float x0,float y0,float thea){
	float x;
	return x=x0*cos(thea)-y0*sin(thea);
}

float BH_Y(float x0,float y0,float thea){
	float y;
	return y=x0*sin(thea)+y0*cos(thea);
}

float num(){
	float t=rand()/(RAND_MAX+1.0);
	return t;
}

void myDisplay(void){
	InitDisplay();
	float a=0.3;
	float color[3]={1.0f,0.0f,0.0f};
	float points[6]={0.0,0.0,0.0,a,a,0.0};
	float point[6]={0.0,0.0,0.0,a,a,0.0};
	int i=0,j=0;
	DispalyTriangles(points,color);	
	for(;i<3;i++){
		for(;j<6;j+=2){
			point[j]=BH_X(points[j],points[j+1],i*PI/2+PI/2);
			point[j+1]=BH_Y(points[j],points[j+1],i*PI/2+PI/2);
		}
		j=0;
		DispalyTriangles(point,color);
	}
	
	
	float points1[6]={a,a,a*2,0,a,-a};
	float point1[6]={a,a,a*2,0,a,-a};
	float color1[3]={num(),num(),num()};
	DispalyTriangles(points1,color1);	
	for(i=0,j=0 ;i<3;i++){
		for(;j<6;j+=2){
			point1[j]=BH_X(points1[j],points1[j+1],i*PI/2+PI/2);
			point1[j+1]=BH_Y(points1[j],points1[j+1],i*PI/2+PI/2);
		}
		j=0;
		float color[3]={num(),num(),num()};
		DispalyTriangles(point1,color);
	}
 	glFlush();
}

int main(int argc, char *argv[]){ /* glut ��ͷ��ȫ����GLUT���߰����ṩ�ĺ���  */
	glutInit(&argc, argv);//��ʼ�� ��������GLUTʹ��֮ǰ����һ��
 	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	// ��ʾ��ʽΪRGB��ɫ���ߵ����壺��ͼָ���ڴ�����ֱ��ִ��
 	glutInitWindowPosition(600, 400);//���ô�������Ļ�е�λ��
 	glutInitWindowSize(400, 400);//���ô��ڵĴ�С
 	glutCreateWindow("Hello World!");
	//��������ʾΪ���ڵı��⣬����Ҫ����glutMainLoop������ʾ
  	glutDisplayFunc(&myDisplay);//��Ҫ��ͼʱ���ͻ�����������
 	glutMainLoop();
 	return 0;
}