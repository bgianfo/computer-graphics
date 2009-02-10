/*
** File:	shape.cpp
** Authors:	Christopher Kulla, Reynold Bailey
** Contributors: J. Geigel, W. Carithers, ?
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

	// Your code for tessellating a cube goes here

}

Cone::Cone(int n, int m) : Shape() {
	if( n < 3 )
		n = 3;

	// Your code for tessellating a cone goes here

}

Cylinder::Cylinder(int n, int m) : Shape() {
	if( n < 3 )
		n = 3;

	// Your code for tessellating a cylinder goes here

}

Sphere::Sphere(int n) : Shape() {

	// Your code for tessellating a sphere goes here


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
