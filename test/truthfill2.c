/*
** testfill2
**
** This program is designed to test filling triangles and rectangles
** using the supplied SkPolygonFill() routine
*/

#include "support.h"		/* also includes GL/glut.h et. al. */

#include "SkPolygonFill.h"

#include <iostream>
	using std::cout;
	using std::endl;

#ifdef __cplusplus
extern "C" {
#endif

void display( void ) {
	glClear( GL_COLOR_BUFFER_BIT );

	/* 
	** First, draw a basic diamond, vertices specified in 
	** counter-clockwise (CCW) sequence from the lower-left (LL)
	** corner, in red
	*/
	cout << endl;
	cout << "Red Polygon" << endl;

	glColor3f( 1.0, 0.0, 0.0 );
	glBegin(GL_POLYGON);
		glVertex2i(100,10);
		glVertex2i(120,30);
		glVertex2i(100,50);
		glVertex2i(80,30);
	glEnd();

	/*
	** Pentagon, concave on right, LL, CCW, green
	*/
	cout << endl;
	cout << "Green Polygon" << endl;
	glColor3f( 0.0, 1.0, 0.0 );
	glBegin(GL_POLYGON);
		glVertex2i(80,70);
		glVertex2i(140,70);
		glVertex2i(100,90);
		glVertex2i(110,130);
		glVertex2i(60,110);
	glEnd();

	/*
	** Pentagon, concave on bottom, LL, CCW, black
	*/
	cout << endl;
	cout << "Black Polygon" << endl;
	glColor3f( 0.0, 0.0, 0.0 );
	glBegin(GL_POLYGON);
		glVertex2i(80,150);
		glVertex2i(140,150);
		glVertex2i(160,190);
		glVertex2i(100,170);
		glVertex2i(60,190);
	glEnd();

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
