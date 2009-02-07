#include <stdlib.h>
#if defined(__APPLE__) && defined(__MACH__)
#	include <GLUT/glut.h>
#else
#	include <GL/glut.h>
#endif

const static int WIDTH = 400;
const static int HEIGHT = 300;

/**
 * Cordinate all scene drawing.
 */
static void display ( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	glColor3f(1.0,1.0,1.0);
	glutSolidCube(1);

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
			glOrtho(-2.0*64/48.0, 2.0*64/48.0, -2.0, 2.0, 0.1, 100);
			glMatrixMode(GL_MODELVIEW); // position and aim the camera
			glLoadIdentity();
			gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
			break;
		default:
			break;
	}
}

/**
 * 
 */
static void init ( void )
{
	glClearColor ( 0.0, 0.0, 0.0, 0.0 );
	glMatrixMode(GL_PROJECTION); // set the view volume shape
  	glLoadIdentity();
	glOrtho(-2.0*64/48.0, 2.0*64/48.0, -2.0, 2.0, 0.1, 100);
	glMatrixMode(GL_MODELVIEW); // position and aim the camera
	glLoadIdentity();
	gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

/**
 * Define our GL
 */
int main ( int argc, char** argv ) 
{
	glutInit( &argc , argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowPosition( (glutGet(GLUT_SCREEN_WIDTH)/2)-(WIDTH/2), (glutGet(GLUT_SCREEN_HEIGHT)/2)-(HEIGHT/2));
	glutInitWindowSize( WIDTH, HEIGHT );
	glutCreateWindow( "Project #3" );

	init();

	glutDisplayFunc( display );
	glutKeyboardFunc( keyboard );

	glutMainLoop();

	return( 0 );
}
