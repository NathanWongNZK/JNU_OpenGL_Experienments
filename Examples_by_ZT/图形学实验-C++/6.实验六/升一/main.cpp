#include <windows.h>
#include <GL/glut.h> 
GLfloat light_position[] = {0.0,3.0,6.0,0.0};
GLfloat no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat mat_grey_ambient[] = {0.5,0.5,0.5,1.0};
GLfloat mat_red_ambient[] = {0.0,0.0,1.0,1.0};
GLfloat mat_diffuse[] = {0.8,0.2,0.5,1.0};
GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};
GLfloat no_shininess[] = {0.0};
GLfloat low_shininess[] = {5.0};
GLfloat high_shininess[] = {100.0};
GLfloat mat_emission[] = {0.3,0.2,0.2,0.0};

void myInit(void)
{
	glLightfv(GL_LIGHT2,GL_POSITION,light_position);//设置光源
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);//指定深度比较中使用的数值
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	/*为光照模型指定材质参数*/
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess);
	glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);

	glColorMaterial(GL_FRONT,GL_AMBIENT);//使材质色跟踪当前颜色
	glEnable(GL_COLOR_MATERIAL);

	/*第一个球形*/
	glPushMatrix();
	glColor3fv(no_mat);
	glTranslatef(-2.5,1.5,0.0);
	glRotatef(15.0,1.0,0.0,0.0);
	glutSolidSphere(1.2,20.0,20.0);
	glPopMatrix();

	/*第二个球形*/
	glPushMatrix();
	glColor3fv(mat_grey_ambient);
	glRotatef(15.0,1.0,0.0,0.0);
	glutSolidSphere(1.2,20.0,20.0);
	glPopMatrix();

	/*第三个球形*/
	glPushMatrix();
	glColor3fv(mat_red_ambient);
	glTranslatef(2.5,-1.5,0.0);
	glRotatef(15.0,1.0,0.0,0.0);
	glutSolidSphere(1.2,20.0,20.0);
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glFlush();
}

void myReshape(int w,int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(w <= h)
		glOrtho(-5.5,5.5,-5.5*(GLfloat)h/(GLfloat)w,5.5*(GLfloat)h/(GLfloat)w,-5.5,5.5);
	else
		glOrtho(-5.5*(GLfloat)w/(GLfloat)h,5.5*(GLfloat)w/(GLfloat)h,-5.5,5.5,-5.5,5.5);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc,char ** argv)
{
	/*初始化*/
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(400,400);
	glutInitWindowPosition(100,100);

	/*创建窗口*/
	glutCreateWindow(" Light&Material ");

	/*绘制与显示*/
	myInit();
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}