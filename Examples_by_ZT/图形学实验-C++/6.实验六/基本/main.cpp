# include < GL/glut.h > 
/* 初始化材料属性、光源属性、光照模型，打开深度缓冲区等 */ 
void init(void) 
{ 
	GLfloat light_position [ ] = { 0.0, 0.0, 1.0, 0.0 }; 
	GLfloat mat_diffuse[] = { 0.0, 0.0, 5.0, 0.0 };
	glClearColor ( 0.0, 0.0, 0.0, 0.0 ); //设置背景色为蓝色
	glShadeModel ( GL_SMOOTH ); 
	//glMaterialfv(GL_FRONT,GL_AMBIENT,mat_specular);
	 glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glLightfv ( GL_LIGHT0, GL_POSITION, light_position); 
	glEnable (GL_LIGHTING); 
	glEnable (GL_LIGHT0); 
	glEnable (GL_DEPTH_TEST); 
} 
/*调用 GLUT 函数,绘制一个球*/ 
void display ( void ) 
{ 
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glutSolidSphere (1.0, 40, 50);    //半径为 1,40 条纬线,50 条经线
	glFlush (); 
} 
/* 定义 GLUT 的 reshape 函数，w、h 分别是输出图形的窗口的宽和高*/ 
void reshape (int w, int h) 
{ 
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION); 
	glLoadIdentity ( ); 
	if (w <= h) 
		glOrtho (-1.5, 1.5, -1.5 * ( GLfloat ) h / ( GLfloat ) w, 
		1.5* ( GLfloat ) h / ( GLfloat ) w, -10.0, 10.0 ); //创建平行视景体
	else 
		glOrtho (-1.5 * ( GLfloat ) w / ( GLfloat ) h,1.5 * ( GLfloat ) 
		w/( GLfloat ) h, -1.5, 1.5, -10.0, 10.0); 
	glMatrixMode ( GL_MODELVIEW ); 
	glLoadIdentity ( ) ; 
} 
int main(int argc, char** argv) 
{ 
	glutInit (&argc, argv);     // GLUT 环境初始化
	glutInitDisplayMode (GLUT_SINGLE |GLUT_RGB |GLUT_DEPTH); // 显示模式初始化
	glutInitWindowSize (300, 300);       // 定义窗口大小
	glutInitWindowPosition (100, 100);   // 定义窗口位置  
	glutCreateWindow ( argv [ 0 ] );   // 显示窗口,窗口标题为执行函数名
	init( );
	glutDisplayFunc ( display ); 	// 注册 OpenGL 绘图函数(一种特殊的调用方式,下同) 
	glutReshapeFunc ( reshape );   // 注册窗口大小改变时的响应函数
	glutMainLoop( );      // 进入 GLUT 消息循环，开始执行程序
	return 0; 
} 
