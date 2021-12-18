# include < GL/glut.h > 
/* ��ʼ���������ԡ���Դ���ԡ�����ģ�ͣ�����Ȼ������� */ 
void init(void) 
{ 
	GLfloat light_position [ ] = { 0.0, 0.0, 1.0, 0.0 }; 
	GLfloat mat_diffuse[] = { 0.0, 0.0, 5.0, 0.0 };
	glClearColor ( 0.0, 0.0, 0.0, 0.0 ); //���ñ���ɫΪ��ɫ
	glShadeModel ( GL_SMOOTH ); 
	//glMaterialfv(GL_FRONT,GL_AMBIENT,mat_specular);
	 glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glLightfv ( GL_LIGHT0, GL_POSITION, light_position); 
	glEnable (GL_LIGHTING); 
	glEnable (GL_LIGHT0); 
	glEnable (GL_DEPTH_TEST); 
} 
/*���� GLUT ����,����һ����*/ 
void display ( void ) 
{ 
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glutSolidSphere (1.0, 40, 50);    //�뾶Ϊ 1,40 ��γ��,50 ������
	glFlush (); 
} 
/* ���� GLUT �� reshape ������w��h �ֱ������ͼ�εĴ��ڵĿ�͸�*/ 
void reshape (int w, int h) 
{ 
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION); 
	glLoadIdentity ( ); 
	if (w <= h) 
		glOrtho (-1.5, 1.5, -1.5 * ( GLfloat ) h / ( GLfloat ) w, 
		1.5* ( GLfloat ) h / ( GLfloat ) w, -10.0, 10.0 ); //����ƽ���Ӿ���
	else 
		glOrtho (-1.5 * ( GLfloat ) w / ( GLfloat ) h,1.5 * ( GLfloat ) 
		w/( GLfloat ) h, -1.5, 1.5, -10.0, 10.0); 
	glMatrixMode ( GL_MODELVIEW ); 
	glLoadIdentity ( ) ; 
} 
int main(int argc, char** argv) 
{ 
	glutInit (&argc, argv);     // GLUT ������ʼ��
	glutInitDisplayMode (GLUT_SINGLE |GLUT_RGB |GLUT_DEPTH); // ��ʾģʽ��ʼ��
	glutInitWindowSize (300, 300);       // ���崰�ڴ�С
	glutInitWindowPosition (100, 100);   // ���崰��λ��  
	glutCreateWindow ( argv [ 0 ] );   // ��ʾ����,���ڱ���Ϊִ�к�����
	init( );
	glutDisplayFunc ( display ); 	// ע�� OpenGL ��ͼ����(һ������ĵ��÷�ʽ,��ͬ) 
	glutReshapeFunc ( reshape );   // ע�ᴰ�ڴ�С�ı�ʱ����Ӧ����
	glutMainLoop( );      // ���� GLUT ��Ϣѭ������ʼִ�г���
	return 0; 
} 
