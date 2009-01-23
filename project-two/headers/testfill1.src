/*
** testfill1
**
** This program is designed to test filling triangles and rectangles
** using the supplied drawFilledPolygon() routine
*/

#include <support.h>		/* also includes GL/glut.h, et. al. */

#include <drawFilledPolygon.h>

#ifdef __cplusplus
extern "C" {
#endif

void display( void ) {
	GLint v[4][2];

	glClear( GL_COLOR_BUFFER_BIT );	/* clear the display window */

	/* 
	** Use student's drawFilledPolygon() to draw polygons of
	** various sizes, shapes, and orientations
	*/

	/*
	** First, draw a basic quad from (10,10) to (20,20), vertices
	** specified in counter-clockwise (CCW) sequence from the 
	** lower-left (LL) corner, in red
	*/

	v[0][0] = 10; v[0][1] = 10;
	v[1][0] = 20; v[1][1] = 10;
	v[2][0] = 20; v[2][1] = 20;
	v[3][0] = 10; v[3][1] = 20;

	glColor3f( 1.0, 0.0, 0.0 );	
	drawFilledPolygon( 4, v );

	/*
	** Quad from (40,30) to (30,50), CCW, LR, green
	*/

	v[0][0] = 40; v[0][1] = 30;
	v[1][0] = 40; v[1][1] = 50;
	v[2][0] = 30; v[2][1] = 50;
	v[3][0] = 30; v[3][1] = 30;

	glColor3f( 0.0, 1.0, 0.0 );
	drawFilledPolygon( 4, v );

	/*
	** Quad, (10,70) to (40,90), UR, CW, blue
	*/
	v[0][0] = 40; v[0][1] = 90;
	v[1][0] = 40; v[1][1] = 70;
	v[2][0] = 10; v[2][1] = 70;
	v[3][0] = 10; v[3][1] = 90;

	glColor3f( 0.0, 0.0, 1.0 );
	drawFilledPolygon( 4, v );

	/*
	** Quad, (10,210) to (40,230), UL, CW
	*/
	v[0][0] = 10; v[0][1] = 230;
	v[1][0] = 40; v[1][1] = 230;
	v[2][0] = 40; v[2][1] = 210;
	v[3][0] = 10; v[3][1] = 210;

	glColor3f( 0.0, 1.0, 1.0 );
	drawFilledPolygon( 4, v );

	/*
	** Triangle, isoceles. aligned lower edge, magenta
	*/
	v[0][0] = 100; v[0][1] = 10;
	v[1][0] = 150; v[1][1] = 10;
	v[2][0] = 125; v[2][1] = 20;

	glColor3f( 1.0, 0.0, 1.0 );
	drawFilledPolygon( 3, v );

	/*
	** Triangle, aligned top, tail on left, yellow
	*/
	v[0][0] = 100; v[0][1] = 30;
	v[1][0] = 140; v[1][1] = 50;
	v[2][0] = 175; v[2][1] = 50;

	glColor3f( 1.0, 1.0, 0.0 );
	drawFilledPolygon( 3, v );

	/*
	** Triangle, aligned top, tail on right, black
	*/
	v[0][0] = 120; v[0][1] = 40;
	v[1][0] = 80;  v[1][1] = 60;
	v[2][0] = 45;  v[2][1] = 60;

	glColor3f( 0.0, 0.0, 0.0 );
	drawFilledPolygon( 3, v );

	/*
	** Triangle, right
	*/
	v[0][0] = 10; v[0][1] = 100;
	v[1][0] = 10; v[1][1] = 120;
	v[2][0] = 25; v[2][1] = 100;

	glColor3f( 1.0, 1.0, 0.5 );
	drawFilledPolygon( 3, v );

	/*
	** Triangle, right
	*/
	v[0][0] = 10; v[0][1] = 130;
	v[1][0] = 20; v[1][1] = 130;
	v[2][0] = 20; v[2][1] = 140;

	glColor3f( 1.0, 0.5, 1.0 );
	drawFilledPolygon( 3, v );

	/*
	** Triangle, right
	*/
	v[0][0] = 10; v[0][1] = 170;
	v[1][0] = 20; v[1][1] = 170;
	v[2][0] = 10; v[2][1] = 150;

	glColor3f( 0.5, 1.0, 1.0 );
	drawFilledPolygon( 3, v );

	/*
	** Triangle, aligned bottom, tail upper left
	*/
	v[0][0] = 100; v[0][1] = 70;
	v[1][0] = 150; v[1][1] = 70;
	v[2][0] = 75;  v[2][1] = 90;

	glColor3f( 1.0, 0.5, 0.5 );
	drawFilledPolygon( 3, v );

	/*
	** Triangle, aligned bottom, tail upper right
	*/
	v[0][0] = 100; v[0][1] = 100;
	v[1][0] = 150; v[1][1] = 100;
	v[2][0] = 195; v[2][1] = 120;

	glColor3f( 0.5, 0.5, 1.0 );
	drawFilledPolygon( 3, v );

	/*
	** Triangle, scalene
	*/
	v[0][0] = 100; v[0][1] = 170;
	v[1][0] = 150; v[1][1] = 150;
	v[2][0] = 175; v[2][1] = 130;

	glColor3f( 0.5, 0.5, 0.5 );
	drawFilledPolygon( 3, v );


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

	init( argc, argv, "PolyFill Test 1" );

	/*
	** Enter the event loop
	*/

	glutMainLoop( );

	/* this statement is never reached */
	return( 0 );

}
