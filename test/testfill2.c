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

#include <vector>
	using std::vector;

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

	vector<vector<int> > v;

	vector<int> vtx;
	vtx.push_back(100);
	vtx.push_back(10);
	v.push_back(vtx);

	vtx.clear();

	vtx.push_back(120);
	vtx.push_back(30);
	v.push_back(vtx);

	vtx.clear();

	vtx.push_back(100);
	vtx.push_back(50);
	v.push_back(vtx);

	vtx.clear();

	vtx.push_back(80);
	vtx.push_back(30);
	v.push_back(vtx);

	glColor3f( 1.0, 0.0, 0.0 );
	SkPolygonFill( v );

	/*
	** Pentagon, concave on right, LL, CCW, green
	*/
	cout << endl;
	cout << "Green Polygon" << endl;

	vector<vector<int> > v2;
	vtx.push_back(80);
	vtx.push_back(70);
	v2.push_back(vtx);

	vtx.clear();
	vtx.push_back(140);
	vtx.push_back(70);
	v2.push_back(vtx);

	vtx.clear();
	vtx.push_back(100);
	vtx.push_back(90);
	v2.push_back(vtx);

	vtx.clear();
	vtx.push_back(110);
	vtx.push_back(130);
	v2.push_back(vtx);

	vtx.clear();
	vtx.push_back(60);
	vtx.push_back(110);
	v2.push_back(vtx);

	glColor3f( 0.0, 1.0, 0.0 );
	SkPolygonFill( v2 );

	/*
	** Pentagon, concave on bottom, LL, CCW, black
	*/
	cout << endl;
	cout << "Black Polygon" << endl;

	vector<vector<int> > v3;
	vtx.push_back(80);
	vtx.push_back(150);
	v3.push_back(vtx);

	vtx.clear();
	vtx.push_back(140);
	vtx.push_back(150);
	v3.push_back(vtx);

	vtx.clear();
	vtx.push_back(160);
	vtx.push_back(190);
	v3.push_back(vtx);

	vtx.clear();
	vtx.push_back(100);
	vtx.push_back(170);
	v3.push_back(vtx);

	vtx.clear();
	vtx.push_back(60);
	vtx.push_back(190);
	v3.push_back(vtx);

	glColor3f( 0.0, 0.0, 0.0 );
	SkPolygonFill( v3 );

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
