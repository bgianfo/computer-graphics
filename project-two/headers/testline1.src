/*
**  testline
**
**  This program is designed to test "drawLine".
*/

#include <support.h>		/* also includes GL/glut.h et. al. */

#include <drawLine.h>

#ifdef __cplusplus
extern "C" {
#endif

void display( void ) {

	glClear( GL_COLOR_BUFFER_BIT );	/* clear the display window */

	/*
	** Draw various line segments
	*/

	/*
	** First, draw left-to-right, bottom-to-top versions in black
	*/

	glColor3f( 0.0, 0.0, 0.0 );

	drawLine(  10, 100,  10, 150 );	/* Vertical */
	drawLine(  60, 100, 110, 100 );	/* Horizontal */
	drawLine(  60, 150, 110, 200 );	/* + diagonal */
	drawLine(  60, 270, 110, 220 );	/* - diagonal */
	drawLine(  10,  10,  50,  20 );	/* shallow + slope */
	drawLine(  10,  40,  50,  30 );	/* shallow - slope */
	drawLine(  70,  10,  90,  40 );	/* steep + slope */
	drawLine( 100,  40, 120,  10 );	/* steep - slope */

	/*
	** Now, draw right-to-left, top-to-bottom versions in red
	*/

	glColor3f( 1.0, 0.0, 0.0 );

	drawLine( 160, 150, 160, 100 );	/* Vertical */
	drawLine( 260, 100, 210, 100 );	/* Horizontal */
	drawLine( 260, 200, 210, 150 );	/* + diagonal */
	drawLine( 260, 220, 210, 270 );	/* - diagonal */
	drawLine( 200,  20, 160,  10 );	/* shallow + slope */
	drawLine( 200,  30, 160,  40 );	/* shallow - slope */
	drawLine( 240,  40, 220,  10 );	/* steep + slope */
	drawLine( 270,  10, 250,  40 );	/* steep - slope */

	/*
	** Ensure that everything is displayed
	*/

	glFlush();

}

#ifdef __cplusplus
}
#endif


/* 
** Main routine - GLUT setup and initialization 
*/

int main( int argc, char** argv ) {

	/*
	** Call our generic "initialize everything" routine
	*/

	init( argc, argv, "Line Test 1" );

	/*
	** Enter the event loop
	*/

	glutMainLoop( );

	/* this statement is never reached */
	return( 0 );

}
