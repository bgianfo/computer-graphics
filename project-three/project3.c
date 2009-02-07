#include <stdlib.h>
#if defined(__APPLE__) && defined(__MACH__)
#	include <GLUT/glut.h>
#else
#	include <GL/glut.h>
#endif

const static int WIDTH = 800;
const static int HEIGHT = 600;
int window;
int spin = 0;
int animate = 1;

/**
 * Cordinate all scene drawing.
 * Args:
 * 		none
 */
static void display ( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	glColor4f(1.0,0.3,0.3,0.0);
	glTranslatef(0.0,0.0,-20.0);
	glPushMatrix();
		glRotatef(spin,1.0,1.0,0.0);
		glutSolidCube(1);
	glPopMatrix();

	glutSwapBuffers();
}

/**
 * Description: Catch keyboard args handle appropriately.
 * Args:
 * 		key - key which has been called. 
 * 		x - The X cordinate in the window when key was pressed.
 * 		y - The Y cordinate in the window when key was pressed.
 */
static void keyboard ( unsigned char key, int x, int y )
{
	switch ( key ) {
		case 'q':
		case 'Q':
		case 033:
			glutDestroyWindow(window);
			exit( EXIT_SUCCESS );
			break;
		case '1':
			//Select camera position 1
			glMatrixMode(GL_PROJECTION); // set the view volume shape
			glLoadIdentity();
			glOrtho(-2.0*64/48.0, 2.0*64/48.0, -2.0, 2.0, 0.1, 100);
			glMatrixMode(GL_MODELVIEW); // position and aim the camera
			glLoadIdentity();
			gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			break;
		case '2':
			//Select camera position 2
			glMatrixMode(GL_PROJECTION); // set the view volume shape
			glLoadIdentity();
			gluPerspective(45.0f,(GLfloat)WIDTH/(GLfloat)HEIGHT,0.1f,100.0f);
			glMatrixMode(GL_MODELVIEW); // position and aim the camera
			break;
		case '5':
			//Toggle first light source
			(glIsEnabled(GL_LIGHT0) == GL_TRUE ) ? glDisable(GL_LIGHT0) : glEnable(GL_LIGHT0);
			break;
		case '6':
			//Toggle second light source
			(glIsEnabled(GL_LIGHT1) == GL_TRUE) ? glDisable(GL_LIGHT1) : glEnable(GL_LIGHT1);
			break;
		case 'a':
			//Toggle animation state
			animate = (animate == 1) ? 0 : 1;
			break;
		default:
			glutPostRedisplay();
			break;
	}
}

/**
 * Description: Handle timer events
 * Args:
 * 		timernum - interger identifying which timer was called
 */
void timer(int timernum) 
{
	if (0 == timernum ) {
		if (animate == 1) {

			spin++;
			glutPostRedisplay();
		}
		glutTimerFunc(15,timer,0);
	}
}

/**
 * Description: Setup openGL viewport/lookat, enable lighting etc.  
 * Args:
 * 		none
 */
static void init ( void )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
	glClearDepth( 1.0 );
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION); // set the view volume shape
  	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)WIDTH/(GLfloat)HEIGHT,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW); // position and aim the camera

	glEnable(GL_LIGHTING);
	//glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
    glEnable ( GL_COLOR_MATERIAL ) ;

	glEnable(GL_LIGHT0);
	GLfloat light_pos[] = {3.0,3.0,3.0,0.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}


/**
 * Define our GLUT Window and callbacks
 * Args:
 * 		argc - number of args
 *		argv - char pionter array to commanline args
 */
int main ( int argc, char** argv ) 
{
	glutInit( &argc , argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowPosition( (glutGet(GLUT_SCREEN_WIDTH)/2)-(WIDTH/2), (glutGet(GLUT_SCREEN_HEIGHT)/2)-(HEIGHT/2));
	glutInitWindowSize( WIDTH, HEIGHT );
	window = glutCreateWindow( "Project #3" );
	init();
	glutDisplayFunc( display );
	glutTimerFunc(0,timer,0);
	glutKeyboardFunc( keyboard );
	glutMainLoop();
	return( 0 );
}
