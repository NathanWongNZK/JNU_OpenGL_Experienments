#include <GL/glut.h>
#include <stdio.h>
#include<stdlib.h>
#define LEFT_EDGE   1 //代表0001

#define RIGHT_EDGE 2         //代表0010

#define BOTTOM_EDGE 4       //代表0100

#define TOP_EDGE    8         //代表1000
void LineGL1(int x0,int y0,int x1,int y1)
{

         glBegin (GL_LINES);

         glColor3f (1.0f, 0.0f, 0.0f);   glVertex2f (x0,y0);

         glColor3f (0.0f, 1.0f, 0.0f);   glVertex2f (x1,y1); 

         glEnd ();

}
void LineGL2(int x2,int y2,int x3,int y3)
{
         glBegin (GL_LINES);
         glColor3f (1.0f, 0.0f, 1.0f);   glVertex2f (x2,y2);
         glColor3f (1.0f, 0.0f, 1.0f);   glVertex2f (x3,y3); 
         glEnd ();

}
void LineGL3(int x4,int y4,int x5,int y5)
{

         glBegin (GL_LINES);
         glColor3f (1.0f, 1.0f, 1.0f);   glVertex2f (x4,y4);
         glColor3f (1.0f, 1.0f, 1.0f);   glVertex2f (x5,y5); 
         glEnd ();
}
struct Rectangle
{
	float xmin,xmax,ymin,ymax;
};
Rectangle rect;
int x0,y0,x1,y1,x2,y2,x3,y3,x4,y4,x5,y5;
int CompCode(int x,int y,Rectangle rect)
{
         int code=0x00;
         if(y<rect.ymin)

                   code=code|4;
         if(y>rect.ymax)

                   code=code|8;
         if(x>rect.xmax)

                   code=code|2;
         if(x<rect.xmin)
                   code=code|1;

         return code;
}
void cohensutherlandlineclip(Rectangle rect, int &x0,int &y0,int &x1,int &y1)

{
		int accept,done;
		float x,y;
		accept=0;
		done=0;
 int code0,code1, codeout;
         code0 = CompCode(x0,y0,rect);
         code1 = CompCode(x1,y1,rect);
         do{
			   if(!(code0 | code1))
			   { accept=1;

					done=1;
			   }
			   else if(code0 & code1)
			   {
					done = 1;
			   }
			   else
			   {  
					if(code0!=0)

						codeout = code0;
					else
						codeout = code1;
					if(codeout&LEFT_EDGE){
						 y=y0+(y1-y0)*(rect.xmin-x0)/(x1-x0);
						 x=(float)rect.xmin;
					}
					else if(codeout&RIGHT_EDGE){

						 y=y0+(y1-y0)*(rect.xmax-x0)/(x1-x0);
						 x=(float)rect.xmax;
					}
					else if(codeout&BOTTOM_EDGE){
						 x=x0+(x1-x0)*(rect.ymin-y0)/(y1-y0);
						 y=(float)rect.ymin;
					}
					else if(codeout&TOP_EDGE){
						 x=x0+(x1-x0)*(rect.ymax-y0)/(y1-y0);
						 y=(float)rect.ymax;
					}
					if(codeout == code0)
					{
						 x0=x;y0=y;
						 code0 = CompCode(x0,y0,rect);
					}
					else
					{
						 x1=x;y1=y;
						 code1 = CompCode(x1,y1,rect);
					}
			   }

		}while(!done);

}

void myDisplay()

{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2i(300,300);
	glVertex2i(100,300);
	glVertex2i(100,300);
	glVertex2i(100,100);
	glVertex2i(100,100);
	glVertex2i(300,100);
	glVertex2i(300,100);
	glVertex2i(300,300);
	glEnd();
    LineGL1(x0,y0,x1,y1);
	LineGL2(x2,y2,x3,y3);
	LineGL3(x4,y4,x5,y5);
    glFlush();
}
void Init()

{
         glClearColor(0.0, 0.0, 0.0, 0.0);
         glShadeModel(GL_FLAT);
         rect.xmin=100;
         rect.xmax=300;
         rect.ymin=100;
         rect.ymax=300;
		 x0=500,y0=0,x1=0,y1=450;
		 x2=250,y2=0,x3=250,y3=400;
		 x4=500,y4=200,x5=0,y5=200;
         printf("Press key 'c' to Clip!n");
}
void Reshape(int w, int h)
{

         glViewport(0, 0, (GLsizei) w, (GLsizei) h);
         glMatrixMode(GL_PROJECTION);
         glLoadIdentity();
         gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);

}
void keyboard(unsigned char key, int x, int y)
{
         switch (key)
         {
         case 'c':
         cohensutherlandlineclip(rect,x0,y0,x1,y1);
		 glutPostRedisplay();
		 cohensutherlandlineclip(rect,x2,y2,x3,y3);	
		 cohensutherlandlineclip(rect,x4,y4,x5,y5);	
		break;
		 case 'r':
			 Init();
			glutPostRedisplay();
			break;
		 case 'x':
			 exit(0);
			 break;
         default:
			break;
         }
}

int main(int argc, char *argv[])
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
 glutInitWindowPosition(100, 100);
 glutInitWindowSize(640, 480);
 glutCreateWindow("Hello World!");

 Init();
 glutDisplayFunc(myDisplay);
 glutReshapeFunc(Reshape);
 glutKeyboardFunc(keyboard);
 glutMainLoop();
 return 0;
}