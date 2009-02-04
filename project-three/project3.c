#if defined(__APPLE__) && defined(__MACH__)
#   include <GLUT/glut.h>
#else
#	include <GL/glut.h>
#endif
#include <stdlib.h>


/**
 * Cordinate all scene drawing.
 */
static void display ( void )
{
	glClear( GL_COLOR_BUFFER_BIT );

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
	}
}
/**
 * 
 */
static void init ( void )
{
	glClearColor ( 0.0, 0.0, 0.0, 0.0 );

	glMatrixMode( GL_PROJECTION );
}

/**
 * Define our GL
 */
int main ( int argc, char** argv ) 
{
	glutInit( &argc , argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowPosition( 50, 100 );
	glutInitWindowSize( 400, 300 );
	glutCreateWindow( "Project #3" );

	init();

	glutDisplayFunc( display );
	glutKeyboardFunc( keyboard );

	glutMainLoop();

	return( 0 );
}
