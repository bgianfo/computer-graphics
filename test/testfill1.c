/*
** testfill1
**
** This program is designed to test filling triangles and rectangles
** using the supplied drawFilledPolygon() routine
*/

#include "support.h"		/* also includes GL/glut.h, et. al. */

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
	glClear( GL_COLOR_BUFFER_BIT );	/* clear the display window */

	/* 
	** Use student's drawFilledPolygon() to draw polygons of
	** various sizes, shapes, and orientations
	*/

	/*
	** First, draw a basic quad from (10,10) to (20,20), vertices
	** specified in counter-clockwise (CCW) sequence from the 
	** lower-left (LL) corner, in red
	* PASS
	*/

	vector<vector<int> > v;
	vector<int> vtx;
	vtx.push_back(10);
	vtx.push_back(10);
	v.push_back(vtx);

	vtx.clear();
	vtx.push_back(20);
	vtx.push_back(10);
	v.push_back(vtx);

	vtx.clear();
	vtx.push_back(20);
	vtx.push_back(20);
	v.push_back(vtx);

	vtx.clear();
	vtx.push_back(10);
	vtx.push_back(20);
	v.push_back(vtx);

	glColor3f( 1.0, 0.0, 0.0 );	
	//SkPolygonFill( v );

	/*
	** Quad from (40,30) to (30,50), CCW, LR, green
	* PASS
	*/
	vector<vector<int> > v1;
	vtx.clear();
	vtx.push_back(40);
	vtx.push_back(30);
	v1.push_back(vtx);

	vtx.clear();
	vtx.push_back(40);
	vtx.push_back(50);
	v1.push_back(vtx);

	vtx.clear();
	vtx.push_back(30);
	vtx.push_back(50);
	v1.push_back(vtx);

	vtx.clear();
	vtx.push_back(30);
	vtx.push_back(30);
	v1.push_back(vtx);

	glColor3f( 0.0, 1.0, 0.0 );
	//SkPolygonFill( v1 );

	/*
	** Quad, (10,70) to (40,90), UR, CW, blue
	* PASS
	*/
	vector<vector<int> > v2;
	vtx.clear();
	vtx.push_back(40);
	vtx.push_back(90);
	v2.push_back(vtx);

	vtx.clear();
	vtx.push_back(40);
	vtx.push_back(70);
	v2.push_back(vtx);

	vtx.clear();
	vtx.push_back(10);
	vtx.push_back(70);
	v2.push_back(vtx);

	vtx.clear();
	vtx.push_back(10);
	vtx.push_back(90);
	v2.push_back(vtx);

	glColor3f( 0.0, 0.0, 1.0 );
	//SkPolygonFill( v2 );

	/*
	** Quad, (10,210) to (40,230), UL, CW
	* 
	*/
	cout << endl;
	cout << "Yellowish Quad" << endl;
	vector<vector<int> > v3;
	vtx.clear();
	vtx.push_back(10);
	vtx.push_back(230);
	v3.push_back(vtx);

	vtx.clear();
	vtx.push_back(40);
	vtx.push_back(230);
	v3.push_back(vtx);

	vtx.clear();
	vtx.push_back(40);
	vtx.push_back(210);
	v3.push_back(vtx);

	vtx.clear();
	vtx.push_back(10);
	vtx.push_back(210);
	v3.push_back(vtx);


	glColor3f( 0.0, 1.0, 1.0 );
	SkPolygonFill( v3 );

	/*
	** Triangle, isoceles. aligned lower edge, magenta
	* Missing top tip
	*/
	cout << endl;
	cout << "Magenta Triangle" << endl;
	vector<vector<int> > v4;
	
	vtx.clear();
	vtx.push_back(100);
	vtx.push_back(10);
	v4.push_back(vtx);

	vtx.clear();
	vtx.push_back(150);
	vtx.push_back(10);
	v4.push_back(vtx);

	vtx.clear();
	vtx.push_back(125);
	vtx.push_back(20);
	v4.push_back(vtx);

	glColor3f( 1.0, 0.0, 1.0 );
	SkPolygonFill( v4 );

	/*
	** Triangle, aligned top, tail on left, yellow
	*/
	cout << endl;
	cout << "Yellow Triangle" << endl;
	vector<vector<int> > v5;
	vtx.clear();
	vtx.push_back(100);
	vtx.push_back(30);
	v5.push_back(vtx);

	vtx.clear();
	vtx.push_back(140);
	vtx.push_back(50);
	v5.push_back(vtx);

	vtx.clear();
	vtx.push_back(175);
	vtx.push_back(50);
	v5.push_back(vtx);

	glColor3f( 1.0, 1.0, 0.0 );
	SkPolygonFill( v5 );

	/*
	** Triangle, aligned top, tail on right, black
	*/
	cout << endl;
	cout << "Black Triangle" << endl;

	vector<vector<int> > v6;
	vtx.clear();
	vtx.push_back(120);
	vtx.push_back(40);
	v6.push_back(vtx);

	vtx.clear();
	vtx.push_back(80);
	vtx.push_back(60);
	v6.push_back(vtx);

	vtx.clear();
	vtx.push_back(45);
	vtx.push_back(60);
	v6.push_back(vtx);

	glColor3f( 0.0, 0.0, 0.0 );
	SkPolygonFill( v6 );

	/*
	** Triangle, right
	*/
	cout << endl;
	cout << "Right Triangle" << endl;

	vector<vector<int> > v7;
	vtx.clear();
	vtx.push_back(10);
	vtx.push_back(100);
	v7.push_back(vtx);

	vtx.clear();
	vtx.push_back(10);
	vtx.push_back(120);
	v7.push_back(vtx);

	vtx.clear();
	vtx.push_back(25);
	vtx.push_back(100);
	v7.push_back(vtx);

	glColor3f( 1.0, 1.0, 0.5 );
	SkPolygonFill( v7 );

	/*
	** Triangle, right
	*/
	cout << endl;
	cout << "Right Triangle" << endl;

	vector<vector<int> > v8;
	vtx.clear();
	vtx.push_back(10);
	vtx.push_back(130);
	v8.push_back(vtx);

	vtx.clear();
	vtx.push_back(20);
	vtx.push_back(130);
	v8.push_back(vtx);

	vtx.clear();
	vtx.push_back(20);
	vtx.push_back(140);
	v8.push_back(vtx);

	glColor3f( 1.0, 0.5, 1.0 );
	SkPolygonFill( v8 );

	/*
	** Triangle, right
	*/
	cout << endl;
	cout << "Right Triangle" << endl;

	vector<vector<int> > v9;
	vtx.clear();
	vtx.push_back(10);
	vtx.push_back(170);
	v9.push_back(vtx);

	vtx.clear();
	vtx.push_back(20);
	vtx.push_back(170);
	v9.push_back(vtx);

	vtx.clear();
	vtx.push_back(10);
	vtx.push_back(150);
	v9.push_back(vtx);

	glColor3f( 0.5, 1.0, 1.0 );
	SkPolygonFill( v9 );

	/*
	** Triangle, aligned bottom, tail upper left
	*/
	cout << endl;
	cout << "Right Triangle more reddish" << endl;


	vector<vector<int> > v10;
	vtx.clear();
	vtx.push_back(100);
	vtx.push_back(70);
	v10.push_back(vtx);

	vtx.clear();
	vtx.push_back(150);
	vtx.push_back(70);
	v10.push_back(vtx);

	vtx.clear();
	vtx.push_back(75);
	vtx.push_back(90);
	v10.push_back(vtx);

	glColor3f( 1.0, 0.5, 0.5 );
	SkPolygonFill( v10 );

	/*
	** Triangle, aligned bottom, tail upper right
	*/
	cout << endl;
	cout << "Right Triangle more blueish" << endl;


	vector<vector<int> > v11;
	vtx.clear();
	vtx.push_back(100);
	vtx.push_back(100);
	v11.push_back(vtx);

	vtx.clear();
	vtx.push_back(150);
	vtx.push_back(100);
	v11.push_back(vtx);

	vtx.clear();
	vtx.push_back(195);
	vtx.push_back(120);
	v11.push_back(vtx);

	glColor3f( 0.5, 0.5, 1.0 );
	SkPolygonFill( v11 );

	/*
	** Triangle, scalene
	*/
	cout << endl;
	cout << "Scalene Triangle gray" << endl;

	vector<vector<int> > v12;
	vtx.clear();
	vtx.push_back(100);
	vtx.push_back(170);
	v12.push_back(vtx);

	vtx.clear();
	vtx.push_back(150);
	vtx.push_back(150);
	v12.push_back(vtx);

	vtx.clear();
	vtx.push_back(175);
	vtx.push_back(130);
	v12.push_back(vtx);

	glColor3f( 0.5, 0.5, 0.5 );
	SkPolygonFill( v12 );

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

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
