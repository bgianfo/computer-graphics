/*
** File:	shape.cpp
** Authors:	Christopher Kulla, Reynold Bailey
** Contributors: J. Geigel, W. Carithers, Brian Gianforcaro
*/

#include "shape.h"
#include "draw_routines.h"
#include <fstream>

// you must edit this file

const double PI = 3.14159265359;

Shape::~Shape() {
}

void Shape::draw() {
	for( unsigned int i = 0; i < vertices.size(); i += 3 )
		DrawRoutines::drawTriangle( vertices[i],
					    vertices[i + 1],
					    vertices[i + 2]   );
}

Shape::Shape() : vertices() {
}

void Shape::addTriangle(const Point3 &p1, const Point3 &p2, const Point3 &p3) {
	vertices.push_back(p1);
	vertices.push_back(p2);
	vertices.push_back(p3);
}

Cube::Cube(int n) : Shape() {
    const double DIM = 0.5;
    const double R = (2*DIM)/n;
    for ( int face = 0; face < 6; face++ ) {
        double xval = -(DIM);
        for ( int i = 0; i < n; i++ ) {
            double yval = DIM;
            for ( int j = 0; j < n; j++ ) {
                Point3 p1; Point3 p2; Point3 p3; Point3 p4;
                switch ( face ) {
                    case 0: //FRONT
                        p3.x = xval;   p3.y = yval;   p3.z = DIM;
                        p1.x = xval;   p1.y = yval-R; p1.z = DIM;
                        p4.x = xval+R; p4.y = yval;   p4.z = DIM;
                        p2.x = xval+R; p2.y = yval-R; p2.z = DIM;
                        break;
                    case 1: //BACK
                        p4.x = xval;   p4.y = yval;   p4.z = -DIM;
                        p2.x = xval;   p2.y = yval-R; p2.z = -DIM;
                        p3.x = xval+R; p3.y = yval;   p3.z = -DIM;
                        p1.x = xval+R; p1.y = yval-R; p1.z = -DIM;
                        break;
                    case 2: //LEFT
                        p1.x = -DIM;   p1.y = yval;   p1.z = xval;
                        p2.x = -DIM;   p2.y = yval-R; p2.z = xval;
                        p3.x = -DIM;   p3.y = yval;   p3.z = xval+R;
                        p4.x = -DIM;   p4.y = yval-R; p4.z = xval+R;
                        break;
                    case 3: //RIGHT
                        p3.x = DIM;    p3.y = yval;   p3.z = xval;
                        p4.x = DIM;    p4.y = yval-R; p4.z = xval;
                        p1.x = DIM;    p1.y = yval;   p1.z = xval+R;
                        p2.x = DIM;    p2.y = yval-R; p2.z = xval+R;
                        break;
                    case 4: //TOP
                        p3.x = xval;   p3.y = DIM;    p3.z = yval;
                        p4.x = xval;   p4.y = DIM;    p4.z = yval-R;
                        p1.x = xval+R; p1.y = DIM;    p1.z = yval;
                        p2.x = xval+R; p2.y = DIM;    p2.z = yval-R;
                        break;
                    case 5: //BOTTOM
                        p1.x = xval;   p1.y = -DIM;   p1.z = yval;
                        p2.x = xval;   p2.y = -DIM;   p2.z = yval-R;
                        p3.x = xval+R; p3.y = -DIM;   p3.z = yval;
                        p4.x = xval+R; p4.y = -DIM;   p4.z = yval-R;
                        break;
                }
                addTriangle(p4,p3,p1);
                addTriangle(p4,p1,p2);
                yval -= R; 
            }
            xval += R;
        }
    }
}

Cone::Cone(int n, int m) : Shape() {
	if( n < 3 )
		n = 3;
	// Your code for tessellating a cone goes here
	const static double MINY = -0.5;	
	const static double MAXY = 0.5;	
	const static double RAD = 0.5;
	double RADDEC = RAD/(double)m;
	double YINC = 2*(MAXY/(double)m);

	for ( double i = 0; i < 360; i += 360/(double)n ) {
		Point3 a; Point3 b; Point3 c; Point3 d; 
		double degl = i*(PI/180);
		double degr = (i+(360/(double)n))*(PI/180);

	    a.x = cos(degl)*RAD; a.z = sin(degl)*RAD; a.y = MINY;
	    b.x = cos(degr)*RAD; b.z = sin(degr)*RAD; b.y = MINY;
		c.x = 0; c.z = 0; c.y = MINY;
		addTriangle(a,b,c);
	
		double yval = MINY;
		c.y = yval; d.y = yval;
		double r = RAD;
		for (int j = 1; j < m; j++) {
			a.y = yval;
			b.y = yval;
			r = r - RADDEC;

			c.x = cos(degl)*r; c.z = sin(degl)*r; c.y += YINC;
	    	d.x = cos(degr)*r; d.z = sin(degr)*r; d.y += YINC;

			addTriangle(d,b,a);
			addTriangle(c,d,a);

			a.x = c.x; a.z = c.z;
			b.x = d.x; b.z = d.z;
			yval += YINC;
		}

		a.y = yval;
		b.y = yval;
		c.x = 0; c.z = 0; c.y = MAXY;
		addTriangle(c,b,a);
	}
}

