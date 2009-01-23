/*
**  support
**
**  Supporting functions for all the test* programs
*/

#include <stdlib.h>

#include <GL/glut.h>         /* glut.h includes gl.h and glu.h*/

#include <support.h>

/*
** print_poly - print a set of vertices as a line loop
**
** parameters:
**	n	number of vertices
**	v	vertex array
**
*/

void print_poly( GLint n, GLint v[][2] ) {
	int i;

	/*
	** draw the lines
	*/

	glBegin( GL_LINE_LOOP );
	  for( i = 0; i < n; ++i ) {
		glVertex2i( v[i][0], v[i][1] );
	  }
	glEnd();

}

#ifdef __cplusplus
extern "C" {
#endif

/*
** Keyboard routine - handle what minimal keyboard input is required
*/

void keyboard( GLubyte key, GLint x, GLint y ) {

	switch( key ) {

		/* exit on ESC or 'q' */
		case 0x1b:
		case 'q':
		case 'Q':
			exit( 0 );
	
	}
		
}

/*
** init - set up the display
*/

void display( void );	/* display callback routine prototype */

#ifdef __cplusplus
}
#endif

void init( int argc, char **argv, const char *title ) {

	/*
	** Begin by setting up all the window parameters
	*/

	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE );
	glutInitWindowSize( 300, 300 );
	glutCreateWindow( title );

	/*
	** Clear window to white
	*/
	glClearColor( 1.0, 1.0, 1.0, 1.0 );

	/*
	** Turn on stippling (for print_poly)
	*/
	glEnable( GL_LINE_STIPPLE );

	/*
	** Register the "standard" callbacks
	**
	** NOTE:  the display callback isn't defined here -
	** it must be provided by whatever program uses this
	** support code.
	*/

	glutKeyboardFunc( keyboard );
	glutDisplayFunc( display );

	/*
	** Set the view window and viewport
	*/
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D( 0, 299, 0, 299 );
	glViewport( 0, 0, 300, 300 );

}
