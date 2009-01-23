/*
** testfill2
**
** This program is designed to test filling triangles and rectangles
** using the supplied drawFilledPolygon() routine
*/

#include <support.h>		/* also includes GL/glut.h et. al. */

#include <drawFilledPolygon.h>

#ifdef __cplusplus
extern "C" {
#endif

void display( void ) {
	GLint v[10][2];

	glClear( GL_COLOR_BUFFER_BIT );

	/* 
	** First, draw a basic diamond, vertices specified in 
	** counter-clockwise (CCW) sequence from the lower-left (LL)
	** corner, in red
	*/
	v[0][0] = 100; v[0][1] = 10;
	v[1][0] = 120; v[1][1] = 30;
	v[2][0] = 100; v[2][1] = 50;
	v[3][0] =  80; v[3][1] = 30;

	glColor3f( 1.0, 0.0, 0.0 );
	drawFilledPolygon( 4, v );

	/*
	** Pentagon, concave on right, LL, CCW, green
	*/
	v[0][0] =  80; v[0][1] =  70;
	v[1][0] = 140; v[1][1] =  70;
	v[2][0] = 100; v[2][1] =  90;
	v[3][0] = 110; v[3][1] = 130;
	v[4][0] =  60; v[4][1] = 110;

	glColor3f( 0.0, 1.0, 0.0 );
	drawFilledPolygon( 5, v );

	/*
	** Pentagon, concave on bottom, LL, CCW, black
	*/
	v[0][0] =  80; v[0][1] = 150;
	v[1][0] = 140; v[1][1] = 150;
	v[2][0] = 160; v[2][1] = 190;
	v[3][0] = 100; v[3][1] = 170;
	v[4][0] =  60; v[4][1] = 190;

	glColor3f( 0.0, 0.0, 0.0 );
	drawFilledPolygon( 5, v );

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

	init( argc, argv, "PolyFill Test 2" );

	/*
	** Enter the event loop
	*/

	glutMainLoop( );

	/* this statement is never reached */
	return( 0 );

}
