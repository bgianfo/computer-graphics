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
    const float DIM = 0.5;
    const float R = (2*DIM)/n;

    for (int face = 0; face < 7; face++) {
        float xval = -(DIM);
        for (int i = 0; i < n; i++) {
            float yval = DIM;
            for (int j = 0; j < n; j++) {
                Point3 p1; Point3 p2; Point3 p3; Point3 p4;
                switch (face) {
                    case 0: //FRONT
                        p1.x = xval;   p1.y = yval;   p1.z = DIM;
                        p2.x = xval;   p2.y = yval-R; p2.z = DIM;
                        p3.x = xval+R; p3.y = yval;   p3.z = DIM;
                        p4.x = xval+R; p4.y = yval-R; p4.z = DIM;
                        addTriangle(p1,p2,p3);
                        addTriangle(p4,p3,p2);
                        break;
                    case 1: //BACK
                        p3.x = xval;   p3.y = yval;   p3.z = -DIM;
                        p4.x = xval;   p4.y = yval-R; p4.z = -DIM;
                        p1.x = xval+R; p1.y = yval;   p1.z = -DIM;
                        p2.x = xval+R; p2.y = yval-R; p2.z = -DIM;
                        addTriangle(p1,p2,p3);
                        addTriangle(p4,p3,p2);
                        break;
                    case 2: //LEFT
                        p1.x = -DIM; p1.y = yval;   p1.z = xval;
                        p2.x = -DIM; p2.y = yval-R; p2.z = xval;
                        p3.x = -DIM; p3.y = yval;   p3.z = xval+R;
                        p4.x = -DIM; p4.y = yval-R; p4.z = xval+R;
                        addTriangle(p4,p3,p1);
                        addTriangle(p4,p1,p2);
                        break;
                    case 3: //RIGHT
                        p3.x = DIM; p3.y = yval;   p3.z = xval;
                        p4.x = DIM; p4.y = yval-R; p4.z = xval;
                        p1.x = DIM; p1.y = yval;   p1.z = xval+R;
                        p2.x = DIM; p2.y = yval-R; p2.z = xval+R;
                        addTriangle(p4,p3,p1);
                        addTriangle(p4,p1,p2);
                        break;
                    case 4: //TOP
                        p3.x = xval;   p3.y = DIM/*yval*/;   p3.z = yval;
                        p4.x = xval;   p4.y = DIM/*yval-R*/; p4.z = yval-R;
                        p1.x = xval+R; p1.y = DIM/*yval*/;   p1.z = yval;
                        p2.x = xval+R; p2.y = DIM/*yval-R*/; p2.z = yval-R;
                        addTriangle(p4,p3,p1);
                        addTriangle(p4,p1,p2);

                        break;
                    case 5: //BOTTOM
                        p1.x = xval;   p1.y = -DIM/*yval*/;   p1.z = yval;
                        p2.x = xval;   p2.y = -DIM/*yval-R*/; p2.z = yval-R;
                        p3.x = xval+R; p3.y = -DIM/*yval*/;   p3.z = yval;
                        p4.x = xval+R; p4.y = -DIM/*yval-R*/; p4.z = yval-R;
                        addTriangle(p4,p3,p1);
                        addTriangle(p4,p1,p2);
                        break;

                }
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