Cylinder::Cylinder(int n, int m) : Shape() {
	if( n < 3 )
		n = 3;

	// Your code for tessellating a cylinder goes here
	const static double MINY = -0.5;	
	const static double MAXY = 0.5;	
	const static double RAD = 0.5;
	
	const double YINC = (2*MAXY)/m;
	for ( int i = 0; i < 360; i += 360/n ) {
		Point3 a; Point3 b; Point3 c; Point3 d; 
		double degl = i*(PI/180);
		double degr = (i+(360/n))*(PI/180);
	    a.x = cos(degl)*RAD; a.z = sin(degl)*RAD; a.y = MAXY;
	    b.x = cos(degr)*RAD; b.z = sin(degr)*RAD; b.y = MAXY;
		c.x = 0; c.z = 0; c.y = MAXY;
		addTriangle(c,b,a);
	
		c.x = a.x; c.z = a.z;
		d.x = b.x; d.z = b.z;
		double yval = MAXY;
		for (int j = 0; j < m; j++) {
			a.y = yval;
			b.y = yval;
			c.y = yval- YINC;	
			d.y = yval- YINC;	
			addTriangle(a,b,c);
			addTriangle(c,b,d);
			yval -= YINC;
		}
		c.x = 0; c.z = 0; c.y = MINY;
		a.y = MINY; b.y = MINY;
		addTriangle(a,b,c);
	}
}

Sphere::Sphere(int n) : Shape() {
#define T(a,b,c) addTriangle(a,b,c);
	// Your code for tessellating a sphere goes here
	if (n > 5) 
		n = 5;

	const static double A = 2/(1+sqrt(5));
	const static double R = .5;

	Point3 v0;Point3 v1;Point3 v2;Point3 v3;Point3 v4; Point3 v5;
	Point3 v6;Point3 v7;Point3 v8;Point3 v9;Point3 v10;Point3 v11;
	v0.x = 0; v0.y = A; v0.z =-R;    v1.x =-A; v1.y = R; v1.z = 0;
	v2.x = A; v2.y = R; v2.z = 0;    v3.x = 0; v3.y = A; v3.z = R;
	v4.x =-R; v4.y = 0; v4.z = A;    v5.x = 0; v5.y =-A; v5.z = R;
	v6.x = R; v6.y = 0; v6.z = A;    v7.x = R; v7.y = 0; v7.z =-A;
	v8.x = 0; v8.y =-A; v8.z =-R;    v9.x =-R; v9.y = 0; v9.z =-A;
   v10.x =-A; v10.y=-R;v10.z = 0;   v11.x = A;v11.y =-R;v11.z = 0;


    T(v0,v1,v2);  T(v3,v2,v1);
    T(v3,v4,v5);  T(v3,v5,v6);
    T(v0,v7,v8);  T(v0,v8,v9);
    T(v5,v10,v11);T(v8,v11,v10);
    T(v1,v9,v4);  T(v10,v4,v9);
    T(v2,v6,v7);  T(v11,v7,v6);
    T(v3,v1,v4);  T(v3,v6,v2);
    T(v0,v9,v1);  T(v0,v2,v7);
    T(v8,v10,v9); T(v8,v7,v11);
    T(v5,v4,v10); T(v5,v11,v6);

#undef T
	// Note:
	// If you decide to solve this problem by recursively subdividing
	// a regular platonic solid, you may use the geometric
	// description of an icosahredron mesh provided in the lecture
	// notes as a starting point for the subdivision.
	//
	// You should divide each triangle into 4 smaller triangles as the
	// parameter 'n' increases.  There is no need to go beyond 5
	// levels of subdivision - i.e. if n > 5 then set n = 5

}

Sphere::Sphere(int n, const Point3 &p1, const Point3 &p2, const Point3 &p3) :Shape() {

}
